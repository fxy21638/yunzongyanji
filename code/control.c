// 电机与舵机转向控制, 含速度自适应与加速度限制

#include "control.h"
#include "encoder.h"
#include "icm.h"
#include "servo.h"
#include "motor.h"
#include "vision.h"
#include "track_fsm.h"

float speed_base = 65;

// 速度模式: 1=开环固定PWM, 0=编码器闭环增量PID
#define FIXED_SPEED_DEBUG 0
#define FIXED_PWM_DUTY 600

// 转向: 0=像素偏差PID, 1=Pure Pursuit (需BEV数据)
#define VISION_USE_PURE_PURSUIT 0

/* 速度自适应: 偏移越大速度越慢 */
#define SPEED_ERR_COEFF   0.30f   /* 偏移→速度衰减系数, 越大转弯越慢 */
#define SPEED_MIN         25.0f   /* 最低速度 */
#define SPEED_ACCEL_MAX   1.0f    /* 每帧(5ms)最大加速量, 防甩尾 */

/* TODO: 角度环融合 — 从图像中线偏移计算赛道方向, 修正车身姿态
   ANGLE_BLEND_WEIGHT: 角度环占比 (0.15~0.35), 越大角度环越强
   ANGLE_BLEND_KP:     角度环比例 (0.2~0.6), 输入单位=中线偏移像素
   ANGLE_BLEND_KD:     角度环微分/阻尼 (0.3~1.0) */
#define ANGLE_BLEND_WEIGHT 0.25f
#define ANGLE_BLEND_KP     0.35f
#define ANGLE_BLEND_KD     0.50f

float gyro_target = 0;
uint8_t turn_step = 0;

float speed_l = 0;
float speed_r = 0;
float speed_now_l = 0;
float speed_now_r = 0;
static uint8_t speed_tune_mode = 0;

/* 陀螺仪 Z 轴积分: 追踪环岛已转过角度 */
int32_t cnt_degree = 0;
float ring_start_yaw = 0.0f;

/* 加速度限制: 记录上帧目标速度 */
static float speed_target_prev = 0.0f;

static void control_timer_callback(void)
{
    float gyro_z_dps;

    encoder_task();

    /* 陀螺仪 Z 轴积分: 追踪环岛转角 */
    gyro_z_dps = icm_get_gyro_z_dps();
    cnt_degree += (int32_t)(gyro_z_dps * 5.0f);  /* dps × 5ms → 毫度累计 */

    if (speed_tune_mode)
    {
        motor_speed_control();
        servo_set_wheel_angle(0.0f);
        Set_PWM((int16_t)speed_now_l, (int16_t)speed_now_r);
        return;
    }

    if (track_element == NONE)
    {
        motor_clear();
        servo_set_wheel_angle(0.0f);
        Set_PWM(0, 0);
        return;
    }

#if FIXED_SPEED_DEBUG
    {
        float spd_factor;
        float fsm_speed;
        float spd;

        spd_factor = trail_speed_factor();
        fsm_speed  = track_fsm_get_speed_factor(&g_track_fsm);
        spd = (float)FIXED_PWM_DUTY * spd_factor * fsm_speed;
        speed_now_l = spd;
        speed_now_r = spd;
    }
#else
    motor_speed_control();
#endif
    steering_control();
    Set_PWM((int16_t)speed_now_l, (int16_t)speed_now_r);
}

void control_Init(void)
{
    timer_init_ms(TIM_1, 5, control_timer_callback);
}

void control_set_speed_tune_mode(uint8_t enable)
{
    speed_tune_mode = enable;
    if (!enable) return;
    motor_clear();
    servo_set_wheel_angle(0.0f);
}

void all_control(void)
{
    if (track_element == NONE)
    {
        motor_clear();
        servo_set_wheel_angle(0.0f);
        return;
    }
    motor_speed_control();
    steering_control();
}

void motor_clear(void)
{
    speed_l = 0;
    speed_r = 0;
    speed_now_l = 0;
    speed_now_r = 0;
    speed_pid_l.output = 0;
    speed_pid_l.error_prev = 0;
    speed_pid_l.error_prev2 = 0;
    speed_pid_r.output = 0;
    speed_pid_r.error_prev = 0;
    speed_pid_r.error_prev2 = 0;
}

void motor_speed_control(void)
{
    float target_speed;
    float spd_factor;
    float fsm_speed;
    float track_err;
    float err_reduction;

    spd_factor = trail_speed_factor();
    fsm_speed  = track_fsm_get_speed_factor(&g_track_fsm);

    /* 速度 = 基准 - 系数 × |偏移|, 偏移越大速度越慢 */
    track_err = (float)CENTER_POINT - (float)track_midpoint_target;
    if (track_err < 0.0f) track_err = -track_err;
    err_reduction = SPEED_ERR_COEFF * track_err;
    target_speed = (speed_base - err_reduction) * spd_factor * fsm_speed;

    if (target_speed < SPEED_MIN)
        target_speed = SPEED_MIN;

    /* 加速度限制: 每帧最多增加 SPEED_ACCEL_MAX (防甩尾) */
    {
        float delta;
        delta = target_speed - speed_target_prev;
        if (delta > SPEED_ACCEL_MAX)
            target_speed = speed_target_prev + SPEED_ACCEL_MAX;
    }
    speed_target_prev = target_speed;

    // 增量PID内部已累加+限幅, 直接赋值
    speed_now_l = IncrementalPID_Calculate(&speed_pid_l, target_speed - (float)encoder_data_dir[0]);
    speed_now_r = IncrementalPID_Calculate(&speed_pid_r, target_speed - (float)encoder_data_dir[1]);
}

void steering_control(void)
{
    float steer_output;
    uint16_t y;
    int16_t last_l, last_r;
    uint8_t emergency;

#if 1
	    // ====== Emergency recovery ======
	    emergency = 0;
	    steer_output = 0.0f;
	    last_l = -1;
	    last_r = -1;

	    if (!g_track_valid ||
	        g_track.feature == VISION_FEATURE_LOST ||
	        g_track.visible_high > (uint8_t)(MT9V034_HEIGHT - 25) ||
	        track_element == BROKEN)
	    {
	        for (y = (uint16_t)(MT9V034_HEIGHT / 2); y < MT9V034_HEIGHT; y++)
	        {
	            if (g_track.left[y] > 2)  last_l = g_track.left[y];
	            if (g_track.right[y] < (int16_t)(MT9V034_WIDTH - 4)) last_r = g_track.right[y];
	        }

	        if (last_l >= 0 && last_r < 0)
	        {
	            emergency = 1;
	            steer_output = -STEER_OUTPUT_LIMIT;
	        }
	        else if (last_r >= 0 && last_l < 0)
	        {
	            emergency = 2;
	            steer_output = STEER_OUTPUT_LIMIT;
	        }
	        else if (last_l < 0 && last_r < 0)
	        {
	            static int8_t last_emergency_dir = 0;
	            if (last_emergency_dir == 0) last_emergency_dir = -1;
	            emergency = 3;
	            steer_output = (float)last_emergency_dir * STEER_OUTPUT_LIMIT * 0.25f;
	        }
	    }

	    if (emergency)
	    {
	        speed_now_l = FIXED_PWM_DUTY / 3;
	        speed_now_r = FIXED_PWM_DUTY / 3;
	        servo_set_wheel_angle(steer_output);
	        return;
	    }
#endif

    // ====== 正常转向 ======
#if VISION_USE_PURE_PURSUIT
    // 纯追踪模式: 直接使用预计算转向角
    // pp_steering_angle 单位=度, 正值右转
    {
        float pp_err;
        float ema_alpha;
        float fsm_Kp;
        float fsm_Kd;
        static float steer_smooth = 0.0f;

        pp_err    = pp_steering_angle;
        ema_alpha = track_fsm_get_ema_alpha(&g_track_fsm);

        if (track_element == BROKEN_RODE)
        {
            fsm_Kp = track_fsm_get_Kp(&g_track_fsm);
            fsm_Kd = track_fsm_get_Kd(&g_track_fsm);

            pid_gyro.Kp = fsm_Kp;
            pid_gyro.Kd = fsm_Kd;
            steer_output = PositionalPID_Calculate(&pid_gyro, gyro_target - yaw);
        }
        else
        {
            float pp_gain;
            pp_gain = 0.55f;

            fsm_Kp = track_fsm_get_Kp(&g_track_fsm);
            fsm_Kd = track_fsm_get_Kd(&g_track_fsm);

            pid_pos.Kp = fsm_Kp;
            pid_pos.Kd = fsm_Kd;
            steer_output = PositionalPID_Calculate(&pid_pos, pp_err);
            steer_output = pp_err * pp_gain;
        }

        steer_output = SATURATE(steer_output, -STEER_OUTPUT_LIMIT, STEER_OUTPUT_LIMIT);

        steer_output = steer_smooth * (1.0f - ema_alpha) + steer_output * ema_alpha;
        steer_smooth = steer_output;

        servo_set_wheel_angle(steer_output);
        return;
    }
#else
    // 像素偏差模式: 基于中线偏移的逐状态 PID 转向
    {
        float track_error;
        float ema_alpha;
        float fsm_Kp;
        float fsm_Kd;
        float fsm_Ki;
        float fsm_imax;
        float fsm_angle_kp;
        float fsm_angle_ki;
        float fsm_angle_kd;
        float fsm_angle_imax;
        float fsm_angle_w;
        static float steer_smooth = 0.0f;

        track_error = (float)CENTER_POINT - (float)track_midpoint_target;
        ema_alpha  = track_fsm_get_ema_alpha(&g_track_fsm);

    if (track_element == BROKEN_RODE)
    {
        fsm_Kp = track_fsm_get_Kp(&g_track_fsm);
        fsm_Kd = track_fsm_get_Kd(&g_track_fsm);
        fsm_Ki = track_fsm_get_Ki(&g_track_fsm);
        fsm_imax = track_fsm_get_integral_max(&g_track_fsm);

        pid_gyro.Kp = fsm_Kp;
        pid_gyro.Kd = fsm_Kd;
        pid_gyro.Ki = fsm_Ki;
        pid_gyro.integral_max = fsm_imax;
        steer_output = PositionalPID_Calculate(&pid_gyro, gyro_target - yaw);
    }
    else
    {
        float pos_out;
        float ang_out;
        float track_dx;

        fsm_Kp = track_fsm_get_Kp(&g_track_fsm);
        fsm_Kd = track_fsm_get_Kd(&g_track_fsm);
        fsm_Ki = track_fsm_get_Ki(&g_track_fsm);
        fsm_imax = track_fsm_get_integral_max(&g_track_fsm);
        fsm_angle_kp = track_fsm_get_angle_kp(&g_track_fsm);
        fsm_angle_ki = track_fsm_get_angle_ki(&g_track_fsm);
        fsm_angle_kd = track_fsm_get_angle_kd(&g_track_fsm);
        fsm_angle_imax = track_fsm_get_angle_imax(&g_track_fsm);
        fsm_angle_w  = track_fsm_get_angle_weight(&g_track_fsm);

        /* 图像赛道方向: 中线近远偏移 */
        {
            int16_t l_near, r_near;
            int16_t l_far, r_far;
            int16_t c_near, c_far;
            uint16_t ny, fy;

            ny = (uint16_t)(MT9V034_HEIGHT - 20);
            fy = (uint16_t)VISION_LOOKAHEAD_Y;

            l_near = g_track.left[ny];
            r_near = g_track.right[ny];
            l_far  = g_track.left[fy];
            r_far  = g_track.right[fy];

            if (l_near > 2 && r_near < (int16_t)(MT9V034_WIDTH - 4) &&
                l_far  > 2 && r_far  < (int16_t)(MT9V034_WIDTH - 4))
            {
                c_near = (l_near + r_near) / 2;
                c_far  = (l_far + r_far) / 2;
                track_dx = (float)(c_far - c_near);
            }
            else
            {
                track_dx = 0.0f;
            }
        }

        /* 位置 PID */
        pid_pos.Kp = fsm_Kp;
        pid_pos.Kd = fsm_Kd;
        pid_pos.Ki = fsm_Ki;
        pid_pos.integral_max = fsm_imax;
        pos_out = PositionalPID_Calculate(&pid_pos, track_error);

        /* 角度 PID: 赛道右偏(dx>0) → 右转(-dx<0) */
        pid_gyro.Kp = fsm_angle_kp;
        pid_gyro.Ki = fsm_angle_ki;
        pid_gyro.Kd = fsm_angle_kd;
        pid_gyro.integral_max = fsm_angle_imax;
        ang_out = PositionalPID_Calculate(&pid_gyro, -track_dx);

        steer_output = pos_out * (1.0f - fsm_angle_w)
                     + ang_out * fsm_angle_w;
    }

    steer_output = SATURATE(steer_output, -STEER_OUTPUT_LIMIT, STEER_OUTPUT_LIMIT);

    steer_output = steer_smooth * (1.0f - ema_alpha) + steer_output * ema_alpha;
    steer_smooth = steer_output;

    servo_set_wheel_angle(steer_output);
    }
#endif
}

void motor_speed_position_control(void)
{
    motor_speed_control();
    steering_control();
}

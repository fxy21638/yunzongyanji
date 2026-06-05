// Motor + steering control with Pure Pursuit and speed adaptation

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

float gyro_target = 0;
float gyro_control = 60;
uint8_t turn_step = 0;

float speed_l = 0;
float speed_r = 0;
float speed_now_l = 0;
float speed_now_r = 0;
static uint8_t speed_tune_mode = 0;

static void control_timer_callback(void)
{
    encoder_task();

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

    spd_factor = trail_speed_factor();
    fsm_speed  = track_fsm_get_speed_factor(&g_track_fsm);
    target_speed = speed_base * spd_factor * fsm_speed;

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

#if 0
	    // ====== Emergency recovery (disabled for tuning) ======
	    emergency = 0;
	    steer_output = 0.0f;
	    last_l = -1;
	    last_r = -1;

	    if (!g_track_valid ||
	        g_track.feature == VISION_FEATURE_LOST ||
	        g_track.valid_rows < 5)
	    {
	        for (y = (uint16_t)(MT9V034_HEIGHT / 2); y < MT9V034_HEIGHT; y++)
	        {
	            if (g_track.left[y] >= 0)  last_l = g_track.left[y];
	            if (g_track.right[y] >= 0) last_r = g_track.right[y];
	        }

	        if (last_l >= 0 && last_r < 0)
	        {
	            emergency = 1;
	            steer_output = STEER_OUTPUT_LIMIT;
	        }
	        else if (last_r >= 0 && last_l < 0)
	        {
	            emergency = 2;
	            steer_output = -STEER_OUTPUT_LIMIT;
	        }
	        else if (last_l < 0 && last_r < 0)
	        {
	            static int8_t last_emergency_dir = 0;
	            if (last_emergency_dir == 0) last_emergency_dir = 1;
	            emergency = 3;
	            steer_output = (float)last_emergency_dir * STEER_OUTPUT_LIMIT * 0.5f;
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

    // ====== Normal steering ======
#if VISION_USE_PURE_PURSUIT
    // Pure Pursuit: use pre-computed steering angle directly
    // pp_steering_angle is in degrees, positive = right turn
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

#if (CASCADE_PID == 1)
            pid_gyro.Kp = fsm_Kp;
            pid_gyro.Kd = fsm_Kd;
            steer_output = PositionalPID_Calculate(&pid_gyro, gyro_target - yaw);
#else
            inertia_pid.Kp = fsm_Kp;
            inertia_pid.Kd = fsm_Kd;
            steer_output = PositionalPID_Calculate(&inertia_pid, gyro_target - yaw);
#endif
        }
        else
        {
            float pp_gain;
            pp_gain = 0.55f;

            fsm_Kp = track_fsm_get_Kp(&g_track_fsm);
            fsm_Kd = track_fsm_get_Kd(&g_track_fsm);

#if (CASCADE_PID == 1)
            pid_pos.Kp = fsm_Kp;
            pid_pos.Kd = fsm_Kd;
            steer_output = PositionalPID_Calculate(&pid_pos, pp_err);
#else
            angle_pid.KP  = fsm_Kp;
            angle_pid.KD  = fsm_Kd;
            steer_output = AnglePID_Calculate(&angle_pid, pp_err);
#endif
            steer_output = pp_err * pp_gain;
        }

        steer_output = SATURATE(steer_output, -STEER_OUTPUT_LIMIT, STEER_OUTPUT_LIMIT);

        steer_output = steer_smooth * (1.0f - ema_alpha) + steer_output * ema_alpha;
        steer_smooth = steer_output;

        servo_set_wheel_angle(steer_output);
        return;
    }
#else
    // Original: pixel-error based steering with per-state PID
    {
        float track_error;
        float ema_alpha;
        float fsm_Kp;
        float fsm_Kd;
        static float steer_smooth = 0.0f;

        track_error = (float)CENTER_POINT - (float)track_midpoint_target;
        ema_alpha  = track_fsm_get_ema_alpha(&g_track_fsm);

    if (track_element == BROKEN_RODE)
    {
        fsm_Kp = track_fsm_get_Kp(&g_track_fsm);
        fsm_Kd = track_fsm_get_Kd(&g_track_fsm);

#if (CASCADE_PID == 1)
        pid_gyro.Kp = fsm_Kp;
        pid_gyro.Kd = fsm_Kd;
        steer_output = PositionalPID_Calculate(&pid_gyro, gyro_target - yaw);
#else
        inertia_pid.Kp = fsm_Kp;
        inertia_pid.Kd = fsm_Kd;
        steer_output = PositionalPID_Calculate(&inertia_pid, gyro_target - yaw);
#endif
    }
    else
    {
        fsm_Kp = track_fsm_get_Kp(&g_track_fsm);
        fsm_Kd = track_fsm_get_Kd(&g_track_fsm);

#if (CASCADE_PID == 1)
        pid_pos.Kp = fsm_Kp;
        pid_pos.Kd = fsm_Kd;
        steer_output = PositionalPID_Calculate(&pid_pos, track_error);
#else
        angle_pid.KP  = fsm_Kp;
        angle_pid.KD  = fsm_Kd;
        steer_output = AnglePID_Calculate(&angle_pid, track_error);
#endif
    }

    steer_output = SATURATE(steer_output, -STEER_OUTPUT_LIMIT, STEER_OUTPUT_LIMIT);

    steer_output = steer_smooth * (1.0f - ema_alpha) + steer_output * ema_alpha;
    steer_smooth = steer_output;

    servo_set_wheel_angle(steer_output);
    }
#endif
}

#if (CASCADE_PID == 1)
void motor_speed_position_control(void)
{
    motor_speed_control();
    steering_control();
}
#elif (CASCADE_PID == 2)
void motor_agle_control(void)
{
    motor_speed_control();
    steering_control();
}

void motor_inertia_control(void)
{
    motor_speed_control();
    steering_control();
}
#elif (CASCADE_PID == 3)
void motor_agle_control(void)
{
    motor_speed_control();
    steering_control();
}
#endif

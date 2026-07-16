// ====================================================================
// control.c — 舵机 PD + 差速电机 + 赛车线 + 编码器速度 PID
// 引脚定义保持不变
// ====================================================================

#include "control.h"
#include "encoder.h"
#include "icm.h"
#include "servo.h"
#include "motor.h"
#include "trail.h"
#include "laser.h"

/* ================================================================
 * 第 1 节 — 全局变量 + 全部可调参数
 * ================================================================ */

float speed_base = 45.0f; /* 基准速度 (直道全速) */
int16_t error = 0;
int16_t error_last = 0;
static float servo_d_filter = 0.0f;

/* ---- 舵机参数 ---- */
#define SERVO_P_BASE 0.50f   /* 直道小偏差 P */
#define SERVO_P_SCALE 0.010f /* P 随偏差增长率 (abs_err×SCALE) */
#define SERVO_P_MAX 1.20f    /* P 上限 */
#define SERVO_D 5.50f        /* D 固定 */
#define SERVO_D_FILTER 0.40f /* D 滤波: 旧值权重 (0~1, 越大越平滑) */
#define SERVO_LIMIT 50.0f    /* 舵机输出限幅 */

/* 十字用时 P 乘这个系数 */
#define CROSS_P_SCALE 2.00f /* 十字 P = SERVO_P_BASE × CROSS_P_SCALE */
#define CROSS_SPEED 32.0f   /* 十字基准速度 */
#define CROSS_DIFF_K 0.45f

/* ---- 电机速度参数 ---- */
#define MOTOR_KP 0.60f
#define MOTOR_KI 0.15f
#define MOTOR_KD 0.00f
#define MOTOR_D_LP 0.35f
#define PID_LIMIT 1500.0f      /* 正常限幅 */
#define PID_LIMIT_HILL 4000.0f /* 上坡限幅 */
#define MOTOR_I_MAX 500.0f     /* I 项上限 */
#define MOTOR_RAMP_UP 3.0f     /* 加速斜率 */
#define MOTOR_RAMP_DN 3.0f     /* 减速斜率 */
#define MOTOR_MIN_SPEED 30.0f  /* 最低速度 */

/* ---- 速度连续映射: speed = BASE - abs_err × SCALE, 下限 MIN ---- */
#define SPD_SCALE 0.30f  /* 偏差→减速系数 */
#define DIFF_K_MAX 0.20f /* 差速系数上限 */

/* ---- 坡道 ---- */
#define SLOPE_ENABLE 1
#define SLOPE_ENTER_DEG 10.0f
#define SLOPE_EXIT_DEG 3.0f
#define SLOPE_UP_SPEED 250.0f
#define SLOPE_DN_SPEED -20.0f

/* ---- 赛车线 (暂关闭: START_ERR=0) ---- */
#define RACING_LINE_START_ERR 0
#define RACING_LINE_MAX_OFFSET 30

/* 电机斜坡 */
static float g_speed_l_target = 0, g_speed_r_target = 0;
float speed_l = 0, speed_r = 0;
float speed_now_l = 0, speed_now_r = 0;
static uint8_t speed_tune_mode = 0;
int32_t cnt_degree = 0;
float ring_start_yaw = 0.0f;
uint8_t g_slope_detected = 0;

/* ==== 舵机 PD ==== */
static float g_z_p = SERVO_P_BASE, g_z_d = SERVO_D;

static void servo_pd_set(void)
{
    int16_t a;
    a = error;
    if (a < 0)
        a = -a;
    if (cross_state || cross_phase != CROSS_PHASE_NONE)
    {
        g_z_p = SERVO_P_BASE * CROSS_P_SCALE;
        g_z_d = SERVO_D;
    }
    else
    {
        g_z_p = SERVO_P_BASE + (float)a * SERVO_P_SCALE;
        if (g_z_p > SERVO_P_MAX)
            g_z_p = SERVO_P_MAX;
        g_z_d = SERVO_D;
    }
}

static void servo_pd(void)
{
    float d_error, servo_out;
    d_error = (float)(error - error_last);
    servo_d_filter = SERVO_D_FILTER * servo_d_filter + (1.0f - SERVO_D_FILTER) * d_error;
    servo_out = (float)error * g_z_p + servo_d_filter * g_z_d;
    if (servo_out > SERVO_LIMIT)
        servo_out = SERVO_LIMIT;
    if (servo_out < -SERVO_LIMIT)
        servo_out = -SERVO_LIMIT;
    servo_set_wheel_angle(servo_out);
    error_last = error;
}

/* ==== 编码器 ==== */
static float g_enc_l_speed = 0, g_enc_r_speed = 0;

static void encoder_smooth(void)
{
    int16_t raw_l, raw_r;
    raw_l = encoder_data_dir[0];
    raw_r = encoder_data_dir[1];
    g_enc_l_speed = g_enc_l_speed * 0.8f + (float)raw_l * 0.2f;
    g_enc_r_speed = g_enc_r_speed * 0.8f + (float)raw_r * 0.2f;
}

/* ==== 电机 PID ==== */
static float g_pid_l_out = 0, g_pid_r_out = 0;
static float g_pid_l_err = 0, g_pid_l_err1 = 0, g_pid_l_err2 = 0;
static float g_pid_r_err = 0, g_pid_r_err1 = 0, g_pid_r_err2 = 0;
static float g_pid_l_d = 0, g_pid_r_d = 0;

static float pid_increase(float *out, float *e, float *e1, float *e2,
                          float *d_filt, float target, float actual)
{
    float err, p_term, i_term, d_temp;
    float i_contrib, lim;

    err = target - actual;
    if (err < 1.0f && err > -1.0f)
        err = 0;
    p_term = err - *e1;
    i_term = err;
    d_temp = err - 2.0f * (*e1) + (*e2);

    *d_filt = MOTOR_D_LP * d_temp + (1.0f - MOTOR_D_LP) * (*d_filt);
    *e2 = *e1;
    *e1 = *e;
    *e = err;

    i_contrib = MOTOR_KI * i_term;
    if (i_contrib > MOTOR_I_MAX)
        i_contrib = MOTOR_I_MAX;
    if (i_contrib < -MOTOR_I_MAX)
        i_contrib = -MOTOR_I_MAX;
    *out += MOTOR_KP * p_term + i_contrib + MOTOR_KD * (*d_filt);

    lim = g_slope_detected ? PID_LIMIT_HILL : PID_LIMIT;
    if (*out > lim)
        *out = lim;
    if (*out < -lim)
        *out = -lim;
    return *out;
}

static float motor_target_ramp(float now, float target)
{
    if (target > now + MOTOR_RAMP_UP)
        return now + MOTOR_RAMP_UP;
    if (target < now - MOTOR_RAMP_DN)
        return now - MOTOR_RAMP_DN;
    return target;
}

static void motor_output(float spd_l, float spd_r)
{
    g_speed_l_target = motor_target_ramp(g_speed_l_target, spd_l);
    g_speed_r_target = motor_target_ramp(g_speed_r_target, spd_r);
    pid_increase(&g_pid_l_out, &g_pid_l_err, &g_pid_l_err1, &g_pid_l_err2,
                 &g_pid_l_d, g_speed_l_target, g_enc_l_speed);
    pid_increase(&g_pid_r_out, &g_pid_r_err, &g_pid_r_err1, &g_pid_r_err2,
                 &g_pid_r_d, g_speed_r_target, g_enc_r_speed);
    speed_now_l = g_pid_l_out;
    speed_now_r = g_pid_r_out;
    Set_PWM((int16_t)speed_now_l, (int16_t)speed_now_r);
}

/* ==== 差速 + 连续速度映射 ==== */
static void final_motor_control(int16_t base_speed, float diff_k, int16_t diff_limit)
{
    float diff, target_l, target_r;
    diff = (float)error * diff_k;
    if (diff > (float)diff_limit)
        diff = (float)diff_limit;
    if (diff < -(float)diff_limit)
        diff = -(float)diff_limit;
    target_l = (float)base_speed - diff;
    target_r = (float)base_speed + diff;
    if (target_l < MOTOR_MIN_SPEED)
        target_l = MOTOR_MIN_SPEED;
    if (target_r < MOTOR_MIN_SPEED)
        target_r = MOTOR_MIN_SPEED;
    motor_output(target_l, target_r);
}

static void track_motor_control(void)
{
    int16_t a;
    a = error;
    if (a < 0)
        a = -a;

    if (cross_state || cross_phase != CROSS_PHASE_NONE)
    {
        final_motor_control((int16_t)CROSS_SPEED, CROSS_DIFF_K, 12);
    }
    else
    {
        float spd, dk;
        int16_t dl;
        spd = (float)speed_base - (float)a * SPD_SCALE;
        if (spd < MOTOR_MIN_SPEED)
            spd = MOTOR_MIN_SPEED;
        dk = 0.10f + (float)a * 0.003f;
        if (dk > DIFF_K_MAX)
            dk = DIFF_K_MAX;
        dl = (int16_t)(10 + (a / 3));
        if (dl > 15)
            dl = 15;
        final_motor_control((int16_t)spd, dk, dl);
    }
}

/* ================================================================
 * 定时器 ISR
 * ================================================================ */

static void control_timer_callback(void)
{
    float gyro_z_dps;

    encoder_task();
    encoder_smooth();

    gyro_z_dps = icm_get_gyro_z_dps();
    cnt_degree += (int32_t)(gyro_z_dps * 5.0f);

    laser_off_handler(); /* 靶子激光倒计时 */

    /* 斑马线检测到 → 立即停车 */
    if (g_stop_detected)
    {
        control_clear();
        Set_PWM(0, 0);
        servo_set_wheel_angle(0.0f);
        return;
    }

    /* 坡道检测 */
#if SLOPE_ENABLE
    {
        static uint8_t slope_cnt = 0;
        if (roll > SLOPE_ENTER_DEG || roll < -SLOPE_ENTER_DEG)
        {
            slope_cnt++;
            if (slope_cnt > 3)
                g_slope_detected = 1;
        }
        else if (roll < SLOPE_EXIT_DEG && roll > -SLOPE_EXIT_DEG)
        {
            slope_cnt = 0;
            g_slope_detected = 0;
        }
        else
        {
            slope_cnt = 0;
            g_slope_detected = 0;
        }
    }
#endif

    if (speed_tune_mode)
    {
        motor_output(30, 30);
        servo_set_wheel_angle(0.0f);
        return;
    }

#define OBS_AVOID_ENABLE 0 /* 1=启用避障, 0=仅检测不避让 */

    /* 坡道速度调节 */
#if SLOPE_ENABLE
    if (g_slope_detected)
    {
        if (roll > 5.0f)
        {
            motor_output(250, 250); /* 上坡加速 */
        }
        else
        {
            motor_output(-20, -20); /* 下坡减速 */
        }
        return;
    }
#endif

    /* 障碍避让: 向空间大的一侧转向 + 减速 */
    if (OBS_AVOID_ENABLE && g_obstacle_detected)
    {
        float obs_steer;
        int16_t space_l, space_r;
        space_l = (int16_t)g_obstacle_center_x;
        space_r = (int16_t)(MT9V034_WIDTH - g_obstacle_center_x);
        /* 障碍在左 → 向右避, 障碍在右 → 向左避 */
        obs_steer = (space_l < space_r) ? 30.0f : -30.0f;
        servo_set_wheel_angle(obs_steer);
        motor_output(25, 25); /* 减速 */
        return;
    }

    /* error = Image_Error (trail.c 底部中线偏差, 已含 EMA 滤波) */
    error = Image_Error;

    servo_pd_set();        /* 选 PD 参数 */
    servo_pd();            /* PD 计算 + 舵机输出 */
    track_motor_control(); /* 速度档位 + 电机输出 */
}

/* ================================================================
 * 第 12 节 — 接口
 * ================================================================ */

void control_Init(void)
{
    timer_init_ms(TIM_1, 5, control_timer_callback);
}

void control_set_speed_tune_mode(uint8_t enable)
{
    speed_tune_mode = enable;
    if (!enable)
        return;
    control_clear();
    servo_set_wheel_angle(0.0f);
}

void all_control(void) {}
void motor_speed_control(void) {}
void steering_control(void) {}
void motor_speed_position_control(void) {}

void control_clear(void)
{
    speed_l = speed_r = 0;
    speed_now_l = speed_now_r = 0;
    g_speed_l_target = g_speed_r_target = 0;
    g_pid_l_out = g_pid_r_out = 0;
    g_pid_l_err = g_pid_l_err1 = g_pid_l_err2 = 0;
    g_pid_r_err = g_pid_r_err1 = g_pid_r_err2 = 0;
    g_pid_l_d = g_pid_r_d = 0;
}

// 参考49.9完整移植: 舵机PD + 差速电机 + 赛车线 + 编码器速度PID
// 引脚定义保持不变

#include "control.h"
#include "encoder.h"
#include "icm.h"
#include "servo.h"
#include "motor.h"
#include "vision.h"

/* ================================================================
 * 第 1 节 全局变量
 * ================================================================ */
float speed_base = 28;
int16_t posi = 0;
int16_t error_last = 0;
static float servo_d_filter = 0.0f;

/* 电机斜坡 */
static float g_speed_l_target = 0;
static float g_speed_r_target = 0;

extern IncrementalPID speed_pid_l;
extern IncrementalPID speed_pid_r;

float speed_l = 0;
float speed_r = 0;
float speed_now_l = 0;
float speed_now_r = 0;
static uint8_t speed_tune_mode = 0;

int32_t cnt_degree = 0;
float ring_start_yaw = 0.0f;

/* ================================================================
 * 第 2 节 — 赛车线偏移 
 * ================================================================ */
#define RACING_LINE_START_ERR   9
#define RACING_LINE_MAX_OFFSET  10

static int16_t racing_line_offset(int16_t raw_error)
{
    int16_t abs_err, offset;
    abs_err = raw_error; if (abs_err < 0) abs_err = -abs_err;
    if (abs_err <= RACING_LINE_START_ERR) return 0;
    offset = (abs_err - RACING_LINE_START_ERR) / 2;
    if (offset > RACING_LINE_MAX_OFFSET) offset = RACING_LINE_MAX_OFFSET;
    if (raw_error > 0) return -offset;
    return offset;
}

/* ================================================================
 * 第 3 节 — 舵机PD参数选档 
 * ================================================================ */
static float g_z_p = 1.70f, g_z_d = 5.60f;

static void servo_pd_set(void)
{
    int16_t abs_err = posi; if (abs_err < 0) abs_err = -abs_err;

    /* D砍半 */
    if (track_element == RING_l || track_element == RING_r || track_element == RING_c)
        { g_z_p = 2.00f; g_z_d = 2.00f; }
    else if (track_element == CROSS)
        { g_z_p = 1.80f; g_z_d = 2.50f; }
    else if (abs_err >= 30)
        { g_z_p = 2.20f; g_z_d = 2.30f; }
    else if (abs_err >= 15)
        { g_z_p = 2.40f; g_z_d = 2.00f; }
    else
        { g_z_p = 1.70f; g_z_d = 2.80f; }
}

/* ================================================================
 * 第 4 节 — 舵机PD (servo_PD + servo_Control)
 * ================================================================ */
#define SERVO_PWM_LIMIT  75

static void servo_pd(void)
{
    float d_error, servo_out;
    d_error = (float)(posi - error_last);
    servo_d_filter = 0.3f * servo_d_filter + 0.7f * d_error;  /* 减滤波: 70%新值, D不残留 */
    servo_out = (float)posi * g_z_p + servo_d_filter * g_z_d;
    if (servo_out > (float)SERVO_PWM_LIMIT)  servo_out = (float)SERVO_PWM_LIMIT;
    if (servo_out < -(float)SERVO_PWM_LIMIT) servo_out = -(float)SERVO_PWM_LIMIT;
    servo_set_wheel_angle(servo_out);
    error_last = posi;
}

/* ================================================================
 * 第 5 节 — 编码器读取+滤波 (EncoderCount)
 * ================================================================ */
static float g_enc_l_speed = 0, g_enc_r_speed = 0;

static void encoder_smooth(void)
{
    int16_t raw_l, raw_r;
    raw_l = encoder_data_dir[0];
    raw_r = encoder_data_dir[1];
    /* EMA滤波: 49.9用 0.2*raw + 0.8*old */
    g_enc_l_speed = g_enc_l_speed * 0.8f + (float)raw_l * 0.2f;
    g_enc_r_speed = g_enc_r_speed * 0.8f + (float)raw_r * 0.2f;
}

/* ================================================================
 * 第 6 节 — 增量PID+低通D (PID_Increase)
 * ================================================================ */
static float g_pid_l_out = 0, g_pid_r_out = 0;
static float g_pid_l_err = 0, g_pid_l_err1 = 0, g_pid_l_err2 = 0;
static float g_pid_r_err = 0, g_pid_r_err1 = 0, g_pid_r_err2 = 0;
static float g_pid_l_d = 0, g_pid_r_d = 0;

#define MOTOR_KP    0.60f   
#define MOTOR_KI    0.15f
#define MOTOR_KD    0.50f
#define MOTOR_D_LP  0.35f
#define PID_LIMIT   1500

static float pid_increase(float *out, float *err, float *err1, float *err2,
                          float *d_filter, float target, float actual)
{
    float error, p_term, i_term, d_temp;
    error = target - actual;
    if (error < 1.0f && error > -1.0f) error = 0;  /* 死区 */
    p_term = error - *err1;        /* Δe */
    i_term = error;                 /* e(k) */
    d_temp = error - 2.0f*(*err1) + (*err2);
    *d_filter = MOTOR_D_LP * d_temp + (1.0f - MOTOR_D_LP) * (*d_filter);
    *err2 = *err1;
    *err1 = *err;
    *err = error;
    *out += MOTOR_KP * p_term + MOTOR_KI * i_term + MOTOR_KD * (*d_filter);
    if (*out > (float)PID_LIMIT)  *out = (float)PID_LIMIT;
    if (*out < -(float)PID_LIMIT) *out = -(float)PID_LIMIT;
    return *out;
}

/* ================================================================
 * 第 7 节 — 速度斜坡 (Motor_Target_Ramp)
 * ================================================================ */
static float motor_target_ramp(float now, float target)
{
    if (target > now + 14.0f)  return now + 14.0f;
    if (target < now - 8.0f)   return now - 8.0f;
    return target;
}

/* ================================================================
 * 第 8 节 — 电机输出 (Speed_Set + Motor_Control)
 * ================================================================ */
static void motor_control(float speed_l, float speed_r)
{
    if (track_element == NONE) {
        Set_PWM(0, 0); return;
    }
    g_speed_l_target = motor_target_ramp(g_speed_l_target, speed_l);
    g_speed_r_target = motor_target_ramp(g_speed_r_target, speed_r);

    pid_increase(&g_pid_l_out, &g_pid_l_err, &g_pid_l_err1, &g_pid_l_err2,
                 &g_pid_l_d, g_speed_l_target, g_enc_l_speed);
    pid_increase(&g_pid_r_out, &g_pid_r_err, &g_pid_r_err1, &g_pid_r_err2,
                 &g_pid_r_d, g_speed_r_target, g_enc_r_speed);

    speed_now_l = g_pid_l_out;
    speed_now_r = g_pid_r_out;
    Set_PWM((int16_t)speed_now_l, (int16_t)speed_now_r);
}

/* ================================================================
 * 第 9 节 — 差速电机 (Final_Motor_Control)
 * ================================================================ */
static void final_motor_control(int16_t base_speed, float diff_k, int16_t diff_limit)
{
    float diff, target_l, target_r;
    diff = (float)posi * diff_k;
    if (diff > (float)diff_limit)  diff = (float)diff_limit;
    if (diff < -(float)diff_limit) diff = -(float)diff_limit;

    target_l = (float)base_speed - diff;
    target_r = (float)base_speed + diff;
    if (target_l < 15.0f) target_l = 15.0f;
    if (target_r < 15.0f) target_r = 15.0f;

    motor_control(target_l, target_r);
}

/* ================================================================
 * 第 10 节 — 速度档位 (Track_Motor_Control)
 * ================================================================ */
static void track_motor_control(void)
{
    int16_t abs_err = posi; if (abs_err < 0) abs_err = -abs_err;

    if (track_element == RING_l || track_element == RING_r || track_element == RING_c)
        /* 环岛 */
        final_motor_control(20, 0.35f, 10);
    else if (track_element == CROSS)
        final_motor_control(22, 0.40f, 12);
    else if (abs_err >= 30)
        final_motor_control(18, 0.50f, 12);
    else if (abs_err >= 15)
        final_motor_control(22, 0.65f, 14);
    else if (abs_err < 5)
        final_motor_control((int16_t)speed_base, 0.30f, 10);
    else
        final_motor_control(28, 0.38f, 12);
}

/* ================================================================
 * 第 11 节 — 定时器回调 5ms (合并 EncoderCount+主循环)
 * ================================================================ */
static void control_timer_callback(void)
{
    float gyro_z_dps;

    encoder_task();
    encoder_smooth();  /* EncoderCount: EMA滤波+符号 */

    gyro_z_dps = icm_get_gyro_z_dps();
    cnt_degree += (int32_t)(gyro_z_dps * 5.0f);

    if (speed_tune_mode) {
        motor_control(30, 30);
        servo_set_wheel_angle(0.0f);
        return;
    }
    if (track_element == NONE) {
        motor_control(0, 0);
        servo_set_wheel_angle(0.0f);
        return;
    }

    /* error = 图像中心 - 目标中点,  Image_Error */
    {
        int16_t error;
        error = (int16_t)CENTER_POINT - (int16_t)track_midpoint_target;
        posi = error + racing_line_offset(error);
    }

    servo_pd_set();       /* 选舵机PD参数 */
    servo_pd();           /* 舵机PD计算+输出 */
    track_motor_control();/* 选速度+差速输出 */
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
    if (!enable) return;
    motor_clear();
    servo_set_wheel_angle(0.0f);
}

void all_control(void) { motor_speed_control(); steering_control(); }

void motor_clear(void)
{
    speed_l = speed_r = 0;
    speed_now_l = speed_now_r = 0;
    g_speed_l_target = g_speed_r_target = 0;
    g_pid_l_out = g_pid_r_out = 0;
    g_pid_l_err = g_pid_l_err1 = g_pid_l_err2 = 0;
    g_pid_r_err = g_pid_r_err1 = g_pid_r_err2 = 0;
    g_pid_l_d = g_pid_r_d = 0;
    speed_pid_l.output = speed_pid_r.output = 0;
}

void motor_speed_control(void) {}
void steering_control(void) {}
void motor_speed_position_control(void) {}

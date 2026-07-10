// 电机与舵机控制 — 参考 49.9 方案: 舵机PD + 差速电机 + 赛车线偏移
// 引脚定义保持不变

#include "control.h"
#include "encoder.h"
#include "icm.h"
#include "servo.h"
#include "motor.h"
#include "vision.h"
// #include "laser.h"  /* laser.c 未加入工程 */

/* ================================================================
 * 第 1 节 — 运行参数
 * ================================================================ */
float speed_base = 40;  /* 再降 */

/* 赛车线偏移: 小误差不动(防抖), 大误差向内切 */
#define RACING_LINE_START_ERR   8
#define RACING_LINE_MAX_OFFSET  10

/* 舵机PD限幅 */
#define SERVO_PWM_LIMIT  90   /* 全范围, 靠机械限位 */

/* 差速转向增益 */
#define SPEED_DIFF_GAIN  0.50f

/* 速度环增量PID限幅 */
#define MOTOR_PID_LIMIT  6000

/* ================================================================
 * 第 2 节 — 全局状态
 * ================================================================ */
int16_t error = 0;              /* 像素偏差: 正=右偏, 负=左偏 */
int16_t error_last = 0;         /* 上一帧偏差 */
int16_t posi = 0;               /* 方向偏差(赛车线偏移后) */
static float servo_d_filter = 0.0f;  /* 舵机D项低通滤波 */

float speed_l = 0;
float speed_r = 0;
float speed_now_l = 0;
float speed_now_r = 0;
static uint8_t speed_tune_mode = 0;

int32_t cnt_degree = 0;
float ring_start_yaw = 0.0f;

/* 舵机PD参数 (按元素+误差分档, 参考49.9) */
static float g_z_p = 1.70f;  /* 位置P */
static float g_z_d = 5.60f;  /* 微分D */

/* 差速控制参数 (按元素分档) */
static float g_diff_gain = SPEED_DIFF_GAIN;

/* 速度/增益表 (参考49.9 Track_Motor_Control) */
static void control_param_select(void)
{
    int16_t abs_err;
    abs_err = error;
    if (abs_err < 0) abs_err = -abs_err;

    /* 防振荡: P↓ D↑ (振荡=阻尼不够) */
    /* 降60% */
    if (track_element == RING_l || track_element == RING_r || track_element == RING_c)
    { g_z_p = 1.50f;  g_z_d = 4.00f;  g_diff_gain = 5.0f; }
    else if (track_element == CROSS)
    { g_z_p = 1.20f;  g_z_d = 4.00f;  g_diff_gain = 3.0f; }
    else if (abs_err >= 30)
    { g_z_p = 2.80f;  g_z_d = 4.00f;  g_diff_gain = 9.0f; }
    else if (abs_err >= 15)
    { g_z_p = 3.20f;  g_z_d = 3.50f;  g_diff_gain = 10.0f; }
    else
    { g_z_p = 1.00f;  g_z_d = 4.50f;  g_diff_gain = 3.0f; }
}

/* ================================================================
 * 第 3 节 — 赛车线偏移 (参考49.9 racing_line.c)
 * ================================================================ */
static int16_t racing_line_offset(int16_t raw_error)
{
    int16_t abs_err;
    int16_t offset;

    abs_err = raw_error;
    if (abs_err < 0) abs_err = -abs_err;
    if (abs_err <= RACING_LINE_START_ERR)
        return 0;

    offset = (abs_err - RACING_LINE_START_ERR) / 2;
    if (offset > RACING_LINE_MAX_OFFSET)
        offset = RACING_LINE_MAX_OFFSET;

    /* 右偏(正)→目标左移(负偏移量); 左偏(负)→目标右移(正偏移量) */
    if (raw_error > 0)
        return -offset;
    else
        return offset;
}

/* ================================================================
 * 第 4 节 — 舵机PD (参考49.9 servo_PD)
 * ================================================================ */
static void servo_pd(void)
{
    float d_error;
    float servo_out;

    /* error 使用赛车线偏移后的 posi (wider lookahead effect) */
    d_error = (float)(posi - error_last);

    /* D项低通滤波 */
    servo_d_filter = 0.6f * servo_d_filter + 0.4f * d_error;

    servo_out = (float)posi * g_z_p + servo_d_filter * g_z_d;

    /* 限幅 */
    if (servo_out > (float)SERVO_PWM_LIMIT)
        servo_out = (float)SERVO_PWM_LIMIT;
    else if (servo_out < -(float)SERVO_PWM_LIMIT)
        servo_out = -(float)SERVO_PWM_LIMIT;

    servo_set_wheel_angle(servo_out);

    error_last = posi;
}

/* ================================================================
 * 第 5 节 — 差速电机控制 (参考49.9 Final_Motor_Control)
 * ================================================================ */
static float g_speed_l_prev = 0;  /* 速度斜坡用 */
static float g_speed_r_prev = 0;

static void diff_motor_control(int16_t base_speed)
{
    float target_l, target_r;
    float diff;
    int16_t diff_limit;

    diff = (float)posi * g_diff_gain;

    /* 49.9式限幅: Limit(base-limit, base±k*posi, base+limit) */
    diff_limit = base_speed / 3;  /* 最大差速 = 1/3 基础速度 */
    if (diff > (float)diff_limit)  diff = (float)diff_limit;
    if (diff < -(float)diff_limit) diff = -(float)diff_limit;

    target_l = (float)(base_speed) - diff;
    target_r = (float)(base_speed) + diff;

    if (target_l < 200.0f) target_l = 200.0f;
    if (target_r < 200.0f) target_r = 200.0f;
    if (target_l > 8000.0f) target_l = 8000.0f;
    if (target_r > 8000.0f) target_r = 8000.0f;

    /* 速度斜坡: 每次最多变±200 PWM */
    if (target_l > g_speed_l_prev + 200.0f) target_l = g_speed_l_prev + 200.0f;
    if (target_l < g_speed_l_prev - 100.0f) target_l = g_speed_l_prev - 100.0f;
    if (target_r > g_speed_r_prev + 200.0f) target_r = g_speed_r_prev + 200.0f;
    if (target_r < g_speed_r_prev - 100.0f) target_r = g_speed_r_prev - 100.0f;
    g_speed_l_prev = target_l;
    g_speed_r_prev = target_r;

    speed_now_l = target_l;
    speed_now_r = target_r;
}

/* ================================================================
 * 第 6 节 — 速度档位选择 (参考49.9 Track_Motor_Control)
 * ================================================================ */
static int16_t track_speed_select(void)
{
    int16_t abs_err;
    abs_err = error;
    if (abs_err < 0) abs_err = -abs_err;

    /* 环岛 */
    /* 直接PWM: 降速60% */
    if (track_element == RING_l || track_element == RING_r || track_element == RING_c)
        return 900;

    if (track_element == CROSS)
        return 1100;

    if (abs_err >= 30)
        return 1000;

    if (abs_err >= 15)
        return 1100;

    if (abs_err < 5)
        return 1300;

    return 1200;
}

/* ================================================================
 * 第 7 节 — 定时器回调 (5ms)
 * ================================================================ */
static void control_timer_callback(void)
{
    float gyro_z_dps;
    int16_t base_speed;

    encoder_task();

    gyro_z_dps = icm_get_gyro_z_dps();
    cnt_degree += (int32_t)(gyro_z_dps * 5.0f);

    /* laser_fsm_update(); — laser.c 未加入工程, 暂时跳过 */

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

    /* error = 图像中心 - 目标中点 (正=偏右, 负=偏左) */
    error = (int16_t)CENTER_POINT - (int16_t)track_midpoint_target;

    /* 赛车线偏移: 小误差不动, 大误差向内切 */
    posi = error + racing_line_offset(error);

    /* 选择控制参数 */
    control_param_select();

    /* 舵机PD */
    servo_pd();

    /* 速度 */
    base_speed = track_speed_select();

    /* 差速电机 */
    diff_motor_control(base_speed);

    Set_PWM((int16_t)speed_now_l, (int16_t)speed_now_r);
}

/* ================================================================
 * 第 8 节 — 初始化和公共接口
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
    /* 简化版: 固定target, 用增量PID */
    float target;
    target = speed_base;
    speed_now_l = IncrementalPID_Calculate(&speed_pid_l, target - (float)encoder_data_dir[0]);
    speed_now_r = IncrementalPID_Calculate(&speed_pid_r, target - (float)encoder_data_dir[1]);
}

void steering_control(void)
{
    /* 舵机PD — 主控制在 control_timer_callback 中, 这里留空 */
}

void motor_speed_position_control(void)
{
    motor_speed_control();
    steering_control();
}

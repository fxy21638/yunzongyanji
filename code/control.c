#include "control.h"
#include "encoder.h"
#include "icm.h"
#include "servo.h"
#include "motor.h"
#include "vision.h"        // g_track, g_track_valid

float speed_base = 45;

#define FIXED_SPEED_DEBUG 0
#define FIXED_PWM_DUTY 600
float gyro_target = 0;
float gyro_control = 60;
uint8_t turn_step = 0;

float speed_l = 0;
float speed_r = 0;
float speed_now_l = 0;
float speed_now_r = 0;

static void control_timer_callback(void)
{
    encoder_task();

    if (track_element == NONE)
    {
        motor_clear();
        servo_set_wheel_angle(0.0f);
        Set_PWM(0, 0);
        return;
    }

#if FIXED_SPEED_DEBUG
    speed_now_l = FIXED_PWM_DUTY;
    speed_now_r = FIXED_PWM_DUTY;
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
}

void motor_speed_control(void)
{
    float speed_gain_l;
    float speed_gain_r;

    speed_gain_l = IncrementalPID_Calculate(&speed_pid_l, speed_base - encoder_data_dir[0]);
    speed_l += speed_gain_l;
    speed_gain_r = IncrementalPID_Calculate(&speed_pid_r, speed_base - encoder_data_dir[1]);
    speed_r += speed_gain_r;

    // Anti-windup: clamp and prevent further accumulation in saturation direction
    if (speed_l > MOTOR_SPEED_LIMIT)
    {
        speed_l = MOTOR_SPEED_LIMIT;
        if (speed_gain_l > 0) speed_l -= speed_gain_l;
    }
    else if (speed_l < -MOTOR_SPEED_LIMIT)
    {
        speed_l = -MOTOR_SPEED_LIMIT;
        if (speed_gain_l < 0) speed_l -= speed_gain_l;
    }

    if (speed_r > MOTOR_SPEED_LIMIT)
    {
        speed_r = MOTOR_SPEED_LIMIT;
        if (speed_gain_r > 0) speed_r -= speed_gain_r;
    }
    else if (speed_r < -MOTOR_SPEED_LIMIT)
    {
        speed_r = -MOTOR_SPEED_LIMIT;
        if (speed_gain_r < 0) speed_r -= speed_gain_r;
    }

    speed_now_l = speed_l;
    speed_now_r = speed_r;
}

void steering_control(void)
{
    float steer_output;
    float track_error;
    uint16_t y;
    int16_t last_l, last_r;
    uint8_t emergency;

    // ====== 紧急出界恢复检测 ======
    // 当有效行极少或 FEATURE=LOST 时，判定为即将/已经出界
    emergency = 0;
    if (!g_track_valid ||
        g_track.feature == VISION_FEATURE_LOST ||
        g_track.valid_rows < 5)
    {
        // 在底部区域扫描哪一侧还有有效边界数据
        // 只有一侧有数据 → 赛道在这一侧 → 向该侧强行转向
        last_l = -1;
        last_r = -1;
        for (y = (uint16_t)(MT9V034_HEIGHT / 2); y < MT9V034_HEIGHT; y++)
        {
            if (g_track.left[y] >= 0)  last_l = g_track.left[y];
            if (g_track.right[y] >= 0) last_r = g_track.right[y];
        }

        if (last_l >= 0 && last_r < 0)
        {
            // 只有左边有数据 → 向左偏了 → 强行向左转
            emergency = 1;
            steer_output = STEER_OUTPUT_LIMIT;         // 满舵左转
        }
        else if (last_r >= 0 && last_l < 0)
        {
            // 只有右边有数据 → 向右偏了 → 强行向右转
            emergency = 2;
            steer_output = -STEER_OUTPUT_LIMIT;        // 满舵右转
        }
        else if (last_l < 0 && last_r < 0)
        {
            // 两边都没数据 → 完全丢线 → 保持上次方向
            static int8_t last_emergency_dir = 0;
            if (last_emergency_dir == 0)
                last_emergency_dir = 1;  // 默认左转
            emergency = 3;
            steer_output = (float)last_emergency_dir * STEER_OUTPUT_LIMIT * 0.5f;
        }
    }

    if (emergency)
    {
        // 紧急转向：不经过PID和平滑，直接输出
        // 同时降低车速便于找回赛道
        speed_now_l = FIXED_PWM_DUTY / 3;
        speed_now_r = FIXED_PWM_DUTY / 3;
        servo_set_wheel_angle(steer_output);
        return;
    }

    // ====== 正常 PID 转向控制 ======
    track_error = (float)CENTER_POINT - (float)track_midpoint_target;

    if (track_element == BROKEN_RODE)
    {
#if (CASCADE_PID == 1)
        steer_output = PositionalPID_Calculate(&pid_gyro, gyro_target - yaw);
#else
        steer_output = PositionalPID_Calculate(&inertia_pid, gyro_target - yaw);
#endif
    }
    else
    {
#if (CASCADE_PID == 1)
        steer_output = PositionalPID_Calculate(&pid_pos, track_error);
#else
        steer_output = AnglePID_Calculate(&angle_pid, track_error);
#endif
    }

    steer_output = SATURATE(steer_output, -STEER_OUTPUT_LIMIT, STEER_OUTPUT_LIMIT);

    {
        static float steer_smooth = 0.0f;
        steer_output = steer_smooth * 0.2f + steer_output * 0.8f;
        steer_smooth = steer_output;
    }

    servo_set_wheel_angle(steer_output);
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

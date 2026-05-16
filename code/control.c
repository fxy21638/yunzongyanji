#include "control.h"
#include "encoder.h"
#include "icm.h"
#include "servo.h"
#include "motor.h"

float speed_base = 80;

#define FIXED_SPEED_DEBUG 1
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

    speed_l = SATURATE(speed_l, -MOTOR_SPEED_LIMIT, MOTOR_SPEED_LIMIT);
    speed_r = SATURATE(speed_r, -MOTOR_SPEED_LIMIT, MOTOR_SPEED_LIMIT);

    speed_now_l = speed_l;
    speed_now_r = speed_r;
}

void steering_control(void)
{
    float steer_output;
    float track_error;

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

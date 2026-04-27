/*********************************************************************************************************************
    TODO: 实现控制模块
    实现电机速度控制和位置控制
    包含PID控制和PID级联控制
        1. PID控制：通过调整电机PWM占空比来控制速度，使用增量式PID算法计算速度误差并进行修正。
        2. PID级联控制：在PID控制的基础上增加位置控制环，根据小车与轨迹中心点的偏移调整电机速度，实现更精准的路径跟踪。
 ********************************************************************************************************************/
#include "control.h"
#include "main.h"

float speed_base = 180;
float gyro_target = 0;
float gyro_control = 60;
uint8_t turn_step = 0;

float speed_l = 0;
float speed_r = 0;

float speed_now_l = 0;
float speed_now_r = 0;

// uint8_t pid_time = 0;

void all_control(void)
{
    if (track_element == NONE)
    {
        speed_l = 0;
        speed_r = 0;
        speed_now_l = 0;
        speed_now_r = 0;
    }
    else
    {
#if (CASCADE_PID == 1)
        motor_speed_position_control();
#elif (CASCADE_PID == 2)

        if (start_stage == 3)
            motor_clear();
        else if (track_element == BROKEN_RODE)
            motor_inertia_control();
        else
            motor_agle_control();
#endif
    }
}

void motor_clear(void)
{
    speed_l = 0;
    speed_r = 0;
    speed_now_l = 0;
    speed_now_r = 0;
}

// �����ٶȻ�
void motor_speed_control(void)
{
    float speed_gain_l = 0;
    float speed_gain_r = 0;
    speed_gain_l = IncrementalPID_Calculate(&speed_pid_l, speed_base - encoder_data_dir[0]);
    speed_l += speed_gain_l;
    speed_gain_r = IncrementalPID_Calculate(&speed_pid_r, speed_base - encoder_data_dir[1]);
    speed_r += speed_gain_r;
    speed_l = SATURATE(speed_l, -MOTOR_SPEED_LIMIT, MOTOR_SPEED_LIMIT);
    speed_r = SATURATE(speed_r, -MOTOR_SPEED_LIMIT, MOTOR_SPEED_LIMIT);

    speed_now_l = speed_l;
    speed_now_r = speed_r;
}

#if (CASCADE_PID == 1)
// ����1��λ�ô��ٶȻ���û�н��ٶ�kd���棬ת��ʱ�����׳�����
void motor_speed_position_control()
{
    float speed_gain_l = 0;
    float speed_gain_r = 0;
    float position_gain = 0;
    // track_straight_target(dir);
    speed_gain_l = IncrementalPID_Calculate(&speed_pid_l, speed_base - encoder_data_dir[0]);
    speed_gain_r = IncrementalPID_Calculate(&speed_pid_r, speed_base - encoder_data_dir[1]);
    speed_l = speed_l + speed_gain_l;
    speed_r = speed_r + speed_gain_r;

    speed_l = SATURATE(speed_l, -MOTOR_SPEED_LIMIT, MOTOR_SPEED_LIMIT);
    speed_r = SATURATE(speed_r, -MOTOR_SPEED_LIMIT, MOTOR_SPEED_LIMIT);

    position_gain = PositionalPID_Calculate(&pid_pos, CENTER_POINT - track_midpoint_target);
    position_gain = SATURATE(position_gain, -MOTOR_POSITION_LIMIT, MOTOR_POSITION_LIMIT);
    speed_l = speed_l - position_gain;
    speed_r = speed_r + position_gain;
    speed_now_l = speed_l;
    speed_now_r = speed_r;
}
#elif (CASCADE_PID == 2)
// ����2��ת��ֵ�������ٶȻ����Ƽ���
void motor_agle_control(void)
{
    float speed_gain_l = 0;
    float speed_gain_r = 0;
    float agle_gain = 0;
    speed_gain_l = IncrementalPID_Calculate(&speed_pid_l, speed_base - encoder_data_dir[0]);
    speed_gain_r = IncrementalPID_Calculate(&speed_pid_r, speed_base - encoder_data_dir[1]);
    speed_l = speed_l + speed_gain_l;
    speed_r = speed_r + speed_gain_r;
    speed_l = SATURATE(speed_l, -MOTOR_SPEED_LIMIT, MOTOR_SPEED_LIMIT);
    speed_r = SATURATE(speed_r, -MOTOR_SPEED_LIMIT, MOTOR_SPEED_LIMIT);
    agle_gain = AnglePID_Calculate(&angle_pid, CENTER_POINT - track_midpoint_target);
    speed_l = speed_l - agle_gain;
    speed_r = speed_r + agle_gain;
    speed_l = SATURATE(speed_l, -MOTOR_ANGLE_LIMIT, MOTOR_ANGLE_LIMIT);
    speed_r = SATURATE(speed_r, -MOTOR_ANGLE_LIMIT, MOTOR_ANGLE_LIMIT);
    speed_now_l = speed_l;
    speed_now_r = speed_r;
}
void motor_inertia_control(void)
{
    float speed_gain_l = 0;
    float speed_gain_r = 0;
    float agle_gain = 0;
    speed_gain_l = IncrementalPID_Calculate(&speed_pid_l, speed_base - encoder_data_dir[0]);
    speed_gain_r = IncrementalPID_Calculate(&speed_pid_r, speed_base - encoder_data_dir[1]);
    speed_l = speed_l + speed_gain_l;
    speed_r = speed_r + speed_gain_r;
    speed_l = SATURATE(speed_l, -MOTOR_SPEED_LIMIT, MOTOR_SPEED_LIMIT);
    speed_r = SATURATE(speed_r, -MOTOR_SPEED_LIMIT, MOTOR_SPEED_LIMIT);
    agle_gain = PositionalPID_Calculate(&inertia_pid, gyro_target - yaw);
    speed_l = speed_l - agle_gain;
    speed_r = speed_r + agle_gain;
    speed_l = SATURATE(speed_l, -MOTOR_ANGLE_LIMIT, MOTOR_ANGLE_LIMIT);
    speed_r = SATURATE(speed_r, -MOTOR_ANGLE_LIMIT, MOTOR_ANGLE_LIMIT);
    speed_now_l = speed_l;
    speed_now_r = speed_r;
}
#elif (CASCADE_PID == 3)
// ����3����ɷ���
void motor_agle_control()
{
    float speed_gain = 0;
    float agle_gain = 0;
    float speed_average = (encoder_data_dir[0] + encoder_data_dir[1]) / 2.0f;
    speed_gain = IncrementalPID_Calculate(&speed_pid_l, speed_base - speed_average);
    agle_gain = AnglePID_Calculate(&angle_pid, CENTER_POINT - track_midpoint_target);
    speed_l = speed_l + speed_gain - agle_gain;
    speed_r = speed_r + speed_gain + agle_gain;
    speed_l = SATURATE(speed_l, -MAX_DUTY, MAX_DUTY);
    speed_r = SATURATE(speed_r, -MAX_DUTY, MAX_DUTY);
    speed_now_l = speed_l;
    speed_now_r = speed_r;
}
#endif

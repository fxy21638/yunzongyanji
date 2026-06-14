#include "main.h"

IncrementalPID speed_pid_l = {0.60f, 0.15f, 0.50f, -1500.0f, 1500.0f, 0.0f, 0.0f, 0.0f};
IncrementalPID speed_pid_r = {0.55f, 0.12f, 0.36f, -1500.0f, 1500.0f, 0.0f, 0.0f, 0.0f};
PositionalPID pid_pos = {0.40f, 0.28f, 0.04f, 0.0f, 4.0f, 0.0f};
PositionalPID pid_gyro = {1.00f, 2.00f, 0.00f, 0.0f, 0.0f, 0.0f};

float PositionalPID_Calculate(PositionalPID *pid, float error)
{
    float derivative;
    float output;

    if (pid->Ki == 0.0f)
        pid->integral = 0.0f;
    else
        pid->integral += error;

    if (pid->integral_max > 0.0f)
    {
        if (pid->integral > pid->integral_max)
            pid->integral = pid->integral_max;
        else if (pid->integral < -pid->integral_max)
            pid->integral = -pid->integral_max;
    }
    derivative = error - pid->prev_error;
    output = pid->Kp * error + pid->integral * pid->Ki + pid->Kd * derivative;
    pid->prev_error = error;
    return output;
}

float IncrementalPID_Calculate(IncrementalPID *pid, float current_error)
{
    float p_term, i_term, d_term;
    float delta;

    // 增量式 PID: P=Δe, I=e(k), D=e(k)-2e(k-1)+e(k-2)
    p_term = current_error - pid->error_prev;
    i_term = current_error;
    d_term = current_error - 2.0f * pid->error_prev + pid->error_prev2;

    pid->error_prev2 = pid->error_prev;
    pid->error_prev = current_error;

    delta = pid->Kp * p_term + pid->Ki * i_term + pid->Kd * d_term;
    pid->output += delta;

    // 输出限幅
    if (pid->output > pid->out_max)
        pid->output = pid->out_max;
    else if (pid->output < pid->out_min)
        pid->output = pid->out_min;

    return pid->output;
}


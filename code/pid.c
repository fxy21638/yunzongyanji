#include "main.h"

#if (CASCADE_PID == 1)
IncrementalPID speed_pid_l = {0.45f, 0.07f, 0.50f, -800.0f, 800.0f, 0.0f, 0.0f, 0.0f};
IncrementalPID speed_pid_r = {0.42f, 0.05f, 0.36f, -800.0f, 800.0f, 0.0f, 0.0f, 0.0f};
PositionalPID pid_pos = {0.40f, 0.35f, 0.0f};
PositionalPID pid_gyro = {1.4f, 3.4f, 0.0f};
#elif (CASCADE_PID == 2)
AnglePID angle_pid = {0.02f, 0.00f, 1.0f, 0.00f, 0.0f};
IncrementalPID speed_pid_l = {0.60f, 0.15f, 0.40f, -800.0f, 800.0f, 0.0f, 0.0f, 0.0f};
IncrementalPID speed_pid_r = {0.55f, 0.12f, 0.35f, -800.0f, 800.0f, 0.0f, 0.0f, 0.0f};
PositionalPID inertia_pid = {0.10f, 0.30f, 0.0f};
#elif (CASCADE_PID == 3)
AnglePID angle_pid = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
IncrementalPID speed_pid = {0.00f, 0.00f, 0.0f, -800.0f, 800.0f, 0.0f, 0.0f, 0.0f};
#endif

float PositionalPID_Calculate(PositionalPID *pid, float error)
{
    float derivative;
    float output;

    derivative = error - pid->prev_error;
    output = pid->Kp * error + pid->Kd * derivative;
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

float AnglePID_Calculate(AnglePID *pid, float error)
{
    float angle;

    angle = error * pid->KP + (error - pid->error_prev) * pid->KD;
    pid->error_prev = error;
    return angle;
}

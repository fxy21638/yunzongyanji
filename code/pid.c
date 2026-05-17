#include "main.h"

#if (CASCADE_PID == 1)
IncrementalPID speed_pid_l = {1.37f, 0.20f, 0.0f, 0.0f};
IncrementalPID speed_pid_r = {1.38f, 0.16f, 0.0f, 0.0f};
PositionalPID pid_pos = {0.40f, 0.35f, 0.0f};
PositionalPID pid_gyro = {1.4f, 3.4f, 0.0f};
#elif (CASCADE_PID == 2)
AnglePID angle_pid = {0.02f, 0.00f, 1.0f, 0.00f, 0.0f};
IncrementalPID speed_pid_l = {0.00f, 0.00f, 0.0f, 0.0f};
IncrementalPID speed_pid_r = {0.00f, 0.00f, 0.0f, 0.0f};
PositionalPID inertia_pid = {0.10f, 0.30f, 0.0f};
#elif (CASCADE_PID == 3)
AnglePID angle_pid = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
IncrementalPID speed_pid = {0.00f, 0.00f, 0.0f, 0.0f};
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
    float delta;

    delta = pid->Kp * (current_error - pid->error_prev) + pid->Ki * current_error;
    pid->error_prev = current_error;
    return delta;
}

float AnglePID_Calculate(AnglePID *pid, float error)
{
    float angle;

    angle = error * pid->KP + (error - pid->error_prev) * pid->KD;
    pid->error_prev = error;
    return angle;
}

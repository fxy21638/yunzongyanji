#ifndef _PID_H_
#define _PID_H_

typedef struct
{
    float Kp;
    float Ki;
    float Kd;
    float out_min;
    float out_max;
    float error_prev;
    float error_prev2;
    float output;
} IncrementalPID;

typedef struct
{
    float Kp;
    float Kd;
    float Ki;
    float integral;
    float integral_max;
    float prev_error;
} PositionalPID;

extern PositionalPID pid_pos;
extern PositionalPID pid_gyro;
extern IncrementalPID speed_pid_l;
extern IncrementalPID speed_pid_r;

float IncrementalPID_Calculate(IncrementalPID *pid, float current_error);
float PositionalPID_Calculate(PositionalPID *pid, float error);

#endif

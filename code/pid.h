#ifndef _PID_H_
#define _PID_H_

#ifndef CASCADE_PID
#define CASCADE_PID (2)
#endif

typedef struct
{
    float Kp;
    float Ki;
    float error_prev;
    float error_prev2;
} IncrementalPID;

typedef struct
{
    float Kp;
    float Kd;
    float prev_error;
} PositionalPID;

typedef struct
{
    float KP;
    float KP2;
    float KD;
    float GKD;
    float error_prev;
} AnglePID;

#if (CASCADE_PID == 1)
extern PositionalPID pid_pos;
extern PositionalPID pid_gyro;
extern IncrementalPID speed_pid_l;
extern IncrementalPID speed_pid_r;
#elif (CASCADE_PID == 2)
extern AnglePID angle_pid;
extern IncrementalPID speed_pid_l;
extern IncrementalPID speed_pid_r;
extern PositionalPID inertia_pid;
#elif (CASCADE_PID == 3)
extern AnglePID angle_pid;
extern IncrementalPID speed_pid;
#endif

float IncrementalPID_Calculate(IncrementalPID *pid, float current_error);
float PositionalPID_Calculate(PositionalPID *pid, float error);
float AnglePID_Calculate(AnglePID *pid, float error);

#endif

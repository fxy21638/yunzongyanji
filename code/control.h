#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "ky_headfile.h"

/* 舵机 PD 参数结构 (49.9) */
typedef struct
{
    float z_p;
    float z_d;
} PID_t;

extern PID_t Pid;
extern float server_out;
extern int16_t error;

/* 电机 PID 结构 (49.9) */
typedef struct
{
    float Kp, Ki, Kd, Lowpass;
    float out_P, out_I, out_D;
    float Error, LastError, PrevError, LastData;
} MPID_t;

/* 电机状态 */
typedef struct
{
    int16_t encoder_raw;
    float encoder_speed;
    int32_t total_encoder;
    int16_t target_speed;
    int16_t duty;
} motor_t;

extern motor_t motor_L, motor_R;
extern MPID_t motor_pid_L, motor_pid_R;

extern float speed_base;
extern float speed_now_l, speed_now_r;

/* ---- 舵机控制 ---- */
void servo_pd_set(void);
void server_PD(void);
void servo_Control(void);

/* ---- 电机控制 ---- */
void motor_Pid_init(void);
void Motor_Control(int16_t speed_L, int16_t speed_R);
void Track_Motor_Control(void);
void Final_Motor_Control(int16_t speed, float k, int16_t limit);
float PID_Increase(MPID_t *pid, float NowData, float Point);
void EncoderCount(void);

void control_Init(void);
void control_clear(void);
void control_set_speed_tune_mode(uint8_t enable);

#endif

#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "ky_headfile.h"

#define CASCADE_PID (2)

#define change_kib 4
#define MOTOR_SPEED_LIMIT 500
#define MOTOR_POSITION_LIMIT 1000
#define MOTOR_ANGLE_LIMIT 1000

#define SATURATE(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

extern float speed_base;
extern float gyro_target;
extern float gyro_control;
extern uint8 turn_step;

extern float speed_l;
extern float speed_r;
extern float speed_now_l;
extern float speed_now_r;

//extern uint8_t pid_time;

void all_control(void);

void motor_speed_control(void);
//void motor_gyro_control(void);
#if (CASCADE_PID == 1)
void motor_speed_position_control(void);
#elif (CASCADE_PID == 2)
void motor_agle_control(void);
void motor_inertia_control(void);
#endif

void motor_clear(void);






//float changable_pid_solve(pid_param_t *pid, float error);



#endif

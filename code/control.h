#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "ky_headfile.h"

#define CASCADE_PID (2)

#include "trail.h"
#include "pid.h"

#define change_kib 4
#define MOTOR_SPEED_LIMIT 4000
#define MOTOR_POSITION_LIMIT 1000
#define MOTOR_ANGLE_LIMIT 1000
#define STEER_OUTPUT_LIMIT 20.0f

#define SATURATE(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

extern float speed_base;
extern float gyro_target;
extern float gyro_control;
extern uint8_t turn_step;

extern float speed_l;
extern float speed_r;
extern float speed_now_l;
extern float speed_now_r;

void control_Init(void);
void all_control(void);
void motor_speed_control(void);
void steering_control(void);
#if (CASCADE_PID == 1)
void motor_speed_position_control(void);
#elif (CASCADE_PID == 2)
void motor_agle_control(void);
void motor_inertia_control(void);
#endif
void motor_clear(void);

#endif

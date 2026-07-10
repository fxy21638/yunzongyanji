#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "ky_headfile.h"

#include "trail.h"
#include "pid.h"

#define STEER_OUTPUT_LIMIT 20.0f
#define SPEED_DIFF_GAIN    0.50f   /* diff steering gain: pixel_err x gain = speed bias */

#define SATURATE(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

extern float speed_base;
extern int32_t cnt_degree;
extern float ring_start_yaw;

extern float speed_l;
extern float speed_r;
extern float speed_now_l;
extern float speed_now_r;

void control_Init(void);
void control_set_speed_tune_mode(uint8_t enable);
void all_control(void);
void motor_speed_control(void);
void steering_control(void);
void motor_speed_position_control(void);
void motor_clear(void);

#endif

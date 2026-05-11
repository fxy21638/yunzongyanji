#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "ky_headfile.h"

void motor_Init(void);
void motor_task(void);
void Set_PWM(int16_t left, int16_t right);

#endif

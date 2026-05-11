#ifndef __SERVO_H__
#define __SERVO_H__

#include "ky_headfile.h"

#define SERVO_PIN      PWME_CH5_P43
#define SERVO_FREQ     330

#define ANGLE_TO_DUTY(angle) \
    ((uint16_t)(1800 + (110 * (uint16_t)(angle)) / 3))

void servo_Init(void);
void servo_task(void);
void servo_set_angle(uint8_t angle_deg);
void servo_set_wheel_angle(float wheel_angle_deg);

#endif

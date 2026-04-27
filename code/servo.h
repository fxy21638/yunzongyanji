#ifndef __SERVO_H__
#define __SERVO_H__

#include "ky_headfile.h"

// 引脚宏定义 - 舵机
#define SERVO_PIN      PWME_CH5_P43     // 舵机信号 (P4.3)

// 舵机参数
#define SERVO_FREQ     330              // 舵机PWM频率 330Hz

// 占空比公式
// 高电平时间 = 0.5ms + angle/180 * 2ms = (0.5 + angle/90.0) ms
// 占空比 = 高电平时间 / 周期 * 10000
//        = 10000 / (1000 / FREQ) * (0.5 + angle / 90.0)
#define ANGLE_TO_DUTY(angle) \
    ((uint16_t)(1650 + (110 * (uint16_t)(angle)) / 3))
	
void servo_Init(void);
void servo_task(void);

#endif

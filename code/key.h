#ifndef __KEY_H__
#define __KEY_H__

#include "ky_headfile.h"

// 引脚宏定义 - 按键
#define KEY1_PIN       GPIO_P92         // 按键1
#define KEY2_PIN       GPIO_P93         // 按键2
#define KEY3_PIN       GPIO_P94         // 按键3
#define KEY4_PIN       GPIO_P95         // 按键4

// 按键ID定义
#define KEY1_ID        0
#define KEY2_ID        1
#define KEY3_ID        2
#define KEY4_ID        3

#define KEY_COUNT      4

void key_system_Init(void);

#endif

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "ky_headfile.h"
#include "main.h"

// 引脚宏定义 - 编码器1 (正交模式)
#define ENC1_A_PIN      ENCC_A_P80       // 编码器1 A相 (P8.0)
#define ENC1_B_PIN      ENCC_B_P82       // 编码器1 B相 (P8.2)

// 引脚宏定义 - 编码器2 (带方向模式)
#define ENC2_P_PIN      ENCD_A_P81       // 编码器2 脉冲 (P8.1)
#define ENC2_D_PIN      ENCD_B_P83       // 编码器2 方向 (P8.3)

void encoder_Init(void);
void encoder_task(void);
void encoder_debug(void);

#endif

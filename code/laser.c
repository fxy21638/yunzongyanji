#include "laser.h"

void laser_Init(void)
{
    // P9.0 推挽输出，高电平常亮（仅在初始化时设置一次）
    P9M1 &= ~0x01;  // M1=0
    P9M0 |= 0x01;   // M0=1  → 推挽输出
    P9OUT |= 0x01;  // P9.0 = 1（点亮激光）
}

#ifndef __LASER_H__
#define __LASER_H__

#include "ky_headfile.h"

/* ================================================================
 * GPIO — 5 激光 独立控制, 同属 P9.0~P9.4 (位掩码操作)
 *
 * TODO: 如需更换引脚, 修改以下宏 + laser.c 中 Init/set_mask 的端口寄存器
 * ================================================================ */

#define LASER_PORT       P9OUT       /* 输出寄存器 */
#define LASER_PORT_M1    P9M1        /* 模式寄存器 M1 */
#define LASER_PORT_M0    P9M0        /* 模式寄存器 M0 */

#define LASER_PIN_CENTER  0x01       /* P9.0 — 中心  0cm */
#define LASER_PIN_L1      0x02       /* P9.1 — 左内 -5cm */
#define LASER_PIN_L2      0x04       /* P9.2 — 左外 -10cm */
#define LASER_PIN_R1      0x08       /* P9.3 — 右内 +5cm */
#define LASER_PIN_R2      0x10       /* P9.4 — 右外 +10cm */
#define LASER_PIN_ALL     0x1F       /* 全部 5 个 */

/* ---- 阈值 ---- */
#define LASER_FIRE_RADIUS_MIN   18u   /* 靶子内半径 > 此值才允许开火 (够近) */
#define LASER_FIRE_RADIUS_MID   25u   /* > 此值可开 ±5cm 激光 */
#define LASER_FIRE_RADIUS_NEAR  35u   /* > 此值可开 ±10cm 激光 (偏移大时) */
#define LASER_STOP_RADIUS        8u   /* radius < 此值强制关火 */
#define LASER_CENTER_WINDOW     10u   /* |center_x - 94| < 此值 = 居中 */
#define LASER_DEBOUNCE_CNT       3u   /* 连续确认帧数 (3 × ~20ms = 60ms) */
#define LASER_MAX_ON_MS        500u   /* 硬超时 (500ms) */
#define LASER_COOLDOWN_MS     1500u   /* 冷却期, 防重复触发 */

/* ---- API ---- */
void laser_Init(void);
void laser_set_mask(uint8_t mask);   /* 位掩码 0x01~0x1F */
void laser_fsm_update(void);         /* 每 5ms 调用一次 */
void laser_force_off(void);          /* 紧急全关 */

#endif

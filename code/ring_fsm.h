// ====================================================================
// 环岛状态机 — 封装环岛检测、入环/出环/中心转换、目标规划
// ====================================================================
//
// 环岛生命周期 (以左环岛为例):
//   IDLE → (检测到左侧分叉 + 上方有路) → ENTER_l
//   ENTER_l → (转过阈值角度) → CENTER
//   CENTER → (检测到对侧分叉) → IDLE
//
// 核心检测条件: 必须同时满足
//   条件1: 一侧边界出现"终点"(分叉/丢线), 另一侧保持稳定
//   条件2: 分叉上方仍有道路 (中线不偏太远), 排除转弯误判
//   两个条件同时成立才确认环岛
// ====================================================================

#ifndef __RING_FSM_H__
#define __RING_FSM_H__

#include "trail.h"

/* ---- 环岛状态机内部状态 ---- */
typedef enum
{
    RING_IDLE = 0,
    RING_ENTER_l,       /* 入左环岛: 跟随左侧鼓出边界 */
    RING_ENTER_r,       /* 入右环岛: 跟随右侧鼓出边界 */
    RING_CENTER,        /* 环岛中心: 直行通过 */
} ring_state_t;

/* ---- 环岛状态机实例 ---- */
typedef struct
{
    ring_state_t state;
    float        entry_yaw;     /* 入环时陀螺仪角度 (yaw) */
} ring_fsm_t;

/* ---- 全局环岛状态机 (trail.c 使用) ---- */
extern ring_fsm_t g_ring_fsm;

/* ---- 生命周期 ---- */
void ring_fsm_init(ring_fsm_t *rf);                             /* 初始化到 IDLE */

/* ---- 每帧处理 ---- */
TRACK_ELEMENT ring_fsm_process(ring_fsm_t *rf, TRACK_ELEMENT seg_elem);  /* 输入段分类, 输出 RING_xxx 或透传 */
uint8_t       ring_fsm_get_target(const ring_fsm_t *rf);                 /* 当前环岛状态的目标中点 */
uint8_t       ring_fsm_is_active(const ring_fsm_t *rf);                  /* 是否处于环岛状态 */
void          ring_fsm_reset(ring_fsm_t *rf);                            /* 强制重置到 IDLE */

/* ---- 环岛状态切换阈值 (毫度) ---- */
#define RING_CENTER_DEGREE   25000   /* ENTER→CENTER: 转过 25° 进入环岛中心 */
#define RING_EXIT_DEGREE_MIN 90000   /* CENTER→IDLE: 最少转过 90° 才能退出, 防叉口误触发 */

#endif

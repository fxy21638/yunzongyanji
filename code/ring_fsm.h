// 环岛状态机 — 移植49.9 huandao_detect 7状态
//   IDLE → RING_ENTER_r → RING_CENTER → IDLE

#ifndef __RING_FSM_H__
#define __RING_FSM_H__

#include "trail.h"

typedef enum
{
    RING_IDLE = 0,
    RING_ENTER_l,
    RING_ENTER_r,
    RING_CENTER,
} ring_state_t;

typedef struct
{
    ring_state_t state;
    float        entry_yaw;
} ring_fsm_t;

extern ring_fsm_t g_ring_fsm;

void ring_fsm_init(ring_fsm_t *rf);
void ring_fsm_reset(ring_fsm_t *rf);
uint8_t ring_fsm_get_target(const ring_fsm_t *rf);
uint8_t ring_fsm_is_active(const ring_fsm_t *rf);

#endif

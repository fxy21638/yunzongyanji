#ifndef __TRACK_FSM_H__
#define __TRACK_FSM_H__

#include "trail.h"

enum
{
    PLAN_STRAIGHT   = 0,
    PLAN_TURN_LEFT  = 1,
    PLAN_TURN_RIGHT = 2,
    PLAN_CROSS      = 3,
    PLAN_BROKEN     = 4,
    PLAN_HOLD       = 5
};
typedef uint8_t track_plan_t;

typedef struct
{
    float    Kp;
    float    Kd;
    float    ema_alpha;
    track_plan_t plan;
    float    speed_factor;
    uint8_t  debounce_frames;
} track_fsm_cfg_t;

typedef void (*track_fsm_cb_t)(TRACK_ELEMENT state);

#define TRACK_FSM_CFG_COUNT 11

typedef struct
{
    TRACK_ELEMENT     state;
    TRACK_ELEMENT     pending;
    uint8_t           debounce_cnt;
    track_fsm_cfg_t   cfg[TRACK_FSM_CFG_COUNT];

    track_fsm_cb_t    on_entry;
    track_fsm_cb_t    on_exit;

    uint8_t           state_hold;
} track_fsm_t;

extern track_fsm_t g_track_fsm;

void  track_fsm_init(track_fsm_t *fsm);
void  track_fsm_update(track_fsm_t *fsm, TRACK_ELEMENT raw_elem);

float         track_fsm_get_Kp(const track_fsm_t *fsm);
float         track_fsm_get_Kd(const track_fsm_t *fsm);
float         track_fsm_get_ema_alpha(const track_fsm_t *fsm);
float         track_fsm_get_speed_factor(const track_fsm_t *fsm);
track_plan_t  track_fsm_get_plan(const track_fsm_t *fsm);

void track_fsm_set_cfg(track_fsm_t *fsm, TRACK_ELEMENT elem,
                       const track_fsm_cfg_t *cfg);
void track_fsm_set_callbacks(track_fsm_t *fsm,
                             track_fsm_cb_t entry_cb,
                             track_fsm_cb_t exit_cb);

#endif

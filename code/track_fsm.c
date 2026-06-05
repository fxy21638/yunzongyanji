#include "track_fsm.h"

track_fsm_t g_track_fsm;

static const track_fsm_cfg_t s_default_cfg[TRACK_FSM_CFG_COUNT] =
{
    /* NONE 无效 */           {0.40f, 0.35f, 0.80f, PLAN_HOLD,       0.0f,  1},
    /* START 发车 */          {0.40f, 0.35f, 0.80f, PLAN_STRAIGHT,   0.50f, 1},
    /* STRAIGHT 直道 */       {0.40f, 0.35f, 0.80f, PLAN_STRAIGHT,   1.0f,  2},
    /* RIGHT_ANGLE_l 左直角 */{0.45f, 0.40f, 0.70f, PLAN_TURN_LEFT,  0.55f, 3},
    /* RIGHT_ANGLE_r 右直角 */{0.45f, 0.40f, 0.70f, PLAN_TURN_RIGHT, 0.55f, 3},
    /* RING_l 左环岛 */       {0.38f, 0.33f, 0.78f, PLAN_STRAIGHT,   0.65f, 3},
    /* RING_r 右环岛 */       {0.38f, 0.33f, 0.78f, PLAN_STRAIGHT,   0.65f, 3},
    /* RING_c 环岛中心 */     {0.38f, 0.33f, 0.78f, PLAN_STRAIGHT,   0.65f, 3},
    /* CROSS 十字路口 */      {0.32f, 0.28f, 0.85f, PLAN_CROSS,      0.75f, 2},
    /* BROKEN 断桥通过中 */   {0.30f, 0.20f, 0.90f, PLAN_HOLD,       0.45f, 3},
    /* BROKEN_RODE 断桥已过 */{1.40f, 3.40f, 0.60f, PLAN_BROKEN,     0.50f, 1}
};

void track_fsm_init(track_fsm_t *fsm)
{
    uint8_t i;

    fsm->state        = NONE;
    fsm->pending      = NONE;
    fsm->debounce_cnt = 0;
    fsm->state_hold   = 0;
    fsm->on_entry     = 0;
    fsm->on_exit      = 0;

    for (i = 0; i < TRACK_FSM_CFG_COUNT; i++)
    {
        fsm->cfg[i] = s_default_cfg[i];
    }
}

void track_fsm_update(track_fsm_t *fsm, TRACK_ELEMENT raw_elem)
{
    const track_fsm_cfg_t *cfg;
    uint8_t idx;

    if (raw_elem >= TRACK_FSM_CFG_COUNT)
        return;

    if (fsm->state_hold > 0)
    {
        fsm->state_hold--;
        return;
    }

    if (raw_elem == fsm->state)
    {
        fsm->pending      = NONE;
        fsm->debounce_cnt = 0;
        return;
    }

    if (raw_elem == fsm->pending)
    {
        cfg = &fsm->cfg[(uint8_t)raw_elem];
        fsm->debounce_cnt++;
        if (fsm->debounce_cnt >= cfg->debounce_frames)
        {
            if (fsm->on_exit)
                fsm->on_exit(fsm->state);

            idx = (uint8_t)raw_elem;
            fsm->state        = (TRACK_ELEMENT)idx;
            fsm->pending      = NONE;
            fsm->debounce_cnt = 0;

            if (fsm->on_entry)
                fsm->on_entry(fsm->state);
        }
        return;
    }

    fsm->pending      = raw_elem;
    fsm->debounce_cnt = 1;
}

float track_fsm_get_Kp(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT) return 0.40f;
    return fsm->cfg[idx].Kp;
}

float track_fsm_get_Kd(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT) return 0.35f;
    return fsm->cfg[idx].Kd;
}

float track_fsm_get_ema_alpha(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT) return 0.80f;
    return fsm->cfg[idx].ema_alpha;
}

float track_fsm_get_speed_factor(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT) return 0.0f;
    return fsm->cfg[idx].speed_factor;
}

track_plan_t track_fsm_get_plan(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT) return PLAN_HOLD;
    return fsm->cfg[idx].plan;
}

void track_fsm_set_cfg(track_fsm_t *fsm, TRACK_ELEMENT elem,
                       const track_fsm_cfg_t *cfg)
{
    uint8_t idx;
    idx = (uint8_t)elem;
    if (idx >= TRACK_FSM_CFG_COUNT) return;
    fsm->cfg[idx] = *cfg;
}

void track_fsm_set_callbacks(track_fsm_t *fsm,
                             track_fsm_cb_t entry_cb,
                             track_fsm_cb_t exit_cb)
{
    fsm->on_entry = entry_cb;
    fsm->on_exit  = exit_cb;
}

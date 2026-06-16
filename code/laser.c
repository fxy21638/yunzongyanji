#include "laser.h"
#include "main.h"     /* for g_track_valid, g_target_*, etc. via trail.h/vision.h chain */

/* ---- 内部状态 ---- */
static uint8_t  s_state;           /* 0=OFF, 1=FIRING, 2=COOLDOWN */
static uint8_t  s_debounce_cnt;    /* 连续满足条件帧数 */
static uint16_t s_fire_ticks;      /* FIRING 状态下累计 5ms 滴答 */
static uint16_t s_cooldown_ticks;  /* COOLDOWN 状态下累计 5ms 滴答 */

/* ================================================================
 * 初始化 — P9.0~P9.4 推挽输出, 全部 LOW
 * ================================================================ */
void laser_Init(void)
{
    /* TODO: 若更换端口, 同步改 LASER_PORT_M1/M0 宏 + 以下几行 */
    LASER_PORT_M1 &= ~LASER_PIN_ALL;  /* M1=0 */
    LASER_PORT_M0 |= LASER_PIN_ALL;   /* M0=1 → 推挽输出 */
    LASER_PORT     &= ~LASER_PIN_ALL; /* 全部 LOW (关) */

    s_state           = 0;  /* OFF */
    s_debounce_cnt    = 0;
    s_fire_ticks      = 0;
    s_cooldown_ticks  = 0;
}

/* ================================================================
 * 位掩码写入 — 同时控制 5 个激光
 * ================================================================ */
void laser_set_mask(uint8_t mask)
{
    /* TODO: 若更换端口, 改为对应端口的 &= ~ / |= 操作 */
    LASER_PORT = (LASER_PORT & ~LASER_PIN_ALL) | (mask & LASER_PIN_ALL);
}

/* ================================================================
 * 紧急全关 — 赛道丢失 / 异常时调用
 * ================================================================ */
void laser_force_off(void)
{
    laser_set_mask(0x00);
    s_state          = 0;  /* OFF */
    s_debounce_cnt   = 0;
    s_fire_ticks     = 0;
    s_cooldown_ticks = 0;
}

/* ================================================================
 * FSM 更新 — 每 5ms 由 control_timer_callback 调用
 *
 * 状态: OFF → (防抖) → FIRING → COOLDOWN → OFF
 *
 * 开火决策 (按靶子位置 + 大小选择激光组合):
 *
 *   偏移量 offset = |g_target_center_x - 94|
 *
 *   居中 (offset < 10):   CENTER + L1 + R1   (中心点 + 两侧落在环壁)
 *   偏左 (center_x < 84):  CENTER + L1 + L2   (左侧重火力)
 *   偏右 (center_x > 104): CENTER + R1 + R2   (右侧重火力)
 *
 *   距离门控:
 *     radius < 18  → 不开火 (太远)
 *     radius 18~25 → 仅 CENTER  (保守)
 *     radius ≥ 25  → CENTER + 2 个侧激光
 * ================================================================ */
void laser_fsm_update(void)
{
    uint8_t target_ok;
    uint8_t radius;
    uint8_t center_x;
    uint8_t offset;
    uint8_t fire_mask;

    /* ---- 变量声明区 (C251 要求块首) ---- */
    target_ok = 0;
    radius    = 0;
    center_x  = 94;
    offset    = 0;
    fire_mask = 0;

    /* ---- 紧急门: 赛道丢失 → 立即全关 ---- */
    if (!g_track_valid)
    {
        laser_force_off();
        return;
    }

    /* ---- 读取靶子状态 ---- */
    if (g_target_detected)
    {
        target_ok = 1;
        radius    = g_target_radius;
        center_x  = g_target_center_x;
        if (center_x >= 94)
            offset = center_x - 94;
        else
            offset = 94 - center_x;
    }

    /* ---- 计算开火位掩码 ---- */
    if (target_ok && radius > LASER_FIRE_RADIUS_MIN)
    {
        /* 基础: 至少开中心激光 */
        fire_mask = LASER_PIN_CENTER;

        /* 距离够近时可加侧激光 */
        if (radius >= LASER_FIRE_RADIUS_MID)
        {
            if (offset < LASER_CENTER_WINDOW)
            {
                /* 靶子居中: 对称开中间 3 个 */
                fire_mask |= LASER_PIN_L1 | LASER_PIN_R1;
            }
            else if (center_x < 94)
            {
                /* 靶子偏左: 左侧火力 */
                fire_mask |= LASER_PIN_L1 | LASER_PIN_L2;
            }
            else
            {
                /* 靶子偏右: 右侧火力 */
                fire_mask |= LASER_PIN_R1 | LASER_PIN_R2;
            }
        }
    }
    else
    {
        fire_mask = 0;
    }

    /* ---- 状态机 ---- */
    if (s_state == 0)  /* OFF */
    {
        if (fire_mask != 0)
        {
            s_debounce_cnt++;
            if (s_debounce_cnt >= LASER_DEBOUNCE_CNT)
            {
                s_state        = 1;  /* FIRING */
                s_debounce_cnt = 0;
                s_fire_ticks   = 0;
                laser_set_mask(fire_mask);
            }
        }
        else
        {
            s_debounce_cnt = 0;
        }
    }
    else if (s_state == 1)  /* FIRING */
    {
        s_fire_ticks++;

        /* 更新掩码 (靶子位置可能变化) */
        if (fire_mask != 0)
            laser_set_mask(fire_mask);

        /* 退出条件: 靶子丢失 / 半径缩小 / 超时 */
        if (!target_ok
            || radius < LASER_STOP_RADIUS
            || s_fire_ticks > (LASER_MAX_ON_MS / 5u))
        {
            laser_set_mask(0x00);
            s_state          = 2;  /* COOLDOWN */
            s_cooldown_ticks = 0;
        }
    }
    else  /* COOLDOWN (s_state == 2) */
    {
        s_cooldown_ticks++;
        if (!target_ok && s_cooldown_ticks > (LASER_COOLDOWN_MS / 5u))
        {
            s_state          = 0;  /* OFF */
            s_debounce_cnt   = 0;
            s_cooldown_ticks = 0;
        }
    }
}

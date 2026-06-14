// ====================================================================
// 循迹状态机 (Track FSM) — 滞回滤波 + 每元素独立 PID/EMA/速度参数
// ====================================================================
//
// 核心机制:
//   1. 滞回转换 (debounce): 候选元素需连续 N 帧不变才确认切换
//   2. 状态保持 (state_hold): 状态切换后锁定 M 帧, 防止反复横跳
//   3. 每元素配置表: 位置 PID + 角度 PID + EMA + 规划策略 + 速度倍率
//
// 配置表字段 (track_fsm_cfg_t):
//   Kp/Ki/Kd/integral_max  — 位置 PID (控制中线偏差 → 舵机)
//   angle_kp/ki/kd/imax/w   — 角度 PID (控制赛道方向变化)
//   ema_alpha               — 转向输出平滑系数 (越大越灵敏)
//   plan                    — 目标规划策略 (PLAN_STRAIGHT/CROSS/...)
//   speed_factor            — 速度倍率 (1.0=全速)
//   debounce_frames         — 滞回确认帧数
//
// 规划策略 (track_plan_t):
//   PLAN_STRAIGHT   (0) — 直道: 近远加权中点
//   PLAN_TURN_LEFT  (1) — 左弯: 道路中心 + 左偏置
//   PLAN_TURN_RIGHT (2) — 右弯: 道路中心 + 右偏置
//   PLAN_CROSS      (3) — 十字: 取图像中心
//   PLAN_BROKEN     (4) — 断桥后: 陀螺仪航向保持
//   PLAN_HOLD       (5) — 保持上一帧目标不变
//
// 使用方式:
//   track_fsm_init(&g_track_fsm)           — 初始化 (加载默认配置)
//   track_fsm_set_callbacks(...)           — 注册 entry/exit 回调
//   track_fsm_update(&g_track_fsm, raw)    — 每帧喂入原始分类结果
//   track_fsm_get_Kp/Kd/...(&g_track_fsm) — control.c 取参
// ====================================================================

#include "track_fsm.h"

track_fsm_t g_track_fsm;

/* ================================================================
 * 默认配置表 — 11 元素的 PID/EMA/规划/速度参数
 *
 * 字段顺序: Kp, Ki, Kd, imax, aKp, aKi, aKd, aImax, aW, EMA, plan, spd, db
 *
 * 调参指南:
 *   Kp ↑ → 转向更猛, 过大振荡
 *   Kd ↑ → 阻尼增强, 过大高频抖动
 *   Ki ↑ → 消除稳态误差, 过大积分饱和
 *   ema_alpha ↑ → 响应更快, 但更不平滑
 *   speed_factor ↑ → 提速
 *   debounce_frames ↑ → 防误触发, 但响应变慢
 *   angle_weight ↑ → 角度环占比增加, 预判弯道更早
 * ================================================================ */
static const track_fsm_cfg_t s_default_cfg[TRACK_FSM_CFG_COUNT] =
{
	/*                      Kp     Ki    Kd    imax  aKp   aKi   aKd   aImax aW    EMA    plan             spd  db */
	/* NONE 无效 */         {0.20f,0.00f,0.18f,0.0f, 0.20f,0.00f,0.40f,0.0f, 0.00f,0.80f, PLAN_HOLD,       0.0f, 1},
	/* START 发车 */        {0.20f,0.00f,0.18f,0.0f, 0.20f,0.00f,0.40f,0.0f, 0.10f,0.80f, PLAN_STRAIGHT,   0.50f,1},
	/* STRAIGHT 直道 */     {0.30f,0.00f,0.08f,0.0f, 0.25f,0.02f,0.40f,2.0f, 0.15f,0.80f, PLAN_STRAIGHT,   1.0f, 3},
	/* RIGHT_ANGLE_l 左弯 */{0.35f,0.00f,0.10f,0.0f, 0.40f,0.06f,0.50f,6.0f, 0.30f,0.72f,  PLAN_TURN_LEFT,  0.55f,5},
	/* RIGHT_ANGLE_r 右弯 */{0.35f,0.00f,0.10f,0.0f, 0.40f,0.06f,0.50f,6.0f, 0.30f,0.72f, PLAN_TURN_RIGHT, 0.55f,5},
	/* RING_l 左环岛 */     {0.42f,0.00f,0.30f,0.0f, 0.35f,0.03f,0.50f,3.0f, 0.25f,0.80f, PLAN_TURN_LEFT,  0.65f,1},
	/* RING_r 右环岛 */     {0.42f,0.00f,0.30f,0.0f, 0.35f,0.03f,0.50f,3.0f, 0.25f,0.80f, PLAN_TURN_RIGHT, 0.65f,1},
	/* RING_c 环岛中心 */   {0.42f,0.00f,0.30f,0.0f, 0.35f,0.03f,0.50f,3.0f, 0.25f,0.80f, PLAN_STRAIGHT,   0.65f,1},
	/* CROSS 十字路口 */    {0.35f,0.00f,0.25f,0.0f, 0.20f,0.00f,0.40f,0.0f, 0.10f,0.85f, PLAN_CROSS,      0.75f,2},
	/* BROKEN 断桥通过中 */ {0.25f,0.00f,0.15f,0.0f, 0.20f,0.00f,0.35f,0.0f, 0.05f,0.90f, PLAN_HOLD,       0.45f,3},
	/* BROKEN_RODE 断桥后 */{1.00f,0.00f,2.00f,0.0f, 0.00f,0.00f,0.00f,0.0f, 0.00f,0.60f, PLAN_BROKEN,     0.50f,2}
};

/* ================================================================
 * 初始化 — 加载默认配置表, 清零运行状态
 * ================================================================ */
void track_fsm_init(track_fsm_t *fsm)
{
    uint8_t i;

    fsm->state = NONE;
    fsm->pending = NONE;
    fsm->debounce_cnt = 0;
    fsm->state_hold = 0;
    fsm->on_entry = 0;
    fsm->on_exit = 0;

    for (i = 0; i < TRACK_FSM_CFG_COUNT; i++)
    {
        fsm->cfg[i] = s_default_cfg[i];
    }
}

/* ================================================================
 * 滞回状态转换 — debounce 机制 + entry/exit 回调
 *
 * 转换流程:
 *   raw ≠ state 且 raw ≠ pending → 设为候选, debounce_cnt=1
 *   raw = pending               → debounce_cnt++
 *   debounce_cnt ≥ debounce_frames → 确认转换:
 *     on_exit(old) → state=new → on_entry(new)
 *
 * state_hold > 0 时跳过所有转换 (防止反复横跳)
 * ================================================================ */
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
        fsm->pending = NONE;
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
            fsm->state = (TRACK_ELEMENT)idx;
            fsm->pending = NONE;
            fsm->debounce_cnt = 0;

            if (fsm->on_entry)
                fsm->on_entry(fsm->state);
        }
        return;
    }

    fsm->pending = raw_elem;
    fsm->debounce_cnt = 1;
}

/* ================================================================
 * 参数查询 — 从当前状态的配置中取对应字段
 *
 * track_fsm_get_cfg() 一步返指针, 替代多次 getter 调用。
 * 所有 getter 都有边界保护: 状态索引越界时返回安全默认值
 * ================================================================ */

const track_fsm_cfg_t *track_fsm_get_cfg(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        idx = 2;  /* 越界回退 STRAIGHT */
    return &fsm->cfg[idx];
}

float track_fsm_get_Kp(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return 0.40f;
    return fsm->cfg[idx].Kp;
}

float track_fsm_get_Kd(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return 0.35f;
    return fsm->cfg[idx].Kd;
}

float track_fsm_get_Ki(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return 0.00f;
    return fsm->cfg[idx].Ki;
}

float track_fsm_get_integral_max(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return 0.0f;
    return fsm->cfg[idx].integral_max;
}

float track_fsm_get_ema_alpha(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return 0.80f;
    return fsm->cfg[idx].ema_alpha;
}

float track_fsm_get_angle_kp(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return 0.30f;
    return fsm->cfg[idx].angle_kp;
}

float track_fsm_get_angle_ki(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return 0.00f;
    return fsm->cfg[idx].angle_ki;
}

float track_fsm_get_angle_kd(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return 0.45f;
    return fsm->cfg[idx].angle_kd;
}

float track_fsm_get_angle_imax(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return 0.0f;
    return fsm->cfg[idx].angle_imax;
}

float track_fsm_get_angle_weight(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return 0.20f;
    return fsm->cfg[idx].angle_weight;
}

float track_fsm_get_speed_factor(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return 0.0f;
    return fsm->cfg[idx].speed_factor;
}

track_plan_t track_fsm_get_plan(const track_fsm_t *fsm)
{
    uint8_t idx;
    idx = (uint8_t)fsm->state;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return PLAN_HOLD;
    return fsm->cfg[idx].plan;
}

/* ================================================================
 * 配置写入 — 运行时修改单元素配置 (调参用)
 * ================================================================ */
void track_fsm_set_cfg(track_fsm_t *fsm, TRACK_ELEMENT elem,
                       const track_fsm_cfg_t *cfg)
{
    uint8_t idx;
    idx = (uint8_t)elem;
    if (idx >= TRACK_FSM_CFG_COUNT)
        return;
    fsm->cfg[idx] = *cfg;
}

void track_fsm_set_callbacks(track_fsm_t *fsm,
                             track_fsm_cb_t entry_cb,
                             track_fsm_cb_t exit_cb)
{
    fsm->on_entry = entry_cb;
    fsm->on_exit = exit_cb;
}

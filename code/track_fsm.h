// ====================================================================
// 循迹状态机 — 滞回滤波 + 每元素独立 PID/EMA/速度参数
// ====================================================================

#ifndef __TRACK_FSM_H__
#define __TRACK_FSM_H__

#include "trail.h"

/* ---- 目标规划策略 ---- */
enum
{
    PLAN_STRAIGHT   = 0,  /* 直道: 近远加权中点 (near + far×2)/3 */
    PLAN_TURN_LEFT  = 1,  /* 左弯: 道路中心 + 左偏置 */
    PLAN_TURN_RIGHT = 2,  /* 右弯: 道路中心 + 右偏置 */
    PLAN_CROSS      = 3,  /* 十字: 取图像中心点 */
    PLAN_BROKEN     = 4,  /* 断桥后: 陀螺仪航向保持, 忽略图像 */
    PLAN_HOLD       = 5   /* 兜底: 保持上一帧目标不变 */
};
typedef uint8_t track_plan_t;

/* ---- 每元素配置 (11 元素 × 14 字段 = 56 字节/元素, ~616 字节 xdata) ---- */
typedef struct
{
    /* 位置 PID — 中线偏差 → 舵机转向 */
    float    Kp;              /* 比例: 偏差越大输出越大 */
    float    Ki;              /* 积分: 消除稳态误差 (弯道/环岛使用) */
    float    Kd;              /* 微分: 阻尼, 抑制振荡 */
    float    integral_max;    /* 积分限幅 */

    /* 角度 PID — 赛道方向变化 → 预判弯道 (与位置环加权融合) */
    float    angle_kp;        /* 角度环比例 */
    float    angle_ki;        /* 角度环积分 */
    float    angle_kd;        /* 角度环微分 */
    float    angle_imax;      /* 角度环积分限幅 */
    float    angle_weight;    /* 角度环融合权重 (0.0~1.0), 越大角度环越强 */

    /* 其他 */
    float    ema_alpha;       /* EMA 平滑系数: 0=完全平滑, 1=立即响应 */
    track_plan_t plan;        /* 目标规划策略 */
    float    speed_factor;    /* 速度倍率: 1.0=全速, 0.5=半速 */
    uint8_t  debounce_frames; /* 滞回确认帧数: 连续多少帧不变才切换 */
} track_fsm_cfg_t;

/* ---- 状态切换回调 ---- */
typedef void (*track_fsm_cb_t)(TRACK_ELEMENT state);

#define TRACK_FSM_CFG_COUNT 11   /* NONE=0..BROKEN_RODE=10 */

/* ---- 状态机实例 (~680 字节) ---- */
typedef struct
{
    TRACK_ELEMENT     state;         /* 当前确认状态 */
    TRACK_ELEMENT     pending;       /* 候选状态 (debounce 中) */
    uint8_t           debounce_cnt;  /* 候选累计帧数 */
    track_fsm_cfg_t   cfg[TRACK_FSM_CFG_COUNT];  /* 每元素配置表 */

    track_fsm_cb_t    on_entry;      /* 进入状态回调 (trail.c 注册) */
    track_fsm_cb_t    on_exit;       /* 退出状态回调 */

    uint8_t           state_hold;    /* 状态锁定剩余帧数 (防反复横跳) */
} track_fsm_t;

/* ---- 全局状态机实例 (trail.c 使用) ---- */
extern track_fsm_t g_track_fsm;

/* ---- 生命周期 ---- */
void  track_fsm_init(track_fsm_t *fsm);                          /* 加载默认配置 + 清零状态 */
void  track_fsm_update(track_fsm_t *fsm, TRACK_ELEMENT raw_elem); /* 每帧喂入原始分类, 执行滞回转换 */

/* ---- 参数查询 — control.c 每帧从 FSM 取当前状态的 PID/EMA/速度 ---- */
float         track_fsm_get_Kp(const track_fsm_t *fsm);            /* 位置环比例 */
float         track_fsm_get_Kd(const track_fsm_t *fsm);            /* 位置环微分 */
float         track_fsm_get_Ki(const track_fsm_t *fsm);            /* 位置环积分 */
float         track_fsm_get_integral_max(const track_fsm_t *fsm);  /* 积分限幅 */
float         track_fsm_get_ema_alpha(const track_fsm_t *fsm);     /* 转向 EMA 平滑系数 */
float         track_fsm_get_angle_kp(const track_fsm_t *fsm);      /* 角度环比例 */
float         track_fsm_get_angle_ki(const track_fsm_t *fsm);      /* 角度环积分 */
float         track_fsm_get_angle_kd(const track_fsm_t *fsm);      /* 角度环微分 */
float         track_fsm_get_angle_imax(const track_fsm_t *fsm);    /* 角度环积分限幅 */
float         track_fsm_get_angle_weight(const track_fsm_t *fsm);  /* 角度环融合权重 */
float         track_fsm_get_speed_factor(const track_fsm_t *fsm);  /* 速度倍率 */
track_plan_t  track_fsm_get_plan(const track_fsm_t *fsm);          /* 目标规划策略 */

/* ---- 配置写入 (运行时调参) ---- */
void track_fsm_set_cfg(track_fsm_t *fsm, TRACK_ELEMENT elem,
                       const track_fsm_cfg_t *cfg);               /* 覆盖单个元素的配置 */
void track_fsm_set_callbacks(track_fsm_t *fsm,
                             track_fsm_cb_t entry_cb,
                             track_fsm_cb_t exit_cb);              /* 注册 entry/exit 回调 */

#endif

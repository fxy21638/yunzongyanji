// ====================================================================
// 环岛状态机 — 封装环岛检测、入环/出环/中心转换、目标规划
// ====================================================================
//
// 核心检测条件: 必须同时满足两个条件才确认环岛
//   条件1: 一侧边界出现"终点"(分叉/跳变), 另一侧保持稳定
//   条件2: 分叉上方仍有道路 (中线不偏太远), 排除转弯误判
//
// 检测策略: 段分叉优先 (不依赖边界突变阈值), 边界突变扫描兜底
//
// 环岛生命周期:
//   IDLE → (条件1+2同时成立) → ENTER_l/r
//   ENTER_l/r → (转过阈值角度) → CENTER
//   CENTER → (检测到对侧分叉) → IDLE
// ====================================================================

#include "ring_fsm.h"
#include "control.h"
#include "icm.h"
#include "vision.h"

/* ---- 外部引用: 段分类数据 (trail.c) ---- */
extern int8_t  g_seg_type[];
extern uint8_t g_seg_start[];
extern uint8_t g_seg_end[];
extern uint8_t g_seg_num;

/* ---- 外部引用: 中线限幅 (trail.c) ---- */
extern uint8_t clamp_center_to_target(int16_t center_x);

/* ---- 全局环岛状态机实例 ---- */
ring_fsm_t g_ring_fsm;

/* ================================================================
 * 第 1 节 — 环岛检测常量
 * ================================================================ */

/* 边界突变扫描 */
#define RING_SUDDEN_TH      10   /* 边界突变下限: |dl/dr|>10 认为跳变 */
#define RING_SUDDEN_MAX     40   /* 边界突变上限: |dl/dr|>40 视为追踪伪影 */
#define RING_STABLE_TH       3   /* 稳定段 dl/dr 上限: |dl/dr|<3 认为平滑 */
#define RING_STABLE_MIN      5   /* 突变前最少稳定行数 */
#define RING_ROAD_AHEAD_MIN  3   /* 突变后最少有路行数 */
#define RING_SCAN_Y_NEAR     (MT9V034_HEIGHT - 8)    /* 扫描起点(近行) 112 */
#define RING_SCAN_Y_FAR      (MT9V034_HEIGHT / 5)    /* 扫描终点(远行) 24 */
#define RING_NEAR_SEARCH     8   /* 近行丢线时向上搜索双边行的最大行数 */

/* 段分叉检测 */
#define RING_FORK_BOTH_MIN   10  /* BOTH 段最少行数 */
#define RING_FORK_Y_MIN      55  /* 分叉点最小行号 (太远忽略) */
#define RING_ROAD_CENTER_TOL 30  /* 上方道路中线偏离容差 */

/* 条件3: 边界平滑度 — 参考浙大 cur_circle, 三行边界变化率一致性
   真正的环岛边界是逐渐鼓出的(平滑), 追踪伪影是突变的(锯齿)
   d1*5 ≈ d2*7 表示每行变化率一致 → 边界平滑 */
#define RING_SMOOTH_MAX_DIFF 8    /* |d1*7 - d2*5| 上限, 超过则边界锯齿化 */

/* 环岛目标偏置: 入环时跟鼓出侧边界的偏移量 (像素) */
#define RING_ENTRY_OFFSET    30

/* ================================================================
 * 第 2 节 — 边界突变扫描 (逐行扫描一侧边界跳变)
 *
 * 从近到远扫描, 找一侧边界突然大幅跳变("刺入"),
 * 同时另一侧保持稳定, 跳变上方仍有路(中线居中)确认岛后通路。
 * 以此区分环岛(跳变后有路)和普通转弯/断头路(跳变后没路)。
 *
 * 返回值: 0=无突变, 1=左环岛, 2=右环岛
 * ================================================================ */
static uint8_t scan_ring_jump(void)
{
    uint16_t y;
    uint16_t start_y;
    int16_t l_prev, r_prev, l_cur, r_cur;
    int16_t dl, dr;
    uint8_t stable_cnt;
    uint8_t jump_side;
    uint16_t jump_y;
    uint8_t road_cnt;
    int16_t center;
    uint8_t found;
    uint8_t left_lost, right_lost;

    /* 0. 找第一个双边可见行 */
    start_y = (uint16_t)RING_SCAN_Y_NEAR;
    l_prev = g_track.left[start_y];
    r_prev = g_track.right[start_y];
    if (l_prev <= 2 || r_prev >= (int16_t)(MT9V034_WIDTH - 4))
    {
        found = 0;
        for (y = (uint16_t)(RING_SCAN_Y_NEAR - 1);
             y > (uint16_t)(RING_SCAN_Y_NEAR - RING_NEAR_SEARCH); y--)
        {
            l_cur = g_track.left[y];
            r_cur = g_track.right[y];
            if (l_cur > 2 && r_cur < (int16_t)(MT9V034_WIDTH - 4))
            {
                start_y = y;
                l_prev = l_cur;
                r_prev = r_cur;
                found = 1;
                break;
            }
        }
        if (!found)
            return 0;
    }

    stable_cnt = 0;
    jump_side = 0;
    jump_y = 0;

    for (y = start_y - 1; y > (uint16_t)RING_SCAN_Y_FAR; y--)
    {
        l_cur = g_track.left[y];
        r_cur = g_track.right[y];
        dl = l_cur - l_prev;
        dr = r_cur - r_prev;

        left_lost  = (l_cur <= 2) ? 1 : 0;
        right_lost = (r_cur >= (int16_t)(MT9V034_WIDTH - 4)) ? 1 : 0;

        if (left_lost || right_lost)
        {
            /* 单侧丢线 — 可能是环岛跳变 (边界突然刺入画面) */
            if (stable_cnt >= RING_STABLE_MIN && jump_side == 0)
            {
                if (left_lost && !right_lost)
                {
                    if (dl < -(int16_t)RING_SUDDEN_TH &&
                        dr > -(int16_t)RING_STABLE_TH && dr < (int16_t)RING_STABLE_TH)
                    {
                        jump_side = 1;  /* 左边界跳变 → 左环岛 */
                        jump_y = y;
                    }
                }
                else if (right_lost && !left_lost)
                {
                    if (dr > (int16_t)RING_SUDDEN_TH &&
                        dl > -(int16_t)RING_STABLE_TH && dl < (int16_t)RING_STABLE_TH)
                    {
                        jump_side = 2;  /* 右边界跳变 → 右环岛 */
                        jump_y = y;
                    }
                }
            }

            stable_cnt = 0;
            l_prev = l_cur;
            r_prev = r_cur;
            continue;
        }

        /* 双边可见行 */
        if (jump_side == 0)
        {
            if (dl > -(int16_t)RING_STABLE_TH && dl < (int16_t)RING_STABLE_TH &&
                dr > -(int16_t)RING_STABLE_TH && dr < (int16_t)RING_STABLE_TH)
            {
                stable_cnt++;
            }
            else if (stable_cnt >= RING_STABLE_MIN)
            {
                /* 稳定段后在双边范围内出现跳变 (带上限防追踪伪影) */
                if (dl < -(int16_t)RING_SUDDEN_TH && dl > -(int16_t)RING_SUDDEN_MAX &&
                    dr > -(int16_t)RING_STABLE_TH && dr < (int16_t)RING_STABLE_TH)
                {
                    jump_side = 1;  /* 左边界向外跳 → 左环岛 */
                    jump_y = y;
                }
                else if (dr > (int16_t)RING_SUDDEN_TH && dr < (int16_t)RING_SUDDEN_MAX &&
                         dl > -(int16_t)RING_STABLE_TH && dl < (int16_t)RING_STABLE_TH)
                {
                    jump_side = 2;  /* 右边界向外跳 → 右环岛 */
                    jump_y = y;
                }
                else
                {
                    stable_cnt = 0;
                }
            }
            else
            {
                stable_cnt = 0;
            }
        }

        l_prev = l_cur;
        r_prev = r_cur;
    }

    if (jump_side == 0)
        return 0;

    /* 2. 检查跳变上方是否有路 (允许单侧可见 — 环岛入口特征) */
    road_cnt = 0;
    for (y = jump_y; y > (uint16_t)RING_SCAN_Y_FAR && y > 0; y--)
    {
        l_cur = g_track.left[y];
        r_cur = g_track.right[y];
        if (l_cur > 2 && r_cur < (int16_t)(MT9V034_WIDTH - 4))
        {
            center = (l_cur + r_cur) / 2;
            if (center > (int16_t)(CENTER_POINT - 25) && center < (int16_t)(CENTER_POINT + 25))
            {
                road_cnt++;
                if (road_cnt >= RING_ROAD_AHEAD_MIN)
                    return jump_side;
            }
        }
        else if (l_cur > 2 && r_cur >= (int16_t)(MT9V034_WIDTH - 4))
        {
            /* 只有左边界 — 估计中线=左边界+半道宽(~30) */
            center = l_cur + 30;
            if (center > (int16_t)(CENTER_POINT - 25) && center < (int16_t)(CENTER_POINT + 25))
            {
                road_cnt++;
                if (road_cnt >= RING_ROAD_AHEAD_MIN)
                    return jump_side;
            }
        }
        else if (l_cur <= 2 && r_cur < (int16_t)(MT9V034_WIDTH - 4))
        {
            /* 只有右边界 — 估计中线=右边界-半道宽(~30) */
            center = r_cur - 30;
            if (center > (int16_t)(CENTER_POINT - 25) && center < (int16_t)(CENTER_POINT + 25))
            {
                road_cnt++;
                if (road_cnt >= RING_ROAD_AHEAD_MIN)
                    return jump_side;
            }
        }
    }

    return 0;
}

/* ================================================================
 * 第 3 节 — 段分叉检测 (主要检测路径)
 *
 * 利用已计算的段序列 (g_seg_type/start/end/num), 识别
 * BOTH→单侧丢线(BOTH→单侧突变) 的分叉模式。
 *
 * 确认条件 (必须同时满足):
 *   条件1: 近处正常双边(BOTH段≥10行, 分叉位置合理),
 *          远端一侧边界出现"终点"(LEFT_LOST/RIGHT_LOST/LEFT_JUMP/RIGHT_JUMP)
 *   条件2: 分叉上方仍有道路 (≥3行中心不偏), 排除十字(s2≠超宽)
 *
 * 返回值: NONE / RING_l / RING_r
 * ================================================================ */
static TRACK_ELEMENT detect_ring_from_segments(void)
{
    int8_t s0_type;
    int8_t s1_type;
    uint8_t both_len;
    uint8_t fork_y;
    uint8_t ring_dir;
    uint8_t road_cnt;
    uint16_t y;
    int16_t l_cur;
    int16_t r_cur;
    int16_t center;

    if (g_seg_num < 2)
        return NONE;

    s0_type = g_seg_type[0];
    s1_type = g_seg_type[1];

    /* 条件1: 近处必须有 BOTH 段打底, 且足够长 */
    if (s0_type != 0)   /* ROW_BOTH = 0 */
        return NONE;
    both_len = g_seg_start[0] - g_seg_end[0] + 1;
    if (both_len < RING_FORK_BOTH_MIN)
        return NONE;

    /* 条件1(续): 第二段必须是单侧丢线/突变 (边界终点) */
    if (s1_type == 1)         /* ROW_LEFT_LOST */
        ring_dir = RING_l;
    else if (s1_type == 2)    /* ROW_RIGHT_LOST */
        ring_dir = RING_r;
    else if (s1_type == 5)    /* ROW_LEFT_JUMP */
        ring_dir = RING_l;
    else if (s1_type == 6)    /* ROW_RIGHT_JUMP */
        ring_dir = RING_r;
    else
        return NONE;

    /* 分叉点不能太远 (排除图像顶部边界丢失导致的假分叉) */
    fork_y = g_seg_start[1];
    if (fork_y < RING_FORK_Y_MIN)
        return NONE;

    /* 排除十字: s2 是超宽段 → 十字路口, 不是环岛 */
    if (g_seg_num >= 3)
    {
        if (g_seg_type[2] == 3)   /* ROW_WIDE */
            return NONE;
    }

    /* 条件2: 分叉上方必须有路 (≥3行道路可见, 中线不偏太远)
       允许单侧可见 — 环岛上方只有一侧边界是正常的 */
    road_cnt = 0;
    for (y = (uint16_t)fork_y; y > (uint16_t)RING_SCAN_Y_FAR; y--)
    {
        l_cur = g_track.left[y];
        r_cur = g_track.right[y];
        if (l_cur > 2 || r_cur < (int16_t)(MT9V034_WIDTH - 4))
        {
            if (l_cur > 2 && r_cur < (int16_t)(MT9V034_WIDTH - 4))
            {
                center = (l_cur + r_cur) / 2;
            }
            else if (l_cur > 2)
            {
                center = l_cur + 30;
            }
            else
            {
                center = r_cur - 30;
            }
            if (abs(center - (int16_t)CENTER_POINT) < RING_ROAD_CENTER_TOL)
            {
                road_cnt++;
                if (road_cnt >= RING_ROAD_AHEAD_MIN)
                {
                    /* 条件3: 边界平滑度 — 分叉侧边界在 BOTH 段内变化率是否一致
                       参考浙大 cur_circle: 真正的环岛边界是逐渐鼓出的(平滑线),
                       追踪伪影是突变的(锯齿线)。取分叉点下方三行边界 x 值,
                       检查每行变化率 d1(5行)和 d2(7行)是否接近
                       注意: fork_y+15≥IMG_H 时跳过检查(边界太靠底部) */
                    if (fork_y + 15 < (uint8_t)MT9V034_HEIGHT)
                    {
                        int16_t x_near, x_mid, x_far;
                        int16_t d1, d2, diff;
                        uint8_t y3, y8, y15;

                        y3  = fork_y + 3;
                        y8  = fork_y + 8;
                        y15 = fork_y + 15;

                        if (ring_dir == RING_l)
                        {
                            x_near = g_track.left[y3];
                            x_mid  = g_track.left[y8];
                            x_far  = g_track.left[y15];
                            if (x_near > 2 && x_mid > 2 && x_far > 2)
                            {
                                d1 = x_mid - x_near;    /* 5行间距变化 */
                                d2 = x_far - x_mid;     /* 7行间距变化 */
                                diff = d1 * 7 - d2 * 5; /* 归一化: |d1/5 - d2/7|×35 */
                                if (diff < 0) diff = -diff;
                                if (diff > (int16_t)RING_SMOOTH_MAX_DIFF)
                                    return NONE;  /* 边界锯齿 → 不是环岛 */
                            }
                        }
                        else  /* RING_r: 检查右边界 */
                        {
                            x_near = g_track.right[y3];
                            x_mid  = g_track.right[y8];
                            x_far  = g_track.right[y15];
                            if (x_near < (int16_t)(MT9V034_WIDTH - 4) &&
                                x_mid < (int16_t)(MT9V034_WIDTH - 4) &&
                                x_far < (int16_t)(MT9V034_WIDTH - 4))
                            {
                                d1 = x_mid - x_near;
                                d2 = x_far - x_mid;
                                diff = d1 * 7 - d2 * 5;
                                if (diff < 0) diff = -diff;
                                if (diff > (int16_t)RING_SMOOTH_MAX_DIFF)
                                    return NONE;
                            }
                        }
                    }

                    return (TRACK_ELEMENT)ring_dir;
                }
            }
        }
    }

    return NONE;
}

/* ================================================================
 * 第 4 节 — 环岛入口检测 (组合两套方法)
 *
 * 优先用段分叉检测 (不依赖边界突变阈值, 真实照片可用),
 * 兜底用边界突变扫描 (合成图/极端场景)。
 * 两种方法都在内部验证"条件1(边界终点)+条件2(上方有路)"同时成立。
 * ================================================================ */
static TRACK_ELEMENT detect_ring(void)
{
    TRACK_ELEMENT result;
    uint8_t jump_result;

    /* 优先: 段分叉检测 */
    result = detect_ring_from_segments();
    if (result != NONE)
        return result;

    /* 兜底: 边界突变扫描 */
    jump_result = scan_ring_jump();
    if (jump_result == 1) return RING_l;
    if (jump_result == 2) return RING_r;
    return NONE;
}

/* ================================================================
 * 第 5 节 — 状态机核心
 *
 * ring_fsm_process() 每帧调用, 输入段分类结果, 输出 TRACK_ELEMENT:
 *   - 在环岛中 → 返回 RING_l/r/c (状态保持)
 *   - 不在环岛 → 检查入口条件, 可能返回 RING_l/r, 否则透传 seg_elem
 *
 * 内部状态转换:
 *   IDLE → ENTER_l/r: detect_ring() 非 NONE
 *     - 同时清零 cnt_degree 并捕获 entry_yaw
 *   ENTER_l/r → CENTER: cnt_degree >= RING_CENTER_DEGREE
 *   ENTER_l/r → IDLE: 对侧出现分叉 (路汇合)
 *   CENTER → IDLE: 任一侧出现分叉 (路汇合)
 * ================================================================ */

void ring_fsm_init(ring_fsm_t *rf)
{
    rf->state = RING_IDLE;
    rf->entry_yaw = 0.0f;
}

void ring_fsm_reset(ring_fsm_t *rf)
{
    rf->state = RING_IDLE;
}

uint8_t ring_fsm_is_active(const ring_fsm_t *rf)
{
    return (rf->state != RING_IDLE) ? 1 : 0;
}

TRACK_ELEMENT ring_fsm_process(ring_fsm_t *rf, TRACK_ELEMENT seg_elem)
{
    TRACK_ELEMENT ring_check;

    /* 视觉丢线 → 退出环岛状态 */
    if (!g_track_valid)
    {
        rf->state = RING_IDLE;
        return seg_elem;
    }

    /* ---- 状态保持: 已在环岛中, 检查退出条件 ---- */
    if (rf->state == RING_ENTER_l)
    {
        /* 左环岛: 右侧出现分叉 → 路汇合, 出环岛 */
        ring_check = detect_ring_from_segments();
        if (ring_check == RING_r)
        {
            rf->state = RING_IDLE;
            return STRAIGHT;
        }
        /* 转过阈值角度 → 进入环岛中心 */
        if (cnt_degree >= RING_CENTER_DEGREE)
        {
            rf->state = RING_CENTER;
            return RING_c;
        }
        return RING_l;
    }

    if (rf->state == RING_ENTER_r)
    {
        /* 右环岛: 左侧出现分叉 → 路汇合, 出环岛 */
        ring_check = detect_ring_from_segments();
        if (ring_check == RING_l)
        {
            rf->state = RING_IDLE;
            return STRAIGHT;
        }
        if (cnt_degree >= RING_CENTER_DEGREE)
        {
            rf->state = RING_CENTER;
            return RING_c;
        }
        return RING_r;
    }

    if (rf->state == RING_CENTER)
    {
        /* 环岛中心: 任一侧出现分叉 → 路汇合, 出环岛 */
        ring_check = detect_ring_from_segments();
        if (ring_check != NONE)
        {
            rf->state = RING_IDLE;
            return STRAIGHT;
        }
        return RING_c;
    }

    /* ---- 入口检测: 不在环岛中, 检查是否进入环岛 ----
       段分类看起来像直道或转弯, 但存在分叉+上方有路 → 环岛入口
       条件1(边界终点)+条件2(上方有路) 在 detect_ring() 内部同时验证 */
    if (seg_elem == STRAIGHT || seg_elem == RIGHT_ANGLE_l || seg_elem == RIGHT_ANGLE_r)
    {
        ring_check = detect_ring();
        if (ring_check == RING_l)
        {
            rf->state = RING_ENTER_l;
            rf->entry_yaw = yaw;
            cnt_degree = 0;
            ring_start_yaw = yaw;
            return RING_l;
        }
        if (ring_check == RING_r)
        {
            rf->state = RING_ENTER_r;
            rf->entry_yaw = yaw;
            cnt_degree = 0;
            ring_start_yaw = yaw;
            return RING_r;
        }
    }

    /* 非环岛: 透传段分类结果 */
    return seg_elem;
}

/* ================================================================
 * 第 6 节 — 目标规划
 *
 * 环岛入口: 目标点选在环岛鼓出侧的边界上, 偏移 RING_ENTRY_OFFSET
 *   左环岛 → 跟左边界 + 30
 *   右环岛 → 跟右边界 - 30
 * 环岛中心: 直行取图像中心点
 * ================================================================ */

uint8_t ring_fsm_get_target(const ring_fsm_t *rf)
{
    int16_t l_far, r_far;
    int16_t target;
    uint16_t far_y;

    far_y = (uint16_t)VISION_LOOKAHEAD_Y;
    l_far = g_track.left[far_y];
    r_far = g_track.right[far_y];

    if (rf->state == RING_ENTER_l)
    {
        /* 左环岛: 跟左边界 (环岛鼓出侧) */
        if (l_far > 2)
            target = l_far + (int16_t)RING_ENTRY_OFFSET;
        else
            target = (int16_t)CENTER_POINT - (int16_t)RING_ENTRY_OFFSET;
        return clamp_center_to_target(target);
    }

    if (rf->state == RING_ENTER_r)
    {
        /* 右环岛: 跟右边界 (环岛鼓出侧) */
        if (r_far < (int16_t)(MT9V034_WIDTH - 4))
            target = r_far - (int16_t)RING_ENTRY_OFFSET;
        else
            target = (int16_t)CENTER_POINT + (int16_t)RING_ENTRY_OFFSET;
        return clamp_center_to_target(target);
    }

    /* RING_CENTER / IDLE: 直行取中心 */
    return (uint8_t)CENTER_POINT;
}

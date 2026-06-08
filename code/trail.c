// ====================================================================
// 赛道元素分类 + 目标点规划 — 循迹管线第 2 层
// ====================================================================
//
// 数据流:
//   vision_track.c → g_track (边界/中线/特征)
//     │
//   [1] track_element_judge()  — 元素分类: 分段检测 → 环岛确认 → 十字回退
//   [2] track_fsm_update()     — 滞回滤波 + entry/exit 回调 (track_fsm.c)
//   [3] track_handle()         — 目标规划: 按 FSM plan 策略委派具体规划函数
//     │
//     ▼
//   control.c ← track_midpoint_target + pp_steering_angle
//
// 内部模块:
//   - 纯追踪 (Pure Pursuit): 中线点集 → 前瞻距离 → 转向角 + 曲率估计
//   - 速度决策: 曲率降速 + 视距降速, 取保守值
//   - 环岛检测: 逐行边界突变扫描 (scan_ring_jump → detect_ring)
//   - 行分类 + 分段合并: 7 种行类型 → 段序列 → 元素识别
//   - 目标规划: 直道(近远加权) / 弯道(道路中心估计+偏置) / 十字(图像中心)
// ====================================================================

#ifndef __INTELLISENSE__
#include "ky_headfile.h"
#endif

#include "trail.h"
#include "main.h"
#include "track_fsm.h"

/* ================================================================
 * 第 1 节 — 常量定义
 * ================================================================ */

/* 目标规划参数 */
#define TRACK_LOOKAHEAD_Y_NEAR (MT9V034_HEIGHT - 22)  /* 直道近点行: 98 */
#define TRACK_LOOKAHEAD_Y_FAR  (MT9V034_HEIGHT / 2)   /* 直道远点行: 60 (权重 67%) */
#define TRACK_EDGE_NEAR_TH     3
#define TRACK_WIDE_TH          (MT9V034_WIDTH * 7 / 10)

/* 调试开关 */
#define TRAIL_DBG_PRINTF       0

/* 弯道/十字检测参数 */
#define TRACK_MIN_VALID_TURN_ROWS 8
#define CROSS_MIN_STREAK          3
#define CROSS_TOUCH_MARGIN        4
#define CROSS_WIDE_EXTRA_NUM      5

/* 转弯目标偏置: 向弯道内侧偏移, 越大切入越深 (3~10) */
#define TRACK_TURN_BIAS          6
/* 环岛目标偏置: 叠加在转弯偏置上, 绕岛更外 (2~8) */
#define RING_BIAS                4

/* 纯追踪参数 */
#define PP_LOOKAHEAD_MIN   12    /* 最短前瞻距离 (像素) */
#define PP_LOOKAHEAD_MAX   70    /* 最长前瞻距离 (像素) */
#define PP_LOOKAHEAD_SCALE 4     /* 前瞻 = 速度 / SCALE */

/* VOFA+ Firewater 遥测 (通过 CDC 发送 10 个 float) */
#define VOFA_FIREWATER 0
#if VOFA_FIREWATER
#define VOFA_FLOAT_COUNT 10
#endif

/* ================================================================
 * 第 2 节 — 全局状态
 * ================================================================ */

uint8_t white_count = 0;
uint8_t straight_target = 0;
uint8_t white_segments[20] = {0};
uint8_t time_search = 0;

/* 元素分类结果 (FSM 滤波后) */
TRACK_ELEMENT track_element = NONE;
TRACK_ELEMENT track_element_P = NONE;    /* 上一帧 */
TRACK_ELEMENT current_element = NONE;    /* 原始分类 (未滤波) */
uint8_t track_midpoint_target = CENTER_POINT;
uint8_t track_midpoint_target_P = CENTER_POINT;

/* 纯追踪输出 (供 control.c 使用) */
float pp_steering_angle = 0.0f;   /* 转向角 (度), 正值右转 */
float pp_lookahead_dist = 25.0f;  /* 当前前瞻距离 (像素) */
float pp_curvature = 0.0f;        /* 赛道曲率估计 (×1000) */
uint8_t pp_visible_high = 120;    /* 可见赛道行数 */

/* 断桥状态 */
uint8_t start_stage = 0;
uint8_t broken_flag = 0;
int32_t judge_distance = 0;       /* 断桥累计行驶距离 */

/* ================================================================
 * 第 3 节 — 元素名称 (调试用)
 * ================================================================ */

static const char *track_element_name(TRACK_ELEMENT element)
{
    switch (element)
    {
    case NONE:
        return "NONE";
    case START:
        return "START";
    case STRAIGHT:
        return "STRAIGHT";
    case RIGHT_ANGLE_l:
        return "RIGHT_ANGLE_L";
    case RIGHT_ANGLE_r:
        return "RIGHT_ANGLE_R";
    case RING_l:
        return "RING_L";
    case RING_r:
        return "RING_R";
    case RING_c:
        return "RING_C";
    case CROSS:
        return "CROSS";
    case BROKEN:
        return "BROKEN";
    case BROKEN_RODE:
        return "BROKEN_ROAD";
    default:
        return "UNKNOWN";
    }
}

/* ================================================================
 * 第 4 节 — 纯追踪 (Pure Pursuit)
 *
 * pure_pursuit_angle()    — 在中线点集中找离前瞻距离最近的点, 返回转向角
 * compute_road_curvature() — 双边边界 Menger 曲率均值 (×1000)
 * plan_pure_pursuit()     — 根据速度计算前瞻距离, 调用 pure_pursuit_angle
 * ================================================================ */

/* 在前瞻距离处找中线目标点, 返回转向角 (度) */
static float pure_pursuit_angle(const vision_track_result_t *track, float lookahead)
{
    uint8_t i;
    uint8_t best_idx;
    float min_diff;
    float vehicle_x, vehicle_y;
    float target_x, target_y;
    float dx, dy;
    float angle;

    if (track->mid_step < 2)
        return 0.0f;

    vehicle_x = (float)(MT9V034_WIDTH / 2);
    vehicle_y = (float)MT9V034_HEIGHT;

    best_idx = 0;
    min_diff = 1e9f;

    for (i = 0; i < track->mid_step; i++)
    {
        float dist;
        float diff;
        dist = (float)track->mid_dist[i];
        if (dist < 1.0f)
            continue;
        diff = dist - lookahead;
        if (diff < 0.0f)
            diff = -diff;
        if (diff < min_diff)
        {
            min_diff = diff;
            best_idx = i;
        }
    }

    target_x = (float)track->mid_pts[best_idx][0];
    target_y = (float)track->mid_pts[best_idx][1];

    dx = target_x - vehicle_x;
    dy = vehicle_y - target_y;
    if (dy < 1.0f)
        dy = 1.0f;

    angle = atan2f(dx, dy) * 180.0f / 3.14159265358979f;
    return angle;
}

/* 双边边界 Menger 曲率均值 (×1000), 用于速度决策 */
static float compute_road_curvature(const vision_track_result_t *track)
{
    float curv_l, curv_r;
    uint8_t cnt;

    cnt = 0;
    curv_l = 0.0f;
    curv_r = 0.0f;

    if (track->left_bev_step > 10)
    {
        uint8_t p0[2], p1[2], p2[2];
        uint8_t n;
        n = track->left_bev_step;
        p0[0] = track->left_bev[0][0];
        p0[1] = track->left_bev[0][1];
        p1[0] = track->left_bev[n / 2][0];
        p1[1] = track->left_bev[n / 2][1];
        p2[0] = track->left_bev[n - 1][0];
        p2[1] = track->left_bev[n - 1][1];
        curv_l = (float)pts_curvature_3pt(p0, p1, p2) / 1000.0f;
        cnt++;
    }

    if (track->right_bev_step > 10)
    {
        uint8_t p0[2], p1[2], p2[2];
        uint8_t n;
        n = track->right_bev_step;
        p0[0] = track->right_bev[0][0];
        p0[1] = track->right_bev[0][1];
        p1[0] = track->right_bev[n / 2][0];
        p1[1] = track->right_bev[n / 2][1];
        p2[0] = track->right_bev[n - 1][0];
        p2[1] = track->right_bev[n - 1][1];
        curv_r = (float)pts_curvature_3pt(p0, p1, p2) / 1000.0f;
        cnt++;
    }

    if (cnt == 0)
        return 0.0f;
    if (cnt == 1)
        return curv_l + curv_r; // one of them is 0
    return (curv_l + curv_r) / 2.0f;
}

/* ================================================================
 * 第 5 节 — 速度决策
 *
 * trail_speed_factor() — 曲率降速 + 视距降速, 取更保守值
 *   曲率 >0.05 → ×0.6,  >0.02 → ×0.8
 *   视距 <20  → ×0.4,  <40 → ×0.6,  <60 → ×0.8
 *   下限 0.3
 * ================================================================ */
float trail_speed_factor(void)
{
    float factor;
    float abs_curv;
    float vis_factor;
    uint8_t high;

    factor = 1.0f;

    // 曲率降速: 弯道越大速度越低
    abs_curv = pp_curvature;
    if (abs_curv < 0.0f)
        abs_curv = -abs_curv;
    if (abs_curv > 0.05f)
    {
        factor = 0.6f;
    }
    else if (abs_curv > 0.02f)
    {
        factor = 0.8f;
    }

    // 视距降速: 可见行越少速度越低
    high = pp_visible_high;
    vis_factor = 1.0f;
    if (high > 60)
        vis_factor = 1.0f;
    else if (high > 40)
        vis_factor = 0.8f;
    else if (high > 20)
        vis_factor = 0.6f;
    else
        vis_factor = 0.4f;

    // 取更保守的降速系数
    if (vis_factor < factor)
        factor = vis_factor;
    if (factor < 0.3f)
        factor = 0.3f;

    return factor;
}

/* ================================================================
 * 第 6 节 — 辅助工具函数
 *
 * clamp_center_to_target() — 限幅到 [0,255]
 * broken_flag_clear()      — 清零断桥累积状态
 * broken_judged()          — 累加行驶距离, 超过 BROKEN_LENTH 返回 1
 * find_mid_at_or_above()   — 从指定行向上找第一个有效中线值
 * average_lane_width()     — 指定行范围的平均道宽
 * detect_cross_break_row() — 从底部向上扫: 先宽后窄, 返回十字起始行
 * detect_cross_scene()     — 封装 detect_cross_break_row 为 bool
 * count_cross_rows()       — 统计下半图超宽行数 (宽度法十字辅助)
 * ================================================================ */

/* 统计下半图超宽行数 — 宽度法十字路口辅助判断 */
static uint8_t count_cross_rows(const vision_track_result_t *track)
{
    uint16_t y;
    uint8_t cross_cnt;
    int16_t l, r;
    uint16_t w;
    int16_t margin;

    cross_cnt = 0;
    margin = (int16_t)CROSS_TOUCH_MARGIN;

    for (y = (uint16_t)(MT9V034_HEIGHT / 2); y < MT9V034_HEIGHT; y++)
    {
        l = track->left[y];
        r = track->right[y];
        if (l < 0 || r < 0)
            continue;

        w = (uint16_t)(r - l + 1);
        if (w > (uint16_t)TRACK_WIDE_TH &&
            (l <= margin || r >= (int16_t)(MT9V034_WIDTH - 1 - margin)))
        {
            cross_cnt++;
        }
        else if (w > (uint16_t)(TRACK_WIDE_TH + TRACK_WIDE_TH / CROSS_WIDE_EXTRA_NUM))
        {
            cross_cnt++;
        }
    }

    return cross_cnt;
}

/* ================================================================
 * Helper utilities
 * ================================================================ */
static uint8_t clamp_center_to_target(int16_t center_x)
{
    if (center_x < 0)
        return 0;
    if (center_x > 255)
        return 255;
    return (uint8_t)center_x;
}

static uint16_t get_broken_progress(void)
{
    int16_t left_abs, right_abs;
    left_abs = encoder_data_dir[0];
    right_abs = encoder_data_dir[1];
    if (left_abs < 0)
        left_abs = -left_abs;
    if (right_abs < 0)
        right_abs = -right_abs;
    return (uint16_t)((left_abs + right_abs) / 2);
}

static void broken_flag_clear(void)
{
    broken_flag = 0;
    judge_distance = 0;
}

static uint8_t broken_judged(void)
{
    broken_flag = 1;
    judge_distance += get_broken_progress();
    if (judge_distance > BROKEN_LENTH)
        return 1;
    return 0;
}

static int16_t find_mid_at_or_above(uint16_t y_start)
{
    int16_t y;
    for (y = (int16_t)y_start; y >= 0; y--)
    {
        if (g_track.mid[(uint16_t)y] >= 0)
            return g_track.mid[(uint16_t)y];
    }
    return -1;
}

static int16_t average_lane_width(uint16_t y0, uint16_t y1)
{
    uint16_t y;
    long sum;
    uint16_t cnt;
    int16_t l, r;

    sum = 0;
    cnt = 0;

    if (y1 >= MT9V034_HEIGHT)
        y1 = MT9V034_HEIGHT - 1;

    for (y = y0; y <= y1; y++)
    {
        l = g_track.left[y];
        r = g_track.right[y];
        if (l >= 0 && r >= 0)
        {
            sum += (long)(r - l + 1);
            cnt++;
        }
    }

    if (cnt == 0)
        return (int16_t)(MT9V034_WIDTH / 3);
    return (int16_t)(sum / cnt);
}

static int16_t detect_cross_break_row(void)
{
    int16_t base_w;
    int16_t y;
    int16_t cross_start;
    uint8_t in_cross;
    uint8_t narrow_streak;
    int16_t l, r, w;
    int16_t margin;

    margin = (int16_t)CROSS_TOUCH_MARGIN;
    base_w = average_lane_width((uint16_t)(MT9V034_HEIGHT - 25),
                                (uint16_t)(MT9V034_HEIGHT - 5));
    if (base_w < 8)
        return -1;

    cross_start = -1;
    in_cross = 0;
    narrow_streak = 0;

    for (y = (int16_t)(MT9V034_HEIGHT - 4); y >= (int16_t)(MT9V034_HEIGHT / 4); y--)
    {
        l = g_track.left[(uint16_t)y];
        r = g_track.right[(uint16_t)y];
        if (l < 0 || r < 0)
            continue;

        w = r - l + 1;
        if (w > base_w + base_w / 5 ||
            (w > base_w + 12 &&
             (l <= margin || r >= (int16_t)(MT9V034_WIDTH - 1 - margin))))
        {
            if (!in_cross)
                in_cross = 1;
            cross_start = y;
            narrow_streak = 0;
        }
        else if (in_cross)
        {
            narrow_streak++;
            if (narrow_streak >= CROSS_MIN_STREAK)
                return cross_start;
        }
    }

    if (in_cross && cross_start >= 0)
        return cross_start;
    return -1;
}

static uint8_t detect_cross_scene(void)
{
    return (detect_cross_break_row() >= 0) ? 1 : 0;
}

/* ================================================================
 * 第 7 节 — 环岛检测 (逐行边界突变扫描)
 *
 * scan_ring_jump() 从近到远逐行扫描, 找一侧边界突然大幅跳变("刺入"),
 * 同时另一侧保持稳定, 跳变上方仍有路(中线居中)确认岛后通路。
 * 以此区分环岛(跳变后有路)和普通转弯/断头路(跳变后没路)。
 *
 * 检测逻辑:
 *   0. 从近行找第一个双边可见行 (允许近行丢线, 向上搜索最多 8 行)
 *   1. 积累稳定直道段: |dl|<3 且 |dr|<3 连续 >=5 行
 *   2. 检测单侧跳变: dl<-10(左) 或 dr>+10(右), 对侧 |变化|<3
 *      - 双边→单边丢线也算跳变 (环岛入口特征: 一侧边界突然刺入画面边缘)
 *   3. 跳变上方验证有路: >=3 行道路可见 + 中线估计在中心 +-25px 内
 *      - 允许单侧可见 (环岛入口上方只有一侧边界可见, 用半道宽估计中线)
 *
 * detect_ring()      — 有跳变 + 跳变后有路 → 返回 RING_l / RING_r
 * detect_ring_exit() — 无跳变 → 鼓出消失 → 返回 1 (出环岛)
 * ================================================================ */
#define RING_SUDDEN_TH      10   /* 边界突变下限: |dl/dr|>10 认为跳变 */
#define RING_SUDDEN_MAX     40   /* 边界突变上限: |dl/dr|>40 视为追踪伪影 */
#define RING_STABLE_TH       3   /* 稳定段 dl/dr 上限: |dl/dr|<3 认为平滑 */
#define RING_STABLE_MIN      5   /* 突变前最少稳定行数 */
#define RING_ROAD_AHEAD_MIN  3   /* 突变后最少有路行数 */
#define RING_SCAN_Y_NEAR     (MT9V034_HEIGHT - 8)    /* 扫描起点(近行) 112 */
#define RING_SCAN_Y_FAR      (MT9V034_HEIGHT / 5)    /* 扫描终点(远行) 24 */
#define RING_NEAR_SEARCH     8   /* 近行丢线时向上搜索双边行的最大行数 */

/* 逐行扫描找边界突变, 返回 0=无突变 1=左环岛 2=右环岛 */
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

/* 检测环岛入口: 有边界突变 + 突变后有路 → 环岛 */
static TRACK_ELEMENT detect_ring(void)
{
    uint8_t result;
    result = scan_ring_jump();
    if (result == 1) return RING_l;
    if (result == 2) return RING_r;
    return NONE;
}

/* 检测环岛出口: 边界突变消失 → 环岛结束 */
static uint8_t detect_ring_exit(void)
{
    return (scan_ring_jump() == 0) ? 1 : 0;
}
/* ================================================================
 * 第 8 节 — 行类型分类与分段合并
 *
 * 逐行计算 dl/dr/dw (边界变化量 + 宽度变化量), 将每行分为 7 种类型,
 * 合并连续同类型行为段, 用段序列代替双行固定行比较来识别元素。
 *
 * 三遍管线:
 *   row_classify_basic()  — 第一遍: 按边界存在性做基础分类
 *   row_classify_refine() — 第二遍: dl/dr/dw 状态机细化 (突变/超宽/发散)
 *   segment_merge()       — 第三遍: 连续同类型行合并为段, 相邻同类段再合并
 *
 * 行类型:
 *   -1 无效行    0 双边可见    1 左边界丢失   2 右边界丢失
 *    3 超宽(十字) 4 发散(断桥)  5 左边界突变   6 右边界突变
 *
 * 段序列 → 元素 (detect_element_segment):
 *   [0]           → STRAIGHT       直道
 *   [0, 3]        → CROSS          直道 → 超宽 = 十字路口
 *   [0, 1]        → RIGHT_ANGLE_r  左边界丢 → 路向右转
 *   [0, 2]        → RIGHT_ANGLE_l  右边界丢 → 路向左转
 *   [0, 5]        → STRAIGHT       突变 → 留给 detect_ring 确认环岛
 *   [0, 6]        → STRAIGHT       突变 → 留给 detect_ring 确认环岛
 *   [3] or [3,0]  → CROSS          超宽段 = 十字路口
 *   [4] or [0,4]  → BROKEN         发散段 = 断桥
 * ================================================================ */

/* 行类型常量 */
#define ROW_INVALID     (-1)
#define ROW_BOTH         0
#define ROW_LEFT_LOST    1
#define ROW_RIGHT_LOST   2
#define ROW_WIDE         3
#define ROW_DIVERGE      4
#define ROW_LEFT_JUMP    5
#define ROW_RIGHT_JUMP   6

/* 分段参数: 最小段长度=7行, 扫描范围 118→24 行 */
#define ROW_CLASSIFY_START  (MT9V034_HEIGHT - 2)   /* 118, 从底部倒数第二行开始 */
#define ROW_CLASSIFY_END    (MT9V034_HEIGHT / 5)   /* 24 */
#define SEGMENT_MIN_LEN     7
#define SEGMENT_MAX         12

/* 逐行类型 (xdata) */
static int8_t  g_row_flag[MT9V034_HEIGHT];

/* 分段信息 */
static int8_t  g_seg_type[SEGMENT_MAX];
static uint8_t g_seg_start[SEGMENT_MAX];  /* 远行(小行号) */
static uint8_t g_seg_end[SEGMENT_MAX];    /* 近行(大行号) */
static uint8_t g_seg_num;

/* ---------- 第一遍: 根据边界存在性做基础分类 ---------- */
static void row_classify_basic(void)
{
    uint16_t y;
    int16_t l, r;

    for (y = 0; y < MT9V034_HEIGHT; y++)
    {
        l = g_track.left[y];
        r = g_track.right[y];

        if (l < 0 || r < 0)
        {
            g_row_flag[y] = ROW_INVALID;
            continue;
        }

        if (l <= 2 && r >= (int16_t)(MT9V034_WIDTH - 4))
            g_row_flag[y] = ROW_WIDE;
        else if (l <= 2)
            g_row_flag[y] = ROW_LEFT_LOST;
        else if (r >= (int16_t)(MT9V034_WIDTH - 4))
            g_row_flag[y] = ROW_RIGHT_LOST;
        else
            g_row_flag[y] = ROW_BOTH;
    }
}

/* ---------- 第二遍: dl/dr/dw 细化分类 (突变检测 + 发散检测) ---------- */
static void row_classify_refine(void)
{
    uint16_t y;
    int16_t l_cur, r_cur, l_prev, r_prev;
    int16_t dl, dr, dw, w_cur, w_prev;
    int16_t w_min;
    uint8_t flag_sud;
    int8_t prev_flag;

    w_min = 65;
    flag_sud = 0;

    l_prev = g_track.left[(uint16_t)ROW_CLASSIFY_START + 1];
    r_prev = g_track.right[(uint16_t)ROW_CLASSIFY_START + 1];

    for (y = (uint16_t)ROW_CLASSIFY_START; y > (uint16_t)ROW_CLASSIFY_END; y--)
    {
        if (g_row_flag[y] == ROW_INVALID)
            continue;

        l_cur = g_track.left[y];
        r_cur = g_track.right[y];

        if (l_prev <= 2 || r_prev >= (int16_t)(MT9V034_WIDTH - 4))
        {
            l_prev = l_cur;
            r_prev = r_cur;
            continue;
        }

        w_cur = r_cur - l_cur + 1;
        w_prev = r_prev - l_prev + 1;

        if (w_cur < w_min && y > 10)
            w_min = w_cur;
        else if (y % 2 == 0)
            w_min -= 1;

        dw = w_cur - w_prev;
        dl = l_cur - l_prev;
        dr = r_cur - r_prev;
        prev_flag = g_row_flag[y];

        /* 十字: 宽度暴涨 + 两边到边界 */
        if ((dw > 20 && dl < -10 && dr > 3) ||
            (dw > 20 && dl < -3 && dr > 10))
        {
            g_row_flag[y] = ROW_WIDE;
            flag_sud = 3;
        }
        /* 延续十字 */
        else if (prev_flag == ROW_WIDE ||
                 (prev_flag == ROW_LEFT_LOST && dr > 10 && flag_sud == 0) ||
                 (prev_flag == ROW_RIGHT_LOST && dl < -10 && flag_sud == 0))
        {
            g_row_flag[y] = ROW_WIDE;
            flag_sud = 3;
        }
        /* 左边界突变: dl < -10, 右稳定 */
        else if (dl < -10 && dr < 3 && flag_sud == 0)
        {
            g_row_flag[y] = ROW_LEFT_JUMP;
            flag_sud = 5;
        }
        /* 右边界突变: dr > 10, 左稳定 */
        else if (dr > 10 && dl > -3 && flag_sud == 0)
        {
            g_row_flag[y] = ROW_RIGHT_JUMP;
            flag_sud = 6;
        }
        /* 延续左突变 */
        else if (flag_sud == 5 && dl < 5 && dl > -5 && dr < 3 && w_cur > w_min)
        {
            g_row_flag[y] = ROW_LEFT_JUMP;
        }
        /* 延续右突变 */
        else if (flag_sud == 6 && dr < 5 && dr > -5 && dl > -3 && w_cur > w_min)
        {
            g_row_flag[y] = ROW_RIGHT_JUMP;
        }
        /* 左突变转十字 */
        else if (flag_sud == 5 && dl < 3 && dl > -3 && dr >= 3)
        {
            g_row_flag[y] = ROW_WIDE;
            flag_sud = 3;
        }
        /* 右突变转十字 */
        else if (flag_sud == 6 && dr < 3 && dr > -3 && dl <= -3)
        {
            g_row_flag[y] = ROW_WIDE;
            flag_sud = 3;
        }
        /* 十字内稳定 */
        else if (flag_sud == 3 && dr < 10 && dr > -10 &&
                 dl < 10 && dl > -10 && w_cur > w_min)
        {
            g_row_flag[y] = ROW_WIDE;
        }
        /* 十字结束 */
        else if (flag_sud == 3 &&
                 (dr < -10 || dl > 10 || w_cur < w_min) &&
                 g_row_flag[y] == ROW_BOTH)
        {
            flag_sud = 0;
        }
        /* 边界发散: dw>0 但 dl/dr 很小 → 断桥 */
        else if (dl <= 0 && dl >= -10 && dr >= 0 && dr <= 10 &&
                 flag_sud == 0 && dw > 0)
        {
            g_row_flag[y] = ROW_DIVERGE;
        }

        l_prev = l_cur;
        r_prev = r_cur;
    }

    /* 滤波: 消除孤立单行误分类 */
    {
        uint16_t fy;
        for (fy = (uint16_t)(ROW_CLASSIFY_START - 1); fy > (uint16_t)ROW_CLASSIFY_END; fy--)
        {
            if (g_row_flag[fy - 1] == g_row_flag[fy + 1] &&
                g_row_flag[fy - 2] == g_row_flag[fy + 1] &&
                g_row_flag[fy] != g_row_flag[fy + 1])
            {
                g_row_flag[fy] = g_row_flag[fy + 1];
            }
        }
    }
}

/* ---------- 分段合并: 连续同类型行 → 段 ---------- */
static void segment_merge(void)
{
    uint16_t y;
    int8_t cur_type;
    uint8_t seg_cnt;
    uint8_t cnt;

    seg_cnt = 0;
    cur_type = g_row_flag[(uint16_t)ROW_CLASSIFY_START];
    cnt = 1;

    for (y = (uint16_t)(ROW_CLASSIFY_START - 1); y > (uint16_t)ROW_CLASSIFY_END; y--)
    {
        if (cur_type == g_row_flag[y])
        {
            cnt++;
        }
        else
        {
            if (cnt >= SEGMENT_MIN_LEN)
            {
                g_seg_type[seg_cnt] = cur_type;
                g_seg_start[seg_cnt] = (uint8_t)(y + cnt);
                g_seg_end[seg_cnt] = (uint8_t)(y + 1);
                seg_cnt++;
                if (seg_cnt >= SEGMENT_MAX)
                    break;
            }
            cur_type = g_row_flag[y];
            cnt = 1;
        }
    }

    if (cnt >= SEGMENT_MIN_LEN && seg_cnt < SEGMENT_MAX)
    {
        g_seg_type[seg_cnt] = cur_type;
        g_seg_start[seg_cnt] = (uint8_t)(y + cnt);
        g_seg_end[seg_cnt] = (uint8_t)(y + 1);
        seg_cnt++;
    }

    g_seg_num = seg_cnt;

    /* 合并相邻同类段 */
    {
        uint8_t mi, si;
        mi = 1;
        for (si = 1; si < g_seg_num; si++)
        {
            if (g_seg_type[si] == g_seg_type[mi - 1])
                g_seg_end[mi - 1] = g_seg_end[si];
            else
            {
                g_seg_type[mi] = g_seg_type[si];
                g_seg_start[mi] = g_seg_start[si];
                g_seg_end[mi] = g_seg_end[si];
                mi++;
            }
        }
        g_seg_num = mi;
    }
}

/* ---------- 基于分段的元素检测 ---------- */
static TRACK_ELEMENT detect_element_segment(void)
{
    int8_t s0, s1;
    uint8_t n;
    int16_t l_near, r_near, l_far, r_far;
    uint16_t near_y, far_y;
    uint8_t near_left_ok, near_right_ok;
    uint8_t far_left_ok, far_right_ok;
    int16_t c_near, c_far, dx;

    row_classify_basic();
    row_classify_refine();
    segment_merge();

    n = g_seg_num;

    if (n == 0)
        return BROKEN;

    s0 = g_seg_type[0];
    s1 = (n >= 2) ? g_seg_type[1] : ROW_INVALID;

    /* 段0=双边正常 → 看段1 */
    if (s0 == ROW_BOTH)
    {
        if (s1 == ROW_WIDE)
            return CROSS;
        if (s1 == ROW_LEFT_JUMP || s1 == ROW_RIGHT_JUMP)
            return STRAIGHT;  /* 突变 → 由 detect_ring 确认 */
        if (s1 == ROW_LEFT_LOST)
            return RIGHT_ANGLE_l;
        if (s1 == ROW_RIGHT_LOST)
            return RIGHT_ANGLE_r;
        if (s1 == ROW_DIVERGE)
            return BROKEN;
        /* s1 不显著 → 落到双行比较确认 (平滑弯道分段看不出) */
    }
    else if (s0 == ROW_WIDE)
        return CROSS;
    else if (s0 == ROW_LEFT_LOST)
        return RIGHT_ANGLE_l;
    else if (s0 == ROW_RIGHT_LOST)
        return RIGHT_ANGLE_r;
    else if (s0 == ROW_DIVERGE)
        return BROKEN;
    else if (s0 == ROW_LEFT_JUMP || s0 == ROW_RIGHT_JUMP)
        return STRAIGHT;  /* 突变 → 让 detect_ring 处理 */

    /* ---- 双行比较 (分段无法判定时) ---- */
    near_y = (uint16_t)(MT9V034_HEIGHT - 20);
    far_y = (uint16_t)VISION_LOOKAHEAD_Y;

    l_near = g_track.left[near_y];
    r_near = g_track.right[near_y];
    l_far = g_track.left[far_y];
    r_far = g_track.right[far_y];

    if (l_near < 0 || r_near < 0 || l_far < 0 || r_far < 0)
        return BROKEN;

    near_left_ok = (l_near > 2) ? 1 : 0;
    near_right_ok = (r_near < (int16_t)(MT9V034_WIDTH - 4)) ? 1 : 0;
    far_left_ok = (l_far > 2) ? 1 : 0;
    far_right_ok = (r_far < (int16_t)(MT9V034_WIDTH - 4)) ? 1 : 0;

    if (!near_left_ok && !near_right_ok)
        return BROKEN;

    if (near_left_ok && near_right_ok && far_left_ok && far_right_ok)
    {
        if ((l_near - l_far) > 8 && (r_far - r_near) > 8)
            return CROSS;
    }

    if (near_left_ok && near_right_ok)
    {
        if (far_left_ok && !far_right_ok)
        {
            if (l_far > 15)
                return RIGHT_ANGLE_r;
        }
        if (!far_left_ok && far_right_ok)
        {
            if (r_far < (int16_t)(MT9V034_WIDTH - 15))
                return RIGHT_ANGLE_l;
        }
        if (far_left_ok && far_right_ok)
        {
            c_near = (l_near + r_near) / 2;
            c_far = (l_far + r_far) / 2;
            dx = c_far - c_near;
            if (dx > 4)  return RIGHT_ANGLE_r;
            if (dx < -4) return RIGHT_ANGLE_l;
        }
    }
    else if (near_left_ok && far_left_ok)
    {
        dx = l_far - l_near;
        if (dx > 6)  return RIGHT_ANGLE_r;
        if (dx < -6) return RIGHT_ANGLE_l;
    }
    else if (near_right_ok && far_right_ok)
    {
        dx = r_far - r_near;
        if (dx > 6)  return RIGHT_ANGLE_r;
        if (dx < -6) return RIGHT_ANGLE_l;
    }

    return STRAIGHT;
}

/* ================================================================
 * 第 9 节 — 元素检测主逻辑
 *
 * track_element_judge()    — 主入口: 环岛退出 → 分段检测 → 环岛确认 → 十字回退
 * detect_element_segment() — 行分类 + 分段合并 + 段序列 → 元素
 * ================================================================ */

/* 主分类入口: 环岛退出 → 分段检测 → 环岛确认 → 十字回退 */
TRACK_ELEMENT track_element_judge(void)
{
    TRACK_ELEMENT seg_elem;

    if (!g_track_valid)
        return NONE;

    /* 视觉层特征标志 */
    if (g_track.feature == VISION_FEATURE_LOST)
        return BROKEN;

    /* 出环岛: 当前在环岛状态, 边界鼓出消失 → 环岛结束 */
    if (g_track_fsm.state == RING_l || g_track_fsm.state == RING_r)
    {
        if (detect_ring_exit())
            return STRAIGHT;
    }

    /* 基于分段的中点偏移分类 (主要) */
    seg_elem = detect_element_segment();

    /* 进环岛: segment 像转弯, 但路前面还在 + 一侧边界鼓出 → 环岛入口 */
    if (seg_elem == STRAIGHT || seg_elem == RIGHT_ANGLE_l || seg_elem == RIGHT_ANGLE_r)
    {
        TRACK_ELEMENT ring_elem;
        ring_elem = detect_ring();
        if (ring_elem != NONE)
            return ring_elem;
    }

    if (seg_elem != STRAIGHT)
        return seg_elem;

    /* 回退: 宽度法十字检测 (不再盲信视觉层 VISION_FEATURE_CROSS, 宽弯道会误触发) */
    if (detect_cross_scene())
        return CROSS;

    return STRAIGHT;
}

/* ================================================================
 * 第 10 节 — 目标规划
 *
 * plan_straight_center() — 直道: 近远加权 (near + far×2)/3, 偏好远点 67%
 * plan_turn_center()     — 弯道: 道路中心估计 + 内侧偏置
 *   - 双边可见 → (L+R)/2
 *   - 单边丢线 → 可见边 ± 半道宽
 *   - 十字路口 → CENTER_POINT
 * plan_pure_pursuit()    — 纯追踪: 中线点集 → 前瞻转向角
 * ================================================================ */

/* 直道: 近行(98)+远行(60)加权, 远行权重 67% */
static uint8_t plan_straight_center(void)
{
    int16_t near_mid, far_mid, target;

    near_mid = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_NEAR);
    far_mid = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_FAR);
    if (near_mid >= 0 && far_mid >= 0)
    {
        target = (int16_t)((near_mid + far_mid * 2) / 3);
        return clamp_center_to_target(target);
    }
    if (g_track.center_x >= 0)
        return clamp_center_to_target(g_track.center_x);
    return track_midpoint_target_P;
}
static uint8_t plan_turn_center(TRACK_ELEMENT turn_type)
{
    int16_t l_far, r_far;
    int16_t target;
    int16_t lane_w;
    int16_t near_y;
    uint16_t far_y;
    uint8_t far_left_ok, far_right_ok;

    far_y = (uint16_t)VISION_LOOKAHEAD_Y;
    l_far = g_track.left[far_y];
    r_far = g_track.right[far_y];

    far_left_ok  = (l_far > 2) ? 1 : 0;
    far_right_ok = (r_far < (int16_t)(MT9V034_WIDTH - 4)) ? 1 : 0;

    /* 双边丢线: 保持上一帧目标 */
    if (!far_left_ok && !far_right_ok)
    {
        return track_midpoint_target_P;
    }

    /* 从近行取道宽 */
    near_y = (int16_t)(MT9V034_HEIGHT - 18);
    {
        int16_t l_near, r_near;
        l_near = g_track.left[near_y];
        r_near = g_track.right[near_y];
        if (l_near > 2 && r_near < (int16_t)(MT9V034_WIDTH - 4))
        {
            lane_w = r_near - l_near + 1;
        }
        else
        {
            lane_w = 65;
        }
    }
    /* TODO: 道宽范围, 根据实际赛道在图像中的像素宽调整 (兜底值=65) */
    if (lane_w < 25) lane_w = 65;
    if (lane_w > 160) lane_w = 160;

    /* 十字路口: 双边都在边界 → 保持中心 */
    if (l_far <= 5 && r_far >= (int16_t)(MT9V034_WIDTH - 5))
    {
        target = CENTER_POINT;
    }
    /* 双边可见: 标准 (L+R)/2 */
    else if (far_left_ok && far_right_ok)
    {
        target = (l_far + r_far) / 2;
    }
    /* 右边界丢线: 道路中心 = 左边界 + 半道宽 */
    else if (far_left_ok && !far_right_ok)
    {
        target = l_far + lane_w / 2;
    }
    /* 左边界丢线: 道路中心 = 右边界 - 半道宽 */
    else /* !far_left_ok && far_right_ok */
    {
        target = r_far - lane_w / 2;
    }

    /* 向弯道内侧偏移, 增大切入力度 */
    if (turn_type == RIGHT_ANGLE_r)
        target += (int16_t)TRACK_TURN_BIAS;
    else if (turn_type == RIGHT_ANGLE_l)
        target -= (int16_t)TRACK_TURN_BIAS;

    return clamp_center_to_target(target);
}


/* 纯追踪: 速度 → 前瞻距离 → 中线点集最近点 → 转向角 */
static void plan_pure_pursuit(float current_speed)
{
    float lp;

    lp = (current_speed > 5.0f) ? (current_speed / (float)PP_LOOKAHEAD_SCALE) : (float)PP_LOOKAHEAD_MIN;
    if (lp < (float)PP_LOOKAHEAD_MIN)
        lp = (float)PP_LOOKAHEAD_MIN;
    if (lp > (float)PP_LOOKAHEAD_MAX)
        lp = (float)PP_LOOKAHEAD_MAX;

    pp_lookahead_dist = lp;
    pp_steering_angle = pure_pursuit_angle(&g_track, lp);
}

void track_straight_target(uint8_t position)
{
    (void)position;
    straight_target = plan_straight_center();
    track_midpoint_target = straight_target;
}

/* ================================================================
 * 第 11 节 — VOFA+ Firewater 遥测 (CDC 发送 10 个 float)
 * ================================================================ */
#if VOFA_FIREWATER

typedef union
{
    float f;
    uint8_t b[4];
} float_bytes_t;

static void vofa_send_firewater(void)
{
    uint8_t buf[VOFA_FLOAT_COUNT * 4 + 4];
    float fvals[VOFA_FLOAT_COUNT];
    uint8_t i;
    float_bytes_t fb;

    // 打包遥测浮点数
    fvals[0] = pp_steering_angle;
    fvals[1] = (float)g_track.center_x;
    fvals[2] = (float)g_track.error_x;
    fvals[3] = pp_curvature;
    fvals[4] = (float)g_track.visible_high;
    fvals[5] = (float)g_track.lane_width;
    fvals[6] = (float)g_track.left_bev_step;
    fvals[7] = (float)g_track.right_bev_step;
    fvals[8] = (float)g_track.mid_step;
    fvals[9] = (float)track_element;

    for (i = 0; i < VOFA_FLOAT_COUNT; i++)
    {
        fb.f = fvals[i];
        buf[i * 4 + 0] = fb.b[0];
        buf[i * 4 + 1] = fb.b[1];
        buf[i * 4 + 2] = fb.b[2];
        buf[i * 4 + 3] = fb.b[3];
    }

    // Firewater 帧尾: 0x00 0x00 0x80 0x7F
    buf[VOFA_FLOAT_COUNT * 4 + 0] = 0x00;
    buf[VOFA_FLOAT_COUNT * 4 + 1] = 0x00;
    buf[VOFA_FLOAT_COUNT * 4 + 2] = 0x80;
    buf[VOFA_FLOAT_COUNT * 4 + 3] = 0x7F;

    usb_cdc_send_buffer(buf, sizeof(buf));
}

#endif // VOFA_FIREWATER

static void report_track_element_if_changed(void)
{
    // 正常运行时关闭调试输出
}

/* ================================================================
 * 第 12 节 — FSM 状态切换回调
 *
 * trail_fsm_on_entry() — 进入新状态: 清零积分 → 锁定航向 → 状态保持 → 环岛初始化
 * trail_fsm_on_exit()  — 退出旧状态 (预留)
 * ================================================================ */
static void trail_fsm_on_entry(TRACK_ELEMENT state)
{
    /* 切换元素时清零积分, 防止上一段积分值在新Ki下产生跳变 */
    pid_pos.integral = 0.0f;
    pid_gyro.integral = 0.0f;

    /* 锁定航向: 直道保持姿态, 断桥保持冲出方向 */
    if (state == STRAIGHT || state == BROKEN_RODE)
    {
        gyro_target = yaw;
    }
    if (state == CROSS)
    {
        g_track_fsm.state_hold = 3;
    }
    /* TODO: 防切回保护帧数, 配合debounce. 切回太快→加大(8~12), 出弯太慢→减小(3~5) */
    if (state == RIGHT_ANGLE_l || state == RIGHT_ANGLE_r)
    {
        g_track_fsm.state_hold = 6;
    }
    if (state == STRAIGHT)
    {
        broken_flag_clear();
    }
    /* 环岛: 清零断桥累积 + 启动陀螺仪积分追踪转角 */
    if (state == RING_l || state == RING_r || state == RING_c)
    {
        broken_flag_clear();
        cnt_degree = 0;
        ring_start_yaw = yaw;
    }
}

static void trail_fsm_on_exit(TRACK_ELEMENT state)
{
    (void)state;
}

/* ================================================================
 * 第 13 节 — 主处理入口
 *
 * track_handle() 每帧调用, 执行完整管线:
 *   1. vision_poll_track()  — 等待新帧 + 运行 vision_track_process
 *   2. track_element_judge() → 元素分类
 *   3. 纯追踪 + 曲率计算 (供速度决策)
 *   4. 断桥升级 (累积距离 → BROKEN_RODE)
 *   5. track_fsm_update()    → 滞回滤波
 *   6. 目标规划 (按 FSM plan 策略委派)
 *   7. 环岛偏置叠加
 *   8. 跳变限幅 ±12px + EMA 平滑
 *   9. VOFA 遥测发送
 * ================================================================ */
void track_handle(void)
{
    static uint8_t fsm_inited = 0;
    TRACK_ELEMENT raw_elem;
    track_plan_t plan;
    int16_t break_row;
    uint8_t cross_cnt;
    float speed_est;
    int16_t jump;
    uint8_t new_target;
    float ema_alpha;

    if (!fsm_inited)
    {
        track_fsm_init(&g_track_fsm);
        track_fsm_set_callbacks(&g_track_fsm, trail_fsm_on_entry, trail_fsm_on_exit);
        fsm_inited = 1;
    }

    vision_poll_track();
    if (!g_track_valid)
    {
        track_element = NONE;
        current_element = NONE;
        return;
    }

    track_element_P = track_element;
    track_midpoint_target_P = track_midpoint_target;
    current_element = track_element_judge();
    raw_elem = current_element;
    cross_cnt = count_cross_rows(&g_track);
    break_row = detect_cross_break_row();

    // 计算纯追踪与曲率 (供速度决策)
    speed_est = 45.0f;
    plan_pure_pursuit(speed_est);
    pp_curvature = compute_road_curvature(&g_track);
    pp_visible_high = g_track.visible_high;

    // 断桥升级: 累积行驶距离超过阈值 → 进入断桥后阶段
    if (raw_elem == BROKEN)
    {
        if (broken_judged())
            raw_elem = BROKEN_RODE;
    }

    track_fsm_update(&g_track_fsm, raw_elem);
    track_element = g_track_fsm.state;

    // 目标规划 — 按 FSM 规划策略委派
    plan = track_fsm_get_plan(&g_track_fsm);
    new_target = track_midpoint_target_P;

    if (plan == PLAN_STRAIGHT)
    {
        new_target = plan_straight_center();
    }
    else if (plan == PLAN_TURN_LEFT)
    {
        new_target = plan_turn_center(RIGHT_ANGLE_l);
    }
    else if (plan == PLAN_TURN_RIGHT)
    {
        new_target = plan_turn_center(RIGHT_ANGLE_r);
    }
    else if (plan == PLAN_CROSS)
    {
        if (g_track.center_x >= 0)
            new_target = clamp_center_to_target(g_track.center_x);
        else
            new_target = CENTER_POINT;
    }
    /* PLAN_HOLD 和 PLAN_BROKEN: 保持上一帧目标 */

    /* 环岛偏置: 左环岛向左偏(绕岛外侧), 右环岛向右偏 */
    if (track_element == RING_l)
        new_target = clamp_center_to_target((int16_t)new_target + (int16_t)RING_BIAS);
    else if (track_element == RING_r)
        new_target = clamp_center_to_target((int16_t)new_target - (int16_t)RING_BIAS);

    // 后处理: 跳变限幅 ±12px + 逐状态 EMA 平滑
    if (track_element != BROKEN_RODE && track_element != NONE &&
        track_element != RIGHT_ANGLE_l && track_element != RIGHT_ANGLE_r)
    {
        jump = (int16_t)new_target - (int16_t)track_midpoint_target_P;
        if (jump > 12)
            new_target = (uint8_t)((int16_t)track_midpoint_target_P + 12);
        else if (jump < -12)
            new_target = (uint8_t)((int16_t)track_midpoint_target_P - 12);

        ema_alpha = track_fsm_get_ema_alpha(&g_track_fsm);
        {
            float tf;
            tf = (float)new_target * ema_alpha + (float)track_midpoint_target_P * (1.0f - ema_alpha);
            track_midpoint_target = (uint8_t)(tf + 0.5f);
        }
    }
    else
    {
        track_midpoint_target = new_target;
    }

#if TRAIL_DBG_PRINTF
    printf("DBG feature:%d cross_cnt:%u break_row:%d valid_rows:%u center_x:%d element:%s target:%u pp_ang:%.1f\r\n",
           g_track.feature,
           cross_cnt,
           break_row,
           g_track.valid_rows,
           g_track.center_x,
           track_element_name(track_element),
           track_midpoint_target,
           pp_steering_angle);
#endif

#if VOFA_FIREWATER
    vofa_send_firewater();
#endif

    report_track_element_if_changed();
}

void state_display(void)
{
    printf("track:%s center:%u err:%d feature:%d valid:%u\r\n",
           track_element_name(track_element),
           track_midpoint_target,
           g_track.error_x,
           g_track.feature,
           g_track.valid_rows);
}

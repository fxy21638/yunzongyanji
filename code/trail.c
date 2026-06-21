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
//   - 环岛检测: 委托 ring_fsm (段分叉+边界突变, 条件1+条件2同时验证)
//   - 行分类 + 分段合并: 7 种行类型 → 段序列 → 元素识别
//   - 目标规划: 直道(近远加权) / 弯道(道路中心估计+偏置) / 十字(图像中心) / 环岛(ring_fsm)
// ====================================================================

#ifndef __INTELLISENSE__
#include "ky_headfile.h"
#endif

#include "trail.h"
#include "main.h"
#include "track_fsm.h"
#include "ring_fsm.h"

extern uint8_t xdata mt9v034_image[MT9V034_HEIGHT][MT9V034_WIDTH];

/* ================================================================
 * 第 1 节 — 常量定义
 * ================================================================ */

/* 目标规划参数 */
#define TRACK_LOOKAHEAD_Y_NEAR (MT9V034_HEIGHT - 22) /* 直道近点行: 98 */
#define TRACK_LOOKAHEAD_Y_FAR (MT9V034_HEIGHT / 2)   /* 直道远点行: 60 (权重 67%) */
#define TRACK_EDGE_NEAR_TH 3
#define TRACK_WIDE_TH (MT9V034_WIDTH * 7 / 10)

/* 调试开关 */
#define TRAIL_DBG_PRINTF 1

/* 弯道/十字检测参数 */
#define TRACK_MIN_VALID_TURN_ROWS 8
#define CROSS_MIN_STREAK 3
#define CROSS_TOUCH_MARGIN 4
#define CROSS_WIDE_EXTRA_NUM 5

/* 转弯目标偏置: 向弯道内侧偏移, 道宽的 1/8 (原固定 6px 太小) */
#define TRACK_TURN_BIAS_RATIO 8

/* 纯追踪参数 */
#define PP_LOOKAHEAD_MIN 12  /* 最短前瞻距离 (像素) */
#define PP_LOOKAHEAD_MAX 70  /* 最长前瞻距离 (像素) */
#define PP_LOOKAHEAD_SCALE 4 /* 前瞻 = 速度 / SCALE */

/* VOFA+ Firewater 遥测 (通过 CDC 发送 10 个 float) */
#define VOFA_FIREWATER 0
#if VOFA_FIREWATER
#define VOFA_FLOAT_COUNT 10
#endif

/* ================================================================
 * 第 2 节 — 全局状态
 * ================================================================ */

uint8_t white_count = 0;

uint8_t white_segments[20] = {0};
uint8_t time_search = 0;

/* 元素分类结果 (FSM 滤波后) */
TRACK_ELEMENT track_element = NONE;
TRACK_ELEMENT track_element_P = NONE; /* 上一帧 */
TRACK_ELEMENT current_element = NONE; /* 原始分类 (未滤波) */
uint8_t track_midpoint_target = CENTER_POINT;
uint8_t track_midpoint_target_P = CENTER_POINT;

/* 纯追踪输出 (供 control.c 使用) */
float pp_steering_angle = 0.0f;  /* 转向角 (度), 正值右转 */
float pp_lookahead_dist = 25.0f; /* 当前前瞻距离 (像素) */
float pp_curvature = 0.0f;       /* 赛道曲率估计 (×1000) */
uint8_t pp_visible_high = 120;   /* 可见赛道行数 */

/* 靶子检测 (独立于赛道元素) */
uint8_t g_target_detected = 0;  /* 当前帧检测到靶子 */
uint8_t g_target_center_x = 94; /* 靶心 x 坐标 */
uint8_t g_target_radius = 30;   /* 靶环内径的一半 */
uint8_t g_target_y_mid = 60;    /* 靶心所在行 y */

/* 障碍检测 (独立于赛道元素, 与靶子并行) */
uint8_t g_obstacle_detected = 0;
uint8_t g_obstacle_center_x = 94;
uint8_t g_obstacle_width = 30;
uint8_t g_obstacle_y_mid = 60;
uint8_t g_obstacle_left_edge = 0;
uint8_t g_obstacle_right_edge = 0;

/* 出界检测 (调试专用): 摄像头全黑 → 停车 */
uint8_t g_out_of_bounds = 0;
static uint8_t s_oob_cnt = 0;
#define OOB_WHITE_THRESHOLD  15   /* 采样白点数低于此值判定全黑 */
#define OOB_DEBOUNCE          5   /* 连续全黑帧数确认出界 */

/* 断桥状态 */
uint8_t start_stage = 0;
uint8_t broken_flag = 0;
int32_t judge_distance = 0; /* 断桥累计行驶距离 */

/* ================================================================
 * 第 2.5 节 — 出界检测 (调试专用)
 *
 * 采样二值图白像素数: 低于阈值 → 判定摄像头全黑/赛道完全丢失 → 停车
 * image_data: 赛道=0(黑), 背景=255(白), 尺寸 188×120 (已翻转)
 * 采样步长 4 → ~1410 个采样点, 白点数 <15 即全黑
 * ================================================================ */

extern image_t image_data[];

static void check_out_of_bounds(void)
{
    uint16_t i, j;
    uint16_t white_cnt;
    uint16_t row_off;

    if (g_out_of_bounds)
        return;

    white_cnt = 0;
    for (i = 0; i < (uint16_t)MT9V034_HEIGHT; i += 4)
    {
        row_off = i * (uint16_t)MT9V034_WIDTH;
        for (j = 0; j < (uint16_t)MT9V034_WIDTH; j += 4)
        {
            if (image_data[row_off + j] == 0)   /* 0=赛道(白), 255=背景(黑) */
                white_cnt++;
        }
    }

    if (white_cnt < OOB_WHITE_THRESHOLD)
    {
        s_oob_cnt++;
        if (s_oob_cnt >= OOB_DEBOUNCE)
            g_out_of_bounds = 1;
    }
    else
    {
        s_oob_cnt = 0;
    }
}

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
uint8_t clamp_center_to_target(int16_t center_x)
{
    if (center_x < 0)
        return 0;
    if (center_x > 255)
        return 255;
    return (uint8_t)center_x;
}

/* [本次比赛无断桥, 辅助函数已注释]
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
*/

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
 * 第 8 节 — 行类型分类与分段合并
 *
 * 逐行计算 dl/dr/dw (边界变化量 + 宽度变化量), 将每行分为 7 种类型,
 * 合并连续同类型行为段, 用段序列代替双行固定行比较来识别元素。
 *
 * 两遍管线:
 *   row_classify_refine() — 第一遍: 基础分类内联 + dl/dr/dw 状态机细化 (突变/超宽)
 *   segment_merge()       — 第二遍: 连续同类型行合并为段, 相邻同类段再合并
 *
 * 行类型:
 *   -1 无效行    0 双边可见    1 左边界丢失   2 右边界丢失
 *    3 超宽(十字) 4 发散(断桥)  5 左边界突变   6 右边界突变
 *
 * 段序列 → 元素 (detect_element_segment):
 *   [0]           → STRAIGHT       直道
 *   [0, 3]        → CROSS          直道 → 超宽 = 十字路口
 *   [0, 1]        → RIGHT_ANGLE_l  左边界丢 → 路向左转
 *   [0, 2]        → RIGHT_ANGLE_r  右边界丢 → 路向右转
 *   [0, 5]        → STRAIGHT       突变 → 留给 detect_ring 确认环岛
 *   [0, 6]        → STRAIGHT       突变 → 留给 detect_ring 确认环岛
 *   [3] or [3,0]  → CROSS          超宽段 = 十字路口
 *   [4] or [0,4]  → BROKEN         发散段 = 断桥
 * ================================================================ */

/* 行类型常量 */
#define ROW_INVALID (-1)
#define ROW_BOTH 0
#define ROW_LEFT_LOST 1
#define ROW_RIGHT_LOST 2
#define ROW_WIDE 3
#define ROW_DIVERGE 4
#define ROW_LEFT_JUMP 5
#define ROW_RIGHT_JUMP 6

/* 分段参数: 最小段长度=7行, 扫描范围 118→24 行 */
#define ROW_CLASSIFY_START (MT9V034_HEIGHT - 2) /* 118, 从底部倒数第二行开始 */
#define ROW_CLASSIFY_END (MT9V034_HEIGHT / 5)   /* 24 */
#define SEGMENT_MIN_LEN 7

/* 逐行类型 (xdata) */
static int8_t g_row_flag[MT9V034_HEIGHT];

/* 分段信息 (非 static: 供 ring_fsm.c 读取) */
int8_t g_seg_type[SEGMENT_MAX];
uint8_t g_seg_start[SEGMENT_MAX];
uint8_t g_seg_end[SEGMENT_MAX];
uint8_t g_seg_num;

/* ---------- 单遍: 基础分类 + dl/dr/dw 细化 (合并原 row_classify_basic + row_classify_refine) ---------- */
static void row_classify_refine(void)
{
    uint16_t y;
    int16_t l_cur, r_cur, l_prev, r_prev;
    int16_t dl, dr, dw, w_cur, w_prev;
    int16_t w_min;
    uint8_t flag_sud;
    int8_t basic_type;

    w_min = 65;
    flag_sud = 0;

    l_prev = g_track.left[(uint16_t)ROW_CLASSIFY_START + 1];
    r_prev = g_track.right[(uint16_t)ROW_CLASSIFY_START + 1];

    for (y = (uint16_t)ROW_CLASSIFY_START; y > (uint16_t)ROW_CLASSIFY_END; y--)
    {
        l_cur = g_track.left[y];
        r_cur = g_track.right[y];

        /* ---- 内联基础分类 (原 row_classify_basic) ---- */
        if (l_cur < 0 || r_cur < 0)
        {
            g_row_flag[y] = ROW_INVALID;
            l_prev = l_cur;
            r_prev = r_cur;
            continue;
        }

        if (l_cur <= 2 && r_cur >= (int16_t)(MT9V034_WIDTH - 4))
            basic_type = ROW_WIDE;
        else if (l_cur <= 2)
            basic_type = ROW_LEFT_LOST;
        else if (r_cur >= (int16_t)(MT9V034_WIDTH - 4))
            basic_type = ROW_RIGHT_LOST;
        else
            basic_type = ROW_BOTH;
        g_row_flag[y] = basic_type;

        /* ---- 跳变/增量检测: 当前和上一行都必须是双边 ---- */
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

        /* 十字: 宽度暴涨 + 两边到边界 */
        if ((dw > 20 && dl < -10 && dr > 3) ||
            (dw > 20 && dl < -3 && dr > 10))
        {
            g_row_flag[y] = ROW_WIDE;
            flag_sud = 3;
        }
        /* 延续十字 */
        else if (basic_type == ROW_WIDE ||
                 (basic_type == ROW_LEFT_LOST && dr > 10 && flag_sud == 0) ||
                 (basic_type == ROW_RIGHT_LOST && dl < -10 && flag_sud == 0))
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
                 basic_type == ROW_BOTH)
        {
            flag_sud = 0;
        }
        /* 边界发散: dw>0 但 dl/dr 很小 → 断桥 [本次比赛无断桥, 已注释] */
        /*
        else if (dl <= 0 && dl >= -10 && dr >= 0 && dr <= 10 &&
                 flag_sud == 0 && dw > 0)
        {
            g_row_flag[y] = ROW_DIVERGE;
        }
        */

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
/* 角点检测: 边界在窗口内的最大水平偏移.
   偏移超过阈值 → 存在真角点; 否则是平滑弯道.
   用于门控 detect_element_segment 的 RIGHT_ANGLE 分类
   和 ring_fsm 的环岛入口确认. */
uint8_t has_boundary_corner(int16_t *border)
{
    int16_t max_shift;
    int16_t shift;
    int i;
    int16_t prev, next;

    max_shift = 0;
    for (i = 6; i < (int)(MT9V034_HEIGHT - 6); i++)
    {
        prev = border[i - 6];
        next = border[i + 6];
        if (prev > 0 && next > 0)
        {
            shift = next - prev;
            if (shift < 0) shift = (int16_t)(-shift);
            if (shift > max_shift) max_shift = shift;
        }
    }
    return (max_shift > 12) ? 1 : 0;
}


static TRACK_ELEMENT detect_element_segment(void)
{
    int8_t s0, s1;
    uint8_t n;
    int16_t l_near, r_near, l_far, r_far;
    uint16_t near_y, far_y;
    uint8_t near_left_ok, near_right_ok;
    uint8_t far_left_ok, far_right_ok;
    int16_t c_near, c_far, dx;
    int8_t break_row;  /* 整图宽度法十字检测 */
    TRACK_ELEMENT result;

    row_classify_refine(); /* 基础分类已内联, 单遍扫描完成 */
    segment_merge();

    /* 整图扫宽度突变: 扩宽在 LOST 区也能识别, 比 BOTH 段端点对比更稳 */
    break_row = detect_cross_break_row();

    n = g_seg_num;

    if (n == 0)
        return NONE; /* 原 BROKEN → 本次比赛无断桥, 改 NONE */

    s0 = g_seg_type[0];
    s1 = (n >= 2) ? g_seg_type[1] : ROW_INVALID;
    result = STRAIGHT; /* 默认直道 */

    /* 段0=双边正常 → 看段1 */
    if (s0 == ROW_BOTH)
    {
        if (s1 == ROW_WIDE)
            result = CROSS;
        else if (s1 == ROW_LEFT_JUMP || s1 == ROW_RIGHT_JUMP)
            result = STRAIGHT; /* 突变 → 由 ring_fsm_process 确认 */
        else if (s1 == ROW_LEFT_LOST)
            result = (break_row >= 0) ? CROSS : RIGHT_ANGLE_l;
        else if (s1 == ROW_RIGHT_LOST)
            result = (break_row >= 0) ? CROSS : RIGHT_ANGLE_r;
        else if (s1 == ROW_DIVERGE)
            result = STRAIGHT;
        /* s1 不显著 → 落到双行比较确认 */
    }
    else if (s0 == ROW_WIDE)
        result = CROSS;
    else if (s0 == ROW_LEFT_LOST)
        result = (break_row >= 0) ? CROSS : RIGHT_ANGLE_l;
    else if (s0 == ROW_RIGHT_LOST)
        result = (break_row >= 0) ? CROSS : RIGHT_ANGLE_r;
    else if (s0 == ROW_DIVERGE)
        result = STRAIGHT;
    else if (s0 == ROW_LEFT_JUMP || s0 == ROW_RIGHT_JUMP)
        result = STRAIGHT;

    /* ---- 双行比较 ---- */
    if (result == STRAIGHT)
    {
        near_y = (uint16_t)(MT9V034_HEIGHT - 20);
        far_y = (uint16_t)(MT9V034_HEIGHT / 2);

        l_near = g_track.left[near_y];
        r_near = g_track.right[near_y];
        l_far = g_track.left[far_y];
        r_far = g_track.right[far_y];

        if (l_near < 0 || r_near < 0 || l_far < 0 || r_far < 0)
            result = STRAIGHT;
        else
        {
            near_left_ok = (l_near > 2) ? 1 : 0;
            near_right_ok = (r_near < (int16_t)(MT9V034_WIDTH - 4)) ? 1 : 0;
            far_left_ok = (l_far > 2) ? 1 : 0;
            far_right_ok = (r_far < (int16_t)(MT9V034_WIDTH - 4)) ? 1 : 0;

            if (!near_left_ok && !near_right_ok)
                result = STRAIGHT;
            else if (near_left_ok && near_right_ok && far_left_ok && far_right_ok)
            {
                if ((l_near - l_far) > 8 && (r_far - r_near) > 8)
                    result = CROSS;
                else
                {
                    c_near = (l_near + r_near) / 2;
                    c_far = (l_far + r_far) / 2;
                    dx = c_far - c_near;
                    if (dx > 5) result = RIGHT_ANGLE_r;
                    else if (dx < -5) result = RIGHT_ANGLE_l;
                }
            }
            else if (near_left_ok && near_right_ok)
            {
                /* 近行双边可见, 远行单边丢: 用可见边的偏移方向判弯
                   原假设: 右丢→右转, 左丢→左转 — 但左转弯道左侧移左也会丢右!
                   改用可见边方向: L右移(dx>0)→右转, L左移(dx<0)→左转 */
                if (far_left_ok && !far_right_ok)
                {
                    dx = l_far - l_near;
                    if (dx > 5) result = RIGHT_ANGLE_r;
                    else if (dx < -5) result = RIGHT_ANGLE_l;
                }
                else if (!far_left_ok && far_right_ok)
                {
                    dx = r_far - r_near;
                    if (dx > 5) result = RIGHT_ANGLE_r;
                    else if (dx < -5) result = RIGHT_ANGLE_l;
                }
            }
            else if (near_left_ok && far_left_ok)
            {
                dx = l_far - l_near;
                if (dx > 5) result = RIGHT_ANGLE_r;
                else if (dx < -5) result = RIGHT_ANGLE_l;
            }
            else if (near_right_ok && far_right_ok)
            {
                dx = r_far - r_near;
                if (dx > 5) result = RIGHT_ANGLE_r;
                else if (dx < -5) result = RIGHT_ANGLE_l;
            }
        }

    /* ---- 角点门控: 参考 Front_Car ----
       段分叉可能因 dx 异常误判, 用角点检测二次确认.
       一侧有真角点 + 对侧无 → 弯曲方向 */
    if (result == RIGHT_ANGLE_l || result == RIGHT_ANGLE_r)
    {
        uint8_t l_corner, r_corner;
        l_corner = has_boundary_corner(g_track.left);
        r_corner = has_boundary_corner(g_track.right);

        /* 角点确认: 一侧有角点 + 对侧没有 → 真转弯, 否则降级直道 */
        if (result == RIGHT_ANGLE_l)
        {
            /* 左转需要左边界有角点 (弯道鼓出侧) */
            if (!l_corner) result = STRAIGHT;
        }
        else /* RIGHT_ANGLE_r */
        {
            /* 右转需要右边界有角点 */
            if (!r_corner) result = STRAIGHT;
        }
    }
    }

    return result;
}

/* ================================================================
 * 第 8.5 节 — 靶子检测 (独立于赛道元素分类)
 *
 * 简化统一版: 利用横向直径/洞宽规律, 单函数覆盖远近
 *   近处 5段: 亮→暗(壁)→亮(洞)→暗(壁)→亮  洞中心=靶心
 *   远处 3段: 亮→暗(环)→亮                   暗段中心=靶心
 * 逐行收集所有候选, 跨行聚类, 取最大中心一致簇
 * 透视: 靶子洞宽远小近大 (span 随 y 递增)
 * ================================================================ */
#define TARGET_SCAN_Y_START   ((uint16_t)(MT9V034_HEIGHT - 25)) /* 95 */
#define TARGET_SCAN_Y_END     ((uint16_t)(MT9V034_HEIGHT / 4))   /* 30 */
#define TARGET_MIN_TRACK_W    50
#define TARGET_DARK_THRESH    100
#define TARGET_MIN_ROWS       3
#define TARGET_CX_CLUSTER     10
#define TARGET_MAX_SEGS       32
#define TARGET_MAX_CAND       64

/* 障碍检测常量 */
#define OBS_DW_MIN            20
#define OBS_DW_MAX            100
#define OBS_MAX_CAND          64
#define OBS_CX_TOLERANCE      10

static uint8_t detect_target(void)
{
    static uint8_t seg_val[TARGET_MAX_SEGS];
    static uint8_t seg_start[TARGET_MAX_SEGS];
    static uint8_t seg_end[TARGET_MAX_SEGS];
    static uint8_t feat_y[TARGET_MAX_CAND];
    static uint8_t feat_cx[TARGET_MAX_CAND];
    static uint8_t feat_sp[TARGET_MAX_CAND];
    static uint8_t feat_type[TARGET_MAX_CAND]; /* 3=5seg, 2=3segA, 1=3segB */
    uint8_t feat_cnt;
    uint16_t y;
    int16_t l_bound, r_bound;
    uint16_t track_w;
    uint16_t x;
    uint8_t seg_cnt;
    uint8_t in_seg;
    uint8_t pix;
    uint8_t cur_val;
    uint8_t idx;
    uint8_t pos;
    uint8_t lw, hw, rw;
    uint8_t lb, rb;
    uint8_t lr_diff;
    uint8_t dw;
    uint8_t cx;
    uint8_t best_prio;
    uint8_t best_cx, best_sp;
    uint8_t feat_i;
    uint8_t streak_start, streak_len;
    uint8_t best_start, best_len;
    uint8_t cur_start;
    uint8_t i, j;
    uint8_t anchor_cx;
    uint8_t tmp_arr[3];
    uint8_t strong_cnt;
    uint8_t cx_min, cx_max;
    uint8_t cx_med;
    uint8_t sp_bot, sp_top;
    uint8_t max_sp;
    uint16_t score, best_score;

    feat_cnt = 0;

    /* 第一遍: 逐行收集最佳候选 (底→顶), 每行只保留优先级最高的 */
    for (y = TARGET_SCAN_Y_START; y > TARGET_SCAN_Y_END; y--)
    {
        l_bound = g_track.left[y];
        r_bound = g_track.right[y];
        track_w = (uint16_t)(r_bound - l_bound + 1);
        if (track_w < TARGET_MIN_TRACK_W)
            continue;

        seg_cnt = 0;
        in_seg = 0;
        for (x = (uint16_t)l_bound; x <= (uint16_t)r_bound; x++)
        {
            pix = mt9v034_image[y][x];
            cur_val = (pix <= TARGET_DARK_THRESH) ? 1 : 0;

            if (!in_seg)
            {
                if (seg_cnt >= TARGET_MAX_SEGS) break;
                seg_val[seg_cnt] = cur_val;
                seg_start[seg_cnt] = (uint8_t)x;
                in_seg = 1;
            }
            else if (cur_val != seg_val[seg_cnt])
            {
                seg_end[seg_cnt] = (uint8_t)(x - 1);
                seg_cnt++;
                if (seg_cnt >= TARGET_MAX_SEGS) break;
                seg_val[seg_cnt] = cur_val;
                seg_start[seg_cnt] = (uint8_t)x;
            }
        }
        if (in_seg)
        {
            seg_end[seg_cnt] = (uint8_t)r_bound;
            seg_cnt++;
        }

        if (seg_cnt < 3) continue;

        idx = 0;
        while (idx < seg_cnt && seg_val[idx] == 1) idx++;

        best_prio = 0;
        best_cx = 0;
        best_sp = 0;
        pos = idx;

        while (pos + 2 < seg_cnt)
        {
            if (seg_val[pos] != 0) { pos++; continue; }

            /* 5 段: 亮→暗→亮→暗→亮 (优先级 3) */
            if (pos + 4 < seg_cnt
                && seg_val[pos + 1] == 1 && seg_val[pos + 2] == 0
                && seg_val[pos + 3] == 1 && seg_val[pos + 4] == 0)
            {
                lw = seg_end[pos + 1] - seg_start[pos + 1] + 1;
                hw = seg_end[pos + 2] - seg_start[pos + 2] + 1;
                rw = seg_end[pos + 3] - seg_start[pos + 3] + 1;
                lb = seg_end[pos + 0] - seg_start[pos + 0] + 1;
                rb = seg_end[pos + 4] - seg_start[pos + 4] + 1;
                lr_diff = (lw >= rw) ? (uint8_t)(lw - rw) : (uint8_t)(rw - lw);

                if (1 <= lw && lw <= 15 && 1 <= rw && rw <= 15
                    && lr_diff <= 3 && 2 <= hw && hw <= 45
                    && hw >= lw + rw && lb >= 5 && rb >= 3)
                {
                    cx = (seg_start[pos + 2] + seg_end[pos + 2]) / 2;
                    if (3 > best_prio)
                    {
                        best_prio = 3;
                        best_cx = cx;
                        best_sp = seg_end[pos + 3] - seg_start[pos + 1] + 1;
                    }
                }
            }

            /* 3 段 A: dw≥5 (优先级 2) / B: dw≥3 (优先级 1) */
            if (seg_val[pos + 1] == 1 && seg_val[pos + 2] == 0)
            {
                dw = seg_end[pos + 1] - seg_start[pos + 1] + 1;
                lb = seg_end[pos + 0] - seg_start[pos + 0] + 1;
                rb = seg_end[pos + 2] - seg_start[pos + 2] + 1;

                if (dw >= 5 && dw <= 60 && lb >= 5 && rb >= 3)
                {
                    cx = (seg_start[pos + 1] + seg_end[pos + 1]) / 2;
                    if (2 > best_prio)
                    {
                        best_prio = 2;
                        best_cx = cx;
                        best_sp = dw;
                    }
                }
                else if (dw >= 3 && lb >= 15 && rb >= 10)
                {
                    cx = (seg_start[pos + 1] + seg_end[pos + 1]) / 2;
                    if (1 > best_prio)
                    {
                        best_prio = 1;
                        best_cx = cx;
                        best_sp = dw;
                    }
                }
            }

            pos++;
        }

        if (best_prio > 0 && feat_cnt < TARGET_MAX_CAND)
        {
            feat_y[feat_cnt]    = (uint8_t)y;
            feat_cx[feat_cnt]   = best_cx;
            feat_sp[feat_cnt]   = best_sp;
            feat_type[feat_cnt] = best_prio;
            feat_cnt++;
        }
    }

    if (feat_cnt < TARGET_MIN_ROWS)
        return 0;

    /* 第二遍: 连续行一致性筛选 (固定锚点防漂移)
       feat 已按 y 降序 (底→顶), 即 feat_y[0] 最大(最近) */
    best_start = 0;
    best_len   = 0;
    best_score = 0;
    cur_start  = 0;

    while (cur_start < feat_cnt)
    {
        /* 从 cur_start 开始构建 streak */
        streak_start = cur_start;
        streak_len   = 1;

        /* 固定锚点: 前 3 个元素的中位数 cx */
        if (streak_len >= 3)
        {
            tmp_arr[0] = feat_cx[streak_start];
            tmp_arr[1] = feat_cx[streak_start + 1];
            tmp_arr[2] = feat_cx[streak_start + 2];
            /* 冒泡排序 3 个元素 */
            if (tmp_arr[0] > tmp_arr[1]) { j = tmp_arr[0]; tmp_arr[0] = tmp_arr[1]; tmp_arr[1] = j; }
            if (tmp_arr[1] > tmp_arr[2]) { j = tmp_arr[1]; tmp_arr[1] = tmp_arr[2]; tmp_arr[2] = j; }
            if (tmp_arr[0] > tmp_arr[1]) { j = tmp_arr[0]; tmp_arr[0] = tmp_arr[1]; tmp_arr[1] = j; }
            anchor_cx = tmp_arr[1];
        }
        else
        {
            anchor_cx = feat_cx[streak_start];
        }

        /* 从 streak_start+1 开始向后扩展 */
        for (i = streak_start + 1; i < feat_cnt; i++)
        {
            /* y 间隔检查: 允许 ≤2 行空缺 */
            {
                uint8_t prev_y;
                prev_y = feat_y[streak_start + streak_len - 1];
                if (prev_y - feat_y[i] > 3) /* 3 = MAX_Y_GAP(2) + 1 */
                    break;
            }

            /* cx 一致性: |cx - anchor| ≤ 6 */
            {
                int16_t diff;
                diff = (int16_t)feat_cx[i] - (int16_t)anchor_cx;
                if (diff < 0) diff = -diff;
                if (diff > 6) /* CX_TOLERANCE = 5, 放宽到 6 抗噪 */
                    break;
            }

            streak_len++;

            /* 锚点更新: ≥3 行后重新计算 */
            if (streak_len == 3)
            {
                tmp_arr[0] = feat_cx[streak_start];
                tmp_arr[1] = feat_cx[streak_start + 1];
                tmp_arr[2] = feat_cx[streak_start + 2];
                if (tmp_arr[0] > tmp_arr[1]) { j = tmp_arr[0]; tmp_arr[0] = tmp_arr[1]; tmp_arr[1] = j; }
                if (tmp_arr[1] > tmp_arr[2]) { j = tmp_arr[1]; tmp_arr[1] = tmp_arr[2]; tmp_arr[2] = j; }
                if (tmp_arr[0] > tmp_arr[1]) { j = tmp_arr[0]; tmp_arr[0] = tmp_arr[1]; tmp_arr[1] = j; }
                anchor_cx = tmp_arr[1];
            }
        }

        /* 评分当前 streak */
        if (streak_len >= TARGET_MIN_ROWS)
        {
            /* 统计强信号数量, cx 范围, span 透视 */
            strong_cnt = 0;
            cx_min = 255;
            cx_max = 0;
            max_sp = 0;
            sp_bot = feat_sp[streak_start]; /* 第一行 = 最近 (底部) */

            for (i = streak_start; i < streak_start + streak_len; i++)
            {
                if (feat_type[i] >= 2) strong_cnt++; /* 5seg=3, 3segA=2 */
                if (feat_cx[i] < cx_min) cx_min = feat_cx[i];
                if (feat_cx[i] > cx_max) cx_max = feat_cx[i];
                if (feat_sp[i] > max_sp) max_sp = feat_sp[i];
            }
            sp_top = feat_sp[streak_start + streak_len - 1]; /* 最后一行 = 最远 (顶部) */

            /* cx 范围检查 */
            if ((uint8_t)(cx_max - cx_min) > 12)
                goto next_streak;

            /* 纯 B 级信号需要更多行 */
            if (strong_cnt == 0 && streak_len < 5)
                goto next_streak;

            /* 透视检查: span 不应从远到近明显缩小 */
            if (sp_top > sp_bot && sp_bot > 0)
            {
                /* sp_top > sp_bot 意味着远处 span 大于近处, 不符合透视 */
                if ((uint16_t)sp_top * 10 > (uint16_t)sp_bot * 15)
                    goto next_streak; /* sp_top/sp_bot > 1.5 → 拒绝 */
            }

            /* 评分: 长度优先, 强信号加分, cx 稳定加分 */
            score = (uint16_t)streak_len * 10 + (uint16_t)strong_cnt * 8;
            if (score > best_score)
            {
                best_score = score;
                best_start = streak_start;
                best_len   = streak_len;
            }
        }

next_streak:
        cur_start++;
        /* 跳过重叠的 streak: 从下一个候选行开始 */
    }

    if (best_len < TARGET_MIN_ROWS)
        return 0;

    /* 第三遍: 从最佳 streak 输出结果 */
    {
        uint8_t med_idx;
        uint8_t tmp_cxs[12]; /* 最多 12 行 */
        uint8_t sort_i, sort_j, tmp_cx;

        max_sp = 0;
        for (i = best_start; i < best_start + best_len; i++)
        {
            tmp_cxs[i - best_start] = feat_cx[i];
            if (feat_sp[i] > max_sp)
            {
                max_sp = feat_sp[i];
                g_target_y_mid = feat_y[i];
            }
        }

        /* 中位数 cx */
        for (sort_i = 1; sort_i < best_len; sort_i++)
        {
            tmp_cx = tmp_cxs[sort_i];
            sort_j = sort_i;
            while (sort_j > 0 && tmp_cxs[sort_j - 1] > tmp_cx)
            {
                tmp_cxs[sort_j] = tmp_cxs[sort_j - 1];
                sort_j--;
            }
            tmp_cxs[sort_j] = tmp_cx;
        }
        g_target_center_x = tmp_cxs[best_len / 2];
        g_target_radius   = max_sp / 2;
    }

    return 1;
}

/* ================================================================
 * 第 8.6 节 — 障碍检测 (独立于靶子检测)
 *
 * 障碍是实心矩形暗块 (dw >= 20), 与靶子(空心环)不同.
 * 逐行扫描 3 段模式 (亮→暗→亮), 暗段宽 ≥ 20 即为候选.
 * 跨行连续性筛选 (与靶子相同的 streak 逻辑, 但 cx 容差更大).
 * ================================================================ */
static uint8_t detect_obstacle(void)
{
    static uint8_t seg_val[TARGET_MAX_SEGS];
    static uint8_t seg_start[TARGET_MAX_SEGS];
    static uint8_t seg_end[TARGET_MAX_SEGS];
    static uint8_t feat_y[OBS_MAX_CAND];
    static uint8_t feat_cx[OBS_MAX_CAND];
    static uint8_t feat_dw[OBS_MAX_CAND];
    static uint8_t feat_x0[OBS_MAX_CAND];
    static uint8_t feat_x1[OBS_MAX_CAND];
    uint8_t feat_cnt;
    uint16_t y;
    int16_t l_bound, r_bound;
    uint16_t track_w;
    uint16_t x;
    uint8_t seg_cnt;
    uint8_t in_seg;
    uint8_t pix;
    uint8_t cur_val;
    uint8_t idx;
    uint8_t pos;
    uint8_t dw, lb, rb;
    uint8_t cx;
    uint8_t best_dw;
    uint8_t best_cx, best_x0, best_x1;
    uint8_t rows_sorted[OBS_MAX_CAND];
    uint8_t row_count;
    uint8_t cur_streak[OBS_MAX_CAND];
    uint8_t streak_len;
    uint8_t best_start, best_len;
    uint8_t anchor_cx;
    uint8_t tmp_arr[3];
    uint8_t i, j;
    uint8_t sort_i, sort_j, tmp_val;

    feat_cnt = 0;

    /* Step 1: 逐行收集障碍候选 (底→顶) */
    for (y = TARGET_SCAN_Y_START; y > TARGET_SCAN_Y_END; y--)
    {
        l_bound = g_track.left[y];
        r_bound = g_track.right[y];
        track_w = (uint16_t)(r_bound - l_bound + 1);
        if (track_w < TARGET_MIN_TRACK_W)
            continue;

        seg_cnt = 0;
        in_seg = 0;
        for (x = (uint16_t)l_bound; x <= (uint16_t)r_bound; x++)
        {
            pix = mt9v034_image[y][x];
            cur_val = (pix <= TARGET_DARK_THRESH) ? 1 : 0;

            if (!in_seg)
            {
                if (seg_cnt >= TARGET_MAX_SEGS) break;
                seg_val[seg_cnt] = cur_val;
                seg_start[seg_cnt] = (uint8_t)x;
                in_seg = 1;
            }
            else if (cur_val != seg_val[seg_cnt])
            {
                seg_end[seg_cnt] = (uint8_t)(x - 1);
                seg_cnt++;
                if (seg_cnt >= TARGET_MAX_SEGS) break;
                seg_val[seg_cnt] = cur_val;
                seg_start[seg_cnt] = (uint8_t)x;
            }
        }
        if (in_seg)
        {
            seg_end[seg_cnt] = (uint8_t)r_bound;
            seg_cnt++;
        }

        if (seg_cnt < 3) continue;

        idx = 0;
        while (idx < seg_cnt && seg_val[idx] == 1) idx++;

        best_dw = 0;
        best_cx = 0;
        best_x0 = 0;
        best_x1 = 0;
        pos = idx;

        while (pos + 2 < seg_cnt)
        {
            if (seg_val[pos] != 0) { pos++; continue; }

            /* 只检查 3 段模式: 亮→暗→亮 */
            if (seg_val[pos + 1] == 1 && seg_val[pos + 2] == 0)
            {
                dw = seg_end[pos + 1] - seg_start[pos + 1] + 1;
                lb = seg_end[pos + 0] - seg_start[pos + 0] + 1;
                rb = seg_end[pos + 2] - seg_start[pos + 2] + 1;

                if (dw >= OBS_DW_MIN && dw <= OBS_DW_MAX && lb >= 5 && rb >= 5)
                {
                    cx = (seg_start[pos + 1] + seg_end[pos + 1]) / 2;
                    /* 优先选择更宽的暗段 (更多像素 = 更可靠) */
                    if (dw > best_dw)
                    {
                        best_dw = dw;
                        best_cx = cx;
                        best_x0 = seg_start[pos + 1];
                        best_x1 = seg_end[pos + 1];
                    }
                }
            }

            pos++;
        }

        if (best_dw > 0 && feat_cnt < OBS_MAX_CAND)
        {
            feat_y[feat_cnt]  = (uint8_t)y;
            feat_cx[feat_cnt] = best_cx;
            feat_dw[feat_cnt] = best_dw;
            feat_x0[feat_cnt] = best_x0;
            feat_x1[feat_cnt] = best_x1;
            feat_cnt++;
        }
    }

    if (feat_cnt < TARGET_MIN_ROWS)
        return 0;

    /* Step 2: 连续行一致性筛选 (与靶子相同的 streak 逻辑) */
    best_start = 0;
    best_len   = 0;

    /* 构建行号排序数组 (底→顶, 已在 feat 中) */
    row_count = feat_cnt;

    {
        uint8_t cur_start;
        cur_start = 0;
        while (cur_start < row_count)
        {
            streak_len = 1;
            /* 固定锚点 */
            if (streak_len >= 3)
            {
                tmp_arr[0] = feat_cx[cur_start];
                tmp_arr[1] = feat_cx[cur_start + 1];
                tmp_arr[2] = feat_cx[cur_start + 2];
                if (tmp_arr[0] > tmp_arr[1]) { j = tmp_arr[0]; tmp_arr[0] = tmp_arr[1]; tmp_arr[1] = j; }
                if (tmp_arr[1] > tmp_arr[2]) { j = tmp_arr[1]; tmp_arr[1] = tmp_arr[2]; tmp_arr[2] = j; }
                if (tmp_arr[0] > tmp_arr[1]) { j = tmp_arr[0]; tmp_arr[0] = tmp_arr[1]; tmp_arr[1] = j; }
                anchor_cx = tmp_arr[1];
            }
            else
            {
                anchor_cx = feat_cx[cur_start];
            }

            for (i = cur_start + 1; i < row_count; i++)
            {
                {
                    uint8_t prev_y;
                    int16_t diff;
                    prev_y = feat_y[cur_start + streak_len - 1];
                    if (prev_y - feat_y[i] > 3)
                        break;
                    diff = (int16_t)feat_cx[i] - (int16_t)anchor_cx;
                    if (diff < 0) diff = -diff;
                    if (diff > OBS_CX_TOLERANCE)
                        break;
                }

                streak_len++;

                if (streak_len == 3)
                {
                    tmp_arr[0] = feat_cx[cur_start];
                    tmp_arr[1] = feat_cx[cur_start + 1];
                    tmp_arr[2] = feat_cx[cur_start + 2];
                    if (tmp_arr[0] > tmp_arr[1]) { j = tmp_arr[0]; tmp_arr[0] = tmp_arr[1]; tmp_arr[1] = j; }
                    if (tmp_arr[1] > tmp_arr[2]) { j = tmp_arr[1]; tmp_arr[1] = tmp_arr[2]; tmp_arr[2] = j; }
                    if (tmp_arr[0] > tmp_arr[1]) { j = tmp_arr[0]; tmp_arr[0] = tmp_arr[1]; tmp_arr[1] = j; }
                    anchor_cx = tmp_arr[1];
                }
            }

            if (streak_len > best_len)
            {
                best_len   = streak_len;
                best_start = cur_start;
            }

            cur_start++;
        }
    }

    if (best_len < TARGET_MIN_ROWS)
        return 0;

    /* Step 3: 从最佳 streak 输出结果 */
    {
        uint8_t max_dw;
        uint8_t med_idx;
        uint8_t tmp_cxs[12];

        max_dw = 0;
        for (i = best_start; i < best_start + best_len; i++)
        {
            tmp_cxs[i - best_start] = feat_cx[i];
            if (feat_dw[i] > max_dw)
            {
                max_dw = feat_dw[i];
                g_obstacle_y_mid      = feat_y[i];
                g_obstacle_left_edge  = feat_x0[i];
                g_obstacle_right_edge = feat_x1[i];
            }
        }

        /* 中位数 cx */
        for (sort_i = 1; sort_i < best_len; sort_i++)
        {
            tmp_val = tmp_cxs[sort_i];
            sort_j = sort_i;
            while (sort_j > 0 && tmp_cxs[sort_j - 1] > tmp_val)
            {
                tmp_cxs[sort_j] = tmp_cxs[sort_j - 1];
                sort_j--;
            }
            tmp_cxs[sort_j] = tmp_val;
        }
        g_obstacle_center_x = tmp_cxs[best_len / 2];
        g_obstacle_width     = max_dw;
    }

    return 1;
}

/* 综合瞄准: 靶子吸引 + 障碍排斥 → 单一目标点
   仅靶子: 指向靶心
   仅障碍: 指向远离障碍的一侧 (空间更大的一侧)
   两者都有: 靶子吸引(权重 2.0) + 障碍排斥(权重 1.5), 加权合成 */
static uint8_t compute_combined_aim(void)
{
    uint8_t t_det, o_det;
    uint8_t t_cx, o_cx, o_x0, o_x1;
    uint8_t left_space, right_space;
    int16_t aim;
    int16_t push;

    t_det = g_target_detected;
    o_det = g_obstacle_detected;
    t_cx  = g_target_center_x;
    o_cx  = g_obstacle_center_x;
    o_x0  = g_obstacle_left_edge;
    o_x1  = g_obstacle_right_edge;
    left_space  = 0;
    right_space = 0;

    if (!t_det && !o_det)
        return CENTER_POINT;

    if (t_det && !o_det)
    {
        /* 吸引到靶子前方: 偏置量 = 靶子半径 × 2 (越近偏越多)
           靶子在左 → 瞄准靶子右侧; 靶子在右 → 瞄准靶子左侧 */
        int16_t offset;
        offset = (int16_t)g_target_radius * 2;
        if (offset < 8) offset = 8;
        if ((int16_t)t_cx < (int16_t)CENTER_POINT)
            aim = (int16_t)t_cx + offset;
        else
            aim = (int16_t)t_cx - offset;
        if (aim < 5) aim = 5;
        if (aim > (int16_t)(MT9V034_WIDTH - 5)) aim = (int16_t)(MT9V034_WIDTH - 5);
        return (uint8_t)aim;
    }

    if (o_det && !t_det)
    {
        left_space  = o_x0;
        right_space = (uint8_t)(MT9V034_WIDTH - o_x1);
        if (left_space > right_space)
            return (uint8_t)(o_x0 / 2);
        else
            return (uint8_t)(o_x1 + (MT9V034_WIDTH - o_x1) / 2);
    }

    /* 两者都有: 靶子吸引 + 障碍排斥
       target_weight=2.0, obstacle_weight=1.5
       障碍在左 → 向右推; 障碍在右 → 向左推 */
    aim = (int16_t)t_cx;
    if (o_cx < t_cx)
    {
        push = (int16_t)(t_cx - o_cx) * 15 / 35;  /* 1.5/(2.0+1.5) * 10 */
        aim = (int16_t)t_cx + push;
    }
    else
    {
        push = (int16_t)(o_cx - t_cx) * 15 / 35;
        aim = (int16_t)t_cx - push;
    }

    if (aim < 5) aim = 5;
    if (aim > (int16_t)(MT9V034_WIDTH - 5)) aim = (int16_t)(MT9V034_WIDTH - 5);

    (void)left_space;
    (void)right_space;

    return (uint8_t)aim;
}

/* ================================================================
 * 第 9 节 — 元素检测主逻辑
 *
 * track_element_judge()    — 主入口: 环岛退出 → 分段检测 → 环岛确认 → 十字回退
 * detect_element_segment() — 行分类 + 分段合并 + 段序列 → 元素
 * ================================================================ */

/* 主分类入口: 段分类 → 环岛状态机 → 十字回退

   环岛检测由 ring_fsm 封装:
     - 条件1(边界终点) + 条件2(上方有路) 同时成立才确认环岛
     - 状态保持 + 入口/出口/中心转换 全在 ring_fsm 内部管理 */
TRACK_ELEMENT track_element_judge(void)
{
    TRACK_ELEMENT seg_elem;

    if (!g_track_valid)
    {
        ring_fsm_reset(&g_ring_fsm);
        return NONE;
    }

    if (g_track.feature == VISION_FEATURE_LOST)
        return NONE; /* 原 BROKEN → 本次比赛无断桥, 改 NONE */

    seg_elem = detect_element_segment();

    /* 环岛状态机: 处理入口/保持/出口, 返回 RING_x 或透传 seg_elem
       条件1(边界终点) + 条件2(上方有路) 在 ring_fsm 内部同时验证 */
    seg_elem = ring_fsm_process(&g_ring_fsm, seg_elem);

    /* 环岛元素直接返回, 不经过十字回退 */
    if (seg_elem == RING_l || seg_elem == RING_r || seg_elem == RING_c)
        return seg_elem;

    if (seg_elem != STRAIGHT)
        return seg_elem;

    /* 回退: 宽度法十字检测 */
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

/* 直道: 近行(98)+远行(60)加权 — Fix 3b: 近行 67% (噪声小) + 远行 33% (前瞻) */
static uint8_t plan_straight_center(void)
{
    int16_t near_mid, far_mid, target;

    near_mid = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_NEAR);
    far_mid = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_FAR);
    if (near_mid >= 0 && far_mid >= 0)
    {
        int16_t dx;
        target = (int16_t)((near_mid + far_mid * 2) / 3);
        /* 前瞻偏置: 远行偏右→提前右靠, 远行偏左→提前左靠 (入弯预判) */
        dx = far_mid - near_mid;
        if (dx > 3)
            target += 10;
        else if (dx < -3)
            target -= 10;
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

    far_y = (uint16_t)(MT9V034_HEIGHT / 2); /* y=60, 同 straight 远行避免 target 回跳 */
    l_far = g_track.left[far_y];
    r_far = g_track.right[far_y];

    far_left_ok = (l_far > 2) ? 1 : 0;
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
            lane_w = 85;
        }
    }
    /* 道宽范围: 竞赛赛道在图像中约 70~100px */
    if (lane_w < 50)
        lane_w = 85;
    if (lane_w > 160)
        lane_w = 160;

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

    /* 向弯道内侧偏移 (道宽比例, 原固定 6px 太小)
       error = 94 - target: target偏右→左打; target偏左→右打
       右转向左偏(切入内侧), 左转向右偏(切入内侧) */
    {
        int16_t bias;
        bias = lane_w / TRACK_TURN_BIAS_RATIO;
        if (bias < 5) bias = 5;
        if (bias > 20) bias = 20;
        if (turn_type == RIGHT_ANGLE_r)
            target -= bias;
        else if (turn_type == RIGHT_ANGLE_l)
            target += bias;
    }

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
    if (g_target_detected)
        fvals[9] = (float)((int16_t)g_target_center_x + 256);
    else if (g_obstacle_detected)
        fvals[9] = (float)((int16_t)g_obstacle_center_x + 512);
    else
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

    /* 锁定航向: 直道保持姿态 [BROKEN_RODE 已注释, 本次比赛无断桥] */
    if (state == STRAIGHT)
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
    /* [本次比赛无断桥, broken_flag_clear 已注释]
    if (state == STRAIGHT)
    {
        broken_flag_clear();
    }
    if (state == RING_l || state == RING_r || state == RING_c)
    {
        broken_flag_clear();
    }
    */
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
        track_fsm_set_callbacks(&g_track_fsm, trail_fsm_on_entry, 0);
        ring_fsm_init(&g_ring_fsm);
        fsm_inited = 1;
    }

    vision_poll_track();
    check_out_of_bounds();
    if (g_out_of_bounds)
    {
        track_element = NONE;
        current_element = NONE;
        return;
    }
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

#if TRAIL_DBG_PRINTF
    cross_cnt = count_cross_rows(&g_track);
    break_row = detect_cross_break_row();
#endif

#if VISION_USE_PURE_PURSUIT || VOFA_FIREWATER
    // 计算纯追踪与曲率 (供速度决策或调试)
    speed_est = 45.0f;
    plan_pure_pursuit(speed_est);
    pp_curvature = compute_road_curvature(&g_track);
#endif
    pp_visible_high = g_track.visible_high;

    // 断桥升级: 累积行驶距离超过阈值 → 进入断桥后阶段 [本次比赛无断桥, 已注释]
    /*
    if (raw_elem == BROKEN)
    {
        if (broken_judged())
            raw_elem = BROKEN_RODE;
    }
    */

    // 靶子+障碍检测 (在 FSM 之前, 检测到则强制直道, 避免靶环干扰元素分类)
    {
        static uint8_t target_skip = 0;
        target_skip++;
        if (target_skip >= 4)
        {
            uint8_t target_found;
            uint8_t obstacle_found;
            target_skip = 0;
            target_found = detect_target();
            g_target_detected = target_found ? 1 : 0;
            obstacle_found = detect_obstacle();
            g_obstacle_detected = obstacle_found ? 1 : 0;
        }
    }

    if ((g_target_detected || g_obstacle_detected)
        && current_element != RING_l && current_element != RING_r && current_element != RING_c)
        raw_elem = STRAIGHT;

    track_fsm_update(&g_track_fsm, raw_elem);
    track_element = g_track_fsm.state;

    // 目标规划 — 环岛状态用专用规划函数, 其他按 FSM plan 委派
    plan = track_fsm_get_plan(&g_track_fsm);
    new_target = track_midpoint_target_P;

    if (track_element == RING_l || track_element == RING_r || track_element == RING_c)
    {
        new_target = ring_fsm_get_target(&g_ring_fsm);
    }
    else if (plan == PLAN_STRAIGHT)
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

    /* 靶子+障碍覆写: 综合吸引(靶子) + 排斥(障碍) → 单一目标点 */
    if (g_target_detected || g_obstacle_detected)
    {
        new_target = compute_combined_aim();
    }

    // 后处理: 跳变限幅 ±12px + 逐状态 EMA 平滑
    if (!g_target_detected && !g_obstacle_detected &&
        track_element != NONE &&
        track_element != RIGHT_ANGLE_l && track_element != RIGHT_ANGLE_r &&
        track_element != RING_l && track_element != RING_r &&
        track_element != CROSS)
    {
        jump = (int16_t)new_target - (int16_t)track_midpoint_target_P;
        /* Fix 3c: 跳变限制 ±12 → ±6, 抑制 10Hz 振荡 */
        if (jump > 6)
            new_target = (uint8_t)((int16_t)track_midpoint_target_P + 6);
        else if (jump < -6)
            new_target = (uint8_t)((int16_t)track_midpoint_target_P - 6);

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
    printf("DBG feature:%d cross_cnt:%u break_row:%d valid_rows:%u center_x:%d element:%s target:%u tg_det:%u tg_cx:%u ob_det:%u ob_cx:%u pp_ang:%.1f\r\n",
           g_track.feature,
           cross_cnt,
           break_row,
           g_track.valid_rows,
           g_track.center_x,
           track_element_name(track_element),
           track_midpoint_target,
           g_target_detected,
           g_target_center_x,
           g_obstacle_detected,
           g_obstacle_center_x,
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

// 环岛检测 — 移植49.9 huandao_detect 核心状态机
//   0:HUANDAO_NONE → 1:STATE1(确认) → 2:STATE2(入环) → 2B(即将入)
//   → 3:STATE3(环内) → 4:STATE4(等白列) → 5:STATE5(跟踪) → 6:STATE6(半宽)
//   → 7:STATE7(右上拐点) → 0:退出
// 适配: g_track.left/right 替代 l_border/r_border
//       g_track.visible_high 替代 Search_Stop_Line

#include "ring_fsm.h"
#include "control.h"
#include "icm.h"
#include "vision.h"

extern uint8_t xdata mt9v034_image[MT9V034_HEIGHT][MT9V034_WIDTH];

ring_fsm_t g_ring_fsm;

/* ===== 49.9环岛常量 ===== */
#define HUANDAO_NONE       0
#define HUANDAO_STATE1     1
#define HUANDAO_STATE2     2
#define HUANDAO_STATE2B    3
#define HUANDAO_STATE3     4
#define HUANDAO_STATE4     6
#define HUANDAO_STATE5     7
#define HUANDAO_STATE6     8
#define HUANDAO_STATE7     9

#define HD_R_DOWN_MIN_ROW  50
#define HD_R_DOWN_MIN_DIST 30
#define HD_R_STABLE_TH     8
#define HD_R_START_MIN_ROW 110
#define HD_L_CONT_JUMP_TH  3
#define HD_L_EFFECT_MIN    55
#define HD_R_UP_STABLE_TH  12
#define HD_R_UP_MAX_COL    180

static uint8_t g_huandao_state = HUANDAO_NONE;
static int16_t g_hd_r_down = 0;
static int16_t g_hd_r_up = 0;
static int16_t g_hd_l_up = 0;
static int16_t g_hd_l_turn = 0;

/* ===== 辅助: 找首个同时有效的行 (first_end) ===== */
static int16_t ring_first_end(void)
{
    int16_t y;
    for (y = MT9V034_HEIGHT - 1; y > 0; y--) {
        if (g_track.left[y] > 2 && g_track.right[y] < (int16_t)(MT9V034_WIDTH - 4))
            return y;
    }
    return 0;
}

/* ===== 辅助: 右边界有效标记 ===== */
static int8_t r_ef(int16_t y)
{
    if (y < 0 || y >= (int16_t)MT9V034_HEIGHT) return 0;
    return (g_track.right[y] < (int16_t)(MT9V034_WIDTH - 4)) ? 1 : 0;
}

static int8_t l_ef(int16_t y)
{
    if (y < 0 || y >= (int16_t)MT9V034_HEIGHT) return 0;
    return (g_track.left[y] > 2) ? 1 : 0;
}

/* ===== 49.9 find_right_down_point ===== */
static void find_r_down(void)
{
    int16_t i;
    g_hd_r_down = 0;
    for (i = MT9V034_HEIGHT - 4; i >= HD_R_DOWN_MIN_ROW; i--) {
        if (r_ef(i) && r_ef(i+1) && r_ef(i+2) && !r_ef(i-3) && !r_ef(i-4) &&
            abs((int16_t)(g_track.right[i] - g_track.right[i+1])) <= HD_R_STABLE_TH &&
            abs((int16_t)(g_track.right[i+1] - g_track.right[i+2])) <= HD_R_STABLE_TH &&
            abs((int16_t)(g_track.right[i] - g_track.right[i-3])) >= HD_R_STABLE_TH) {
            g_hd_r_down = i; break;
        }
    }
}

/* ===== 49.9 check_left_continuous ===== */
static uint8_t check_l_cont(void)
{
    int16_t i, fend;
    int16_t valid = 0;
    uint8_t started = 0;
    fend = ring_first_end();
    for (i = MT9V034_HEIGHT - 1; i > fend; i--) {
        if (!started) {
            if (l_ef(i)) { started = 1; valid = 1; }
        } else {
            if ((int16_t)(g_track.left[i] - g_track.left[i+1]) >= HD_L_CONT_JUMP_TH)
                return 0;
            valid++;
        }
    }
    return (valid >= HD_L_EFFECT_MIN) ? 1 : 0;
}

/* ===== 49.9 check_r_invalid_l_valid ===== */
static uint8_t check_r_inv_l_val(int16_t from_row)
{
    int16_t i, fend;
    fend = ring_first_end();
    if (from_row >= MT9V034_HEIGHT) from_row = MT9V034_HEIGHT - 1;
    for (i = from_row; i > fend; i -= 2) {
        if (!r_ef(i) && !l_ef(i)) return 0;
    }
    return 1;
}

/* ===== 49.9 get_right_first_valid_row ===== */
static int16_t get_r_first(void)
{
    int16_t i, fend;
    fend = ring_first_end();
    for (i = MT9V034_HEIGHT - 1; i > fend; i--) {
        if (r_ef(i)) return i;
    }
    return -1;
}

/* ===== 49.9 简化版右上拐点 ===== */
static void find_r_up_simple(void)
{
    int16_t i;
    g_hd_r_up = 0;
    for (i = MT9V034_HEIGHT - 2; i > ring_first_end() + 1; i--) {
        if (r_ef(i) && r_ef(i-1) && !r_ef(i+1) && g_track.right[i] < HD_R_UP_MAX_COL) {
            g_hd_r_up = i; break;
        }
    }
}

/* ===== 49.9 find_hd_r_up_point ===== */
static void find_r_up(void)
{
    int16_t i;
    g_hd_r_up = 0;
    for (i = MT9V034_HEIGHT - 5; i > ring_first_end() + 2; i--) {
        if (r_ef(i) && r_ef(i-1) && r_ef(i-2) && !r_ef(i+3) && !r_ef(i+4) &&
            abs((int16_t)(g_track.right[i] - g_track.right[i-1])) <= HD_R_UP_STABLE_TH &&
            abs((int16_t)(g_track.right[i-1] - g_track.right[i-2])) <= HD_R_UP_STABLE_TH &&
            abs((int16_t)(g_track.right[i] - g_track.right[i+3])) >= HD_R_UP_STABLE_TH &&
            abs((int16_t)(g_track.right[i] - g_track.right[i+4])) >= HD_R_UP_STABLE_TH &&
            g_track.right[i] < HD_R_UP_MAX_COL) {
            g_hd_r_up = i; break;
        }
    }
}

/* ===== 核心: 49.9 huandao_detect 移植 ===== */
static TRACK_ELEMENT ring_detect(void)
{
    int16_t r_first;

    switch (g_huandao_state) {
    case HUANDAO_NONE:
        find_r_down();
        if (!g_hd_r_down) break;
        if (g_hd_r_down > MT9V034_HEIGHT - 1 - HD_R_DOWN_MIN_DIST) break;
        if (g_hd_r_down < HD_R_DOWN_MIN_ROW) break;
        if (!check_l_cont()) break;
        if (!check_r_inv_l_val(g_hd_r_down)) break;
        if (g_track.visible_high <= 100) break;  /* Search_Stop_Line */
        g_huandao_state = HUANDAO_STATE1;
        break;

    case HUANDAO_STATE1:
        find_r_down();
        if (!check_l_cont()) break;
        r_first = get_r_first();
        if (r_first < 0 || r_first >= HD_R_START_MIN_ROW) break;
        if (g_hd_r_down != 0) break;
        g_huandao_state = HUANDAO_STATE2;
        break;

    case HUANDAO_STATE2:
        r_first = get_r_first();
        if (r_first > HD_R_START_MIN_ROW)
            g_huandao_state = HUANDAO_STATE2B;
        break;

    case HUANDAO_STATE2B:
        r_first = get_r_first();
        if (r_first < 0 || r_first >= HD_R_START_MIN_ROW) break;
        find_r_up_simple();
        if (g_hd_r_up) g_huandao_state = HUANDAO_STATE3;
        break;

    case HUANDAO_STATE3:
        find_r_up_simple();
        if ((MT9V034_HEIGHT - 1 - g_track.visible_high) < 80)
            g_huandao_state = HUANDAO_STATE4;
        break;

    case HUANDAO_STATE4:
        if ((MT9V034_HEIGHT - 1 - g_track.visible_high) > 80)
            g_huandao_state = HUANDAO_STATE5;
        break;

    case HUANDAO_STATE5:
        /* 跟踪左拐点: 简化—左边界首次有效行 */
        {
            int16_t i, fend = ring_first_end();
            g_hd_l_turn = 0;
            for (i = MT9V034_HEIGHT - 1; i > fend; i--)
                if (l_ef(i)) { g_hd_l_turn = i; break; }
            if (!g_hd_l_turn) g_huandao_state = HUANDAO_STATE6;
        }
        break;

    case HUANDAO_STATE6:
        if (g_track.visible_high <= 100) break;
        find_r_up_simple();
        if (g_hd_r_up > 0) g_huandao_state = HUANDAO_STATE7;
        break;

    case HUANDAO_STATE7:
        find_r_up();
        if (!g_hd_r_up) {
            g_huandao_state = HUANDAO_NONE;
            g_hd_r_down = g_hd_r_up = g_hd_l_up = g_hd_l_turn = 0;
        }
        break;

    default:
        g_huandao_state = HUANDAO_NONE;
        break;
    }

    if (g_huandao_state >= HUANDAO_STATE2)
        return RING_r;  /* 右环岛 */
    if (g_huandao_state == HUANDAO_STATE1)
        return RING_r;
    return NONE;
}

/* ===== 接口 ===== */
void ring_fsm_init(ring_fsm_t *rf)
{
    rf->state = RING_IDLE;
    rf->entry_yaw = 0.0f;
    g_huandao_state = HUANDAO_NONE;
}

void ring_fsm_reset(ring_fsm_t *rf)
{
    rf->state = RING_IDLE;
    g_huandao_state = HUANDAO_NONE;
}

uint8_t ring_fsm_is_active(const ring_fsm_t *rf)
{
    return (rf->state != RING_IDLE) ? 1 : 0;
}

TRACK_ELEMENT ring_fsm_process(ring_fsm_t *rf, TRACK_ELEMENT seg_elem)
{
    TRACK_ELEMENT ring_result;

    if (!g_track_valid) {
        rf->state = RING_IDLE;
        g_huandao_state = HUANDAO_NONE;
        return seg_elem;
    }

    /* 49.9环岛检测: 十字期间不检测环岛 */
    /* ring_detect调用内部状态机 */
    ring_result = ring_detect();

    if (ring_result != NONE) {
        rf->state = RING_ENTER_r;  /* 49.9只有右环岛 */
        return RING_r;
    }

    /* 状态保持 */
    if (rf->state == RING_ENTER_r) {
        if (g_huandao_state == HUANDAO_NONE) {
            rf->state = RING_IDLE;
            return STRAIGHT;
        }
        if (g_huandao_state >= HUANDAO_STATE5) {
            rf->state = RING_CENTER;
            return RING_c;
        }
        return RING_r;
    }

    if (rf->state == RING_CENTER) {
        if (g_huandao_state == HUANDAO_NONE) {
            rf->state = RING_IDLE;
            return STRAIGHT;
        }
        return RING_c;
    }

    return seg_elem;
}

uint8_t ring_fsm_get_target(const ring_fsm_t *rf)
{
    int16_t l_far, r_far;
    uint16_t far_y = (uint16_t)VISION_LOOKAHEAD_Y;
    l_far = g_track.left[far_y];
    r_far = g_track.right[far_y];

    if (rf->state == RING_ENTER_r) {
        /* 右环岛: 跟右边界 */
        if (r_far < (int16_t)(MT9V034_WIDTH - 4))
            return clamp_center_to_target(r_far - 30);
        return (uint8_t)(CENTER_POINT + 30);
    }
    return (uint8_t)CENTER_POINT;
}

// trail.c — 边界扫描 + Front_Car 动态半宽中线
// 边界: calc_diff 逐行扫描 (稳定)
// 中线: 双边中点 / 单边+动态半宽 (防弯道94回退)
// 误差: 种子行中点 + EMA滤波

#include "trail.h"
#include "laser.h"
#include "control.h"

extern uint8_t xdata mt9v034_image[MT9V034_HEIGHT][MT9V034_WIDTH];
extern uint8_t g_slope_detected;

/* ==== 全局变量 ==== */
uint8_t g_track_valid = 0, g_target_detected = 0, g_target_center_x = 94, g_target_radius = 0, g_target_y_mid = 60, g_vofa_pending = 0;
uint8_t g_obstacle_detected = 0, g_obstacle_center_x = 94, g_obstacle_width = 0;
image_t image_data[MT9V034_HEIGHT * MT9V034_WIDTH];
vision_track_result_t g_track;
int16_t Image_Error = 0, posi = 0;

volatile target_state_e target_state = TARGET_WAIT_FAR;
volatile int8_t target_flag = 0;
int16_t target_center_col = 0, target_center_row = 0, target_focus_col = 0;
int16_t target_red_rows[TARGET_RED_MAX], target_red_cols[TARGET_RED_MAX];
int16_t target_red_count = 0;

int16_t current_white = 0, l_border[IMAGE_H], r_border[IMAGE_H], image_position[IMAGE_H];
int8_t l_effect_flag[IMAGE_H], r_effect_flag[IMAGE_H];
int16_t first_end = 0, l_effect_num = 0, r_effect_num = 0, l_invalid_cnt = 0, r_invalid_cnt = 0;
uint8_t cross_state = 0, cross_phase = 0, huandao_state = HUANDAO_NONE;
/* 十字拐点 */
int16_t l_down_point = 0, r_down_point = 0, l_up_point = 0, r_up_point = 0;
int16_t l_dp_prev = 0, r_dp_prev = 0, l_up_prev = 0, r_up_prev = 0;
int16_t l_slope_num = 0, l_slope_den = 1, r_slope_num = 0, r_slope_den = 1;
/* 右环岛 */
int16_t hd_r_dp = 0, hd_r_up = 0, hd_l_up = 0, hd_l_tp = 0;
/* 左环岛 */
uint8_t  l_huandao_state = HUANDAO_NONE;
int16_t l_hd_l_dp = 0, l_hd_l_up = 0, l_hd_r_up = 0, l_hd_r_tp = 0;
struct road_type_t road_type = {0};
int16_t sudu_yingzi_val = 0, Search_Stop_Line = 0, Both_Lost_Time = 0;
int16_t white_length_max[2][1], white_length[2][WH_COL_NUM];

const uint8_t Half_Road_Wide[120] = {
    7, 7, 8, 9, 10, 11, 11, 12, 13, 13, 14, 15, 15, 16, 17, 17, 18, 19, 20, 21, 21, 22, 23, 23, 24, 25, 25, 26, 27, 27,
    28, 29, 29, 30, 31, 31, 32, 33, 33, 34, 35, 36, 37, 38, 38, 39, 39, 40, 41, 41, 42, 43, 44, 45, 45, 46, 47, 48, 49, 50,
    51, 51, 52, 53, 53, 54, 50, 55, 56, 57, 57, 57, 58, 59, 60, 61, 62, 62, 63, 63, 64, 64, 65, 66, 67, 67, 68, 68, 69, 70,
    71, 72, 72, 73, 73, 74, 75, 76, 76, 77, 78, 78, 79, 80, 80, 81, 82, 83, 84, 85, 86, 86, 87, 88, 89, 90, 91, 92, 93, 94};

/* ==== 内部状态 ==== */
static int16_t g_mid_out[MT9V034_HEIGHT];
static int16_t g_hw_bottom = 55, g_err_smooth = 0;
#define HALF_WIDTH_SCALE 12 /* 半宽缩放 1.0→1.2x */

/* ==== 工具 ==== */
int16_t myabs(int16_t d) { return (d >= 0) ? d : -d; }
int16_t limit_ab(int16_t x, int16_t a, int16_t b)
{
    if (x < a)
        x = a;
    if (x > b)
        x = b;
    return x;
}
int16_t limit_float(int16_t x, int16_t y)
{
    if (x > y)
        return y;
    if (x < -y)
        return -y;
    return x;
}
int16_t calc_diff(int16_t x, int16_t y) { return (int16_t)(((x - y) << 7) / (x + y)); }

/* ==== search_white ==== */
void search_white(uint8_t *photo, uint16_t point_num)
{
    uint16_t i;
    int16_t wl, ws = 0, we = 0, tv, tv2;
    uint8_t hist[256];
    for (i = 0; i < 256; i++)
        hist[i] = 0;
    for (i = 0; i < point_num; i++)
    {
        hist[*photo]++;
        photo++;
    }
    wl = 0;
    for (i = 255; i > 0; i--)
    {
        if (!ws)
        {
            if (hist[i] > 5)
                ws = (int16_t)i;
        }
        else
        {
            if (!hist[i])
            {
                we = (int16_t)i + wl;
                if (hist[i] < 5)
                    wl++;
            }
            else
                wl = 0;
        }
        if (wl >= 5)
            break;
    }
    tv = we + (ws - we) / 5;
    if (!current_white)
        current_white = tv;
    else
    {
        tv2 = calc_diff(tv, current_white);
        if (tv2 > -(THRESHOLD / 2))
            current_white += limit_float(tv - current_white, 10);
    }
}

/* ==== search_longest_white_col ==== */
void search_longest_white_col(void)
{
    int16_t i, j, col, ci, tv, ns = WH_START_ROW, wt, wb, jr, br = IMAGE_H - 1, bc = IMAGE_W / 2, cd;
    uint8_t bd, ff = 0;
    for (i = 0; i < WH_COL_NUM; i++)
    {
        white_length[0][i] = IMAGE_H - 1;
        white_length[1][i] = WH_COL_MIN + (int16_t)i * (int16_t)WH_COL_STEP;
    }
    ci = 0;
    for (col = (int16_t)WH_COL_MIN; col <= (int16_t)WH_COL_MAX; col += (int16_t)WH_COL_STEP)
    {
        if (ci >= WH_COL_NUM)
            break;
        white_length[1][ci] = col;
        bd = 0;
        for (j = IMAGE_H - 1; j > IMAGE_H - 1 - PHASE1_ROWS; j--)
        {
            tv = calc_diff(current_white, (int16_t)mt9v034_image[(uint16_t)j][(uint16_t)col]);
            if (tv > THRESHOLD)
            {
                bd = 1;
                break;
            }
        }
        if (!bd && mt9v034_image[IMAGE_H - 1][(uint16_t)col] < BOTTOM_DARK_GATE && mt9v034_image[IMAGE_H - 2][(uint16_t)col] < BOTTOM_DARK_GATE)
            bd = 1;
        if (bd)
        {
            ci++;
            continue;
        }
        if (!ff)
        {
            ns = WH_START_ROW;
            ff = 1;
        }
        {
            int16_t sr = ns;
            if (sr > IMAGE_H - 1 - JUMP_NUM)
                sr = IMAGE_H - 1 - JUMP_NUM;
            if (sr < WH_ROW_MIN)
                sr = WH_ROW_MIN;
            wb = sr;
            wt = sr - (WH_WINDOW_SIZE - 1);
            if (wt < WH_ROW_MIN)
                wt = WH_ROW_MIN;
            jr = -1;
            for (j = wb; j >= wt; j -= (int16_t)WH_ROW_STEP)
            {
                if (j + JUMP_NUM > IMAGE_H - 1)
                    continue;
                tv = calc_diff((int16_t)mt9v034_image[(uint16_t)(j + JUMP_NUM)][(uint16_t)col], (int16_t)mt9v034_image[(uint16_t)j][(uint16_t)col]);
                if (tv > THRESHOLD)
                {
                    jr = j;
                    break;
                }
            }
            if (jr < 0 && wt > WH_ROW_MIN)
                for (j = WH_START_ROW; j >= WH_ROW_MIN; j -= (int16_t)WH_ROW_STEP)
                {
                    if (j + JUMP_NUM > IMAGE_H - 1)
                        continue;
                    tv = calc_diff((int16_t)mt9v034_image[(uint16_t)(j + JUMP_NUM)][(uint16_t)col], (int16_t)mt9v034_image[(uint16_t)j][(uint16_t)col]);
                    if (tv > THRESHOLD)
                    {
                        jr = j;
                        break;
                    }
                }
            if (jr < 0)
                jr = WH_ROW_MIN;
        }
        white_length[0][ci] = jr;
        ns = jr + WH_NEXT_OFFSET;
        if (ns > IMAGE_H - 1 - JUMP_NUM)
            ns = IMAGE_H - 1 - JUMP_NUM;
        if (ns < WH_ROW_MIN)
            ns = WH_ROW_MIN;
        if (jr < br)
        {
            if (br >= IMAGE_H - 1)
            {
                br = jr;
                bc = col;
            }
            else
            {
                cd = (col > bc) ? (col - bc) : (bc - col);
                if (cd < 60)
                {
                    br = jr;
                    bc = col;
                }
            }
        }
        ci++;
    }
    white_length_max[0][0] = br;
    white_length_max[1][0] = bc;
}

/* ==== search_border ==== */
void search_border(void)
{
    int16_t i, j, tv, rc = white_length_max[1][0], lsc, lec, rsc, rec;
    uint8_t sp;
    if (rc < SEARCH_MIN + JUMP_NUM)
        rc = SEARCH_MIN + JUMP_NUM;
    if (rc > SEARCH_MAX - JUMP_NUM)
        rc = SEARCH_MAX - JUMP_NUM;
    first_end = white_length_max[0][0] + 3;
    if (first_end > IMAGE_H - 1)
        first_end = IMAGE_H - 1;
    if (first_end < 0)
        first_end = 0;
    l_effect_num = r_effect_num = 0;
    Both_Lost_Time = 0;
    for (i = 0; i < IMAGE_H; i++)
    {
        l_border[i] = 0;
        r_border[i] = IMAGE_W;
        l_effect_flag[i] = r_effect_flag[i] = 0;
        image_position[i] = IMAGE_W / 2;
    }
    lsc = rc;
    lec = SEARCH_MIN;
    rsc = rc;
    rec = SEARCH_MAX;
    for (i = IMAGE_H - 1; i > first_end; i--)
    {
        sp = 2;
        while (sp > 0)
        {
            if (sp == 1)
            {
                lsc = rc;
                lec = SEARCH_MIN;
            }
            sp--;
            for (j = lsc; j >= lec; j--)
            {
                if (j < SEARCH_MIN || j + JUMP_NUM >= IMAGE_W)
                    continue;
                tv = calc_diff((int16_t)mt9v034_image[(uint16_t)i][(uint16_t)(j + JUMP_NUM)], (int16_t)mt9v034_image[(uint16_t)i][(uint16_t)j]);
                if (tv > THRESHOLD)
                {
                    l_border[i] = j;
                    l_effect_flag[i] = 1;
                    l_effect_num++;
                    lsc = j + SEARCH_RANGE;
                    if (lsc > SEARCH_MAX - JUMP_NUM)
                        lsc = SEARCH_MAX - JUMP_NUM;
                    lec = j - SEARCH_RANGE;
                    if (lec < SEARCH_MIN)
                        lec = SEARCH_MIN;
                    sp = 0;
                    break;
                }
            }
        }
        sp = 2;
        while (sp > 0)
        {
            if (sp == 1)
            {
                rsc = rc;
                rec = SEARCH_MAX;
            }
            sp--;
            for (j = rsc; j <= rec; j++)
            {
                if (j > SEARCH_MAX || j - JUMP_NUM < 0)
                    continue;
                tv = calc_diff((int16_t)mt9v034_image[(uint16_t)i][(uint16_t)(j - JUMP_NUM)], (int16_t)mt9v034_image[(uint16_t)i][(uint16_t)j]);
                if (tv > THRESHOLD)
                {
                    r_border[i] = j;
                    r_effect_flag[i] = 1;
                    r_effect_num++;
                    rsc = j - SEARCH_RANGE;
                    if (rsc < SEARCH_MIN + JUMP_NUM)
                        rsc = SEARCH_MIN + JUMP_NUM;
                    rec = j + SEARCH_RANGE;
                    if (rec > SEARCH_MAX)
                        rec = SEARCH_MAX;
                    sp = 0;
                    break;
                }
            }
        }
        if (!l_effect_flag[i] && !r_effect_flag[i])
            Both_Lost_Time++;
    }
}

/* ==== 中线: 双边中点 / 单边+动态半宽 ==== */
static void calc_midline(void)
{
    uint8_t i;
    int16_t est, sw = 0, cw = 0;
    for (i = 100; i < MT9V034_HEIGHT; i++)
    {
        if (l_effect_flag[i] && r_effect_flag[i])
        {
            int16_t w = r_border[i] - l_border[i];
            if (w > 30 && w < 180)
            {
                sw += (int16_t)(w / 2);
                cw++;
            }
        }
    }
    if (cw >= 3)
    {
        int16_t m = (int16_t)(sw / cw);
        g_hw_bottom = (m * 2 + g_hw_bottom * 8 + 5) / 10;
    }
    for (i = 0; i < MT9V034_HEIGHT; i++)
    {
        int16_t hw = (int16_t)(((int32_t)g_hw_bottom * (int32_t)i * 2 / 3) / 119 + (int32_t)g_hw_bottom / 3);
        hw = (int16_t)(((int32_t)hw * HALF_WIDTH_SCALE + 5) / 10);
        if (hw < 8)
            hw = 8;
        if (hw > 90)
            hw = 90;
        if (l_effect_flag[i] && r_effect_flag[i])
            image_position[i] = (l_border[i] + r_border[i]) / 2;
        else if (l_effect_flag[i])
        {
            est = l_border[i] + hw;
            image_position[i] = (est > SEARCH_MAX) ? SEARCH_MAX : (est < 1 ? 1 : est);
        }
        else if (r_effect_flag[i])
        {
            est = r_border[i] - hw;
            image_position[i] = (est > SEARCH_MAX) ? SEARCH_MAX : (est < 1 ? 1 : est);
        }
        else
            image_position[i] = MT9V034_WIDTH / 2;
        g_mid_out[i] = image_position[i];
    }
}

/* ==== 误差: 全图下半部均值 + 强平滑(20%新) ==== */
static int16_t calc_error(void)
{
    int32_t sum = 0;
    int16_t est;
    uint8_t i;
    int16_t cnt = 0;
    for (i = (uint8_t)(MT9V034_HEIGHT / 2); i < MT9V034_HEIGHT; i++)
    {
        if (l_effect_flag[i] && r_effect_flag[i])
            est = (l_border[i] + r_border[i]) / 2;
        else if (l_effect_flag[i])
            est = l_border[i] + g_hw_bottom;
        else if (r_effect_flag[i])
            est = r_border[i] - g_hw_bottom;
        else
            continue;
        sum += (int32_t)est;
        cnt++;
    }
    if (cnt < 20)
        return g_err_smooth;
    {
        int16_t raw = (int16_t)(MT9V034_WIDTH / 2) - (int16_t)(sum / (int32_t)cnt);
        g_err_smooth = (raw * 20 + g_err_smooth * 80 + 50) / 100; /* 20%新 */
        return g_err_smooth;
    }
}

/* ==== 元素检测 ==== */
static void detect_element(void)
{
    road_type.straight = road_type.bend = road_type.cross = 0;
    if (cross_phase)
        road_type.cross = 1;
    else if (huandao_state)
        road_type.right_cirque = 1;
    else
    {
        int16_t d = l_effect_num - r_effect_num;
        if (d > 20 || d < -20)
            road_type.bend = 1;
        else
            road_type.straight = 1;
    }
}

/* ==== 十字检测 ==== */
static void find_down_points(void)
{
    int16_t i, st = first_end + 7;
    l_down_point = r_down_point = 0;
    for (i = IMAGE_H - 1 - 3; i >= st; i--)
    {
        if (!l_down_point && l_effect_flag[i] && !l_effect_flag[i - 5] && !l_effect_flag[i - 6] && l_effect_flag[i + 1] && l_effect_flag[i + 2] && myabs(l_border[i] - l_border[i - 5]) >= DOWN_JUMP_TH && myabs(l_border[i] - l_border[i - 6]) >= DOWN_JUMP_TH && myabs(l_border[i] - l_border[i + 1]) <= DOWN_STABLE_TH && myabs(l_border[i] - l_border[i + 2]) <= DOWN_STABLE_TH)
            l_down_point = i;
        if (!r_down_point && r_effect_flag[i] && !r_effect_flag[i - 5] && !r_effect_flag[i - 6] && r_effect_flag[i + 1] && r_effect_flag[i + 2] && myabs(r_border[i] - r_border[i - 5]) >= DOWN_JUMP_TH && myabs(r_border[i] - r_border[i - 6]) >= DOWN_JUMP_TH && myabs(r_border[i] - r_border[i + 1]) <= DOWN_STABLE_TH && myabs(r_border[i] - r_border[i + 2]) <= DOWN_STABLE_TH)
            r_down_point = i;
        if (l_down_point && r_down_point)
            break;
    }
    if (l_down_point && r_down_point && myabs(l_down_point - r_down_point) >= CROSS_TEAR_TH)
        l_down_point = r_down_point = 0;
}
static void find_up_points(void)
{
    int16_t i, ls = l_down_point ? l_down_point - 1 : IMAGE_H / 2, rs = r_down_point ? r_down_point - 1 : IMAGE_H / 2;
    l_up_point = r_up_point = 0;
    if (ls >= IMAGE_H - 5)
        ls = IMAGE_H - 6;
    if (rs >= IMAGE_H - 5)
        rs = IMAGE_H - 6;
    for (i = ls; i >= first_end + 4; i--)
        if (l_effect_flag[i] && l_effect_flag[i - 1] && l_effect_flag[i - 2] && !l_effect_flag[i + 4] && !r_effect_flag[i + 5] && myabs(l_border[i] - l_border[i - 1]) <= CROSS_STABLE_TH && myabs(l_border[i - 1] - l_border[i - 2]) <= CROSS_STABLE_TH && myabs(l_border[i - 2] - l_border[i - 3]) <= CROSS_STABLE_TH && (l_border[i] - l_border[i + 3]) >= UP_JUMP_TH2 && (l_border[i] - l_border[i + 4]) >= UP_JUMP_TH2)
        {
            l_up_point = i;
            break;
        }
    for (i = rs; i >= first_end + 4; i--)
        if (r_effect_flag[i] && r_effect_flag[i - 1] && r_effect_flag[i - 2] && !l_effect_flag[i + 4] && !r_effect_flag[i + 5] && myabs(r_border[i] - r_border[i - 1]) <= CROSS_STABLE_TH && myabs(r_border[i - 1] - r_border[i - 2]) <= CROSS_STABLE_TH && myabs(r_border[i - 2] - r_border[i - 3]) <= CROSS_STABLE_TH && (r_border[i] - r_border[i + 3]) <= -UP_JUMP_TH2 && (r_border[i] - r_border[i + 4]) <= -UP_JUMP_TH2)
        {
            r_up_point = i;
            break;
        }
    if (l_up_point && r_up_point && myabs(l_up_point - r_up_point) >= CROSS_TEAR_TH)
        l_up_point = r_up_point = 0;
}
void cross_detect(void)
{
    int16_t i, li = 0, ri = 0;
    uint8_t cf = 0, cc = 0;
    cross_state = CROSS_NONE;
    for (i = IMAGE_H - 1; i > first_end; i--)
    {
        if (!l_effect_flag[i])
            li++;
        if (!r_effect_flag[i])
            ri++;
    }
    l_invalid_cnt = li;
    r_invalid_cnt = ri;
    if (cross_phase)
    {
        find_down_points();
        find_up_points();
        cc = (l_up_point > 0) + (r_up_point > 0) + (l_down_point > 0) + (r_down_point > 0);
        if (li >= CROSS_INVALID_MIN && ri >= CROSS_INVALID_MIN && cc >= 3)
        {
            cross_state = CROSS_CONFIRMED;
            cf = 1;
        }
    }
    else
    {
        if (li >= CROSS_INVALID_MIN && ri >= CROSS_INVALID_MIN)
        {
            find_down_points();
            find_up_points();
            cc = (l_up_point > 0) + (r_up_point > 0) + (l_down_point > 0) + (r_down_point > 0);
            if (cc >= 3)
            {
                cross_state = CROSS_CONFIRMED;
                cf = 1;
            }
        }
        if (!cf)
            l_up_point = r_up_point = l_down_point = r_down_point = 0;
    }
    switch (cross_phase)
    {
    case CROSS_PHASE_NONE:
        if (cf)
            cross_phase = CROSS_PHASE_FOUND;
        break;
    case CROSS_PHASE_FOUND:
        if (li >= CROSS_ENTERING_TH && ri >= CROSS_ENTERING_TH)
            cross_phase = CROSS_PHASE_ENTERING;
        break;
    case CROSS_PHASE_ENTERING:
        if (li < CROSS_IN_BEND_TH && ri < CROSS_IN_BEND_TH)
            cross_phase = CROSS_PHASE_IN_BEND;
        break;
    case CROSS_PHASE_IN_BEND:
        if (li >= CROSS_EXITING_TH && ri >= CROSS_EXITING_TH)
            cross_phase = CROSS_PHASE_EXITING;
        else if (li < CROSS_INVALID_MIN || ri < CROSS_INVALID_MIN)
            cross_phase = CROSS_PHASE_NONE;
        break;
    case CROSS_PHASE_EXITING:
        if ((li < CROSS_IN_BEND_TH && ri < CROSS_IN_BEND_TH) || (li < CROSS_INVALID_MIN && ri < CROSS_INVALID_MIN))
            cross_phase = CROSS_PHASE_NONE;
        break;
    default:
        cross_phase = CROSS_PHASE_NONE;
    }
    if (cross_phase)
    {
        if (!l_up_point && l_up_prev)
            l_up_point = l_up_prev;
        if (!r_up_point && r_up_prev)
            r_up_point = r_up_prev;
        if (!l_down_point && l_dp_prev)
            l_down_point = l_dp_prev;
        if (!r_down_point && r_dp_prev)
            r_down_point = r_dp_prev;
    }
    l_dp_prev = l_down_point;
    r_dp_prev = r_down_point;
    l_up_prev = l_up_point;
    r_up_prev = r_up_point;
}

static void fill_line_2p(int16_t r1, int16_t c1, int16_t r2, int16_t c2, int16_t *b, int8_t *e)
{
    int16_t i, rs, re, cv, nm, dn;
    if (r1 == r2)
        return;
    if (r1 < r2)
    {
        rs = r1;
        re = r2;
    }
    else
    {
        rs = r2;
        re = r1;
    }
    if (rs < 0)
        rs = 0;
    if (re >= IMAGE_H)
        re = IMAGE_H - 1;
    nm = c2 - c1;
    dn = r2 - r1;
    if (dn == 0)
        dn = 1;
    for (i = rs; i <= re; i++)
    {
        cv = c1 + (int16_t)(((int32_t)(i - r1) * nm) / dn);
        cv = limit_ab(cv, SEARCH_MIN, SEARCH_MAX);
        b[i] = cv;
        e[i] = 1;
    }
}
void cross_fill(void)
{
    int16_t i, hi, nv, lft = 0, lfb = 0, rft = 0, rfb = 0;
    if (!cross_phase)
        return;
    if (l_down_point)
    {
        fill_line_2p(l_down_point, l_border[l_down_point], IMAGE_H - 1, SEARCH_MIN, l_border, l_effect_flag);
        lft = l_down_point;
        lfb = IMAGE_H - 1;
    }
    if (r_down_point)
    {
        fill_line_2p(r_down_point, r_border[r_down_point], IMAGE_H - 1, SEARCH_MAX, r_border, r_effect_flag);
        rft = r_down_point;
        rfb = IMAGE_H - 1;
    }
    if (lft && lfb && !rft)
        for (i = lft; i <= lfb; i++)
            if (!r_effect_flag[i])
            {
                hi = i;
                if (hi < 0)
                    hi = 0;
                if (hi > 119)
                    hi = 119;
                nv = l_border[i] + 2 * (int16_t)Half_Road_Wide[hi];
                if (nv > SEARCH_MAX)
                    nv = SEARCH_MAX;
                r_border[i] = nv;
                r_effect_flag[i] = 1;
            }
    if (rft && rfb && !lft)
        for (i = rft; i <= rfb; i++)
            if (!l_effect_flag[i])
            {
                hi = i;
                if (hi < 0)
                    hi = 0;
                if (hi > 119)
                    hi = 119;
                nv = r_border[i] - 2 * (int16_t)Half_Road_Wide[hi];
                if (nv < SEARCH_MIN)
                    nv = SEARCH_MIN;
                l_border[i] = nv;
                l_effect_flag[i] = 1;
            }
    {
        int16_t ct = IMAGE_H - 1, cb = 0;
        if (lft)
        {
            if (lft < ct)
                ct = lft;
            if (lfb > cb)
                cb = lfb;
        }
        if (rft)
        {
            if (rft < ct)
                ct = rft;
            if (rfb > cb)
                cb = rfb;
        }
        if (ct <= cb)
            for (i = ct; i <= cb; i++)
            {
                hi = i;
                if (hi < 0)
                    hi = 0;
                if (hi > 119)
                    hi = 119;
                if (!l_effect_flag[i] && r_effect_flag[i])
                {
                    nv = r_border[i] - 2 * (int16_t)Half_Road_Wide[hi];
                    if (nv < SEARCH_MIN)
                        nv = SEARCH_MIN;
                    l_border[i] = nv;
                    l_effect_flag[i] = 1;
                }
                else if (!r_effect_flag[i] && l_effect_flag[i])
                {
                    nv = l_border[i] + 2 * (int16_t)Half_Road_Wide[hi];
                    if (nv > SEARCH_MAX)
                        nv = SEARCH_MAX;
                    r_border[i] = nv;
                    r_effect_flag[i] = 1;
                }
                else if (!l_effect_flag[i] && !r_effect_flag[i])
                {
                    l_border[i] = IMAGE_W / 2 - (int16_t)Half_Road_Wide[hi];
                    r_border[i] = IMAGE_W / 2 + (int16_t)Half_Road_Wide[hi];
                    if (l_border[i] < SEARCH_MIN)
                        l_border[i] = SEARCH_MIN;
                    if (r_border[i] > SEARCH_MAX)
                        r_border[i] = SEARCH_MAX;
                    l_effect_flag[i] = r_effect_flag[i] = 1;
                }
            }
    }
}

/* ==== 环岛检测 ==== */
static int16_t hd_get_rf(void)
{
    int16_t i;
    for (i = IMAGE_H - 1; i > first_end; i--)
        if (r_effect_flag[i])
            return i;
    return -1;
}
static uint8_t hd_chk_lc(void)
{
    int16_t i, vc = 0;
    uint8_t st = 0;
    for (i = IMAGE_H - 1; i > first_end; i--)
    {
        if (!st)
        {
            if (l_effect_flag[i])
            {
                st = 1;
                vc = 1;
            }
        }
        else
        {
            if ((l_border[i] - l_border[i + 1]) >= HD_L_CONT_JUMP_TH)
                return 0;
            vc++;
        }
    }
    return (vc >= HD_L_EFFECT_MIN) ? 1 : 0;
}
static uint8_t hd_chk_rl(int16_t fr, int16_t st)
{
    int16_t i;
    if (st < 1)
        st = 1;
    if (fr >= IMAGE_H)
        fr = IMAGE_H - 1;
    for (i = fr; i > first_end; i -= st)
        if (!r_effect_flag[i] && !l_effect_flag[i])
            return 0;
    return 1;
}
static void hd_frdp(void)
{
    int16_t i;
    hd_r_dp = 0;
    for (i = IMAGE_H - 1 - 3; i >= HD_R_DOWN_MIN_ROW; i--)
        if (r_effect_flag[i] && r_effect_flag[i + 1] && r_effect_flag[i + 2] && !r_effect_flag[i - 3] && !r_effect_flag[i - 4] && myabs(r_border[i] - r_border[i + 1]) <= HD_R_STABLE_TH && myabs(r_border[i + 1] - r_border[i + 2]) <= HD_R_STABLE_TH && myabs(r_border[i] - r_border[i - 3]) >= HD_R_STABLE_TH)
        {
            hd_r_dp = i;
            break;
        }
}
static void hd_frup(void)
{
    int16_t i;
    hd_r_up = 0;
    for (i = IMAGE_H - 2; i > first_end + 1; i--)
        if (r_effect_flag[i] && r_effect_flag[i - 1] && !r_effect_flag[i + 1] && r_border[i] < HD_R_UP_MAX_COL)
        {
            hd_r_up = i;
            break;
        }
}

/* Front_Car 策略: 一侧边界很完整(>80行) + 另一侧几乎全丢(<8行) = 环岛 */
#define RING_VALID_TH 80  /* "直"侧最少有效行 */
#define RING_LOST_TH   8  /* "丢"侧最多有效行 */

void huandao_detect(void)
{
    int16_t rf;
    switch (huandao_state)
    {
    case HUANDAO_NONE:
    {   /* 右环岛: 左侧直, 右侧丢, 且右边界第一有效行靠上(>110排除出口) */
        int16_t rf2 = hd_get_rf();
        if (l_effect_num > RING_VALID_TH && r_effect_num < RING_LOST_TH
            && rf2 >= 0 && rf2 < HD_R_START_MIN_ROW)
            huandao_state = HUANDAO_STATE1;
    }   break;
    case HUANDAO_STATE1:
        rf = hd_get_rf();
        if (rf < 0 || rf >= HD_R_START_MIN_ROW) break;
        huandao_state = HUANDAO_STATE2; break;
    case HUANDAO_STATE2:
        rf = hd_get_rf();
        if (rf > HD_R_START_MIN_ROW) huandao_state = HUANDAO_STATE2B; break;
    case HUANDAO_STATE2B:
        rf = hd_get_rf(); if (rf < 0 || rf >= HD_R_START_MIN_ROW) break;
        hd_frup(); if (hd_r_up) huandao_state = HUANDAO_STATE3; break;
    case HUANDAO_STATE3:
        if ((IMAGE_H - 1 - white_length_max[0][0]) < 80) huandao_state = HUANDAO_STATE4; break;
    case HUANDAO_STATE4:
        if ((IMAGE_H - 1 - white_length_max[0][0]) > 80) huandao_state = HUANDAO_STATE5; break;
    case HUANDAO_STATE5:
    {   int16_t ii, lwc = white_length_max[1][0];
        hd_l_tp = 0;
        for (ii = IMAGE_H - 3; ii >= first_end + 2; ii--)
            if (l_effect_flag[ii] && l_effect_flag[ii - 2] && l_effect_flag[ii + 2])
            { int16_t di = myabs(l_border[ii] - lwc), du = myabs(l_border[ii - 2] - lwc), dd = myabs(l_border[ii + 2] - lwc);
              if (du > di && dd > di) { hd_l_tp = ii; break; } }
        hd_l_up = hd_l_tp; if (!hd_l_tp) huandao_state = HUANDAO_STATE6;
    } break;
    case HUANDAO_STATE6:
        hd_frup(); if (hd_r_up > 0) huandao_state = HUANDAO_STATE7; break;
    case HUANDAO_STATE7:
        hd_frup(); if (!hd_r_up) { huandao_state = HUANDAO_NONE; hd_r_dp = hd_r_up = hd_l_up = hd_l_tp = 0; } break;
    }
}
void huandao_fill(void)
{
    int16_t i, hi, nv;
    if (huandao_state == HUANDAO_STATE1 || huandao_state == HUANDAO_STATE2 || huandao_state == HUANDAO_STATE2B)
        for (i = IMAGE_H - 1; i > first_end; i--)
            if (l_effect_flag[i])
            {
                hi = i;
                if (hi < 0)
                    hi = 0;
                if (hi > 119)
                    hi = 119;
                nv = l_border[i] + 2 * (int16_t)Half_Road_Wide[hi];
                if (nv > SEARCH_MAX)
                    nv = SEARCH_MAX;
                r_border[i] = nv;
                r_effect_flag[i] = 1;
            }
    if (huandao_state == HUANDAO_STATE7)
        for (i = IMAGE_H - 1; i > first_end; i--)
            if (l_effect_flag[i])
            {
                hi = i;
                if (hi < 0)
                    hi = 0;
                if (hi > 119)
                    hi = 119;
                nv = l_border[i] + 2 * (int16_t)Half_Road_Wide[hi] + HD_HALF_WIDTH_RIGHT_OFFSET;
                if (nv > SEARCH_MAX)
                    nv = SEARCH_MAX;
                r_border[i] = nv;
                r_effect_flag[i] = 1;
            }
    if (huandao_state == HUANDAO_STATE4 || huandao_state == HUANDAO_STATE5)
    {
        int16_t rb = IMAGE_H - 1, cb = (l_effect_flag[IMAGE_H - 1]) ? l_border[IMAGE_H - 1] : SEARCH_MIN, rt = 0, ct = 188, cv;
        for (i = rt; i <= rb; i++)
        {
            cv = ct + (int16_t)(((int32_t)(cb - ct) * (i - rt)) / (rb - rt));
            cv = limit_ab(cv, SEARCH_MIN, SEARCH_MAX);
            l_border[i] = cv;
            l_effect_flag[i] = 1;
        }
        for (i = first_end + 1; i < IMAGE_H; i++)
        {
            r_border[i] = SEARCH_MAX;
            r_effect_flag[i] = 1;
        }
    }
}

/* ==== 左环岛 (镜像右环岛) ==== */
static int16_t lhd_get_lf(void)
{
    int16_t i;
    for (i = IMAGE_H - 1; i > first_end; i--)
        if (l_effect_flag[i]) return i;
    return -1;
}
static uint8_t lhd_chk_rc(void)
{
    int16_t i, vc = 0;
    uint8_t st = 0;
    for (i = IMAGE_H - 1; i > first_end; i--)
    {
        if (!st) { if (r_effect_flag[i]) { st = 1; vc = 1; } }
        else { if ((r_border[i + 1] - r_border[i]) >= HD_R_CONT_JUMP_TH) return 0; vc++; }
    }
    return (vc >= HD_R_EFFECT_MIN) ? 1 : 0;
}
static uint8_t lhd_chk_lr(int16_t fr, int16_t st)
{
    int16_t i;
    if (st < 1) st = 1;
    if (fr >= IMAGE_H) fr = IMAGE_H - 1;
    for (i = fr; i > first_end; i -= st)
        if (!l_effect_flag[i] && !r_effect_flag[i]) return 0;
    return 1;
}
static void lhd_fldp(void)
{
    int16_t i;
    l_hd_l_dp = 0;
    for (i = IMAGE_H - 1 - 3; i >= HD_R_DOWN_MIN_ROW; i--)
        if (l_effect_flag[i] && l_effect_flag[i + 1] && l_effect_flag[i + 2] && !l_effect_flag[i - 3] && !l_effect_flag[i - 4] && myabs(l_border[i] - l_border[i + 1]) <= HD_R_STABLE_TH && myabs(l_border[i + 1] - l_border[i + 2]) <= HD_R_STABLE_TH && myabs(l_border[i] - l_border[i - 3]) >= HD_R_STABLE_TH)
        { l_hd_l_dp = i; break; }
}
static void lhd_flup(void)
{
    int16_t i;
    l_hd_l_up = 0;
    for (i = IMAGE_H - 2; i > first_end + 1; i--)
        if (l_effect_flag[i] && l_effect_flag[i - 1] && !l_effect_flag[i + 1] && l_border[i] > HD_L_UP_MAX_COL)
        { l_hd_l_up = i; break; }
}

/* 左环岛 (Front_Car 策略: 右侧直 + 左侧丢) */
void left_huandao_detect(void)
{
    int16_t lf;
    switch (l_huandao_state)
    {
    case HUANDAO_NONE:
    {   int16_t lf2 = lhd_get_lf();
        if (r_effect_num > RING_VALID_TH && l_effect_num < RING_LOST_TH
            && lf2 >= 0 && lf2 < HD_R_START_MIN_ROW)
            l_huandao_state = HUANDAO_STATE1;
    }   break;
    case HUANDAO_STATE1:
        lf = lhd_get_lf(); if (lf < 0 || lf >= HD_R_START_MIN_ROW) break;
        l_huandao_state = HUANDAO_STATE2; break;
    case HUANDAO_STATE2:
        lf = lhd_get_lf(); if (lf > HD_R_START_MIN_ROW) l_huandao_state = HUANDAO_STATE2B; break;
    case HUANDAO_STATE2B:
        lf = lhd_get_lf(); if (lf < 0 || lf >= HD_R_START_MIN_ROW) break;
        lhd_flup(); if (l_hd_l_up) l_huandao_state = HUANDAO_STATE3; break;
    case HUANDAO_STATE3:
        if ((IMAGE_H - 1 - white_length_max[0][0]) < 80) l_huandao_state = HUANDAO_STATE4; break;
    case HUANDAO_STATE4:
        if ((IMAGE_H - 1 - white_length_max[0][0]) > 80) l_huandao_state = HUANDAO_STATE5; break;
    case HUANDAO_STATE5:
    {   int16_t ii, lwc = white_length_max[1][0];
        l_hd_r_tp = 0;
        for (ii = IMAGE_H - 3; ii >= first_end + 2; ii--)
            if (r_effect_flag[ii] && r_effect_flag[ii - 2] && r_effect_flag[ii + 2])
            { int16_t di = myabs(r_border[ii] - lwc), du = myabs(r_border[ii - 2] - lwc), dd = myabs(r_border[ii + 2] - lwc);
              if (du > di && dd > di) { l_hd_r_tp = ii; break; } }
        l_hd_r_up = l_hd_r_tp; if (!l_hd_r_tp) l_huandao_state = HUANDAO_STATE6;
    } break;
    case HUANDAO_STATE6:
        lhd_flup(); if (l_hd_l_up > 0) l_huandao_state = HUANDAO_STATE7; break;
    case HUANDAO_STATE7:
        lhd_flup(); if (!l_hd_l_up) { l_huandao_state = HUANDAO_NONE; l_hd_l_dp = l_hd_l_up = l_hd_r_up = l_hd_r_tp = 0; } break;
    }
}

void left_huandao_fill(void)
{
    int16_t i, hi, nv;
    if (l_huandao_state == HUANDAO_STATE1 || l_huandao_state == HUANDAO_STATE2 || l_huandao_state == HUANDAO_STATE2B)
        for (i = IMAGE_H - 1; i > first_end; i--)
            if (r_effect_flag[i])
            { hi = i; if (hi < 0) hi = 0; if (hi > 119) hi = 119;
              nv = r_border[i] - 2 * (int16_t)Half_Road_Wide[hi];
              if (nv < SEARCH_MIN) nv = SEARCH_MIN; l_border[i] = nv; l_effect_flag[i] = 1; }
    if (l_huandao_state == HUANDAO_STATE7)
        for (i = IMAGE_H - 1; i > first_end; i--)
            if (r_effect_flag[i])
            { hi = i; if (hi < 0) hi = 0; if (hi > 119) hi = 119;
              nv = r_border[i] - 2 * (int16_t)Half_Road_Wide[hi] - HD_HALF_WIDTH_RIGHT_OFFSET;
              if (nv < SEARCH_MIN) nv = SEARCH_MIN; l_border[i] = nv; l_effect_flag[i] = 1; }
    if (l_huandao_state == HUANDAO_STATE4 || l_huandao_state == HUANDAO_STATE5)
    {
        int16_t rb = IMAGE_H - 1, cb = (r_effect_flag[IMAGE_H - 1]) ? r_border[IMAGE_H - 1] : SEARCH_MAX, rt = 0, ct = 1, cv;
        for (i = rt; i <= rb; i++)
        { cv = ct + (int16_t)(((int32_t)(cb - ct) * (i - rt)) / (rb - rt)); cv = limit_ab(cv, SEARCH_MIN, SEARCH_MAX); r_border[i] = cv; r_effect_flag[i] = 1; }
        for (i = first_end + 1; i < IMAGE_H; i++) { l_border[i] = SEARCH_MIN; l_effect_flag[i] = 1; }
    }
}

/* ==== 障碍检测: 赛道内连续暗像素 ≥ OBS_DW_MIN 即判定 ==== */
#define OBS_DW_MIN 15
#define OBS_DW_MAX 120
#define OBS_DARK_THRESH 100 /* 低于此灰度值算"暗" */

static void detect_obstacle(void)
{
    int16_t r, c, start, dark_cnt;
    static uint8_t obs_lost = 0; /* 连续丢失帧计数 */
    uint8_t found = 0;

    /* 只在直道检测, 弯道边界不全易误判 */
    if (!road_type.straight)
    {
        obs_lost++;
        if (obs_lost > 15)
        {
            g_obstacle_detected = 0;
            obs_lost = 0;
        }
        return;
    }

    for (r = TARGET_ROW_START; r >= TARGET_ROW_END; r -= TARGET_ROW_STEP)
    {
        int16_t rl, rr;
        rl = l_effect_flag[r] ? l_border[r] : SEARCH_MIN;
        rr = r_effect_flag[r] ? r_border[r] : SEARCH_MAX;
        if (rl > rr || rr - rl < 30)
            continue;

        /* 扫描连续暗像素 */
        dark_cnt = 0;
        start = 0;
        for (c = rl; c <= rr; c++)
        {
            if (mt9v034_image[(uint16_t)r][(uint16_t)c] <= OBS_DARK_THRESH)
            {
                if (!dark_cnt)
                    start = c;
                dark_cnt++;
            }
            else
            {
                if (dark_cnt >= OBS_DW_MIN && dark_cnt <= OBS_DW_MAX)
                {
                    g_obstacle_center_x = (uint8_t)(start + dark_cnt / 2);
                    g_obstacle_width = (uint8_t)dark_cnt;
                    found = 1;
                }
                dark_cnt = 0;
            }
        }
        /* 行末检查 */
        if (dark_cnt >= OBS_DW_MIN && dark_cnt <= OBS_DW_MAX)
        {
            g_obstacle_center_x = (uint8_t)(start + dark_cnt / 2);
            g_obstacle_width = (uint8_t)dark_cnt;
            found = 1;
        }
    }

    /* 保持: 检测到立即置1, 连续丢5帧才清零 */
    if (found)
    {
        g_obstacle_detected = 1;
        obs_lost = 0;
    }
    else
    {
        obs_lost++;
        if (obs_lost > 15)
        {
            g_obstacle_detected = 0;
            obs_lost = 0;
        }
    }
}

/* ==== 占位 ==== */
void target_detect(void) {}
void laser_off_handler(void) {}
void element_detect(void) { detect_element(); }

/* ==== image_process ==== */
void image_process(void)
{
    if (!mt9v034_frame_ready)
        return;
    search_white(&mt9v034_image[IMAGE_H - 1][SEARCH_MIN], (uint16_t)(SEARCH_MAX - SEARCH_MIN + 1));
    search_longest_white_col();
    search_border();
    /* 元素检测 (互斥: 环岛期间不检十字, 十字期间不检环岛) */
#if HUANDAO_ENABLE
    if (!huandao_state)
        cross_detect();
    if (!cross_phase)
        huandao_detect();
#else
    cross_detect();
#endif
    /* 左环岛 (先右后左, 互斥: 已检测到右环岛时跳过左) */
#if HUANDAO_ENABLE
    if (!huandao_state && !cross_phase) left_huandao_detect();
#endif
    /* 障碍检测 (环岛/十字期间跳过, 防误判) */
    if (huandao_state == HUANDAO_NONE && l_huandao_state == HUANDAO_NONE && cross_phase == CROSS_PHASE_NONE)
        detect_obstacle();
    /* 补线 (修改边界, 必须在 calc_midline 之前) */
    if (!huandao_state && !l_huandao_state) cross_fill();
    if (!cross_phase) { huandao_fill(); left_huandao_fill(); }
    /* 中线+误差 */
    calc_midline();
    Image_Error = calc_error();
    posi = Image_Error;
    detect_element();
    g_track_valid = 1;
    mt9v034_frame_ready = 0;
}

/* ==== IPS 调试 ==== */
extern float speed_base;
void debug_ips_display(void)
{
    uint16_t row;
    const char *elem;
    int16_t y;
    uint16_t px;
    if (!g_track_valid)
        return;
    ips_show_gray_image(10, 0, (const uint8_t *)mt9v034_image, IMAGE_W, IMAGE_H, IMAGE_W, IMAGE_H, 0);
    for (y = 0; y < IMAGE_H; y++)
    {
        if (l_effect_flag[y])
        {
            px = (uint16_t)(10 + (uint16_t)l_border[y]);
            if (px < (uint16_t)(10 + IMAGE_W))
                ips_draw_point(px, (uint16_t)y, 0x07E0);
        }
        if (r_effect_flag[y])
        {
            px = (uint16_t)(10 + (uint16_t)r_border[y]);
            if (px < (uint16_t)(10 + IMAGE_W))
                ips_draw_point(px, (uint16_t)y, 0x07FF);
        }
        px = (uint16_t)(10 + (uint16_t)g_mid_out[y]);
        if (px < (uint16_t)(10 + IMAGE_W))
            ips_draw_point(px, (uint16_t)y, 0xF800);
    }
    row = 128;
    if (road_type.cross)
        elem = "CROSS";
    else if (road_type.right_cirque)
        elem = "RING";
    else if (road_type.bend)
        elem = (l_effect_num > r_effect_num) ? "RIGHT" : "LEFT";
    else
        elem = "STRAIGHT";
    ips_show_string(10, row, "E:");
    ips_show_string(40, row, elem);
    row += 18;
    ips_show_string(10, row, "Err:");
    ips_show_int(55, row, (int32_t)Image_Error, 4);
    ips_show_string(100, row, "Spd:");
    ips_show_int(145, row, (int32_t)speed_base, 3);
    row += 18;
    {
        extern float roll, pitch, yaw;
        ips_show_string(10, row, "r:");
        ips_show_int(28, row, (int32_t)roll, 3);
        ips_show_string(55, row, "p:");
        ips_show_int(73, row, (int32_t)pitch, 3);
        ips_show_string(100, row, "y:");
        ips_show_int(118, row, (int32_t)yaw, 3);
        ips_show_string(145, row, "H");
        ips_show_int(155, row, (int32_t)huandao_state, 1);
        ips_show_string(162, row, "h");
        ips_show_int(172, row, (int32_t)l_huandao_state, 1);
    }
    row += 18;
    if (g_obstacle_detected)
    {
        ips_show_string(10, row, "OBS!");
        ips_show_int(55, row, (int32_t)g_obstacle_center_x, 3);
        ips_show_string(95, row, "w:");
        ips_show_int(115, row, (int32_t)g_obstacle_width, 3);
    }
    row += 18;
    ips_show_string(10, row, "HW:");
    ips_show_int(40, row, (int32_t)g_hw_bottom, 3);
    ips_show_string(80, row, "W:");
    ips_show_int(100, row, (int32_t)(l_effect_num + r_effect_num), 3);
}

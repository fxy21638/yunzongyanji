#include "trail.h"
#include "main.h"

#define TRACK_LOOKAHEAD_Y_NEAR (MT9V034_HEIGHT - 22)
#define TRACK_LOOKAHEAD_Y_FAR  (MT9V034_HEIGHT / 2)
#define TRACK_EDGE_NEAR_TH     3
#define TRACK_WIDE_TH          (MT9V034_WIDTH * 7 / 10)
#define TRACK_TURN_SHIFT       28
#define TRACK_MIN_VALID_TURN_ROWS 8
#define CROSS_MIN_STREAK       3

typedef struct
{
    int16_t k_q8;
    int16_t b_q8;
} track_line_q8_t;

uint8_t white_count = 0;
uint8_t straight_target = 0;
uint8_t white_segments[20] = {0};
uint8_t time_search = 0;

TRACK_ELEMENT track_element = NONE;
TRACK_ELEMENT track_element_P = NONE;
TRACK_ELEMENT current_element = NONE;
uint8_t track_midpoint_target = CENTER_POINT;
uint8_t track_midpoint_target_P = CENTER_POINT;

uint8_t start_stage = 0;
uint8_t broken_flag = 0;
int32_t judge_distance = 0;

static const char *track_element_name(TRACK_ELEMENT element)
{
    switch (element)
    {
    case NONE: return "NONE";
    case START: return "START";
    case STRAIGHT: return "STRAIGHT";
    case RIGHT_ANGLE_l: return "RIGHT_ANGLE_L";
    case RIGHT_ANGLE_r: return "RIGHT_ANGLE_R";
    case RING_l: return "RING_L";
    case RING_r: return "RING_R";
    case RING_c: return "RING_C";
    case CROSS: return "CROSS";
    case BROKEN: return "BROKEN";
    case BROKEN_RODE: return "BROKEN_ROAD";
    default: return "UNKNOWN";
    }
}

static uint8_t clamp_center_to_target(int16_t center_x)
{
    if (center_x < 0)
    {
        return track_midpoint_target_P;
    }
    if (center_x > 255)
    {
        return 255;
    }
    return (uint8_t)center_x;
}

static uint16_t get_broken_progress(void)
{
    int16_t left_abs;
    int16_t right_abs;

    left_abs = encoder_data_dir[0];
    right_abs = encoder_data_dir[1];

    if (left_abs < 0)
    {
        left_abs = -left_abs;
    }
    if (right_abs < 0)
    {
        right_abs = -right_abs;
    }

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
    {
        return 1;
    }
    return 0;
}

static int16_t find_mid_at_or_above(uint16_t y_start)
{
    int16_t y;

    for (y = (int16_t)y_start; y >= 0; y--)
    {
        if (g_track.mid[(uint16_t)y] >= 0)
        {
            return g_track.mid[(uint16_t)y];
        }
    }
    return -1;
}

static int16_t average_lane_width(uint16_t y0, uint16_t y1)
{
    uint16_t y;
    long sum = 0;
    uint16_t cnt = 0;

    if (y1 >= MT9V034_HEIGHT)
    {
        y1 = MT9V034_HEIGHT - 1;
    }

    for (y = y0; y <= y1; y++)
    {
        if (g_track.left[y] >= 0 && g_track.right[y] >= 0)
        {
            sum += (long)(g_track.right[y] - g_track.left[y] + 1);
            cnt++;
        }
    }

    if (cnt == 0)
    {
        return (int16_t)(MT9V034_WIDTH / 3);
    }
    return (int16_t)(sum / cnt);
}

static uint8_t fit_edge_line_q8(const int16_t *edge, uint16_t y0, uint16_t y1, track_line_q8_t *line)
{
    uint16_t y;
    uint16_t n = 0;
    long sum_y = 0;
    long sum_x = 0;
    long sum_yy = 0;
    long sum_xy = 0;
    long denom;
    long numer;

    if (y1 >= MT9V034_HEIGHT)
    {
        y1 = MT9V034_HEIGHT - 1;
    }
    if (y0 > y1)
    {
        return 0;
    }

    for (y = y0; y <= y1; y++)
    {
        if (edge[y] >= 0)
        {
            n++;
            sum_y += y;
            sum_x += edge[y];
            sum_yy += (long)y * y;
            sum_xy += (long)y * edge[y];
        }
    }

    if (n < 4)
    {
        return 0;
    }

    denom = (long)n * sum_yy - sum_y * sum_y;
    if (denom == 0)
    {
        return 0;
    }

    numer = (long)n * sum_xy - sum_y * sum_x;
    line->k_q8 = (int16_t)((numer << 8) / denom);
    line->b_q8 = (int16_t)(((sum_x << 8) - (long)line->k_q8 * sum_y) / (long)n);
    return 1;
}

static int16_t eval_line_q8(const track_line_q8_t *line, uint16_t y)
{
    long x_q8 = (long)line->k_q8 * y + line->b_q8;
    if (x_q8 >= 0)
    {
        return (int16_t)((x_q8 + 128) >> 8);
    }
    return (int16_t)((x_q8 - 128) >> 8);
}

static int16_t detect_cross_break_row(void)
{
    int16_t base_w;
    int16_t y;
    int16_t cross_start = -1;
    uint8_t in_cross = 0;
    uint8_t narrow_streak = 0;

    base_w = average_lane_width((uint16_t)(MT9V034_HEIGHT / 3),
                                (uint16_t)(MT9V034_HEIGHT / 2));
    if (base_w < 8)
    {
        return -1;
    }

    for (y = (int16_t)(MT9V034_HEIGHT - 1); y >= (int16_t)(MT9V034_HEIGHT / 4); y--)
    {
        if (g_track.left[(uint16_t)y] >= 0 && g_track.right[(uint16_t)y] >= 0)
        {
            int16_t w = (int16_t)(g_track.right[(uint16_t)y] - g_track.left[(uint16_t)y] + 1);
            if (w > base_w + base_w / 2)
            {
                if (!in_cross)
                {
                    in_cross = 1;
                }
                cross_start = y;
                narrow_streak = 0;
            }
            else if (in_cross)
            {
                narrow_streak++;
                if (narrow_streak >= CROSS_MIN_STREAK)
                {
                    return cross_start;
                }
            }
        }
    }

    if (in_cross && cross_start >= 0)
    {
        return cross_start;
    }

    return -1;
}

static uint8_t detect_cross_scene(void)
{
    return (detect_cross_break_row() >= 0) ? 1 : 0;
}

static TRACK_ELEMENT detect_turn_scene(void)
{
    int16_t near_mid;
    int16_t far_mid;
    int16_t lane_w;
    int16_t dx;
    uint16_t y;
    uint8_t left_edge_lost = 0;
    uint8_t right_edge_lost = 0;

    near_mid = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_NEAR);
    far_mid = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_FAR);
    if (near_mid < 0 || far_mid < 0)
    {
        return STRAIGHT;
    }

    lane_w = average_lane_width((uint16_t)(MT9V034_HEIGHT - 20), (uint16_t)(MT9V034_HEIGHT - 5));
    dx = (int16_t)(far_mid - near_mid);

    for (y = (uint16_t)(MT9V034_HEIGHT / 2); y < MT9V034_HEIGHT; y++)
    {
        if (g_track.left[y] < 0 || g_track.left[y] <= TRACK_EDGE_NEAR_TH)
        {
            left_edge_lost++;
        }
        if (g_track.right[y] < 0 || g_track.right[y] >= (int16_t)(MT9V034_WIDTH - 1 - TRACK_EDGE_NEAR_TH))
        {
            right_edge_lost++;
        }
    }

    if (dx > (lane_w / 6) && left_edge_lost >= TRACK_MIN_VALID_TURN_ROWS)
    {
        return RIGHT_ANGLE_l;
    }
    if (dx < -(lane_w / 6) && right_edge_lost >= TRACK_MIN_VALID_TURN_ROWS)
    {
        return RIGHT_ANGLE_r;
    }

    return STRAIGHT;
}

TRACK_ELEMENT track_element_judge(void)
{
    if (!g_track_valid)
    {
        return NONE;
    }

    if (g_track.feature == VISION_FEATURE_LOST)
    {
        return BROKEN;
    }
    if (g_track.feature == VISION_FEATURE_RING_LEFT)
    {
        return RING_l;
    }
    if (g_track.feature == VISION_FEATURE_RING_RIGHT)
    {
        return RING_r;
    }
    if (g_track.feature == VISION_FEATURE_CROSS || detect_cross_scene())
    {
        return CROSS;
    }
    return detect_turn_scene();
}

static uint8_t plan_straight_center(void)
{
    int16_t near_mid;
    int16_t far_mid;
    int16_t target;

    near_mid = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_NEAR);
    far_mid = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_FAR);
    if (near_mid >= 0 && far_mid >= 0)
    {
        target = (int16_t)((near_mid + far_mid * 2) / 3);
        return clamp_center_to_target(target);
    }
    if (g_track.center_x >= 0)
    {
        return clamp_center_to_target(g_track.center_x);
    }
    return track_midpoint_target_P;
}

static uint8_t plan_cross_center(void)
{
    int16_t break_row;
    track_line_q8_t left_line;
    track_line_q8_t right_line;
    uint16_t y0;
    uint16_t y1;
    int16_t left_x;
    int16_t right_x;

    break_row = detect_cross_break_row();
    if (break_row >= 12)
    {
        y0 = (uint16_t)(break_row - 28);
        y1 = (uint16_t)(break_row - 4);
        if (y0 < y1 && fit_edge_line_q8(g_track.left, y0, y1, &left_line) &&
            fit_edge_line_q8(g_track.right, y0, y1, &right_line))
        {
            uint16_t eval_y = (uint16_t)VISION_LOOKAHEAD_Y;
            if (eval_y >= MT9V034_HEIGHT) eval_y = MT9V034_HEIGHT - 1;
            left_x = eval_line_q8(&left_line, eval_y);
            right_x = eval_line_q8(&right_line, eval_y);
            return clamp_center_to_target((int16_t)((left_x + right_x) / 2));
        }
    }

    return plan_straight_center();
}

static uint8_t plan_turn_center(TRACK_ELEMENT turn_type)
{
    int16_t lane_w;
    int16_t y_ref;
    int16_t target = -1;

    lane_w = average_lane_width((uint16_t)(MT9V034_HEIGHT - 20), (uint16_t)(MT9V034_HEIGHT - 5));
    if (lane_w < 20)
    {
        lane_w = 20;
    }

    for (y_ref = (int16_t)(MT9V034_HEIGHT - 15); y_ref >= (int16_t)(MT9V034_HEIGHT / 3); y_ref--)
    {
        if (turn_type == RIGHT_ANGLE_l)
        {
            if (g_track.right[(uint16_t)y_ref] >= 0)
            {
                target = (int16_t)(g_track.right[(uint16_t)y_ref] - lane_w / 2 - TRACK_TURN_SHIFT / 2);
                break;
            }
        }
        else
        {
            if (g_track.left[(uint16_t)y_ref] >= 0)
            {
                target = (int16_t)(g_track.left[(uint16_t)y_ref] + lane_w / 2 + TRACK_TURN_SHIFT / 2);
                break;
            }
        }
    }

    if (target < 0)
    {
        target = g_track.center_x;
    }
    return clamp_center_to_target(target);
}

void track_straight_target(uint8_t position)
{
    position = position;
    straight_target = plan_straight_center();
    track_midpoint_target = straight_target;
}

static void report_track_element_if_changed(void)
{
    if (track_element != track_element_P)
    {
        printf("ELEMENT:%s center:%u err:%d valid:%u\r\n",
               track_element_name(track_element),
               track_midpoint_target,
               g_track.error_x,
               g_track.valid_rows);
    }
}

void track_handle(void)
{
    static uint8_t cross_exit_hold = 0;

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

    if (current_element == CROSS)
    {
        broken_flag_clear();
        track_midpoint_target = CENTER_POINT;
        track_element = CROSS;
        cross_exit_hold = 3;
    }
    else if (track_element == CROSS && cross_exit_hold > 0)
    {
        cross_exit_hold--;
        track_midpoint_target = CENTER_POINT;
    }
    else if (current_element == RIGHT_ANGLE_l || current_element == RIGHT_ANGLE_r)
    {
        broken_flag_clear();
        track_midpoint_target = plan_turn_center(current_element);
        track_element = current_element;
    }
    else if (current_element == RING_l || current_element == RING_r || current_element == RING_c)
    {
        broken_flag_clear();
        track_midpoint_target = plan_straight_center();
        track_element = current_element;
    }
    else if (current_element == BROKEN)
    {
        if (broken_judged())
        {
            track_element = BROKEN_RODE;
            gyro_target = yaw;
        }
        else
        {
            track_element = BROKEN;
            track_midpoint_target = track_midpoint_target_P;
        }
    }
    else
    {
        broken_flag_clear();
        track_straight_target(0);
        track_element = STRAIGHT;
    }

    if (track_element != BROKEN_RODE && track_element != NONE)
    {
        if (track_element == CROSS)
        {
            uint16_t smooth = (uint16_t)track_midpoint_target + (uint16_t)track_midpoint_target_P;
            track_midpoint_target = (uint8_t)((smooth + 1) / 2);
        }
        else
        {
            uint16_t smooth = (uint16_t)track_midpoint_target + (uint16_t)track_midpoint_target_P * 3;
            track_midpoint_target = (uint8_t)((smooth + 2) / 4);
        }
    }

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

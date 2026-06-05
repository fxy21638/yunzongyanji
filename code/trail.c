// Track element classification + Pure Pursuit target planning
// Uses bird's-eye view midline point set (when VISION_USE_WALLFOLLOW=1)
// Falls back to per-row mid array (original mode)

#ifndef __INTELLISENSE__
#include "ky_headfile.h"
#endif

#include "trail.h"
#include "main.h"

#define TRACK_LOOKAHEAD_Y_NEAR (MT9V034_HEIGHT - 22)
#define TRACK_LOOKAHEAD_Y_FAR  (MT9V034_HEIGHT / 2)
#define TRACK_EDGE_NEAR_TH     3
#define TRACK_WIDE_TH          (MT9V034_WIDTH * 7 / 10)

#define TRAIL_DBG_PRINTF 0
#define TRACK_TURN_SHIFT       28
#define TRACK_MIN_VALID_TURN_ROWS 8
#define CROSS_MIN_STREAK       3
#define CROSS_TOUCH_MARGIN     4
#define CROSS_WIDE_EXTRA_NUM   5

// Pure Pursuit parameters
#define PP_LOOKAHEAD_MIN  12
#define PP_LOOKAHEAD_MAX  70
#define PP_LOOKAHEAD_SCALE 4  // lookahead = speed / SCALE (pixels)

// VOFA+ firewater debug output via CDC
#define VOFA_FIREWATER 1
#if VOFA_FIREWATER
#define VOFA_FLOAT_COUNT 10
#endif

uint8_t white_count = 0;
uint8_t straight_target = 0;
uint8_t white_segments[20] = {0};
uint8_t time_search = 0;

TRACK_ELEMENT track_element = NONE;
TRACK_ELEMENT track_element_P = NONE;
TRACK_ELEMENT current_element = NONE;
uint8_t track_midpoint_target = CENTER_POINT;
uint8_t track_midpoint_target_P = CENTER_POINT;

// Pure Pursuit state
float pp_steering_angle = 0.0f;   // output steering angle (degrees)
float pp_lookahead_dist = 25.0f;  // current lookahead distance
float pp_curvature = 0.0f;        // estimated road curvature (×1000)
uint8_t pp_visible_high = 120;    // visible track distance

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

/* ================================================================
 * Pure Pursuit: find target on midline at lookahead distance
 * Returns steering angle in degrees
 * ================================================================ */
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
        if (dist < 1.0f) continue;
        diff = dist - lookahead;
        if (diff < 0.0f) diff = -diff;
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
    if (dy < 1.0f) dy = 1.0f;

    angle = atan2f(dx, dy) * 180.0f / 3.14159265358979f;
    return angle;
}

/* ================================================================
 * Compute road curvature from boundary points (bird's-eye view)
 * Uses Menger curvature on 3 sample points
 * ================================================================ */
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
        p0[0] = track->left_bev[0][0];     p0[1] = track->left_bev[0][1];
        p1[0] = track->left_bev[n / 2][0]; p1[1] = track->left_bev[n / 2][1];
        p2[0] = track->left_bev[n - 1][0]; p2[1] = track->left_bev[n - 1][1];
        curv_l = (float)pts_curvature_3pt(p0, p1, p2) / 1000.0f;
        cnt++;
    }

    if (track->right_bev_step > 10)
    {
        uint8_t p0[2], p1[2], p2[2];
        uint8_t n;
        n = track->right_bev_step;
        p0[0] = track->right_bev[0][0];     p0[1] = track->right_bev[0][1];
        p1[0] = track->right_bev[n / 2][0]; p1[1] = track->right_bev[n / 2][1];
        p2[0] = track->right_bev[n - 1][0]; p2[1] = track->right_bev[n - 1][1];
        curv_r = (float)pts_curvature_3pt(p0, p1, p2) / 1000.0f;
        cnt++;
    }

    if (cnt == 0) return 0.0f;
    if (cnt == 1) return curv_l + curv_r; // one of them is 0
    return (curv_l + curv_r) / 2.0f;
}

/* ================================================================
 * Speed decision: reduce speed based on curvature and visibility
 * Returns speed factor (0.3 to 1.0)
 * ================================================================ */
float trail_speed_factor(void)
{
    float factor;
    float abs_curv;
    float vis_factor;
    uint8_t high;

    factor = 1.0f;

    // Curvature-based reduction
    abs_curv = pp_curvature;
    if (abs_curv < 0.0f) abs_curv = -abs_curv;
    if (abs_curv > 0.05f)
    {
        factor = 0.6f;
    }
    else if (abs_curv > 0.02f)
    {
        factor = 0.8f;
    }

    // Visibility-based reduction
    high = pp_visible_high;
    vis_factor = 1.0f;
    if (high > 60)      vis_factor = 1.0f;
    else if (high > 40) vis_factor = 0.8f;
    else if (high > 20) vis_factor = 0.6f;
    else                vis_factor = 0.4f;

    // Take the more conservative factor
    if (vis_factor < factor) factor = vis_factor;
    if (factor < 0.3f) factor = 0.3f;

    return factor;
}

/* ================================================================
 * Count cross rows (width-based, for legacy detection)
 * ================================================================ */
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
        if (l < 0 || r < 0) continue;

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
    if (center_x < 0)   return track_midpoint_target_P;
    if (center_x > 255) return 255;
    return (uint8_t)center_x;
}

static uint16_t get_broken_progress(void)
{
    int16_t left_abs, right_abs;
    left_abs  = encoder_data_dir[0];
    right_abs = encoder_data_dir[1];
    if (left_abs < 0)  left_abs  = -left_abs;
    if (right_abs < 0) right_abs = -right_abs;
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
    if (judge_distance > BROKEN_LENTH) return 1;
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

    if (y1 >= MT9V034_HEIGHT) y1 = MT9V034_HEIGHT - 1;

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

    if (cnt == 0) return (int16_t)(MT9V034_WIDTH / 3);
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
    if (base_w < 8) return -1;

    cross_start = -1;
    in_cross = 0;
    narrow_streak = 0;

    for (y = (int16_t)(MT9V034_HEIGHT - 1); y >= (int16_t)(MT9V034_HEIGHT / 4); y--)
    {
        l = g_track.left[(uint16_t)y];
        r = g_track.right[(uint16_t)y];
        if (l < 0 || r < 0) continue;

        w = r - l + 1;
        if (w > base_w + base_w / 5 ||
            (w > base_w + 12 &&
             (l <= margin || r >= (int16_t)(MT9V034_WIDTH - 1 - margin))))
        {
            if (!in_cross) in_cross = 1;
            cross_start = y;
            narrow_streak = 0;
        }
        else if (in_cross)
        {
            narrow_streak++;
            if (narrow_streak >= CROSS_MIN_STREAK) return cross_start;
        }
    }

    if (in_cross && cross_start >= 0) return cross_start;
    return -1;
}

static uint8_t detect_cross_scene(void)
{
    return (detect_cross_break_row() >= 0) ? 1 : 0;
}

static TRACK_ELEMENT detect_turn_scene(void)
{
    int16_t near_mid, far_mid, lane_w, dx;
    uint16_t y;
    uint8_t left_edge_lost, right_edge_lost;
    int16_t el, er;

    near_mid = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_NEAR);
    far_mid  = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_FAR);
    if (near_mid < 0 || far_mid < 0) return STRAIGHT;

    lane_w = average_lane_width((uint16_t)(MT9V034_HEIGHT - 20), (uint16_t)(MT9V034_HEIGHT - 5));
    dx = (int16_t)(far_mid - near_mid);

    left_edge_lost  = 0;
    right_edge_lost = 0;

    for (y = (uint16_t)(MT9V034_HEIGHT / 2); y < MT9V034_HEIGHT; y++)
    {
        el = g_track.left[y];
        er = g_track.right[y];
        if (el < 0 || el <= TRACK_EDGE_NEAR_TH) left_edge_lost++;
        if (er < 0 || er >= (int16_t)(MT9V034_WIDTH - 1 - TRACK_EDGE_NEAR_TH)) right_edge_lost++;
    }

    if (dx > (lane_w / 6) && left_edge_lost >= TRACK_MIN_VALID_TURN_ROWS)  return RIGHT_ANGLE_l;
    if (dx < -(lane_w / 6) && right_edge_lost >= TRACK_MIN_VALID_TURN_ROWS) return RIGHT_ANGLE_r;

    return STRAIGHT;
}

/* ================================================================
 * Element classification
 * ================================================================ */
TRACK_ELEMENT track_element_judge(void)
{
    if (!g_track_valid) return NONE;

    if (g_track.feature == VISION_FEATURE_LOST)       return BROKEN;
    if (g_track.feature == VISION_FEATURE_RING_LEFT)  return RING_l;
    if (g_track.feature == VISION_FEATURE_RING_RIGHT) return RING_r;
    if (g_track.feature == VISION_FEATURE_CROSS || detect_cross_scene()) return CROSS;
    return detect_turn_scene();
}

/* ================================================================
 * Target planning per element type
 * ================================================================ */
static uint8_t plan_straight_center(void)
{
    int16_t near_mid, far_mid, target;

    near_mid = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_NEAR);
    far_mid  = find_mid_at_or_above(TRACK_LOOKAHEAD_Y_FAR);
    if (near_mid >= 0 && far_mid >= 0)
    {
        target = (int16_t)((near_mid + far_mid * 2) / 3);
        return clamp_center_to_target(target);
    }
    if (g_track.center_x >= 0) return clamp_center_to_target(g_track.center_x);
    return track_midpoint_target_P;
}

static uint8_t plan_turn_center(TRACK_ELEMENT turn_type)
{
    int16_t lane_w;
    int16_t y_ref;
    int16_t target;

    lane_w = average_lane_width((uint16_t)(MT9V034_HEIGHT - 20), (uint16_t)(MT9V034_HEIGHT - 5));
    if (lane_w < 20) lane_w = 20;
    target = -1;

    for (y_ref = (int16_t)(MT9V034_HEIGHT - 15); y_ref >= (int16_t)(MT9V034_HEIGHT / 3); y_ref--)
    {
        if (turn_type == RIGHT_ANGLE_l)
        {
            if (g_track.right[(uint16_t)y_ref] >= 0)
            {
                target = g_track.right[(uint16_t)y_ref] - lane_w / 2 - TRACK_TURN_SHIFT / 2;
                break;
            }
        }
        else
        {
            if (g_track.left[(uint16_t)y_ref] >= 0)
            {
                target = g_track.left[(uint16_t)y_ref] + lane_w / 2 + TRACK_TURN_SHIFT / 2;
                break;
            }
        }
    }

    if (target < 0) target = g_track.center_x;
    return clamp_center_to_target(target);
}

/* ================================================================
 * Pure Pursuit target planning (new mode)
 * Computes steering angle directly from midline point set
 * ================================================================ */
static void plan_pure_pursuit(float current_speed)
{
    float lp;

    lp = (current_speed > 5.0f) ? (current_speed / (float)PP_LOOKAHEAD_SCALE) : (float)PP_LOOKAHEAD_MIN;
    if (lp < (float)PP_LOOKAHEAD_MIN) lp = (float)PP_LOOKAHEAD_MIN;
    if (lp > (float)PP_LOOKAHEAD_MAX) lp = (float)PP_LOOKAHEAD_MAX;

    pp_lookahead_dist = lp;
    pp_steering_angle = pure_pursuit_angle(&g_track, lp);
}

void track_straight_target(uint8_t position)
{
    (void)position;
    straight_target = plan_straight_center();
    track_midpoint_target = straight_target;
}

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

    // Pack telemetry floats
    fvals[0] = pp_steering_angle;
    fvals[1] = (float)g_track.center_x;
    fvals[2] = (float)g_track.error_x;
    fvals[3] = pp_curvature;
    fvals[4] = (float)g_track.visible_high;
    fvals[5] = (float)g_track.lane_width;
    fvals[6] = (float)g_track.left_bev_step;
    fvals[7] = (float)g_track.right_bev_step;
    fvals[8] = (float)g_track.mid_step;
    fvals[9] = (float)g_track.feature;

    for (i = 0; i < VOFA_FLOAT_COUNT; i++)
    {
        fb.f = fvals[i];
        buf[i * 4 + 0] = fb.b[0];
        buf[i * 4 + 1] = fb.b[1];
        buf[i * 4 + 2] = fb.b[2];
        buf[i * 4 + 3] = fb.b[3];
    }

    // Firewater frame tail: 0x00 0x00 0x80 0x7F
    buf[VOFA_FLOAT_COUNT * 4 + 0] = 0x00;
    buf[VOFA_FLOAT_COUNT * 4 + 1] = 0x00;
    buf[VOFA_FLOAT_COUNT * 4 + 2] = 0x80;
    buf[VOFA_FLOAT_COUNT * 4 + 3] = 0x7F;

    usb_cdc_send_buffer(buf, sizeof(buf));
}

#endif // VOFA_FIREWATER

static void report_track_element_if_changed(void)
{
    // Debug output suppressed in normal operation
}

/* ================================================================
 * Main track handler
 * ================================================================ */
void track_handle(void)
{
    static uint8_t cross_exit_hold = 0;
    int16_t break_row;
    uint8_t cross_cnt;
    float speed_est;
    int16_t jump;
    uint16_t smooth;

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
    cross_cnt = count_cross_rows(&g_track);
    break_row = detect_cross_break_row();

    // Compute Pure Pursuit and curvature (for speed decision)
    speed_est = 45.0f; // estimated speed when FIXED_SPEED_DEBUG=1
    plan_pure_pursuit(speed_est);
    pp_curvature = compute_road_curvature(&g_track);
    pp_visible_high = g_track.visible_high;

    // Element-specific target planning
    if (current_element == CROSS)
    {
        broken_flag_clear();
        if (g_track.center_x >= 0)
            track_midpoint_target = clamp_center_to_target(g_track.center_x);
        else
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

    // Post-processing: jump limiter + EMA smoothing
    if (track_element != BROKEN_RODE && track_element != NONE)
    {
        jump = (int16_t)track_midpoint_target - (int16_t)track_midpoint_target_P;
        if (jump > 12)
            track_midpoint_target = (uint8_t)((int16_t)track_midpoint_target_P + 12);
        else if (jump < -12)
            track_midpoint_target = (uint8_t)((int16_t)track_midpoint_target_P - 12);

        smooth = (uint16_t)track_midpoint_target + (uint16_t)track_midpoint_target_P * 3;
        track_midpoint_target = (uint8_t)((smooth + 2) / 4);
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

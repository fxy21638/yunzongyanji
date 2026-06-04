#ifndef __VISION_TRACK_H__
#define __VISION_TRACK_H__

#ifndef __INTELLISENSE__
#include "ky_headfile.h"
#else
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned long uint32_t;
#endif

#ifndef MT9V034_WIDTH
#define MT9V034_WIDTH 188
#endif

#ifndef MT9V034_HEIGHT
#define MT9V034_HEIGHT 120
#endif

#ifndef VISION_LOOKAHEAD_Y
#define VISION_LOOKAHEAD_Y (MT9V034_HEIGHT - 35)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define VISION_TRACK_POLARITY_AUTO 0
#define VISION_TRACK_POLARITY_DARK 1
#define VISION_TRACK_POLARITY_BRIGHT 2

#ifndef VISION_TRACK_POLARITY
#define VISION_TRACK_POLARITY VISION_TRACK_POLARITY_BRIGHT
#endif

#define VISION_THRESHOLD_ISODATA 0
#define VISION_THRESHOLD_OTSU 2

#ifndef VISION_THRESHOLD_METHOD
#define VISION_THRESHOLD_METHOD VISION_THRESHOLD_OTSU
#endif

#ifndef VISION_USE_SPLIT_THRESHOLD
#define VISION_USE_SPLIT_THRESHOLD 1
#endif

#ifndef VISION_FAR_REGION_HEIGHT
#define VISION_FAR_REGION_HEIGHT 16u
#endif

#ifndef VISION_FAR_THRESHOLD_OFFSET
#define VISION_FAR_THRESHOLD_OFFSET -18
#endif

#ifndef VISION_BIN_DESPECKLE
#define VISION_BIN_DESPECKLE 1
#endif

#ifndef VISION_BIN_CLOSE_GAP_MAX
#define VISION_BIN_CLOSE_GAP_MAX 5u
#endif

#ifndef VISION_BIN_OPEN_SPUR_MAX
#define VISION_BIN_OPEN_SPUR_MAX 3u
#endif

#ifndef VISION_EDGE_INTERP_MAX_GAP_ROWS
#define VISION_EDGE_INTERP_MAX_GAP_ROWS 5u
#endif

#ifndef VISION_ROW_MAX_CENTER_JUMP
#define VISION_ROW_MAX_CENTER_JUMP 22u
#endif

#ifndef VISION_ROW_MAX_WIDTH_GROW
#define VISION_ROW_MAX_WIDTH_GROW 20u
#endif

#ifndef VISION_ROW_MAX_WIDTH_RATIO_NUM
#define VISION_ROW_MAX_WIDTH_RATIO_NUM 9u
#endif

#ifndef VISION_ROW_MAX_WIDTH_RATIO_DEN
#define VISION_ROW_MAX_WIDTH_RATIO_DEN 5u
#endif

#ifndef VISION_CENTER_WINDOW_RADIUS
#define VISION_CENTER_WINDOW_RADIUS 2u
#endif

#ifndef VISION_CENTER_FRAME_MAX_JUMP
#define VISION_CENTER_FRAME_MAX_JUMP 10u
#endif

#ifndef VISION_CENTER_SMOOTH_NUM
#define VISION_CENTER_SMOOTH_NUM 3u
#endif

#ifndef VISION_CENTER_SMOOTH_DEN
#define VISION_CENTER_SMOOTH_DEN 4u
#endif

#ifndef VISION_CENTER_HOLD_FRAMES
#define VISION_CENTER_HOLD_FRAMES 3u
#endif

// Compile-time switch: wall-following disabled (migrated to Image.c Search_L_R pipeline)
#ifndef VISION_USE_WALLFOLLOW
#define VISION_USE_WALLFOLLOW 0
#endif

#define VISION_PTS_MAX (MT9V034_WIDTH)

// Corner point data (detected拐点 on a boundary)
typedef struct
{
    uint8_t img_pt[2];   // corner position in original image (x, y)
    uint8_t bev_pt[2];   // corner position in bird's-eye view (x, y)
    uint8_t pts_idx;     // index in the point set array
    int16_t angle_q7;    // local angle at corner (radians × 128)
    uint8_t is_valid;    // 1 = valid corner detected
} vision_corner_t;

typedef enum
{
    VISION_FEATURE_NORMAL = 0,
    VISION_FEATURE_CROSS,
    VISION_FEATURE_RING_LEFT,
    VISION_FEATURE_RING_RIGHT,
    VISION_FEATURE_LOST,
} vision_feature_t;

typedef struct
{
    uint8_t threshold;
    uint8_t track_is_dark;

    vision_feature_t feature;

    int16_t center_x;
    int16_t error_x;

    uint8_t valid_rows;

    // Per-row boundary arrays (image space, for backward compatibility)
    int16_t left[MT9V034_HEIGHT];
    int16_t right[MT9V034_HEIGHT];
    int16_t mid[MT9V034_HEIGHT];

    // Sparse point sets (image space, ordered bottom→top)
    uint8_t left_pts[VISION_PTS_MAX][2];
    uint8_t left_step;
    uint8_t right_pts[VISION_PTS_MAX][2];
    uint8_t right_step;

    // Bird's-eye view point sets (after perspective transform)
    uint8_t left_bev[VISION_PTS_MAX][2];
    uint8_t left_bev_step;
    uint8_t right_bev[VISION_PTS_MAX][2];
    uint8_t right_bev_step;

    // Midline point set (bird's-eye view)
    uint8_t mid_pts[VISION_PTS_MAX][2];
    uint8_t mid_step;

    // Distance from each midline point to vehicle (94, 120)
    int16_t mid_dist[VISION_PTS_MAX];

    // Lane width estimate (pixels at bottom of image)
    int16_t lane_width;

    // Corner points on left/right boundaries
    vision_corner_t corner_l;
    vision_corner_t corner_r;

    // Visible track distance (highest row with valid edge)
    uint8_t visible_high;
} vision_track_result_t;

void vision_track_process(uint8_t *gray, uint8_t *bin, vision_track_result_t *res);

// 浮点数学函数 (C251 无标准 libm)
float sqrtf(float x);
float atan2f(float y, float x);

// 三点 Menger 曲率 (×1000), 正值右转, 负值左转
int16_t pts_curvature_3pt(const uint8_t p0[2], const uint8_t p1[2], const uint8_t p2[2]);

#ifdef __cplusplus
}
#endif

#endif

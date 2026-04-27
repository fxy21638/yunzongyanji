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
#define VISION_BIN_CLOSE_GAP_MAX 3u
#endif

#ifndef VISION_BIN_OPEN_SPUR_MAX
#define VISION_BIN_OPEN_SPUR_MAX 2u
#endif

#ifndef VISION_EDGE_INTERP_MAX_GAP_ROWS
#define VISION_EDGE_INTERP_MAX_GAP_ROWS 3u
#endif

#ifndef VISION_ROW_MAX_CENTER_JUMP
#define VISION_ROW_MAX_CENTER_JUMP 18u
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

    int16_t left[MT9V034_HEIGHT];
    int16_t right[MT9V034_HEIGHT];
    int16_t mid[MT9V034_HEIGHT];
} vision_track_result_t;

void vision_track_process(const uint8_t *gray, uint8_t *bin, vision_track_result_t *res);
void vision_track_debug_draw(uint8_t *bin, const vision_track_result_t *res);
void vision_track_show_color(uint16_t x, uint16_t y, const vision_track_result_t *res);
void vision_track_overlay_lines(uint16_t x, uint16_t y, const vision_track_result_t *res);

#ifdef __cplusplus
}
#endif

#endif

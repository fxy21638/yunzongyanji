#ifndef _TRAIL_H_
#define _TRAIL_H_

#include "ky_headfile.h"
#include "vision_track.h"

#define CENTER_POINT (MT9V034_WIDTH / 2)
#define EDGE_IGNORE 7
#define MIN_WHITE_LENGTH 3

#define PICTURE_LENGTH 64
#define BROKEN_LENTH 32

typedef enum TRACK_ELEMENT
{
    NONE,
    START,
    STRAIGHT,
    RIGHT_ANGLE_l,
    RIGHT_ANGLE_r,
    RING_l,
    RING_r,
    RING_c,
    CROSS,
    BROKEN,
    BROKEN_RODE
} TRACK_ELEMENT;

extern uint8_t white_count;

extern uint8_t white_segments[20];
extern uint8_t time_search;
extern uint8_t start_stage;
extern int32_t judge_distance;
extern uint8_t broken_flag;

extern TRACK_ELEMENT track_element;
extern TRACK_ELEMENT track_element_P;
extern TRACK_ELEMENT current_element;
extern uint8_t track_midpoint_target;
extern uint8_t track_midpoint_target_P;
extern uint8_t g_target_detected;
extern uint8_t g_target_center_x;
extern uint8_t g_target_radius;
extern uint8_t g_target_y_mid;
extern uint8_t g_obstacle_detected;
extern uint8_t g_obstacle_center_x;
extern uint8_t g_obstacle_width;
extern uint8_t g_obstacle_y_mid;
extern uint8_t g_obstacle_left_edge;
extern uint8_t g_obstacle_right_edge;
extern uint8_t g_out_of_bounds;

// 纯追踪输出 (供 control.c 使用)
extern float pp_steering_angle;   // 纯追踪转向角 (度)
extern float pp_lookahead_dist;   // 当前前瞻距离 (像素)
extern float pp_curvature;        // 赛道曲率估计
extern uint8_t pp_visible_high;   // 可见赛道行数

TRACK_ELEMENT track_element_judge(void);
void state_display(void);
void track_handle(void);

float trail_speed_factor(void);

/* ---- 段分类数据 (供 ring_fsm 使用) ---- */
#define SEGMENT_MAX 12
extern int8_t  g_seg_type[SEGMENT_MAX];
extern uint8_t g_seg_start[SEGMENT_MAX];
extern uint8_t g_seg_end[SEGMENT_MAX];
extern uint8_t g_seg_num;

/* ---- 中线限幅 (供 ring_fsm 使用) ---- */
uint8_t clamp_center_to_target(int16_t center_x);

#endif

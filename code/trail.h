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
extern uint8_t straight_target;
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

TRACK_ELEMENT track_element_judge(void);
void state_display(void);
void track_handle(void);
void track_straight_target(uint8_t position);

#endif

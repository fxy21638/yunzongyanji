#ifndef __VISION_H__
#define __VISION_H__

#include "ky_headfile.h"
#include "vision_track.h"

extern vision_track_result_t g_track;
extern uint8_t g_track_valid;

void vision_Init(void);
void vision_poll_track(void);
void vision_task(void);
void vision_isp_task(void);

#endif

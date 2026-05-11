#ifndef __VISION_ISP_H__
#define __VISION_ISP_H__

#include "vision_track.h"

void vision_isp_show_color(uint16_t x, uint16_t y, const vision_track_result_t *res);
void vision_isp_overlay_lines(uint16_t x, uint16_t y, const vision_track_result_t *res);
void vision_isp_debug_draw(uint8_t *bin, const vision_track_result_t *res);

#endif

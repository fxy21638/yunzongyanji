#ifndef __VISION_MASTER_H__
#define __VISION_MASTER_H__

#include "ky_headfile.h"

void image_copy(image_t *img, const uint8_t *src);
void vofa_sendGrayscaleImage(uint8_t *img, uint16_t width, uint16_t height);
void vofa_image_task(void);

#endif

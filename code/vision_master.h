#ifndef __VISION_MASTER_H__
#define __VISION_MASTER_H__

#include "ky_headfile.h"

#define VOFA_IMAGE_ID_GRAY 1
#define VOFA_IMAGE_ID_OVERLAY 2
#define VOFA_IMAGE_ID_PSEUDO 3

void image_copy(image_t *img, const uint8_t *src);
void vofa_sendGrayscaleImageEx(uint8_t *img, uint16_t width, uint16_t height, uint8_t image_id);
void vofa_sendGrayscaleImage(uint8_t *img, uint16_t width, uint16_t height);
void vofa_image_task(void);

#endif

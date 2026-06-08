#ifndef __ICM_H__
#define __ICM_H__

#include "ky_headfile.h"

extern float roll;
extern float pitch;
extern float yaw;

float icm_get_gyro_z_dps(void);

void icm_Init(void);
void tim0_callback(void);
void icm_debug(void);

#endif

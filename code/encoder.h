#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "ky_headfile.h"

#define ENC1_PWM ENCODER_PWMC
#define ENC2_PWM ENCODER_PWMD

#define ENC1_A_PIN ENCC_A_P80
#define ENC1_B_PIN ENCC_B_P82
#define ENC2_A_PIN ENCD_A_P81
#define ENC2_B_PIN ENCD_B_P83

extern int16_t enc1_value;
extern int16_t enc2_value;
extern int16_t encoder_data_dir[2];

void encoder_Init(void);
void encoder_task(void);
void encoder_debug(void);

#endif

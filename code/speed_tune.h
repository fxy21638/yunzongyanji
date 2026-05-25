#ifndef __SPEED_TUNE_H__
#define __SPEED_TUNE_H__

#include "ky_headfile.h"

// Firewater protocol (CSV format) for VOFA+
// Frame: target,actual_L,actual_R,pwm_L,pwm_R,error_L,error_R
//
// Channel layout:
//   [0] target_speed    — speed_base
//   [1] actual_speed_L  — encoder_data_dir[0]
//   [2] actual_speed_R  — encoder_data_dir[1]
//   [3] pwm_out_L       — speed_now_l
//   [4] pwm_out_R       — speed_now_r
//   [5] error_L         — target - actual L
//   [6] error_R         — target - actual R

void speed_tune_send(void);

#endif

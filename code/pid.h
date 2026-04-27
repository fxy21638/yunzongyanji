#ifndef _PID_H_
#define _PID_H_

#include "ky_headfile.h"

// PID结构体：包含所有参数和状态变量
typedef struct
{
    // PID参数
    float Kp; // 比例系数
    float Ki; // 积分系数
    float Kd; // 微分系数

    // 目标值与实际值
    float target; // 目标值（如：脉冲数/10ms）
    float actual; // 实际值（编码器反馈）

    // 误差相关
    float err;          // 当前误差（target - actual）
    float err_last;     // 上一次误差（未滤波）
    float err_filtered; // 滤波后的当前误差
    float err_sum;      // 误差积分（滤波后）
    float diff;         // 误差变化率（滤波后）

    // 输出限制
    float output;     // PID输出（PWM值）
    float output_max; // 输出最大值（如100）
    float output_min; // 输出最小值（如-100）
    float sum_max;    // 积分限幅（防止饱和）

    // 滤波系数（一阶低通滤波）
    float filter_alpha; // 滤波系数（0~1，越大响应越快）
} PID_t;

// 函数声明
void PID_Init(PID_t *pid, float Kp, float Ki, float Kd,
              float output_max, float output_min, float sum_max, float filter_alpha);
void PID_Update(PID_t *pid);
void PID_Reset(PID_t *pid); // 重置PID状态

void PID_control(void);
// Angle control: set target and actual yaw (degrees), returns control output
float Angle_Control(float targetYawDeg, float actualYawDeg);
void TurnToAngle(float targetYawDeg);


#endif

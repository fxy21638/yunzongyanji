#include "pid.h"
#include "motor.h"
#include <math.h>

/*
extern int BASE_SPEED;
extern int linePos;
extern PID_t leftPID;
extern PID_t rightPID;
extern PID_t steerPID;
extern PID_t anglePID;
extern int PWMleft, PWMright;
extern int targetLeftSpeed, targetRightSpeed;
extern int leftEncSpeed, rightEncSpeed;
extern int is_lost;
extern float angle_err;
extern float yaw;
*/

/**
 * @brief  PID初始化
 * @param  pid: PID结构体指针
 * @param  Kp: 比例系数
 * @param  Ki: 积分系数
 * @param  Kd: 微分系数
 * @param  output_max: 输出最大值
 * @param  output_min: 输出最小值
 * @param  sum_max: 积分限幅（建议为输出范围的1/5~1/3）
 * @param  filter_alpha: 误差滤波系数（0.1~0.3，小车推荐0.2）
 */
void PID_Init(PID_t *pid, float Kp, float Ki, float Kd,
              float output_max, float output_min, float sum_max, float filter_alpha)
{
    // 初始化参数
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->output_max = output_max;
    pid->output_min = output_min;
    pid->sum_max = sum_max;
    pid->filter_alpha = (filter_alpha > 1.0f) ? 1.0f : (filter_alpha < 0.0f) ? 0.0f
                                                                             : filter_alpha;

    // 初始化状态变量
    pid->target = 0.0f;
    pid->actual = 0.0f;
    pid->err = 0.0f;
    pid->err_last = 0.0f;
    pid->err_filtered = 0.0f;
    pid->err_sum = 0.0f;
    pid->diff = 0.0f;
    pid->output = 0.0f;
}

/**
 * @brief  PID更新（核心控制逻辑）
 * @note   需在定时中断中调用（如10ms一次）
 * @param  pid: PID结构体指针
 */
void PID_Update(PID_t *pid)
{
    // 1. 计算当前误差（未滤波）
    pid->err = pid->target - pid->actual;

    // 2. 误差一阶低通滤波（减少噪声干扰）
    pid->err_filtered = pid->filter_alpha * pid->err + (1 - pid->filter_alpha) * pid->err_filtered;

    // 3. 计算微分（基于滤波后的误差变化率）
    pid->diff = pid->err_filtered - pid->err_last;
    pid->err_last = pid->err_filtered; // 保存当前滤波误差用于下次计算

    // 4. 计算积分（带抗饱和处理：输出限幅时停止积分）
    if (!(pid->output >= pid->output_max && pid->err_filtered > 0) &&
        !(pid->output <= pid->output_min && pid->err_filtered < 0))
    {
        pid->err_sum += pid->err_filtered;
        // 积分限幅（防止积分饱和）
        if (pid->err_sum > pid->sum_max)
        {
            pid->err_sum = pid->sum_max;
        }
        else if (pid->err_sum < -pid->sum_max)
        {
            pid->err_sum = -pid->sum_max;
        }
    }

    // 5. 计算PID输出
    pid->output = pid->Kp * pid->err_filtered + // 比例项（滤波后误差，减少震荡）
                  pid->Ki * pid->err_sum +      // 积分项（消除静态误差）
                  pid->Kd * pid->diff;          // 微分项（抑制超调）

    // 6. 输出限幅（确保在PWM有效范围）
    if (pid->output > pid->output_max)
    {
        pid->output = pid->output_max;
    }
    else if (pid->output < pid->output_min)
    {
        pid->output = pid->output_min;
    }
}

/**
 * @brief  重置PID状态（用于小车启停时清零）
 * @param  pid: PID结构体指针
 */
void PID_Reset(PID_t *pid)
{
    pid->err = 0.0f;
    pid->err_last = 0.0f;
    pid->err_filtered = 0.0f;
    pid->err_sum = 0.0f;
    pid->diff = 0.0f;
    pid->output = 0.0f;
}

/*
void PID_control(void)
{
    //        // ???PID????
    steerPID.target = 0;
    steerPID.actual = linePos;
    PID_Update(&steerPID);

    targetLeftSpeed = BASE_SPEED + steerPID.output;
    targetRightSpeed = BASE_SPEED - steerPID.output;

    //        // ?????PID
    leftPID.target = targetLeftSpeed;
    rightPID.target = targetRightSpeed;

    leftPID.actual = leftEncSpeed;
    rightPID.actual = rightEncSpeed;
    PID_Update(&leftPID);
    PID_Update(&rightPID);

    int turn_speed = 30;
    if (is_lost == 0)
    {
        PWMleft = leftPID.output;
        PWMright = rightPID.output;
    }
    else
    {
        if (is_lost == 1)
        {
            PWMleft = -turn_speed;
            PWMright = turn_speed;
        }
        else if (is_lost == -1)
        {
            PWMleft = turn_speed;
            PWMright = -turn_speed;
        }
    }

    // PWMleft = BASE_SPEED - linePos;
    // PWMright = BASE_SPEED + linePos;

    Set_PWM(PWMleft, PWMright);
}
*/

/*
 * @brief Angle control helper
 * @param targetYawDeg: desired yaw in degrees
 * @param actualYawDeg: current yaw in degrees
 * @return control output (signed), range limited by steerPID.output_min/max
 */
/*
float Angle_Control(float targetYawDeg, float actualYawDeg)
{
   anglePID.target = targetYawDeg;
   anglePID.actual = actualYawDeg;
   PID_Update(&anglePID);
   return anglePID.output;
}
*/

/* TurnToAngle implementation: compute shortest-angle error and apply steering
 * Uses Angle_Control (anglePID) and existing speed PIDs to drive wheels.
 */
/*
void TurnToAngle(float targetYawDeg)
{
    float err = targetYawDeg - yaw;

    // drive error to zero: target=0, actual=err
    float steer = Angle_Control(0.0f, err);

    targetLeftSpeed = (int)steer;
    targetRightSpeed = -(int)steer;

    leftPID.target = targetLeftSpeed;
    rightPID.target = targetRightSpeed;
    leftPID.actual = leftEncSpeed;
    rightPID.actual = rightEncSpeed;
    PID_Update(&leftPID);
    PID_Update(&rightPID);

    PWMleft = (int)leftPID.output;
    PWMright = (int)rightPID.output;
    Set_PWM(PWMleft, PWMright);
}
*/

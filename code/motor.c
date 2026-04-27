/*******************************************************************************
 * 接线说明:
 * -----------------------------------------------------------------------------
 * 模块         | 引脚         | 连接说明
 * -------------|--------------|----------------------------------------------
 * 电机1 PWM1   | PWMB_CH5_P74 | 接P7.4 (电机1正转PWM)
 * 电机1 PWM2   | PWMB_CH6_P75 | 接P7.5 (电机1反转PWM)
 * 电机2 PWM1   | PWMB_CH7_P76 | 接P7.6 (电机2正转PWM)
 * 电机2 PWM2   | PWMB_CH8_P77 | 接P7.7 (电机2反转PWM)
 * -----------------------------------------------------------------------------
 *
 * 实验现象:
 * -----------------------------------------------------------------------------
 * 1. 电机1正转加速-减速-反转加速-减速循环
 * 2. 电机2正转加速-减速-反转加速-减速循环
 * 3. 两路电机使用双PWM控制（一路正转时另一路为0）
 * 4. LED心跳灯每500ms翻转一次
 * -----------------------------------------------------------------------------
 ******************************************************************************/
/*
#include "motor.h"

// 引脚宏定义 
// 电机1引脚
#define M1_PWM1         PWMB_CH5_P74     // 电机1 PWM1 (P7.4)
#define M1_PWM2         PWMB_CH7_P76     // 电机1 PWM2 (P7.6)

// 电机2引脚
#define M2_PWM1         PWMB_CH6_P75     // 电机2 PWM1 (P7.5)
#define M2_PWM2         PWMB_CH8_P77     // 电机2 PWM2 (P7.7)

// PWM参数
#define PWM_FREQ        10000            // PWM频率 10kHz
#define PWM_DUTY_MAX    8000             // 最大占空比
#define DUTY_STEP       50               // 占空比变化步长

uint16_t duty = 0;
uint8_t direction = 0;               // 0=正转, 1=反转
	
void motor_Init(void)
{
	pwm_init(M1_PWM1, PWM_FREQ, 0);
    pwm_init(M1_PWM2, PWM_FREQ, 0);
    pwm_init(M2_PWM1, PWM_FREQ, 0);
    pwm_init(M2_PWM2, PWM_FREQ, 0);
}

void motor_task(void)
{
	if (direction == 0) {
		duty += DUTY_STEP;
		if (duty >= PWM_DUTY_MAX) {
			duty = PWM_DUTY_MAX;
			direction = 1;
		}
	}
	// 减速阶段
	else {
		if (duty > DUTY_STEP) {
			duty -= DUTY_STEP;
		} else {
			duty = 0;
			direction = 0;
		}
	}

	// 正转时PWM1输出，PWM2为0；反转时PWM2输出，PWM1为0
	if (duty == 0) {
		// 停止：两个都为0
		pwm_set_duty(M1_PWM1, 0);
		pwm_set_duty(M1_PWM2, 0);
		pwm_set_duty(M2_PWM1, 0);
		pwm_set_duty(M2_PWM2, 0);
	} else if (direction == 0) {
		// 正转：PWM1输出，PWM2为0
		pwm_set_duty(M1_PWM1, duty);
		pwm_set_duty(M1_PWM2, 0);
		pwm_set_duty(M2_PWM1, duty);
		pwm_set_duty(M2_PWM2, 0);
	} else {
		// 反转：PWM2输出，PWM1为0
		pwm_set_duty(M1_PWM1, 0);
		pwm_set_duty(M1_PWM2, duty);
		pwm_set_duty(M2_PWM1, 0);
		pwm_set_duty(M2_PWM2, duty);
	}
	
	
}
*/


#include "motor.h"

// ===================== 你的引脚定义 =====================
// 电机1
#define M1_PWM         PWMB_CH5_P74     // 速度 PWM
#define M1_DIR         PWMB_CH7_P76     // 方向引脚

// 电机2
#define M2_PWM         PWMB_CH6_P75     // 速度 PWM
#define M2_DIR         PWMB_CH8_P77     // 方向引脚

// PWM参数
#define PWM_FREQ        10000
#define PWM_DUTY_MAX    8000

// ===================== 全局变量 =====================
int16_t leftSpeed = 0;   // 左轮速度（带符号）
int16_t rightSpeed = 0;  // 右轮速度（带符号）

// ===================== 电机初始化 =====================
void motor_Init(void)
{
    // 只初始化 PWM 引脚
    pwm_init(M1_PWM, PWM_FREQ, 0);
    pwm_init(M2_PWM, PWM_FREQ, 0);

    // 方向脚初始化为输出低电平
    gpio_init(M1_DIR, GPIO_MODE_IN_PU, GPIO_LOW);
    gpio_init(M2_DIR, GPIO_MODE_IN_PU, GPIO_LOW);

    gpio_write_pin(M1_DIR, 0);
    gpio_write_pin(M2_DIR, 0);
}

// ===================== 核心驱动函数（你PID最终调用这个） =====================
void Set_PWM(int16_t left, int16_t right)
{
	leftSpeed = left;rightSpeed = right;
    // 限幅，防止超界
    if(left > PWM_DUTY_MAX) left = PWM_DUTY_MAX;
    if(left < -PWM_DUTY_MAX) left = -PWM_DUTY_MAX;

    if(right > PWM_DUTY_MAX) right = PWM_DUTY_MAX;
    if(right < -PWM_DUTY_MAX) right = -PWM_DUTY_MAX;

    // ---------------- 左轮控制 ----------------
    if(left > 0)
    {
        gpio_write_pin(M1_DIR, 0);    // 正转
        pwm_set_duty(M1_PWM, left);
    }
    else
    {
        gpio_write_pin(M1_DIR, 1);    // 反转
        pwm_set_duty(M1_PWM, -left);  // 取正
    }

    // ---------------- 右轮控制 ----------------
    if(right > 0)
    {
        gpio_write_pin(M2_DIR, 0);    // 正转
        pwm_set_duty(M2_PWM, right);
    }
    else if(right < 0)
    {
        gpio_write_pin(M2_DIR, 1);    // 反转
        pwm_set_duty(M2_PWM, -right); // 取正
    }
}

// ===================== 测试用（不需要可以删掉） =====================
void motor_task(void)
{
    // 这里可以留空，PID会直接调用 Set_PWM()
	Set_PWM(1000,1000);
	
	printf("left:%d,right:%d\n", leftSpeed, rightSpeed);
}


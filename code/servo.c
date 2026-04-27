/*******************************************************************************
 * 接线说明:
 * -----------------------------------------------------------------------------
 * 模块         | 引脚         | 连接说明
 * -------------|--------------|----------------------------------------------
 * 舵机信号     | SERVO_PIN    | 接P4.3 (PWME CH5 - PWM输出)
 * 按键1        | KEY1_PIN     | 接P9.2 (低电平有效，按下为低)
 * 按键2        | KEY2_PIN     | 接P9.3 (低电平有效，按下为低)
 * 按键3        | KEY3_PIN     | 接P9.4 (低电平有效，按下为低)
 * 按键4        | KEY4_PIN     | 接P9.5 (低电平有效，按下为低)
 * -----------------------------------------------------------------------------
 *
 * 实验现象:
 * -----------------------------------------------------------------------------
 * 1. KEY1短按：舵机角度-10度
 * 2. KEY2短按：舵机角度+10度
 * 3. KEY3短按：舵机转到0度位置
 * 4. KEY4短按：舵机转到180度位置
 * 5. KEY1长按：舵机连续转到0度位置
 * 6. KEY2长按：舵机连续转到180度位置
 * 7. 通过USB CDC虚拟串口输出舵机角度
 * 8. LED指示灯状态表示按键事件
 * -----------------------------------------------------------------------------
 *
 * 舵机参数说明:
 * -----------------------------------------------------------------------------
 * PWM频率: 330Hz
 * 0度对应脉宽: 0.5ms
 * 180度对应脉宽: 2.5ms
 * 90度对应脉宽: 1.5ms
 * 占空比公式: 10000 / (1000 / FREQ) * (0.5 + angle / 90.0)
 * -----------------------------------------------------------------------------
 ******************************************************************************/

// 可以先取下舵机，矫正到90度在装上去
// 可以先取下舵机，矫正到90度在装上去
// 可以先取下舵机，矫正到90度在装上去
#include "servo.h"
#include "key.h"
#include "main.h"

#define Servo_max_angle 110
#define Servo_min_angle 70

uint8_t servo_angle = 90;  // 初始角度90度

extern uint8_t key_id;

void servo_Init(void)
{
	// 舵机初始化 - 330Hz PWM, 初始90度
    pwm_init(SERVO_PIN, SERVO_FREQ, ANGLE_TO_DUTY(servo_angle));
}

//限制到20到160
void servo_task(void)
{
	// 检测所有按键的短按和长按事件
	for (key_id = 0; key_id < KEY_COUNT; key_id++) {
		// 检测短按
		if (key_is_pressed(key_id)) {
			gpio_toggle_pin(LED);  // LED闪烁指示按键事件

			switch (key_id) {
				case KEY1_ID:  // 角度-10度
					if (servo_angle > Servo_min_angle) servo_angle -= 10;
					else servo_angle = 0;
					pwm_set_duty(SERVO_PIN, ANGLE_TO_DUTY(servo_angle));
					printf("Angle: %d\r\n", servo_angle);
					break;

				case KEY2_ID:  // 角度+10度
					if (servo_angle < Servo_max_angle) servo_angle += 10;
					else servo_angle = 180;
					pwm_set_duty(SERVO_PIN, ANGLE_TO_DUTY(servo_angle));
					printf("Angle: %d\r\n", servo_angle);
					break;

				case KEY3_ID:  // 转到60度
					servo_angle = Servo_min_angle;
					pwm_set_duty(SERVO_PIN, ANGLE_TO_DUTY(servo_angle));
					printf("Angle: 60\r\n");
					break;

				case KEY4_ID:  // 转到120度
					servo_angle = Servo_max_angle;
					pwm_set_duty(SERVO_PIN, ANGLE_TO_DUTY(servo_angle));
					printf("Angle: 120\r\n");
					break;
			}
		}
		// 检测长按
		if (key_is_long_pressed(key_id)) {
			gpio_write_pin(LED, 0);  // LED点亮指示长按

			switch (key_id) {
				case KEY1_ID:  // 连续转到60度
					printf("To 60...\r\n");
					for (servo_angle = servo_angle; servo_angle > Servo_min_angle; servo_angle--) {
						pwm_set_duty(SERVO_PIN, ANGLE_TO_DUTY(servo_angle));
						delay_ms(20);
					}
					printf("Done\r\n");
					break;

				case KEY2_ID:  // 连续转到120度
					printf("To 120...\r\n");
					for (servo_angle = servo_angle; servo_angle < Servo_max_angle; servo_angle++) {
						pwm_set_duty(SERVO_PIN, ANGLE_TO_DUTY(servo_angle));
						delay_ms(20);
					}
					printf("Done\r\n");
					break;

				case KEY3_ID:  // 长按无操作
				case KEY4_ID:  // 长按无操作
					break;
			}
			gpio_write_pin(LED, 1);  // 恢复LED
		}
	}
}

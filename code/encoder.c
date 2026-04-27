/*******************************************************************************
 * 接线说明:
 * -----------------------------------------------------------------------------
 * 模块         | 引脚         | 连接说明
 * -------------|--------------|----------------------------------------------
 * 编码器1 A相   | ENC1_A_PIN   | 接P8.0 (PWMC A相 - 正交模式)
 * 编码器1 B相   | ENC1_B_PIN   | 接P8.2 (PWMC B相 - 正交模式)
 * 编码器2 脉冲  | ENC2_P_PIN   | 接P8.1 (PWMD 脉冲 - 带方向模式)
 * 编码器2 方向  | ENC2_D_PIN   | 接P8.3 (PWMD 方向 - 带方向模式)
 * LED指示灯    | LED_PIN      | 接PB6
 * -----------------------------------------------------------------------------
 *
 * 实验现象:
 * -----------------------------------------------------------------------------
 * 1. 旋转编码器1(正交模式)，计数器值随之增加或减少
 * 2. 旋转编码器2(带方向模式)，计数器值根据方向信号增加或减少
 * 3. 顺时针旋转计数器增加，逆时针旋转计数器减少
 * 4. 通过USB CDC虚拟串口输出两个编码器计数值
 * 5. LED指示灯状态表示编码器1的正反转
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#include "encoder.h"

int16_t enc1_value, enc2_value;
int16_t last_enc1_value = 0;

void encoder_Init(void)
{
	// 编码器1初始化 - 正交编码模式
    encoder_init_quad(ENCODER_PWMC, ENC1_A_PIN, ENC1_B_PIN);

    // 编码器2初始化 - 带方向编码模式
    encoder_init_dir(ENCODER_PWMD, ENC2_P_PIN, ENC2_D_PIN);
}
	
void encoder_task(void)
{
	// 读取编码器值
    enc1_value = encoder_read(ENCODER_PWMC);
    enc2_value = encoder_read(ENCODER_PWMD);

    // 检测编码器1旋转方向
    if (enc1_value > last_enc1_value) {
        // 顺时针旋转
        gpio_write_pin(LED, 0);
    } else if (enc1_value < last_enc1_value) {
        // 逆时针旋转
        gpio_write_pin(LED, 1);
    }

    last_enc1_value = enc1_value;
}

void encoder_debug(void)
{
	printf("ENC1(Q): %d, ENC2(D): %d\r\n", enc1_value, enc2_value);
}

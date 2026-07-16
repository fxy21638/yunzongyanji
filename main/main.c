// ====================================================================
// main.c
// ====================================================================

#include "ky_headfile.h"
#include "main.h"
#include "control.h"

#define DEBUG_IPS_DISPLAY 1 /* 1=开启IPS屏幕调试, 0=关闭 */

int main()
{
    uint8_t card_detected;

    system_clock_init(SYS_CLK_99MHZ);
    gpio_init(LED, GPIO_MODE_OUT_PP, GPIO_HIGH);

    /* 初始化硬件 (定时器/电机控制以外的部分) */
    key_system_Init();
    usb_cdc_init();
#if DEBUG_IPS_DISPLAY
    ips_init(IPS_TYPE_200);
    ips_set_direction(IPS_DIR_PORTRAIT);
#endif
    vision_Init();
    icm_Init();
    motor_Init();
    encoder_Init();
    servo_Init();
    laser_Init();

    /* ===== 等待启动: 黑色卡片被抽走 (此时控制定时器未启动, 电机不转) ===== */
    gpio_write_pin(LED, GPIO_LOW);    /* LED亮, 表示等待启动 */
    card_detected = 1;
    while (card_detected)
    {
        if (mt9v034_frame_ready)
        {
            card_detected = detect_start_card();
            mt9v034_frame_ready = 0;
        }
    }
    gpio_write_pin(LED, GPIO_HIGH);   /* LED灭, 表示启动就绪 */

    /* 启动控制定时器 (5ms, 电机+舵机控制) */
    control_Init();

    /* ===== 主循环 ===== */
    while (1)
    {
        image_process();
        check_stop_line();        /* 检测斑马线停止 */
        gpio_toggle_pin(LED);
    }
}

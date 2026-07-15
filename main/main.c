// ====================================================================
// main.c — 49.9 架构
// ====================================================================

#include "ky_headfile.h"
#include "main.h"
#include "control.h"

#define DEBUG_IPS_DISPLAY 0  /* 1=开启IPS屏幕调试, 0=关闭 */

void System_Init(void);

int main()
{
    system_clock_init(SYS_CLK_99MHZ);
    gpio_init(LED, GPIO_MODE_OUT_PP, GPIO_HIGH);
    System_Init();

    while (1)
    {
        image_process();
#if DEBUG_IPS_DISPLAY
        debug_ips_display();
#endif
        gpio_toggle_pin(LED);
    }
}

void System_Init(void)
{
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
    control_Init();
}

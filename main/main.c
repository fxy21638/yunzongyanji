#include "ky_headfile.h"
#include "main.h"
#include "vision_master.h"

void System_Init(void);
void debug_main(void);

int main()
{
    system_clock_init(SYS_CLK_99MHZ);

    gpio_init(LED, GPIO_MODE_OUT_PP, GPIO_HIGH);
    System_Init();

    while (1)
    {
        debug_main();
        gpio_toggle_pin(LED);
        //delay_ms(5);
    }
}

void System_Init(void)
{
    key_system_Init();
    usb_cdc_init();
    vision_Init();
    icm_Init();
    motor_Init();
    encoder_Init();
    servo_Init();
    laser_Init();   // P9.0 激光常亮
    control_Init();
}

void debug_main(void)
{
    track_handle();
    vofa_image_task();
}

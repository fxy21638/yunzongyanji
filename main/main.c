#include "ky_headfile.h"
#include "main.h"
#include "wireless_vision.h"

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
    vision_Init();
    icm_Init();
    motor_Init();
    encoder_Init();
    servo_Init();
    control_Init();
    //wireless_vision_init();
}

void debug_main(void)
{
    static uint8_t started = 0;

//    key_scan(10);

//    if (!started)
//    {
//        if (key_is_pressed(KEY1_ID))
//            started = 1;
//        return;
//    }

    vofa_image_task();
    track_handle();
    //speed_tune_send();
}

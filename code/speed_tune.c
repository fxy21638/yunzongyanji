#include "speed_tune.h"
#include "control.h"
#include "encoder.h"

#define TUNE_SEND_INTERVAL 4

// Step-test mode: set to 1 to enable square-wave target speed toggling.
#define TUNE_STEP_ENABLE 0
#define TUNE_STEP_INTERVAL 80
#define TUNE_STEP_LOW 40.0f
#define TUNE_STEP_HIGH 100.0f

void speed_tune_send(void)
{
    static uint8_t counter = 0;
#if TUNE_STEP_ENABLE
    static uint16_t step_cnt = 0;
    static uint8_t step_state = 0;
#endif
    float target;

    if (++counter < TUNE_SEND_INTERVAL)
        return;
    counter = 0;

#if TUNE_STEP_ENABLE
    if (++step_cnt >= TUNE_STEP_INTERVAL)
    {
        step_cnt = 0;
        step_state = !step_state;
    }
    target = step_state ? TUNE_STEP_HIGH : TUNE_STEP_LOW;
    speed_base = target;
#else
    target = speed_base;
#endif

    // Firewater protocol: use %d integers to avoid Keil C251 printf float bug
    printf("%d,%d,%d,", (int)target, encoder_data_dir[0], encoder_data_dir[1]);
    printf("%d,%d,", (int)speed_now_l, (int)speed_now_r);
    printf("%d,%d\r\n", (int)(target - encoder_data_dir[0]), (int)(target - encoder_data_dir[1]));
}

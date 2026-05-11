#include "servo.h"
#include "key.h"
#include "main.h"

#define SERVO_MAX_ANGLE            110
#define SERVO_MIN_ANGLE            70
#define CAR_MAX_ANGLE				130
#define CAR_MIN_ANGLE				50
#define SERVO_CENTER_ANGLE         90.0f
#define WHEEL_TO_SERVO_SCALE       2.00f
#define WHEEL_TO_SERVO_OFFSET_DEG  0.0f

uint8_t servo_angle = 90;

extern uint8_t key_id;

static uint8_t servo_clamp_angle(float angle_deg)
{
    if (angle_deg < SERVO_MIN_ANGLE)
    {
        angle_deg = SERVO_MIN_ANGLE;
    }
    else if (angle_deg > SERVO_MAX_ANGLE)
    {
        angle_deg = SERVO_MAX_ANGLE;
    }

    return (uint8_t)(angle_deg + 0.5f);
}

void servo_set_angle(uint8_t angle_deg)
{
    servo_angle = servo_clamp_angle((float)angle_deg);
    pwm_set_duty(SERVO_PIN, ANGLE_TO_DUTY(servo_angle));
}

void servo_set_wheel_angle(float wheel_angle_deg)
{
    float servo_target = SERVO_CENTER_ANGLE +
                         WHEEL_TO_SERVO_OFFSET_DEG +
                         wheel_angle_deg * WHEEL_TO_SERVO_SCALE;

    servo_set_angle(servo_clamp_angle(servo_target));
}

void servo_Init(void)
{
    pwm_init(SERVO_PIN, SERVO_FREQ, ANGLE_TO_DUTY(servo_angle));
}

void servo_task(void)
{
    for (key_id = 0; key_id < KEY_COUNT; key_id++)
    {
        if (key_is_pressed(key_id))
        {
            gpio_toggle_pin(LED);

            switch (key_id)
            {
            case KEY1_ID:
                if (servo_angle > SERVO_MIN_ANGLE)
                {
                    servo_set_angle((uint8_t)(servo_angle - 10));
                }
                else
                {
                    servo_set_angle(SERVO_MIN_ANGLE);
                }
                printf("ServoAngle:%d\r\n", servo_angle);
                break;

            case KEY2_ID:
                if (servo_angle < SERVO_MAX_ANGLE)
                {
                    servo_set_angle((uint8_t)(servo_angle + 10));
                }
                else
                {
                    servo_set_angle(SERVO_MAX_ANGLE);
                }
                printf("ServoAngle:%d\r\n", servo_angle);
                break;

            case KEY3_ID:
                servo_set_angle(SERVO_MIN_ANGLE);
                printf("ServoAngle:%d\r\n", servo_angle);
                break;

            case KEY4_ID:
                servo_set_angle(SERVO_MAX_ANGLE);
                printf("ServoAngle:%d\r\n", servo_angle);
                break;
            }
        }

        if (key_is_long_pressed(key_id))
        {
            gpio_write_pin(LED, 0);

            switch (key_id)
            {
            case KEY1_ID:
                printf("To %d...\r\n", SERVO_MIN_ANGLE);
                while (servo_angle > SERVO_MIN_ANGLE)
                {
                    servo_set_angle((uint8_t)(servo_angle - 1));
                    delay_ms(20);
                }
                printf("Done\r\n");
                break;

            case KEY2_ID:
                printf("To %d...\r\n", SERVO_MAX_ANGLE);
                while (servo_angle < SERVO_MAX_ANGLE)
                {
                    servo_set_angle((uint8_t)(servo_angle + 1));
                    delay_ms(20);
                }
                printf("Done\r\n");
                break;

            case KEY3_ID:
            case KEY4_ID:
                break;
            }

            gpio_write_pin(LED, 1);
        }
    }
}

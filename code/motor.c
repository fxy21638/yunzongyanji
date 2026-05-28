#include "motor.h"

#define M1_PWM PWMB_CH5_P74
#define M1_DIR GPIO_P76
#define M2_PWM PWMB_CH6_P75
#define M2_DIR GPIO_P77

#define PWM_FREQ 10000
#define PWM_DUTY_MAX 8000

int16_t leftSpeed = 0;
int16_t rightSpeed = 0;

void motor_Init(void)
{
    pwm_init(M1_PWM, PWM_FREQ, 0);
    pwm_init(M2_PWM, PWM_FREQ, 0);

    gpio_init(M1_DIR, GPIO_MODE_OUT_PP, GPIO_LOW);
    gpio_init(M2_DIR, GPIO_MODE_OUT_PP, GPIO_LOW);

    gpio_write_pin(M1_DIR, 0);
    gpio_write_pin(M2_DIR, 0);
}

void Set_PWM(int16_t left, int16_t right)
{
    leftSpeed = left;
    rightSpeed = right;

    if (left > PWM_DUTY_MAX)
    {
        left = PWM_DUTY_MAX;
    }
    if (left < -PWM_DUTY_MAX)
    {
        left = -PWM_DUTY_MAX;
    }

    if (right > PWM_DUTY_MAX)
    {
        right = PWM_DUTY_MAX;
    }
    if (right < -PWM_DUTY_MAX)
    {
        right = -PWM_DUTY_MAX;
    }

    if (left >= 0)
    {
        gpio_write_pin(M1_DIR, 0);
        pwm_set_duty(M1_PWM, left);
    }
    else
    {
        gpio_write_pin(M1_DIR, 1);
        pwm_set_duty(M1_PWM, -left);
    }

    if (right >= 0)
    {
        gpio_write_pin(M2_DIR, 1);
        pwm_set_duty(M2_PWM, right);
    }
    else
    {
        gpio_write_pin(M2_DIR, 0);
        pwm_set_duty(M2_PWM, -right);
    }
}

void motor_task(void)
{
    Set_PWM(leftSpeed, rightSpeed);
}

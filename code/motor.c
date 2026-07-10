#include "motor.h"

/* BTN7971B 双PWM驱动: 每路电机两个PWM(正转/反转)
   M1_PWM1(P7.6)=左正转, M1_PWM2(P7.4)=左反转
   M2_PWM1(P7.7)=右正转, M2_PWM2(P7.5)=右反转 */
#define M1_PWM1    PWMB_CH5_P74   /* 左电机正转 */
#define M1_PWM2    PWMB_CH7_P76   /* 左电机反转 */
#define M2_PWM1    PWMB_CH8_P77   /* 右电机正转 */
#define M2_PWM2    PWMB_CH6_P75   /* 右电机反转 */

#define PWM_FREQ       10000
#define PWM_DUTY_MAX   8000

int16_t leftSpeed = 0;
int16_t rightSpeed = 0;

void motor_Init(void)
{
    pwm_init(M1_PWM1, PWM_FREQ, 0);
    pwm_init(M1_PWM2, PWM_FREQ, 0);
    pwm_init(M2_PWM1, PWM_FREQ, 0);
    pwm_init(M2_PWM2, PWM_FREQ, 0);
}

void Set_PWM(int16_t left, int16_t right)
{
    leftSpeed = left;
    rightSpeed = right;

    /* 左电机 */
    if (left > PWM_DUTY_MAX)  left = PWM_DUTY_MAX;
    if (left < -PWM_DUTY_MAX) left = -PWM_DUTY_MAX;

    if (left >= 0) {
        pwm_set_duty(M1_PWM1, (uint16_t)left);
        pwm_set_duty(M1_PWM2, 0);
    } else {
        pwm_set_duty(M1_PWM1, 0);
        pwm_set_duty(M1_PWM2, (uint16_t)(-left));
    }

    /* 右电机 */
    if (right > PWM_DUTY_MAX)  right = PWM_DUTY_MAX;
    if (right < -PWM_DUTY_MAX) right = -PWM_DUTY_MAX;

    if (right >= 0) {
        pwm_set_duty(M2_PWM1, (uint16_t)right);
        pwm_set_duty(M2_PWM2, 0);
    } else {
        pwm_set_duty(M2_PWM1, 0);
        pwm_set_duty(M2_PWM2, (uint16_t)(-right));
    }
}

void motor_task(void)
{
    Set_PWM(leftSpeed, rightSpeed);
}

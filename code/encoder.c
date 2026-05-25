#include "encoder.h"
#include "main.h"

int16_t enc1_value = 0;
int16_t enc2_value = 0;
int16_t last_enc1_value = 0;
int16_t last_enc2_value = 0;
int16_t encoder_data_dir[2] = {0, 0};

void encoder_Init(void)
{
    encoder_init_quad(ENC1_PWM, ENC1_A_PIN, ENC1_B_PIN);
    encoder_init_quad(ENC2_PWM, ENC2_A_PIN, ENC2_B_PIN);
}

void encoder_task(void)
{
    enc1_value = encoder_read(ENC1_PWM);
    enc2_value = encoder_read(ENC2_PWM);

    encoder_data_dir[0] = last_enc1_value - enc1_value;
    encoder_data_dir[1] = last_enc2_value - enc2_value;

    last_enc1_value = enc1_value;
    last_enc2_value = enc2_value;
}

void encoder_debug(void)
{
    printf("ENC1:%d ENC2:%d DL:%d DR:%d\r\n",
           enc1_value,
           enc2_value,
           encoder_data_dir[0],
           encoder_data_dir[1]);
}

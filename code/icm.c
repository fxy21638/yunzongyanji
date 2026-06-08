#include "icm.h"

#define ICM_SAMPLE_DT            (0.005f)
#define ICM_GYRO_CALIB_SAMPLES   (500)
#define ICM_CALIB_DELAY_MS       (2)
#define ICM_COMPLEMENTARY_ALPHA  (0.98f)
#define ICM_GYRO_Z_DEADBAND_DPS  (0.15f)
#define ICM_GYRO_Z_BIAS_TRACK_DPS (0.80f)
#define ICM_BIAS_ADAPT_ALPHA     (0.01f)
#define RAD_TO_DEG               (57.2957795f)

float roll  = 0.0f;
float pitch = 0.0f;
float yaw   = 0.0f;

static float gyro_bias_x = 0.0f;
static float gyro_bias_y = 0.0f;
static float gyro_bias_z = 0.0f;
static float g_gyro_z_dps = 0.0f;   /* 偏置补偿后的 Z 轴角速度 (dps) */

float icm_get_gyro_z_dps(void)
{
    return g_gyro_z_dps;
}

static float icm_absf(float value)
{
    return (value < 0.0f) ? -value : value;
}

static float icm_get_acc_roll_deg(void)
{
    return math_atan2(g_icm42686_data.acc.y, g_icm42686_data.acc.z) * RAD_TO_DEG;
}

static float icm_get_acc_pitch_deg(void)
{
    float acc_yz_sq = g_icm42686_data.acc.y * g_icm42686_data.acc.y +
                      g_icm42686_data.acc.z * g_icm42686_data.acc.z;
    float acc_yz = 0.0f;

    if (acc_yz_sq > 0.0f)
    {
        acc_yz = acc_yz_sq * math_inv_sqrt(acc_yz_sq);
    }

    return math_atan2(-g_icm42686_data.acc.x, acc_yz) * RAD_TO_DEG;
}

static void icm_calibrate_gyro_bias(void)
{
    uint16_t i;
    float sum_x = 0.0f;
    float sum_y = 0.0f;
    float sum_z = 0.0f;

    for (i = 0; i < ICM_GYRO_CALIB_SAMPLES; i++)
    {
        icm42686_read_gyro();
        sum_x += g_icm42686_data.gyro.x;
        sum_y += g_icm42686_data.gyro.y;
        sum_z += g_icm42686_data.gyro.z;
        delay_ms(ICM_CALIB_DELAY_MS);
    }

    gyro_bias_x = sum_x / ICM_GYRO_CALIB_SAMPLES;
    gyro_bias_y = sum_y / ICM_GYRO_CALIB_SAMPLES;
    gyro_bias_z = sum_z / ICM_GYRO_CALIB_SAMPLES;
}

void icm_Init(void)
{
    icm42686_init();

    delay_ms(100);

    icm_calibrate_gyro_bias();

    icm42686_read_acc();
    roll = icm_get_acc_roll_deg();
    pitch = icm_get_acc_pitch_deg();
    yaw = 0.0f;

    timer_init_ms(0, 5, tim0_callback);
}

void tim0_callback(void)
{
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float gyro_x_raw;
    float gyro_y_raw;
    float gyro_z_raw;
    float gyro_z_err;
    float acc_roll;
    float acc_pitch;

    icm42686_read_gyro();
    icm42686_read_acc();

    gyro_x_raw = g_icm42686_data.gyro.x;
    gyro_y_raw = g_icm42686_data.gyro.y;
    gyro_z_raw = g_icm42686_data.gyro.z;
    gyro_z_err = gyro_z_raw - gyro_bias_z;

    if (icm_absf(gyro_z_err) < ICM_GYRO_Z_BIAS_TRACK_DPS)
    {
        gyro_bias_z = (1.0f - ICM_BIAS_ADAPT_ALPHA) * gyro_bias_z + ICM_BIAS_ADAPT_ALPHA * gyro_z_raw;
    }

    gyro_x = gyro_x_raw - gyro_bias_x;
    gyro_y = gyro_y_raw - gyro_bias_y;
    gyro_z = gyro_z_raw - gyro_bias_z;

    if (gyro_z > -ICM_GYRO_Z_DEADBAND_DPS && gyro_z < ICM_GYRO_Z_DEADBAND_DPS)
    {
        gyro_z = 0.0f;
    }

    g_gyro_z_dps = gyro_z;

    acc_roll = icm_get_acc_roll_deg();
    acc_pitch = icm_get_acc_pitch_deg();

    roll = ICM_COMPLEMENTARY_ALPHA * (roll + gyro_x * ICM_SAMPLE_DT) +
           (1.0f - ICM_COMPLEMENTARY_ALPHA) * acc_roll;
    pitch = ICM_COMPLEMENTARY_ALPHA * (pitch + gyro_y * ICM_SAMPLE_DT) +
            (1.0f - ICM_COMPLEMENTARY_ALPHA) * acc_pitch;
    if (icm_absf(gyro_z) >= ICM_GYRO_Z_DEADBAND_DPS)
    {
        yaw += gyro_z * ICM_SAMPLE_DT;
    }
}

void icm_debug(void)
{
    printf("Roll:%.2f,Pitch:%.2f,Yaw:%.2f,BiasZ:%.3f\n", roll, pitch, yaw, gyro_bias_z);
}

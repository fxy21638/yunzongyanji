/*********************************************************************************
 * 项目名称：[STC32G144K246开源库] 开源组件库
 * 版权所有：[2025] [北京科宇通博科技有限公司]
 *
 * 许可协议：采用 GNU GPL v3.0 开源许可
 * 您可依据协议进行二次开发、传播，但须保留原始版权信息
 * 协议详情参见：https://www.gnu.org/licenses/gpl-3.0.html
 *
 * 免责声明：本组件库仅提供技术参考，使用方需自行验证适用性
 *
 * 协议文件：GPL v3.0 完整文本位于根目录下
 *
 * === 文件信息 ===
 * 文件名：ky_icm42688.c
 * 开发单位：北京科宇通博科技有限公司
 * 适用环境：[Keil C251 / STC32G系列单片机]
 * 官方渠道：
 * - 代码仓库：[https://gitee.com/beijing-keyu---jiangxi/KEYU_AI8052U_OpenLibrary]
 * - 淘宝店铺：https://kyznc.taobao.com/
 * - 技术支持：QQ群 974530818
 *
 * === 修订记录 ===
 * 日期       |  开发者  | 变更说明
 * -----------|----------|----------------------
 * 2026.01.24 |   xiao   | V2.0
 *********************************************************************************/
#include "ky_icm42688.h"
#include "stc32g144k246.h"
#include "ky_delay.h"
#include "ky_spi.h"
#include <stdio.h>

Imu_Data_t g_icm42688_data;

// 原始陀螺仪数据
int16_t icm42688_gyro_raw_x, icm42688_gyro_raw_y, icm42688_gyro_raw_z;
// 原始加速度数据
int16_t icm42688_acc_raw_x, icm42688_acc_raw_y, icm42688_acc_raw_z;

static float g_acc_scale = 1.0f;
static float g_gyro_scale = 1.0f;

/***************************************************************
 * @brief     检查ICM42688的设备ID
 * @param     None
 * @Sample usage:     icm42688_check_id();
 **************************************************************/
static void icm42688_check_id(void)
{
    uint8_t model_id = 0xFF;
    uint8_t timeout_count = 0;

    while (1)
    {
        imu_read_regs(ICM42688_WHO_AM_I, &model_id, 1);
        if (model_id == 0x47) // ICM42688 默认 ID
        {
            printf("ICM42688 FOUND!\r\n");
            break;
        }
        else
        {
            delay_ms(10);
            if (timeout_count++ > 10)
            {
                printf("ICM42688 Init Error! ID: 0x%02X\r\n", model_id);
                while (1){printf("ICM42688 Init Error! ID: 0x%02X\r\n", model_id);};
            }
        }
    }
}

/***************************************************************
 * @brief     设置加速度计的量程和数据输出速率
 * @param     afs     量程 (Full-Scale)
 * @param     aodr    数据输出速率
 * @Sample usage:     icm42688_set_afs_aodr(ICM42688_AFS_16G, ICM42688_AODR_1KHZ);
 **************************************************************/
static void icm42688_set_afs_aodr(ICM42688_Afs_t afs, ICM42688_Aodr_t aodr)
{
    // ICM42688: ACCEL_FS_SEL 位于 bits[7:5], ACCEL_ODR 位于 bits[3:0]
    uint8_t config = ((afs & 0x07) << 5) | (aodr & 0x0F);
    imu_write_reg(ICM42688_ACCEL_CONFIG0, config);

    switch (afs)
    {
    case ICM42688_AFS_16G:
        g_acc_scale = 1.0f / 2048.0f;
        break;
    case ICM42688_AFS_8G:
        g_acc_scale = 1.0f / 4096.0f;
        break;
    case ICM42688_AFS_4G:
        g_acc_scale = 1.0f / 8192.0f;
        break;
    case ICM42688_AFS_2G:
        g_acc_scale = 1.0f / 16384.0f;
        break;
    default:
        g_acc_scale = 1.0f / 2048.0f;
        break;
    }
}

/***************************************************************
 * @brief     设置陀螺仪的量程和数据输出速率
 * @param     gfs     量程 (Full-Scale)
 * @param     godr    数据输出速率
 * @Sample usage:     icm42688_set_gfs_godr(ICM42688_GFS_2000DPS, ICM42688_GODR_1KHZ);
 **************************************************************/
static void icm42688_set_gfs_godr(ICM42688_Gfs_t gfs, ICM42688_Godr_t godr)
{
    // ICM42688: GYRO_FS_SEL 位于 bits[7:5], GYRO_ODR 位于 bits[3:0]
    uint8_t config = ((gfs & 0x07) << 5) | (godr & 0x0F);
    imu_write_reg(ICM42688_GYRO_CONFIG0, config);

    switch (gfs)
    {
    case ICM42688_GFS_2000DPS:
        g_gyro_scale = 1.0f / 16.4f;
        break;
    case ICM42688_GFS_1000DPS:
        g_gyro_scale = 1.0f / 32.8f;
        break;
    case ICM42688_GFS_500DPS:
        g_gyro_scale = 1.0f / 65.5f;
        break;
    case ICM42688_GFS_250DPS:
        g_gyro_scale = 1.0f / 131.0f;
        break;
    case ICM42688_GFS_125DPS:
        g_gyro_scale = 1.0f / 262.0f;
        break;
    case ICM42688_GFS_62_5DPS:
        g_gyro_scale = 1.0f / 524.3f;
        break;
    case ICM42688_GFS_31_25DPS:
        g_gyro_scale = 1.0f / 1048.6f;
        break;
    case ICM42688_GFS_15_625DPS:
        g_gyro_scale = 1.0f / 2097.2f;
        break;
    default:
        g_gyro_scale = 1.0f / 16.4f;
        break;
    }
}

/***************************************************************
 * @brief     初始化ICM42688传感器
 * @param     None
 * @Sample usage:     icm42688_init();
 **************************************************************/
void icm42688_init(void)
{
    imu_init();

    // 软复位设备
    imu_write_reg(ICM42688_DEVICE_CONFIG, 0x01);
    delay_ms(10);

    icm42688_check_id();

    // 开启低噪声模式 (LN Mode)
    imu_write_reg(ICM42688_PWR_MGMT0, 0x0F);
    delay_ms(10);

    // 设置默认量程与速率
    icm42688_set_afs_aodr(ICM42688_AFS_16G, ICM42688_AODR_1KHZ);
    icm42688_set_gfs_godr(ICM42688_GFS_2000DPS, ICM42688_GODR_1KHZ);
    
    // 配置 LPF 带宽为 ODR/10 (0x52 写入 0x11)
    imu_write_reg(ICM42688_GYRO_ACCEL_CONFIG0, 0x11);

}

/***************************************************************
 * @brief     从传感器读取最新的加速度计数据
 * @param     None
 * @Sample usage:     icm42688_read_acc();
 **************************************************************/
void icm42688_read_acc(void)
{
    uint8_t data_buffer[6];

    // ICM42688 数据寄存器高位在前 (Big-Endian)
    imu_read_regs(ICM42688_ACCEL_DATA_X1, data_buffer, 6);

    // 保存原始值
    icm42688_acc_raw_x = (int16_t)((data_buffer[0] << 8) | data_buffer[1]);
    icm42688_acc_raw_y = (int16_t)((data_buffer[2] << 8) | data_buffer[3]);
    icm42688_acc_raw_z = (int16_t)((data_buffer[4] << 8) | data_buffer[5]);

    g_icm42688_data.acc.x = (float)icm42688_acc_raw_x * g_acc_scale;
    g_icm42688_data.acc.y = (float)icm42688_acc_raw_y * g_acc_scale;
    g_icm42688_data.acc.z = (float)icm42688_acc_raw_z * g_acc_scale;
}

/***************************************************************
 * @brief     从传感器读取最新的陀螺仪数据
 * @param     None
 * @Sample usage:     icm42688_read_gyro();
 **************************************************************/
void icm42688_read_gyro(void)
{
    uint8_t data_buffer[6];

    // ICM42688 数据寄存器高位在前 
    imu_read_regs(ICM42688_GYRO_DATA_X1, data_buffer, 6);

    // 保存原始值
    icm42688_gyro_raw_x = (int16_t)((data_buffer[0] << 8) | data_buffer[1]);
    icm42688_gyro_raw_y = (int16_t)((data_buffer[2] << 8) | data_buffer[3]);
    icm42688_gyro_raw_z = (int16_t)((data_buffer[4] << 8) | data_buffer[5]);

    g_icm42688_data.gyro.x = (float)icm42688_gyro_raw_x * g_gyro_scale;
    g_icm42688_data.gyro.y = (float)icm42688_gyro_raw_y * g_gyro_scale;
    g_icm42688_data.gyro.z = (float)icm42688_gyro_raw_z * g_gyro_scale;
}

/***************************************************************
 * @brief     从传感器读取温度数据
 * @param     None
 * @Sample usage:     icm42688_read_temp();
 **************************************************************/
void icm42688_read_temp(void)
{
    uint8_t data_buffer[2];
    int16_t raw_temp;
    
    imu_read_regs(ICM42688_TEMP_DATA1, data_buffer, 2);

    raw_temp = (int16_t)((data_buffer[0] << 8) | data_buffer[1]);

    // 公式：Temperature in Degrees Centigrade = (TEMP_DATA / 132.48) + 25
    g_icm42688_data.temperature = (float)raw_temp / 132.48f + 25.0f;
}
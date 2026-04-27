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
 * 文件名：ky_icm45686.c
 * 开发单位：北京科宇通博科技有限公司
 * 适用环境：[Keil C251 / STC32G系列单片机]
 * 官方渠道：
 *   - 代码仓库：[https://gitee.com/beijing-keyu---jiangxi/KEYU_AI8052U_OpenLibrary]
 *   - 淘宝店铺：https://kyznc.taobao.com/
 *   - 技术支持：QQ群 974530818
 *
 * === 修订记录 ===
 * 日期       |  开发者  | 变更说明
 * -----------|----------|----------------------
 * 2025.12.22 |   xiao   | V2.0
 *********************************************************************************/
#include "ky_icm45686.h"
#include "stc32g144k246.h"
#include "ky_delay.h"
#include "ky_spi.h"


// 原始陀螺仪数据
int16_t icm45686_gyro_raw_x, icm45686_gyro_raw_y, icm45686_gyro_raw_z;
// 原始加速度数据
int16_t icm45686_acc_raw_x, icm45686_acc_raw_y, icm45686_acc_raw_z;


Imu_Data_t g_icm45686_data;

static float g_acc_scale = 1.0f;
static float g_gyro_scale = 1.0f;

/***************************************************************
 *  @brief     检查ICM45686的设备ID
 *  @param     None
 *  @Sample usage:     icm45686_check_id();
 **************************************************************/
static void icm45686_check_id(void)
{
    uint8_t model_id = 0xFF;
    uint8_t timeout_count = 0;

    while (1)
    {
        imu_read_regs(ICM45686_WHO_AM_I, &model_id, 1);
        if (model_id == 0xE9 || model_id == 0xFD)
        {
            printf("ICM45686 FOUND!\r\n");
            break;
        }
        else
        {
            delay_ms(10);
            if (timeout_count++ > 10)
            {
                printf("ICM45686 Init Error! ID: 0x%02X\r\n", model_id);
                while (1)
                    ;
            }
        }
    }
}

/***************************************************************
 *  @brief     设置加速度计的量程和数据输出速率
 *  @param     afs     量程 (Full-Scale)
 *  @param     aodr    数据输出速率
 *  @Sample usage:     icm45686_set_afs_aodr(ICM45686_AFS_16G, ICM45686_AODR_800HZ);
 **************************************************************/
static void icm45686_set_afs_aodr(ICM45686_Afs_t afs, ICM45686_Aodr_t aodr)
{
    uint8_t config = ((afs & 0x07) << 4) | (aodr & 0x0F);
    imu_write_reg(ICM45686_ACCEL_CONFIG0, config);

    switch (afs)
    {
    case ICM45686_AFS_32G:
        g_acc_scale = 1.0f / 1024.0f;
        break;
    case ICM45686_AFS_16G:
        g_acc_scale = 1.0f / 2048.0f;
        break;
    case ICM45686_AFS_8G:
        g_acc_scale = 1.0f / 4096.0f;
        break;
    case ICM45686_AFS_4G:
        g_acc_scale = 1.0f / 8192.0f;
        break;
    case ICM45686_AFS_2G:
        g_acc_scale = 1.0f / 16384.0f;
        break;
    default:
        g_acc_scale = 1.0f;
        break;
    }
}

/***************************************************************
 *  @brief     设置陀螺仪的量程和数据输出速率
 *  @param     gfs     量程 (Full-Scale)
 *  @param     godr    数据输出速率
 *  @Sample usage:     icm45686_set_gfs_godr(ICM45686_GFS_2000DPS, ICM45686_GODR_800HZ);
 **************************************************************/
static void icm45686_set_gfs_godr(ICM45686_Gfs_t gfs, ICM45686_Godr_t godr)
{
    uint8_t config = ((gfs & 0x0F) << 4) | (godr & 0x0F);
    imu_write_reg(ICM45686_GYRO_CONFIG0, config);

    switch (gfs)
    {
    case ICM45686_GFS_4000DPS:
        g_gyro_scale = 1.0f / 8.2f;
        break;
    case ICM45686_GFS_2000DPS:
        g_gyro_scale = 1.0f / 16.4f;
        break;
    case ICM45686_GFS_1000DPS:
        g_gyro_scale = 1.0f / 32.8f;
        break;
    case ICM45686_GFS_500DPS:
        g_gyro_scale = 1.0f / 65.5f;
        break;
    case ICM45686_GFS_250DPS:
        g_gyro_scale = 1.0f / 131.0f;
        break;
    case ICM45686_GFS_125DPS:
        g_gyro_scale = 1.0f / 262.0f;
        break;
    case ICM45686_GFS_62_5DPS:
        g_gyro_scale = 1.0f / 524.3f;
        break;
    case ICM45686_GFS_31_25DPS:
        g_gyro_scale = 1.0f / 1048.6f;
        break;
    case ICM45686_GFS_15_625DPS:
        g_gyro_scale = 1.0f / 2097.2f;
        break;
    default:
        g_gyro_scale = 1.0f;
        break;
    }
}

/***************************************************************
 *  @brief     初始化ICM45686传感器
 *  @param     None
 *  @Sample usage:     icm45686_init();
 **************************************************************/
void icm45686_init(void)
{
    imu_init();

    icm45686_check_id();

    imu_write_reg(ICM45686_REG_MISC2, 0x02);
    delay_ms(10);

    imu_write_reg(ICM45686_PWR_MGMT0, 0x0F);

    icm45686_set_afs_aodr(ICM45686_AFS_16G, ICM45686_AODR_1600HZ);
    icm45686_set_gfs_godr(ICM45686_GFS_2000DPS, ICM45686_GODR_1600HZ);
#ifdef ICM45686_AUTO_CALIBRATE_ON_STARTUP
    delay_ms(50);

    icm45686_calibrate_bias();
#endif
    delay_ms(10);
}

/***************************************************************
 *  @brief     从传感器读取最新的加速度计数据
 *  @param     None
 *  @Sample usage:     icm45686_read_acc();
 **************************************************************/
void icm45686_read_acc(void)
{
    uint8_t data_buffer[6];
    imu_read_regs(ICM45686_ACCEL_DATA_X1_UI, data_buffer, 6);

    // 保存原始值
    icm45686_acc_raw_x = (int16_t)((data_buffer[1] << 8) | data_buffer[0]);
    icm45686_acc_raw_y = (int16_t)((data_buffer[3] << 8) | data_buffer[2]);
    icm45686_acc_raw_z = (int16_t)((data_buffer[5] << 8) | data_buffer[4]);

    g_icm45686_data.acc.x = (float)icm45686_acc_raw_x * g_acc_scale;
    g_icm45686_data.acc.y = (float)icm45686_acc_raw_y * g_acc_scale;
    g_icm45686_data.acc.z = (float)icm45686_acc_raw_z * g_acc_scale;
}

/***************************************************************
 *  @brief     从传感器读取最新的陀螺仪数据
 *  @param     None
 *  @Sample usage:     icm45686_read_gyro();
 **************************************************************/
void icm45686_read_gyro(void)
{
    uint8_t data_buffer[6];
    imu_read_regs(ICM45686_GYRO_DATA_X1_UI, data_buffer, 6);

    // 保存原始值
    icm45686_gyro_raw_x = (int16_t)((data_buffer[1] << 8) | data_buffer[0]);
    icm45686_gyro_raw_y = (int16_t)((data_buffer[3] << 8) | data_buffer[2]);
    icm45686_gyro_raw_z = (int16_t)((data_buffer[5] << 8) | data_buffer[4]);

    g_icm45686_data.gyro.x = (float)icm45686_gyro_raw_x * g_gyro_scale;
    g_icm45686_data.gyro.y = (float)icm45686_gyro_raw_y * g_gyro_scale;
    g_icm45686_data.gyro.z = (float)icm45686_gyro_raw_z * g_gyro_scale;
}

/***************************************************************
 *  @brief     从传感器读取温度数据
 *  @param     None
 *  @Sample usage:     icm45686_read_temp();
 **************************************************************/
void icm45686_read_temp(void)
{
    uint8_t data_buffer[2];
    int16_t raw_temp;
    imu_read_regs(ICM45686_TEMP_DATA1_UI, data_buffer, 2);

    raw_temp = (int16_t)((data_buffer[1] << 8) | data_buffer[0]);

    g_icm45686_data.temperature = (float)raw_temp / 132.48f + 25.0f;
}

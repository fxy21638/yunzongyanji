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
 * 文件名：ky_lsm6dsr.c
 * 开发单位：北京科宇通博科技有限公司
 * 适用环境：[Keil C251 / STC32G系列单片机]
 * 官方渠道：
 *   - 代码仓库：[https://gitee.com/beijing-keyu---jiangxi/KEYU_AI8052U_OpenLibrary]
 *   - 淘宝店铺：https://kyznc.taobao.com/
 *   - 技术支持：QQ群 974530818
 *
 * === 修订记录 ===
 * 日期       | 开发者   | 变更说明
 * -----------|----------|----------------------
 * 2025.12.22 |   xiao   | V2.0
 *********************************************************************************/
#include "ky_lsm6dsr.h"
#include "stc32g144k246.h"
#include "ky_delay.h"


Imu_Data_t g_lsm6dsr_data;

// 原始陀螺仪数据
int16_t lsm6dsr_gyro_raw_x, lsm6dsr_gyro_raw_y, lsm6dsr_gyro_raw_z;
// 原始加速度数据
int16_t lsm6dsr_acc_raw_x, lsm6dsr_acc_raw_y, lsm6dsr_acc_raw_z;

static float g_acc_scale = 1.0f;
static float g_gyro_scale = 1.0f;

/***************************************************************
 *  @brief     检查LSM6DSR的设备ID是否正确
 *  @param     None
 *  @Sample usage:     lsm6dsr_check_id();
 **************************************************************/
static void lsm6dsr_check_id(void)
{
    uint8_t model_id = 0xFF;
    uint8_t timeout_count = 0;

    while (1)
    {
        imu_read_regs(LSM6DSR_WHO_AM_I, &model_id, 1);
        if (model_id == 0x7f || model_id == 0x6b)
        {
            printf("LSM6DSR FOUND!\r\n");
            break;
        }
        else
        {
            delay_ms(10);
            if (timeout_count++ > 10)
            {
                printf("LSM6DSR Init Error! ID: 0x%02X\r\n", model_id);
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
 *  @Sample usage:     lsm6dsr_set_afs_aodr(LSM6DSR_AFS_16G, LSM6DSR_AODR_6664HZ);
 **************************************************************/
static void lsm6dsr_set_afs_aodr(Lsm6dsr_Afs_t afs, Lsm6dsr_Aodr_t aodr)
{
    imu_write_reg(LSM6DSR_CTRL1_XL, (aodr << 4) | (afs << 2));

    switch (afs)
    {
    case LSM6DSR_AFS_2G:
        g_acc_scale = 0.061f / 1000.0f;
        break;
    case LSM6DSR_AFS_4G:
        g_acc_scale = 0.122f / 1000.0f;
        break;
    case LSM6DSR_AFS_8G:
        g_acc_scale = 0.244f / 1000.0f;
        break;
    case LSM6DSR_AFS_16G:
        g_acc_scale = 0.488f / 1000.0f;
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
 *  @Sample usage:     lsm6dsr_set_gfs_godr(LSM6DSR_GFS_2000DPS, LSM6DSR_GODR_6664HZ);
 **************************************************************/
static void lsm6dsr_set_gfs_godr(Lsm6dsr_Gfs_t gfs, Lsm6dsr_Godr_t godr)
{
    imu_write_reg(LSM6DSR_CTRL2_G, (godr << 4) | (gfs << 1));

    switch (gfs)
    {
    case LSM6DSR_GFS_125DPS:
        g_gyro_scale = 4.375f / 1000.0f;
        break;
    case LSM6DSR_GFS_250DPS:
        g_gyro_scale = 8.75f / 1000.0f;
        break;
    case LSM6DSR_GFS_500DPS:
        g_gyro_scale = 17.50f / 1000.0f;
        break;
    case LSM6DSR_GFS_1000DPS:
        g_gyro_scale = 35.0f / 1000.0f;
        break;
    case LSM6DSR_GFS_2000DPS:
        g_gyro_scale = 70.0f / 1000.0f;
        break;
    case LSM6DSR_GFS_4000DPS:
        g_gyro_scale = 140.0f / 1000.0f;
        break;
    default:
        g_gyro_scale = 1.0f;
        break;
    }
}

/***************************************************************
 *  @brief     初始化LSM6DSR传感器
 *  @param     None
 *  @Sample usage:     lsm6dsr_init();
 **************************************************************/
void lsm6dsr_init(void)
{
    imu_init();

    lsm6dsr_check_id();

    imu_write_reg(LSM6DSR_CTRL3_C, 0x01);
    delay_ms(10);

    lsm6dsr_set_afs_aodr(LSM6DSR_AFS_16G, LSM6DSR_AODR_6664HZ);
    lsm6dsr_set_gfs_godr(LSM6DSR_GFS_2000DPS, LSM6DSR_GODR_6664HZ);

    imu_write_reg(LSM6DSR_CTRL6_C, 0x00);
    imu_write_reg(LSM6DSR_CTRL7_G, 0x00);

    delay_ms(10);
}

/***************************************************************
 *  @brief     从传感器读取最新的加速度计数据
 *  @param     None
 *  @Sample usage:     lsm6dsr_read_acc();
 **************************************************************/
void lsm6dsr_read_acc(void)
{
    uint8_t data_buffer[6];
    imu_read_regs(LSM6DSR_OUTX_L_A, data_buffer, 6);

    // 保存原始值
    lsm6dsr_acc_raw_x = (int16_t)(((uint16_t)data_buffer[1] << 8) | data_buffer[0]);
    lsm6dsr_acc_raw_y = (int16_t)(((uint16_t)data_buffer[3] << 8) | data_buffer[2]);
    lsm6dsr_acc_raw_z = (int16_t)(((uint16_t)data_buffer[5] << 8) | data_buffer[4]);

    g_lsm6dsr_data.acc.x = g_acc_scale * lsm6dsr_acc_raw_x;
    g_lsm6dsr_data.acc.y = g_acc_scale * lsm6dsr_acc_raw_y;
    g_lsm6dsr_data.acc.z = g_acc_scale * lsm6dsr_acc_raw_z;
}

/***************************************************************
 *  @brief     从传感器读取最新的陀螺仪数据
 *  @param     None
 *  @Sample usage:     lsm6dsr_read_gyro();
 **************************************************************/
void lsm6dsr_read_gyro(void)
{
    uint8_t data_buffer[6];
    imu_read_regs(LSM6DSR_OUTX_L_G, data_buffer, 6);

    // 保存原始值
    lsm6dsr_gyro_raw_x = (int16_t)(((uint16_t)data_buffer[1] << 8) | data_buffer[0]);
    lsm6dsr_gyro_raw_y = (int16_t)(((uint16_t)data_buffer[3] << 8) | data_buffer[2]);
    lsm6dsr_gyro_raw_z = (int16_t)(((uint16_t)data_buffer[5] << 8) | data_buffer[4]);

    g_lsm6dsr_data.gyro.x = g_gyro_scale * lsm6dsr_gyro_raw_x;
    g_lsm6dsr_data.gyro.y = g_gyro_scale * lsm6dsr_gyro_raw_y;
    g_lsm6dsr_data.gyro.z = g_gyro_scale * lsm6dsr_gyro_raw_z;
}

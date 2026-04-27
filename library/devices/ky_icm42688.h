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
 * 文件名：ky_icm45686.h
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
#ifndef __KY_ICM42688_H__
#define __KY_ICM42688_H__

#include "ky_imu_base.h"
#include "ky_math.h"
#include "ky_typedef.h"

typedef enum
{
    ICM42688_AFS_16G = 0x00, // 寄存器值 000
    ICM42688_AFS_8G  = 0x01, // 寄存器值 001
    ICM42688_AFS_4G  = 0x02, // 寄存器值 010
    ICM42688_AFS_2G  = 0x03  // 寄存器值 011
} ICM42688_Afs_t;

typedef enum
{
    ICM42688_GFS_2000DPS   = 0x00, // 000
    ICM42688_GFS_1000DPS   = 0x01, // 001
    ICM42688_GFS_500DPS    = 0x02, // 010
    ICM42688_GFS_250DPS    = 0x03, // 011
    ICM42688_GFS_125DPS    = 0x04, // 100
    ICM42688_GFS_62_5DPS   = 0x05, // 101
    ICM42688_GFS_31_25DPS  = 0x06, // 110
    ICM42688_GFS_15_625DPS = 0x07  // 111
} ICM42688_Gfs_t;

typedef enum
{
    ICM42688_AODR_32KHZ    = 0x01,
    ICM42688_AODR_16KHZ    = 0x02,
    ICM42688_AODR_8KHZ     = 0x03,
    ICM42688_AODR_4KHZ     = 0x04,
    ICM42688_AODR_2KHZ     = 0x05,
    ICM42688_AODR_1KHZ     = 0x06,
    ICM42688_AODR_500HZ    = 0x07,
    ICM42688_AODR_200HZ    = 0x08,
    ICM42688_AODR_100HZ    = 0x09,
    ICM42688_AODR_50HZ     = 0x0A,
    ICM42688_AODR_25HZ     = 0x0B,
    ICM42688_AODR_12_5HZ   = 0x0C,
    ICM42688_AODR_6_25HZ   = 0x0D,
    ICM42688_AODR_3_125HZ  = 0x0E,
    ICM42688_AODR_1_5625HZ = 0x0F
} ICM42688_Aodr_t;

typedef enum
{
    ICM42688_GODR_32KHZ    = 0x01,
    ICM42688_GODR_16KHZ    = 0x02,
    ICM42688_GODR_8KHZ     = 0x03,
    ICM42688_GODR_4KHZ     = 0x04,
    ICM42688_GODR_2KHZ     = 0x05,
    ICM42688_GODR_1KHZ     = 0x06,
    ICM42688_GODR_500HZ    = 0x07,
    ICM42688_GODR_200HZ    = 0x08,
    ICM42688_GODR_100HZ    = 0x09,
    ICM42688_GODR_50HZ     = 0x0A,
    ICM42688_GODR_25HZ     = 0x0B,
    ICM42688_GODR_12_5HZ   = 0x0C
} ICM42688_Godr_t;

// 陀螺仪数据
extern Imu_Data_t g_icm42688_data;

// 原始陀螺仪数据
extern int16_t icm42688_gyro_raw_x, icm42688_gyro_raw_y, icm42688_gyro_raw_z;
// 原始加速度数据
extern int16_t icm42688_acc_raw_x, icm42688_acc_raw_y, icm42688_acc_raw_z;

// 初始化ICM42688
void icm42688_init(void);
// 读取加速度数据
void icm42688_read_acc(void);
// 读取陀螺仪数据
void icm42688_read_gyro(void);
// 读取温度数据
void icm42688_read_temp(void);

// ICM42688寄存器地址定义
#define ICM42688_REG_BANK_SEL 0x76 // bank选择寄存器

/************************************ bank0寄存器 **************************************/
#define ICM42688_DEVICE_CONFIG                      0x11
#define ICM42688_DRIVE_CONFIG                       0x13
#define ICM42688_INT_CONFIG                         0x14
#define ICM42688_FIFO_CONFIG                        0x16

// 传感器数据寄存器
#define ICM42688_TEMP_DATA1                         0x1D
#define ICM42688_TEMP_DATA0                         0x1E
#define ICM42688_ACCEL_DATA_X1                      0x1F
#define ICM42688_ACCEL_DATA_X0                      0x20
#define ICM42688_ACCEL_DATA_Y1                      0x21
#define ICM42688_ACCEL_DATA_Y0                      0x22
#define ICM42688_ACCEL_DATA_Z1                      0x23
#define ICM42688_ACCEL_DATA_Z0                      0x24
#define ICM42688_GYRO_DATA_X1                       0x25
#define ICM42688_GYRO_DATA_X0                       0x26
#define ICM42688_GYRO_DATA_Y1                       0x27
#define ICM42688_GYRO_DATA_Y0                       0x28
#define ICM42688_GYRO_DATA_Z1                       0x29
#define ICM42688_GYRO_DATA_Z0                       0x2A

// 中断与FIFO状态
#define ICM42688_INT_STATUS                         0x2D
#define ICM42688_FIFO_COUNTH                        0x2E
#define ICM42688_FIFO_COUNTL                        0x2F
#define ICM42688_FIFO_DATA                          0x30

// 核心配置寄存器
#define ICM42688_SIGNAL_PATH_RESET                  0x4B
#define ICM42688_INTF_CONFIG0                       0x4C
#define ICM42688_PWR_MGMT0                          0x4E
#define ICM42688_GYRO_CONFIG0                       0x4F
#define ICM42688_ACCEL_CONFIG0                      0x50
#define ICM42688_GYRO_ACCEL_CONFIG0                 0x52
#define ICM42688_INT_SOURCE0                        0x65
#define ICM42688_WHO_AM_I                           0x75

/************************************ bank1寄存器 **************************************/
#define ICM42688_SENSOR_CONFIG0                     0x03
#define ICM42688_GYRO_CONFIG_STATIC2                0x0B
#define ICM42688_GYRO_CONFIG_STATIC3                0x0C
#define ICM42688_GYRO_CONFIG_STATIC10               0x13
#define ICM42688_INTF_CONFIG4                       0x7A
#define ICM42688_INTF_CONFIG6                       0x7C

/************************************ bank4寄存器 **************************************/
#define ICM42688_ACCEL_WOM_X_THR                    0x4A
#define ICM42688_ACCEL_WOM_Y_THR                    0x4B
#define ICM42688_ACCEL_WOM_Z_THR                    0x4C
// 硬件零偏校准 (OFFSET)
#define ICM42688_OFFSET_USER0                       0x77 // Gyro X [7:0]
#define ICM42688_OFFSET_USER1                       0x78 // Gyro Y[11:8], Gyro X[11:8]
#define ICM42688_OFFSET_USER2                       0x79 // Gyro Y [7:0]
#define ICM42688_OFFSET_USER3                       0x7A // Gyro Z [7:0]
#define ICM42688_OFFSET_USER4                       0x7B // Accel X[11:8], Gyro Z[11:8]
#define ICM42688_OFFSET_USER5                       0x7C // Accel X [7:0]
#define ICM42688_OFFSET_USER6                       0x7D // Accel Y [7:0]
#define ICM42688_OFFSET_USER7                       0x7E // Accel Z[11:8], Accel Y[11:8]
#define ICM42688_OFFSET_USER8                       0x7F // Accel Z [7:0]

#endif

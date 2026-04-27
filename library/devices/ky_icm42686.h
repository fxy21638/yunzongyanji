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
 * 2026.02.04 |   xiao   | V2.0
 *********************************************************************************/
#ifndef __KY_ICM42686_H__
#define __KY_ICM42686_H__

#include "ky_imu_base.h"
#include "ky_math.h"
#include "ky_typedef.h"

// 加速度计满量程范围选择 (ACCEL_FS_SEL)
typedef enum
{
    ICM42686_AFS_32G = 0x00, // 000: ±32g (Default)
    ICM42686_AFS_16G = 0x01, // 001: ±16g
    ICM42686_AFS_8G  = 0x02, // 010: ±8g
    ICM42686_AFS_4G  = 0x03, // 011: ±4g
    ICM42686_AFS_2G  = 0x04  // 100: ±2g
} ICM42686_Afs_t;

// 陀螺仪满量程范围选择 (GYRO_FS_SEL)
typedef enum
{
    ICM42686_GFS_4000DPS   = 0x00, // 000: ±4000dps (Default)
    ICM42686_GFS_2000DPS   = 0x01, // 001: ±2000dps
    ICM42686_GFS_1000DPS   = 0x02, // 010: ±1000dps
    ICM42686_GFS_500DPS    = 0x03, // 011: ±500dps
    ICM42686_GFS_250DPS    = 0x04, // 100: ±250dps
    ICM42686_GFS_125DPS    = 0x05, // 101: ±125dps
    ICM42686_GFS_62_5DPS   = 0x06, // 110: ±62.5dps
    ICM42686_GFS_31_25DPS  = 0x07  // 111: ±31.25dps
} ICM42686_Gfs_t;

// 加速度计输出速率 (ACCEL_ODR)
typedef enum
{
    ICM42686_AODR_32KHZ    = 0x01, // LN mode
    ICM42686_AODR_16KHZ    = 0x02, // LN mode
    ICM42686_AODR_8KHZ     = 0x03, // LN mode
    ICM42686_AODR_4KHZ     = 0x04, // LN mode
    ICM42686_AODR_2KHZ     = 0x05, // LN mode
    ICM42686_AODR_1KHZ     = 0x06, // LN mode (Default)
    ICM42686_AODR_500HZ    = 0x07, // LP or LN
    ICM42686_AODR_200HZ    = 0x08,
    ICM42686_AODR_100HZ    = 0x09,
    ICM42686_AODR_50HZ     = 0x0A,
    ICM42686_AODR_25HZ     = 0x0B,
    ICM42686_AODR_12_5HZ   = 0x0C,
    ICM42686_AODR_6_25HZ   = 0x0D, // LP mode only
    ICM42686_AODR_3_125HZ  = 0x0E, // LP mode only
    ICM42686_AODR_1_5625HZ = 0x0F  // LP mode only
} ICM42686_Aodr_t;

// 陀螺仪输出速率 (GYRO_ODR)
typedef enum
{
    ICM42686_GODR_32KHZ    = 0x01,
    ICM42686_GODR_16KHZ    = 0x02,
    ICM42686_GODR_8KHZ     = 0x03,
    ICM42686_GODR_4KHZ     = 0x04,
    ICM42686_GODR_2KHZ     = 0x05,
    ICM42686_GODR_1KHZ     = 0x06, // Default
    ICM42686_GODR_500HZ    = 0x0F, 
    ICM42686_GODR_200HZ    = 0x07,
    ICM42686_GODR_100HZ    = 0x08,
    ICM42686_GODR_50HZ     = 0x09,
    ICM42686_GODR_25HZ     = 0x0A,
    ICM42686_GODR_12_5HZ   = 0x0B
} ICM42686_Godr_t;

// 陀螺仪数据结构体
extern Imu_Data_t g_icm42686_data;

// 原始数据
extern int16_t icm42686_gyro_raw_x, icm42686_gyro_raw_y, icm42686_gyro_raw_z;
extern int16_t icm42686_acc_raw_x, icm42686_acc_raw_y, icm42686_acc_raw_z;

// 初始化
void icm42686_init(void);
// 读取加速度计数据
void icm42686_read_acc(void);
// 读取陀螺仪数据
void icm42686_read_gyro(void);
// 读取温度数据
void icm42686_read_temp(void);

#define ICM42686_REG_BANK_SEL               0x76 // Bank 选择

/************************************ User Bank 0 **************************************/
#define ICM42686_DEVICE_CONFIG              0x11
#define ICM42686_DRIVE_CONFIG               0x13
#define ICM42686_INT_CONFIG                 0x14
#define ICM42686_FIFO_CONFIG                0x16

// 传感器数据寄存器
#define ICM42686_TEMP_DATA1                 0x1D
#define ICM42686_TEMP_DATA0                 0x1E
#define ICM42686_ACCEL_DATA_X1              0x1F
#define ICM42686_ACCEL_DATA_X0              0x20
#define ICM42686_ACCEL_DATA_Y1              0x21
#define ICM42686_ACCEL_DATA_Y0              0x22
#define ICM42686_ACCEL_DATA_Z1              0x23
#define ICM42686_ACCEL_DATA_Z0              0x24
#define ICM42686_GYRO_DATA_X1               0x25
#define ICM42686_GYRO_DATA_X0               0x26
#define ICM42686_GYRO_DATA_Y1               0x27
#define ICM42686_GYRO_DATA_Y0               0x28
#define ICM42686_GYRO_DATA_Z1               0x29
#define ICM42686_GYRO_DATA_Z0               0x2A

// 中断与FIFO状态
#define ICM42686_INT_STATUS                 0x2D
#define ICM42686_FIFO_COUNTH                0x2E
#define ICM42686_FIFO_COUNTL                0x2F
#define ICM42686_FIFO_DATA                  0x30

// 核心配置寄存器
#define ICM42686_SIGNAL_PATH_RESET          0x4B
#define ICM42686_INTF_CONFIG0               0x4C
#define ICM42686_PWR_MGMT0                  0x4E
#define ICM42686_GYRO_CONFIG0               0x4F
#define ICM42686_ACCEL_CONFIG0              0x50
#define ICM42686_GYRO_ACCEL_CONFIG0         0x52
#define ICM42686_INT_SOURCE0                0x65
#define ICM42686_WHO_AM_I                   0x75 // 默认值 0x44

/************************************ User Bank 1 **************************************/
#define ICM42686_SENSOR_CONFIG0             0x03
#define ICM42686_GYRO_CONFIG_STATIC2        0x0B
#define ICM42686_GYRO_CONFIG_STATIC3        0x0C
#define ICM42686_GYRO_CONFIG_STATIC10       0x13
#define ICM42686_INTF_CONFIG4               0x7A
#define ICM42686_INTF_CONFIG6               0x7C

/************************************ User Bank 4 **************************************/
#define ICM42686_ACCEL_WOM_X_THR            0x4A
#define ICM42686_ACCEL_WOM_Y_THR            0x4B
#define ICM42686_ACCEL_WOM_Z_THR            0x4C
// 硬件零偏校准 (OFFSET)
#define ICM42686_OFFSET_USER0               0x77 
#define ICM42686_OFFSET_USER1               0x78 
#define ICM42686_OFFSET_USER2               0x79 
#define ICM42686_OFFSET_USER3               0x7A 
#define ICM42686_OFFSET_USER4               0x7B 
#define ICM42686_OFFSET_USER5               0x7C 
#define ICM42686_OFFSET_USER6               0x7D 
#define ICM42686_OFFSET_USER7               0x7E 
#define ICM42686_OFFSET_USER8               0x7F 

#endif
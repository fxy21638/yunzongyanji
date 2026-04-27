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
 * 文件名：ky_imu_base.h
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
#ifndef __KY_IMU_BASE_H__
#define __KY_IMU_BASE_H__

#include "ky_spi.h"
#include "ky_typedef.h"
#include "stc32g144k246.h"

#define IMU_SPI SPI_2                       // SPI编号
#define IMU_SPI_SCL SPI2_SCLK_P05           // SCL引脚
#define IMU_SPI_SDA SPI2_MOSI_P03           // MOSI引脚
#define IMU_SPI_SDO SPI2_MISO_P04           // MISO引脚
#define IMU_SPI_CS_PIN P02                  // CS引脚
#define IMU_SPI_CS_GPIO GPIO_P02            // GPIO_P02
#define IMU_SPI_MODE SPI_MODE_0             // SPI_MODE_0
#define IMU_SPI_BAUD 10000000               // 10MHz

#define IMU_SET_SPI_CS(x) (IMU_SPI_CS_PIN = (x))

typedef struct { 
    float x;            // x轴
    float y;            // y轴
    float z;            // z轴
} Imu_Axis_t;

typedef struct {
    Imu_Axis_t acc;     // 加速度
    Imu_Axis_t gyro;    // 陀螺仪
    Imu_Axis_t mag;     // 磁力计
    float temperature;  // 温度
} Imu_Data_t;

void imu_write_reg  (uint8_t reg, uint8_t dat);
void imu_read_regs  (uint8_t reg, uint8_t *buffer, uint16_t length);
void imu_init       (void);

#endif

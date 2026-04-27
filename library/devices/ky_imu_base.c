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
 * 文件名：ky_imu_base.c
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
#include "ky_imu_base.h"
#include "ky_delay.h"
#include "ky_gpio.h"


/***************************************************************
 *  @brief     向IMU传感器写入单个寄存器
 *  @param     reg     目标寄存器地址
 *  @param     dat     要写入的8位数据
 *  @Sample usage:     imu_write_reg(0x20, 0x47);
 **************************************************************/
void imu_write_reg(uint8_t reg, uint8_t dat)
{
    uint8_t buffer[2];
    buffer[0] = reg;
    buffer[1] = dat;

    IMU_SET_SPI_CS(0);
    spi_send_buffer(IMU_SPI, buffer, 2);
    IMU_SET_SPI_CS(1);
}

/***************************************************************
 *  @brief     从IMU传感器连续读取多个寄存器
 *  @param     reg     起始寄存器地址
 *  @param     buffer  用于存储读取数据的缓冲区
 *  @param     length  要读取的字节数
 *  @Sample usage:     uint8_t data[6];
 *                     imu_read_regs(0x28, data, 6);
 **************************************************************/
void imu_read_regs(uint8_t reg, uint8_t *buffer, uint16_t length)
{
    IMU_SET_SPI_CS(0);
    spi_send_byte(IMU_SPI, reg | 0x80);
    spi_read_buffer(IMU_SPI, buffer, length);
    IMU_SET_SPI_CS(1);
}

/***************************************************************
 *  @brief     通用IMU传感器初始化
 *  @param     None
 *  @Sample usage:     imu_init();
 **************************************************************/
void imu_init(void)
{
    spi_init(IMU_SPI, IMU_SPI_MODE, IMU_SPI_BAUD, IMU_SPI_SCL, IMU_SPI_SDA, IMU_SPI_SDO);
    gpio_init(IMU_SPI_CS_GPIO, GPIO_MODE_OUT_PP, GPIO_HIGH);

    delay_ms(10);
}




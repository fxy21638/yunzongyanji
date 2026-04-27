/*********************************************************************************
 * 项目名称:[STC32G144K246开源库] 开源组件库
 * 版权所有:[2025] [北京科宇通博科技有限公司]
 *
 * 许可协议:采用 GNU GPL v3.0 开源许可
 * 您可依据协议进行二次开发、传播,但须保留原始版权信息
 * 协议详情参见:https://www.gnu.org/licenses/gpl-3.0.html
 *
 * 免责声明:本组件库仅提供技术参考,使用方需自行验证适用性
 *
 * 协议文件:GPL v3.0 完整文本位于根目录下
 *
 * === 文件信息 ===
 * 文件名:[ky_spi.h]
 * 开发单位:北京科宇通博科技有限公司
 * 适用环境:[Keil C251 / STC32G系列单片机]
 * 官方渠道:
 *   -
 * 代码仓库:[https://gitee.com/beijing-keyu---jiangxi/KEYU_AI8052U_OpenLibrary]
 *   - 淘宝店铺:https://kyznc.taobao.com/
 *   - 技术支持:QQ群 974530818
 *
 * === 修订记录 ===
 * 日期       |  开发者  | 变更说明
 * -----------|----------|----------------------
 * 2025.12.22 |   xiao   | V2.0
 *********************************************************************************/
#ifndef __KY_SPI_H__
#define __KY_SPI_H__

#include "ky_gpio.h"
#include "ky_typedef.h"

#define STC32_FLASH_ADDR_START 0x800000

typedef enum
{
	SPI_1,
	SPI_2,
	SPI_3
} SPI_Index_t;

typedef enum
{
	SPI_MODE_0 = 0,
	SPI_MODE_1,
	SPI_MODE_2,
	SPI_MODE_3
} SPI_Mode_t;

typedef enum
{
	// SPI1 通道1 (P1组: SCK=P1.5, MOSI=P1.3, MISO=P1.4)
	SPI1_SCLK_P15 = (0 << 13 | 0 << 9 | 0 << 7 | GPIO_P15),
	SPI1_MOSI_P13 = (0 << 13 | 1 << 9 | 0 << 7 | GPIO_P13),
	SPI1_MISO_P14 = (0 << 13 | 2 << 9 | 0 << 7 | GPIO_P14),

	// SPI1 通道2 (P2组: SCK=P2.5, MOSI=P2.3, MISO=P2.4)
	SPI1_SCLK_P25 = (0 << 13 | 0 << 9 | 1 << 7 | GPIO_P25),
	SPI1_MOSI_P23 = (0 << 13 | 1 << 9 | 1 << 7 | GPIO_P23),
	SPI1_MISO_P24 = (0 << 13 | 2 << 9 | 1 << 7 | GPIO_P24),

	// SPI1 通道3 (P4组: SCK=P4.3, MOSI=P4.0, MISO=P4.1)
	SPI1_SCLK_P43 = (0 << 13 | 0 << 9 | 2 << 7 | GPIO_P43),
	SPI1_MOSI_P40 = (0 << 13 | 1 << 9 | 2 << 7 | GPIO_P40),
	SPI1_MISO_P41 = (0 << 13 | 2 << 9 | 2 << 7 | GPIO_P41),

	// SPI1 通道4 (P7组: SCK=P7.7, MOSI=P7.5, MISO=P7.6)
	SPI1_SCLK_P77 = (0 << 13 | 0 << 9 | 3 << 7 | GPIO_P77),
	SPI1_MOSI_P75 = (0 << 13 | 1 << 9 | 3 << 7 | GPIO_P75),
	SPI1_MISO_P76 = (0 << 13 | 2 << 9 | 3 << 7 | GPIO_P76),

	// SPI2 通道1 (P6组: SCK=P6.7, MOSI=P6.5, MISO=P6.6)
	SPI2_SCLK_P67 = (1 << 13 | 0 << 9 | 0 << 7 | GPIO_P67),
	SPI2_MOSI_P65 = (1 << 13 | 1 << 9 | 0 << 7 | GPIO_P65),
	SPI2_MISO_P66 = (1 << 13 | 2 << 9 | 0 << 7 | GPIO_P66),

	// SPI2 通道2 (P0组: SCK=P0.5, MOSI=P0.3, MISO=P0.4)
	SPI2_SCLK_P05 = (1 << 13 | 0 << 9 | 1 << 7 | GPIO_P05),
	SPI2_MOSI_P03 = (1 << 13 | 1 << 9 | 1 << 7 | GPIO_P03),
	SPI2_MISO_P04 = (1 << 13 | 2 << 9 | 1 << 7 | GPIO_P04),

	// SPI2 通道3 (PB组: SCK=PB.4, MOSI=PB.2, MISO=PB.3)
	SPI2_SCLK_PB4 = (1 << 13 | 0 << 9 | 2 << 7 | GPIO_PB4),
	SPI2_MOSI_PB2 = (1 << 13 | 1 << 9 | 2 << 7 | GPIO_PB2),
	SPI2_MISO_PB3 = (1 << 13 | 2 << 9 | 2 << 7 | GPIO_PB3),

	// SPI2 通道4 (P8组: SCK=P8.3, MOSI=P8.1, MISO=P8.2)
	SPI2_SCLK_P83 = (1 << 13 | 0 << 9 | 3 << 7 | GPIO_P83),
	SPI2_MOSI_P81 = (1 << 13 | 1 << 9 | 3 << 7 | GPIO_P81),
	SPI2_MISO_P82 = (1 << 13 | 2 << 9 | 3 << 7 | GPIO_P82),

	// SPI3 通道1 (P2组: SCK=P2.5, MOSI=P2.3, MISO=P2.4)
	SPI3_SCLK_P25 = (2 << 13 | 0 << 9 | 0 << 7 | GPIO_P25),
	SPI3_MOSI_P23 = (2 << 13 | 1 << 9 | 0 << 7 | GPIO_P23),
	SPI3_MISO_P24 = (2 << 13 | 2 << 9 | 0 << 7 | GPIO_P24),

	// SPI3 通道2 (P7组: SCK=P7.3, MOSI=P7.1, MISO=P7.2)
	SPI3_SCLK_P73 = (2 << 13 | 0 << 9 | 1 << 7 | GPIO_P73),
	SPI3_MOSI_P71 = (2 << 13 | 1 << 9 | 1 << 7 | GPIO_P71),
	SPI3_MISO_P72 = (2 << 13 | 2 << 9 | 1 << 7 | GPIO_P72),

	// SPI3 通道3 (P8组: SCK=P8.7, MOSI=P8.5, MISO=P8.6)
	SPI3_SCLK_P87 = (2 << 13 | 0 << 9 | 2 << 7 | GPIO_P87),
	SPI3_MOSI_P85 = (2 << 13 | 1 << 9 | 2 << 7 | GPIO_P85),
	SPI3_MISO_P86 = (2 << 13 | 2 << 9 | 2 << 7 | GPIO_P86),

	// SPI3 通道4 (P9组: SCK=P9.3, MOSI=P9.1, MISO=P9.2)
	SPI3_SCLK_P93 = (2 << 13 | 0 << 9 | 3 << 7 | GPIO_P93),
	SPI3_MOSI_P91 = (2 << 13 | 1 << 9 | 3 << 7 | GPIO_P91),
	SPI3_MISO_P92 = (2 << 13 | 2 << 9 | 3 << 7 | GPIO_P92),
} SPI_Pin_t;

// 初始化SPI
void spi_init(SPI_Index_t spiIndex, SPI_Mode_t mode, uint32_t baud, SPI_Pin_t sck_pin, SPI_Pin_t mosi_pin,
			  SPI_Pin_t miso_pin);
// 发送一个字节
void spi_send_byte(SPI_Index_t spiIndex, const uint8_t dat);
// 读取一个字节
uint8_t spi_read_byte(SPI_Index_t spiIndex);
// 发送一个缓冲区
void spi_send_buffer(SPI_Index_t spiIndex, const uint8_t *dat, uint32_t length);
// 读取一个缓冲区
void spi_read_buffer(SPI_Index_t spiIndex, uint8_t *dat, uint32_t length);

// 初始化SPI DMA (同一时刻只能使用一个SPI)
void spi_dma_init(SPI_Index_t spiIndex, SPI_Mode_t mode, uint32_t baud, SPI_Pin_t sck_pin, SPI_Pin_t mosi_pin,
				  SPI_Pin_t miso_pin);
// 发送16位数组
void spi_dma_send_16bit_array(SPI_Index_t spiIndex, const uint16_t *dat, uint32_t length);
// 发送8位数组
void spi_dma_send_8bit_array(SPI_Index_t spiIndex, const uint8_t *dat, uint32_t length);
// 读取16位数组
void spi_dma_read_16bit_array(SPI_Index_t spiIndex, uint16_t *dat, uint32_t length);
// 读取8位数组
void spi_dma_read_8bit_array(SPI_Index_t spiIndex, uint8_t *dat, uint32_t length);
// 发送一个字节
void spi_dma_send_byte(SPI_Index_t spiIndex, const uint8_t dat);
// 读取一个字节
void spi_dma_read_byte(SPI_Index_t spiIndex, uint8_t *dat);

#endif

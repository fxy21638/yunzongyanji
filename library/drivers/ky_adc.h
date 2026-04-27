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
 * 文件名：[ky_adc.h]
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
#ifndef __KY_ADC_H__
#define __KY_ADC_H__

#include "ky_gpio.h"
#include "ky_typedef.h"

typedef enum
{
	// ADC1 通道
	ADC1_CH0_P10 = 1 << 12 | 0 << 8 | GPIO_P10,
	ADC1_CH1_P11 = 1 << 12 | 1 << 8 | GPIO_P11,
	ADC1_CH2_P12 = 1 << 12 | 2 << 8 | GPIO_P12,
	ADC1_CH3_P13 = 1 << 12 | 3 << 8 | GPIO_P13,
	ADC1_CH4_P14 = 1 << 12 | 4 << 8 | GPIO_P14,
	ADC1_CH5_P15 = 1 << 12 | 5 << 8 | GPIO_P15,
	ADC1_CH6_P16 = 1 << 12 | 6 << 8 | GPIO_P16,
	ADC1_CH7_P17 = 1 << 12 | 7 << 8 | GPIO_P17,
	ADC1_CH8_P00 = 1 << 12 | 8 << 8 | GPIO_P00,
	ADC1_CH9_P01 = 1 << 12 | 9 << 8 | GPIO_P01,
	ADC1_CH10_P02 = 1 << 12 | 10 << 8 | GPIO_P02,
	ADC1_CH15_BGV = 1 << 12 | 15 << 8 | 0xFF,

	// ADC2 通道
	ADC2_CH0_P00 = 2 << 12 | 0 << 8 | GPIO_P00,
	ADC2_CH1_P01 = 2 << 12 | 1 << 8 | GPIO_P01,
	ADC2_CH2_P02 = 2 << 12 | 2 << 8 | GPIO_P02,
	ADC2_CH3_P03 = 2 << 12 | 3 << 8 | GPIO_P03,
	ADC2_CH4_P04 = 2 << 12 | 4 << 8 | GPIO_P04,
	ADC2_CH5_P05 = 2 << 12 | 5 << 8 | GPIO_P05,
	ADC2_CH6_P06 = 2 << 12 | 6 << 8 | GPIO_P06,
	ADC2_CH7_P07 = 2 << 12 | 7 << 8 | GPIO_P07,
	ADC2_CH8_P60 = 2 << 12 | 8 << 8 | GPIO_P60,
	ADC2_CH9_P61 = 2 << 12 | 9 << 8 | GPIO_P61,
	ADC2_CH10_P62 = 2 << 12 | 10 << 8 | GPIO_P62,
	ADC2_CH15_BGV = 2 << 12 | 15 << 8 | 0xFF
} ADC_Channel_t;

typedef enum
{
	ADC_CLK_DIV_2 = 0,	 // 时钟分频2
	ADC_CLK_DIV_4 = 1,	 // 时钟分频4
	ADC_CLK_DIV_6 = 2,	 // 时钟分频6
	ADC_CLK_DIV_8 = 3,	 // 时钟分频8
	ADC_CLK_DIV_10 = 4,	 // 时钟分频10
	ADC_CLK_DIV_12 = 5,	 // 时钟分频12
	ADC_CLK_DIV_14 = 6,	 // 时钟分频14
	ADC_CLK_DIV_16 = 7,	 // 时钟分频16
	ADC_CLK_DIV_18 = 8,	 // 时钟分频18
	ADC_CLK_DIV_20 = 9,	 // 时钟分频20
	ADC_CLK_DIV_22 = 10, // 时钟分频22
	ADC_CLK_DIV_24 = 11, // 时钟分频24
	ADC_CLK_DIV_26 = 12, // 时钟分频26
	ADC_CLK_DIV_28 = 13, // 时钟分频28
	ADC_CLK_DIV_30 = 14, // 时钟分频30
	ADC_CLK_DIV_32 = 15	 // 时钟分频32
} ADC_Clock_t;

typedef enum
{
	ADC_RES_12BIT = 1, // 12位分辨率
	ADC_RES_8BIT = 0   // 8位分辨率
} ADC_Resolution_t;

typedef enum
{
	ADC_DMA_CV_1 = 0x00,   // 1次转换
	ADC_DMA_CV_2 = 0x08,   // 2次转换
	ADC_DMA_CV_4 = 0x09,   // 4次转换
	ADC_DMA_CV_8 = 0x0A,   // 8次转换
	ADC_DMA_CV_16 = 0x0B,  // 16次转换
	ADC_DMA_CV_32 = 0x0C,  // 32次转换
	ADC_DMA_CV_64 = 0x0D,  // 64次转换
	ADC_DMA_CV_128 = 0x0E, // 128次转换
	ADC_DMA_CV_256 = 0x0F  // 256次转换
} ADC_DMA_CvCount_t;

// 初始化ADC
void adc_init(ADC_Channel_t ch, ADC_Clock_t clock, ADC_Resolution_t resolution);
// 读取ADC值
uint16_t adc_read(ADC_Channel_t ch);
// 读取ADC值并滤波
uint16_t adc_read_filter(ADC_Channel_t ch, uint8_t count);

// 初始化ADC DMA
void adc_dma_init(uint8_t module, uint16_t channel_mask, ADC_DMA_CvCount_t cv_count, uint16_t interval,
				  uint16_t scan_count, uint8_t *buffer);
// 启动ADC DMA
void adc_dma_start(uint8_t module);
// 检查ADC DMA是否完成
uint8_t adc_dma_is_done(uint8_t module);
// 清除ADC DMA标志
void adc_dma_clear_flag(uint8_t module);
// 获取ADC DMA结果
uint16_t adc_dma_get_result(uint8_t *buffer, uint8_t channel_index, uint16_t cv_count);

#endif

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
 * 文件名：[ky_uart.h]
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
#ifndef __KY_UART_H__
#define __KY_UART_H__

#include "ky_gpio.h"
#include "ky_typedef.h"

#define UART_GET_PINGRP(pin) ((uint8_t)(((pin) >> 8) & 0x03))
#define UART_GET_PIN(pin) ((GPIO_Pin_t)((pin) & 0xFF))

typedef enum
{
	UART_1 = 0,
	UART_2,
	UART_3,
	UART_4,
	UART_5,
	UART_6,
	UART_7,
	UART_8,
	UART_MAX
} UART_Index_t;

typedef enum
{
	// UART1 引脚组
	UART1_RX_P30 = (0 << 10 | 0 << 8 | GPIO_P30),
	UART1_TX_P31 = (0 << 10 | 0 << 8 | GPIO_P31),
	UART1_RX_P36 = (0 << 10 | 1 << 8 | GPIO_P36),
	UART1_TX_P37 = (0 << 10 | 1 << 8 | GPIO_P37),
	UART1_RX_P16 = (0 << 10 | 2 << 8 | GPIO_P16),
	UART1_TX_P17 = (0 << 10 | 2 << 8 | GPIO_P17),
	UART1_RX_P43 = (0 << 10 | 3 << 8 | GPIO_P43),
	UART1_TX_P44 = (0 << 10 | 3 << 8 | GPIO_P44),

	// UART2 引脚组
	UART2_RX_P10 = (1 << 10 | 0 << 8 | GPIO_P10),
	UART2_TX_P11 = (1 << 10 | 0 << 8 | GPIO_P11),
	UART2_RX_P46 = (1 << 10 | 1 << 8 | GPIO_P46),
	UART2_TX_P47 = (1 << 10 | 1 << 8 | GPIO_P47),
	UART2_RX_P84 = (1 << 10 | 2 << 8 | GPIO_P84),
	UART2_TX_P85 = (1 << 10 | 2 << 8 | GPIO_P85),
	UART2_RX_PA0 = (1 << 10 | 3 << 8 | GPIO_PA0),
	UART2_TX_PA1 = (1 << 10 | 3 << 8 | GPIO_PA1),

	// UART3 引脚组
	UART3_RX_P00 = (2 << 10 | 0 << 8 | GPIO_P00),
	UART3_TX_P01 = (2 << 10 | 0 << 8 | GPIO_P01),
	UART3_RX_P50 = (2 << 10 | 1 << 8 | GPIO_P50),
	UART3_TX_P51 = (2 << 10 | 1 << 8 | GPIO_P51),
	UART3_RX_P86 = (2 << 10 | 2 << 8 | GPIO_P86),
	UART3_TX_P87 = (2 << 10 | 2 << 8 | GPIO_P87),
	UART3_RX_PB6 = (2 << 10 | 3 << 8 | GPIO_PB6),
	UART3_TX_PB7 = (2 << 10 | 3 << 8 | GPIO_PB7),

	// UART4 引脚组
	UART4_RX_P02 = (3 << 10 | 0 << 8 | GPIO_P02),
	UART4_TX_P03 = (3 << 10 | 0 << 8 | GPIO_P03),
	UART4_RX_P52 = (3 << 10 | 1 << 8 | GPIO_P52),
	UART4_TX_P53 = (3 << 10 | 1 << 8 | GPIO_P53),
	UART4_RX_PA2 = (3 << 10 | 2 << 8 | GPIO_PA2),
	UART4_TX_PA3 = (3 << 10 | 2 << 8 | GPIO_PA3),

	// UART5 引脚组
	UART5_RX_P04 = (4 << 10 | 0 << 8 | GPIO_P04),
	UART5_TX_P05 = (4 << 10 | 0 << 8 | GPIO_P05),
	UART5_RX_P40 = (4 << 10 | 1 << 8 | GPIO_P40),
	UART5_TX_P41 = (4 << 10 | 1 << 8 | GPIO_P41),
	UART5_RX_P14 = (4 << 10 | 2 << 8 | GPIO_P14),
	UART5_TX_P15 = (4 << 10 | 2 << 8 | GPIO_P15),
	UART5_RX_P20 = (4 << 10 | 3 << 8 | GPIO_P20),
	UART5_TX_P21 = (4 << 10 | 3 << 8 | GPIO_P21),

	// UART6 引脚组
	UART6_RX_P06 = (5 << 10 | 0 << 8 | GPIO_P06),
	UART6_TX_P07 = (5 << 10 | 0 << 8 | GPIO_P07),
	UART6_RX_P62 = (5 << 10 | 1 << 8 | GPIO_P62),
	UART6_TX_P63 = (5 << 10 | 1 << 8 | GPIO_P63),
	UART6_RX_P32 = (5 << 10 | 2 << 8 | GPIO_P32),
	UART6_TX_P33 = (5 << 10 | 2 << 8 | GPIO_P33),
	UART6_RX_P26 = (5 << 10 | 3 << 8 | GPIO_P26),
	UART6_TX_P27 = (5 << 10 | 3 << 8 | GPIO_P27),

	// UART7 引脚组
	UART7_RX_P50 = (6 << 10 | 0 << 8 | GPIO_P50),
	UART7_TX_P51 = (6 << 10 | 0 << 8 | GPIO_P51),
	UART7_RX_PA4 = (6 << 10 | 1 << 8 | GPIO_PA4),
	UART7_TX_PA5 = (6 << 10 | 1 << 8 | GPIO_PA5),
	UART7_RX_P90 = (6 << 10 | 2 << 8 | GPIO_P90),
	UART7_TX_P91 = (6 << 10 | 2 << 8 | GPIO_P91),
	UART7_RX_P12 = (6 << 10 | 3 << 8 | GPIO_P12),
	UART7_TX_P13 = (6 << 10 | 3 << 8 | GPIO_P13),

	// UART8 引脚组
	UART8_RX_P52 = (7 << 10 | 0 << 8 | GPIO_P52),
	UART8_TX_P53 = (7 << 10 | 0 << 8 | GPIO_P53),
	UART8_RX_PA6 = (7 << 10 | 1 << 8 | GPIO_PA6),
	UART8_TX_PA7 = (7 << 10 | 1 << 8 | GPIO_PA7),
	UART8_RX_P92 = (7 << 10 | 2 << 8 | GPIO_P92),
	UART8_TX_P93 = (7 << 10 | 2 << 8 | GPIO_P93),
	UART8_RX_P60 = (7 << 10 | 3 << 8 | GPIO_P60),
	UART8_TX_P61 = (7 << 10 | 3 << 8 | GPIO_P61),
} UART_Pin_t;

typedef void (*UART_Callback_t)(uint8_t dat);
typedef void (*UART_Callback_Dma_t)(void);

// 初始化串口
void uart_init(UART_Index_t index, uint32_t baudrate, UART_Pin_t tx_pin, UART_Pin_t rx_pin);
// 发送一个字节
void uart_send_byte(UART_Index_t index, uint8_t dat);
// 发送一个缓冲区
void uart_send_buffer(UART_Index_t index, uint8_t *buffer, uint16_t len);
// 发送一个字符串
void uart_send_string(UART_Index_t index, char *str);
// 设置接收回调
void uart_set_rx_callback(UART_Index_t index, UART_Callback_t callback);
// 中断处理
void uart_isr_handler(UART_Index_t index);

// DMA 发送
void uart_dma_send(UART_Index_t index, uint8_t *buffer, uint16_t len);
// DMA 接收
void uart_dma_receive(UART_Index_t index, uint8_t *buffer, uint16_t len);
// 设置 DMA 发送回调
void uart_set_dma_tx_callback(UART_Index_t index, UART_Callback_Dma_t callback);
// 设置 DMA 接收回调
void uart_set_dma_rx_callback(UART_Index_t index, UART_Callback_Dma_t callback);
// DMA 发送中断处理
void uart_dma_tx_isr_handler(UART_Index_t index);
void uart_dma_rx_isr_handler(UART_Index_t index);

#endif

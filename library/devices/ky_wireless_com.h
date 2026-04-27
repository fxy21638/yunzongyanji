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
 * 文件名：ky_wireless_com.h
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
 * 2026.01.07 |   xiao   | V2.0 
 *********************************************************************************/
#ifndef __KY_WIRELESS_COM_H__
#define __KY_WIRELESS_COM_H__

#include "ky_uart.h"
#include "ky_ringbuffer.h"

// 默认波特率
#define WIRELESS_COM_DEFAULT_BAUD   1000000

// UART 配置
#define WIRELESS_COM_UART           UART_4
#define WIRELESS_COM_TX_PIN         UART4_TX_P53
#define WIRELESS_COM_RX_PIN         UART4_RX_P52
#define WIRELESS_COM_RTS_PIN        GPIO_PB0

// 初始化无线串口模块
uint8_t ky_wireless_com_init(uint32_t baudrate);
// 发送数据到电脑虚拟串口
void ky_wireless_com_send(uint8_t *dat, uint8_t len);
// 从电脑虚拟串口读取数据
uint8_t ky_wireless_com_read(uint8_t *buf, uint8_t max_len);

#endif

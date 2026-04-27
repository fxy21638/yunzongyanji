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
 * 文件名：ky_usb_cdc.h
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
#ifndef __KY_USB_CDC_H__
#define __KY_USB_CDC_H__

#include "ky_ringbuffer.h"
#include "config.h"

#define USB_CDC_TIMEOUT_COUNT   10000

typedef void (*usb_cdc_rx_callback_t)(uint8_t *buff, uint16_t len);

extern RingBuffer_t usb_cdc_rx_ringbuf;
extern void (*_usb_cdc_user_rx_callback)(uint8_t *buff, uint16_t len);

// 初始化USB CDC
void usb_cdc_init(void);

// 发送一个字节
void usb_cdc_send_byte(uint8_t dat);

// 发送一个缓冲区
uint16_t usb_cdc_send_buffer(const uint8_t *buff, uint16_t len);

// 发送一个字符串
uint16_t usb_cdc_send_string(const char *str);

// 设置接收回调
void usb_cdc_set_rx_callback(usb_cdc_rx_callback_t callback);


// 读取接收的数据
uint16_t usb_cdc_available(void);

// 读取一个字节
uint8_t usb_cdc_read_byte(uint8_t *dat);

// 读取一个缓冲区
uint16_t usb_cdc_read_buffer(uint8_t *buff, uint16_t len);

// 清空接收缓冲区
void usb_cdc_flush(void);

// 检查ISP命令 (用于自动ISP下载)
void usb_check_isp_command(uint8_t *buff, uint16_t len);

#endif

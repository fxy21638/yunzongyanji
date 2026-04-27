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
 * 文件名：ky_wireless_com.c
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
 * 2026.01.07 |   xiao   | V1.0 
 *********************************************************************************/
#include "ky_wireless_com.h"
#include "ky_delay.h"
#include <string.h>

// RTS控制宏
#define WIRELESS_RTS_ASSERT()   gpio_write_pin(WIRELESS_COM_RTS_PIN, GPIO_LOW)
#define WIRELESS_RTS_DEASSERT() gpio_write_pin(WIRELESS_COM_RTS_PIN, GPIO_HIGH)
// 内部缓冲区定义
#define WIRELESS_RB_SIZE   256
static uint8_t xdata wireless_buffer_storage[WIRELESS_RB_SIZE];
static uint8_t xdata wireless_buffer_storage_dma[1];
static RingBuffer_t wireless_rb;

/*********************************************************************************
 *  @brief     UART接收回调函数
 *********************************************************************************/
static void _wireless_uart_callback()
{
    uint8_t recv_byte = wireless_buffer_storage_dma[0];
    uart_dma_receive(WIRELESS_COM_UART, wireless_buffer_storage_dma, 1);
    ringbuffer_putc(&wireless_rb, recv_byte);
}

/*********************************************************************************
 *  @brief     初始化无线串口模块 (透传模式)
 *  @param     baudrate    通信波特率
 *  @return    0: 成功
 *********************************************************************************/
uint8_t ky_wireless_com_init(uint32_t baudrate)
{
    // 初始化环形缓冲区
    ringbuffer_init(&wireless_rb, wireless_buffer_storage, WIRELESS_RB_SIZE);
    gpio_init(WIRELESS_COM_RTS_PIN, GPIO_MODE_OUT_PP, GPIO_HIGH);
    WIRELESS_RTS_DEASSERT();
    uart_init(WIRELESS_COM_UART, baudrate, WIRELESS_COM_TX_PIN, WIRELESS_COM_RX_PIN);
    uart_dma_receive(WIRELESS_COM_UART, wireless_buffer_storage_dma, 1);
    // 注册接收回调，启用中断接收
    // uart_set_rx_callback(UART_8, _wireless_uart_callback);
    uart_set_dma_rx_callback(WIRELESS_COM_UART, _wireless_uart_callback);

    return 0;
}

/*********************************************************************************
 *  @brief     发送数据到电脑虚拟串口 (透传)
 *  @param     data    数据缓冲区
 *  @param     len     数据长度
 *********************************************************************************/
void ky_wireless_com_send(uint8_t *dat, uint8_t len)
{
    if (len == 0) return;
    WIRELESS_RTS_ASSERT();                          // 通知 
    uart_dma_send(WIRELESS_COM_UART, dat, len);     // 发送
    WIRELESS_RTS_DEASSERT();                        // 发送完毕，释放
}

/*********************************************************************************
 *  @brief     从电脑虚拟串口读取数据 (透传)
 *  @param     buf     用户接收缓冲区
 *  @param     max_len 缓冲区最大长度
 *  @return    实际读取的长度
 *********************************************************************************/
uint8_t ky_wireless_com_read(uint8_t *buf, uint8_t max_len)
{
    // 直接从 RingBuffer 读取指定长度的数据
    return (uint8_t)ringbuffer_read(&wireless_rb, buf, max_len);
}
 
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
 * 文件名：ky_usb_cdc.c
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
#include "ky_usb_cdc.h"
#include "stc32g144k246.h"
#include "usb.h"
#include "ky_ringbuffer.h"
#include "ky_delay.h"

#define USB_CDC_RX_BUFFER_SIZE  256

void (*_usb_cdc_user_rx_callback)(uint8_t *buff, uint16_t len) = NULL;

RingBuffer_t usb_cdc_rx_ringbuf;
static uint8_t usb_cdc_rx_buffer[USB_CDC_RX_BUFFER_SIZE];



/*********************************************************************************
 *  @brief     USB CDC 初始化
 *  @param     无
 *  @return    无
 *********************************************************************************/
void usb_cdc_init(void)
{
    ringbuffer_init(&usb_cdc_rx_ringbuf, usb_cdc_rx_buffer, USB_CDC_RX_BUFFER_SIZE);
    usb_init();
}

/*********************************************************************************
 *  @brief     检查 ISP 复位命令
 *  @param     buff  接收到的数据
 *  @param     len   数据长度
 *  @return    无
 *********************************************************************************/
void usb_check_isp_command(uint8_t *buff, uint16_t len)
{
    uint8_t isp_cmd[] = "@STCISP#";
    
    if (len < sizeof(isp_cmd) - 1)
        return;
    if (!strncmp(buff, isp_cmd, sizeof(isp_cmd) - 1)) {
            CLKSEL = 0x00;
            USBCON = 0x00;
            USBCLK &= 0xF0;
            IRC48MCR = 0x00;
            delay_ms(20);
			
            IAP_CONTR = 0x60;
    }
}

/*********************************************************************************
 *  @brief     USB CDC 发送缓冲区
 *  @param     buff  数据缓冲区指针
 *  @param     len   数据长度
 *  @return    剩余未发送字节数 (0 表示全部发送成功)
 *********************************************************************************/
uint16_t usb_cdc_send_buffer(const uint8_t *buff, uint16_t len)
{
    int32_t timeout = USB_CDC_TIMEOUT_COUNT;
    uint8_t tmp_len = 0;
    uint8_t idx = 0;
    
    if (DeviceState != DEVSTATE_CONFIGURED)
        return len;
    
    while(len > 0) {
        timeout = USB_CDC_TIMEOUT_COUNT;
        tmp_len = (len >= 64) ? 64 : len;
        
        UsbInBusy = 1;
        EUSB = 0;
        usb_write_reg(INDEX, 1);
        
        for(idx=0; idx < tmp_len; idx++)
            usb_write_reg(FIFO1, *buff++);
        
        usb_write_reg(INCSR1, INIPRDY);
        EUSB = 1;
        
        while(UsbInBusy && timeout--);
        
        if(timeout <= 0)
            return len;
        else
            len = len - tmp_len;
    }

    return 0;
}

/*********************************************************************************
 *  @brief     USB CDC 发送单字节
 *  @param     dat   要发送的字节
 *  @return    无
 *********************************************************************************/
void usb_cdc_send_byte(uint8_t dat)
{
    usb_cdc_send_buffer(&dat, 1);
}

/*********************************************************************************
 *  @brief     USB CDC 发送字符串
 *  @param     str   字符串指针
 *  @return    剩余未发送字节数
 *********************************************************************************/
uint16_t usb_cdc_send_string(const char *str)
{
    uint16_t len = 0;
    const char *p = str;
    
    while(*p++)
        len++;
    
    return usb_cdc_send_buffer((const uint8_t *)str, len);
}

/*********************************************************************************
 *  @brief     获取接收缓冲区可读数据量
 *  @param     无
 *  @return    可读字节数
 *********************************************************************************/
uint16_t usb_cdc_available(void)
{
    return (uint16_t)ringbuffer_len(&usb_cdc_rx_ringbuf);
}

/*********************************************************************************
 *  @brief     从接收缓冲区读取一个字节
 *  @param     dat   存储读取数据的指针
 *  @return    1-成功, 0-缓冲区为空
 *********************************************************************************/
uint8_t usb_cdc_read_byte(uint8_t *dat)
{
    return ringbuffer_getc(&usb_cdc_rx_ringbuf, dat);
}

/*********************************************************************************
 *  @brief     从接收缓冲区读取多个字节
 *  @param     buff  存储读取数据的缓冲区
 *  @param     len   要读取的字节数
 *  @return    实际读取的字节数
 *********************************************************************************/
uint16_t usb_cdc_read_buffer(uint8_t *buff, uint16_t len)
{
    return (uint16_t)ringbuffer_read(&usb_cdc_rx_ringbuf, buff, len);
}

/*********************************************************************************
 *  @brief     清空接收缓冲区
 *  @param     无
 *  @return    无
 *********************************************************************************/
void usb_cdc_flush(void)
{
    ringbuffer_clear(&usb_cdc_rx_ringbuf);
}

/*********************************************************************************
 *  @brief     设置接收回调函数
 *  @param     callback  回调函数指针
 *  @return    无
 *********************************************************************************/
void usb_cdc_set_rx_callback(usb_cdc_rx_callback_t callback)
{
    _usb_cdc_user_rx_callback = callback;
}

/*********************************************************************************
 *  @brief     重定向 putchar 以支持 printf 输出到 USB CDC
 *  @param     c   要输出的字符
 *  @return    输出的字符
 *********************************************************************************/
char putchar(char c)
{
    usb_cdc_send_byte((uint8_t)c);
    return c;
}


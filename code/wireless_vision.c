/*********************************************************************************
 * 文件名称：wireless_vision.c
 * 功能描述：无线串口视觉图像传输模块实现
 *
 * 协议说明（兼容 VOFA+）：
 *   每帧图像前发送文本头: "\nimage:<id>,<size>,<width>,<height>,<bpp>\n"
 *   紧接着发送原始像素字节流
 *
 * 传输方式：DMA 发送（ky_wireless_com_send）。
 *   uart_dma_send 内部 64 字节分块，每块 DMA 完成后轮询标志位（中断已关闭，无竞争）。
 *   DMA 字节间无间隔，1M 无线模块不会误判帧边界。
 *********************************************************************************/
#include "wireless_vision.h"

void wireless_vision_init(void)
{
    ky_wireless_com_init(WIRELESS_VISION_BAUD);

    printf("WIRELESS INIT OK (UART4, 115200)\r\n");

    // 启动后发一次测试字符串，验证 UART4+无线模块正常
    gpio_write_pin(WIRELESS_COM_RTS_PIN, GPIO_LOW);
    uart_send_string(WIRELESS_COM_UART, "WIRELESS OK\r\n");
    gpio_write_pin(WIRELESS_COM_RTS_PIN, GPIO_HIGH);
}

void wireless_vision_send_image(uint8_t *img, uint16_t width, uint16_t height, uint8_t image_id)
{
    uint8_t header[60];
    uint16_t size;
    uint16_t header_len;

    size = width * height;
    header_len = (uint16_t)sprintf((char *)header, "\nimage:%d,%d,%d,%d,%d\n",
                                    image_id, size, width, height, 24);

    // 一次 RTS 拉低，连续发送头+图像，避免 RTS 切换导致模块断流
    gpio_write_pin(WIRELESS_COM_RTS_PIN, GPIO_LOW);
    uart_dma_send(WIRELESS_COM_UART, header, header_len);
    uart_dma_send(WIRELESS_COM_UART, img, size);
    gpio_write_pin(WIRELESS_COM_RTS_PIN, GPIO_HIGH);
}

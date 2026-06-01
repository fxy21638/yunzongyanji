/*********************************************************************************
 * 文件名称：wireless_vision.h
 * 功能描述：无线串口视觉图像传输模块
 * 使用说明：
 *   1. 在 System_Init() 末尾调用 wireless_vision_init()
 *   2. 在需要发送图像处调用 wireless_vision_send_image(img, w, h, id)
 *   3. 图像格式兼容 VOFA+ 协议的 \nimage:...\n + raw bytes
 *
 * 波特率配置：
 *   - WIRELESS_VISION_BAUD 默认 1000000 (1Mbps)
 *   - 需确认无线模块和接收端支持所选波特率
 *   - STC32G 硬件上限约 3Mbps
 *
 * 依赖：
 *   - ky_wireless_com.h (UART4 + RTS, 已包含在 ky_headfile.h 中)
 *   - 占用引脚: TX=P5.3, RX=P5.2, RTS=PB0
 *********************************************************************************/
#ifndef __WIRELESS_VISION_H__
#define __WIRELESS_VISION_H__

#include "ky_headfile.h"

// 无线串口波特率（需模块支持）
#define WIRELESS_VISION_BAUD 115200

// 图像下采样: 1=原始 188x120, 2=94x60, 4=47x30
#define WIRELESS_VISION_DOWNSCALE 1

// 无线图像发送初始化（配置 UART4 + RTS）
void wireless_vision_init(void);

// 通过无线模块发送一幅灰度图像
// img: 图像数据缓冲区(原始分辨率), width/height: 图像宽高, image_id: VOFA 图像 ID
// 若启用下采样，内部自动降采样后发送
void wireless_vision_send_image(uint8_t *img, uint16_t width, uint16_t height, uint8_t image_id);

#endif

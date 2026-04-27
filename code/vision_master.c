#include "ky_headfile.h"
#include "vision_master.h"

extern image_t image_data[MT9V034_HEIGHT * MT9V034_WIDTH];

// 复制原图像
void image_copy(image_t *img, const uint8_t *src)
{
    memcpy(img, src, MT9V034_IMAGE_SIZE);
}

// VOFA+ 发送灰度图像到上位机
// format=24: Format_Grayscale8 (8位灰度，每像素1字节)
// 协议格式: \nimage:id,size,w,h,format\n + 原始像素数据
void vofa_sendGrayscaleImage(uint8_t *img, uint16_t width, uint16_t height)
{
    uint8_t header[60];
    uint16_t size = width * height;
    uint16_t offset = 0;

    sprintf((char *)header, "\nimage:%d,%d,%d,%d,%d\n",
             1, size, width, height, 24);

    usb_cdc_send_buffer(header, strlen((char *)header)); 
    usb_cdc_send_buffer(img, size); 

}

//
void vofa_image_task(void)
{
	// 等待帧数据就绪
	if (mt9v034_frame_ready) {
		// 复制图像到缓冲区
		image_copy(image_data, (const uint8_t *)mt9v034_image);

		// 发送灰度图像到VOFA+上位机
		vofa_sendGrayscaleImage((uint8_t *)image_data, MT9V034_WIDTH, MT9V034_HEIGHT);

		// 翻转LED状态
		//gpio_toggle_pin(LED);
		
		mt9v034_frame_ready = 0;
	}
}

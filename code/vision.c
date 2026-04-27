/*******************************************************************************
 * 接线说明:
 * -----------------------------------------------------------------------------
 * 模块         | 引脚         | 连接说明
 * -------------|--------------|----------------------------------------------
 * MT9V034 SDA  | MT9V034_SDA  | 接P1.4 (SCCB SDA)
 * MT9V034 SCL  | MT9V034_SCL  | 接P1.5 (SCCB SCL)
 * 数据口D0-D7  | P20-P27      | 8位并行数据
 * FIFO WRST    | P85          | FIFO写复位
 * FIFO RRST    | P34          | FIFO读复位
 * FIFO OE     | P35          | FIFO输出使能
 * FIFO WEN    | P36          | FIFO写使能
 * VSYNC       | P33          | 场同步信号
 * FIFO RCLK   | P44          | FIFO读时钟
 * FIFO RE     | PA6          | FIFO读使能
 * -----------------------------------------------------------------------------
 *
 * 实验现象:
 * -----------------------------------------------------------------------------
 * 1. MT9V034摄像头初始化成功
 * 2. 自动采集图像数据到FIFO
 * 3. 可通过IPS屏幕显示图像（需连接IPS模块）
 * 4. LED指示灯闪烁表示图像采集正常
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#include "vision.h"
#include "vision_track.h"

image_t image_data[MT9V034_HEIGHT * MT9V034_WIDTH];

vision_track_result_t g_track;

void vision_Init(void)
{
	mt9v034_init();
}

void vision_task(void)
{
	if (mt9v034_frame_ready)
	{
		// 屏幕显示
		ips_show_gray_image(10, 10, (const uint8_t *)mt9v034_image, 188, 120, 188, 120, 0);

		// 视觉循迹：二值化 + 中线/特征
		vision_track_process((const uint8_t *)mt9v034_image, (uint8_t *)image_data, &g_track);

		// 在原图上叠加同步的边界/中线（与二值化提取结果一致）
		vision_track_overlay_lines(10, 10, &g_track);

		// 彩色显示：赛道外蓝色、赛道白色、中线黑色
		vision_track_show_color(10, 140, &g_track);
		
		
		// 标志位归0
		mt9v034_frame_ready = 0;
	}
}

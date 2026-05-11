#include "vision.h"
#include "vision_track.h"
#include "vision_isp.h"

image_t image_data[MT9V034_HEIGHT * MT9V034_WIDTH];

vision_track_result_t g_track;
uint8_t g_track_valid = 0;

void vision_Init(void)
{
    mt9v034_init();
}

void vision_poll_track(void)
{
    if (mt9v034_frame_ready)
    {
        vision_track_process((const uint8_t *)mt9v034_image, (uint8_t *)image_data, &g_track);
        g_track_valid = 1;
        mt9v034_frame_ready = 0;
    }
}

void vision_task(void)
{
    if (mt9v034_frame_ready)
    {
        ips_show_gray_image(10, 10, (const uint8_t *)mt9v034_image, 188, 120, 188, 120, 0);
        vision_track_process((const uint8_t *)mt9v034_image, (uint8_t *)image_data, &g_track);
        g_track_valid = 1;
        vision_isp_overlay_lines(10, 10, &g_track);
        vision_isp_show_color(10, 140, &g_track);
        mt9v034_frame_ready = 0;
    }
}

void vision_isp_task(void)
{
    if (mt9v034_frame_ready)
    {
        ips_show_gray_image(10, 10, (const uint8_t *)mt9v034_image, 188, 120, 188, 120, 0);
        vision_track_process((const uint8_t *)mt9v034_image, (uint8_t *)image_data, &g_track);
        g_track_valid = 1;
        vision_isp_overlay_lines(10, 10, &g_track);
        vision_isp_show_color(10, 140, &g_track);
        mt9v034_frame_ready = 0;
    }
}

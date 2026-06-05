// Vision module integration: camera init, frame polling, perspective setup

#ifndef __INTELLISENSE__
#include "ky_headfile.h"
#endif

#include "vision.h"
#include "vision_track.h"
#include "vision_isp.h"

#if VISION_USE_WALLFOLLOW
#include "perspective.h"
#endif

image_t image_data[MT9V034_HEIGHT * MT9V034_WIDTH];

vision_track_result_t g_track;
uint8_t g_track_valid = 0;
uint8_t g_vofa_pending = 0;  // 新帧就绪待 VOFA 发送, 与 g_track_valid 解耦

void vision_Init(void)
{
    mt9v034_init();

#if VISION_USE_WALLFOLLOW
    // Initialize perspective transform with 4 point correspondences
    // Source: image coordinates of a trapezoid on the road
    // Dest: bird's-eye view rectangle centered on track
    {
        uint8_t src[4][2];
        uint8_t dst[4][2];

        // Bottom-left of track trapezoid
        src[0][0] = 15;  src[0][1] = 112;
        // Bottom-right
        src[1][0] = 173; src[1][1] = 112;
        // Top-right
        src[2][0] = 130; src[2][1] = 25;
        // Top-left
        src[3][0] = 58;  src[3][1] = 25;

        // Destination: rectangle in bird's-eye view
        // Width = 80px, centered at x=94
        dst[0][0] = 54;  dst[0][1] = 120;
        dst[1][0] = 134; dst[1][1] = 120;
        dst[2][0] = 134; dst[2][1] = 0;
        dst[3][0] = 54;  dst[3][1] = 0;

        perspective_init(src, dst);

        if (perspective_is_ready())
        {
            printf("PERSPECTIVE OK\r\n");
        }
        else
        {
            printf("PERSPECTIVE FAIL\r\n");
        }
    }
#endif
}

void vision_poll_track(void)
{
    if (mt9v034_frame_ready)
    {
        vision_track_process((uint8_t *)mt9v034_image, (uint8_t *)image_data, &g_track);
        g_track_valid = 1;
        g_vofa_pending = 1;
        mt9v034_frame_ready = 0;
    }
}

void vision_task(void)
{
    if (mt9v034_frame_ready)
    {
        ips_show_gray_image(10, 10, (const uint8_t *)mt9v034_image, 188, 120, 188, 120, 0);
        vision_track_process((uint8_t *)mt9v034_image, (uint8_t *)image_data, &g_track);
        g_track_valid = 1;
        vision_isp_overlay_lines(10, 10, &g_track);
#if VISION_USE_WALLFOLLOW
        vision_isp_overlay_wallfollow(10, 10, &g_track);
#endif
        vision_isp_show_color(10, 140, &g_track);
        mt9v034_frame_ready = 0;
    }
}

void vision_isp_task(void)
{
    if (mt9v034_frame_ready)
    {
        ips_show_gray_image(10, 10, (const uint8_t *)mt9v034_image, 188, 120, 188, 120, 0);
        vision_track_process((uint8_t *)mt9v034_image, (uint8_t *)image_data, &g_track);
        g_track_valid = 1;
        vision_isp_overlay_lines(10, 10, &g_track);
#if VISION_USE_WALLFOLLOW
        vision_isp_overlay_wallfollow(10, 10, &g_track);
#endif
        vision_isp_show_color(10, 140, &g_track);
        mt9v034_frame_ready = 0;
    }
}

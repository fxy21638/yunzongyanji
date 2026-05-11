// IPS 显示屏绘制函数：赛道区域着色、中线叠加、调试绘制

#ifndef __INTELLISENSE__
#include "ky_headfile.h"
#endif

#include "vision_isp.h"

#ifdef __INTELLISENSE__
typedef uint16_t Color_t;
void ips_fill_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color_t color, uint8_t enable);
void ips_draw_point(uint16_t x, uint16_t y, Color_t color);
#endif

#ifndef MT9V034_WIDTH
#error "MT9V034_WIDTH not defined"
#endif

#ifndef MT9V034_HEIGHT
#error "MT9V034_HEIGHT not defined"
#endif

#define VISION_W ((uint16_t)MT9V034_WIDTH)
#define VISION_H ((uint16_t)MT9V034_HEIGHT)

#define VISION_RGB565_BLACK ((Color_t)0x0000)
#define VISION_RGB565_WHITE ((Color_t)0xFFFF)
#define VISION_RGB565_BLUE  ((Color_t)0x001F)
#define VISION_RGB565_RED   ((Color_t)0xF800)

void vision_isp_show_color(uint16_t x, uint16_t y, const vision_track_result_t *res)
{
    uint16_t row;

    for (row = 0; row < VISION_H; row++)
    {
        int16_t l = res->left[row];
        int16_t r = res->right[row];
        int16_t m = res->mid[row];

        if (l < 0 || r < 0 || l > r)
        {
            ips_fill_rectangle(x, (uint16_t)(y + row), (uint16_t)(x + VISION_W - 1), (uint16_t)(y + row), VISION_RGB565_BLUE, 0);
            continue;
        }

        if (l > 0)
        {
            ips_fill_rectangle(x, (uint16_t)(y + row), (uint16_t)(x + (uint16_t)l - 1), (uint16_t)(y + row), VISION_RGB565_BLUE, 0);
        }

        ips_fill_rectangle((uint16_t)(x + (uint16_t)l), (uint16_t)(y + row), (uint16_t)(x + (uint16_t)r), (uint16_t)(y + row), VISION_RGB565_WHITE, 0);

        if (r < (int16_t)(VISION_W - 1))
        {
            ips_fill_rectangle((uint16_t)(x + (uint16_t)r + 1), (uint16_t)(y + row), (uint16_t)(x + VISION_W - 1), (uint16_t)(y + row), VISION_RGB565_BLUE, 0);
        }

        if (m >= 0 && m < (int16_t)VISION_W)
        {
            ips_draw_point((uint16_t)(x + (uint16_t)m), (uint16_t)(y + row), VISION_RGB565_BLACK);
        }
    }
}

void vision_isp_overlay_lines(uint16_t x, uint16_t y, const vision_track_result_t *res)
{
    uint16_t row;

    for (row = 0; row < VISION_H; row++)
    {
        int16_t m = res->mid[row];

        if (m >= 0 && m < (int16_t)VISION_W)
        {
            ips_draw_point((uint16_t)(x + (uint16_t)m), (uint16_t)(y + row), VISION_RGB565_RED);
        }
    }
}

void vision_isp_debug_draw(uint8_t *bin, const vision_track_result_t *res)
{
    uint16_t y;

    for (y = 0; y < VISION_H; y++)
    {
        int16_t l = res->left[y];
        int16_t r = res->right[y];
        int16_t m = res->mid[y];

        if (l >= 0)
        {
            bin[y * VISION_W + (uint16_t)l] = 180;
            bin[y * VISION_W + (uint16_t)r] = 180;
            bin[y * VISION_W + (uint16_t)m] = 100;
        }
    }
}

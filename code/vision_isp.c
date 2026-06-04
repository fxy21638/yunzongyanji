// IPS 显示屏绘制函数：赛道区域着色、中线叠加、调试绘制

#ifndef __INTELLISENSE__
#include "ky_headfile.h"
#endif

#include "vision_isp.h"

#if VISION_USE_WALLFOLLOW
#include "perspective.h"
#endif

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
#define VISION_RGB565_RED    ((Color_t)0xF800)
#define VISION_RGB565_GREEN  ((Color_t)0x07E0)
#define VISION_RGB565_CYAN   ((Color_t)0x07FF)

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

// Draw a 3-pixel horizontal bar to make lines visible on sparse displays
static void draw_bar3(uint16_t cx, uint16_t cy, Color_t color)
{
    uint16_t x0;
    x0 = (cx > 0) ? (uint16_t)(cx - 1) : 0;
    if (x0 < VISION_W) ips_draw_point(x0, cy, color);
    if (cx < VISION_W) ips_draw_point(cx, cy, color);
    if (cx + 1 < VISION_W) ips_draw_point((uint16_t)(cx + 1), cy, color);
}

void vision_isp_overlay_lines(uint16_t x, uint16_t y, const vision_track_result_t *res)
{
    uint16_t row;
    int16_t prev_l, prev_r, prev_m;
    uint8_t has_l, has_r, has_m;

    has_l = 0; has_r = 0; has_m = 0;
    prev_l = 0; prev_r = 0; prev_m = 0;

    for (row = 0; row < VISION_H; row++)
    {
        int16_t l, r, m;
        l = res->left[row];
        r = res->right[row];
        m = res->mid[row];

        // Left boundary: green 3-pixel bar
        if (l >= 0 && l < (int16_t)VISION_W)
        {
            draw_bar3((uint16_t)(x + (uint16_t)l), (uint16_t)(y + row), VISION_RGB565_GREEN);
            // Fill gap from previous valid row
            if (has_l)
            {
                int16_t dl;
                dl = l - prev_l;
                if (dl < 0) dl = -dl;
                if (dl > 1 && dl < 50)
                {
                    uint8_t k;
                    for (k = 1; k < (uint8_t)dl; k++)
                    {
                        uint16_t mx;
                        mx = (uint16_t)(x + (uint16_t)prev_l + (uint16_t)((dl > 0 ? (l - prev_l) : (prev_l - l)) * (int16_t)k / (int16_t)dl));
                        ips_draw_point(mx, (uint16_t)(y + row), VISION_RGB565_GREEN);
                    }
                }
            }
            prev_l = l;
            has_l = 1;
        }
        else { has_l = 0; }

        // Right boundary: cyan 3-pixel bar
        if (r >= 0 && r < (int16_t)VISION_W)
        {
            draw_bar3((uint16_t)(x + (uint16_t)r), (uint16_t)(y + row), VISION_RGB565_CYAN);
            if (has_r)
            {
                int16_t dr;
                dr = r - prev_r;
                if (dr < 0) dr = -dr;
                if (dr > 1 && dr < 50)
                {
                    uint8_t k;
                    for (k = 1; k < (uint8_t)dr; k++)
                    {
                        uint16_t mx;
                        mx = (uint16_t)(x + (uint16_t)prev_r + (uint16_t)((r - prev_r) * (int16_t)k / dr));
                        ips_draw_point(mx, (uint16_t)(y + row), VISION_RGB565_CYAN);
                    }
                }
            }
            prev_r = r;
            has_r = 1;
        }
        else { has_r = 0; }

        // Midline: red 3-pixel bar (replaces old dotted line)
        if (m >= 0 && m < (int16_t)VISION_W)
        {
            draw_bar3((uint16_t)(x + (uint16_t)m), (uint16_t)(y + row), VISION_RGB565_RED);
            if (has_m)
            {
                int16_t dm;
                dm = m - prev_m;
                if (dm < 0) dm = -dm;
                if (dm > 1 && dm < 50)
                {
                    uint8_t k;
                    for (k = 1; k < (uint8_t)dm; k++)
                    {
                        uint16_t mx;
                        mx = (uint16_t)(x + (uint16_t)prev_m + (uint16_t)((m - prev_m) * (int16_t)k / dm));
                        ips_draw_point(mx, (uint16_t)(y + row), VISION_RGB565_RED);
                    }
                }
            }
            prev_m = m;
            has_m = 1;
        }
        else { has_m = 0; }
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

#if VISION_USE_WALLFOLLOW

#define VISION_RGB565_YELLOW  ((Color_t)0xFFE0)
#define VISION_RGB565_MAGENTA ((Color_t)0xF81F)

static void draw_cross(uint16_t cx, uint16_t cy, uint16_t ox, uint16_t oy, Color_t color)
{
    int8_t d;
    for (d = -3; d <= 3; d++)
    {
        uint16_t px, py;
        px = (uint16_t)(ox + (uint16_t)cx + (uint16_t)(int16_t)d);
        py = (uint16_t)(oy + (uint16_t)cy);
        if (px < ox + VISION_W && py < oy + VISION_H)
            ips_draw_point(px, py, color);
        px = (uint16_t)(ox + (uint16_t)cx);
        py = (uint16_t)(oy + (uint16_t)cy + (uint16_t)(int16_t)d);
        if (px < ox + VISION_W && py < oy + VISION_H)
            ips_draw_point(px, py, color);
    }
}

void vision_isp_overlay_wallfollow(uint16_t x, uint16_t y, const vision_track_result_t *res)
{
    uint8_t i;

    // Draw BEV midline points directly (magenta) — they are in [0,W]x[0,H] range
    for (i = 0; i < res->mid_step; i++)
    {
        uint16_t px, py;
        px = (uint16_t)(x + (uint16_t)res->mid_pts[i][0]);
        py = (uint16_t)(y + (uint16_t)res->mid_pts[i][1]);
        if (px < x + VISION_W && py < y + VISION_H)
            ips_draw_point(px, py, VISION_RGB565_MAGENTA);
    }

    // Draw corner markers (yellow crosses)
    if (res->corner_l.is_valid)
    {
        uint16_t cx, cy;
        cx = (uint16_t)res->corner_l.img_pt[0];
        cy = (uint16_t)res->corner_l.img_pt[1];
        draw_cross(cx, cy, x, y, VISION_RGB565_YELLOW);
    }

    if (res->corner_r.is_valid)
    {
        uint16_t cx, cy;
        cx = (uint16_t)res->corner_r.img_pt[0];
        cy = (uint16_t)res->corner_r.img_pt[1];
        draw_cross(cx, cy, x, y, VISION_RGB565_YELLOW);
    }
}

#endif // VISION_USE_WALLFOLLOW

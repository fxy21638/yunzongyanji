// 视觉循迹核心算法：阈值 → 二值化 → 形态学 → 提边界 → 特征分类 → 十字补线 → 中心误差

#ifndef __INTELLISENSE__
#include "ky_headfile.h"
#endif

#include "vision_track.h"

#ifndef MT9V034_WIDTH
#error "MT9V034_WIDTH not defined"
#endif
#ifndef MT9V034_HEIGHT
#error "MT9V034_HEIGHT not defined"
#endif

/* ============================================================
 * 内部宏
 * ============================================================ */
#define VISION_W                ((uint16_t)MT9V034_WIDTH)
#define VISION_H                ((uint16_t)MT9V034_HEIGHT)
#define VISION_SIZE             ((uint16_t)(MT9V034_WIDTH * MT9V034_HEIGHT))

#define VISION_SAMPLE_STEP      1u
#define VISION_MIN_RUN_LEN      3u

#define VISION_CROSS_WIDE_TH_NUM (VISION_W * 8 / 10)
#define VISION_CROSS_END_TH_NUM  (VISION_W * 7 / 10)
#define VISION_EDGE_NEAR_TH      2

#define VISION_CONTOUR_MAX_POINTS (4u * (MT9V034_WIDTH + MT9V034_HEIGHT))

/* ============================================================
 * 静态状态
 * ============================================================ */
static uint16_t g_contour_points[VISION_CONTOUR_MAX_POINTS][2];
static int16_t  g_last_center_x = -1;
static uint8_t  g_center_hold_cnt = 0;

// 八邻域偏移表（Moore 邻域），顺时针
static const signed char nb8[8][2] = {
    {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}
};

/* ============================================================
 * 工具函数
 * ============================================================ */

static uint8_t clamp_u8(long v)
{
    if (v < 0)   return 0;
    if (v > 255) return 255;
    return (uint8_t)v;
}

static int16_t clamp_i16(int16_t v, int16_t lo, int16_t hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static uint16_t abs_i16_to_u16(int16_t v)
{
    return (uint16_t)((v < 0) ? -v : v);
}

static uint8_t in_bounds(int16_t x, int16_t y)
{
    return (x >= 0 && y >= 0 && x < (int16_t)VISION_W && y < (int16_t)VISION_H);
}

static uint8_t bin_at(const uint8_t *bin, int16_t x, int16_t y)
{
    if (!in_bounds(x, y)) return 255;
    return bin[(uint16_t)y * VISION_W + (uint16_t)x];
}

/* ============================================================
 * 阈值计算
 * ============================================================ */

static uint8_t compute_threshold_isodata(const uint8_t *gray)
{
    unsigned long sum = 0, cnt = 0;
    uint16_t x, y;

    for (y = 0; y < VISION_H; y += VISION_SAMPLE_STEP)
    {
        const uint8_t *row = &gray[y * VISION_W];
        for (x = 0; x < VISION_W; x += VISION_SAMPLE_STEP)
        {
            sum += row[x];
            cnt++;
        }
    }

    if (cnt == 0) return 128;

    {
        uint8_t thr = (uint8_t)(sum / cnt);
        uint8_t iter;
        for (iter = 0; iter < 4; iter++)
        {
            unsigned long sum_low = 0, cnt_low = 0;
            unsigned long sum_high = 0, cnt_high = 0;

            for (y = 0; y < VISION_H; y += VISION_SAMPLE_STEP)
            {
                const uint8_t *row = &gray[y * VISION_W];
                for (x = 0; x < VISION_W; x += VISION_SAMPLE_STEP)
                {
                    uint8_t v = row[x];
                    if (v < thr) { sum_low += v;  cnt_low++; }
                    else         { sum_high += v; cnt_high++; }
                }
            }

            if (cnt_low == 0 || cnt_high == 0) break;
            thr = (uint8_t)(((sum_low / cnt_low) + (sum_high / cnt_high)) / 2);
        }
        return thr;
    }
}

// Otsu 大津法：直方图 + 最大类间方差。
// 为兼容 C251（无 long long），对 diff^2 做右移缩放避免 32 位溢出。
static uint8_t compute_threshold_otsu(const uint8_t *gray)
{
    static uint16_t hist[256];
    uint16_t i, x, y;
    unsigned long total = 0, sum = 0;

    for (i = 0; i < 256; i++) hist[i] = 0;
    for (y = 0; y < VISION_H; y += VISION_SAMPLE_STEP)
    {
        const uint8_t *row = &gray[y * VISION_W];
        for (x = 0; x < VISION_W; x += VISION_SAMPLE_STEP)
            hist[row[x]]++;
    }

    for (i = 0; i < 256; i++)
    {
        total += (unsigned long)hist[i];
        sum   += (unsigned long)i * (unsigned long)hist[i];
    }
    if (total == 0) return 128;

    {
        unsigned long wB = 0, sumB = 0;
        unsigned long best_score = 0;
        uint8_t best_thr = 128;
        unsigned long wF, diff2, score;
        uint16_t mB, mF;
        long diff;

        for (i = 0; i < 256; i++)
        {
            wB   += (unsigned long)hist[i];
            sumB += (unsigned long)i * (unsigned long)hist[i];
            if (wB == 0) continue;

            wF = total - wB;
            if (wF == 0) break;

            mB = (uint16_t)(sumB / wB);
            mF = (uint16_t)((sum - sumB) / wF);
            diff = (long)mB - (long)mF;
            diff2 = (unsigned long)(diff * diff);

            score = (wB * wF) * (diff2 >> 10);
            if (score >= best_score)
            {
                best_score = score;
                best_thr = (uint8_t)i;
            }
        }
        return best_thr;
    }
}

#if (VISION_TRACK_POLARITY == VISION_TRACK_POLARITY_AUTO)
// 自动极性：统计底部 1/3 区域暗像素占比。
// ratio < 45% → 赛道暗；ratio > 65% → 赛道亮（反相）
static uint8_t decide_track_is_dark(const uint8_t *gray, uint8_t thr)
{
    unsigned long dark_cnt = 0, total = 0;
    uint16_t y0 = (uint16_t)(VISION_H * 2 / 3);
    uint16_t x, y;

    for (y = y0; y < VISION_H; y += VISION_SAMPLE_STEP)
    {
        const uint8_t *row = &gray[y * VISION_W];
        for (x = 0; x < VISION_W; x += VISION_SAMPLE_STEP)
        {
            if (row[x] < thr) dark_cnt++;
            total++;
        }
    }

    if (total == 0) return 1;

    unsigned long ratio_x100 = (dark_cnt * 100u) / total;
    if (ratio_x100 < 45u) return 1;
    if (ratio_x100 > 65u) return 0;
    return 1;
}
#endif

/* ============================================================
 * 二值化
 * ============================================================ */

static void binarize_to_track0(const uint8_t *gray, uint8_t *bin, uint8_t thr, uint8_t track_is_dark)
{
    uint16_t i;
    if (track_is_dark)
    {
        for (i = 0; i < VISION_SIZE; i++)
            bin[i] = (gray[i] < thr) ? 0 : 255;
    }
    else
    {
        for (i = 0; i < VISION_SIZE; i++)
            bin[i] = (gray[i] > thr) ? 0 : 255;
    }
}

#if VISION_USE_SPLIT_THRESHOLD
static uint8_t clamp_add_u8(uint8_t base, int8_t delta)
{
    int16_t v = (int16_t)base + (int16_t)delta;
    if (v < 0)   return 0;
    if (v > 255) return 255;
    return (uint8_t)v;
}

// 分区阈值：远端（y < VISION_FAR_REGION_HEIGHT）使用 thr + offset
static void binarize_to_track0_split(const uint8_t *gray, uint8_t *bin, uint8_t thr, uint8_t track_is_dark)
{
    uint16_t far_h = (uint16_t)VISION_FAR_REGION_HEIGHT;
    int8_t   off   = (int8_t)VISION_FAR_THRESHOLD_OFFSET;
    uint16_t x, y;

    if (far_h > VISION_H) far_h = VISION_H;

    for (y = 0; y < VISION_H; y++)
    {
        uint8_t thr_y = (y < far_h) ? clamp_add_u8(thr, off) : thr;
        const uint8_t *row = &gray[y * VISION_W];
        uint8_t       *out = &bin[y * VISION_W];

        if (track_is_dark)
        {
            for (x = 0; x < VISION_W; x++)
                out[x] = (row[x] < thr_y) ? 0 : 255;
        }
        else
        {
            for (x = 0; x < VISION_W; x++)
                out[x] = (row[x] > thr_y) ? 0 : 255;
        }
    }
}
#endif

/* ============================================================
 * 二值形态学
 * ============================================================ */

#if VISION_BIN_DESPECKLE
// 4-邻域去椒盐：孤立点（≥3 邻域不同）→ 背景
static void bin_despeckle_4n(uint8_t *bin)
{
    uint16_t y, x;
    for (y = 1; y < (uint16_t)(VISION_H - 1); y++)
    {
        for (x = 1; x < (uint16_t)(VISION_W - 1); x++)
        {
            uint16_t off = y * VISION_W + x;
            uint8_t v = bin[off];
            uint8_t diff = 0;

            if (bin[off - VISION_W] != v) diff++;
            if (bin[off + VISION_W] != v) diff++;
            if (bin[off - 1] != v) diff++;
            if (bin[off + 1] != v) diff++;

            if (diff >= 3) bin[off] = 255;
        }
    }
}
#endif

// 行内闭运算：填补赛道内的窄缝（背景被赛道包围）
static void bin_close_small_gaps_row(uint8_t *bin)
{
    uint16_t gap_max = (uint16_t)VISION_BIN_CLOSE_GAP_MAX;
    uint16_t y;

    if (gap_max == 0) return;

    for (y = 0; y < VISION_H; y++)
    {
        uint16_t row_off = (uint16_t)(y * VISION_W);
        uint16_t x = 1;

        while (x + 1 < VISION_W)
        {
            if (bin[row_off + x] != 255) { x++; continue; }

            if (bin[row_off + (uint16_t)(x - 1)] == 0)
            {
                uint16_t s = x;
                while (x < VISION_W && bin[row_off + x] == 255) x++;

                if (x < VISION_W && bin[row_off + x] == 0)
                {
                    uint16_t e = (uint16_t)(x - 1);
                    if ((uint16_t)(e - s + 1) <= gap_max)
                    {
                        uint16_t k;
                        for (k = s; k <= e; k++) bin[row_off + k] = 0;
                    }
                }
            }
            else { x++; }
        }
    }
}

// 行内开运算：去除赛道边的小毛刺
static void bin_open_small_spurs_row(uint8_t *bin)
{
    uint16_t spur_max = (uint16_t)VISION_BIN_OPEN_SPUR_MAX;
    uint16_t y;

    if (spur_max == 0) return;

    for (y = 0; y < VISION_H; y++)
    {
        uint16_t row_off = (uint16_t)(y * VISION_W);
        uint16_t x = 1;

        while (x + 1 < VISION_W)
        {
            if (bin[row_off + x] != 0) { x++; continue; }

            if (bin[row_off + (uint16_t)(x - 1)] == 255)
            {
                uint16_t s = x;
                while (x < VISION_W && bin[row_off + x] == 0) x++;

                if (x < VISION_W && bin[row_off + x] == 255)
                {
                    uint16_t e = (uint16_t)(x - 1);
                    if ((uint16_t)(e - s + 1) <= spur_max)
                    {
                        uint16_t k;
                        for (k = s; k <= e; k++) bin[row_off + k] = 255;
                    }
                }
            }
            else { x++; }
        }
    }
}

/* ============================================================
 * 边界提取 — 工具
 * ============================================================ */

// 找一行中最长的连续 0（赛道像素）段
static void find_widest_run_0(const uint8_t *row, uint16_t w, int16_t *out_l, int16_t *out_r)
{
    uint16_t x = 0;
    uint16_t best_len = 0;
    int16_t  best_l = -1, best_r = -1;

    while (x < w)
    {
        if (row[x] == 0)
        {
            uint16_t l, r, len;
            l = x;
            while (x < w && row[x] == 0) x++;
            r = (uint16_t)(x - 1);
            len = (uint16_t)(r - l + 1);
            if (len > best_len) { best_len = len; best_l = (int16_t)l; best_r = (int16_t)r; }
        }
        else { x++; }
    }

    if (best_len < VISION_MIN_RUN_LEN)
        { *out_l = -1; *out_r = -1; }
    else
        { *out_l = best_l; *out_r = best_r; }
}

static uint8_t is_track_pixel(const uint8_t *bin, int16_t x, int16_t y)
{
    return (bin_at(bin, x, y) == 0);
}

// 赛道像素(0) 且八邻域存在背景(255)或越界 → 边界像素
static uint8_t is_boundary_track_pixel(const uint8_t *bin, int16_t x, int16_t y)
{
    uint8_t k;

    if (!is_track_pixel(bin, x, y)) return 0;
    for (k = 0; k < 8; k++)
    {
        int16_t nx = (int16_t)(x + nb8[k][0]);
        int16_t ny = (int16_t)(y + nb8[k][1]);
        if (!in_bounds(nx, ny))    return 1;
        if (bin_at(bin, nx, ny) != 0) return 1;
    }
    return 0;
}

// 在图像底部附近找边界像素作为轮廓跟踪种子点
static uint8_t find_seed_boundary(const uint8_t *bin, int16_t *out_x, int16_t *out_y)
{
    int16_t y  = (int16_t)(VISION_H - 2);
    int16_t cx = (int16_t)(VISION_W / 2);
    int16_t dx;

    if (y < 0) y = 0;

    for (dx = 0; dx < (int16_t)VISION_W; dx++)
    {
        int16_t x1 = (int16_t)(cx - dx);
        int16_t x2 = (int16_t)(cx + dx);

        if (in_bounds(x1, y) && is_boundary_track_pixel(bin, x1, y))
            { *out_x = x1; *out_y = y; return 1; }
        if (in_bounds(x2, y) && is_boundary_track_pixel(bin, x2, y))
            { *out_x = x2; *out_y = y; return 1; }
    }
    return 0;
}

// Moore 邻域轮廓追踪
static uint16_t trace_contour_moore(const uint8_t *bin, int16_t sx, int16_t sy)
{
    int16_t cx = sx, cy = sy;
    int16_t bx = (int16_t)(sx - 1), by = sy;
    int16_t b0x = bx, b0y = by;
    uint16_t count = 0;
    uint16_t guard = (uint16_t)(VISION_CONTOUR_MAX_POINTS - 1);

    if (!in_bounds(cx, cy) || !is_boundary_track_pixel(bin, cx, cy))
        return 0;

    while (guard--)
    {
        uint8_t start_idx, k;
        uint8_t found, i;

        if (count < VISION_CONTOUR_MAX_POINTS)
        {
            g_contour_points[count][0] = (uint16_t)cx;
            g_contour_points[count][1] = (uint16_t)cy;
            count++;
        }

        // 找 backtrack 点在邻域中的索引
        start_idx = 0;
        for (k = 0; k < 8; k++)
        {
            if ((int16_t)(cx + nb8[k][0]) == bx && (int16_t)(cy + nb8[k][1]) == by)
                { start_idx = k; break; }
        }

        // 顺时针找下一个轮廓点
        found = 0;
        for (i = 0; i < 8; i++)
        {
            uint8_t idx = (uint8_t)((start_idx + 1 + i) & 7);
            int16_t nx = (int16_t)(cx + nb8[idx][0]);
            int16_t ny = (int16_t)(cy + nb8[idx][1]);
            if (is_track_pixel(bin, nx, ny))
            {
                uint8_t prev = (uint8_t)((idx + 7) & 7);
                bx = (int16_t)(cx + nb8[prev][0]);
                by = (int16_t)(cy + nb8[prev][1]);
                cx = nx; cy = ny;
                found = 1;
                break;
            }
        }
        if (!found) break;

        if (cx == sx && cy == sy && bx == b0x && by == b0y) break;
    }
    return count;
}

/* ============================================================
 * 边界提取 — 主流程
 * ============================================================ */

// 八邻域轮廓跟踪 → 按行取 min/max 得左右边界
static uint8_t extract_edges_8neighbor(const uint8_t *bin, vision_track_result_t *res)
{
    int16_t sx, sy;
    uint16_t n, y, i;

    if (!find_seed_boundary(bin, &sx, &sy)) return 0;

    n = trace_contour_moore(bin, sx, sy);
    if (n < 40) return 0;

    for (y = 0; y < VISION_H; y++)
        { res->left[y] = -1; res->right[y] = -1; res->mid[y] = -1; }

    for (i = 0; i < n; i++)
    {
        uint16_t yy = g_contour_points[i][1];
        int16_t  x  = (int16_t)g_contour_points[i][0];
        if (yy >= VISION_H) continue;

        if (res->left[yy]  < 0 || x < res->left[yy])  res->left[yy]  = x;
        if (res->right[yy] < 0 || x > res->right[yy]) res->right[yy] = x;
    }

    res->valid_rows = 0;
    for (y = 0; y < VISION_H; y++)
    {
        if (res->left[y] >= 0 && res->right[y] >= 0)
        {
            // 稀疏行跨度太小 → 全行扫描兜底
            if (res->right[y] - res->left[y] + 1 < (int16_t)VISION_MIN_RUN_LEN)
                find_widest_run_0(&bin[y * VISION_W], VISION_W, &res->left[y], &res->right[y]);

            if (res->left[y] >= 0 && res->right[y] >= 0)
            {
                res->mid[y] = (int16_t)((res->left[y] + res->right[y]) / 2);
                res->valid_rows++;
            }
        }
    }
    return (res->valid_rows > (uint8_t)(VISION_H / 3));
}

// 逐行搜索：从底部向上，用 last_mid 保持中线连续性
static void extract_edges(const uint8_t *bin, vision_track_result_t *res)
{
    int16_t last_mid = (int16_t)(VISION_W / 2);
    uint16_t y;

    res->valid_rows = 0;
    for (y = 0; y < VISION_H; y++)
        { res->left[y] = -1; res->right[y] = -1; res->mid[y] = -1; }

    for (y = (uint16_t)(VISION_H - 1);; y--)
    {
        const uint8_t *row = &bin[y * VISION_W];
        int16_t l = -1, r = -1;

        if (last_mid >= 0 && last_mid < (int16_t)VISION_W && row[last_mid] == 0)
        {
            int16_t tl = last_mid, tr = last_mid;
            while (tl > 0 && row[tl] == 0) tl--;
            if (row[tl] != 0) tl++;
            while (tr < (int16_t)(VISION_W - 1) && row[tr] == 0) tr++;
            if (row[tr] != 0) tr--;

            if ((uint16_t)(tr - tl + 1) >= VISION_MIN_RUN_LEN)
                { l = tl; r = tr; }
        }

        if (l < 0)
            find_widest_run_0(row, VISION_W, &l, &r);

        if (l >= 0)
        {
            int16_t m = (int16_t)((l + r) / 2);
            res->left[y]  = l;
            res->right[y] = r;
            res->mid[y]   = m;
            last_mid = m;
            res->valid_rows++;
        }
        if (y == 0) break;
    }
}

// 线性插值填补边界中的小间隙
static void interpolate_edge_gaps(vision_track_result_t *res)
{
    uint16_t max_gap = (uint16_t)VISION_EDGE_INTERP_MAX_GAP_ROWS;
    uint16_t y, y0, y1, g, k;
    int16_t gap_i16;

    if (max_gap == 0) return;

    y = 0;
    while (y < VISION_H)
    {
        if (res->mid[y] >= 0) { y++; continue; }
        if (y == 0)            { y++; continue; }

        y0 = (uint16_t)(y - 1);
        if (res->mid[y0] < 0)  { y++; continue; }

        y1 = y;
        while (y1 < VISION_H && res->mid[y1] < 0) y1++;
        if (y1 >= VISION_H || res->mid[y1] < 0) break;

        g = (uint16_t)(y1 - y0 - 1);
        if (g == 0 || g > max_gap) { y = y1; continue; }

        if (res->left[y0] < 0 || res->left[y1] < 0 ||
            res->right[y0] < 0 || res->right[y1] < 0)
            { y = y1; continue; }

        gap_i16 = (int16_t)(g + 1);
        for (k = 1; k <= g; k++)
        {
            uint16_t yy = (uint16_t)(y0 + k);
            int16_t ki16 = (int16_t)k;
            int16_t l = (int16_t)(res->left[y0]  + ((res->left[y1]  - res->left[y0])  * ki16) / gap_i16);
            int16_t r = (int16_t)(res->right[y0] + ((res->right[y1] - res->right[y0]) * ki16) / gap_i16);
            if (l < 0) l = 0;
            if (r > (int16_t)(VISION_W - 1)) r = (int16_t)(VISION_W - 1);
            if (l > r) { int16_t t = l; l = r; r = t; }
            res->left[yy]  = l;
            res->right[yy] = r;
            res->mid[yy]   = (int16_t)((l + r) / 2);
            res->valid_rows++;
        }
        y = y1;
    }
}

// 抗眩光行稳定：检测宽度/中线突变并回退
static void stabilize_rows_against_glare(vision_track_result_t *res)
{
    int16_t last_l = -1, last_r = -1, last_m = -1;
    uint16_t y;

    for (y = (uint16_t)(VISION_H - 1);; y--)
    {
        int16_t l = res->left[y], r = res->right[y], m = res->mid[y];
        if (!(l >= 0 && r >= l && m >= 0)) { if (y == 0) break; continue; }

        if (last_m >= 0)
        {
            uint16_t w      = (uint16_t)(r - l + 1);
            uint16_t last_w = (uint16_t)(last_r - last_l + 1);
            uint16_t mid_jump = abs_i16_to_u16((int16_t)(m - last_m));
            uint8_t touches_both = (uint8_t)(l <= VISION_EDGE_NEAR_TH &&
                                             r >= (int16_t)(VISION_W - 1 - VISION_EDGE_NEAR_TH));
            uint8_t width_grows_too_fast = 0;

            if (w > (uint16_t)(last_w + (uint16_t)VISION_ROW_MAX_WIDTH_GROW))
            {
                if ((unsigned long)w * (unsigned long)VISION_ROW_MAX_WIDTH_RATIO_DEN >
                    (unsigned long)last_w * (unsigned long)VISION_ROW_MAX_WIDTH_RATIO_NUM)
                    width_grows_too_fast = 1;
            }

            if (!touches_both && mid_jump > (uint16_t)VISION_ROW_MAX_CENTER_JUMP && width_grows_too_fast)
            {
                res->left[y]  = last_l;
                res->right[y] = last_r;
                res->mid[y]   = last_m;
            }
            else { last_l = l; last_r = r; last_m = m; }
        }
        else { last_l = l; last_r = r; last_m = m; }

        if (y == 0) break;
    }
}

/* ============================================================
 * 特征分类
 * ============================================================ */

static void classify_feature(const vision_track_result_t *res, vision_track_result_t *out)
{
    uint16_t y;
    uint8_t cross_cnt = 0, ring_left_cnt = 0, ring_right_cnt = 0;
    uint16_t y0 = (uint16_t)(VISION_H / 2);
    static uint8_t cross_hold = 0;

    for (y = y0; y < VISION_H; y++)
    {
        int16_t l, r;
        uint16_t w;

        l = res->left[y];
        r = res->right[y];
        if (l < 0) continue;

        w = (uint16_t)(r - l + 1);

        if (w > (uint16_t)VISION_CROSS_WIDE_TH_NUM &&
            l <= VISION_EDGE_NEAR_TH &&
            r >= (int16_t)(VISION_W - 1 - VISION_EDGE_NEAR_TH))
            cross_cnt++;

        if (w > (uint16_t)(VISION_W * 6 / 10))
        {
            if (l <= 1) ring_left_cnt++;
            if (r >= (int16_t)(VISION_W - 2)) ring_right_cnt++;
        }
    }

    if (out->valid_rows < (uint8_t)(VISION_H / 4))
        { out->feature = VISION_FEATURE_LOST; cross_hold = 0; return; }

    if (cross_cnt >= 6)
    {
        cross_hold = 4;
        out->feature = VISION_FEATURE_CROSS;
        return;
    }

    if (cross_hold > 0)
    {
        cross_hold--;
        out->feature = VISION_FEATURE_CROSS;
        return;
    }

    if (ring_left_cnt >= 6 && ring_right_cnt < 3)
        { out->feature = VISION_FEATURE_RING_LEFT; return; }
    if (ring_right_cnt >= 6 && ring_left_cnt < 3)
        { out->feature = VISION_FEATURE_RING_RIGHT; return; }

    out->feature = VISION_FEATURE_NORMAL;
}

/* ============================================================
 * 十字补线
 * ============================================================ */

// 最小二乘拟合：x = k*y + b，Q10 定点
static uint8_t fit_line_x_of_y_q10(const int16_t *x_arr, uint16_t y_start, uint16_t y_end,
                                    int16_t x_invalid, long *out_k_q10, long *out_b_q10)
{
    unsigned long n, sum_y, sum_y2;
    long sum_x, sum_yx, denom, numer;
    long mean_x_q10, mean_y_q10;
    uint16_t y;

    if (y_end <= y_start) return 0;

    n = 0; sum_y = 0; sum_y2 = 0;
    sum_x = 0; sum_yx = 0;

    for (y = y_start; y <= y_end; y++)
    {
        int16_t x = x_arr[y];
        if (x == x_invalid) continue;
        n++;
        sum_y  += (unsigned long)y;
        sum_y2 += (unsigned long)y * (unsigned long)y;
        sum_x  += (long)x;
        sum_yx += (long)y * (long)x;
    }

    if (n < 6) return 0;

    denom = (long)(n * sum_y2) - (long)sum_y * (long)sum_y;
    numer = (long)(n * (unsigned long)sum_yx) - (long)sum_y * (long)sum_x;
    if (denom == 0) return 0;

    *out_k_q10 = (numer << 10) / denom;

    mean_x_q10 = ((long)sum_x << 10) / (long)n;
    mean_y_q10 = ((long)sum_y << 10) / (long)n;
    *out_b_q10 = mean_x_q10 - (long)(((*out_k_q10) * mean_y_q10) >> 10);
    return 1;
}

static int16_t eval_line_q10(long k_q10, long b_q10, uint16_t y)
{
    long x_q10 = k_q10 * (long)y + b_q10;
    if (x_q10 >= 0) return (int16_t)((x_q10 + (1 << 9)) >> 10);
    else            return (int16_t)((x_q10 - (1 << 9)) >> 10);
}

// 十字补线：用十字上方正常赛道边界拟合直线，向下外推到十字区域
static void cross_fill_borders(vision_track_result_t *res)
{
    int16_t y, break_y = -1;
    uint8_t in_cross = 0, narrow_streak = 0;
    uint16_t y_fit_end, y_fit_start;
    long kL_q10, bL_q10, kR_q10, bR_q10;

    for (y = (int16_t)(VISION_H - 1); y >= 0; y--)
    {
        int16_t l, r;
        uint16_t w;

        l = res->left[(uint16_t)y];
        r = res->right[(uint16_t)y];
        if (l < 0 || r < 0) continue;

        w = (uint16_t)(r - l + 1);
        if (!in_cross)
        {
            if (w > (uint16_t)VISION_CROSS_WIDE_TH_NUM &&
                l <= VISION_EDGE_NEAR_TH &&
                r >= (int16_t)(VISION_W - 1 - VISION_EDGE_NEAR_TH))
                in_cross = 1;
        }
        else
        {
            if (w <= (uint16_t)VISION_CROSS_END_TH_NUM)
            {
                narrow_streak++;
                if (narrow_streak >= 3)
                    { break_y = (int16_t)(y + narrow_streak - 1); break; }
            }
            else { narrow_streak = 0; }
        }
    }

    if (break_y < 0) return;

    y_fit_end = (uint16_t)break_y;
    if (y_fit_end <= 5) return;

    y_fit_start = (y_fit_end > 25) ? (uint16_t)(y_fit_end - 25) : 0;
    y_fit_end = (uint16_t)(y_fit_end - 5);
    if (y_fit_end <= y_fit_start) return;
    if (!fit_line_x_of_y_q10(res->left,  y_fit_start, y_fit_end, -1, &kL_q10, &bL_q10)) return;
    if (!fit_line_x_of_y_q10(res->right, y_fit_start, y_fit_end, -1, &kR_q10, &bR_q10)) return;

    for (y = (int16_t)(break_y + 1); y < (int16_t)VISION_H; y++)
    {
        int16_t l = eval_line_q10(kL_q10, bL_q10, (uint16_t)y);
        int16_t r = eval_line_q10(kR_q10, bR_q10, (uint16_t)y);

        l = clamp_i16(l, 0, (int16_t)(VISION_W - 1));
        r = clamp_i16(r, 0, (int16_t)(VISION_W - 1));
        if (l > r) { int16_t t = l; l = r; r = t; }

        res->left[(uint16_t)y]  = l;
        res->right[(uint16_t)y] = r;
        res->mid[(uint16_t)y]   = (int16_t)((l + r) / 2);
    }
}

/* ============================================================
 * 中心误差计算
 * ============================================================ */

// 取前瞻行附近窗口中位中线
static int16_t median_mid_near_y(const vision_track_result_t *res, uint16_t y_center)
{
    int16_t mids[(VISION_CENTER_WINDOW_RADIUS * 2u) + 1u];
    uint16_t cnt = 0;
    int16_t dy;
    uint16_t i, j;

    for (dy = -(int16_t)VISION_CENTER_WINDOW_RADIUS; dy <= (int16_t)VISION_CENTER_WINDOW_RADIUS; dy++)
    {
        int16_t yy = (int16_t)y_center + dy;
        if (yy < 0 || yy >= (int16_t)VISION_H) continue;
        if (res->mid[(uint16_t)yy] >= 0)
            mids[cnt++] = res->mid[(uint16_t)yy];
    }

    if (cnt == 0) return -1;

    // 冒泡排序取中位
    for (i = 0; i < cnt; i++)
        for (j = (uint16_t)(i + 1); j < cnt; j++)
            if (mids[j] < mids[i])
                { int16_t t = mids[i]; mids[i] = mids[j]; mids[j] = t; }

    return mids[cnt / 2];
}

static void compute_center_error(const vision_track_result_t *res, vision_track_result_t *out)
{
    int16_t cx = -1;
    uint16_t y = (uint16_t)VISION_LOOKAHEAD_Y;
    if (y >= VISION_H) y = (uint16_t)(VISION_H - 1);

    if (res->mid[y] >= 0)
    {
        cx = median_mid_near_y(res, y);
        if (cx < 0) cx = res->mid[y];
    }
    else
    {
        for (y = (uint16_t)(VISION_H - 1);; y--)
        {
            if (res->mid[y] >= 0)
            {
                cx = median_mid_near_y(res, y);
                if (cx < 0) cx = res->mid[y];
                break;
            }
            if (y == 0) break;
        }
    }

    out->center_x = cx;
    if (cx >= 0)
    {
        // 帧间平滑
        uint16_t num = (uint16_t)VISION_CENTER_SMOOTH_NUM;
        uint16_t den = (uint16_t)VISION_CENTER_SMOOTH_DEN;
        if (den == 0) den = 1;

        if (g_last_center_x >= 0 && num <= den)
        {
            uint16_t old_num = (uint16_t)(den - num);
            cx = (int16_t)(((long)num * (long)cx + (long)old_num * (long)g_last_center_x) / (long)den);
        }

        // 帧间跳变限幅
        if (g_last_center_x >= 0)
        {
            int16_t delta = (int16_t)(cx - g_last_center_x);
            int16_t max_jump = (int16_t)VISION_CENTER_FRAME_MAX_JUMP;
            if (delta > max_jump)       cx = (int16_t)(g_last_center_x + max_jump);
            else if (delta < -max_jump) cx = (int16_t)(g_last_center_x - max_jump);
        }

        g_last_center_x = cx;
        g_center_hold_cnt = 0;
        out->center_x = cx;
        out->error_x  = (int16_t)(cx - (int16_t)(VISION_W / 2));
    }
    else
    {
        // 短暂保持上一帧中心
        if (g_last_center_x >= 0 && g_center_hold_cnt < (uint8_t)VISION_CENTER_HOLD_FRAMES)
        {
            g_center_hold_cnt++;
            out->center_x = g_last_center_x;
            out->error_x  = (int16_t)(g_last_center_x - (int16_t)(VISION_W / 2));
        }
        else
        {
            g_last_center_x = -1;
            out->error_x = 0;
        }
    }
}

/* ============================================================
 * 主处理入口
 * ============================================================ */

void vision_track_process(const uint8_t *gray, uint8_t *bin, vision_track_result_t *res)
{
    // 1. 阈值
#if (VISION_THRESHOLD_METHOD == VISION_THRESHOLD_OTSU)
    uint8_t thr = compute_threshold_otsu(gray);
#else
    uint8_t thr = compute_threshold_isodata(gray);
#endif

    // 2. 极性
#if (VISION_TRACK_POLARITY == VISION_TRACK_POLARITY_DARK)
    uint8_t track_is_dark = 1;
#elif (VISION_TRACK_POLARITY == VISION_TRACK_POLARITY_BRIGHT)
    uint8_t track_is_dark = 0;
#else
    uint8_t track_is_dark = decide_track_is_dark(gray, thr);
#endif

    // 微偏置
    thr = track_is_dark ? clamp_u8((long)thr + 5) : clamp_u8((long)thr - 7);
    res->threshold = thr;
    res->track_is_dark = track_is_dark;

    // 3. 二值化
#if VISION_USE_SPLIT_THRESHOLD
    binarize_to_track0_split(gray, bin, thr, track_is_dark);
#else
    binarize_to_track0(gray, bin, thr, track_is_dark);
#endif

    // 4. 形态学
    bin_close_small_gaps_row(bin);
    bin_open_small_spurs_row(bin);
#if VISION_BIN_DESPECKLE
    bin_despeckle_4n(bin);
#endif

    // 5. 边界提取
#if VISION_USE_8NEIGHBOR
    if (!extract_edges_8neighbor(bin, res))
        extract_edges(bin, res);
#else
    extract_edges(bin, res);
#endif
    interpolate_edge_gaps(res);
    stabilize_rows_against_glare(res);

    // 6. 特征分类
    classify_feature(res, res);

    // 7. 十字补线
    if (res->feature == VISION_FEATURE_CROSS)
        cross_fill_borders(res);

    // 8. 中心误差
    compute_center_error(res, res);
}

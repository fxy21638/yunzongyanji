// Keil 编译需要库头文件提供外设/类型/宏；
// VS Code IntelliSense 环境下该头文件可能不在工作区，跳过以免报错。

// 不可以直接操作原图像数据
// 不可以直接操作原图像数据
// 不可以直接操作原图像数据

#ifndef __INTELLISENSE__
#include "ky_headfile.h"
#endif

#include "vision_track.h"

#ifdef __INTELLISENSE__
// 仅用于 VS Code 语法分析；Keil 编译时由库头文件提供真实定义
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
#define VISION_SIZE ((uint16_t)(MT9V034_WIDTH * MT9V034_HEIGHT))

// 子采样步长：用于阈值统计/自动极性判断的采样间隔（不是二值化输出的分辨率）。
// - 越大：运算更快，但阈值可能抖动/不准（尤其在光照不均、画面噪声大时）。
// - 越小：阈值更稳定，但耗时更高。
// 一般 1~4 都可用；188x120 场景下 2 是较均衡的默认值。
#define VISION_SAMPLE_STEP 1u

// 行内“有效赛道段”的最小连续长度（像素）。
// - 越大：更抗噪（避免把小黑块/白块当赛道），但细线或远端窄线更容易丢。
// - 越小：更敏感，但更易被噪点诱导。
// 建议 3~8；如果你的赛道/线在远端只有 1~2 像素宽，先别调大。
#define VISION_MIN_RUN_LEN 3u

// 十字判定阈值（按行宽度占比）：
// - VISION_CROSS_WIDE_TH_NUM：认为“进入十字”的宽度阈值（越大越不容易触发）。
// - VISION_CROSS_END_TH_NUM ：认为“离开十字”的宽度阈值（通常略小，形成滞回，减少抖动）。
// 说明：十字判断还叠加了“左右贴边”约束（见 classify_feature / cross_fill_borders），避免宽赛道误判。
#define VISION_CROSS_WIDE_TH_NUM (VISION_W * 8 / 10)
#define VISION_CROSS_END_TH_NUM (VISION_W * 7 / 10)

// 贴边判断阈值：left<=TH 认为贴左边，right>=W-1-TH 认为贴右边。
// - 越大：更容易被认为贴边（十字/环岛更容易触发，也更容易误判）。
// - 越小：更严格，可能漏检十字/环岛。
// 建议 1~4。
#define VISION_EDGE_NEAR_TH 2

// 前瞻行：用于输出 error_x 的参考行。
// - 越靠下：更接近车头“当前看到的近处”，响应更快，但更容易受噪声影响（抖）。
// - 越靠上：更“看远一点”，更平滑，但会引入滞后（过弯可能变慢）。
// 调参建议：先把二值化/边界稳定后再调它；常见范围为 H-20 ~ H-50。
#define VISION_LOOKAHEAD_Y (MT9V034_HEIGHT - 35)

// 使能八邻域轮廓跟踪提边界：
// - 1：优先用 Moore 邻域跟踪外轮廓（边界更连贯，遇到局部缺口更稳），失败则回退逐行搜索。
// - 0：直接逐行找最大连通段（更快更简单，但在十字/环岛/噪声时边界更跳）。
#ifndef VISION_USE_8NEIGHBOR
#define VISION_USE_8NEIGHBOR 1
#endif

// 轮廓点缓存上限：用于保存外轮廓跟踪点。
// - 经验上对“宽赛道外轮廓”长度约在 O(W+H)，取 4*(W+H) 可覆盖大多数情况。
// - 若你发现 8 邻域模式经常失败、且轮廓实际很长（比如复杂形状、很多锯齿），可适当加大。
//   注意：这是静态数组，增大会占用更多 RAM。
// 注意：这里保持为“纯宏常量表达式”，避免某些 C251 环境对强转/typedef 作为数组维度挑剔
#define VISION_CONTOUR_MAX_POINTS (4u * (MT9V034_WIDTH + MT9V034_HEIGHT))

// RGB565 颜色常量
#define VISION_RGB565_BLACK ((Color_t)0x0000)
#define VISION_RGB565_WHITE ((Color_t)0xFFFF)
#define VISION_RGB565_BLUE ((Color_t)0x001F)
#define VISION_RGB565_RED ((Color_t)0xF800)

static uint16_t g_contour_points[VISION_CONTOUR_MAX_POINTS][2];
static int16_t g_last_center_x = -1;
static uint8_t g_center_hold_cnt = 0;

static void find_widest_run_0(const uint8_t *row, uint16_t w, int16_t *out_l, int16_t *out_r)
{
    uint16_t x = 0;
    uint16_t best_len = 0;
    int16_t best_l = -1;
    int16_t best_r = -1;

    while (x < w)
    {
        if (row[x] == 0)
        {
            uint16_t l = x;
            while (x < w && row[x] == 0)
                x++;
            {
                uint16_t r = (uint16_t)(x - 1);
                uint16_t len = (uint16_t)(r - l + 1);
                if (len > best_len)
                {
                    best_len = len;
                    best_l = (int16_t)l;
                    best_r = (int16_t)r;
                }
            }
        }
        else
        {
            x++;
        }
    }

    if (best_len < VISION_MIN_RUN_LEN)
    {
        *out_l = -1;
        *out_r = -1;
    }
    else
    {
        *out_l = best_l;
        *out_r = best_r;
    }
}

static uint8_t in_bounds(int16_t x, int16_t y)
{
    return (x >= 0 && y >= 0 && x < (int16_t)VISION_W && y < (int16_t)VISION_H);
}

static uint8_t bin_at(const uint8_t *bin, int16_t x, int16_t y)
{
    if (!in_bounds(x, y))
        return 255;
    return bin[(uint16_t)y * VISION_W + (uint16_t)x];
}

static uint8_t is_track_pixel(const uint8_t *bin, int16_t x, int16_t y)
{
    return (bin_at(bin, x, y) == 0);
}

static uint8_t is_boundary_track_pixel(const uint8_t *bin, int16_t x, int16_t y)
{
    // 赛道像素(0) 且八邻域存在背景(255)或越界
    if (!is_track_pixel(bin, x, y))
        return 0;

    {
        static const signed char nb[8][2] = {
            {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};
        uint8_t k;
        for (k = 0; k < 8; k++)
        {
            int16_t nx = (int16_t)(x + nb[k][0]);
            int16_t ny = (int16_t)(y + nb[k][1]);
            if (!in_bounds(nx, ny))
                return 1;
            if (bin_at(bin, nx, ny) != 0)
                return 1;
        }
    }

    return 0;
}

static uint8_t find_seed_boundary(const uint8_t *bin, int16_t *out_x, int16_t *out_y)
{
    int16_t y = (int16_t)(VISION_H - 2);
    int16_t cx = (int16_t)(VISION_W / 2);
    int16_t dx;

    if (y < 0)
        y = 0;

    // 从中间向两边找赛道像素，再确认它是边界像素
    for (dx = 0; dx < (int16_t)VISION_W; dx++)
    {
        int16_t x1 = (int16_t)(cx - dx);
        int16_t x2 = (int16_t)(cx + dx);

        if (in_bounds(x1, y) && is_boundary_track_pixel(bin, x1, y))
        {
            *out_x = x1;
            *out_y = y;
            return 1;
        }
        if (in_bounds(x2, y) && is_boundary_track_pixel(bin, x2, y))
        {
            *out_x = x2;
            *out_y = y;
            return 1;
        }
    }

    return 0;
}

// Moore 邻域轮廓追踪：跟踪赛道(0)连通区域的外轮廓
static uint16_t trace_contour_moore(const uint8_t *bin, int16_t sx, int16_t sy)
{
    static const signed char nb[8][2] = {
        {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};

    int16_t cx = sx;
    int16_t cy = sy;
    int16_t bx = (int16_t)(sx - 1);
    int16_t by = sy;
    int16_t b0x = bx;
    int16_t b0y = by;
    uint16_t count = 0;
    uint16_t guard = (uint16_t)(VISION_CONTOUR_MAX_POINTS - 1);

    if (!in_bounds(cx, cy))
        return 0;
    if (!is_boundary_track_pixel(bin, cx, cy))
        return 0;

    while (guard--)
    {
        uint8_t k;
        uint8_t start_idx = 0;

        if (count < VISION_CONTOUR_MAX_POINTS)
        {
            g_contour_points[count][0] = (uint16_t)cx;
            g_contour_points[count][1] = (uint16_t)cy;
            count++;
        }

        // 找 backtrack 点在邻域中的索引
        for (k = 0; k < 8; k++)
        {
            if ((int16_t)(cx + nb[k][0]) == bx && (int16_t)(cy + nb[k][1]) == by)
            {
                start_idx = k;
                break;
            }
        }

        // 从 start_idx 的下一个开始顺时针找下一个轮廓点
        {
            uint8_t found = 0;
            uint8_t i;
            for (i = 0; i < 8; i++)
            {
                uint8_t idx = (uint8_t)((start_idx + 1 + i) & 7);
                int16_t nx = (int16_t)(cx + nb[idx][0]);
                int16_t ny = (int16_t)(cy + nb[idx][1]);
                if (is_track_pixel(bin, nx, ny))
                {
                    // 新 backtrack = 找到点的前一个邻居(逆时针一个)
                    uint8_t prev = (uint8_t)((idx + 7) & 7);
                    bx = (int16_t)(cx + nb[prev][0]);
                    by = (int16_t)(cy + nb[prev][1]);
                    cx = nx;
                    cy = ny;
                    found = 1;
                    break;
                }
            }

            if (!found)
                break;
        }

        // 回到起点并且 backtrack 也回到初始 backtrack，结束
        if (cx == sx && cy == sy && bx == b0x && by == b0y)
        {
            break;
        }
    }

    return count;
}

static uint8_t extract_edges_8neighbor(const uint8_t *bin, vision_track_result_t *res)
{
    int16_t sx, sy;
    uint16_t i;
    uint16_t y;

    // 先在图像底部附近找一个“边界赛道像素”作为轮廓跟踪种子点。
    // 常见失败原因：
    // - 底部赛道被阈值吃掉（bin 全是 255）
    // - 底部噪声严重，找不到满足“边界像素”条件的点
    // 失败会回退到逐行提取（extract_edges）。
    if (!find_seed_boundary(bin, &sx, &sy))
    {
        return 0;
    }

    {
        // 跟踪得到外轮廓点集。
        // n 太小通常表示：
        // - 种子点找到了，但连通区域很小（可能是噪点）
        // - 轮廓被断裂（阈值/去噪不合适）
        // 这里用 n<40 作为“明显不可信”的快速判定；如果你的赛道很窄/分辨率更小，
        // 可适当降低该阈值，但更推荐先把二值化质量调好。
        uint16_t n = trace_contour_moore(bin, sx, sy);
        if (n < 40)
            return 0;

        // init
        for (y = 0; y < VISION_H; y++)
        {
            res->left[y] = -1;
            res->right[y] = -1;
            res->mid[y] = -1;
        }

        // per-row min/max
        for (i = 0; i < n; i++)
        {
            uint16_t x = g_contour_points[i][0];
            uint16_t yy = g_contour_points[i][1];
            if (yy >= VISION_H)
                continue;

            if (res->left[yy] < 0 || (int16_t)x < res->left[yy])
                res->left[yy] = (int16_t)x;
            if (res->right[yy] < 0 || (int16_t)x > res->right[yy])
                res->right[yy] = (int16_t)x;
        }

        res->valid_rows = 0;
        for (y = 0; y < VISION_H; y++)
        {
            if (res->left[y] >= 0 && res->right[y] >= 0)
            {
                // 若轮廓很稀疏导致某些行跨度太小，可用一次全行扫描兜底
                if (res->right[y] - res->left[y] + 1 < (int16_t)VISION_MIN_RUN_LEN)
                {
                    int16_t l = -1, r = -1;
                    const uint8_t *row = &bin[y * VISION_W];
                    find_widest_run_0(row, VISION_W, &l, &r);
                    res->left[y] = l;
                    res->right[y] = r;
                }

                if (res->left[y] >= 0 && res->right[y] >= 0)
                {
                    res->mid[y] = (int16_t)((res->left[y] + res->right[y]) / 2);
                    res->valid_rows++;
                }
            }
        }

        // 需要足够多的有效行才认为“轮廓提取成功”。
        // - 阈值越高：更严格，失败时更容易回退到逐行算法。
        // - 阈值越低：更容易“勉强成功”，但边界可能稀疏、需要更多兜底扫描。
        return (res->valid_rows > (uint8_t)(VISION_H / 3));
    }
}

// 将 long 裁剪到 0~255。
// 说明：很多地方会对阈值做“微偏置”，这里统一做边界保护。
static uint8_t clamp_u8(long v)
{
    if (v < 0)
        return 0;
    if (v > 255)
        return 255;
    return (uint8_t)v;
}

// ISODATA 阈值（迭代均值法），在子采样像素上运行。
// - 优点：实现简单、开销低，阈值变化相对平滑。
// - 风险：当直方图不是明显双峰时，thr 可能偏向“平均灰度”。
// 调参入口：在 vision_track.h 里切换 VISION_THRESHOLD_METHOD。
static uint8_t compute_threshold_isodata(const uint8_t *gray)
{
    unsigned long sum = 0;
    unsigned long cnt = 0;
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

    if (cnt == 0)
        return 128;

    // 初值：均值
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
                    if (v < thr)
                    {
                        sum_low += v;
                        cnt_low++;
                    }
                    else
                    {
                        sum_high += v;
                        cnt_high++;
                    }
                }
            }

            if (cnt_low == 0 || cnt_high == 0)
                break;

            thr = (uint8_t)(((sum_low / cnt_low) + (sum_high / cnt_high)) / 2);
        }

        return thr;
    }
}

// Otsu 阈值（大津法）：在子采样像素上统计直方图，选择类间方差最大的阈值。
// - 优点：在“前景/背景双峰明显”的场景下很稳。
// - 风险：强光斑、过曝、暗角导致分布畸变时，thr 可能跳。
// 注意：为兼容 C251（long long 支持不完整）并避免 32 位溢出，这里使用缩放后的打分。
static uint8_t compute_threshold_otsu(const uint8_t *gray)
{
    static uint16_t hist[256];
    uint16_t i;
    uint16_t x, y;
    unsigned long total = 0;
    unsigned long sum = 0;

    for (i = 0; i < 256; i++)
        hist[i] = 0;

    for (y = 0; y < VISION_H; y += VISION_SAMPLE_STEP)
    {
        const uint8_t *row = &gray[y * VISION_W];
        for (x = 0; x < VISION_W; x += VISION_SAMPLE_STEP)
        {
            uint8_t v = row[x];
            hist[v]++;
        }
    }

    for (i = 0; i < 256; i++)
    {
        total += (unsigned long)hist[i];
        sum += (unsigned long)i * (unsigned long)hist[i];
    }

    if (total == 0)
        return 128;

    {
        unsigned long wB = 0;
        unsigned long sumB = 0;
        unsigned long best_score = 0;
        uint8_t best_thr = 128;

        for (i = 0; i < 256; i++)
        {
            unsigned long wF;
            unsigned long sumF;
            uint16_t mB;
            uint16_t mF;
            long diff;
            unsigned long diff2;
            unsigned long score;

            wB += (unsigned long)hist[i];
            sumB += (unsigned long)i * (unsigned long)hist[i];

            if (wB == 0)
                continue;

            wF = total - wB;
            if (wF == 0)
                break;

            // 均值（8 位范围），分母最大 ~5640，32 位安全
            mB = (uint16_t)(sumB / wB);
            sumF = sum - sumB;
            mF = (uint16_t)(sumF / wF);

            diff = (long)mB - (long)mF;
            diff2 = (unsigned long)(diff * diff); // <= 65025

            // score ~ wB*wF*diff^2，但直接乘会溢出 32 位；对 diff^2 做缩放
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

// 根据底部区域黑白占比，决定“赛道/线”在原灰度中更暗还是更亮。
// 说明：这是给 VISION_TRACK_POLARITY=AUTO 时用的启发式规则，目标是：
// - 线/赛道通常占画面比例较小；如果“暗像素比例很小”则倾向认为“赛道更暗”。
// - 如果“暗像素比例很大”则倾向认为“背景更暗”，此时赛道更亮，需要反相。
// 调参点（若 AUTO 误判）：
// - 可以直接在 vision_track.h 里强制 VISION_TRACK_POLARITY_DARK/BRIGHT。
// - 或调整下面 ratio_x100 的阈值（45/65），让“暗占比”分界更符合你的赛道宽度。
#if (VISION_TRACK_POLARITY == VISION_TRACK_POLARITY_AUTO)
static uint8_t decide_track_is_dark(const uint8_t *gray, uint8_t thr)
{
    uint16_t y;
    unsigned long dark_cnt = 0;
    unsigned long total = 0;

    // 仅看底部 1/3 区域，更贴近循迹。
    // 若你希望更“看近处”，可以把起始行调得更靠下（比例更大）；
    // 若希望更稳定，可扩大统计区域（比例更小）。
    uint16_t y0 = (uint16_t)(VISION_H * 2 / 3);
    for (y = y0; y < VISION_H; y += VISION_SAMPLE_STEP)
    {
        uint16_t x;
        const uint8_t *row = &gray[y * VISION_W];
        for (x = 0; x < VISION_W; x += VISION_SAMPLE_STEP)
        {
            if (row[x] < thr)
                dark_cnt++;
            total++;
        }
    }

    if (total == 0)
        return 1;

    // 经验：若暗像素占比很小(线较窄)，则线更暗
    // 若暗像素占比很大(大面积背景更暗)，则线更亮(需要反相)
    {
        unsigned long ratio_x100 = (dark_cnt * 100u) / total;
        if (ratio_x100 < 45u)
            return 1; // 线/赛道更暗
        if (ratio_x100 > 65u)
            return 0; // 线/赛道更亮
        return 1;
    }
}
#endif

static void binarize_to_track0(const uint8_t *gray, uint8_t *bin, uint8_t thr, uint8_t track_is_dark)
{
    uint16_t i;

    // bin: 0=赛道/线, 255=背景。
    // 关键检查点：如果你在 IPS 上看到赛道区域没有变成“0 区域”，优先检查：
    // - VISION_TRACK_POLARITY 是否设反
    // - thr 是否偏离（可看 res->threshold）
    // - 是否需要启用/调整分区阈值（远端 offset）
    if (track_is_dark)
    {
        for (i = 0; i < VISION_SIZE; i++)
        {
            bin[i] = (gray[i] < thr) ? 0 : 255;
        }
    }
    else
    {
        for (i = 0; i < VISION_SIZE; i++)
        {
            bin[i] = (gray[i] > thr) ? 0 : 255;
        }
    }
}

#if VISION_USE_SPLIT_THRESHOLD
static uint8_t clamp_add_u8(uint8_t base, int8_t delta)
{
    int16_t v = (int16_t)base + (int16_t)delta;
    if (v < 0)
        return 0;
    if (v > 255)
        return 255;
    return (uint8_t)v;
}

static void binarize_to_track0_split(const uint8_t *gray, uint8_t *bin, uint8_t thr, uint8_t track_is_dark)
{
    uint16_t x, y;
    uint16_t far_h = (uint16_t)VISION_FAR_REGION_HEIGHT;
    int8_t off = (int8_t)VISION_FAR_THRESHOLD_OFFSET;

    if (far_h > VISION_H)
        far_h = VISION_H;

    // 分区阈值：对“远端区域（图像上方 y<far_h）”使用 thr+off。
    // 调参口诀：
    // - 远端断线/被背景吃掉：尝试让远端更容易判为“赛道(0)”
    // - 远端粘连/背景被判成赛道：反方向调整
    // 注意：由于 track_is_dark 的不同，thr 变大/变小对结果影响方向也不同，
    // 建议结合显示效果逐步小幅调整（例如每次 5~10）。
    for (y = 0; y < VISION_H; y++)
    {
        uint8_t thr_y = thr;
        if (y < far_h)
            thr_y = clamp_add_u8(thr, off);

        {
            const uint8_t *row = &gray[y * VISION_W];
            uint8_t *out = &bin[y * VISION_W];

            if (track_is_dark)
            {
                for (x = 0; x < VISION_W; x++)
                {
                    out[x] = (row[x] < thr_y) ? 0 : 255;
                }
            }
            else
            {
                for (x = 0; x < VISION_W; x++)
                {
                    out[x] = (row[x] > thr_y) ? 0 : 255;
                }
            }
        }
    }
}
#endif

#if VISION_BIN_DESPECKLE
static void bin_despeckle_4n(uint8_t *bin)
{
    uint16_t y, x;

    // 跳过边界，避免越界
    for (y = 1; y < (uint16_t)(VISION_H - 1); y++)
    {
        for (x = 1; x < (uint16_t)(VISION_W - 1); x++)
        {
            uint8_t v = bin[y * VISION_W + x];
            uint8_t diff = 0;

            if (bin[(y - 1) * VISION_W + x] != v)
                diff++;
            if (bin[(y + 1) * VISION_W + x] != v)
                diff++;
            if (bin[y * VISION_W + (x - 1)] != v)
                diff++;
            if (bin[y * VISION_W + (x + 1)] != v)
                diff++;

            // 若与四邻域中至少 3 个不同，认为是尖点/毛刺，压到背景色(255)。
            // 调参建议：如果你需要保留非常细的线（例如 1 像素线），并且发现线被“断开”，
            // 可临时关闭 VISION_BIN_DESPECKLE 验证是否为这里误伤导致。
            if (diff >= 3)
                bin[y * VISION_W + x] = 255;
        }
    }
}
#endif

static void bin_close_small_gaps_row(uint8_t *bin)
{
    uint16_t y;
    uint16_t gap_max = (uint16_t)VISION_BIN_CLOSE_GAP_MAX;

    if (gap_max == 0)
        return;

    for (y = 0; y < VISION_H; y++)
    {
        uint16_t row_off = (uint16_t)(y * VISION_W);
        uint16_t x = 1;

        while (x + 1 < VISION_W)
        {
            if (bin[row_off + x] != 255)
            {
                x++;
                continue;
            }

            if (bin[row_off + (uint16_t)(x - 1)] == 0)
            {
                uint16_t s = x;
                while (x < VISION_W && bin[row_off + x] == 255)
                    x++;

                if (x < VISION_W && bin[row_off + x] == 0)
                {
                    uint16_t e = (uint16_t)(x - 1);
                    uint16_t len = (uint16_t)(e - s + 1);
                    if (len <= gap_max)
                    {
                        uint16_t k;
                        for (k = s; k <= e; k++)
                        {
                            bin[row_off + k] = 0;
                        }
                    }
                }
            }
            else
            {
                x++;
            }
        }
    }
}

static void bin_open_small_spurs_row(uint8_t *bin)
{
    uint16_t y;
    uint16_t spur_max = (uint16_t)VISION_BIN_OPEN_SPUR_MAX;

    if (spur_max == 0)
        return;

    for (y = 0; y < VISION_H; y++)
    {
        uint16_t row_off = (uint16_t)(y * VISION_W);
        uint16_t x = 1;

        while (x + 1 < VISION_W)
        {
            if (bin[row_off + x] != 0)
            {
                x++;
                continue;
            }

            if (bin[row_off + (uint16_t)(x - 1)] == 255)
            {
                uint16_t s = x;
                while (x < VISION_W && bin[row_off + x] == 0)
                    x++;

                if (x < VISION_W && bin[row_off + x] == 255)
                {
                    uint16_t e = (uint16_t)(x - 1);
                    uint16_t len = (uint16_t)(e - s + 1);
                    if (len <= spur_max)
                    {
                        uint16_t k;
                        for (k = s; k <= e; k++)
                        {
                            bin[row_off + k] = 255;
                        }
                    }
                }
            }
            else
            {
                x++;
            }
        }
    }
}

static void extract_edges(const uint8_t *bin, vision_track_result_t *res)
{
    int16_t last_mid = (int16_t)(VISION_W / 2);
    uint16_t y;

    res->valid_rows = 0;

    for (y = 0; y < VISION_H; y++)
    {
        res->left[y] = -1;
        res->right[y] = -1;
        res->mid[y] = -1;
    }

    // 逐行提边界（回退方案/简化方案）：从底向上扫描。
    // 策略：
    // - 优先在 last_mid 附近扩展，保持中线连续性（抗抖）。
    // - 若该行在 last_mid 处不是赛道(0)或太窄，则全行找“最长的 0 连续段”。
    // 可调参数：VISION_MIN_RUN_LEN（过滤太窄的段）。
    // 典型现象：
    // - 若远端经常丢线：可能是阈值/分区阈值问题，而不是这里。
    // - 若近端边界在噪声下跳：可适当调大 VISION_MIN_RUN_LEN 或开启去毛刺。
    for (y = (uint16_t)(VISION_H - 1);; y--)
    {
        const uint8_t *row = &bin[y * VISION_W];
        int16_t l = -1, r = -1;

        if (last_mid >= 0 && last_mid < (int16_t)VISION_W && row[last_mid] == 0)
        {
            int16_t tl = last_mid;
            int16_t tr = last_mid;

            while (tl > 0 && row[tl] == 0)
                tl--;
            if (row[tl] != 0)
                tl++;

            while (tr < (int16_t)(VISION_W - 1) && row[tr] == 0)
                tr++;
            if (row[tr] != 0)
                tr--;

            l = tl;
            r = tr;

            // 太窄则认为不可靠，退化为全行搜索
            if ((uint16_t)(r - l + 1) < VISION_MIN_RUN_LEN)
            {
                l = -1;
                r = -1;
            }
        }

        if (l < 0)
        {
            find_widest_run_0(row, VISION_W, &l, &r);
        }

        if (l >= 0)
        {
            int16_t m = (int16_t)((l + r) / 2);
            res->left[y] = l;
            res->right[y] = r;
            res->mid[y] = m;
            last_mid = m;
            res->valid_rows++;
        }

        if (y == 0)
            break;
    }
}

static void interpolate_edge_gaps(vision_track_result_t *res)
{
    uint16_t y = 0;
    uint16_t max_gap = (uint16_t)VISION_EDGE_INTERP_MAX_GAP_ROWS;

    if (max_gap == 0)
        return;

    while (y < VISION_H)
    {
        if (res->mid[y] >= 0)
        {
            y++;
            continue;
        }

        {
            uint16_t y0, y1;
            uint16_t g;
            int16_t l0, l1, r0, r1;

            if (y == 0)
            {
                y++;
                continue;
            }

            y0 = (uint16_t)(y - 1);
            if (res->mid[y0] < 0)
            {
                y++;
                continue;
            }

            y1 = y;
            while (y1 < VISION_H && res->mid[y1] < 0)
                y1++;

            if (y1 >= VISION_H || res->mid[y1] < 0)
                break;

            g = (uint16_t)(y1 - y0 - 1);
            if (g == 0 || g > max_gap)
            {
                y = y1;
                continue;
            }

            l0 = res->left[y0];
            l1 = res->left[y1];
            r0 = res->right[y0];
            r1 = res->right[y1];
            if (l0 < 0 || l1 < 0 || r0 < 0 || r1 < 0)
            {
                y = y1;
                continue;
            }

            {
                uint16_t k;
                int16_t gap_i16 = (int16_t)(g + 1);
                for (k = 1; k <= g; k++)
                {
                    uint16_t yy = (uint16_t)(y0 + k);
                    int16_t ki16 = (int16_t)k;
                    int16_t l = (int16_t)(l0 + ((l1 - l0) * ki16) / gap_i16);
                    int16_t r = (int16_t)(r0 + ((r1 - r0) * ki16) / gap_i16);
                    if (l < 0)
                        l = 0;
                    if (r > (int16_t)(VISION_W - 1))
                        r = (int16_t)(VISION_W - 1);
                    if (l > r)
                    {
                        int16_t t = l;
                        l = r;
                        r = t;
                    }
                    res->left[yy] = l;
                    res->right[yy] = r;
                    res->mid[yy] = (int16_t)((l + r) / 2);
                    res->valid_rows++;
                }
            }

            y = y1;
        }
    }
}

static void classify_feature(const vision_track_result_t *res, vision_track_result_t *out)
{
    uint16_t y;
    uint8_t cross_cnt = 0;
    uint8_t ring_left_cnt = 0;
    uint8_t ring_right_cnt = 0;

    // 特征识别仅统计底部一半，减少远处噪声影响。
    // 如需“更早”识别十字/环岛，可把 y0 上移（例如 VISION_H*1/3），但误判风险增加。
    uint16_t y0 = (uint16_t)(VISION_H / 2);

    for (y = y0; y < VISION_H; y++)
    {
        int16_t l = res->left[y];
        int16_t r = res->right[y];
        if (l >= 0)
        {
            uint16_t w = (uint16_t)(r - l + 1);

            // 十字：不仅要“很宽”，还应同时左右贴边，否则宽赛道会误判。
            // 调参入口：
            // - 宽度阈值：VISION_CROSS_WIDE_TH_NUM / VISION_CROSS_END_TH_NUM
            // - 贴边阈值：VISION_EDGE_NEAR_TH
            if (w > (uint16_t)(VISION_W * 8 / 10) && l <= VISION_EDGE_NEAR_TH && r >= (int16_t)(VISION_W - 1 - VISION_EDGE_NEAR_TH))
            {
                cross_cnt++;
            }

            if (w > (uint16_t)(VISION_W * 6 / 10))
            {
                if (l <= 1)
                    ring_left_cnt++;
                if (r >= (int16_t)(VISION_W - 2))
                    ring_right_cnt++;
            }
        }
    }

    // 丢线判定：有效行太少。
    // - 若你在正常赛道上也容易进入 LOST，说明二值化/提边界不稳定，应先回头调阈值与去噪。
    // - 若赛道确实可能只占很少行（例如视野很抬），可适当降低阈值比例。
    if (out->valid_rows < (uint8_t)(VISION_H / 4))
    {
        out->feature = VISION_FEATURE_LOST;
        return;
    }

    // 计数阈值（cross_cnt/ring_cnt）：代表“有多少行满足条件”。
    // - 越大：更稳、更不容易误触发，但更容易漏检或触发更晚。
    // - 越小：更灵敏，但更容易误判。
    if (cross_cnt >= 6)
    {
        out->feature = VISION_FEATURE_CROSS;
        return;
    }

    if (ring_left_cnt >= 6 && ring_right_cnt < 3)
    {
        out->feature = VISION_FEATURE_RING_LEFT;
        return;
    }

    if (ring_right_cnt >= 6 && ring_left_cnt < 3)
    {
        out->feature = VISION_FEATURE_RING_RIGHT;
        return;
    }

    out->feature = VISION_FEATURE_NORMAL;
}

static int16_t clamp_i16(int16_t v, int16_t lo, int16_t hi)
{
    if (v < lo)
        return lo;
    if (v > hi)
        return hi;
    return v;
}

static uint16_t abs_i16_to_u16(int16_t v)
{
    return (uint16_t)((v < 0) ? -v : v);
}

static int16_t median_mid_near_y(const vision_track_result_t *res, uint16_t y_center)
{
    int16_t mids[(VISION_CENTER_WINDOW_RADIUS * 2u) + 1u];
    uint16_t cnt = 0;
    int16_t dy;

    for (dy = -(int16_t)VISION_CENTER_WINDOW_RADIUS; dy <= (int16_t)VISION_CENTER_WINDOW_RADIUS; dy++)
    {
        int16_t y = (int16_t)y_center + dy;
        if (y < 0 || y >= (int16_t)VISION_H)
            continue;
        if (res->mid[(uint16_t)y] >= 0)
            mids[cnt++] = res->mid[(uint16_t)y];
    }

    if (cnt == 0)
        return -1;

    {
        uint16_t i, j;
        for (i = 0; i < cnt; i++)
        {
            for (j = (uint16_t)(i + 1); j < cnt; j++)
            {
                if (mids[j] < mids[i])
                {
                    int16_t t = mids[i];
                    mids[i] = mids[j];
                    mids[j] = t;
                }
            }
        }
    }

    return mids[cnt / 2];
}

static void stabilize_rows_against_glare(vision_track_result_t *res)
{
    int16_t last_l = -1;
    int16_t last_r = -1;
    int16_t last_m = -1;
    uint16_t y;

    for (y = (uint16_t)(VISION_H - 1);; y--)
    {
        int16_t l = res->left[y];
        int16_t r = res->right[y];
        int16_t m = res->mid[y];

        if (l >= 0 && r >= l && m >= 0)
        {
            uint16_t w = (uint16_t)(r - l + 1);

            if (last_m >= 0)
            {
                uint16_t last_w = (uint16_t)(last_r - last_l + 1);
                uint16_t mid_jump = abs_i16_to_u16((int16_t)(m - last_m));
                uint8_t touches_both_edges = (uint8_t)(l <= VISION_EDGE_NEAR_TH &&
                                                       r >= (int16_t)(VISION_W - 1 - VISION_EDGE_NEAR_TH));
                uint8_t width_grows_too_fast = 0;

                if (w > (uint16_t)(last_w + (uint16_t)VISION_ROW_MAX_WIDTH_GROW))
                {
                    if ((unsigned long)w * (unsigned long)VISION_ROW_MAX_WIDTH_RATIO_DEN >
                        (unsigned long)last_w * (unsigned long)VISION_ROW_MAX_WIDTH_RATIO_NUM)
                    {
                        width_grows_too_fast = 1;
                    }
                }

                if (!touches_both_edges &&
                    mid_jump > (uint16_t)VISION_ROW_MAX_CENTER_JUMP &&
                    width_grows_too_fast)
                {
                    res->left[y] = last_l;
                    res->right[y] = last_r;
                    res->mid[y] = last_m;
                }
                else
                {
                    last_l = l;
                    last_r = r;
                    last_m = m;
                }
            }
            else
            {
                last_l = l;
                last_r = r;
                last_m = m;
            }
        }

        if (y == 0)
            break;
    }
}

// 最小二乘拟合：x = k*y + b
// 用 Q10 定点数表示 k/b，避免 float
static uint8_t fit_line_x_of_y_q10(const int16_t *x_arr, uint16_t y_start, uint16_t y_end, int16_t x_invalid,
                                   long *out_k_q10, long *out_b_q10)
{
    unsigned long n = 0;
    unsigned long sum_y = 0;
    unsigned long sum_y2 = 0;
    long sum_x = 0;
    long sum_yx = 0;
    uint16_t y;

    if (y_end <= y_start)
        return 0;

    for (y = y_start; y <= y_end; y++)
    {
        int16_t x = x_arr[y];
        if (x == x_invalid)
            continue;
        n++;
        sum_y += (unsigned long)y;
        sum_y2 += (unsigned long)y * (unsigned long)y;
        sum_x += (long)x;
        sum_yx += (long)y * (long)x;
    }

    if (n < 6)
        return 0;

    // k = (n*sum(yx) - sum(y)*sum(x)) / (n*sum(y2) - sum(y)^2)
    {
        long denom = (long)(n * sum_y2) - (long)sum_y * (long)sum_y;
        long numer = (long)(n * (unsigned long)sum_yx) - (long)sum_y * (long)sum_x;
        if (denom == 0)
            return 0;

        // Q10
        *out_k_q10 = (numer << 10) / denom;
        // b = mean(x) - k*mean(y)
        {
            long mean_x_q10 = ((long)sum_x << 10) / (long)n;
            long mean_y_q10 = ((long)sum_y << 10) / (long)n;
            // C251 对 long long 支持不完整；这里用 long 定点运算即可满足 188x120 的数值范围
            *out_b_q10 = mean_x_q10 - (long)(((*out_k_q10) * mean_y_q10) >> 10);
        }

        return 1;
    }
}

static int16_t eval_line_q10(long k_q10, long b_q10, uint16_t y)
{
    // x_q10 = k_q10*y + b_q10
    long x_q10 = k_q10 * (long)y + b_q10;
    // round
    if (x_q10 >= 0)
        return (int16_t)((x_q10 + (1 << 9)) >> 10);
    else
        return (int16_t)((x_q10 - (1 << 9)) >> 10);
}

// 十字补线：当检测到十字时，用十字上方的边界拟合直线，并向下补到十字区域。
// 目的：十字中心区域往往“全白/全黑”，逐行提取会丢边界，导致中线跳变。
// 参数含义（可按现象微调）：
// - 拟合窗口长度：当前固定取 break_y 往上 25 行作为候选（越长越平滑，越短越贴近局部）。
// - 缓冲行数：拟合终点往上再退 5 行，避开“刚离开十字”那几行的不稳定边界。
static void cross_fill_borders(vision_track_result_t *res)
{
    int16_t y;
    uint8_t in_cross = 0;
    int16_t break_y = -1;

    // 从底向上找：先进入“宽赛道段”区域，再遇到宽度恢复正常时作为 break
    for (y = (int16_t)(VISION_H - 1); y >= 0; y--)
    {
        int16_t l = res->left[(uint16_t)y];
        int16_t r = res->right[(uint16_t)y];
        if (l >= 0 && r >= 0)
        {
            uint16_t w = (uint16_t)(r - l + 1);
            if (!in_cross)
            {
                if (w > (uint16_t)VISION_CROSS_WIDE_TH_NUM && l <= VISION_EDGE_NEAR_TH && r >= (int16_t)(VISION_W - 1 - VISION_EDGE_NEAR_TH))
                {
                    in_cross = 1;
                }
            }
            else
            {
                if (w <= (uint16_t)VISION_CROSS_END_TH_NUM)
                {
                    break_y = y;
                    break;
                }
            }
        }
    }

    if (break_y < 0)
        return;

    {
        uint16_t y_fit_end = (uint16_t)break_y;
        uint16_t y_fit_start;

        if (y_fit_end > 25)
            y_fit_start = (uint16_t)(y_fit_end - 25);
        else
            y_fit_start = 0;

        // 留出几行缓冲，避免刚出十字的行不稳定
        if (y_fit_end > 5)
            y_fit_end = (uint16_t)(y_fit_end - 5);
        else
            return;

        if (y_fit_end <= y_fit_start)
            return;

        {
            long kL_q10 = 0, bL_q10 = 0;
            long kR_q10 = 0, bR_q10 = 0;

            if (!fit_line_x_of_y_q10(res->left, y_fit_start, y_fit_end, -1, &kL_q10, &bL_q10))
                return;
            if (!fit_line_x_of_y_q10(res->right, y_fit_start, y_fit_end, -1, &kR_q10, &bR_q10))
                return;

            // 将 break_y 之后(更靠下)的十字区域补线
            for (y = (int16_t)(break_y + 1); y < (int16_t)VISION_H; y++)
            {
                int16_t l = eval_line_q10(kL_q10, bL_q10, (uint16_t)y);
                int16_t r = eval_line_q10(kR_q10, bR_q10, (uint16_t)y);

                l = clamp_i16(l, 0, (int16_t)(VISION_W - 1));
                r = clamp_i16(r, 0, (int16_t)(VISION_W - 1));
                if (l > r)
                {
                    int16_t t = l;
                    l = r;
                    r = t;
                }

                res->left[(uint16_t)y] = l;
                res->right[(uint16_t)y] = r;
                res->mid[(uint16_t)y] = (int16_t)((l + r) / 2);
            }
        }
    }
}

static void compute_center_error(const vision_track_result_t *res, vision_track_result_t *out)
{
    int16_t cx = -1;
    uint16_t y = (uint16_t)VISION_LOOKAHEAD_Y;

    if (y >= VISION_H)
        y = (uint16_t)(VISION_H - 1);

    // 取前瞻行的中线作为控制参考；若该行无效则从下往上找第一条有效行。
    // 调参入口：VISION_LOOKAHEAD_Y（文件开头宏）。
    if (res->mid[y] >= 0)
    {
        cx = median_mid_near_y(res, y);
        if (cx < 0)
            cx = res->mid[y];
    }
    else
    {
        // fallback: 从下往上找第一条有效中线
        for (y = (uint16_t)(VISION_H - 1);; y--)
        {
            if (res->mid[y] >= 0)
            {
                cx = median_mid_near_y(res, y);
                if (cx < 0)
                    cx = res->mid[y];
                break;
            }
            if (y == 0)
                break;
        }
    }

    out->center_x = cx;
    if (cx >= 0)
    {
        uint16_t num = (uint16_t)VISION_CENTER_SMOOTH_NUM;
        uint16_t den = (uint16_t)VISION_CENTER_SMOOTH_DEN;
        if (den == 0)
            den = 1;

        if (g_last_center_x >= 0 && num <= den)
        {
            uint16_t old_num = (uint16_t)(den - num);
            cx = (int16_t)(((long)num * (long)cx + (long)old_num * (long)g_last_center_x) / (long)den);
        }

        if (g_last_center_x >= 0)
        {
            int16_t delta = (int16_t)(cx - g_last_center_x);
            int16_t max_jump = (int16_t)VISION_CENTER_FRAME_MAX_JUMP;
            if (delta > max_jump)
                cx = (int16_t)(g_last_center_x + max_jump);
            else if (delta < -max_jump)
                cx = (int16_t)(g_last_center_x - max_jump);
        }

        g_last_center_x = cx;
        g_center_hold_cnt = 0;
        out->center_x = cx;
        out->error_x = (int16_t)(cx - (int16_t)(VISION_W / 2));
    }
    else
    {
        if (g_last_center_x >= 0 && g_center_hold_cnt < (uint8_t)VISION_CENTER_HOLD_FRAMES)
        {
            g_center_hold_cnt++;
            out->center_x = g_last_center_x;
            out->error_x = (int16_t)(g_last_center_x - (int16_t)(VISION_W / 2));
        }
        else
        {
            g_last_center_x = -1;
            out->error_x = 0;
        }
    }
}

void vision_track_process(const uint8_t *gray, uint8_t *bin, vision_track_result_t *res)
{
    uint8_t thr;
    uint8_t track_is_dark;

#if (VISION_THRESHOLD_METHOD == VISION_THRESHOLD_OTSU)
    thr = compute_threshold_otsu(gray);
#else
    thr = compute_threshold_isodata(gray);
#endif

#if (VISION_TRACK_POLARITY == VISION_TRACK_POLARITY_DARK)
    track_is_dark = 1;
#elif (VISION_TRACK_POLARITY == VISION_TRACK_POLARITY_BRIGHT)
    track_is_dark = 0;
#else
    track_is_dark = decide_track_is_dark(gray, thr);
#endif

    // 轻微偏置：让阈值更贴近赛道（经验值，用于抵消整体偏暗/偏亮导致的“赛道被吃掉/背景粘连”）。
    // - 当 track_is_dark=1 时：thr 增大，会让“判为赛道(更暗)”的范围略扩大。
    // - 当 track_is_dark=0 时：thr 减小，会让“判为赛道(更亮)”的范围略扩大。
    // 若你发现：
    // - 总是偏向把背景当赛道：可以减小偏置幅度
    // - 总是把赛道吃掉：可以增大偏置幅度
    // 说明：这不是必须调的项，通常优先用分区阈值与极性解决。
    if (track_is_dark)
        thr = clamp_u8((long)thr + 5);
    else
        thr = clamp_u8((long)thr - 7);

    res->threshold = thr;
    res->track_is_dark = track_is_dark;

#if VISION_USE_SPLIT_THRESHOLD
    binarize_to_track0_split(gray, bin, thr, track_is_dark);
#else
    binarize_to_track0(gray, bin, thr, track_is_dark);
#endif

    bin_close_small_gaps_row(bin);
    bin_open_small_spurs_row(bin);

#if VISION_BIN_DESPECKLE
    bin_despeckle_4n(bin);
#endif

    // 边界提取：优先使用八邻域轮廓跟踪，失败则回退到逐行搜索
#if VISION_USE_8NEIGHBOR
    if (!extract_edges_8neighbor(bin, res))
    {
        extract_edges(bin, res);
    }
#else
    extract_edges(bin, res);
#endif
    interpolate_edge_gaps(res);
    stabilize_rows_against_glare(res);

    classify_feature(res, res);

    // 参考八邻域/十字补线思路：十字区域用拟合结果补边界，保证中线稳定
    if (res->feature == VISION_FEATURE_CROSS)
    {
        cross_fill_borders(res);
    }

    compute_center_error(res, res);
}

void vision_track_debug_draw(uint8_t *bin, const vision_track_result_t *res)
{
    uint16_t y;

    for (y = 0; y < VISION_H; y++)
    {
        int16_t l = res->left[y];
        int16_t r = res->right[y];
        int16_t m = res->mid[y];

        if (l >= 0)
        {
            // 这里写入的是“伪灰度”用于调试显示：
            // - left/right：180
            // - mid：100
            // 若你的显示链路对灰度映射不同，可按需要改成更显眼的值。
            bin[y * VISION_W + (uint16_t)l] = 180; // left
            bin[y * VISION_W + (uint16_t)r] = 180; // right
            bin[y * VISION_W + (uint16_t)m] = 100; // mid
        }
    }
}

void vision_track_show_color(uint16_t x, uint16_t y, const vision_track_result_t *res)
{
    uint16_t row;

    for (row = 0; row < VISION_H; row++)
    {
        int16_t l = res->left[row];
        int16_t r = res->right[row];
        int16_t m = res->mid[row];

        // 默认整行蓝色
        if (l < 0 || r < 0 || l > r)
        {
            ips_fill_rectangle(x, (uint16_t)(y + row), (uint16_t)(x + VISION_W - 1), (uint16_t)(y + row), VISION_RGB565_BLUE, 0);
            continue;
        }

        // 左侧蓝色
        if (l > 0)
        {
            ips_fill_rectangle(x, (uint16_t)(y + row), (uint16_t)(x + (uint16_t)l - 1), (uint16_t)(y + row), VISION_RGB565_BLUE, 0);
        }

        // 赛道白色
        ips_fill_rectangle((uint16_t)(x + (uint16_t)l), (uint16_t)(y + row), (uint16_t)(x + (uint16_t)r), (uint16_t)(y + row), VISION_RGB565_WHITE, 0);

        // 右侧蓝色
        if (r < (int16_t)(VISION_W - 1))
        {
            ips_fill_rectangle((uint16_t)(x + (uint16_t)r + 1), (uint16_t)(y + row), (uint16_t)(x + VISION_W - 1), (uint16_t)(y + row), VISION_RGB565_BLUE, 0);
        }

        // 中线黑色（1像素宽）
        if (m >= 0 && m < (int16_t)VISION_W)
        {
            ips_draw_point((uint16_t)(x + (uint16_t)m), (uint16_t)(y + row), VISION_RGB565_BLACK);
        }
    }
}

void vision_track_overlay_lines(uint16_t x, uint16_t y, const vision_track_result_t *res)
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

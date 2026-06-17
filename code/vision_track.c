// ====================================================================
// 视觉循迹核心算法 — 基于 Moore 邻域追踪的双边同步边界提取
// ====================================================================
//
// 12 级处理管线 (vision_track_process):
//
//   原始灰度 (188×120)
//     │
//   [1] Turn_To_Bin      — Otsu 大津法二值化 (阈值×1.075 偏置)
//   [2] Image_Filter      — 8 邻域和阈值形态学滤波
//   [3] Image_Draw_Rectan — 四周 2px 黑边框, 防追踪越界
// [3.5] mask_target       — 靶子区域填充白色(赛道), 防止环壁干扰元素识别
//   [4] Get_Start_Point   — 从图像中间向左右搜索黑白交界种子点
//   [5] Search_L_R        — 双边同步 Moore 8 邻域追踪
//   [6] Get_Borders       — 追踪点集 → 逐行边界数组 (Opt2: 合并左右填充)
//   [7] Cross_Fill        — 拐点检测 + 直线拟合, 补全十字路口缺失边界
//   [8] Center_Line       — 逐行中线 = 道路中心估计 (双边均值/单边±半道宽)
//   [9] Image_Erro        — 加权平均: 0.375×C[103] + 0.5×C[105] + 0.1×C[106]
//  [10] 极性翻转          — 赛道=255→0, 背景=0→255 (YG/VOFA 约定)
//  [11] 帧间平滑          — 当前中心 vs 历史中心取均值
//  [12] 填充输出          — vision_track_result_t (边界/中线/特征/可见行)
//     │
//     ▼
//   g_track (供 trail.c + control.c + VOFA 显示)
//
// 内部二值化约定: 赛道=255(白), 背景=0(黑), 输出前翻转为 YG 约定 (赛道=0)
// 外部接口 vision_track_result_t 使用 x 坐标, 无极性依赖
// ====================================================================

#ifndef __INTELLISENSE__
#include "ky_headfile.h"
#endif

#include "vision_track.h"

/* 靶子检测结果 (定义在 trail.c, 用于掩除靶子区域) */
extern uint8_t g_target_detected;
extern uint8_t g_target_center_x;
extern uint8_t g_target_radius;
extern uint8_t g_target_y_mid;

#ifndef MT9V034_WIDTH
#error "MT9V034_WIDTH not defined"
#endif
#ifndef MT9V034_HEIGHT
#error "MT9V034_HEIGHT not defined"
#endif

/* ============================================================
 * 188×120 适配常量
 * ============================================================ */
#define IMG_W               ((uint16_t)MT9V034_WIDTH)   // 188
#define IMG_H               ((uint16_t)MT9V034_HEIGHT)  // 120
#define IMG_SIZE            ((uint16_t)(IMG_W * IMG_H))

#define MID_TRUST_TOP_MARGIN 8    /* 顶部不采信: Hightest 以上 8 行 */
#define MID_TRUST_BOT_MARGIN 8    /* 底部不采信: 图像底部 8 行 */

#define BORDER_MAX          (IMG_W - 2)   // 186
#define BORDER_MIN          1

#define USE_NUM             ((uint16_t)(IMG_H * 3))  // 360

#define WHITE_PIXEL         255
#define BLACK_PIXEL         0

// Image_Filter 8邻域和阈值
#define THRESHOLD_MAX       (255u * 3u)
#define THRESHOLD_MIN       (255u * 1u)

// Lose_Line 丢线判断 (R_Border >= IMG_W-4=184 视为丢线)
#define LOSE_LINE_R_TH      (IMG_W - 4)   // 184
#define LOSE_LINE_L_TH      2

// Straight_Line_Judge 直线判断计数 (原 60, 按比例: 60*120/80=90)
#define STRAIGHT_LINE_CNT   90

// Image_Erro 前瞻行 (原 row 69-71, 比例缩放: 69*120/80≈103, 71*120/80≈106)
#define ERRO_ROW_LO         103
#define ERRO_ROW_MID        105
#define ERRO_ROW_HI         106

// Cross_Fill 搜索范围
#define CROSS_SEARCH_UP     (IMG_H / 2 + 35)  // 95 (原 Image_H/2+35=75)
#define CROSS_SEARCH_DOWN   (IMG_H / 2 - 5)   // 55 (原 Image_H/2-5=35)

/* ============================================================
 * 静态状态
 * ============================================================ */
static uint8_t L_Border[IMG_H];
static uint8_t R_Border[IMG_H];
static uint8_t Hightest;
/* Opt2: 半道宽缓存 + Image_Erro 三行加权缓存 (避免第 11 步重新算) */
static int8_t g_half_lane_w;
static uint8_t g_erro_lo, g_erro_mid, g_erro_hi;
static uint16_t g_last_lane_w; /* 上一帧有效道宽, 测量失败时沿用 */

static uint16_t Points_L[USE_NUM][2];
static uint16_t Points_R[USE_NUM][2];
static uint16_t Dir_L[USE_NUM];
static uint16_t Dir_R[USE_NUM];
static uint16_t Data_Stastics_L;
static uint16_t Data_Stastics_R;

static uint8_t Start_Point_L[2];
static uint8_t Start_Point_R[2];

static int g_HistGram[256];

// Otsu 工作变量 (避免 C251 局部变量过多导致栈溢出)
static uint16_t g_Otsu_W, g_Otsu_H;
static int g_Otsu_X;
static uint16_t g_Otsu_Y;
static uint8_t *g_Otsu_Data;
static uint32_t g_Otsu_Amount;
static uint32_t g_Otsu_PixelBack;
static uint32_t g_Otsu_PixelIntegralBack;
static uint32_t g_Otsu_PixelIntegral;
static int32_t g_Otsu_PixelIntegralFore;
static int32_t g_Otsu_PixelFore;
static double g_Otsu_OmegaBack, g_Otsu_OmegaFore;
static double g_Otsu_MicroBack, g_Otsu_MicroFore;
static double g_Otsu_SigmaB, g_Otsu_Sigma;
static uint8_t g_Otsu_MinVal, g_Otsu_MaxVal;
static uint8_t g_Otsu_Threshold;
static uint8_t g_Otsu_iClear;

static uint8_t Image_Flag_Cross_Fill;
static uint8_t Image_Flag_Get_Start_Point;

static int16_t g_last_center_x = -1;

// Moore 邻域种子 (左边顺时针, 右边逆时针)
// 左边顺时针
static const int8_t Seeds_L[8][2] = {
    {0,  1}, {-1, 1}, {-1, 0}, {-1, -1},
    {0, -1}, {1, -1}, {1,  0}, {1,  1}
};
// 右边逆时针
static const int8_t Seeds_R[8][2] = {
    {0,  1}, {1, 1}, {1, 0}, {1, -1},
    {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
};

/* ============================================================
 * 工具函数
 * ============================================================ */

static int My_Abs(int value)
{
    if (value >= 0) return value;
    else return -value;
}

static int16_t Limit_a_b(int16_t x, int a, int b)
{
    if (x < a) x = (int16_t)a;
    if (x > b) x = (int16_t)b;
    return x;
}

/* ============================================================
 * 浮点数学函数 (C251 无标准库 libm, 从 point_set 迁移)
 * ============================================================ */

// Newton 法求平方根
float sqrtf(float x)
{
    float y;
    uint8_t i;
    if (x <= 0.0f) return 0.0f;
    y = (x > 1.0f) ? x : 1.0f;
    for (i = 0; i < 8; i++)
    {
        y = (y + x / y) * 0.5f;
    }
    return y;
}

// Padé [2/4] 反正切逼近 (|z|<=1, max error < 0.0009 rad)
static float atan_approx(float z)
{
    float z2, z4, num, den;
    z2 = z * z;
    z4 = z2 * z2;
    num = z * (1.0f + 0.07735027027f * z2);
    den = 1.0f + 0.41035027027f * z2 + 0.08753400568f * z4;
    return num / den;
}

// 四象限反正切, 返回 radian 值 [-PI, PI]
float atan2f(float y, float x)
{
    float pi, half_pi;
    pi     = 3.14159265358979f;
    half_pi = 1.5707963267949f;

    if (x == 0.0f)
    {
        if (y > 0.0f) return half_pi;
        if (y < 0.0f) return -half_pi;
        return 0.0f;
    }

    if (x > 0.0f)
        return atan_approx(y / x);
    else if (y >= 0.0f)
        return atan_approx(y / x) + pi;
    else
        return atan_approx(y / x) - pi;
}

// Menger 曲率 (×1000), 三点确定圆: K = 4*面积/(a*b*c)
// 返回值: 正值右转, 负值左转
int16_t pts_curvature_3pt(const uint8_t p0[2], const uint8_t p1[2], const uint8_t p2[2])
{
    float dx10, dy10, dx20, dy20, dx21, dy21;
    float area, a, b, c, denom, curv;
    float f01, f02, f12;

    dx10 = (float)p1[0] - (float)p0[0];
    dy10 = (float)p1[1] - (float)p0[1];
    dx20 = (float)p2[0] - (float)p0[0];
    dy20 = (float)p2[1] - (float)p0[1];
    dx21 = (float)p2[0] - (float)p1[0];
    dy21 = (float)p2[1] - (float)p1[1];

    area = 0.5f * (dx10 * dy20 - dx20 * dy10);
    if (area < 0.0f) area = -area;
    if (area < 1e-6f) return 0;

    f01 = dx10 * dx10 + dy10 * dy10;
    f02 = dx20 * dx20 + dy20 * dy20;
    f12 = dx21 * dx21 + dy21 * dy21;
    a = sqrtf(f01);
    b = sqrtf(f02);
    c = sqrtf(f12);

    denom = a * b * c;
    if (denom < 1e-6f) return 0;

    curv = 4.0f * area / denom;
    return (int16_t)((float)((dx10 * dy20 - dx20 * dy10) > 0.0f ? curv : -curv) * 1000.0f);
}

// 最小二乘斜率
static float Slope_Calculate(uint8_t begin, uint8_t end, uint8_t *border)
{
    float xsum, ysum, xysum, x2sum;
    int16_t i;
    float result;
    static float resultlast;
    float denom;

    xsum = 0.0f; ysum = 0.0f; xysum = 0.0f; x2sum = 0.0f;

    for (i = (int16_t)begin; i < (int16_t)end; i++)
    {
        xsum  += (float)i;
        ysum  += (float)border[i];
        xysum += (float)i * (float)(border[i]);
        x2sum += (float)i * (float)i;
    }
    denom = ((float)(end - begin) * x2sum - xsum * xsum);
    if (denom != 0.0f)
    {
        result = ((float)(end - begin) * xysum - xsum * ysum) / denom;
        resultlast = result;
    }
    else
    {
        result = resultlast;
    }
    return result;
}

// 两点求斜率截距
static uint8_t Get_K_b(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,
                       float *slope_rate, float *intercept)
{
    if (x1 == x2) return 0;

    *slope_rate = (float)((int16_t)y2 - (int16_t)y1)
                / (float)((int16_t)x2 - (int16_t)x1);
    *intercept = (float)y1 - (*slope_rate * (float)x1);
    return 1;
}

/* ============================================================
 * Otsu 大津法阈值 — 遍历灰度直方图最大化类间方差
 * ============================================================ */
static uint8_t Otsu_Threshold(uint8_t *Image, uint16_t col, uint16_t row)
{
    g_Otsu_W = col;
    g_Otsu_H = row;
    g_Otsu_Data = Image;

    for (g_Otsu_iClear = 0; g_Otsu_iClear < 255; g_Otsu_iClear++)
        g_HistGram[g_Otsu_iClear] = 0;
    g_HistGram[255] = 0;

    for (g_Otsu_Y = 0; g_Otsu_Y < g_Otsu_H; g_Otsu_Y++)
    {
        for (g_Otsu_X = 0; g_Otsu_X < (int)g_Otsu_W; g_Otsu_X++)
        {
            g_HistGram[(int)g_Otsu_Data[g_Otsu_Y * g_Otsu_W + g_Otsu_X]]++;
        }
    }

    for (g_Otsu_MinVal = 0; g_Otsu_MinVal < 255 && g_HistGram[g_Otsu_MinVal] == 0; g_Otsu_MinVal++);
    for (g_Otsu_MaxVal = 255; g_Otsu_MaxVal > g_Otsu_MinVal && g_HistGram[g_Otsu_MinVal] == 0; g_Otsu_MaxVal--);

    if (g_Otsu_MaxVal == g_Otsu_MinVal) return g_Otsu_MaxVal;
    if (g_Otsu_MinVal + 1 == g_Otsu_MaxVal) return g_Otsu_MinVal;

    g_Otsu_Amount = 0;
    for (g_Otsu_Y = g_Otsu_MinVal; g_Otsu_Y <= g_Otsu_MaxVal; g_Otsu_Y++)
        g_Otsu_Amount += (uint32_t)g_HistGram[g_Otsu_Y];

    g_Otsu_PixelIntegral = 0;
    for (g_Otsu_Y = g_Otsu_MinVal; g_Otsu_Y <= g_Otsu_MaxVal; g_Otsu_Y++)
        g_Otsu_PixelIntegral += (uint32_t)g_HistGram[g_Otsu_Y] * (uint32_t)g_Otsu_Y;

    g_Otsu_SigmaB = -1.0;
    g_Otsu_Threshold = 0;
    g_Otsu_PixelBack = 0;
    g_Otsu_PixelIntegralBack = 0;

    for (g_Otsu_Y = g_Otsu_MinVal; g_Otsu_Y < g_Otsu_MaxVal; g_Otsu_Y++)
    {
        g_Otsu_PixelBack += (uint32_t)g_HistGram[g_Otsu_Y];
        g_Otsu_PixelFore = (int32_t)(g_Otsu_Amount - g_Otsu_PixelBack);
        g_Otsu_OmegaBack = (double)g_Otsu_PixelBack / (double)g_Otsu_Amount;
        g_Otsu_OmegaFore = (double)g_Otsu_PixelFore / (double)g_Otsu_Amount;
        g_Otsu_PixelIntegralBack += (uint32_t)g_HistGram[g_Otsu_Y] * (uint32_t)g_Otsu_Y;
        g_Otsu_PixelIntegralFore = (int32_t)(g_Otsu_PixelIntegral - g_Otsu_PixelIntegralBack);
        g_Otsu_MicroBack = (double)g_Otsu_PixelIntegralBack / (double)g_Otsu_PixelBack;
        g_Otsu_MicroFore = (double)g_Otsu_PixelIntegralFore / (double)g_Otsu_PixelFore;
        g_Otsu_Sigma = g_Otsu_OmegaBack * g_Otsu_OmegaFore
                     * (g_Otsu_MicroBack - g_Otsu_MicroFore)
                     * (g_Otsu_MicroBack - g_Otsu_MicroFore);
        if (g_Otsu_Sigma > g_Otsu_SigmaB)
        {
            g_Otsu_SigmaB = g_Otsu_Sigma;
            g_Otsu_Threshold = (uint8_t)g_Otsu_Y;
        }
    }
    return g_Otsu_Threshold;
}

/* ============================================================
 * Turn_To_Bin — 二值化 (Otsu*1.075, bright→255=track)
 * ============================================================ */
static void Turn_To_Bin(uint8_t *gray, uint8_t *bin, uint8_t *out_thr)
{
    uint8_t i, j;
    uint8_t thr_raw;
    float thr_f;

    thr_raw = Otsu_Threshold(gray, IMG_W, IMG_H);
    thr_f = 1.075f * (float)thr_raw;
    if (thr_f > 254.0f) thr_f = 254.0f;
    if (thr_f < 1.0f)   thr_f = 1.0f;
    *out_thr = (uint8_t)thr_f;

    for (i = 0; i < IMG_H; i++)
    {
        for (j = 0; j < IMG_W; j++)
        {
            if (gray[i * IMG_W + j] > (*out_thr))
                bin[i * IMG_W + j] = WHITE_PIXEL;  // 赛道
            else
                bin[i * IMG_W + j] = BLACK_PIXEL;  // 背景
        }
    }
}

/* ============================================================
 * Image_Filter — 4邻域和阈值滤波 (上下左右, 16bit加速)
 * sum >= 255*3 → 填白(255), sum <= 255*1 → 填黑(0)
 * ============================================================ */
static void Image_Filter(uint8_t *bin)
{
    uint16_t i, j;
    uint16_t num;
    uint16_t row_prev;
    uint16_t row_cur;
    uint16_t row_next;

    for (i = 1; i < (uint16_t)(IMG_H - 1); i++)
    {
        row_prev = (uint16_t)(i - 1) * IMG_W;
        row_cur  = (uint16_t)i * IMG_W;
        row_next = (uint16_t)(i + 1) * IMG_W;
        for (j = 1; j < (uint16_t)(IMG_W - 1); j++)
        {
            num = (uint16_t)bin[row_prev + j]
                + (uint16_t)bin[row_cur + (j - 1)]
                + (uint16_t)bin[row_cur + (j + 1)]
                + (uint16_t)bin[row_next + j];

            if (num >= THRESHOLD_MAX && bin[row_cur + j] == 0)
                bin[row_cur + j] = 255;
            if (num <= THRESHOLD_MIN && bin[row_cur + j] == 255)
                bin[row_cur + j] = 0;
        }
    }
}

/* ============================================================
 * Image_Draw_Rectan — 画黑边框 (四周 2px 涂黑, 防止追踪跑到图像外)
 * ============================================================ */
static void Image_Draw_Rectan(uint8_t *bin)
{
    uint8_t i;

    for (i = 0; i < IMG_H; i++)
    {
        bin[i * IMG_W + 0] = 0;
        bin[i * IMG_W + 1] = 0;
        bin[i * IMG_W + (IMG_W - 1)] = 0;
        bin[i * IMG_W + (IMG_W - 2)] = 0;
    }
    for (i = 0; i < IMG_W; i++)
    {
        bin[i] = 0;                     // row 0
        bin[IMG_W + i] = 0;             // row 1
    }
}

/* ============================================================
 * Get_Start_Point — 从中间向两边找黑白交界种子点
 * ============================================================ */
static uint8_t Get_Start_Point(uint8_t *bin, uint8_t Start_Row)
{
    uint8_t i;
    uint8_t L_Found, R_Found;

    L_Found = 0;
    R_Found = 0;
    Image_Flag_Get_Start_Point = 0;

    Start_Point_L[0] = 0;
    Start_Point_L[1] = 0;
    Start_Point_R[0] = 0;
    Start_Point_R[1] = 0;

    // 从中间向左找: 白(赛道)在左, 黑在右 → 右边界
    for (i = (uint8_t)(IMG_W / 2); i > BORDER_MIN; i--)
    {
        Start_Point_L[0] = i;
        Start_Point_L[1] = Start_Row;
        if (bin[Start_Row * IMG_W + i] == 255
            && bin[Start_Row * IMG_W + (i - 1)] == 0)
        {
            L_Found = 1;
            break;
        }
    }

    // 从中间向右找: 白(赛道)在右, 黑在左 → 左边界
    for (i = (uint8_t)(IMG_W / 2); i < BORDER_MAX; i++)
    {
        Start_Point_R[0] = i;
        Start_Point_R[1] = Start_Row;
        if (bin[Start_Row * IMG_W + i] == 255
            && bin[Start_Row * IMG_W + (i + 1)] == 0)
        {
            R_Found = 1;
            break;
        }
    }

    if (L_Found && R_Found)
    {
        Image_Flag_Get_Start_Point = 1;
        return 1;
    }
    else
    {
        Image_Flag_Get_Start_Point = 0;
        return 0;
    }
}

/* ============================================================
 * Search_L_R — 双边同步 Moore 邻域追踪 (8 邻域边界跟踪)
 * 左边顺时针, 右边逆时针, 同步防止交叉
 * ============================================================ */
static void Search_L_R(uint16_t Break_Flag, uint8_t *image,
                       uint16_t *L_Stastic, uint16_t *R_Stastic,
                       uint8_t L_Start_X, uint8_t L_Start_Y,
                       uint8_t R_Start_X, uint8_t R_Start_Y,
                       uint8_t *pHightest)
{
    uint8_t i, j;
    uint16_t L_Data_Statics, R_Data_Statics;
    uint8_t Center_Point_L[2], Center_Point_R[2];
    uint8_t Search_Filds_L[8][2];
    uint8_t Search_Filds_R[8][2];
    uint8_t Temp_L[8][2];
    uint8_t Temp_R[8][2];
    uint8_t Index_L, Index_R;
    /* 白像素优先选择变量 (Fix 1a) */
    int8_t dx, dy;
    uint8_t wx;
    uint8_t best_w;
    uint8_t found;

    L_Data_Statics = *L_Stastic;
    R_Data_Statics = *R_Stastic;

    Center_Point_L[0] = L_Start_X;
    Center_Point_L[1] = L_Start_Y;
    Center_Point_R[0] = R_Start_X;
    Center_Point_R[1] = R_Start_Y;

    while (Break_Flag--)
    {
        // === 左边 — 计算8邻域坐标 ===
        for (i = 0; i < 8; i++)
        {
            Search_Filds_L[i][0] = (uint8_t)((int16_t)Center_Point_L[0] + Seeds_L[i][0]);
            Search_Filds_L[i][1] = (uint8_t)((int16_t)Center_Point_L[1] + Seeds_L[i][1]);
        }

        // 记录左边当前点
        Points_L[L_Data_Statics][0] = Center_Point_L[0];
        Points_L[L_Data_Statics][1] = Center_Point_L[1];
        L_Data_Statics++;

        // === 右边 — 计算8邻域坐标 ===
        for (i = 0; i < 8; i++)
        {
            Search_Filds_R[i][0] = (uint8_t)((int16_t)Center_Point_R[0] + Seeds_R[i][0]);
            Search_Filds_R[i][1] = (uint8_t)((int16_t)Center_Point_R[1] + Seeds_R[i][1]);
        }

        // 记录右边当前点
        Points_R[R_Data_Statics][0] = Center_Point_R[0];
        Points_R[R_Data_Statics][1] = Center_Point_R[1];

        // === 左边判断: 找黑→白过渡 (bg→track) ===
        Index_L = 0;
        for (i = 0; i < 8; i++)
            { Temp_L[i][0] = 0; Temp_L[i][1] = 0; }

        for (i = 0; i < 8; i++)
        {
            if (image[Search_Filds_L[i][1] * IMG_W + Search_Filds_L[i][0]] == 0
                && image[Search_Filds_L[((i + 1) & 7)][1] * IMG_W
                       + Search_Filds_L[((i + 1) & 7)][0]] == 255)
            {
                Temp_L[Index_L][0] = Search_Filds_L[i][0];
                Temp_L[Index_L][1] = Search_Filds_L[i][1];
                Index_L++;
                Dir_L[L_Data_Statics - 1] = i;
            }
        }

        /* Fix 1a + Opt1+2: 单候选快速路径 — 跳过 3x3 白像素扫描 */
        if (Index_L == 1)
        {
            Center_Point_L[0] = Temp_L[0][0];
            Center_Point_L[1] = Temp_L[0][1];
        }
        else if (Index_L > 1)
        {
            /* 多候选: 选 3x3 白像素最多 (避免环壁暗区吸附) */
            Center_Point_L[0] = Temp_L[0][0];
            Center_Point_L[1] = Temp_L[0][1];
            best_w = 0;
            found = 0;
            for (j = 0; j < Index_L; j++)
            {
                wx = 0;
                for (dy = -1; dy <= 1; dy++)
                {
                    for (dx = -1; dx <= 1; dx++)
                    {
                        int16_t npx = (int16_t)Temp_L[j][0] + (int16_t)dx;
                        int16_t npy = (int16_t)Temp_L[j][1] + (int16_t)dy;
                        if (npx < 0 || npx >= (int16_t)IMG_W ||
                            npy < 0 || npy >= (int16_t)IMG_H)
                            continue;
                        if (image[(uint16_t)npy * IMG_W + (uint16_t)npx] == 255)
                            wx++;
                    }
                }
                if ((wx > best_w) ||
                    ((wx == best_w) && (found == 0 || Temp_L[j][1] < Center_Point_L[1])))
                {
                    best_w = wx;
                    Center_Point_L[0] = Temp_L[j][0];
                    Center_Point_L[1] = Temp_L[j][1];
                    found = 1;
                }
            }
        }
        /* else: Index_L == 0, Center_Point_L keeps its previous value (will trigger stuck detection) */

        // 停滞检测: 连续3次同一点 → 退出
        if ((Points_R[R_Data_Statics][0] == Points_R[R_Data_Statics - 1][0]
             && Points_R[R_Data_Statics][0] == Points_R[R_Data_Statics - 2][0]
             && Points_R[R_Data_Statics][1] == Points_R[R_Data_Statics - 1][1]
             && Points_R[R_Data_Statics][1] == Points_R[R_Data_Statics - 2][1])
            || (Points_L[L_Data_Statics - 1][0] == Points_L[L_Data_Statics - 2][0]
                && Points_L[L_Data_Statics - 1][0] == Points_L[L_Data_Statics - 3][0]
                && Points_L[L_Data_Statics - 1][1] == Points_L[L_Data_Statics - 2][1]
                && Points_L[L_Data_Statics - 1][1] == Points_L[L_Data_Statics - 3][1]))
        {
            break;
        }

        // 左右边界交叉检测
        if (My_Abs((int)Points_R[R_Data_Statics][0]
                 - (int)Points_L[L_Data_Statics - 1][0]) < 2
            && My_Abs((int)Points_R[R_Data_Statics][1]
                    - (int)Points_L[L_Data_Statics - 1][1]) < 2)
        {
            *pHightest = (uint8_t)(((uint16_t)Points_R[R_Data_Statics][1]
                                  + (uint16_t)Points_L[L_Data_Statics - 1][1]) >> 1);
            break;
        }

        // 同步: 左边比右边高 → 左边等待
        if (Points_R[R_Data_Statics][1] < Points_L[L_Data_Statics - 1][1])
            continue;

        // 左边方向=7(正上方)且高于右边 → 左边等待
        if (Dir_L[L_Data_Statics - 1] == 7
            && Points_R[R_Data_Statics][1] > Points_L[L_Data_Statics - 1][1])
        {
            Center_Point_L[0] = (uint8_t)Points_L[L_Data_Statics - 1][0];
            Center_Point_L[1] = (uint8_t)Points_L[L_Data_Statics - 1][1];
            L_Data_Statics--;
        }
        R_Data_Statics++;

        // === 右边判断: 找黑→白过渡 (bg→track) ===
        Index_R = 0;
        for (i = 0; i < 8; i++)
            { Temp_R[i][0] = 0; Temp_R[i][1] = 0; }

        for (i = 0; i < 8; i++)
        {
            if (image[Search_Filds_R[i][1] * IMG_W + Search_Filds_R[i][0]] == 0
                && image[Search_Filds_R[((i + 1) & 7)][1] * IMG_W
                       + Search_Filds_R[((i + 1) & 7)][0]] == 255)
            {
                Temp_R[Index_R][0] = Search_Filds_R[i][0];
                Temp_R[Index_R][1] = Search_Filds_R[i][1];
                Index_R++;
                Dir_R[R_Data_Statics - 1] = i;
            }
        }

        /* Fix 1a + Opt1+2: 单候选快速路径 */
        if (Index_R == 1)
        {
            Center_Point_R[0] = Temp_R[0][0];
            Center_Point_R[1] = Temp_R[0][1];
        }
        else if (Index_R > 1)
        {
            Center_Point_R[0] = Temp_R[0][0];
            Center_Point_R[1] = Temp_R[0][1];
            best_w = 0;
            found = 0;
            for (j = 0; j < Index_R; j++)
            {
                wx = 0;
                for (dy = -1; dy <= 1; dy++)
                {
                    for (dx = -1; dx <= 1; dx++)
                    {
                        int16_t npx = (int16_t)Temp_R[j][0] + (int16_t)dx;
                        int16_t npy = (int16_t)Temp_R[j][1] + (int16_t)dy;
                        if (npx < 0 || npx >= (int16_t)IMG_W ||
                            npy < 0 || npy >= (int16_t)IMG_H)
                            continue;
                        if (image[(uint16_t)npy * IMG_W + (uint16_t)npx] == 255)
                            wx++;
                    }
                }
                if ((wx > best_w) ||
                    ((wx == best_w) && (found == 0 || Temp_R[j][1] < Center_Point_R[1])))
                {
                    best_w = wx;
                    Center_Point_R[0] = Temp_R[j][0];
                    Center_Point_R[1] = Temp_R[j][1];
                    found = 1;
                }
            }
        }
    }

    *L_Stastic = L_Data_Statics;
    *R_Stastic = R_Data_Statics;
}

/* ============================================================
 * Get_Borders — 从点集提取左右边界逐行数组 (Opt2: 合并 Get_Left + Get_Right)
 *   原来两个函数各做一次 IMG_H 初始化 + 各自遍历点集
 *   合并后: 一次初始化 + 一次遍历左右点集
 * ============================================================ */
static void Get_Borders(uint16_t Total_L, uint16_t Total_R)
{
    uint8_t i;
    uint16_t j;
    int16_t h;

    /* 一次初始化左右边界数组 (Opt2: 省 1 次 IMG_H 循环) */
    for (i = 0; i < IMG_H; i++)
    {
        L_Border[i] = (uint8_t)BORDER_MIN;
        R_Border[i] = (uint8_t)BORDER_MAX;
    }

    /* 左边界: 从底向上匹配行号 */
    h = (int16_t)(IMG_H - 2);
    for (j = 0; j < Total_L; j++)
    {
        if (Points_L[j][1] == (uint16_t)h)
        {
            L_Border[h] = (uint8_t)(Points_L[j][0] + 1);
        }
        else
        {
            continue;
        }
        h--;
        if (h == 0) break;
    }

    /* 右边界: 从底向上匹配行号 */
    h = (int16_t)(IMG_H - 2);
    for (j = 0; j < Total_R; j++)
    {
        if (Points_R[j][1] == (uint16_t)h)
        {
            R_Border[h] = (uint8_t)(Points_R[j][0] - 1);
        }
        else
        {
            continue;
        }
        h--;
        if (h == 0) break;
    }
}

/* ============================================================
 * Lose_Line — 丢线判断 (检查左右边界是否同时碰到图像边缘)
 * ============================================================ */
static uint8_t Lose_Line(void)
{
    int i;
    uint8_t Lose_Line_Point_L, Lose_Line_Point_R;
    uint8_t prev_l, prev_r;
    uint8_t stuck_run_l, stuck_run_r;

    Lose_Line_Point_L = 0;
    Lose_Line_Point_R = 0;
    prev_l = 255;
    prev_r = 255;
    stuck_run_l = 0;
    stuck_run_r = 0;

    for (i = (int)(IMG_H / 2 + 20); i > (int)(IMG_H / 2 - 20); i -= 1)
    {
        /* 左边界: 贴边 ≤ 2 算 (Fix 1b: 加入常年贴边不算丢) */
        if (L_Border[i] <= (uint8_t)LOSE_LINE_L_TH)
        {
            if (prev_l != 255 && prev_l > (uint8_t)LOSE_LINE_L_TH + 5)
            {
                /* 从正常位置突然跳到贴边 → 真丢线 */
                Lose_Line_Point_L++;
            }
            else if (stuck_run_l < 5)
            {
                /* 刚贴边, 连续 < 5 行才计 */
                Lose_Line_Point_L++;
            }
            stuck_run_l++;
        }
        else
        {
            stuck_run_l = 0;
        }
        prev_l = L_Border[i];

        /* 右边界: 贴边 ≥ 184 算 */
        if (R_Border[i] >= (uint8_t)LOSE_LINE_R_TH)
        {
            if (prev_r != 255 && prev_r < (uint8_t)LOSE_LINE_R_TH - 5)
            {
                /* 从正常位置突然跳到贴边 → 真丢线 */
                Lose_Line_Point_R++;
            }
            else if (stuck_run_r < 5)
            {
                /* 刚贴边, 连续 < 5 行才计 */
                Lose_Line_Point_R++;
            }
            stuck_run_r++;
        }
        else
        {
            stuck_run_r = 0;
        }
        prev_r = R_Border[i];
    }

    if (Lose_Line_Point_L >= 10 && Lose_Line_Point_R >= 10)
        return 1;
    else if (Lose_Line_Point_L >= 10)
        return 2;
    else if (Lose_Line_Point_R >= 10)
        return 3;
    else
        return 0;
}

/* ============================================================
 * Straight_Line_Judge — 直线判断 (相邻行边界变化量累计, 判断赛道是否笔直)
 * lineMode: 0=LeftLine, 1=RightLine
 * ============================================================ */
static uint8_t Straight_Line_Judge(uint8_t *Border, uint16_t Total_Num,
                                   uint8_t lineMode)
{
    int i;
    uint8_t StraightPoint;
    int16_t diff;

    if (Total_Num <= 1) return 1;

    StraightPoint = 0;

    for (i = (int)(IMG_H - 2); i > (int)Hightest; i -= 1)
    {
        if (lineMode == 1)  // RightLine
        {
            diff = (int16_t)Border[i] - (int16_t)Border[i - 1];
            if (diff >= 0 && diff < 2
                && Border[i] < (uint8_t)LOSE_LINE_R_TH
                && Border[i - 1] < (uint8_t)LOSE_LINE_R_TH
                && Border[i] > (uint8_t)(IMG_W / 2)
                && Border[i - 1] > (uint8_t)(IMG_W / 2))
            {
                StraightPoint++;
            }
            else if (My_Abs(diff) > 5)
            {
                StraightPoint = 0;
            }

            if (StraightPoint >= STRAIGHT_LINE_CNT)
                return 1;
        }
        else  // LeftLine
        {
            diff = (int16_t)Border[i] - (int16_t)Border[i - 1];
            if (diff <= 0 && diff > -2
                && Border[i] > 4
                && Border[i - 1] > 4
                && Border[i] < (uint8_t)(IMG_W / 2)
                && Border[i - 1] < (uint8_t)(IMG_W / 2))
            {
                StraightPoint++;
            }
            else if (My_Abs(diff) > 5)
            {
                StraightPoint = 0;
            }

            if (StraightPoint >= STRAIGHT_LINE_CNT)
                return 1;
        }
    }
    return 0;
}

/* ============================================================
 * Cross_Fill — 十字补线 (拐点检测 + 直线拟合填充缺失边界)
 * ============================================================ */
static void Cross_Fill(uint8_t *bin)
{
    uint16_t i;
    uint16_t Break_Num_L_UP, Break_Num_R_UP;
    uint16_t Break_Num_L_DOWN, Break_Num_R_DOWN;
    uint16_t start, end;
    float slope_l_rate, intercept_l;
    int16_t val;

    Break_Num_L_UP = 0;
    Break_Num_R_UP = 0;
    Break_Num_L_DOWN = 0;
    Break_Num_R_DOWN = 0;
    slope_l_rate = 0.0f;
    intercept_l = 0.0f;

    Image_Flag_Cross_Fill = 0;

    // 只有四方都丢线时才检测十字
    if (Lose_Line() != 1) return;

    // 找左上拐点: 连续3点变化≤5, 断点变化≥7
    for (i = 3; i < (uint16_t)CROSS_SEARCH_UP; i++)
    {
        if ((uint16_t)My_Abs((int)L_Border[i] - (int)L_Border[i - 1]) <= 5
            && (uint16_t)My_Abs((int)L_Border[i - 1] - (int)L_Border[i - 2]) <= 5
            && (uint16_t)My_Abs((int)L_Border[i - 2] - (int)L_Border[i - 3]) <= 5
            && (int16_t)L_Border[i] - (int16_t)L_Border[i + 2] >= 7)
        {
            Break_Num_L_UP = i;
            break;
        }
    }

    // 找左下拐点
    for (i = (uint16_t)(IMG_H - 5); i > (uint16_t)CROSS_SEARCH_DOWN; i--)
    {
        if ((uint16_t)My_Abs((int)L_Border[i] - (int)L_Border[i + 1]) <= 5
            && (uint16_t)My_Abs((int)L_Border[i + 1] - (int)L_Border[i + 2]) <= 5
            && (uint16_t)My_Abs((int)L_Border[i + 2] - (int)L_Border[i + 3]) <= 5
            && (int16_t)L_Border[i] - (int16_t)L_Border[i - 2] >= 7)
        {
            Break_Num_L_DOWN = i;
            break;
        }
    }

    // 找右上拐点
    for (i = 3; i < (uint16_t)CROSS_SEARCH_UP; i++)
    {
        if ((uint16_t)My_Abs((int)R_Border[i] - (int)R_Border[i - 1]) <= 5
            && (uint16_t)My_Abs((int)R_Border[i - 1] - (int)R_Border[i - 2]) <= 5
            && (uint16_t)My_Abs((int)R_Border[i - 2] - (int)R_Border[i - 3]) <= 5
            && (int16_t)R_Border[i + 2] - (int16_t)R_Border[i] >= 7)
        {
            Break_Num_R_UP = i;
            break;
        }
    }

    // 找右下拐点
    for (i = (uint16_t)(IMG_H - 5); i > (uint16_t)CROSS_SEARCH_DOWN; i--)
    {
        if ((uint16_t)My_Abs((int)R_Border[i] - (int)R_Border[i + 1]) <= 5
            && (uint16_t)My_Abs((int)R_Border[i + 1] - (int)R_Border[i + 2]) <= 5
            && (uint16_t)My_Abs((int)R_Border[i + 2] - (int)R_Border[i + 3]) <= 5
            && (int16_t)R_Border[i - 2] - (int16_t)R_Border[i] >= 7)
        {
            Break_Num_R_DOWN = i;
            break;
        }
    }

    // 修正无效拐点对
    if ((int16_t)Break_Num_R_DOWN - (int16_t)Break_Num_R_UP < 0
        && Break_Num_R_DOWN && Break_Num_R_UP)
        Break_Num_R_DOWN = 0;
    if ((int16_t)Break_Num_L_DOWN - (int16_t)Break_Num_L_UP < 0
        && Break_Num_L_DOWN && Break_Num_L_UP)
        Break_Num_L_DOWN = 0;
    if ((int16_t)Break_Num_R_UP - (int16_t)Break_Num_R_DOWN > 0
        && Break_Num_R_DOWN && Break_Num_R_UP)
        Break_Num_R_UP = 0;
    if ((int16_t)Break_Num_L_UP - (int16_t)Break_Num_L_DOWN > 0
        && Break_Num_L_DOWN && Break_Num_L_UP)
        Break_Num_L_UP = 0;

    // Case 1: 四拐点都找到 (1111)
    if (Break_Num_L_DOWN && Break_Num_L_UP
        && Break_Num_R_DOWN && Break_Num_R_UP)
    {
        Image_Flag_Cross_Fill = 1;

        Get_K_b((uint8_t)L_Border[Break_Num_L_DOWN], (uint8_t)Break_Num_L_DOWN,
                (uint8_t)L_Border[Break_Num_L_UP],   (uint8_t)Break_Num_L_UP,
                &slope_l_rate, &intercept_l);
        for (i = Break_Num_L_DOWN; i > Break_Num_L_UP; i--)
        {
            val = (int16_t)(((float)i - intercept_l) / slope_l_rate);
            L_Border[i] = (uint8_t)Limit_a_b(val, BORDER_MIN, (int)BORDER_MAX);
        }

        Get_K_b((uint8_t)R_Border[Break_Num_R_DOWN], (uint8_t)Break_Num_R_DOWN,
                (uint8_t)R_Border[Break_Num_R_UP],   (uint8_t)Break_Num_R_UP,
                &slope_l_rate, &intercept_l);
        for (i = Break_Num_R_DOWN; i > Break_Num_R_UP; i--)
        {
            val = (int16_t)(((float)i - intercept_l) / slope_l_rate);
            R_Border[i] = (uint8_t)Limit_a_b(val, BORDER_MIN, (int)BORDER_MAX);
        }
    }
    // Case 2: 左斜十字 — 左有两个拐点, 右只有上拐点 (1101)
    else if (Break_Num_L_DOWN && Break_Num_L_UP
             && !Break_Num_R_DOWN && Break_Num_R_UP)
    {
        Image_Flag_Cross_Fill = 1;

        Get_K_b((uint8_t)L_Border[Break_Num_L_UP], (uint8_t)Break_Num_L_UP,
                (uint8_t)L_Border[Break_Num_L_DOWN], (uint8_t)Break_Num_L_DOWN,
                &slope_l_rate, &intercept_l);
        for (i = Break_Num_L_DOWN; i > Break_Num_L_UP; i--)
        {
            val = (int16_t)(((float)i - intercept_l) / slope_l_rate);
            L_Border[i] = (uint8_t)Limit_a_b(val, BORDER_MIN, (int)BORDER_MAX);
        }

        start = Break_Num_R_UP - 15;
        start = (uint16_t)Limit_a_b((int16_t)start, 5, (int)IMG_H - 5);
        end = Break_Num_R_UP;
        Get_K_b((uint8_t)R_Border[start], (uint8_t)start,
                (uint8_t)R_Border[end],   (uint8_t)end,
                &slope_l_rate, &intercept_l);
        for (i = Break_Num_R_UP; i < (uint16_t)(IMG_H - 2); i++)
        {
            val = (int16_t)(((float)i - intercept_l) / slope_l_rate);
            R_Border[i] = (uint8_t)Limit_a_b(val, BORDER_MIN, (int)BORDER_MAX);
        }
    }
    // Case 3: 右斜十字 — 右有两个拐点, 左只有上拐点 (0111)
    else if (!Break_Num_L_DOWN && Break_Num_L_UP
             && Break_Num_R_UP && Break_Num_R_DOWN)
    {
        Image_Flag_Cross_Fill = 1;

        start = Break_Num_L_UP - 15;
        start = (uint16_t)Limit_a_b((int16_t)start, 5, (int)IMG_H - 5);
        end = Break_Num_L_UP;
        Get_K_b((uint8_t)L_Border[start], (uint8_t)start,
                (uint8_t)L_Border[end],   (uint8_t)end,
                &slope_l_rate, &intercept_l);
        for (i = Break_Num_L_UP; i < (uint16_t)(IMG_H - 2); i++)
        {
            val = (int16_t)(((float)i - intercept_l) / slope_l_rate);
            L_Border[i] = (uint8_t)Limit_a_b(val, BORDER_MIN, (int)BORDER_MAX);
        }

        Get_K_b((uint8_t)R_Border[Break_Num_R_UP], (uint8_t)Break_Num_R_UP,
                (uint8_t)R_Border[Break_Num_R_DOWN], (uint8_t)Break_Num_R_DOWN,
                &slope_l_rate, &intercept_l);
        for (i = Break_Num_R_DOWN; i > Break_Num_R_UP; i--)
        {
            val = (int16_t)(((float)i - intercept_l) / slope_l_rate);
            R_Border[i] = (uint8_t)Limit_a_b(val, BORDER_MIN, (int)BORDER_MAX);
        }
    }
    // Case 4: 只有上拐点, 且底部有赛道 (0101)
    else if (Break_Num_L_UP && Break_Num_R_UP
             && !Break_Num_L_DOWN && !Break_Num_R_DOWN
             && bin[15 * IMG_W + (IMG_W - 10)]
             && bin[(IMG_H - 10) * IMG_W + (IMG_W - 10)])
    {
        Image_Flag_Cross_Fill = 2;

        start = Break_Num_L_UP - 15;
        start = (uint16_t)Limit_a_b((int16_t)start, 5, (int)IMG_H - 5);
        end = Break_Num_L_UP;
        end = (uint16_t)Limit_a_b((int16_t)end, 5, (int)IMG_H - 5);
        Get_K_b((uint8_t)L_Border[start], (uint8_t)start,
                (uint8_t)L_Border[end],   (uint8_t)end,
                &slope_l_rate, &intercept_l);
        for (i = Break_Num_L_UP; i < (uint16_t)(IMG_H - 2); i++)
        {
            val = (int16_t)(((float)i - intercept_l) / slope_l_rate);
            L_Border[i] = (uint8_t)Limit_a_b(val, BORDER_MIN, (int)BORDER_MAX);
        }

        start = Break_Num_R_UP - 15;
        start = (uint16_t)Limit_a_b((int16_t)start, 5, (int)IMG_H - 5);
        end = Break_Num_R_UP;
        end = (uint16_t)Limit_a_b((int16_t)end, 5, (int)IMG_H - 5);
        Get_K_b((uint8_t)R_Border[start], (uint8_t)start,
                (uint8_t)R_Border[end],   (uint8_t)end,
                &slope_l_rate, &intercept_l);
        for (i = Break_Num_R_UP; i < (uint16_t)(IMG_H - 2); i++)
        {
            val = (int16_t)(((float)i - intercept_l) / slope_l_rate);
            R_Border[i] = (uint8_t)Limit_a_b(val, BORDER_MIN, (int)BORDER_MAX);
        }
    }
    else
    {
        Image_Flag_Cross_Fill = 0;
    }
}

/* ============================================================
 * vision_track_process — 主处理入口 (二值化→滤波→追踪→补线→中线→偏差)
 * ============================================================ */
void vision_track_process(uint8_t *gray, uint8_t *bin,
                          vision_track_result_t *res)
{
    uint8_t thr;
    int16_t mid_val;
    float err_f;
    int16_t tgt_cx, tgt_cy, tgt_rm, tgt_dx, tgt_dy, tgt_rr;
    uint16_t tgt_x0, tgt_x1, tgt_y0, tgt_y1, tgt_yy, tgt_xx;

    // 1. 二值化 (Turn_To_Bin: Otsu*1.075, bright→255=track)
    Turn_To_Bin(gray, bin, &thr);
    res->threshold = thr;
    res->track_is_dark = 0;  // 亮色赛道

    // 2. 形态学滤波 (Image_Filter: 8邻域和阈值)
    Image_Filter(bin);

    // 3. 画黑边框 (Image_Draw_Rectan)
    Image_Draw_Rectan(bin);

    // 3.5 靶子掩除: 将上一帧检测到的靶子区域填充为白色(赛道), 防止环壁干扰边界追踪
    if (g_target_detected)
    {
        tgt_cx = (int16_t)g_target_center_x;
        tgt_cy = (int16_t)g_target_y_mid;
        tgt_rm = (int16_t)g_target_radius + 8;
        if (tgt_rm < 12) tgt_rm = 12;
        tgt_x0 = (uint16_t)(tgt_cx - tgt_rm);
        if (tgt_x0 < 0) tgt_x0 = 0;
        tgt_x1 = (uint16_t)(tgt_cx + tgt_rm);
        if (tgt_x1 >= IMG_W) tgt_x1 = IMG_W - 1;
        tgt_y0 = (uint16_t)(tgt_cy - tgt_rm);
        if (tgt_y0 < 0) tgt_y0 = 0;
        tgt_y1 = (uint16_t)(tgt_cy + tgt_rm);
        if (tgt_y1 >= IMG_H) tgt_y1 = IMG_H - 1;
        tgt_rr = tgt_rm * tgt_rm;
        for (tgt_yy = tgt_y0; tgt_yy <= tgt_y1; tgt_yy++)
        {
            tgt_dy = (int16_t)tgt_yy - tgt_cy;
            for (tgt_xx = tgt_x0; tgt_xx <= tgt_x1; tgt_xx++)
            {
                tgt_dx = (int16_t)tgt_xx - tgt_cx;
                if (tgt_dx * tgt_dx + tgt_dy * tgt_dy <= tgt_rr)
                    bin[tgt_yy * IMG_W + tgt_xx] = 255;
            }
        }
    }

    // 4. 初始化边界追踪状态
    Data_Stastics_L = 0;
    Data_Stastics_R = 0;

    // 5. 找种子点 + 双边追踪
    if (Get_Start_Point(bin, (uint8_t)(IMG_H - 2)))
    {
        Search_L_R((uint16_t)USE_NUM, bin,
                   &Data_Stastics_L, &Data_Stastics_R,
                   Start_Point_L[0], Start_Point_L[1],
                   Start_Point_R[0], Start_Point_R[1],
                   &Hightest);

        // 6. 点集→逐行边界数组 (Opt2: 合并)
        Get_Borders(Data_Stastics_L, Data_Stastics_R);

        // 7. 十字补线 (Cross_Fill)
        Cross_Fill(bin);
    }
    else
    {
        // 没找到种子点 — 初始化边界为默认值 (Opt2: 复用 Get_Borders)
        Get_Borders(0, 0);
        Hightest = 0;
    }

    // 8. 中线 = 道路中心估计
    // 参考 Front_Car: 稀疏点集, 不强制每行填值. 丢线行不猜, 直接用最近双边有效行.
    {
        int16_t lane_w, half_w;
        int16_t ln, rn;
        uint16_t near_y;

        /* Opt2: 重置 Image_Erro 缓存 */
        g_erro_lo = 0;
        g_erro_mid = 0;
        g_erro_hi = 0;

        // 道宽 — 双边可见时实测, 否则沿用上一帧 (防止测量失败用默认 65)
        lane_w = 65;
        near_y = (uint16_t)(IMG_H - 18);
        ln = (int16_t)L_Border[near_y];
        rn = (int16_t)R_Border[near_y];
        if (ln > (int16_t)BORDER_MIN && rn < (int16_t)BORDER_MAX)
        {
            lane_w = rn - ln + 1;
            if (lane_w >= 25 && lane_w <= 160)
                g_last_lane_w = (uint16_t)lane_w; /* 记录有效道宽 */
        }
        else if (g_last_lane_w > 0)
        {
            lane_w = (int16_t)g_last_lane_w; /* 双边测量失败 → 沿用上一帧 */
        }
        else
        {
            /* 全图无双边: 用可见边+图像中心估算道宽 */
            if (ln > (int16_t)BORDER_MIN)
                lane_w = 2 * ((int16_t)(IMG_W / 2) - ln);
            else if (rn < (int16_t)BORDER_MAX)
                lane_w = 2 * (rn - (int16_t)(IMG_W / 2));
        }
        if (lane_w < 25) lane_w = 65;
        if (lane_w > 160) lane_w = 160;
        half_w = lane_w / 2;
        g_half_lane_w = (int8_t)half_w;
    }

    // 9. Image_Erro = 加权平均 (原 row 69-71, 适配 103-106) — Opt2: 用缓存值 (第 11 步填)
    err_f = (float)g_erro_lo * 0.375f
          + (float)g_erro_mid * 0.5f
          + (float)g_erro_hi * 0.1f;

    mid_val = (int16_t)err_f;
    if (mid_val < 0)   mid_val = 0;
    if (mid_val > (int16_t)(IMG_W - 1)) mid_val = (int16_t)(IMG_W - 1);

    // 10. 帧间平滑
    if (g_last_center_x >= 0)
    {
        mid_val = (int16_t)(((int32_t)mid_val + (int32_t)g_last_center_x) / 2);
    }
    g_last_center_x = mid_val;
    res->center_x = mid_val;
    res->error_x  = (int16_t)(mid_val - (int16_t)(IMG_W / 2));

    // 11. 翻转二值图 + 填充输出结果 (合并遍历, 用于 trail.c 和 VOFA 显示)
    {
        uint16_t y;
        int16_t l, r;

        res->feature = VISION_FEATURE_NORMAL;
        res->valid_rows = 0;

        for (y = 0; y < IMG_H; y++)
        {
            uint16_t x;
            uint16_t row_off;
            row_off = y * IMG_W;
            for (x = 0; x < IMG_W; x++)
            {
                bin[row_off + x] = (bin[row_off + x] == WHITE_PIXEL) ? 0 : 255;
            }

            l = (int16_t)L_Border[y];
            r = (int16_t)R_Border[y];

            // 边界合理性检查
            if (l >= 0 && r >= (int16_t)l && l < (int16_t)IMG_W && r < (int16_t)IMG_W)
            {
                res->left[y]  = l;
                res->right[y] = r;

                /* 中线: 双边可见→均值, 单边丢线→可见边±半道宽 */
                {
                    int16_t mid_val;
                    uint8_t lok, rok;

                    lok = (l > 2) ? 1 : 0;
                    rok = (r < (int16_t)(IMG_W - 4)) ? 1 : 0;

                    if (!lok && !rok)
                    {
                        mid_val = (int16_t)(IMG_W / 2);
                    }
                    else if (l <= 5 && r >= (int16_t)(IMG_W - 5))
                    {
                        mid_val = (int16_t)(IMG_W / 2);
                    }
                    else if (lok && rok)
                    {
                        mid_val = (l + r) / 2;
                    }
                    else if (lok && !rok)
                    {
                        mid_val = l + (int16_t)g_half_lane_w;
                    }
                    else
                    {
                        mid_val = r - (int16_t)g_half_lane_w;
                    }

                    if (mid_val < 0) mid_val = 0;
                    if (mid_val > (int16_t)(IMG_W - 1)) mid_val = (int16_t)(IMG_W - 1);

                    /* Opt2: 缓存 Image_Erro 加权行 (无论是否在信任区) */
                    if (y == ERRO_ROW_LO) g_erro_lo = (uint8_t)mid_val;
                    else if (y == ERRO_ROW_MID) g_erro_mid = (uint8_t)mid_val;
                    else if (y == ERRO_ROW_HI) g_erro_hi = (uint8_t)mid_val;

                    /* 顶部和底部中线不采信: 上留 8 行, 下留 8 行, 上位机也不画 */
                    if (y < ((uint16_t)Hightest + MID_TRUST_TOP_MARGIN) ||
                        y >= (uint16_t)(IMG_H - MID_TRUST_BOT_MARGIN))
                    {
                        res->mid[y] = -1;
                    }
                    else
                    {
                        res->mid[y] = mid_val;
                    }
                }
                res->valid_rows++;
            }
            else
            {
                res->left[y]  = -1;
                res->right[y] = -1;
                res->mid[y]   = -1;
            }
        }

        // 特征分类 (简化版: 只用 Cross_Fill 结果)
        if (Image_Flag_Cross_Fill)
            res->feature = VISION_FEATURE_CROSS;
        else if (res->valid_rows < (uint8_t)(IMG_H / 4))
            res->feature = VISION_FEATURE_LOST;
        else
            res->feature = VISION_FEATURE_NORMAL;

        // 补充 trail.c 需要的字段
        res->visible_high = Hightest;
        {
            uint16_t bw;
            int16_t l_bot, r_bot;
            l_bot = (int16_t)L_Border[(uint16_t)(IMG_H - 5)];
            r_bot = (int16_t)R_Border[(uint16_t)(IMG_H - 5)];
            bw = (uint16_t)(r_bot - l_bot);
            if (bw > 0 && bw < (uint16_t)IMG_W)
                res->lane_width = (int16_t)bw;
            else
                res->lane_width = (int16_t)(IMG_W / 2);  // 默认半幅宽
        }
    }
}

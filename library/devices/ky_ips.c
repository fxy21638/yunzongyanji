/*********************************************************************************
 * 项目名称：[STC32G144K246开源库] 开源组件库
 * 版权所有：[2025] [北京科宇通博科技有限公司]
 *
 * 许可协议：采用 GNU GPL v3.0 开源许可
 * 您可依据协议进行二次开发、传播，但须保留原始版权信息
 * 协议详情参见：https://www.gnu.org/licenses/gpl-3.0.html
 *
 * 免责声明：本组件库仅提供技术参考，使用方需自行验证适用性
 *
 * 协议文件：GPL v3.0 完整文本位于根目录下
 *
 * === 文件信息 ===
 * 文件名：[ky_ips.c]
 * 开发单位：北京科宇通博科技有限公司
 * 适用环境：[Keil C251 / STC32G系列单片机]
 * 官方渠道：
 *   - 代码仓库：[https://gitee.com/beijing-keyu---jiangxi/KEYU_AI8052U_OpenLibrary]
 *   - 淘宝店铺：https://kyznc.taobao.com/
 *   - 技术支持：QQ群 974530818
 *
 * === 修订记录 ===
 * 日期       |  开发者  | 变更说明
 * -----------|----------|----------------------
 * 2025.12.22 |   xiao   | V2.0
 *********************************************************************************/
#include "ky_ips.h"
#include "stc32g144k246.h"
#include "ky_delay.h"
#include "ky_font.h"
#include "ky_utils.h"

static IPS_Type_t g_ips_current_type = IPS_TYPE_114;
static Color_t g_ips_pen_color = COLOR_BLACK;
static Color_t g_ips_background_color = COLOR_WHITE;
static IPS_Direction_t g_ips_display_direction = IPS_DIR_LANDSCAPE_180;
static uint16_t g_ips_max_width;
static uint16_t g_ips_max_height;
static uint16_t g_ips_native_width;
static uint16_t g_ips_native_height;

/*********************************************************************************
 *  @brief     通过SPI发送一个8位数据
 *  @param     dat     要发送的字节
 *********************************************************************************/
static void ips_write_data_8bit(uint8_t dat)
{
    IPS_SET_CS(0);
    spi_dma_send_byte(IPS_SPI_INDEX, dat);
    IPS_SET_CS(1);
}

/*********************************************************************************
 *  @brief     向屏幕发送一个命令
 *  @param     command     要发送的命令字节
 *********************************************************************************/
static void ips_write_command(uint8_t command)
{
    IPS_SET_DC(0);
    ips_write_data_8bit(command);
    IPS_SET_DC(1);
}

/*********************************************************************************
 *  @brief     通过SPI发送一个16位数据
 *  @param     dat     要发送的16位数据
 *********************************************************************************/
static void ips_write_data_16bit(uint16_t dat)
{
    uint8_t xdata buf[2];
    buf[0] = (uint8_t)(dat >> 8);
    buf[1] = (uint8_t)dat;
    IPS_SET_CS(0);
    spi_dma_send_8bit_array(IPS_SPI_INDEX, buf, 2);
    IPS_SET_CS(1);
}

/*********************************************************************************
 *  @brief     设置屏幕上将要进行绘图操作的窗口区域
 *  @param     x1      窗口左上角X坐标
 *  @param     y1      窗口左上角Y坐标
 *  @param     x2      窗口右下角X坐标
 *  @param     y2      窗口右下角Y坐标
 *********************************************************************************/
static void ips_set_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    int offset_x = 0, offset_y = 0;

    if (x1 >= g_ips_max_width)
        x1 = g_ips_max_width - 1;
    if (x2 >= g_ips_max_width)
        x2 = g_ips_max_width - 1;
    if (y1 >= g_ips_max_height)
        y1 = g_ips_max_height - 1;
    if (y2 >= g_ips_max_height)
        y2 = g_ips_max_height - 1;

    if (x1 > x2)
    {
        uint16_t t = x1;
        x1 = x2;
        x2 = t;
    }
    if (y1 > y2)
    {
        uint16_t t = y1;
        y1 = y2;
        y2 = t;
    }

    switch (g_ips_display_direction)
    {
    case IPS_DIR_PORTRAIT:
        if (g_ips_current_type == IPS_TYPE_114)
        {
            offset_x = 52;
            offset_y = 40;
        }
        break;
    case IPS_DIR_PORTRAIT_180:
        if (g_ips_current_type == IPS_TYPE_114)
        {
            offset_x = 53;
            offset_y = 40;
        }
        break;
    case IPS_DIR_LANDSCAPE:
        if (g_ips_current_type == IPS_TYPE_114)
        {
            offset_x = 40;
            offset_y = 53;
        }
        break;
    case IPS_DIR_LANDSCAPE_180:
        if (g_ips_current_type == IPS_TYPE_114)
        {
            offset_x = 40;
            offset_y = 52;
        }
        break;
    }

    ips_write_command(0x2A);
    ips_write_data_16bit(x1 + offset_x);
    ips_write_data_16bit(x2 + offset_x);
    ips_write_command(0x2B);
    ips_write_data_16bit(y1 + offset_y);
    ips_write_data_16bit(y2 + offset_y);
    ips_write_command(0x2C);
}

/*********************************************************************************
 *  @brief     在指定坐标绘制一个像素点
 *  @param     x       点的X坐标
 *  @param     y       点的Y坐标
 *  @param     color   点的16位RGB565颜色
 *********************************************************************************/
void ips_draw_point(uint16_t x, uint16_t y, Color_t color)
{
    if (x >= g_ips_max_width || y >= g_ips_max_height)
        return;
    ips_set_address(x, y, x, y);
    ips_write_data_16bit(color);
}

/*********************************************************************************
 *  @brief     使用Bresenham算法在两点之间绘制一条直线
 *  @param     x1      起始点的X坐标
 *  @param     y1      起始点的Y坐标
 *  @param     x2      结束点的X坐标
 *  @param     y2      结束点的Y坐标
 *  @param     color   线的16位RGB565颜色
 *********************************************************************************/
void ips_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color_t color)
{
    int16_t dx = (x2 > x1) ? (x2 - x1) : (x1 - x2);
    int16_t dy = (y2 > y1) ? (y2 - y1) : (y1 - y2);
    int8_t sx = (x1 < x2) ? 1 : -1;
    int8_t sy = (y1 < y2) ? 1 : -1;
    int16_t err = (dx > dy ? dx : -dy) / 2;
    int16_t e2;

    for (;;)
    {
        ips_draw_point(x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
}

/*********************************************************************************
 *  @brief     填充矩形区域
 *  @param     x1      左上角X坐标
 *  @param     y1      左上角Y坐标
 *  @param     x2      右下角X坐标
 *  @param     y2      右下角Y坐标
 *  @param     color   填充颜色
 *  @param     enable  0-实心矩形, >0-空心矩形(边框厚度)
 *********************************************************************************/
void ips_fill_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color_t color, uint8_t enable)
{
    uint32_t i, total_points;
    uint16_t thickness;

    if (x1 > x2)
    {
        uint16_t t = x1;
        x1 = x2;
        x2 = t;
    }
    if (y1 > y2)
    {
        uint16_t t = y1;
        y1 = y2;
        y2 = t;
    }

    if (x1 >= g_ips_max_width || y1 >= g_ips_max_height)
        return;
    if (x2 >= g_ips_max_width)
        x2 = g_ips_max_width - 1;
    if (y2 >= g_ips_max_height)
        y2 = g_ips_max_height - 1;

    // enable=0时实心填充，enable>0时绘制空心矩形（边框厚度为enable）
    if (enable == 0)
    {
        // 实心填充
        ips_set_address(x1, y1, x2, y2);
        total_points = (uint32_t)(x2 - x1 + 1) * (y2 - y1 + 1);
        for (i = 0; i < total_points; i++)
        {
            ips_write_data_16bit(color);
        }
        return;
    }

    // 空心矩形（绘制边框）
    thickness = enable;

    // 如果矩形太小，直接填充
    if ((x2 - x1 + 1) <= 2 * thickness || (y2 - y1 + 1) <= 2 * thickness)
    {
        ips_set_address(x1, y1, x2, y2);
        total_points = (uint32_t)(x2 - x1 + 1) * (y2 - y1 + 1);
        for (i = 0; i < total_points; i++)
        {
            ips_write_data_16bit(color);
        }
        return;
    }

    // 绘制上边框
    ips_set_address(x1, y1, x2, y1 + thickness - 1);
    total_points = (uint32_t)(x2 - x1 + 1) * thickness;
    for (i = 0; i < total_points; i++)
    {
        ips_write_data_16bit(color);
    }

    // 绘制下边框
    ips_set_address(x1, y2 - thickness + 1, x2, y2);
    total_points = (uint32_t)(x2 - x1 + 1) * thickness;
    for (i = 0; i < total_points; i++)
    {
        ips_write_data_16bit(color);
    }

    // 绘制左边框
    ips_set_address(x1, y1 + thickness, x1 + thickness - 1, y2 - thickness);
    total_points = (uint32_t)(y2 - y1 - 2 * thickness + 1) * thickness;
    for (i = 0; i < total_points; i++)
    {
        ips_write_data_16bit(color);
    }

    // 绘制右边框
    ips_set_address(x2 - thickness + 1, y1 + thickness, x2, y2 - thickness);
    total_points = (uint32_t)(y2 - y1 - 2 * thickness + 1) * thickness;
    for (i = 0; i < total_points; i++)
    {
        ips_write_data_16bit(color);
    }
}

/*********************************************************************************
 *  @brief     显示一个字符
 *  @param     x           X坐标
 *  @param     y           Y坐标
 *  @param     character   要显示的字符
 *********************************************************************************/
void ips_show_char(uint16_t x, uint16_t y, const char character)
{
    uint8_t i, j;
    uint8_t temp;

    if (x + 7 >= g_ips_max_width || y + 15 >= g_ips_max_height)
        return;
    if (character < ' ' || character > '~')
        return;

    ips_set_address(x, y, x + 7, y + 15);
    for (i = 0; i < 16; i++)
    {
        temp = ascii_font_8x16[character - ' '][i];
        for (j = 0; j < 8; j++)
        {
            if (temp & 0x01)
                ips_write_data_16bit(g_ips_pen_color);
            else
                ips_write_data_16bit(g_ips_background_color);
            temp >>= 1;
        }
    }
}

/*********************************************************************************
 *  @brief     在指定位置显示一个字符串
 *  @param     x       字符串左上角的X坐标
 *  @param     y       字符串左上角的Y坐标
 *  @param     str     要显示的以'\0'结尾的字符串
 *********************************************************************************/
void ips_show_string(uint16_t x, uint16_t y, const char *str)
{
    while (*str != '\0')
    {
        if (x > g_ips_max_width - 8)
        {
            x = 0;
            y += 16;
        }
        if (y > g_ips_max_height - 16)
            break;
        ips_show_char(x, y, *str);
        x += 8;
        str++;
    }
}

/*********************************************************************************
 *  @brief     显示一个带符号整数
 *  @param     x           显示位置的X坐标
 *  @param     y           显示位置的Y坐标
 *  @param     num         要显示的整数
 *  @param     min_len     显示的最小位数
 *********************************************************************************/
void ips_show_int(uint16_t x, uint16_t y, int32_t num, uint8_t min_len)
{
    char buf[12];
    uint8_t len;

    len = utils_int2str(num, buf);
    while (len < min_len)
    {
        ips_show_char(x, y, ' ');
        x += 8;
        min_len--;
    }
    ips_show_string(x, y, buf);
}

/*********************************************************************************
 *  @brief     显示一个无符号长整数
 *  @param     x           显示位置的X坐标
 *  @param     y           显示位置的Y坐标
 *  @param     num         要显示的无符号整数
 *  @param     min_len     显示的最小位数
 *********************************************************************************/
void ips_show_uint(uint16_t x, uint16_t y, uint32_t num, uint8_t min_len)
{
    char buf[12];
    uint8_t len;

    len = utils_uint2str(num, buf);
    while (len < min_len)
    {
        ips_show_char(x, y, ' ');
        x += 8;
        min_len--;
    }
    ips_show_string(x, y, buf);
}

/*********************************************************************************
 *  @brief     显示一个浮点数
 *  @param     x           显示位置的X坐标
 *  @param     y           显示位置的Y坐标
 *  @param     num         要显示的浮点数
 *  @param     min_len     整数部分最小位数
 *  @param     frac        小数点后显示的位数
 *********************************************************************************/
void ips_show_float(uint16_t x, uint16_t y, float num, uint8_t min_len, uint8_t frac)
{
    char buf[16];
    uint8_t len;

    len = utils_float2str(num, buf, frac);
    while (len < min_len)
    {
        ips_show_char(x, y, ' ');
        x += 8;
        min_len--;
    }
    ips_show_string(x, y, buf);
}

/*********************************************************************************
 *  @brief     显示二维数组灰度图像
 *  @param     x           显示位置的X坐标
 *  @param     y           显示位置的Y坐标
 *  @param     image       图像数据数组
 *  @param     img_w       图像实际宽度
 *  @param     img_h       图像实际高度
 *  @param     dis_w       显示宽度
 *  @param     dis_h       显示高度
 *  @param     threshold   二值化阈值
 *********************************************************************************/
void ips_show_gray_image(uint16_t x, uint16_t y, const uint8_t *image, uint16_t img_w, uint16_t img_h, uint16_t dis_w, uint16_t dis_h, uint8_t threshold)
{
    uint16_t row, col;
    uint8_t gray;
    uint16_t line_buffer[320]; 
    const uint8_t *src_row_ptr;
    uint32_t row_step, col_step;
    uint32_t src_row_acc = 0, src_col_acc = 0;

    if (x + dis_w > g_ips_max_width || y + dis_h > g_ips_max_height) return;

    ips_set_address(x, y, x + dis_w - 1, y + dis_h - 1);
    IPS_SET_CS(0);

    if (img_w == dis_w && img_h == dis_h)
    {
        src_row_ptr = image;
        
        for (row = 0; row < dis_h; row++)
        {
            if (threshold == 0) 
            {
                for (col = 0; col < dis_w; col++)
                {
                    gray = *src_row_ptr++; 
                    // RGB565转换: R5 G6 B5
                    line_buffer[col] = ((gray & 0xF8) << 8) | ((gray & 0xFC) << 3) | (gray >> 3);
                }
            }
            else // 二值化显示
            {
                for (col = 0; col < dis_w; col++)
                {
                    gray = *src_row_ptr++;
                    line_buffer[col] = (gray < threshold) ? COLOR_BLACK : COLOR_WHITE;
                }
            }
            // 发送一行
            spi_dma_send_16bit_array(IPS_SPI_INDEX, line_buffer, dis_w);
        }
    }
    else // 
    {
        row_step = ((uint32_t)img_h << 16) / dis_h;
        col_step = ((uint32_t)img_w << 16) / dis_w;
        
        src_row_acc = 0;

        for (row = 0; row < dis_h; row++)
        {
            // 计算当前行在原图中的位置
            src_row_ptr = image + ((src_row_acc >> 16) * img_w);
            src_row_acc += row_step;
            
            src_col_acc = 0;

            if (threshold == 0)
            {
                for (col = 0; col < dis_w; col++)
                {
                    // 取像素
                    gray = src_row_ptr[src_col_acc >> 16];
                    src_col_acc += col_step;
                    // 转换
                    line_buffer[col] = ((gray & 0xF8) << 8) | ((gray & 0xFC) << 3) | (gray >> 3);
                }
            }
            else
            {
                for (col = 0; col < dis_w; col++)
                {
                    gray = src_row_ptr[src_col_acc >> 16];
                    src_col_acc += col_step;
                    line_buffer[col] = (gray < threshold) ? COLOR_BLACK : COLOR_WHITE;
                }
            }
            spi_dma_send_16bit_array(IPS_SPI_INDEX, line_buffer, dis_w);
        }
    }

    IPS_SET_CS(1);
}

/*********************************************************************************
 *  @brief     清屏
 *  @param     background_color    清屏使用的背景色
 *********************************************************************************/
void ips_clear(Color_t background_color)
{
    uint16_t row;
    uint16_t line_buffer[320];

    // 预填充一行缓冲区
    for (row = 0; row < g_ips_max_width; row++)
    {
        line_buffer[row] = background_color;
    }

    // 设置全屏地址窗口
    ips_set_address(0, 0, g_ips_max_width - 1, g_ips_max_height - 1);

    // 使用DMA全屏刷新
    IPS_SET_CS(0);
    for (row = 0; row < g_ips_max_height; row++)
    {
        spi_dma_send_16bit_array(IPS_SPI_INDEX, line_buffer, g_ips_max_width);
    }
    IPS_SET_CS(1);
}

/*********************************************************************************
 *  @brief     设置显示方向
 *  @param     direction   显示方向枚举值
 *********************************************************************************/
void ips_set_direction(IPS_Direction_t direction)
{
    g_ips_display_direction = direction;
    if (direction == IPS_DIR_LANDSCAPE || direction == IPS_DIR_LANDSCAPE_180)
    {
        g_ips_max_width = g_ips_native_height;
        g_ips_max_height = g_ips_native_width;
    }
    else
    {
        g_ips_max_width = g_ips_native_width;
        g_ips_max_height = g_ips_native_height;
    }
}

/*********************************************************************************
 *  @brief     设置画笔和背景颜色
 *  @param     pen_color           画笔颜色
 *  @param     background_color    背景颜色
 *********************************************************************************/
void ips_set_color(Color_t pen_color, Color_t background_color)
{
    g_ips_pen_color = pen_color;
    g_ips_background_color = background_color;
}

/*********************************************************************************
 *  @brief     初始化IPS屏幕
 *  @param     type    屏幕类型
 *********************************************************************************/
void ips_init(IPS_Type_t type)
{
    spi_dma_init(IPS_SPI_INDEX, IPS_SPI_MODE, IPS_SPI_SPEED, IPS_SPI_SCLK, IPS_SPI_MOSI, IPS_SPI_MISO);
    gpio_init(IPS_GPIO_DC, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(IPS_GPIO_BLK, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(IPS_GPIO_RST, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(IPS_GPIO_CS, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_set_speed(IPS_GPIO_CS, GPIO_SPEED_FAST);

    gpio_write_pin(IPS_GPIO_RST, GPIO_LOW);
    delay_ms(100);
    gpio_write_pin(IPS_GPIO_RST, GPIO_HIGH);
    delay_ms(100);

    g_ips_current_type = type;

    switch (g_ips_current_type)
    {
    case IPS_TYPE_114:
        g_ips_native_width = 135;
        g_ips_native_height = 240;
        break;
    case IPS_TYPE_200:
        g_ips_native_width = 240;
        g_ips_native_height = 320;
        break;
    }

    ips_set_direction(g_ips_display_direction);
    ips_set_color(g_ips_pen_color, g_ips_background_color);

    gpio_write_pin(IPS_GPIO_RST, GPIO_LOW);
    delay_ms(100);
    gpio_write_pin(IPS_GPIO_RST, GPIO_HIGH);
    delay_ms(100);

    ips_write_command(0x11);
    delay_ms(120);

    ips_write_command(0x36);
    delay_ms(120);
    if (g_ips_display_direction == IPS_DIR_PORTRAIT)
        ips_write_data_8bit(0x00);
    else if (g_ips_display_direction == IPS_DIR_PORTRAIT_180)
        ips_write_data_8bit(0xC0);
    else if (g_ips_display_direction == IPS_DIR_LANDSCAPE)
        ips_write_data_8bit(0x70);
    else
        ips_write_data_8bit(0xA0);

    ips_write_command(0x3A);
    ips_write_data_8bit(0x05);
    ips_write_command(0xB2);
    ips_write_data_8bit(0x0C);
    ips_write_data_8bit(0x0C);
    ips_write_data_8bit(0x00);
    ips_write_data_8bit(0x33);
    ips_write_data_8bit(0x33);
    ips_write_command(0xB7);
    ips_write_data_8bit(0x35);
    ips_write_command(0xBB);
    ips_write_data_8bit(0x19);
    ips_write_command(0xC0);
    ips_write_data_8bit(0x2C);
    ips_write_command(0xC2);
    ips_write_data_8bit(0x01);
    ips_write_command(0xC3);
    ips_write_data_8bit(0x12);
    ips_write_command(0xC4);
    ips_write_data_8bit(0x20);
    ips_write_command(0xC6);
    ips_write_data_8bit(0x0F);
    ips_write_command(0xD0);
    ips_write_data_8bit(0xA4);
    ips_write_data_8bit(0xA1);
    ips_write_command(0xE0);
    ips_write_data_8bit(0xD0);
    ips_write_data_8bit(0x04);
    ips_write_data_8bit(0x0D);
    ips_write_data_8bit(0x11);
    ips_write_data_8bit(0x13);
    ips_write_data_8bit(0x2B);
    ips_write_data_8bit(0x3F);
    ips_write_data_8bit(0x54);
    ips_write_data_8bit(0x4C);
    ips_write_data_8bit(0x18);
    ips_write_data_8bit(0x0D);
    ips_write_data_8bit(0x0B);
    ips_write_data_8bit(0x1F);
    ips_write_data_8bit(0x23);
    ips_write_command(0xE1);
    ips_write_data_8bit(0xD0);
    ips_write_data_8bit(0x04);
    ips_write_data_8bit(0x0C);
    ips_write_data_8bit(0x11);
    ips_write_data_8bit(0x13);
    ips_write_data_8bit(0x2C);
    ips_write_data_8bit(0x3F);
    ips_write_data_8bit(0x44);
    ips_write_data_8bit(0x51);
    ips_write_data_8bit(0x2F);
    ips_write_data_8bit(0x1F);
    ips_write_data_8bit(0x1F);
    ips_write_data_8bit(0x20);
    ips_write_data_8bit(0x23);
    ips_write_command(0x21);
    delay_ms(120);
    ips_write_command(0x29);

    ips_clear(g_ips_background_color);
    gpio_write_pin(IPS_GPIO_BLK, GPIO_HIGH);
}

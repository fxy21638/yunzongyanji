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
 * 文件名：[ky_ips.h]
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
#ifndef __KY_IPS_H__
#define __KY_IPS_H__

#include "ky_gpio.h"
#include "ky_spi.h"
#include "ky_typedef.h"

// IPS屏幕硬件连接定义
#define IPS_SPI_INDEX SPI_3                     // SPI3
#define IPS_SPI_SPEED 50000000                  // 50MHz
#define IPS_SPI_MODE SPI_MODE_0                 // SPI_MODE_0
#define IPS_SPI_SCLK SPI3_SCLK_P73              // SCLK
#define IPS_SPI_MOSI SPI3_MOSI_P71              // MOSI
#define IPS_SPI_MISO SPI3_MISO_P72              // MISO 
#define IPS_GPIO_RST GPIO_PA0                   // RST
#define IPS_GPIO_DC GPIO_P70                    // DC
#define IPS_GPIO_CS GPIO_P72                    // CS
#define IPS_GPIO_BLK GPIO_PA1                   // BLK

#define IPS_PIN_DC P70                          // DC
#define IPS_PIN_CS P72                          // CS

#define IPS_SET_DC(x)                           (IPS_PIN_DC = (x))
#define IPS_SET_CS(x)                           (IPS_PIN_CS = (x))


typedef enum
{
    IPS_DIR_PORTRAIT,      // 竖屏
    IPS_DIR_PORTRAIT_180,  // 竖屏180度
    IPS_DIR_LANDSCAPE,     // 横屏
    IPS_DIR_LANDSCAPE_180, // 横屏180度
} IPS_Direction_t;

typedef enum
{
    IPS_TYPE_114, // 1.14寸
    IPS_TYPE_200, // 2.0寸
} IPS_Type_t;

typedef uint16_t Color_t;

#define COLOR_WHITE 0xFFFF   // 白色
#define COLOR_BLACK 0x0000   // 黑色
#define COLOR_RED 0xF800     // 红色
#define COLOR_GREEN 0x07E0   // 绿色
#define COLOR_BLUE 0x001F    // 蓝色
#define COLOR_YELLOW 0xFFE0  // 黄色
#define COLOR_CYAN 0x07FF    // 青色
#define COLOR_MAGENTA 0xF81F // 紫色

// 屏幕初始化
void ips_init(IPS_Type_t type);
// 设置旋转方向
void ips_set_direction(IPS_Direction_t direction);
// 设置颜色
void ips_set_color(Color_t pen_color, Color_t background_color);

// 清屏
void ips_clear(Color_t background_color);
// 绘制点
void ips_draw_point(uint16_t x, uint16_t y, Color_t color);
// 绘制线
void ips_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color_t color);
// 填充矩形 (enable=0实心, enable>0空心边框厚度)
void ips_fill_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color_t color, uint8_t enable);

// 显示字符
void ips_show_char(uint16_t x, uint16_t y, const char character);
// 显示浮点数
void ips_show_float(uint16_t x, uint16_t y, float num, uint8_t min_len, uint8_t frac);
// 显示整数
void ips_show_int(uint16_t x, uint16_t y, int32_t num, uint8_t min_len);
// 显示无符号整数
void ips_show_uint(uint16_t x, uint16_t y, uint32_t num, uint8_t min_len);
// 显示字符串
void ips_show_string(uint16_t x, uint16_t y, const char *str);
// 显示灰度图像
void ips_show_gray_image(uint16_t x, uint16_t y, const uint8_t *image, uint16_t img_w, uint16_t img_h, uint16_t dis_w, uint16_t dis_h, uint8_t threshold);

#endif

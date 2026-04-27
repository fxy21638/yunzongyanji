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
 * 文件名：[ky_gpio.h]
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
#ifndef __KY_GPIO_H__
#define __KY_GPIO_H__

#include "ky_typedef.h"

typedef enum {
    GPIO_P00 = 0x00, GPIO_P01, GPIO_P02, GPIO_P03, GPIO_P04, GPIO_P05, GPIO_P06, GPIO_P07,
    GPIO_P10 = 0x10, GPIO_P11, GPIO_P12, GPIO_P13, GPIO_P14, GPIO_P15, GPIO_P16, GPIO_P17,
    GPIO_P20 = 0x20, GPIO_P21, GPIO_P22, GPIO_P23, GPIO_P24, GPIO_P25, GPIO_P26, GPIO_P27,
    GPIO_P30 = 0x30, GPIO_P31, GPIO_P32, GPIO_P33, GPIO_P34, GPIO_P35, GPIO_P36, GPIO_P37,
    GPIO_P40 = 0x40, GPIO_P41, GPIO_P42, GPIO_P43, GPIO_P44, GPIO_P45, GPIO_P46, GPIO_P47,
    GPIO_P50 = 0x50, GPIO_P51, GPIO_P52, GPIO_P53, GPIO_P54, GPIO_P55, GPIO_P56, GPIO_P57,
    GPIO_P60 = 0x60, GPIO_P61, GPIO_P62, GPIO_P63, GPIO_P64, GPIO_P65, GPIO_P66, GPIO_P67,
    GPIO_P70 = 0x70, GPIO_P71, GPIO_P72, GPIO_P73, GPIO_P74, GPIO_P75, GPIO_P76, GPIO_P77,
    GPIO_P80 = 0x80, GPIO_P81, GPIO_P82, GPIO_P83, GPIO_P84, GPIO_P85, GPIO_P86, GPIO_P87,
    GPIO_P90 = 0x90, GPIO_P91, GPIO_P92, GPIO_P93, GPIO_P94, GPIO_P95, GPIO_P96, GPIO_P97,
    GPIO_PA0 = 0xA0, GPIO_PA1, GPIO_PA2, GPIO_PA3, GPIO_PA4, GPIO_PA5, GPIO_PA6, GPIO_PA7,
    GPIO_PB0 = 0xB0, GPIO_PB1, GPIO_PB2, GPIO_PB3, GPIO_PB4, GPIO_PB5, GPIO_PB6, GPIO_PB7,
  GPIO_PFF = 0xFF
} GPIO_Pin_t;

typedef enum {
    GPIO_MODE_IN_FLOATING = 0,      // 浮空输入
    GPIO_MODE_IN_PU,                // 上拉输入
    GPIO_MODE_IN_PD,                // 下拉输入
    GPIO_MODE_OUT_PP,               // 推挽输出
    GPIO_MODE_OUT_OD,               // 开漏输出
    GPIO_MODE_OUT_OD_PU             // 开漏输出上拉
} GPIO_Mode_t;

typedef enum { 
    GPIO_LOW = 0,                   // 低电平
    GPIO_HIGH = 1                   // 高电平
} GPIO_Level_t;

typedef enum { 
    GPIO_SPEED_LOW = 0,             // 低速
    GPIO_SPEED_FAST = 1             // 高速
} GPIO_Speed_t;

typedef enum { 
    GPIO_DRIVE_NORMAL = 0,          // 正常驱动
    GPIO_DRIVE_ENHANCED = 1         // 增强驱动
} GPIO_Drive_t;

typedef enum {
    GPIO_DIGITAL_DISABLE = 0,       // 禁用数字功能
    GPIO_DIGITAL_ENABLE = 1         // 启用数字功能
} GPIO_Digital_t;

typedef enum {
    GPIO_INT_DISABLE = 0,           // 禁用中断         
    GPIO_INT_RISING = 1,            // 上升沿触发
    GPIO_INT_FALLING = 2,           // 下降沿触发
    GPIO_INT_RISING_FALLING = 3     // 上升沿和下降沿都触发
} GPIO_Int_t;

typedef void (*GPIO_IntCallback_t)(void);

// 初始化GPIO
void gpio_init       (GPIO_Pin_t pin, GPIO_Mode_t mode, GPIO_Level_t level);
// 设置GPIO驱动能力
void gpio_set_drive  (GPIO_Pin_t pin, GPIO_Drive_t drive);
// 设置GPIO速度
void gpio_set_speed  (GPIO_Pin_t pin, GPIO_Speed_t speed);
// 设置GPIO数字功能
void gpio_set_digital(GPIO_Pin_t pin, GPIO_Digital_t digital);
// 设置GPIO电平
void gpio_write_pin  (GPIO_Pin_t pin, GPIO_Level_t level);
// 读取GPIO电平
uint8_t gpio_read_pin(GPIO_Pin_t pin);
// 切换GPIO电平
void gpio_toggle_pin (GPIO_Pin_t pin);

// 初始化GPIO中断
void gpio_int_init          (GPIO_Pin_t pin, GPIO_Int_t int_type);
// 设置GPIO中断回调函数
void gpio_int_set_callback  (GPIO_Pin_t pin, GPIO_IntCallback_t callback);
// 中断服务程序
void gpio_isr_handler       (uint8_t port);

#endif

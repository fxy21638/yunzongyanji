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
 * 文件名：[ky_encoder.h]
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
#ifndef __KY_ENCODER_H__
#define __KY_ENCODER_H__

#include "ky_gpio.h"
#include "ky_typedef.h"

typedef enum { 
	ENCODER_PWMA = 0, ENCODER_PWMB = 1, ENCODER_PWMC = 2, 
	ENCODER_PWMD = 3, ENCODER_PWME = 4, ENCODER_PWMF = 5, 
	ENCODER_MAX 
} Encoder_Index_t;

typedef enum {
    // PWMA
    ENCA_A_P10 = (0 << 13 | 0 << 8 | GPIO_P10),
    ENCA_A_P20 = (0 << 13 | 1 << 8 | GPIO_P20),
    ENCA_A_P60 = (0 << 13 | 2 << 8 | GPIO_P60),

    // PWMB
    ENCB_A_P20 = (1 << 13 | 0 << 8 | GPIO_P20),
    ENCB_A_P17 = (1 << 13 | 1 << 8 | GPIO_P17),
    ENCB_A_P00 = (1 << 13 | 2 << 8 | GPIO_P00),
    ENCB_A_P74 = (1 << 13 | 3 << 8 | GPIO_P74),

    // PWMC
    ENCC_A_P60 = (2 << 13 | 0 << 8 | GPIO_P60),
    ENCC_A_P80 = (2 << 13 | 1 << 8 | GPIO_P80),
    ENCC_A_P40 = (2 << 13 | 2 << 8 | GPIO_P40),
    ENCC_A_PB0 = (2 << 13 | 3 << 8 | GPIO_PB0),

    // PWMD
    ENCD_A_P24 = (3 << 13 | 0 << 8 | GPIO_P24),
    ENCD_A_P81 = (3 << 13 | 1 << 8 | GPIO_P81),
    ENCD_A_P50 = (3 << 13 | 2 << 8 | GPIO_P50),
    ENCD_A_PB4 = (3 << 13 | 3 << 8 | GPIO_PB4),

    // PWME
    ENCE_A_P70 = (4 << 13 | 0 << 8 | GPIO_P70),
    ENCE_A_P90 = (4 << 13 | 1 << 8 | GPIO_P90),
    ENCE_A_PA0 = (4 << 13 | 2 << 8 | GPIO_PA0),

    // PWMF
    ENCF_A_P70 = (5 << 13 | 0 << 8 | GPIO_P70),
    ENCF_A_PA1 = (5 << 13 | 1 << 8 | GPIO_PA1),
    ENCF_A_P90 = (5 << 13 | 2 << 8 | GPIO_P90),
} Encoder_A_Pin_t;

typedef enum {
    // PWMA
    ENCA_B_P12 = (0 << 13 | 0 << 8 | GPIO_P12),
    ENCA_B_P22 = (0 << 13 | 1 << 8 | GPIO_P22),
    ENCA_B_P62 = (0 << 13 | 2 << 8 | GPIO_P62),

        // PWMB
    ENCB_B_P21 = (1 << 13 | 0 << 8 | GPIO_P21),
    ENCB_B_P54 = (1 << 13 | 1 << 8 | GPIO_P54),
    ENCB_B_P01 = (1 << 13 | 2 << 8 | GPIO_P01),
    ENCB_B_P75 = (1 << 13 | 3 << 8 | GPIO_P75),

    // PWMC
    ENCC_B_P62 = (2 << 13 | 0 << 8 | GPIO_P62),
    ENCC_B_P82 = (2 << 13 | 1 << 8 | GPIO_P82),
    ENCC_B_P42 = (2 << 13 | 2 << 8 | GPIO_P42),
    ENCC_B_PB2 = (2 << 13 | 3 << 8 | GPIO_PB2),

    // PWMD
    ENCD_B_P25 = (3 << 13 | 0 << 8 | GPIO_P25),
    ENCD_B_P83 = (3 << 13 | 1 << 8 | GPIO_P83),
    ENCD_B_P51 = (3 << 13 | 2 << 8 | GPIO_P51),
    ENCD_B_PB5 = (3 << 13 | 3 << 8 | GPIO_PB5),

    // PWME
    ENCE_B_P72 = (4 << 13 | 0 << 8 | GPIO_P72),
    ENCE_B_P92 = (4 << 13 | 1 << 8 | GPIO_P92),
    ENCE_B_PA2 = (4 << 13 | 2 << 8 | GPIO_PA2),

    // PWMF
    ENCF_B_P71 = (5 << 13 | 0 << 8 | GPIO_P71),
    ENCF_B_PA3 = (5 << 13 | 1 << 8 | GPIO_PA3),
    ENCF_B_P91 = (5 << 13 | 2 << 8 | GPIO_P91),
} Encoder_B_Pin_t;

// 初始化正交编码器
void    encoder_init_quad   (Encoder_Index_t index, Encoder_A_Pin_t a_pin, Encoder_B_Pin_t b_pin);
// 初始化编码器带方向
void    encoder_init_dir    (Encoder_Index_t index, Encoder_A_Pin_t pulse_pin, Encoder_B_Pin_t dir_pin);
// 读取编码器值
int16_t encoder_read        (Encoder_Index_t index);
// 清零编码器值
void    encoder_clear       (Encoder_Index_t index);

#endif

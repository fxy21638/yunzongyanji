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
 * 文件名：[ky_pwm.h]
 * 开发单位：北京科宇通博科技有限公司
 * 适用环境：[Keil C251 / STC32G系列单片机]
 * 官方渠道：
 *   -
 * 代码仓库：[https://gitee.com/beijing-keyu---jiangxi/KEYU_AI8052U_OpenLibrary]
 *   - 淘宝店铺：https://kyznc.taobao.com/
 *   - 技术支持：QQ群 974530818
 *
 * === 修订记录 ===
 * 日期       |  开发者  | 变更说明
 * -----------|----------|----------------------
 * 2025.12.22 |   xiao   | V2.0
 *********************************************************************************/
#ifndef __KY_PWM_H__
#define __KY_PWM_H__

#include "ky_gpio.h"
#include "ky_typedef.h"

#define PWM_MAX_DUTY 10000

typedef enum
{
    // PWMA 通道1
    PWMA_CH1P_P10 = (0 << 13 | 0 << 9 | 0 << 7 | GPIO_P10),
    PWMA_CH1N_P11 = (0 << 13 | 1 << 9 | 0 << 7 | GPIO_P11),
    PWMA_CH1P_P20 = (0 << 13 | 0 << 9 | 1 << 7 | GPIO_P20),
    PWMA_CH1N_P21 = (0 << 13 | 1 << 9 | 1 << 7 | GPIO_P21),
    PWMA_CH1P_P60 = (0 << 13 | 0 << 9 | 2 << 7 | GPIO_P60),
    PWMA_CH1N_P61 = (0 << 13 | 1 << 9 | 2 << 7 | GPIO_P61),
    // PWMA 通道2
    PWMA_CH2P_P12 = (0 << 13 | 2 << 9 | 0 << 7 | GPIO_P12),
    PWMA_CH2N_P13 = (0 << 13 | 3 << 9 | 0 << 7 | GPIO_P13),
    PWMA_CH2P_P22 = (0 << 13 | 2 << 9 | 1 << 7 | GPIO_P22),
    PWMA_CH2N_P23 = (0 << 13 | 3 << 9 | 1 << 7 | GPIO_P23),
    PWMA_CH2P_P62 = (0 << 13 | 2 << 9 | 2 << 7 | GPIO_P62),
    PWMA_CH2N_P63 = (0 << 13 | 3 << 9 | 2 << 7 | GPIO_P63),
    // PWMA 通道3
    PWMA_CH3P_P14 = (0 << 13 | 4 << 9 | 0 << 7 | GPIO_P14),
    PWMA_CH3N_P15 = (0 << 13 | 5 << 9 | 0 << 7 | GPIO_P15),
    PWMA_CH3P_P24 = (0 << 13 | 4 << 9 | 1 << 7 | GPIO_P24),
    PWMA_CH3N_P25 = (0 << 13 | 5 << 9 | 1 << 7 | GPIO_P25),
    PWMA_CH3P_P64 = (0 << 13 | 4 << 9 | 2 << 7 | GPIO_P64),
    PWMA_CH3N_P65 = (0 << 13 | 5 << 9 | 2 << 7 | GPIO_P65),
    // PWMA 通道4
    PWMA_CH4P_P16 = (0 << 13 | 6 << 9 | 0 << 7 | GPIO_P16),
    PWMA_CH4N_P17 = (0 << 13 | 7 << 9 | 0 << 7 | GPIO_P17),
    PWMA_CH4P_P26 = (0 << 13 | 6 << 9 | 1 << 7 | GPIO_P26),
    PWMA_CH4N_P27 = (0 << 13 | 7 << 9 | 1 << 7 | GPIO_P27),
    PWMA_CH4P_P66 = (0 << 13 | 6 << 9 | 2 << 7 | GPIO_P66),
    PWMA_CH4N_P67 = (0 << 13 | 7 << 9 | 2 << 7 | GPIO_P67),
    PWMA_CH4P_P34 = (0 << 13 | 6 << 9 | 3 << 7 | GPIO_P34),
    PWMA_CH4N_P33 = (0 << 13 | 7 << 9 | 3 << 7 | GPIO_P33),

    // PWMB 通道5
    PWMB_CH5_P20 = (1 << 13 | 0 << 9 | 0 << 7 | GPIO_P20),
    PWMB_CH5_P17 = (1 << 13 | 0 << 9 | 1 << 7 | GPIO_P17),
    PWMB_CH5_P00 = (1 << 13 | 0 << 9 | 2 << 7 | GPIO_P00),
    PWMB_CH5_P74 = (1 << 13 | 0 << 9 | 3 << 7 | GPIO_P74),
    // PWMB 通道6
    PWMB_CH6_P21 = (1 << 13 | 1 << 9 | 0 << 7 | GPIO_P21),
    PWMB_CH6_P54 = (1 << 13 | 1 << 9 | 1 << 7 | GPIO_P54),
    PWMB_CH6_P01 = (1 << 13 | 1 << 9 | 2 << 7 | GPIO_P01),
    PWMB_CH6_P75 = (1 << 13 | 1 << 9 | 3 << 7 | GPIO_P75),
    // PWMB 通道7
    PWMB_CH7_P22 = (1 << 13 | 2 << 9 | 0 << 7 | GPIO_P22),
    PWMB_CH7_P33 = (1 << 13 | 2 << 9 | 1 << 7 | GPIO_P33),
    PWMB_CH7_P02 = (1 << 13 | 2 << 9 | 2 << 7 | GPIO_P02),
    PWMB_CH7_P76 = (1 << 13 | 2 << 9 | 3 << 7 | GPIO_P76),
    // PWMB 通道8
    PWMB_CH8_P23 = (1 << 13 | 3 << 9 | 0 << 7 | GPIO_P23),
    PWMB_CH8_P34 = (1 << 13 | 3 << 9 | 1 << 7 | GPIO_P34),
    PWMB_CH8_P03 = (1 << 13 | 3 << 9 | 2 << 7 | GPIO_P03),
    PWMB_CH8_P77 = (1 << 13 | 3 << 9 | 3 << 7 | GPIO_P77),

    // PWMC 通道1
    PWMC_CH1P_P60 = (2 << 13 | 0 << 9 | 0 << 7 | GPIO_P60),
    PWMC_CH1N_P61 = (2 << 13 | 1 << 9 | 0 << 7 | GPIO_P61),
    PWMC_CH1P_P80 = (2 << 13 | 0 << 9 | 1 << 7 | GPIO_P80),
    PWMC_CH1N_P81 = (2 << 13 | 1 << 9 | 1 << 7 | GPIO_P81),
    PWMC_CH1P_P40 = (2 << 13 | 0 << 9 | 2 << 7 | GPIO_P40),
    PWMC_CH1N_P41 = (2 << 13 | 1 << 9 | 2 << 7 | GPIO_P41),
    PWMC_CH1P_PB0 = (2 << 13 | 0 << 9 | 3 << 7 | GPIO_PB0),
    PWMC_CH1N_PB1 = (2 << 13 | 1 << 9 | 3 << 7 | GPIO_PB1),
    // PWMC 通道2
    PWMC_CH2P_P62 = (2 << 13 | 2 << 9 | 0 << 7 | GPIO_P62),
    PWMC_CH2N_P63 = (2 << 13 | 3 << 9 | 0 << 7 | GPIO_P63),
    PWMC_CH2P_P82 = (2 << 13 | 2 << 9 | 1 << 7 | GPIO_P82),
    PWMC_CH2N_P83 = (2 << 13 | 3 << 9 | 1 << 7 | GPIO_P83),
    PWMC_CH2P_P42 = (2 << 13 | 2 << 9 | 2 << 7 | GPIO_P42),
    PWMC_CH2N_P43 = (2 << 13 | 3 << 9 | 2 << 7 | GPIO_P43),
    PWMC_CH2P_PB2 = (2 << 13 | 2 << 9 | 3 << 7 | GPIO_PB2),
    PWMC_CH2N_PB3 = (2 << 13 | 3 << 9 | 3 << 7 | GPIO_PB3),
    // PWMC 通道3
    PWMC_CH3P_P64 = (2 << 13 | 4 << 9 | 0 << 7 | GPIO_P64),
    PWMC_CH3N_P65 = (2 << 13 | 5 << 9 | 0 << 7 | GPIO_P65),
    PWMC_CH3P_P84 = (2 << 13 | 4 << 9 | 1 << 7 | GPIO_P84),
    PWMC_CH3N_P85 = (2 << 13 | 5 << 9 | 1 << 7 | GPIO_P85),
    PWMC_CH3P_P44 = (2 << 13 | 4 << 9 | 2 << 7 | GPIO_P44),
    PWMC_CH3N_P45 = (2 << 13 | 5 << 9 | 2 << 7 | GPIO_P45),
    PWMC_CH3P_PB4 = (2 << 13 | 4 << 9 | 3 << 7 | GPIO_PB4),
    PWMC_CH3N_PB5 = (2 << 13 | 5 << 9 | 3 << 7 | GPIO_PB5),
    // PWMC 通道4
    PWMC_CH4P_P66 = (2 << 13 | 6 << 9 | 0 << 7 | GPIO_P66),
    PWMC_CH4N_P67 = (2 << 13 | 7 << 9 | 0 << 7 | GPIO_P67),
    PWMC_CH4P_P86 = (2 << 13 | 6 << 9 | 1 << 7 | GPIO_P86),
    PWMC_CH4N_P87 = (2 << 13 | 7 << 9 | 1 << 7 | GPIO_P87),
    PWMC_CH4P_P46 = (2 << 13 | 6 << 9 | 2 << 7 | GPIO_P46),
    PWMC_CH4N_P47 = (2 << 13 | 7 << 9 | 2 << 7 | GPIO_P47),
    PWMC_CH4P_PB6 = (2 << 13 | 6 << 9 | 3 << 7 | GPIO_PB6),
    PWMC_CH4N_PB7 = (2 << 13 | 7 << 9 | 3 << 7 | GPIO_PB7),

    // PWMD 通道5
    PWMD_CH5_P24 = (3 << 13 | 0 << 9 | 0 << 7 | GPIO_P24),
    PWMD_CH5_P81 = (3 << 13 | 0 << 9 | 1 << 7 | GPIO_P81),
    PWMD_CH5_P50 = (3 << 13 | 0 << 9 | 2 << 7 | GPIO_P50),
    PWMD_CH5_PB4 = (3 << 13 | 0 << 9 | 3 << 7 | GPIO_PB4),
    // PWMD 通道6
    PWMD_CH6_P25 = (3 << 13 | 1 << 9 | 0 << 7 | GPIO_P25),
    PWMD_CH6_P83 = (3 << 13 | 1 << 9 | 1 << 7 | GPIO_P83),
    PWMD_CH6_P51 = (3 << 13 | 1 << 9 | 2 << 7 | GPIO_P51),
    PWMD_CH6_PB5 = (3 << 13 | 1 << 9 | 3 << 7 | GPIO_PB5),
    // PWMD 通道7
    PWMD_CH7_P26 = (3 << 13 | 2 << 9 | 0 << 7 | GPIO_P26),
    PWMD_CH7_P85 = (3 << 13 | 2 << 9 | 1 << 7 | GPIO_P85),
    PWMD_CH7_P52 = (3 << 13 | 2 << 9 | 2 << 7 | GPIO_P52),
    PWMD_CH7_PB6 = (3 << 13 | 2 << 9 | 3 << 7 | GPIO_PB6),
    // PWMD 通道8
    PWMD_CH8_P27 = (3 << 13 | 3 << 9 | 0 << 7 | GPIO_P27),
    PWMD_CH8_P87 = (3 << 13 | 3 << 9 | 1 << 7 | GPIO_P87),
    PWMD_CH8_P53 = (3 << 13 | 3 << 9 | 2 << 7 | GPIO_P53),
    PWMD_CH8_PB7 = (3 << 13 | 3 << 9 | 3 << 7 | GPIO_PB7),

    // PWME 通道1
    PWME_CH1P_P70 = (4 << 13 | 0 << 9 | 0 << 7 | GPIO_P70),
    PWME_CH1N_P71 = (4 << 13 | 1 << 9 | 0 << 7 | GPIO_P71),
    PWME_CH1P_P90 = (4 << 13 | 0 << 9 | 1 << 7 | GPIO_P90),
    PWME_CH1N_P91 = (4 << 13 | 1 << 9 | 1 << 7 | GPIO_P91),
    PWME_CH1P_PA0 = (4 << 13 | 0 << 9 | 2 << 7 | GPIO_PA0),
    PWME_CH1N_PA1 = (4 << 13 | 1 << 9 | 2 << 7 | GPIO_PA1),
    // PWME 通道2
    PWME_CH2P_P72 = (4 << 13 | 2 << 9 | 0 << 7 | GPIO_P72),
    PWME_CH2N_P73 = (4 << 13 | 3 << 9 | 0 << 7 | GPIO_P73),
    PWME_CH2P_P92 = (4 << 13 | 2 << 9 | 1 << 7 | GPIO_P92),
    PWME_CH2N_P93 = (4 << 13 | 3 << 9 | 1 << 7 | GPIO_P93),
    PWME_CH2P_PA2 = (4 << 13 | 2 << 9 | 2 << 7 | GPIO_PA2),
    PWME_CH2N_PA3 = (4 << 13 | 3 << 9 | 2 << 7 | GPIO_PA3),
    // PWME 通道3
    PWME_CH3P_P74 = (4 << 13 | 4 << 9 | 0 << 7 | GPIO_P74),
    PWME_CH3N_P75 = (4 << 13 | 5 << 9 | 0 << 7 | GPIO_P75),
    PWME_CH3P_P94 = (4 << 13 | 4 << 9 | 1 << 7 | GPIO_P94),
    PWME_CH3N_P95 = (4 << 13 | 5 << 9 | 1 << 7 | GPIO_P95),
    PWME_CH3P_PA4 = (4 << 13 | 4 << 9 | 2 << 7 | GPIO_PA4),
    PWME_CH3N_PA5 = (4 << 13 | 5 << 9 | 2 << 7 | GPIO_PA5),
    // PWME 通道4
    PWME_CH4P_P76 = (4 << 13 | 6 << 9 | 0 << 7 | GPIO_P76),
    PWME_CH4N_P77 = (4 << 13 | 7 << 9 | 0 << 7 | GPIO_P77),
    PWME_CH4P_P96 = (4 << 13 | 6 << 9 | 1 << 7 | GPIO_P96),
    PWME_CH4N_P97 = (4 << 13 | 7 << 9 | 1 << 7 | GPIO_P97),
    PWME_CH4P_PA6 = (4 << 13 | 6 << 9 | 2 << 7 | GPIO_PA6),
    PWME_CH4N_PA7 = (4 << 13 | 7 << 9 | 2 << 7 | GPIO_PA7),
    // PWME 通道5 (单端输出，使用 PWME_PS2 寄存器 EC5PS)
    PWME_CH5_P50 = (4 << 13 | 8 << 9 | 0 << 7 | GPIO_P50),
    PWME_CH5_P43 = (4 << 13 | 8 << 9 | 1 << 7 | GPIO_P43),
    PWME_CH5_PB4 = (4 << 13 | 8 << 9 | 2 << 7 | GPIO_PB4),
    PWME_CH5_P95 = (4 << 13 | 8 << 9 | 3 << 7 | GPIO_P95),
    // PWME 通道6 (单端输出，使用 PWME_PS2 寄存器 EC6PS)
    PWME_CH6_P51 = (4 << 13 | 9 << 9 | 0 << 7 | GPIO_P51),
    PWME_CH6_P44 = (4 << 13 | 9 << 9 | 1 << 7 | GPIO_P44),
    PWME_CH6_PB5 = (4 << 13 | 9 << 9 | 2 << 7 | GPIO_PB5),
    PWME_CH6_P97 = (4 << 13 | 9 << 9 | 3 << 7 | GPIO_P97),

    // PWMF 通道5
    PWMF_CH5_P70 = (5 << 13 | 0 << 9 | 0 << 7 | GPIO_P70),
    PWMF_CH5_PA1 = (5 << 13 | 0 << 9 | 1 << 7 | GPIO_PA1),
    PWMF_CH5_P90 = (5 << 13 | 0 << 9 | 2 << 7 | GPIO_P90),
    // PWMF 通道6
    PWMF_CH6_P71 = (5 << 13 | 1 << 9 | 0 << 7 | GPIO_P71),
    PWMF_CH6_PA3 = (5 << 13 | 1 << 9 | 1 << 7 | GPIO_PA3),
    PWMF_CH6_P91 = (5 << 13 | 1 << 9 | 2 << 7 | GPIO_P91),
    // PWMF 通道7
    PWMF_CH7_P72 = (5 << 13 | 2 << 9 | 0 << 7 | GPIO_P72),
    PWMF_CH7_PA5 = (5 << 13 | 2 << 9 | 1 << 7 | GPIO_PA5),
    PWMF_CH7_P92 = (5 << 13 | 2 << 9 | 2 << 7 | GPIO_P92),
    // PWMF 通道8
    PWMF_CH8_P73 = (5 << 13 | 3 << 9 | 0 << 7 | GPIO_P73),
    PWMF_CH8_PA7 = (5 << 13 | 3 << 9 | 1 << 7 | GPIO_PA7),
    PWMF_CH8_P93 = (5 << 13 | 3 << 9 | 2 << 7 | GPIO_P93),
} PWM_Channel_t;

// 初始化PWM
void pwm_init(PWM_Channel_t ch, uint32_t freq, uint16_t duty);
// 设置占空比
void pwm_set_duty(PWM_Channel_t ch, uint16_t duty);
// 设置频率
void pwm_set_freq(PWM_Channel_t ch, uint16_t freq);

#endif

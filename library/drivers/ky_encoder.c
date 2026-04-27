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
 * 文件名：[ky_encoder.c]
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
#include "ky_encoder.h"
#include "stc32g144k246.h"

static GPIO_Pin_t encoder_dir_pins[ENCODER_MAX] = {GPIO_PFF, GPIO_PFF, GPIO_PFF, GPIO_PFF, GPIO_PFF, GPIO_PFF};

/*********************************************************************************
 *  @brief     设置 PS 寄存器 (通道1/2 或 5/6)
 *  @param     group 组索引
 *  @param     ps_val PS值
 *  @return    无
 *********************************************************************************/
static void _encoder_set_ps(uint8_t group, uint8_t ps_val)
{
    uint8_t val = ps_val | (ps_val << 2);

    switch (group) {
    case 0: PWMA_PS = (PWMA_PS & 0xF0) | val; break;
    case 1: PWMB_PS = (PWMB_PS & 0xF0) | val; break;
    case 2: PWMC_PS = (PWMC_PS & 0xF0) | val; break;
    case 3: PWMD_PS = (PWMD_PS & 0xF0) | val; break;
    case 4: PWME_PS = (PWME_PS & 0xF0) | val; break;
    case 5: PWMF_PS = (PWMF_PS & 0xF0) | val; break;
    }
}

/*********************************************************************************
 *  @brief     配置基础寄存器
 *  @param     group 组索引
 *  @return    无
 *********************************************************************************/
static void _encoder_config_base(uint8_t group)
{
    switch (group) {
    case 0:
        PWMA_ARRH = 0xFF; PWMA_ARRL = 0xFF;
        PWMA_PSCRH = 0; PWMA_PSCRL = 1;
        PWMA_CCMR1 = 0x01; PWMA_CCMR2 = 0x01;
        PWMA_CCER1 = 0; PWMA_EGR = 0x01;
        break;
    case 1:
        PWMB_ARRH = 0xFF; PWMB_ARRL = 0xFF;
        PWMB_PSCRH = 0; PWMB_PSCRL = 1;
        PWMB_CCMR1 = 0x01; PWMB_CCMR2 = 0x01;
        PWMB_CCER1 = 0; PWMB_EGR = 0x01;
        break;
    case 2:
        PWMC_ARRH = 0xFF; PWMC_ARRL = 0xFF;
        PWMC_PSCRH = 0; PWMC_PSCRL = 1;
        PWMC_CCMR1 = 0x01; PWMC_CCMR2 = 0x01;
        PWMC_CCER1 = 0; PWMC_EGR = 0x01;
        break;
    case 3:
        PWMD_ARRH = 0xFF; PWMD_ARRL = 0xFF;
        PWMD_PSCRH = 0; PWMD_PSCRL = 1;
        PWMD_CCMR1 = 0x01; PWMD_CCMR2 = 0x01;
        PWMD_CCER1 = 0; PWMD_EGR = 0x01;
        break;
    case 4:
        PWME_ARRH = 0xFF; PWME_ARRL = 0xFF;
        PWME_PSCRH = 0; PWME_PSCRL = 1;
        PWME_CCMR1 = 0x01; PWME_CCMR2 = 0x01;
        PWME_CCER1 = 0; PWME_EGR = 0x01;
        break;
    case 5:
        PWMF_ARRH = 0xFF; PWMF_ARRL = 0xFF;
        PWMF_PSCRH = 0; PWMF_PSCRL = 1;
        PWMF_CCMR1 = 0x01; PWMF_CCMR2 = 0x01;
        PWMF_CCER1 = 0; PWMF_EGR = 0x01;
        break;
    }
}

/*********************************************************************************
 *  @brief     设置编码器模式并使能
 *  @param     group 组索引
 *  @param     mode 模式 (0x01=模式1, 0x02=模式2, 0x03=模式3(4倍频))
 *  @return    无
 *********************************************************************************/
static void _encoder_set_mode(uint8_t group, uint8_t mode)
{
    switch (group) {
    case 0: PWMA_SMCR = mode; PWMA_CCER1 |= 0x11; PWMA_CR1 |= 0x01; break;
    case 1: PWMB_SMCR = mode; PWMB_CCER1 |= 0x11; PWMB_CR1 |= 0x01; break;
    case 2: PWMC_SMCR = mode; PWMC_CCER1 |= 0x11; PWMC_CR1 |= 0x01; break;
    case 3: PWMD_SMCR = mode; PWMD_CCER1 |= 0x11; PWMD_CR1 |= 0x01; break;
    case 4: PWME_SMCR = mode; PWME_CCER1 |= 0x11; PWME_CR1 |= 0x01; break;
    case 5: PWMF_SMCR = mode; PWMF_CCER1 |= 0x11; PWMF_CR1 |= 0x01; break;
    }
}

/*********************************************************************************
 *  @brief     设置外部时钟模式1 (用于脉冲+方向)
 *  @param     group 组索引
 *  @return    无
 *********************************************************************************/
static void _encoder_set_ext_clock_mode(uint8_t group)
{
    uint8_t smcr_val = 0x57;

    switch (group) {
    case 0: PWMA_SMCR = smcr_val; PWMA_CR1 |= 0x01; break;
    case 1: PWMB_SMCR = smcr_val; PWMB_CR1 |= 0x01; break;
    case 2: PWMC_SMCR = smcr_val; PWMC_CR1 |= 0x01; break;
    case 3: PWMD_SMCR = smcr_val; PWMD_CR1 |= 0x01; break;
    case 4: PWME_SMCR = smcr_val; PWME_CR1 |= 0x01; break;
    case 5: PWMF_SMCR = smcr_val; PWMF_CR1 |= 0x01; break;
    }
}

/*********************************************************************************
 *  @brief     读取计数器
 *  @param     group 组索引
 *  @return    计数器值
 *********************************************************************************/
static uint16_t _encoder_read_counter(uint8_t group)
{
    uint8_t h = 0, l = 0;

    switch (group) {
    case 0: h = PWMA_CNTRH; l = PWMA_CNTRL; break;
    case 1: h = PWMB_CNTRH; l = PWMB_CNTRL; break;
    case 2: h = PWMC_CNTRH; l = PWMC_CNTRL; break;
    case 3: h = PWMD_CNTRH; l = PWMD_CNTRL; break;
    case 4: h = PWME_CNTRH; l = PWME_CNTRL; break;
    case 5: h = PWMF_CNTRH; l = PWMF_CNTRL; break;
    }
    return ((uint16_t)h << 8) | l;
}

/*********************************************************************************
 *  @brief     写入计数器
 *  @param     group 组索引
 *  @param     val 计数器值
 *  @return    无
 *********************************************************************************/
static void _encoder_write_counter(uint8_t group, uint16_t val)
{
    uint8_t h = val >> 8;
    uint8_t l = val & 0xFF;

    switch (group) {
    case 0: PWMA_CNTRH = h; PWMA_CNTRL = l; break;
    case 1: PWMB_CNTRH = h; PWMB_CNTRL = l; break;
    case 2: PWMC_CNTRH = h; PWMC_CNTRL = l; break;
    case 3: PWMD_CNTRH = h; PWMD_CNTRL = l; break;
    case 4: PWME_CNTRH = h; PWME_CNTRL = l; break;
    case 5: PWMF_CNTRH = h; PWMF_CNTRL = l; break;
    }
}

/*********************************************************************************
 *  @brief     正交编码器初始化 (4倍频, 双边沿计数)
 *  @param     index 编码器索引
 *  @param     a_pin A 相引脚
 *  @param     b_pin B 相引脚
 *  @return    无
 *********************************************************************************/
void encoder_init_quad(Encoder_Index_t index, Encoder_A_Pin_t a_pin, Encoder_B_Pin_t b_pin)
{
    uint8_t ps_val;
    GPIO_Pin_t gpio_a, gpio_b;

    // 参数检查：编码器索引有效性
    KY_ASSERT(index < ENCODER_MAX);
    // 参数检查：A相引脚组必须与索引匹配
    KY_ASSERT(((a_pin >> 13) & 0x07) == index);

    ps_val = (a_pin >> 8) & 0x07;
    gpio_a = (GPIO_Pin_t)(a_pin & 0xFF);
    gpio_b = (GPIO_Pin_t)(b_pin & 0xFF);

    gpio_init(gpio_a, GPIO_MODE_IN_PU, GPIO_HIGH);
    gpio_init(gpio_b, GPIO_MODE_IN_PU, GPIO_HIGH);

    _encoder_set_ps((uint8_t)index, ps_val);
    _encoder_config_base((uint8_t)index);
    _encoder_set_mode((uint8_t)index, 0x02);  // 编码器模式2

    encoder_dir_pins[index] = GPIO_PFF;
}

/*********************************************************************************
 *  @brief     脉冲+方向模式初始化
 *  @param     index 编码器索引
 *  @param     pulse_pin 脉冲引脚
 *  @param     dir_pin 方向引脚
 *  @return    无
 *********************************************************************************/
void encoder_init_dir(Encoder_Index_t index, Encoder_A_Pin_t pulse_pin, Encoder_B_Pin_t dir_pin)
{
    uint8_t ps_val;
    GPIO_Pin_t gpio_pulse, gpio_dir;

    // 参数检查：编码器索引有效性
    KY_ASSERT(index < ENCODER_MAX);
    // 参数检查：脉冲引脚组必须与索引匹配
    KY_ASSERT(((pulse_pin >> 13) & 0x07) == index);

    ps_val = (pulse_pin >> 8) & 0x07;
    gpio_pulse = (GPIO_Pin_t)(pulse_pin & 0xFF);
    gpio_dir = (GPIO_Pin_t)(dir_pin & 0xFF);

    gpio_init(gpio_pulse, GPIO_MODE_IN_PU, GPIO_HIGH);
    gpio_init(gpio_dir, GPIO_MODE_IN_PU, GPIO_HIGH);

    _encoder_set_ps((uint8_t)index, ps_val);
    _encoder_config_base((uint8_t)index);
    _encoder_set_ext_clock_mode((uint8_t)index);

    encoder_dir_pins[index] = gpio_dir;
}

/*********************************************************************************
 *  @brief     读取编码器计数值
 *  @param     index 编码器索引
 *  @return    带符号计数值
 *********************************************************************************/
int16_t encoder_read(Encoder_Index_t index)
{
    int16_t count;

    if (index >= ENCODER_MAX)
        return 0;

    count = (int16_t)_encoder_read_counter((uint8_t)index);

    if (encoder_dir_pins[index] == GPIO_PFF) {
        return count;
    } else {
        // 脉冲+方向模式
        if (gpio_read_pin(encoder_dir_pins[index]) == 0)
            return -count;
        return count;
    }
}

/*********************************************************************************
 *  @brief     清零编码器计数
 *  @param     index 编码器索引
 *  @return    无
 *********************************************************************************/
void encoder_clear(Encoder_Index_t index)
{
    if (index >= ENCODER_MAX)
        return;

    _encoder_write_counter((uint8_t)index, 0);
}

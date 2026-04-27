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
 * 文件名：[ky_adc.c]
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
#include "ky_adc.h"
#include "stc32g144k246.h"

static uint8_t adc_resolution[2] = {0, 0};

/*********************************************************************************
 *  @brief     ADC初始化
 *  @param     ch ADC通道
 *  @param     clock ADC时钟分频
 *  @param     resolution ADC分辨率
 *  @return    无
 *********************************************************************************/
void adc_init(ADC_Channel_t ch, ADC_Clock_t clock, ADC_Resolution_t resolution)
{
    uint8_t module = (ch >> 12) & 0x0F;
    uint8_t channel = (ch >> 8) & 0x0F;
    GPIO_Pin_t pin = (GPIO_Pin_t)(ch & 0xFF);

    // 参数检查：ADC 模块有效性 (1 或 2)
    KY_ASSERT(module == 1 || module == 2);

    gpio_init(pin, GPIO_MODE_IN_FLOATING, GPIO_LOW);
    gpio_set_digital(pin, GPIO_DIGITAL_DISABLE);

    if (module == 1) {
        ADC_CONTR &= 0xF0;
        ADC_CONTR |= (channel & 0x0F);
        ADCCFG = (clock & 0x0F);
        if (resolution == ADC_RES_12BIT)
            ADCCFG |= (1 << 5);
        adc_resolution[0] = (resolution == ADC_RES_12BIT) ? 0 : 4;
        ADC_CONTR |= (1 << 7);
    } else if (module == 2) {
        ADC2_CONTR &= 0xF0;
        ADC2_CONTR |= (channel & 0x0F);
        ADC2CFG = (clock & 0x0F);
        if (resolution == ADC_RES_12BIT)
            ADC2CFG |= (1 << 5);
        adc_resolution[1] = (resolution == ADC_RES_12BIT) ? 0 : 4;
        ADC2_CONTR |= (1 << 7);
    }
}

/*********************************************************************************
 *  @brief     ADC读取
 *  @param     ch ADC通道
 *  @return    ADC转换结果
 *********************************************************************************/
uint16_t adc_read(ADC_Channel_t ch)
{
    uint16_t adc_value = 0;
    uint8_t module = (ch >> 12) & 0x0F;
    uint8_t channel = (ch >> 8) & 0x0F;

    if (module == 1) {
        ADC_CONTR &= ~0x20;
        ADC_CONTR &= 0xF0;
        ADC_CONTR |= (channel & 0x0F);
        ADC_CONTR |= 0x40;
        while (!(ADC_CONTR & 0x20))
            ;
        adc_value = (uint16_t)(ADC_RES << 8);
        adc_value |= ADC_RESL;
        ADC_RES = 0;
        ADC_RESL = 0;
        adc_value >>= adc_resolution[0];
    } else if (module == 2) {
        ADC2_CONTR &= ~0x20;
        ADC2_CONTR &= 0xF0;
        ADC2_CONTR |= (channel & 0x0F);
        ADC2_CONTR |= 0x40;
        while (!(ADC2_CONTR & 0x20))
            ;
        adc_value = (uint16_t)(ADC2_RES << 8);
        adc_value |= ADC2_RESL;
        ADC2_RES = 0;
        ADC2_RESL = 0;
        adc_value >>= adc_resolution[1];
    }

    return adc_value;
}

/*********************************************************************************
 *  @brief     ADC滤波采样
 *  @param     ch ADC通道
 *  @param     count 采样次数
 *  @return    ADC滤波后的值
 *********************************************************************************/
uint16_t adc_read_filter(ADC_Channel_t ch, uint8_t count)
{
    uint8_t i;
    uint16_t val;
    uint16_t max_val = 0;
    uint16_t min_val = 0xFFFF;
    uint32_t sum = 0;

    if (count < 3)
        count = 3;

    for (i = 0; i < count; i++) {
        val = adc_read(ch);
        sum += val;
        if (val > max_val)
            max_val = val;
        if (val < min_val)
            min_val = val;
    }

    sum -= max_val;
    sum -= min_val;

    return (uint16_t)(sum / (count - 2));
}

/*********************************************************************************
 *  @brief     ADC DMA 初始化
 *  @param     module ADC模块 (1 或 2)
 *  @param     channel_mask 通道掩码
 *  @param     cv_count 每通道转换次数
 *  @param     interval 转换间隔
 *  @param     scan_count 循环扫描次数
 *  @param     buffer DMA 接收缓冲区地址
 *  @return    无
 *********************************************************************************/
void adc_dma_init(uint8_t module, uint16_t channel_mask, ADC_DMA_CvCount_t cv_count, uint16_t interval, uint16_t scan_count, uint8_t *buffer)
{
    uint16_t addr;
    uint16_t amt_val;

    // 参数检查：ADC 模块有效性 (1 或 2)
    KY_ASSERT(module == 1 || module == 2);

    addr = (uint16_t)buffer;
    amt_val = (scan_count == 0) ? 0 : (scan_count - 1);

    if (module == 1) {
        DMA_ADC_CFG = 0x00;
        DMA_ADC_RXAH = (uint8_t)(addr >> 8);
        DMA_ADC_RXAL = (uint8_t)(addr & 0xFF);
        DMA_ADC_AMTH = (uint8_t)(amt_val >> 8);
        DMA_ADC_AMT = (uint8_t)(amt_val & 0xFF);
        DMA_ADC_CFG2 = (uint8_t)cv_count;
        DMA_ADC_CHSW0 = (uint8_t)(channel_mask & 0xFF);
        DMA_ADC_CHSW1 = (uint8_t)(channel_mask >> 8);
        DMA_ADC_ITVH = (uint8_t)(interval >> 8);
        DMA_ADC_ITVL = (uint8_t)(interval & 0xFF);
        DMA_ADC_CR = 0x80;
    } else if (module == 2) {
        DMA_ADC2_CFG = 0x00;
        DMA_ADC2_RXAH = (uint8_t)(addr >> 8);
        DMA_ADC2_RXAL = (uint8_t)(addr & 0xFF);
        DMA_ADC2_AMTH = (uint8_t)(amt_val >> 8);
        DMA_ADC2_AMT = (uint8_t)(amt_val & 0xFF);
        DMA_ADC2_CFG2 = (uint8_t)cv_count;
        DMA_ADC2_CHSW0 = (uint8_t)(channel_mask & 0xFF);
        DMA_ADC2_CHSW1 = (uint8_t)(channel_mask >> 8);
        DMA_ADC2_ITVH = (uint8_t)(interval >> 8);
        DMA_ADC2_ITVL = (uint8_t)(interval & 0xFF);
        DMA_ADC2_CR = 0x80;
    }
}

/*********************************************************************************
 *  @brief     启动 ADC DMA 扫描
 *  @param     module ADC模块 (1 或 2)
 *  @return    无
 *********************************************************************************/
void adc_dma_start(uint8_t module)
{
    if (module == 1)
        DMA_ADC_CR = 0xC0;
    else if (module == 2)
        DMA_ADC2_CR = 0xC0;
}

/*********************************************************************************
 *  @brief     检查 DMA 是否完成
 *  @param     module ADC模块 (1 或 2)
 *  @return    1=完成, 0=未完成
 *********************************************************************************/
uint8_t adc_dma_is_done(uint8_t module)
{
    if (module == 1)
        return (DMA_ADC_STA & 0x01) ? 1 : 0;
    else if (module == 2)
        return (DMA_ADC2_STA & 0x01) ? 1 : 0;
    return 0;
}

/*********************************************************************************
 *  @brief     清除 DMA 完成标志
 *  @param     module ADC模块 (1 或 2)
 *  @return    无
 *********************************************************************************/
void adc_dma_clear_flag(uint8_t module)
{
    if (module == 1)
        DMA_ADC_STA &= ~0x01;
    else if (module == 2)
        DMA_ADC2_STA &= ~0x01;
}

/*********************************************************************************
 *  @brief     从 DMA 缓冲区获取通道平均值
 *  @param     buffer DMA 缓冲区首地址
 *  @param     channel_index 通道索引
 *  @param     cv_count 每通道转换次数
 *  @return    该通道的平均 ADC 值
 *********************************************************************************/
uint16_t adc_dma_get_result(uint8_t *buffer, uint8_t channel_index, uint16_t cv_count)
{
    uint16_t offset;
    uint16_t bytes_per_ch;
    uint8_t h, l;

    bytes_per_ch = (cv_count * 2) + 4;
    offset = (uint16_t)channel_index * bytes_per_ch + (cv_count * 2) + 2;

    h = buffer[offset];
    l = buffer[offset + 1];

    return ((uint16_t)h << 8) | l;
}

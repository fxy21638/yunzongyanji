/*********************************************************************************
 * 项目名称:[STC32G144K246开源库] 开源组件库
 * 版权所有:[2025] [北京科宇通博科技有限公司]
 *
 * 许可协议:采用 GNU GPL v3.0 开源许可
 * 您可依据协议进行二次开发、传播,但须保留原始版权信息
 * 协议详情参见:https://www.gnu.org/licenses/gpl-3.0.html
 *
 * 免责声明:本组件库仅提供技术参考,使用方需自行验证适用性
 *
 * 协议文件:GPL v3.0 完整文本位于根目录下
 *
 * === 文件信息 ===
 * 文件名:[ky_spi.c]
 * 开发单位:北京科宇通博科技有限公司
 * 适用环境:[Keil C251 / STC32G系列单片机]
 * 官方渠道:
 *   - 代码仓库:[https://gitee.com/beijing-keyu---jiangxi/KEYU_AI8052U_OpenLibrary]
 *   - 淘宝店铺:https://kyznc.taobao.com/
 *   - 技术支持:QQ群 974530818
 *
 * === 修订记录 ===
 * 日期       |  开发者  | 变更说明
 * -----------|----------|----------------------
 * 2025.12.22 |   xiao   | V2.0
 * 2025.01.05 |   xiao   | V2.1 添加spi接口
 *********************************************************************************/
#include "ky_spi.h"
#include "stc32g144k246.h"
#include "stc32g144k246_def.h"
#include "ky_system_clock.h"
#include <string.h>
#pragma warning disable = 188
#define SPI_DMA_TMP_BUFFER_SIZE 256

#define SPI_GET_PIN_SW(pin)     ((uint8_t)((pin) >> 7) & 0x03)
#define SPI_GET_GPIO(pin)       ((GPIO_Pin_t)((pin) & 0x7F))

static const uint32_t DMA_SPI_STA_ADDR[] = {0x7EFA22, 0x7EF812, 0x7EF832};
static const uint32_t DMA_SPI_CFG_ADDR[] = {0x7EFA20, 0x7EF810, 0x7EF830};
static const uint32_t DMA_SPI_AMT_ADDR[] = {0x7EFA23, 0x7EF815, 0x7EF835};
static const uint32_t DMA_SPI_AMTH_ADDR[] = {0x7EFA84, 0x7EF814, 0x7EF834};
static const uint32_t DMA_SPI_TXAH_ADDR[] = {0x7EFA25, 0x7EF818, 0x7EF838};
static const uint32_t DMA_SPI_TXAL_ADDR[] = {0x7EFA26, 0x7EF819, 0x7EF839};
static const uint32_t DMA_SPI_RXAH_ADDR[] = {0x7EFA27, 0x7EF81A, 0x7EF83A};
static const uint32_t DMA_SPI_RXAL_ADDR[] = {0x7EFA28, 0x7EF81B, 0x7EF83B};
static const uint32_t DMA_SPI_ITVH_ADDR[] = {0x7EFA2E, 0x7EF81E, 0x7EF83E};
static const uint32_t DMA_SPI_ITVL_ADDR[] = {0x7EFA2F, 0x7EF81F, 0x7EF83F};
static const uint32_t DMA_SPI_CR_ADDR[] = {0x7EFA21, 0x7EF811, 0x7EF831};
static const uint32_t HSSPI_CFG_ADDR[] = {0x7EFBF8, 0x7EF809, 0x7EF829};
static const uint32_t HSSPI_CFG2_ADDR[] = {0x7EFBF9, 0x7EF80A, 0x7EF82A};
static const uint32_t SPI_CLKDIV_ADDR[] = {0x7EFE90, 0x7EF808, 0x7EF828};

#define DMA_SPIN_STA(n)      (*(unsigned char volatile far *)(DMA_SPI_STA_ADDR[n]))
#define DMA_SPIN_CFG(n)      (*(unsigned char volatile far *)(DMA_SPI_CFG_ADDR[n]))
#define DMA_SPIN_AMT(n)      (*(unsigned char volatile far *)(DMA_SPI_AMT_ADDR[n]))
#define DMA_SPIN_AMTH(n)     (*(unsigned char volatile far *)(DMA_SPI_AMTH_ADDR[n]))
#define DMA_SPIN_TXAH(n)     (*(unsigned char volatile far *)(DMA_SPI_TXAH_ADDR[n]))
#define DMA_SPIN_TXAL(n)     (*(unsigned char volatile far *)(DMA_SPI_TXAL_ADDR[n]))
#define DMA_SPIN_RXAH(n)     (*(unsigned char volatile far *)(DMA_SPI_RXAH_ADDR[n]))
#define DMA_SPIN_RXAL(n)     (*(unsigned char volatile far *)(DMA_SPI_RXAL_ADDR[n]))
#define DMA_SPIN_ITVH(n)     (*(unsigned char volatile far *)(DMA_SPI_ITVH_ADDR[n]))
#define DMA_SPIN_ITVL(n)     (*(unsigned char volatile far *)(DMA_SPI_ITVL_ADDR[n]))
#define DMA_SPIN_CR(n)       (*(unsigned char volatile far *)(DMA_SPI_CR_ADDR[n]))
#define HSSPIN_CFG(n)        (*(unsigned char volatile far *)(HSSPI_CFG_ADDR[n]))
#define HSSPIN_CFG2(n)       (*(unsigned char volatile far *)(HSSPI_CFG2_ADDR[n]))
#define SPIN_CLKDIV(n)       (*(unsigned char volatile far *)(SPI_CLKDIV_ADDR[n]))

static uint8_t xdata _spi_tmp_buffer[SPI_DMA_TMP_BUFFER_SIZE];

/*********************************************************************************
 *  @brief     SPI 收发单字节（内部函数）
 *  @param     spiIndex    SPI模块号
 *  @param     dat         发送的数据
 *  @return    返回接收到的数据
 *********************************************************************************/
static uint8_t _spi_transfer_byte(SPI_Index_t spiIndex, const uint8_t dat)
{
    switch (spiIndex)
    {
    case SPI_1:
        SPSTAT = 0xC0;              // 先清除状态位
        SPDAT = dat;
        while (!(SPSTAT & 0x80));
        return SPDAT;
    case SPI_2:
        SPI2STAT = 0xC0;            // 先清除状态位
        SPI2DAT = dat;
        while (!(SPI2STAT & 0x80));
        return SPI2DAT;
    case SPI_3:
        SPI3STAT = 0xC0;            // 先清除状态位
        SPI3DAT = dat;
        while (!(SPI3STAT & 0x80));
        return SPI3DAT;
    default:
        break;
    }
    return 0xFF;
}

/*********************************************************************************
 *  @brief     SPI DMA初始化
 *  @param     spiIndex    SPI模块号
 *  @param     mode        SPI模式
 *  @param     baud        波特率
 *  @param     sck_pin     SCK引脚
 *  @param     mosi_pin    MOSI引脚
 *  @param     miso_pin    MISO引脚
 *  @return    无
 *********************************************************************************/
void spi_dma_init(SPI_Index_t spiIndex, SPI_Mode_t mode, uint32_t baud, SPI_Pin_t sck_pin, SPI_Pin_t mosi_pin, SPI_Pin_t miso_pin)
{
    uint8_t pin_sw, spi_psc;
    GPIO_Pin_t sck_gpio, mosi_gpio, miso_gpio;
    uint32_t sys_clk;

    // 参数检查：SPI 模块索引有效性
    KY_ASSERT(spiIndex >= SPI_1 && spiIndex <= SPI_3);

    pin_sw = SPI_GET_PIN_SW(sck_pin);

    // 参数检查：三个引脚必须属于同一组
    KY_ASSERT(SPI_GET_PIN_SW(mosi_pin) == pin_sw);
    KY_ASSERT(SPI_GET_PIN_SW(miso_pin) == pin_sw);
    
    sck_gpio = SPI_GET_GPIO(sck_pin);
    mosi_gpio = SPI_GET_GPIO(mosi_pin);
    miso_gpio = SPI_GET_GPIO(miso_pin);
    
    gpio_init(sck_gpio, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(mosi_gpio, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(miso_gpio, GPIO_MODE_IN_PU, GPIO_HIGH);
    
    if (baud >= 10000000U)
    {
        gpio_set_speed(sck_gpio, GPIO_SPEED_FAST);
        gpio_set_speed(mosi_gpio, GPIO_SPEED_FAST);
        gpio_set_speed(miso_gpio, GPIO_SPEED_FAST);
    }
    
    sys_clk = system_clock_freq;
    spi_psc = sys_clk / baud;
    if (spi_psc > 255)
        spi_psc = 255;
    
    switch (spiIndex)
    {
    case SPI_1:
        MODIFY_REG(P_SW1, (BIT3 | BIT2), (pin_sw << 2));
        SPI1_Disable();
        SPI1_IgnoreSS();
        SPI1_MasterMode();
        SPI1_DataMSB();
        // SPI1_SetClockDivider(3);
        
        switch (mode)
        {
        case SPI_MODE_1: SPI1_SetMode1(); break;
        case SPI_MODE_2: SPI1_SetMode2(); break;
        case SPI_MODE_3: SPI1_SetMode3(); break;
        default: SPI1_SetMode0(); break;
        }
        
        SPI1_Enable();
        break;
        
    case SPI_2:
        MODIFY_REG(P_SWX4, (BIT1 | BIT0), (pin_sw << 0));
        SPI2_Disable();
        SPI2_IgnoreSS();
        SPI2_MasterMode();
        SPI2_DataMSB();
        // SPI2_SetClockDivider(3);
        
        switch (mode)
        {
        case SPI_MODE_1: SPI2_SetMode1(); break;
        case SPI_MODE_2: SPI2_SetMode2(); break;
        case SPI_MODE_3: SPI2_SetMode3(); break;
        default: SPI2_SetMode0(); break;
        }
        
        SPI2_Enable();
        break;
        
    case SPI_3:
        MODIFY_REG(P_SWX4, (BIT3 | BIT2), (pin_sw << 2));
        SPI3_Disable();
        SPI3_IgnoreSS();
        SPI3_MasterMode();
        SPI3_DataMSB();
        // SPI3_SetClockDivider(0);
        
        switch (mode)
        {
        case SPI_MODE_1: SPI3_SetMode1(); break;
        case SPI_MODE_2: SPI3_SetMode2(); break;
        case SPI_MODE_3: SPI3_SetMode3(); break;
        default: SPI3_SetMode0(); break;
        }
        
        SPI3_Enable();
        break;
    }
    
    HSSPIN_CFG(spiIndex) = 0x00;
    HSSPIN_CFG2(spiIndex) = 0x10;
    SPIN_CLKDIV(spiIndex) = spi_psc;
    
    DMA_SPIN_STA(spiIndex) = 0x00;
    DMA_SPIN_CFG(spiIndex) = 0x00;
    DMA_SPIN_ITVH(spiIndex) = 0;
    DMA_SPIN_ITVL(spiIndex) = 0;
    DMA_SPIN_CR(spiIndex) = 0xC1;
}

/*********************************************************************************
 *  @brief     SPI DMA发送16bit数组
 *  @param     spiIndex    SPI模块号
 *  @param     dat         数据缓冲区指针
 *  @param     length      数组元素个数
 *  @return    无
 *********************************************************************************/
void spi_dma_send_16bit_array(SPI_Index_t spiIndex, const uint16_t *dat, uint32_t length)
{
    uint32_t byte_len = length * 2;
    uint32_t tmp_len;
    
    if ((uint32_t)dat >= STC32_FLASH_ADDR_START)
    {
        while (byte_len)
        {
            tmp_len = (byte_len > SPI_DMA_TMP_BUFFER_SIZE) ? SPI_DMA_TMP_BUFFER_SIZE : byte_len;
            memcpy(_spi_tmp_buffer, dat, tmp_len);
            byte_len -= tmp_len;
            dat = (const uint16_t *)((uint8_t *)dat + tmp_len);
            
            DMA_SPIN_AMT(spiIndex) = (uint8_t)((tmp_len - 1) & 0xFF);
            DMA_SPIN_AMTH(spiIndex) = (uint8_t)(((tmp_len - 1) >> 8) & 0xFF);
            DMA_SPIN_TXAH(spiIndex) = (uint8_t)((uint16_t)&_spi_tmp_buffer >> 8);
            DMA_SPIN_TXAL(spiIndex) = (uint8_t)((uint16_t)&_spi_tmp_buffer);
            
            DMA_SPIN_CFG(spiIndex) = 0x40;
            DMA_SPIN_CR(spiIndex) = 0xC1;
            while (!(DMA_SPIN_STA(spiIndex) & 0x01));
            DMA_SPIN_STA(spiIndex) = 0;
        }
    }
    else
    {
        DMA_SPIN_AMT(spiIndex) = (uint8_t)((byte_len - 1) & 0xFF);
        DMA_SPIN_AMTH(spiIndex) = (uint8_t)(((byte_len - 1) >> 8) & 0xFF);
        DMA_SPIN_TXAH(spiIndex) = (uint8_t)((uint16_t)dat >> 8);
        DMA_SPIN_TXAL(spiIndex) = (uint8_t)((uint16_t)dat);
        
        DMA_SPIN_CFG(spiIndex) = 0x40;
        DMA_SPIN_CR(spiIndex) = 0xC1;
        while (!(DMA_SPIN_STA(spiIndex) & 0x01));
        DMA_SPIN_STA(spiIndex) = 0;
    }
}

/*********************************************************************************
 *  @brief     SPI DMA发送8bit数组
 *  @param     spiIndex    SPI模块号
 *  @param     dat         数据缓冲区指针
 *  @param     length      数据长度
 *  @return    无
 *********************************************************************************/
void spi_dma_send_8bit_array(SPI_Index_t spiIndex, const uint8_t *dat, uint32_t length)
{
    uint32_t tmp_len;
    
    if ((uint32_t)dat >= STC32_FLASH_ADDR_START)
    {
        while (length)
        {
            tmp_len = (length > SPI_DMA_TMP_BUFFER_SIZE) ? SPI_DMA_TMP_BUFFER_SIZE : length;
            memcpy(_spi_tmp_buffer, dat, tmp_len);
            length -= tmp_len;
            dat += tmp_len;
            
            DMA_SPIN_AMT(spiIndex) = (uint8_t)((tmp_len - 1) & 0xFF);
            DMA_SPIN_AMTH(spiIndex) = (uint8_t)(((tmp_len - 1) >> 8) & 0xFF);
            DMA_SPIN_TXAH(spiIndex) = (uint8_t)((uint16_t)&_spi_tmp_buffer >> 8);
            DMA_SPIN_TXAL(spiIndex) = (uint8_t)((uint16_t)&_spi_tmp_buffer);
            
            DMA_SPIN_CFG(spiIndex) = 0x40;
            DMA_SPIN_CR(spiIndex) = 0xC1;
            while (!(DMA_SPIN_STA(spiIndex) & 0x01));
            DMA_SPIN_STA(spiIndex) = 0;
        }
    }
    else
    {
        DMA_SPIN_AMT(spiIndex) = (uint8_t)((length - 1) & 0xFF);
        DMA_SPIN_AMTH(spiIndex) = (uint8_t)(((length - 1) >> 8) & 0xFF);
        DMA_SPIN_TXAH(spiIndex) = (uint8_t)((uint16_t)dat >> 8);
        DMA_SPIN_TXAL(spiIndex) = (uint8_t)((uint16_t)dat);
        
        DMA_SPIN_CFG(spiIndex) = 0x40;
        DMA_SPIN_CR(spiIndex) = 0xC1;
        while (!(DMA_SPIN_STA(spiIndex) & 0x01));
        DMA_SPIN_STA(spiIndex) = 0;
    }
}

/*********************************************************************************
 *  @brief     SPI DMA发送单字节
 *  @param     spiIndex    SPI模块号
 *  @param     dat         数据
 *  @return    无
 *********************************************************************************/
void spi_dma_send_byte(SPI_Index_t spiIndex, const uint8_t dat)
{
    spi_dma_send_8bit_array(spiIndex, &dat, 1);
}

/*********************************************************************************
 *  @brief     SPI DMA读取16bit数组
 *  @param     spiIndex    SPI模块号
 *  @param     dat         数据缓冲区指针
 *  @param     length      数组元素个数
 *  @return    无
 *********************************************************************************/
void spi_dma_read_16bit_array(SPI_Index_t spiIndex, uint16_t *dat, uint32_t length)
{
    uint32_t byte_len = length * 2;
    
    DMA_SPIN_AMT(spiIndex) = (uint8_t)((byte_len - 1) & 0xFF);
    DMA_SPIN_AMTH(spiIndex) = (uint8_t)(((byte_len - 1) >> 8) & 0xFF);
    DMA_SPIN_RXAH(spiIndex) = (uint8_t)((uint16_t)dat >> 8);
    DMA_SPIN_RXAL(spiIndex) = (uint8_t)((uint16_t)dat);
    
    DMA_SPIN_CFG(spiIndex) = 0x20;
    DMA_SPIN_CR(spiIndex) = 0xC1;
    while (!(DMA_SPIN_STA(spiIndex) & 0x01));
    DMA_SPIN_STA(spiIndex) = 0;
}

/*********************************************************************************
 *  @brief     SPI DMA读取8bit数组
 *  @param     spiIndex    SPI模块号
 *  @param     dat         数据缓冲区指针
 *  @param     length      数据长度
 *  @return    无
 *********************************************************************************/
void spi_dma_read_8bit_array(SPI_Index_t spiIndex, uint8_t *dat, uint32_t length)
{
    DMA_SPIN_AMT(spiIndex) = (uint8_t)((length - 1) & 0xFF);
    DMA_SPIN_AMTH(spiIndex) = (uint8_t)(((length - 1) >> 8) & 0xFF);
    DMA_SPIN_RXAH(spiIndex) = (uint8_t)((uint16_t)dat >> 8);
    DMA_SPIN_RXAL(spiIndex) = (uint8_t)((uint16_t)dat);
    
    DMA_SPIN_CFG(spiIndex) = 0x20;
    DMA_SPIN_CR(spiIndex) = 0xC1;
    while (!(DMA_SPIN_STA(spiIndex) & 0x01));
    DMA_SPIN_STA(spiIndex) = 0;
}

/*********************************************************************************
 *  @brief     SPI DMA读取单字节
 *  @param     spiIndex    SPI模块号
 *  @param     dat         数据指针
 *  @return    无
 *********************************************************************************/
void spi_dma_read_byte(SPI_Index_t spiIndex, uint8_t *dat)
{
    spi_dma_read_8bit_array(spiIndex, dat, 1);
}

/*********************************************************************************
 *  @brief     初始化并配置指定的SPI通道
 *  @param     spiIndex    SPI模块号
 *  @param     mode        SPI模式
 *  @param     baud        波特率
 *  @param     sck_pin     SCK引脚
 *  @param     mosi_pin    MOSI引脚
 *  @param     miso_pin    MISO引脚
 *  @return    无
 *********************************************************************************/
void spi_init(SPI_Index_t spiIndex, SPI_Mode_t mode, uint32_t baud, SPI_Pin_t sck_pin, SPI_Pin_t mosi_pin, SPI_Pin_t miso_pin)
{
    uint8_t pin_sw, spr_bits;
    GPIO_Pin_t sck_gpio, mosi_gpio, miso_gpio;
    uint32_t sys_clk;

    // 参数检查：SPI 模块索引有效性
    KY_ASSERT(spiIndex >= SPI_1 && spiIndex <= SPI_3);

    pin_sw = SPI_GET_PIN_SW(sck_pin);

    // 参数检查：三个引脚必须属于同一组
    KY_ASSERT(SPI_GET_PIN_SW(mosi_pin) == pin_sw);
    KY_ASSERT(SPI_GET_PIN_SW(miso_pin) == pin_sw);
    
    sck_gpio = SPI_GET_GPIO(sck_pin);
    mosi_gpio = SPI_GET_GPIO(mosi_pin);
    miso_gpio = SPI_GET_GPIO(miso_pin);
    
    gpio_init(sck_gpio, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(mosi_gpio, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(miso_gpio, GPIO_MODE_IN_PU, GPIO_HIGH);
    
    if (baud >= 10000000U) {
        gpio_set_speed(sck_gpio, GPIO_SPEED_FAST);
        gpio_set_speed(mosi_gpio, GPIO_SPEED_FAST);
        gpio_set_speed(miso_gpio, GPIO_SPEED_FAST);
    }
    
    if (baud == 0) baud = 1000000;
    sys_clk = system_clock_freq;
    
    // 根据目标波特率选择分频系数 (SPR1:SPR0)
    // 0x03=/2, 0x00=/4, 0x01=/8, 0x02=/16
    if (baud >= sys_clk / 2)      spr_bits = 0x03;
    else if (baud >= sys_clk / 4) spr_bits = 0x00;
    else if (baud >= sys_clk / 8) spr_bits = 0x01;
    else                          spr_bits = 0x02;

    switch (spiIndex)
    {
    case SPI_1:
        MODIFY_REG(P_SW1, (BIT3 | BIT2), (pin_sw << 2));
        // 0xD0 = SSIG(1) + SPEN(1) + MSTR(1) = 忽略SS + 使能SPI + 主机模式
        SPCTL = 0xD0 | ((uint8_t)mode << 2) | spr_bits;
        SPSTAT = 0xC0;
        break;
        
    case SPI_2:
        MODIFY_REG(P_SWX4, (BIT1 | BIT0), (pin_sw << 0));
        SPI2CTL = 0xD0 | ((uint8_t)mode << 2) | spr_bits;
        SPI2STAT = 0xC0;
        break;
        
    case SPI_3:
        MODIFY_REG(P_SWX4, (BIT3 | BIT2), (pin_sw << 2));
        SPI3CTL = 0xD0 | ((uint8_t)mode << 2) | spr_bits;
        SPI3STAT = 0xC0;
        break;
        
    default:
        break;
    }
}



/*********************************************************************************
 *  @brief     SPI发送单字节
 *  @param     spiIndex    SPI模块号
 *  @param     dat         发送的数据
 *  @return    无
 *********************************************************************************/
void spi_send_byte(SPI_Index_t spiIndex, const uint8_t dat)
{
    _spi_transfer_byte(spiIndex, dat);
}

/*********************************************************************************
 *  @brief     SPI读取单字节
 *  @param     spiIndex    SPI模块号
 *  @return    返回接收到的数据
 *********************************************************************************/
uint8_t spi_read_byte(SPI_Index_t spiIndex)
{
    return _spi_transfer_byte(spiIndex, 0xFF);
}

/*********************************************************************************
 *  @brief     SPI发送缓冲区数据
 *  @param     spiIndex    SPI模块号
 *  @param     dat         数据缓冲区指针
 *  @param     length      数据长度
 *  @return    无
 *********************************************************************************/
void spi_send_buffer(SPI_Index_t spiIndex, const uint8_t *dat, uint32_t length)
{
    while (length--) {
        _spi_transfer_byte(spiIndex, *dat++);
    }
}

/*********************************************************************************
 *  @brief     SPI读取缓冲区数据
 *  @param     spiIndex    SPI模块号
 *  @param     dat         数据缓冲区指针
 *  @param     length      数据长度
 *  @return    无
 *********************************************************************************/
void spi_read_buffer(SPI_Index_t spiIndex, uint8_t *dat, uint32_t length)
{
    while (length--) {
        *dat++ = _spi_transfer_byte(spiIndex, 0xFF);
    }
}


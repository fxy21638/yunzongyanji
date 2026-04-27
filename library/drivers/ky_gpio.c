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
 * 文件名：[ky_gpio.c]
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
#include "ky_gpio.h"
#include "stc32g144k246.h"

#define GET_PORT_NUM(pin) ((pin >> 4) & 0x0F)
#define GET_PIN_MASK(pin) (1 << (pin & 0x07))

#define ADDR_PU(port) (unsigned char volatile far *)((port < 8) ? (0x7EFE10 + port) : (0x7EF9C0 + (port - 8)))
#define ADDR_PD(port) (unsigned char volatile far *)((port < 8) ? (0x7EFE40 + port) : (0x7EF9F0 + (port - 8)))
#define ADDR_SR(port) (unsigned char volatile far *)((port < 8) ? (0x7EFE20 + port) : (0x7EF9D0 + (port - 8)))
#define ADDR_DR(port) (unsigned char volatile far *)((port < 8) ? (0x7EFE28 + port) : (0x7EF9D8 + (port - 8)))
#define ADDR_IE(port) (unsigned char volatile far *)((port < 8) ? (0x7EFE30 + port) : (0x7EF9E0 + (port - 8)))

#define ADDR_EXT_OUT(port) (unsigned char volatile far *)(0x7EF700 + (port - 8))
#define ADDR_EXT_IN(port) (unsigned char volatile far *)(0x7EF708 + (port - 8))
#define ADDR_EXT_M1(port) (unsigned char volatile far *)(0x7EF718 + (port - 8))
#define ADDR_EXT_M0(port) (unsigned char volatile far *)(0x7EF710 + (port - 8))

#define ADDR_INTE(port) (unsigned char volatile far *)(0x7EFD00 + port)
#define ADDR_INTF(port) (unsigned char volatile far *)(0x7EFD10 + port)
#define ADDR_IM0(port) (unsigned char volatile far *)(0x7EFD20 + port)
#define ADDR_IM1(port) (unsigned char volatile far *)(0x7EFD30 + port)
#define ADDR_IM2(port) (unsigned char volatile far *)(0x7EF4E0 + port)

static GPIO_IntCallback_t gpio_callbacks[12][8] = {0};

/***************************************************************
 *  @brief     初始化一个GPIO引脚
 *  @param     pin     指定的GPIO引脚
 *  @param     mode    要配置的GPIO模式
 *  @param     level   要配置的GPIO电平
 *  @Sample usage:     gpio_init(GPIO_P10, GPIO_MODE_OUT_PP, GPIO_LOW);
 **************************************************************/
void gpio_init(GPIO_Pin_t pin, GPIO_Mode_t mode, GPIO_Level_t level)
{
    uint8_t port, mask;
    uint8_t valM1 = 0, valM0 = 0;
    uint8_t valPU = 0, valPD = 0;
    uint8_t digital_enable = 1;

    if (pin == GPIO_PFF)
        return;

    port = GET_PORT_NUM(pin);
    mask = GET_PIN_MASK(pin);

    switch (mode)
    {
    case GPIO_MODE_IN_FLOATING:
        valM1 = 1;
        valM0 = 0;
        break;
    case GPIO_MODE_IN_PU:
        valM1 = 1;
        valM0 = 0;
        valPU = 1;
        break;
    case GPIO_MODE_IN_PD:
        valM1 = 1;
        valM0 = 0;
        valPD = 1;
        break;
    case GPIO_MODE_OUT_PP:
        valM1 = 0;
        valM0 = 1;
        break;
    case GPIO_MODE_OUT_OD:
        valM1 = 1;
        valM0 = 1;
        break;
    case GPIO_MODE_OUT_OD_PU:
        valM1 = 1;
        valM0 = 1;
        valPU = 1;
        break;
    default:
        return;
    }

    if (port < 8)
    {
        switch (port)
        {
        case 0:
            if (valM1)
                P0M1 |= mask;
            else
                P0M1 &= ~mask;
            if (valM0)
                P0M0 |= mask;
            else
                P0M0 &= ~mask;
            break;
        case 1:
            if (valM1)
                P1M1 |= mask;
            else
                P1M1 &= ~mask;
            if (valM0)
                P1M0 |= mask;
            else
                P1M0 &= ~mask;
            break;
        case 2:
            if (valM1)
                P2M1 |= mask;
            else
                P2M1 &= ~mask;
            if (valM0)
                P2M0 |= mask;
            else
                P2M0 &= ~mask;
            break;
        case 3:
            if (valM1)
                P3M1 |= mask;
            else
                P3M1 &= ~mask;
            if (valM0)
                P3M0 |= mask;
            else
                P3M0 &= ~mask;
            break;
        case 4:
            if (valM1)
                P4M1 |= mask;
            else
                P4M1 &= ~mask;
            if (valM0)
                P4M0 |= mask;
            else
                P4M0 &= ~mask;
            break;
        case 5:
            if (valM1)
                P5M1 |= mask;
            else
                P5M1 &= ~mask;
            if (valM0)
                P5M0 |= mask;
            else
                P5M0 &= ~mask;
            break;
        case 6:
            if (valM1)
                P6M1 |= mask;
            else
                P6M1 &= ~mask;
            if (valM0)
                P6M0 |= mask;
            else
                P6M0 &= ~mask;
            break;
        case 7:
            if (valM1)
                P7M1 |= mask;
            else
                P7M1 &= ~mask;
            if (valM0)
                P7M0 |= mask;
            else
                P7M0 &= ~mask;
            break;
        }
    }
    else
    {
        if (valM1)
            *ADDR_EXT_M1(port) |= mask;
        else
            *ADDR_EXT_M1(port) &= ~mask;
        if (valM0)
            *ADDR_EXT_M0(port) |= mask;
        else
            *ADDR_EXT_M0(port) &= ~mask;
    }

    if (valPU)
        *ADDR_PU(port) |= mask;
    else
        *ADDR_PU(port) &= ~mask;
    if (valPD)
        *ADDR_PD(port) |= mask;
    else
        *ADDR_PD(port) &= ~mask;

    if (digital_enable)
        *ADDR_IE(port) |= mask;
    else
        *ADDR_IE(port) &= ~mask;

    gpio_write_pin(pin, level);
}

/***************************************************************
 *  @brief     设置GPIO引脚的驱动能力
 *  @param     pin     指定的GPIO引脚
 *  @param     drive   要配置的GPIO驱动能力
 *  @Sample usage:     gpio_set_drive(GPIO_P10, GPIO_DRIVE_ENHANCED);
 **************************************************************/
void gpio_set_drive(GPIO_Pin_t pin, GPIO_Drive_t drive)
{
    uint8_t port;
    uint8_t mask;
    unsigned char volatile far *pDR;

    if (pin == GPIO_PFF)
        return;

    port = GET_PORT_NUM(pin);
    mask = GET_PIN_MASK(pin);
    pDR = ADDR_DR(port);

    if (drive == GPIO_DRIVE_ENHANCED)
    {
        *pDR &= ~mask;
    }
    else
    {
        *pDR |= mask;
    }
}

/***************************************************************
 *  @brief     设置GPIO引脚的速度
 *  @param     pin     指定的GPIO引脚
 *  @param     speed   要配置的GPIO速度
 *  @Sample usage:     gpio_set_speed(GPIO_P10, GPIO_SPEED_FAST);
 **************************************************************/
void gpio_set_speed(GPIO_Pin_t pin, GPIO_Speed_t speed)
{
    uint8_t port;
    uint8_t mask;
    unsigned char volatile far *pSR;

    if (pin == GPIO_PFF)
        return;

    port = GET_PORT_NUM(pin);
    mask = GET_PIN_MASK(pin);
    pSR = ADDR_SR(port);

    if (speed == GPIO_SPEED_FAST)
    {
        *pSR &= ~mask;
    }
    else
    {
        *pSR |= mask;
    }
}

/***************************************************************
 *  @brief     设置GPIO引脚的数字信号使能
 *  @param     pin     指定的GPIO引脚
 *  @param     digital 要配置的GPIO数字信号使能
 *  @Sample usage:     gpio_set_digital(GPIO_P10, GPIO_DIGITAL_ENABLE);
 *  @note      若IO被当作比较器/ADC/触摸按键等模拟口时，设置为DISABLE
 *             若IO被当作数字口时，必须设置为ENABLE，否则无法读取电平
 **************************************************************/
void gpio_set_digital(GPIO_Pin_t pin, GPIO_Digital_t digital)
{
    uint8_t port;
    uint8_t mask;
    unsigned char volatile far *pIE;

    if (pin == GPIO_PFF)
        return;

    port = GET_PORT_NUM(pin);
    mask = GET_PIN_MASK(pin);
    pIE = ADDR_IE(port);

    if (digital == GPIO_DIGITAL_ENABLE)
    {
        *pIE |= mask;
    }
    else
    {
        *pIE &= ~mask;
    }
}

/***************************************************************
 *  @brief     设置GPIO引脚的电平
 *  @param     pin     指定的GPIO引脚
 *  @param     level   要配置的GPIO电平
 *  @Sample usage:     gpio_write_pin(GPIO_P10, GPIO_HIGH);
 **************************************************************/
void gpio_write_pin(GPIO_Pin_t pin, GPIO_Level_t level)
{
    uint8_t port;
    uint8_t mask;
    unsigned char volatile far *pOut;

    if (pin == GPIO_PFF)
        return;

    port = GET_PORT_NUM(pin);
    mask = GET_PIN_MASK(pin);

    if (port < 8)
    {
        switch (port)
        {
        case 0:
            if (level)
                P0 |= mask;
            else
                P0 &= ~mask;
            break;
        case 1:
            if (level)
                P1 |= mask;
            else
                P1 &= ~mask;
            break;
        case 2:
            if (level)
                P2 |= mask;
            else
                P2 &= ~mask;
            break;
        case 3:
            if (level)
                P3 |= mask;
            else
                P3 &= ~mask;
            break;
        case 4:
            if (level)
                P4 |= mask;
            else
                P4 &= ~mask;
            break;
        case 5:
            if (level)
                P5 |= mask;
            else
                P5 &= ~mask;
            break;
        case 6:
            if (level)
                P6 |= mask;
            else
                P6 &= ~mask;
            break;
        case 7:
            if (level)
                P7 |= mask;
            else
                P7 &= ~mask;
            break;
        }
    }
    else
    {
        pOut = ADDR_EXT_OUT(port);
        if (level)
            *pOut |= mask;
        else
            *pOut &= ~mask;
    }
}

/***************************************************************
 *  @brief     读取GPIO引脚的电平
 *  @param     pin     指定的GPIO引脚
 *  @return    GPIO引脚的电平
 *  @Sample usage:     gpio_read_pin(GPIO_P10);
 **************************************************************/
uint8_t gpio_read_pin(GPIO_Pin_t pin)
{
    uint8_t port;
    uint8_t mask;
    uint8_t val;

    if (pin == GPIO_PFF)
        return 0;

    port = GET_PORT_NUM(pin);
    mask = GET_PIN_MASK(pin);
    val = 0;

    if (port < 8)
    {
        switch (port)
        {
        case 0:
            val = P0 & mask;
            break;
        case 1:
            val = P1 & mask;
            break;
        case 2:
            val = P2 & mask;
            break;
        case 3:
            val = P3 & mask;
            break;
        case 4:
            val = P4 & mask;
            break;
        case 5:
            val = P5 & mask;
            break;
        case 6:
            val = P6 & mask;
            break;
        case 7:
            val = P7 & mask;
            break;
        }
    }
    else
    {
        val = *ADDR_EXT_IN(port) & mask;
    }

    return (val ? GPIO_HIGH : GPIO_LOW);
}

/***************************************************************
 *  @brief     切换GPIO引脚的电平
 *  @param     pin     指定的GPIO引脚
 *  @Sample usage:     gpio_toggle_pin(GPIO_P10);
 **************************************************************/
void gpio_toggle_pin(GPIO_Pin_t pin)
{
    gpio_write_pin(pin, !gpio_read_pin(pin));
}

/***************************************************************
 *  @brief     初始化GPIO引脚的中断
 *  @param     pin        指定的GPIO引脚
 *  @param     int_type   要配置的GPIO中断类型
 *  @Sample usage:     gpio_int_init(GPIO_P10, GPIO_INT_RISING);
 **************************************************************/
void gpio_int_init(GPIO_Pin_t pin, GPIO_Int_t int_type)
{
    uint8_t port, mask;
    uint8_t m2 = 0, m1 = 0, m0 = 0;

    if (pin == GPIO_PFF)
        return;

    port = GET_PORT_NUM(pin);
    mask = GET_PIN_MASK(pin);

    if (int_type == GPIO_INT_DISABLE)
    {
        *ADDR_INTE(port) &= ~mask;
        return;
    }

    switch (int_type)
    {
    case GPIO_INT_FALLING:
        m2 = 0;
        m1 = 0;
        m0 = 0;
        break;
    case GPIO_INT_RISING:
        m2 = 0;
        m1 = 0;
        m0 = 1;
        break;
    case GPIO_INT_RISING_FALLING:
        m2 = 1;
        m1 = 0;
        m0 = 0;
        break;
    default:
        return;
    }

    if (m2)
        *ADDR_IM2(port) |= mask;
    else
        *ADDR_IM2(port) &= ~mask;
    if (m1)
        *ADDR_IM1(port) |= mask;
    else
        *ADDR_IM1(port) &= ~mask;
    if (m0)
        *ADDR_IM0(port) |= mask;
    else
        *ADDR_IM0(port) &= ~mask;

    *ADDR_INTE(port) |= mask;
}

/***************************************************************
 *  @brief     设置GPIO引脚的中断回调函数
 *  @param     pin      指定的GPIO引脚
 *  @param     callback 要配置的GPIO中断回调函数
 *  @Sample usage:     gpio_int_set_callback(GPIO_P10, my_callback);
 **************************************************************/
void gpio_int_set_callback(GPIO_Pin_t pin, GPIO_IntCallback_t callback)
{
    uint8_t port, pin_idx;

    if (pin == GPIO_PFF)
        return;

    port = GET_PORT_NUM(pin);
    pin_idx = pin & 0x07;

    if (port < 12 && pin_idx < 8)
    {
        gpio_callbacks[port][pin_idx] = callback;
    }
}

/***************************************************************
 *  @brief     GPIO中断服务处理函数
 *  @param     port    指定的GPIO端口号 (0~11)
 *  @Sample usage:     gpio_isr_handler(1); // 处理P1端口中断
 **************************************************************/
void gpio_isr_handler(uint8_t port) 
{
    unsigned char volatile far *pIntf = ADDR_INTF(port);
    uint8_t flags = *pIntf;

    if (flags & 0x01)
    {
        *pIntf &= ~0x01;
        if (gpio_callbacks[port][0])
            gpio_callbacks[port][0]();
    }
    if (flags & 0x02)
    {
        *pIntf &= ~0x02;
        if (gpio_callbacks[port][1])
            gpio_callbacks[port][1]();
    }
    if (flags & 0x04)
    {
        *pIntf &= ~0x04;
        if (gpio_callbacks[port][2])
            gpio_callbacks[port][2]();
    }
    if (flags & 0x08)
    {
        *pIntf &= ~0x08;
        if (gpio_callbacks[port][3])
            gpio_callbacks[port][3]();
    }
    if (flags & 0x10)
    {
        *pIntf &= ~0x10;
        if (gpio_callbacks[port][4])
            gpio_callbacks[port][4]();
    }
    if (flags & 0x20)
    {
        *pIntf &= ~0x20;
        if (gpio_callbacks[port][5])
            gpio_callbacks[port][5]();
    }
    if (flags & 0x40)
    {
        *pIntf &= ~0x40;
        if (gpio_callbacks[port][6])
            gpio_callbacks[port][6]();
    }
    if (flags & 0x80)
    {
        *pIntf &= ~0x80;
        if (gpio_callbacks[port][7])
            gpio_callbacks[port][7]();
    }
}
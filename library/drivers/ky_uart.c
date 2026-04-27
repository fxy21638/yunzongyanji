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
 * 文件名：[ky_uart.c]
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
#include "ky_uart.h"
#include "stc32g144k246.h"
#include "ky_system_clock.h"
#include <string.h>



static UART_Callback_t uart_callbacks[UART_MAX] = {0};
static UART_Callback_Dma_t uart_dma_tx_callbacks[UART_MAX] = {0};
static UART_Callback_Dma_t uart_dma_rx_callbacks[UART_MAX] = {0};
static uint32_t timer2_baudrate = 0;

// /*********************************************************************************
//  *  @brief     putchar重定向，用于printf
//  *  @param     c   要发送的字符
//  *  @return    发送的字符
//  *********************************************************************************/
// char putchar(char c)
// {
//     uart_send_byte(UART_1, (uint8_t)c);
//     return c;
// }

/*********************************************************************************
 *  @brief     设置UART引脚复用
 *  @param     index       UART索引
 *  @param     tx_pin      TX引脚编码
 *********************************************************************************/
static void _uart_set_pin_mux(UART_Index_t index, UART_Pin_t tx_pin)
{
    uint8_t pingrp = UART_GET_PINGRP(tx_pin);

    switch (index)
    {
    case UART_1:
        P_SW1 = (P_SW1 & ~0xC0) | ((pingrp << 6) & 0xC0);
        break;

    case UART_2:
        if (pingrp & 0x01)
            P_SW2 |= 0x01;
        else
            P_SW2 &= ~0x01;
        if (pingrp & 0x02)
            P_SWX1 |= 0x20;
        else
            P_SWX1 &= ~0x20;
        break;

    case UART_3:
        if (pingrp & 0x01)
            P_SW2 |= 0x02;
        else
            P_SW2 &= ~0x02;
        if (pingrp & 0x02)
            P_SWX1 |= 0x40;
        else
            P_SWX1 &= ~0x40;
        break;

    case UART_4:
        if (pingrp & 0x01)
            P_SW2 |= 0x04;
        else
            P_SW2 &= ~0x04;
        if (pingrp & 0x02)
            P_SWX1 |= 0x80;
        else
            P_SWX1 &= ~0x80;
        break;

    case UART_5:
        P_SWX2 = (P_SWX2 & ~0x03) | (pingrp & 0x03);
        break;

    case UART_6:
        P_SWX2 = (P_SWX2 & ~0x0C) | ((pingrp << 2) & 0x0C);
        break;

    case UART_7:
        P_SWX5 = (P_SWX5 & ~0x30) | ((pingrp << 4) & 0x30);
        break;

    case UART_8:
        P_SWX5 = (P_SWX5 & ~0xC0) | ((pingrp << 6) & 0xC0);
        break;

    default:
        break;
    }
}

// /*********************************************************************************
//  *  @brief     配置Timer2作为波特率发生器
//  *  @param     baud        波特率
//  *********************************************************************************/
static void _uart_config_timer2(uint32_t baud)
{
    uint16_t reload;
    reload = (uint16_t)(65536UL - (system_clock_freq) / 4UL / baud);
    
    T2L = (uint8_t)reload;
    T2H = (uint8_t)(reload >> 8);
    AUXR |= 0x04;    // T2设为1T模式
    AUXR |= 0x10;    // 启动T2
    timer2_baudrate = baud;
}

/*********************************************************************************
 * @brief 配置专用定时器 (T1, T3~T8)
 * @param index 串口索引
 *********************************************************************************/
static void _config_dedicated_timer(UART_Index_t index, uint32_t baud) {
    uint16_t reload;
    reload = (uint16_t)(65536UL - (system_clock_freq) / 4UL / baud);

    switch (index) {
        case UART_1:
            AUXR |= 0x40; // T1设为1T模式
            TMOD &= ~0x0F; // T1设为16位自动重装模式 (Mode 0)
            TH1 = (uint8_t)(reload >> 8);
            TL1 = (uint8_t)reload;
            TR1 = 1;      // 启动T1
            break;
        case UART_3:
            T3L = (uint8_t)reload; T3H = (uint8_t)(reload >> 8);
            T4T3M |= 0x0A; // T3设为1T模式 (BIT1) + 启动T3 (BIT3)
            break;
        case UART_4:
            T4L = (uint8_t)reload; T4H = (uint8_t)(reload >> 8);
            T4T3M |= 0xA0; // T4设为1T模式 (BIT5) + 启动T4 (BIT7)
            break;
        case UART_5:
            T5L = (uint8_t)reload; T5H = (uint8_t)(reload >> 8);
            T6T5M |= 0x0A; // T5设为1T模式 (BIT1) + 启动T5 (BIT3)
            break;
        case UART_6:
            T6L = (uint8_t)reload; T6H = (uint8_t)(reload >> 8);
            T6T5M |= 0xA0; // T6设为1T模式 (BIT5) + 启动T6 (BIT7)
            break;
        case UART_7:
            T7L = (uint8_t)reload; T7H = (uint8_t)(reload >> 8);
            T8T7M |= 0x0A; // T7设为1T模式 (BIT1) + 启动T7 (BIT3)
            break;
        case UART_8:
            T8L = (uint8_t)reload; T8H = (uint8_t)(reload >> 8);
            T8T7M |= 0xA0; // T8设为1T模式 (BIT5) + 启动T8 (BIT7)
            break;
        default: break;
    }
}


/*********************************************************************************
 *  @brief     UART初始化
 *  @param     index       UART索引
 *  @param     baudrate    波特率
 *  @param     tx_pin      TX引脚
 *  @param     rx_pin      RX引脚
 *********************************************************************************/
void uart_init(UART_Index_t index, uint32_t baudrate, UART_Pin_t tx_pin, UART_Pin_t rx_pin)
{
    uint8_t use_timer2 = 0;
    uint16_t reload = 0;
    GPIO_Pin_t gpio_tx = UART_GET_PIN(tx_pin);
    GPIO_Pin_t gpio_rx = UART_GET_PIN(rx_pin);

    // 参数检查：UART 索引有效性
    KY_ASSERT(index >= UART_1 && index < UART_MAX);
    // 参数检查：波特率有效性
    KY_ASSERT(baudrate > 0 && baudrate <= 3000000UL);
    // 参数检查：TX 和 RX 引脚必须属于同一组
    KY_ASSERT(UART_GET_PINGRP(tx_pin) == UART_GET_PINGRP(rx_pin));

    gpio_init(gpio_tx, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(gpio_rx, GPIO_MODE_IN_PU, GPIO_HIGH);

    _uart_set_pin_mux(index, tx_pin);
    // 默认使用定时器2
    if (index == UART_2) {
        // 串口2强制使用定时器2
        _uart_config_timer2(baudrate);
        use_timer2 = 1;
    } else {
        // 检查定时器2是否可用或匹配
        if (timer2_baudrate == 0) {
            _uart_config_timer2(baudrate);
            use_timer2 = 1;
        } else if (timer2_baudrate == baudrate) {
            use_timer2 = 1; // 复用已有的T2
        } else {
            // T2已被占用且频率不符，使用专用定时器
            _config_dedicated_timer(index, baudrate);
            use_timer2 = 0;
        }
    }

    switch (index) {
        case UART_1:
            SCON = 0x50; // Mode 1, REN=1
            if (use_timer2) AUXR |= 0x01; else AUXR &= ~0x01;
            break;
        case UART_2:
            S2CON = 0x50; // 8位异步, REN=1
            break;
        case UART_3:
            S3CON = 0x50;
            if (use_timer2) S3CFG &= ~0x01; else S3CFG |= 0x01;
            break;
        case UART_4:
            S4CON = 0x50;
            if (use_timer2) S4CFG &= ~0x01; else S4CFG |= 0x01;
            break;
        case UART_5:
            S5CON = 0x50;
            if (use_timer2) S5CFG &= ~0x01; else S5CFG |= 0x01;
            break;
        case UART_6:
            S6CON = 0x50;
            if (use_timer2) S6CFG &= ~0x01; else S6CFG |= 0x01;
            break;
        case UART_7:
            S7CON = 0x50;
            if (use_timer2) S7CFG &= ~0x01; else S7CFG |= 0x01;
            break;
        case UART_8:
            S8CON = 0x50;
            if (use_timer2) S8CFG &= ~0x01; else S8CFG |= 0x01;
            break;
    }
}

/*********************************************************************************
 *  @brief     发送一个字节
 *  @param     index   UART索引
 *  @param     dat     要发送的数据
 *********************************************************************************/
void uart_send_byte(UART_Index_t index, uint8_t dat)
{
    switch (index)
    {
    case UART_1:
        SBUF = dat;
        while (!TI);
        TI = 0;
        break;
    case UART_2:
        S2BUF = dat;
        while (!(S2CON & 0x02));
        S2CON &= ~0x02;
        break;
    case UART_3:
        S3BUF = dat;
        while (!(S3CON & 0x02));
        S3CON &= ~0x02;
        break;
    case UART_4:
        S4BUF = dat;
        while (!(S4CON & 0x02));
        S4CON &= ~0x02;
        break;
    case UART_5:
        S5BUF = dat;
        while (!(S5CON & 0x02));
        S5CON &= ~0x02;
        break;
    case UART_6:
        S6BUF = dat;
        while (!(S6CON & 0x02));
        S6CON &= ~0x02;
        break;
    case UART_7:
        S7BUF = dat;
        while (!(S7CON & 0x02));
        S7CON &= ~0x02;
        break;
    case UART_8:
        S8BUF = dat;
        while (!(S8CON & 0x02));
        S8CON &= ~0x02;
        break;
    default:
        break;
    }
}

/*********************************************************************************
 *  @brief     发送字符串
 *  @param     index   UART索引
 *  @param     str     要发送的字符串
 *********************************************************************************/
void uart_send_string(UART_Index_t index, char *str)
{
    while (*str)
        uart_send_byte(index, (uint8_t)*str++);
}

/*********************************************************************************
 *  @brief     发送缓冲区
 *  @param     index   UART索引
 *  @param     buffer  数据缓冲区
 *  @param     len     数据长度
 *********************************************************************************/
void uart_send_buffer(UART_Index_t index, uint8_t *buffer, uint16_t len)
{
    while (len--)
        uart_send_byte(index, *buffer++);
}

/*********************************************************************************
 *  @brief     设置接收回调
 *  @param     index       UART索引
 *  @param     callback    回调函数
 *********************************************************************************/
void uart_set_rx_callback(UART_Index_t index, UART_Callback_t callback)
{
    if (index >= UART_MAX)
        return;

    uart_callbacks[index] = callback;

    if (callback != NULL) {
        switch (index)
        {
        case UART_1: ES = 1; break;
        case UART_2: IE2 |= 0x01; break;
        case UART_3: IE2 |= 0x08; break;
        case UART_4: IE2 |= 0x10; break;
        case UART_5: S5INTR |= 0x80; break;
        case UART_6: S6INTR |= 0x80; break;
        case UART_7: S7INTR |= 0x80; break;
        case UART_8: S8INTR |= 0x80; break;
        default: break;
        }
    } else {
        switch (index)
        {
        case UART_1: ES = 0; break;
        case UART_2: IE2 &= ~0x01; break;
        case UART_3: IE2 &= ~0x08; break;
        case UART_4: IE2 &= ~0x10; break;
        case UART_5: S5INTR &= ~0x80; break;
        case UART_6: S6INTR &= ~0x80; break;
        case UART_7: S7INTR &= ~0x80; break;
        case UART_8: S8INTR &= ~0x80; break;
        default: break;
        }
    }
}

/*********************************************************************************
 *  @brief     UART中断处理
 *  @param     index   UART索引
 *********************************************************************************/
void uart_isr_handler(UART_Index_t index)
{
    uint8_t dat;
    switch (index)
    {
    case UART_1:
        if (RI) {
            RI = 0;
            dat = SBUF;
            if (uart_callbacks[index])
                uart_callbacks[index](dat);
        }
        if (TI)
            TI = 0;
        break;

    case UART_2:
        if (S2CON & 0x01) {
            S2CON &= ~0x01;
            dat = S2BUF;
            if (uart_callbacks[index])
                uart_callbacks[index](dat);
        }
        if (S2CON & 0x02)
            S2CON &= ~0x02;
        break;

    case UART_3:
        if (S3CON & 0x01) {
            S3CON &= ~0x01;
            dat = S3BUF;
            if (uart_callbacks[index])
                uart_callbacks[index](dat);
        }
        if (S3CON & 0x02)
            S3CON &= ~0x02;
        break;

    case UART_4:
        if (S4CON & 0x01) {
            S4CON &= ~0x01;
            dat = S4BUF;
            if (uart_callbacks[index])
                uart_callbacks[index](dat);
        }
        if (S4CON & 0x02)
            S4CON &= ~0x02;
        break;

    case UART_5:
        if (S5CON & 0x01) {
            S5CON &= ~0x01;
            dat = S5BUF;
            if (uart_callbacks[index])
                uart_callbacks[index](dat);
        }
        if (S5CON & 0x02)
            S5CON &= ~0x02;
        break;

    case UART_6:
        if (S6CON & 0x01) {
            S6CON &= ~0x01;
            dat = S6BUF;
            if (uart_callbacks[index])
                uart_callbacks[index](dat);
        }
        if (S6CON & 0x02)
            S6CON &= ~0x02;
        break;

    case UART_7:
        if (S7CON & 0x01) {
            S7CON &= ~0x01;
            dat = S7BUF;
            if (uart_callbacks[index])
                uart_callbacks[index](dat);
        }
        if (S7CON & 0x02)
            S7CON &= ~0x02;
        break;

    case UART_8:
        if (S8CON & 0x01) {
            S8CON &= ~0x01;
            dat = S8BUF;
            if (uart_callbacks[index])
                uart_callbacks[index](dat);
        }
        if (S8CON & 0x02)
            S8CON &= ~0x02;
        break;

    default:
        break;
    }
}

/*********************************************************************************
 *  @brief     DMA 发送数据（内部实现）
 *  @param     index       串口索引
 *  @param     buffer      xdata区域数据缓冲区
 *  @param     len         数据长度
 *********************************************************************************/
static void _uart_dma_send_xdata(UART_Index_t index, uint8_t *buffer, uint16_t len)
{
    uint16_t amtVal;
    uint16_t addr;
    uint8_t addr_h, addr_l, amt_h, amt_l;

    amtVal = len - 1;
    addr = (uint16_t)buffer;
    addr_h = (uint8_t)(addr >> 8);
    addr_l = (uint8_t)(addr & 0xFF);
    amt_h = (uint8_t)(amtVal >> 8);
    amt_l = (uint8_t)(amtVal & 0xFF);

    switch (index)
    {
    case UART_1:
        DMA_UR1T_STA = 0x00;
        DMA_UR1T_CFG = 0x00;
        DMA_UR1T_TXAH = addr_h;
        DMA_UR1T_TXAL = addr_l;
        DMA_UR1T_AMTH = amt_h;
        DMA_UR1T_AMT = amt_l;
        DMA_UR1T_CR = 0xC0;
        while(!(DMA_UR1T_STA & 0x01));
        DMA_UR1T_CR = 0x00;
        break;

    case UART_2:
        DMA_UR2T_STA = 0x00;
        DMA_UR2T_CFG = 0x00;
        DMA_UR2T_TXAH = addr_h;
        DMA_UR2T_TXAL = addr_l;
        DMA_UR2T_AMTH = amt_h;
        DMA_UR2T_AMT = amt_l;
        DMA_UR2T_CR = 0xC0;
        while(!(DMA_UR2T_STA & 0x01));
        DMA_UR2T_CR = 0x00;
        break;

    case UART_3:
        DMA_UR3T_STA = 0x00;
        DMA_UR3T_CFG = 0x00;
        DMA_UR3T_TXAH = addr_h;
        DMA_UR3T_TXAL = addr_l;
        DMA_UR3T_AMTH = amt_h;
        DMA_UR3T_AMT = amt_l;
        DMA_UR3T_CR = 0xC0;
        while(!(DMA_UR3T_STA & 0x01));
        DMA_UR3T_CR = 0x00;
        break;

    case UART_4:
        DMA_UR4T_STA = 0x00;
        DMA_UR4T_CFG = 0x00;
        DMA_UR4T_TXAH = addr_h;
        DMA_UR4T_TXAL = addr_l;
        DMA_UR4T_AMTH = amt_h;
        DMA_UR4T_AMT = amt_l;
        DMA_UR4T_CR = 0xC0;
        while(!(DMA_UR4T_STA & 0x01));
        DMA_UR4T_CR = 0x00;
        break;

    case UART_5:
        DMA_UR5T_STA = 0x00;
        DMA_UR5T_CFG = 0x00;
        DMA_UR5T_TXAH = addr_h;
        DMA_UR5T_TXAL = addr_l;
        DMA_UR5T_AMTH = amt_h;
        DMA_UR5T_AMT = amt_l;
        DMA_UR5T_CR = 0xC0;
        while(!(DMA_UR5T_STA & 0x01));
        DMA_UR5T_CR = 0x00;
        break;

    case UART_6:
        DMA_UR6T_STA = 0x00;
        DMA_UR6T_CFG = 0x00;
        DMA_UR6T_TXAH = addr_h;
        DMA_UR6T_TXAL = addr_l;
        DMA_UR6T_AMTH = amt_h;
        DMA_UR6T_AMT = amt_l;
        DMA_UR6T_CR = 0xC0;
        while(!(DMA_UR6T_STA & 0x01));
        DMA_UR6T_CR = 0x00;
        break;

    case UART_7:
        DMA_UR7T_STA = 0x00;
        DMA_UR7T_CFG = 0x00;
        DMA_UR7T_TXAH = addr_h;
        DMA_UR7T_TXAL = addr_l;
        DMA_UR7T_AMTH = amt_h;
        DMA_UR7T_AMT = amt_l;
        DMA_UR7T_CR = 0xC0;
        while(!(DMA_UR7T_STA & 0x01));
        DMA_UR7T_CR = 0x00;
        break;

    case UART_8:
        DMA_UR8T_STA = 0x00;
        DMA_UR8T_CFG = 0x00;
        DMA_UR8T_TXAH = addr_h;
        DMA_UR8T_TXAL = addr_l;
        DMA_UR8T_AMTH = amt_h;
        DMA_UR8T_AMT = amt_l;
        DMA_UR8T_CR = 0xC0;
        while(!(DMA_UR8T_STA & 0x01));
        DMA_UR8T_CR = 0x00;
        break;

    default:
        break;
    }
}

#define UART_DMA_TMP_BUFFER_SIZE 64
static uint8_t xdata _uart_tmp_buffer[UART_DMA_TMP_BUFFER_SIZE];

/*********************************************************************************
 *  @brief     DMA 发送数据（自动处理非xdata区域数据）
 *  @param     index       串口索引
 *  @param     buffer      数据缓冲区
 *  @param     len         数据长度
 *********************************************************************************/
void uart_dma_send(UART_Index_t index, uint8_t *buffer, uint16_t len)
{
    uint16_t tmp_len;

    if (len == 0)
        return;

    // UART DMA只能操作xdata区域的数据，需要通过临时缓冲区分块传输
    while (len)
    {
        tmp_len = (len > UART_DMA_TMP_BUFFER_SIZE) ? UART_DMA_TMP_BUFFER_SIZE : len;
        memcpy(_uart_tmp_buffer, buffer, tmp_len);
        len -= tmp_len;
        buffer += tmp_len;

        _uart_dma_send_xdata(index, _uart_tmp_buffer, tmp_len);
    }
}


/*********************************************************************************
 *  @brief     配置 UART DMA 接收
 *  @param     index       串口索引
 *  @param     buffer      接收数据缓冲区地址
 *  @param     len         缓冲区最大接收长度
 *********************************************************************************/
void uart_dma_receive(UART_Index_t index, uint8_t *buffer, uint16_t len)
{
    uint16_t amtVal;
    uint16_t addr;
    uint8_t addr_h, addr_l, amt_h, amt_l;

    if (len == 0)
        return;

    amtVal = len - 1;
    addr = (uint16_t)buffer;
    addr_h = (uint8_t)(addr >> 8);
    addr_l = (uint8_t)(addr & 0xFF);
    amt_h = (uint8_t)(amtVal >> 8);
    amt_l = (uint8_t)(amtVal & 0xFF);

    switch (index)
    {
    case UART_1:
        DMA_UR1R_STA = 0x00;
        DMA_UR1R_RXAH = addr_h;
        DMA_UR1R_RXAL = addr_l;
        DMA_UR1R_AMTH = amt_h;
        DMA_UR1R_AMT = amt_l;
        DMA_UR1R_CFG = 0x8F;
        DMA_UR1R_CR = 0xA1;
        break;

    case UART_2:
        DMA_UR2R_STA = 0x00;
        DMA_UR2R_RXAH = addr_h;
        DMA_UR2R_RXAL = addr_l;
        DMA_UR2R_AMTH = amt_h;
        DMA_UR2R_AMT = amt_l;
        DMA_UR2R_CFG = 0x8F;
        DMA_UR2R_CR = 0xA1;
        break;

    case UART_3:
        DMA_UR3R_STA = 0x00;
        DMA_UR3R_RXAH = addr_h;
        DMA_UR3R_RXAL = addr_l;
        DMA_UR3R_AMTH = amt_h;
        DMA_UR3R_AMT = amt_l;
        DMA_UR3R_CFG = 0x8F;
        DMA_UR3R_CR = 0xA1;
        break;

    case UART_4:
        DMA_UR4R_STA = 0x00;
        DMA_UR4R_RXAH = addr_h;
        DMA_UR4R_RXAL = addr_l;
        DMA_UR4R_AMTH = amt_h;
        DMA_UR4R_AMT = amt_l;
        DMA_UR4R_CFG = 0x8F;
        DMA_UR4R_CR = 0xA1;
        break;

    case UART_5:
        DMA_UR5R_STA = 0x00;
        DMA_UR5R_RXAH = addr_h;
        DMA_UR5R_RXAL = addr_l;
        DMA_UR5R_AMTH = amt_h;
        DMA_UR5R_AMT = amt_l;
        DMA_UR5R_CFG = 0x8F;
        DMA_UR5R_CR = 0xA1;
        break;

    case UART_6:
        DMA_UR6R_STA = 0x00;
        DMA_UR6R_RXAH = addr_h;
        DMA_UR6R_RXAL = addr_l;
        DMA_UR6R_AMTH = amt_h;
        DMA_UR6R_AMT = amt_l;
        DMA_UR6R_CFG = 0x8F;
        DMA_UR6R_CR = 0xA1;
        break;

    case UART_7:
        DMA_UR7R_STA = 0x00;
        DMA_UR7R_RXAH = addr_h;
        DMA_UR7R_RXAL = addr_l;
        DMA_UR7R_AMTH = amt_h;
        DMA_UR7R_AMT = amt_l;
        DMA_UR7R_CFG = 0x8F;
        DMA_UR7R_CR = 0xA1;
        break;

    case UART_8:
        DMA_UR8R_STA = 0x00;
        DMA_UR8R_RXAH = addr_h;
        DMA_UR8R_RXAL = addr_l;
        DMA_UR8R_AMTH = amt_h;
        DMA_UR8R_AMT = amt_l;
        DMA_UR8R_CFG = 0x8F;
        DMA_UR8R_CR = 0xA1;
        break;

    default:
        break;
    }
}

/*********************************************************************************
 *  @brief     设置 DMA 发送完成回调
 *  @param     index       串口索引
 *  @param     callback    回调函数
 *********************************************************************************/
void uart_set_dma_tx_callback(UART_Index_t index, UART_Callback_Dma_t callback)
{
    if (index < UART_MAX)
        uart_dma_tx_callbacks[index] = callback;
}

/*********************************************************************************
 *  @brief     设置 DMA 接收完成回调
 *  @param     index       串口索引
 *  @param     callback    回调函数
 *********************************************************************************/
void uart_set_dma_rx_callback(UART_Index_t index, UART_Callback_Dma_t callback)
{
    if (index < UART_MAX)
        uart_dma_rx_callbacks[index] = callback;
}

/*********************************************************************************
 *  @brief     DMA 发送中断处理
 *  @param     index       串口索引
 *********************************************************************************/
void uart_dma_tx_isr_handler(UART_Index_t index)
{
    switch (index)
    {
    case UART_1: DMA_UR1T_STA &= ~0x01; break;
    case UART_2: DMA_UR2T_STA &= ~0x01; break;
    case UART_3: DMA_UR3T_STA &= ~0x01; break;
    case UART_4: DMA_UR4T_STA &= ~0x01; break;
    case UART_5: DMA_UR5T_STA &= ~0x01; break;
    case UART_6: DMA_UR6T_STA &= ~0x01; break;
    case UART_7: DMA_UR7T_STA &= ~0x01; break;
    case UART_8: DMA_UR8T_STA &= ~0x01; break;
    default: return;
    }

    if (uart_dma_tx_callbacks[index])
        uart_dma_tx_callbacks[index]();
}

/*********************************************************************************
 *  @brief     DMA 接收中断处理
 *  @param     index       串口索引
 *********************************************************************************/
void uart_dma_rx_isr_handler(UART_Index_t index)
{
    switch (index)
    {
    case UART_1: DMA_UR1R_STA &= ~0x01; break;
    case UART_2: DMA_UR2R_STA &= ~0x01; break;
    case UART_3: DMA_UR3R_STA &= ~0x01; break;
    case UART_4: DMA_UR4R_STA &= ~0x01; break;
    case UART_5: DMA_UR5R_STA &= ~0x01; break;
    case UART_6: DMA_UR6R_STA &= ~0x01; break;
    case UART_7: DMA_UR7R_STA &= ~0x01; break;
    case UART_8: DMA_UR8R_STA &= ~0x01; break;
    default: return;
    }

    if (uart_dma_rx_callbacks[index])
        uart_dma_rx_callbacks[index]();
}

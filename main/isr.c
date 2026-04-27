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
 * 文件名：isr.c
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
#include "ky_headfile.h"
#include "usb.h"


//=============================================================================
// 定时器中断
//=============================================================================
void Timer0_Isr(void) interrupt TMR0_VECTOR
{
    timer_isr_handler(TIM_0);
}

void Timer1_Isr(void) interrupt TMR1_VECTOR
{
    timer_isr_handler(TIM_1);
}

void Timer2_Isr(void) interrupt TMR2_VECTOR
{
    timer_isr_handler(TIM_2);
}

void Timer3_Isr(void) interrupt TMR3_VECTOR
{
    timer_isr_handler(TIM_3);
}

void Timer4_Isr(void) interrupt TMR4_VECTOR
{
    timer_isr_handler(TIM_4);
}

//=============================================================================
// UART 串口中断
//=============================================================================
void UART1_Isr(void) interrupt UART1_VECTOR
{
    uart_isr_handler(UART_1);
}

void UART2_Isr(void) interrupt UART2_VECTOR
{
    uart_isr_handler(UART_2);
}

void UART3_Isr(void) interrupt UART3_VECTOR
{
    uart_isr_handler(UART_3);
}

void UART4_Isr(void) interrupt UART4_VECTOR
{
    uart_isr_handler(UART_4);
}

void UART5_Isr(void) interrupt UART5_VECTOR
{
    uart_isr_handler(UART_5);
}

void UART6_Isr(void) interrupt UART6_VECTOR
{
    uart_isr_handler(UART_6);
}

void UART7_Isr(void) interrupt UART7_VECTOR
{
    uart_isr_handler(UART_7);
}

void UART8_Isr(void) interrupt UART8_VECTOR
{
    uart_isr_handler(UART_8);
}

//=============================================================================
// GPIO 中断
//=============================================================================
void P0_Isr(void) interrupt P0INT_VECTOR
{
    gpio_isr_handler(0);
}

void P1_Isr(void) interrupt P1INT_VECTOR
{
    gpio_isr_handler(1);
}

void P2_Isr(void) interrupt P2INT_VECTOR
{
    gpio_isr_handler(2);
}

void P3_Isr(void) interrupt P3INT_VECTOR
{
    gpio_isr_handler(3);
}

void P4_Isr(void) interrupt P4INT_VECTOR
{
    gpio_isr_handler(4);
}

void P5_Isr(void) interrupt P5INT_VECTOR
{
    gpio_isr_handler(5);
}

void P6_Isr(void) interrupt P6INT_VECTOR
{
    gpio_isr_handler(6);
}

void P7_Isr(void) interrupt P7INT_VECTOR
{
    gpio_isr_handler(7);
}

//=============================================================================
// DMA UART 中断
//=============================================================================
void DMA_UART1TX_Isr(void) interrupt DMA_UR1T_VECTOR
{
    uart_dma_tx_isr_handler(UART_1);
}

void DMA_UART1RX_Isr(void) interrupt DMA_UR1R_VECTOR
{
    uart_dma_rx_isr_handler(UART_1);
}

void DMA_UART2TX_Isr(void) interrupt DMA_UR2T_VECTOR
{
    uart_dma_tx_isr_handler(UART_2);
}

void DMA_UART2RX_Isr(void) interrupt DMA_UR2R_VECTOR
{
    uart_dma_rx_isr_handler(UART_2);
}

void DMA_UART3TX_Isr(void) interrupt DMA_UR3T_VECTOR
{
    uart_dma_tx_isr_handler(UART_3);
}

void DMA_UART3RX_Isr(void) interrupt DMA_UR3R_VECTOR
{
    uart_dma_rx_isr_handler(UART_3);
}

void DMA_UART4TX_Isr(void) interrupt DMA_UR4T_VECTOR
{
    uart_dma_tx_isr_handler(UART_4);
}

void DMA_UART4RX_Isr(void) interrupt DMA_UR4R_VECTOR
{
    uart_dma_rx_isr_handler(UART_4);
}

void DMA_UART5TX_Isr(void) interrupt DMA_UR5T_VECTOR
{
    uart_dma_tx_isr_handler(UART_5);
}

void DMA_UART5RX_Isr(void) interrupt DMA_UR5R_VECTOR
{
    uart_dma_rx_isr_handler(UART_5);
}

void DMA_UART6TX_Isr(void) interrupt DMA_UR6T_VECTOR
{
    uart_dma_tx_isr_handler(UART_6);
}

void DMA_UART6RX_Isr(void) interrupt DMA_UR6R_VECTOR
{
    uart_dma_rx_isr_handler(UART_6);
}

void DMA_UART7TX_Isr(void) interrupt DMA_UR7T_VECTOR
{
    uart_dma_tx_isr_handler(UART_7);
}

void DMA_UART7RX_Isr(void) interrupt DMA_UR7R_VECTOR
{
    uart_dma_rx_isr_handler(UART_7);
}

void DMA_UART8TX_Isr(void) interrupt DMA_UR8T_VECTOR
{
    uart_dma_tx_isr_handler(UART_8);
}

void DMA_UART8RX_Isr(void) interrupt DMA_UR8R_VECTOR
{
    uart_dma_rx_isr_handler(UART_8);
}

//=============================================================================
// USB 中断
//=============================================================================
void USB_Isr(void) interrupt USB_VECTOR
{
    usb_isr_handler();
}

//=============================================================================
// MT9V034 摄像头中断
//=============================================================================
// LCM DMA 传输完成中断
void LCM_Isr(void) interrupt 58
{
    mt9v034_lcm_isr();
}

// VSYNC 场同步信号中断 (INT1)
void INT1_Isr(void) interrupt 2
{
    mt9v034_vsync_isr();
}


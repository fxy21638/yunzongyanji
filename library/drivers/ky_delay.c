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
 * 文件名：[ky_delay.c]
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
#include "ky_delay.h"
#include "stc32g144k246.h"
#include "ky_system_clock.h"

/***************************************************************
  *  @brief     微秒级延时
  *  @param     us  延时时长
 **************************************************************/
void delay_us(uint32_t us)
{
    uint8_t freq_div;
    uint16_t period_temp;
    uint16_t temp;
    uint32_t period;

    if (us == 0) return;

    // 计算总周期数
    period = (uint32_t)us * (system_clock_freq / 1000000UL);

    T11CR = 0; // 清除控制寄存器
    
    if (period > (255UL * 65535UL))
    {
        // 设置定时器为12T模式防止溢出
        period = (period + 5) / 12;  
        T11CR &= ~0x10; // Bit 4 = 0 for 12T
    }
    else
    {
        // 设置为1T模式
        T11CR |= 0x10;  // Bit 4 = 1 for 1T
    }
    
    freq_div = (uint8_t)(period >> 16);             // 计算预分频
    period_temp = (uint16_t)(period / (freq_div + 1));      // 计算自动重装载值
    temp = (uint16_t)65535 - period_temp;

    T11PS = freq_div;                               // 设置分频值
    T11L = (uint8_t)temp;
    T11H = (uint8_t)(temp >> 8);
    
    T11CR |= 0x80;                                  // 启动定时器 (Bit 7 = 1)
    
    while(!(T11CR & 0x01));                         // 等待硬件定时器溢出 (Bit 0)
    
    T11CR = 0;                                      // 关闭定时器并清除标志
}

/***************************************************************
  *  @brief     毫秒级延时
  *  @param     ms  延时时长
  *  @Sample usage:     delay_ms(100);
 **************************************************************/
void delay_ms(uint32_t ms)
{
    while(ms--)
    {
        delay_us(1000);
    }
}

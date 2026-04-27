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
 * 文件名：[ky_timer.c]
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
#include "ky_timer.h"
#include "ky_system_clock.h"
#include "stc32g144k246.h"

TimerCallback_t TimerCallbacks[5] = {0};

static void timer_calc_params(uint32_t time_us, uint8_t *psc, uint16_t *reload)
{
    uint32_t total_ticks;
    uint32_t prescaler;
    uint32_t reload_val;

    total_ticks = (uint32_t)((double)time_us * (system_clock_freq / 1000000.0));

    if (total_ticks <= 65536)
    {
        prescaler = 0;
    }
    else
    {
        prescaler = total_ticks / 65536;
        if (prescaler > 255)
            prescaler = 255;
    }

    reload_val = 65536UL - (total_ticks / (prescaler + 1));

    *psc = (uint8_t)prescaler;
    *reload = (uint16_t)reload_val;
}

/***************************************************************
 *  @brief     定时器初始化
 *  @param     tim       选择定时器 (TIM_0 ~ TIM_4)
 *  @param     time_us   定时时间，单位微秒(us)。
 *  @param     cb        中断回调函数
 **************************************************************/
void timer_init(TIM_Channel_t tim, uint32_t time_us, TimerCallback_t cb)
{
    uint8_t psc;
    uint16_t rld;

    // 参数检查：定时器索引有效性 (TIM_0 ~ TIM_4)
    KY_ASSERT(tim >= TIM_0 && tim <= TIM_4);
    // 参数检查：时间有效性
    KY_ASSERT(time_us > 0);

    if (tim <= TIM_4)
        TimerCallbacks[tim] = cb;

    timer_calc_params(time_us, &psc, &rld);

    switch (tim)
    {
    case TIM_0:
        // 配置 T0: 1T模式, 模式0(16位自动重装)
        AUXR |= 0x80;
        TMOD &= 0xF0;

        TM0PS = psc;
        TL0 = (uint8_t)(rld & 0xFF);
        TH0 = (uint8_t)(rld >> 8);

        TF0 = 0;
        TR0 = 1;
        ET0 = 1; // 清标志, 启动, 开中断
        break;

    case TIM_1:
        AUXR |= 0x40;
        TMOD &= 0x0F;

        TM1PS = psc;
        TL1 = (uint8_t)(rld & 0xFF);
        TH1 = (uint8_t)(rld >> 8);

        TF1 = 0;
        TR1 = 1;
        ET1 = 1;
        break;

    case TIM_2:
        AUXR |= 0x04;

        TM2PS = psc;
        T2L = (uint8_t)(rld & 0xFF);
        T2H = (uint8_t)(rld >> 8);

        AUXR |= 0x10;
        IE2 |= 0x04;
        break;

    case TIM_3:
        T4T3M |= 0x02;
        T4T3M &= ~0x04;

        TM3PS = psc;
        T3L = (uint8_t)(rld & 0xFF);
        T3H = (uint8_t)(rld >> 8);

        T4T3M |= 0x08;
        IE2 |= 0x20;
        break;

    case TIM_4:
        T4T3M |= 0x20;
        T4T3M &= ~0x40;

        TM4PS = psc;
        T4L = (uint8_t)(rld & 0xFF);
        T4H = (uint8_t)(rld >> 8);

        T4T3M |= 0x80; // T4R=1
        IE2 |= 0x40;   // ET4=1
        break;
    }
}

//=============================================================================
// 中断处理逻辑
//=============================================================================

void timer_isr_handler(TIM_Channel_t tim)
{
    if (tim < 5 && TimerCallbacks[tim])
    {
        TimerCallbacks[tim]();
    }
}

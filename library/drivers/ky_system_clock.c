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
 * 文件名：[ky_system_clock.c]
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

#include "ky_system_clock.h"
#include "stc32g144k246.h"
#include "ky_delay.h"
#include "ky_usb_cdc.h"

uint32_t system_clock_freq = IRC_24MHZ;

static void _delay_for_stable(void) 
{
    unsigned long i = 299998UL;
    _nop_();
    _nop_();
    while (i--)
        ;
}

/*********************************************************************************
 *  @brief     初始化系统时钟
 *  @param     clock 目标时钟频率，使用 SYS_CLK_xxMHZ 宏
 *  @return    无
 *  @note      使用内部 24MHz IRC 作为时钟源，通过 PLL 倍频到目标频率
 *********************************************************************************/
void system_clock_init(uint32_t clock) 
{
    EAXFR = 1;
	
	if (clock == SYS_CLK_120MHZ_HIRC)
	{
		WTST = 3;
		HPLLCR &= ~0x10;    //选择HPLL输入时钟源为HIRC
		HPLLPDIV = 4;
		HPLLCR |= 0x0e;      //HPLL=6MHz*80=480MHz
	//    HPLLCR |= 0x0f;      //HPLL=6MHz*82=492MHz
		
		HPLLCR |= 0x80;     //使能HPLL
		CLKDIV = 2;         //系统时钟=主时钟源/2
		CLKSEL = 0x04;      //选择HPLL/2作为主时钟源
		system_clock_freq = clock - 1;
		EA = 1;

		usb_cdc_init();
        return;
	}
	VRTRIM = CHIPID22;		    // 载入27MHz频段的VRTRIM值
	IRTRIM = CHIPID12;		    // 指定当前HIRC为24MHz
	
    // 24MHz 不使用 PLL，直接用 HIRC
    if (clock <= SYS_CLK_24MHZ) {
        WTST = 0;
        CLKDIV = 0;
        HIRCCR |= 0x80;
        while (!(HIRCCR & 0x01));
        CLKSEL &= ~0x03;
        system_clock_freq = SYS_CLK_24MHZ;
        EA = 1;
        usb_cdc_init();
        return;
    }
    
    // 设置 Flash 等待周期
    if (clock >= 120000000UL)
        WTST = 3;
    else if (clock >= 80000000UL)
        WTST = 3;
    else if (clock >= 48000000UL)
        WTST = 2;
    else
        WTST = 1;

    CLKDIV = 2;                 // 系统时钟 = HPLL / 2 / 2
    
    IRCBAND &= ~0x03;
    IRCBAND |= 0x01;            // 选择27MHz频段
    
    HPLLCR &= ~0x10;            // 选择HPLL输入时钟源为HIRC
    HPLLPDIV = 4;               
    HPLLCR &= ~0x0F;            // 清空倍频系数
    HPLLCR |= (clock / 3000000UL - 26) & 0x0F;  // HPLLDIV = SysClock/3 - 26
    HPLLCR |= 0x80;             // 使能HPLL
    
    _delay_for_stable();
    
    CLKSEL &= ~0x03;            // BASE_CLK选择HIRC
    CLKSEL &= ~0x0C;            // 清空主时钟源选择
    CLKSEL |= (1 << 2);         // 主时钟源为 HPLL1 输出 / 2
    
    system_clock_freq = clock;

    

    EA = 1;

	usb_cdc_init();
}



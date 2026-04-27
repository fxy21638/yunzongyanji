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
 * 文件名：[ky_timer.h]
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
#ifndef __KY_TIMER_H__
#define __KY_TIMER_H__

#include "ky_typedef.h"

typedef enum { 
    TIM_0 = 0, 
	TIM_1, 
	TIM_2, 
	TIM_3, 
	TIM_4 
} TIM_Channel_t;

typedef void (*TimerCallback_t)(void);

extern TimerCallback_t TimerCallbacks[5];

// 初始化定时器
void timer_init(TIM_Channel_t tim, uint32_t time_us, TimerCallback_t cb);

// 定时器初始化，毫秒级
#define timer_init_ms(tim, time_ms, cb) timer_init(tim, time_ms * 1000, cb)

// 定时器中断处理函数
void timer_isr_handler(TIM_Channel_t tim);

#endif

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
 * 文件名：[ky_system_clock.h]
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
#ifndef __KY_SYSTEM_CLOCK_H__
#define __KY_SYSTEM_CLOCK_H__

#include "ky_typedef.h"

#define SYS_CLK_24MHZ 24000000UL
#define SYS_CLK_48MHZ 48000000UL
#define SYS_CLK_72MHZ 72000000UL
#define SYS_CLK_96MHZ 96000000UL
#define SYS_CLK_99MHZ 99000000UL
#define SYS_CLK_102MHZ 102000000UL
#define SYS_CLK_120MHZ 120000000UL
#define SYS_CLK_120MHZ_HIRC 120000001UL

#define IRC_24MHZ 24000000UL

extern uint32_t system_clock_freq;

// 初始化系统时钟
void system_clock_init(uint32_t clock);

#endif

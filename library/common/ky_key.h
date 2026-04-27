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
 * 文件名：[ky_key.h]
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
 * 2026.01.05 |   xiao   | V1.0 
 *********************************************************************************/
#ifndef __KY_KEY_H__
#define __KY_KEY_H__

#include "ky_typedef.h"
#include "ky_gpio.h"

#define KEY_MAX_NUM             4       // 最大支持按键数量
#define KEY_DEBOUNCE_TIME       20      // 消抖时间(ms)
#define KEY_LONG_PRESS_TIME     800     // 长按时间(ms)

typedef enum {
    KEY_ACTIVE_LOW = 0,     // 低电平有效(按下为低)
    KEY_ACTIVE_HIGH = 1     // 高电平有效(按下为高)
} Key_ActiveLevel_t;

typedef enum {
    KEY_STATE_IDLE = 0,     // 空闲(未按下)
    KEY_STATE_PRESSED,      // 短按中
    KEY_STATE_LONG_PRESSED  // 长按中
} Key_State_t;

// 初始化按键
void key_init(uint8_t key_id, GPIO_Pin_t pin, Key_ActiveLevel_t active_level);
// 按键扫描 (需周期性调用)
void key_scan(uint8_t scan_period_ms);
// 获取按键状态
Key_State_t key_get_state(uint8_t key_id);
// 检查按键是否按下
uint8_t key_is_pressed(uint8_t key_id);
// 检查按键是否长按
uint8_t key_is_long_pressed(uint8_t key_id);

#endif

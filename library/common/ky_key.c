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
 * 文件名：[ky_key.c]
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
#include "ky_key.h"

typedef struct {
    GPIO_Pin_t pin;                 // GPIO引脚
    Key_ActiveLevel_t active_level; // 有效电平
    Key_State_t state;              // 当前状态
    uint8_t filter_cnt;             // 消抖计数器
    uint16_t hold_time;             // 按住时间计数
    uint8_t retain_cnt;             // 状态保持计数
} Key_t;

static Key_t _keys[KEY_MAX_NUM];
static uint8_t _key_count = 0;

/*********************************************************************************
 *  @brief     读取按键原始电平状态
 *  @param     key_id    按键ID
 *  @return    1=按下, 0=未按下
 *********************************************************************************/
static uint8_t _key_read_raw(uint8_t key_id)
{
    uint8_t level;
    if (key_id >= _key_count) return 0;
    
    level = gpio_read_pin(_keys[key_id].pin);
    
    if (_keys[key_id].active_level == KEY_ACTIVE_LOW)
        return (level == 0) ? 1 : 0;
    else
        return (level != 0) ? 1 : 0;
}

/*********************************************************************************
 *  @brief     初始化按键
 *  @param     key_id        按键ID (0 ~ KEY_MAX_NUM-1)
 *  @param     pin           GPIO引脚
 *  @param     active_level  有效电平
 *  @return    无
 *********************************************************************************/
void key_init(uint8_t key_id, GPIO_Pin_t pin, Key_ActiveLevel_t active_level)
{
    if (key_id >= KEY_MAX_NUM) return;
    
    // 根据有效电平配置GPIO输入模式
    if (active_level == KEY_ACTIVE_LOW)
        gpio_init(pin, GPIO_MODE_IN_PU, GPIO_HIGH);     // 低有效用上拉
    else
        gpio_init(pin, GPIO_MODE_IN_PD, GPIO_LOW);      // 高有效用下拉
    
    _keys[key_id].pin = pin;
    _keys[key_id].active_level = active_level;
    _keys[key_id].state = KEY_STATE_IDLE;
    _keys[key_id].filter_cnt = 0;
    _keys[key_id].hold_time = 0;
    _keys[key_id].retain_cnt = 0;
    
    if (key_id >= _key_count)
        _key_count = key_id + 1;
}

/*********************************************************************************
 *  @brief     按键扫描(需周期性调用)
 *  @param     scan_period_ms  扫描周期(毫秒)
 *  @return    无
 *********************************************************************************/
void key_scan(uint8_t scan_period_ms)
{
    uint8_t i;
    uint8_t pressed;
    Key_t *key;
    
    for (i = 0; i < _key_count; i++) {
        key = &_keys[i];
        pressed = _key_read_raw(i);
        
        if (pressed) {
            // 按键按下
            // 如果有残留的保持状态，立即清除
            key->retain_cnt = 0; 
            
            if (key->filter_cnt < KEY_DEBOUNCE_TIME) {
                key->filter_cnt += scan_period_ms;
            } else {
                // 消抖完成，累计按住时间
                key->hold_time += scan_period_ms;
                
                // 检测长按 - 长按达到时间立即触发
                if (key->hold_time >= KEY_LONG_PRESS_TIME)
                    key->state = KEY_STATE_LONG_PRESSED;
            }
        } else {
            // 按键松开
            if (key->state == KEY_STATE_LONG_PRESSED) {
                // 长按释放，恢复空闲
                key->state = KEY_STATE_IDLE;
                key->retain_cnt = 0;
            }
            else if (key->hold_time >= KEY_DEBOUNCE_TIME) {
                // 短按释放 -> 触发按下状态
                key->state = KEY_STATE_PRESSED;
                // 设置保持计数 (例如保持5个周期，约50ms)
                key->retain_cnt = 5; 
            }
            else {
                // 处理状态保持
                if (key->retain_cnt > 0) {
                    key->retain_cnt--;
                    // 保持期间状态维持 KEY_STATE_PRESSED
                } else {
                    key->state = KEY_STATE_IDLE;
                }
            }
            
            // 清除按键相关的计数（但不清除 retain_cnt）
            key->filter_cnt = 0;
            key->hold_time = 0;
        }
    }
}

/*********************************************************************************
 *  @brief     获取按键状态
 *  @param     key_id    按键ID
 *  @return    按键状态
 *********************************************************************************/
/*********************************************************************************
 *  @brief     获取按键状态(读后清除短按状态)
 *  @param     key_id    按键ID
 *  @return    按键状态
 *********************************************************************************/
Key_State_t key_get_state(uint8_t key_id)
{
    Key_State_t state;
    if (key_id >= _key_count) return KEY_STATE_IDLE;
    
    state = _keys[key_id].state;
    
    // 如果是短按状态，读取后立即清除(消费事件)，不再等待保持时间结束
    if (state == KEY_STATE_PRESSED) {
        _keys[key_id].state = KEY_STATE_IDLE;
        _keys[key_id].retain_cnt = 0;
    }
    
    return state;
}

/*********************************************************************************
 *  @brief     检查按键是否按下
 *  @param     key_id    按键ID
 *  @return    1=按下, 0=未按下
 *********************************************************************************/
uint8_t key_is_pressed(uint8_t key_id)
{
	Key_State_t state;
    if (key_id >= _key_count) return 0;
	state = _keys[key_id].state;
	if (state == KEY_STATE_PRESSED) {
        _keys[key_id].state = KEY_STATE_IDLE;
        _keys[key_id].retain_cnt = 0;
        return 1;  // 短按事件，消费后清除
    }
    return 0;  // 不是短按状态（包括长按状态）
}

/*********************************************************************************
 *  @brief     检查按键是否长按
 *  @param     key_id    按键ID
 *  @return    1=长按中, 0=否
 *********************************************************************************/
uint8_t key_is_long_pressed(uint8_t key_id)
{
    if (key_id >= _key_count) return 0;
    return (_keys[key_id].state == KEY_STATE_LONG_PRESSED);
}

/*
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
 * 文件名：[ky_headfile.h]
 * 开发单位：北京科宇通博科技有限公司
 * 适用环境：[Keil MDK 5.36 / STC系列单片机]
 * 官方渠道：
 *   - 代码仓库：[https://gitee.com/beijing-keyu---jiangxi/KEYU_AI8052U_OpenLibrary]
 *   - 淘宝店铺：https://kyznc.taobao.com/
 *   - 技术支持：QQ群 974530818
 *
 * === 修订记录 ===
 * 日期       |  开发者  | 变更说明
 * -----------|----------|----------------------
 * 2025.12.22 |   xiao   | V2.0
 */
#ifndef __KY_HEADFILE_H__
#define __KY_HEADFILE_H__

#include <stdio.h>
#include <string.h>

// STC
#include "stc32g144k246.h"

// ------------------Devices------------------
// #include "ky_gnss.h"
#include "ky_icm45686.h"
#include "ky_icm42686.h"
#include "ky_imu_base.h"
#include "ky_ips.h"
#include "ky_lsm6dsr.h"
#include "ky_mt9v034.h"
#include "ky_mt9v034_config.h"
// ------------------Devices------------------

// ------------------Common------------------
#include "ky_assert.h"
#include "ky_font.h"
#include "ky_math.h"
#include "ky_ringbuffer.h"
#include "ky_utils.h"
#include "ky_key.h"
// ------------------Common------------------

// ------------------Core------------------
// #include "ky_macro.h"
// #include "ky_pin_config.h"
#include "ky_system_clock.h"
#include "ky_typedef.h"
// ------------------Core------------------

// ------------------Drivers------------------
#include "ky_adc.h"
#include "ky_delay.h"
#include "ky_encoder.h"
#include "ky_gpio.h"
#include "ky_pwm.h"
#include "ky_soft_i2c.h"
#include "ky_spi.h"
#include "ky_timer.h"
#include "ky_uart.h"
#include "ky_usb_cdc.h"
#include "ky_wireless_com.h"
// ------------------Drivers------------------

#endif

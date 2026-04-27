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
 * 文件名：[ky_utils.h]
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

#ifndef __KY_UTILS_H__
#define __KY_UTILS_H__

#include "ky_typedef.h"

// 整数转字符串
uint8_t utils_int2str(int32_t num, char *buf);
// 无符号整数转字符串
uint8_t utils_uint2str(uint32_t num, char *buf);
// 浮点数转字符串
uint8_t utils_float2str(float num, char *buf, uint8_t frac_len);
// 计算10的n次幂
uint32_t utils_pow10(uint8_t n);

#include "ky_math.h"

#define utils_strstr math_strstr
#define utils_atoi math_atoi
#define utils_atof math_atof

#endif /* __KY_UTILS_H__ */

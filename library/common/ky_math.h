/*************************************************************************************
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
 * 文件名：[ky_math.h]
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
 **************************************************************************************/

#ifndef __KY_MATH_H__
#define __KY_MATH_H__

#include "ky_typedef.h"
#include <math.h>

/***************************************************************
 *  @brief     数学常量定义
 **************************************************************/
#define KY_MATH_PI 3.14159265358979323846
#define KY_MATH_PI_F 3.14159265f
#define KY_MATH_2PI 6.28318530717958647692
#define KY_MATH_E 2.71828182845904523536

#define ky_sin(x) sin(x)
#define ky_cos(x) cos(x)
#define ky_tan(x) tan(x)
#define ky_asin(x) asin(x)
#define ky_acos(x) acos(x)
#define ky_atan(x) atan(x)
#define ky_atan2(y, x) atan2(y, x)
#define ky_sqrt(x) sqrt(x)
#define ky_pow(x, y) pow(x, y)
#define ky_exp(x) exp(x)
#define ky_log(x) log(x)
#define ky_fabs(x) fabs(x)
#define ky_floor(x) floor(x)
#define ky_ceil(x) ceil(x)

#define ky_sinf(x) sinf(x)
#define ky_cosf(x) cosf(x)
#define ky_tanf(x) tanf(x)
#define ky_sqrtf(x) sqrtf(x)
#define ky_fabsf(x) fabsf(x)

// 计算两个参数的反正切值
float math_atan2(float y, float x);

// 计算浮点数绝对值
float math_fabs(float x);

// 快速求平方根倒数
float math_inv_sqrt(float x);

// 角度转弧度
float math_deg_to_rad(float deg);

// 弧度转角度
float math_rad_to_deg(float rad);

// 在字符串中查找子串
char *math_strstr(const char *s1, const char *s2);

// 字符串转整数
int math_atoi(const char *str);

// 字符串转浮点数
float math_atof(const char *str);

#endif /* __KY_MATH_H__ */

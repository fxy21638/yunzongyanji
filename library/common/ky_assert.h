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
 * 文件名：ky_assert.h
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
 * 2026.01.09 |   xiao   | V1.0 
 *********************************************************************************/

#ifndef __KY_ASSERT_H__
#define __KY_ASSERT_H__

#include "ky_typedef.h"


/**
 * @brief 断言系统总开关
 * @note 1=启用断言, 0=禁用断言
 */
#ifndef KY_ASSERT_ENABLE
    #define KY_ASSERT_ENABLE 1
#endif


#if KY_ASSERT_ENABLE

/**
 * @brief 断言宏 - 条件为假时触发
 * @param expr 要检查的表达式
 */
#define KY_ASSERT(expr) \
    do { \
        if (!(expr)) { \
            ky_assert_fail(__FILE__, __LINE__); \
        } \
    } while(0)

/**
 * @brief 断言宏 - 条件为假时触发，并显示自定义信息
 * @param expr 要检查的表达式
 * @param info 自定义信息字符串
 */
#define KY_ASSERT_INFO(expr, info) \
    do { \
        if (!(expr)) { \
            ky_assert_fail_info(__FILE__, __LINE__, info); \
        } \
    } while(0)

#else
    #define KY_ASSERT(expr) ((void)0)
    #define KY_ASSERT_INFO(expr, info) ((void)0)

#endif


// 断言失败处理函数
void ky_assert_fail(const char *file, int line);
void ky_assert_fail_info(const char *file, int line, const char *info);

#endif /* __KY_ASSERT_H__ */

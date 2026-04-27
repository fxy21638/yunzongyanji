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
 * 文件名：ky_assert.c
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

#include "ky_assert.h"
#include <stdio.h>
#include <string.h>
#include "ky_ips.h"
extern void delay_ms(uint32_t ms);
extern void ips_show_string(uint16_t x, uint16_t y, const char *str);

/**************************************************************
 * @brief 断言失败处理函数
 * @param file    文件名
 * @param line    行号
 **************************************************************/
void ky_assert_fail(const char *file, int line)
{
    char buf[128];
		ips_clear(COLOR_WHITE);
    ips_show_string(0, 0, "ASSERT Failed!");

    // 显示文件名
    {
        const char *p = file;
        const char *last_slash = file;
        while (*p) {
            if (*p == '/' || *p == '\\') {
                last_slash = p + 1;
            }
            p++;
        }
        ips_show_string(0, 16, last_slash);
    }
    // 行号
    {
        int n = line;
        char temp[16];
        int i = 0;
        int j = 0;
        if (n == 0) {
            buf[0] = '0';
            buf[1] = '\0';
        } else {
            while (n > 0) {
                temp[i++] = '0' + (n % 10);
                n /= 10;
            }
            for (j = 0; j < i; j++) {
                buf[j] = temp[i - 1 - j];
            }
            buf[i] = '\0';
        }
    }
    ips_show_string(0, 32, "Line: ");
    ips_show_string(40, 32, buf);

    while (1) {
        printf("ASSERT Failed!\r\n");
        printf("File: %s, Line: %d\r\n", file, line);
        delay_ms(500);
    }
}

/**************************************************************
 * @brief 断言失败处理函数（带自定义信息）
 * @param file    文件名
 * @param line    行号
 * @param info    自定义信息字符串
 **************************************************************/
void ky_assert_fail_info(const char *file, int line, const char *info)
{
    char buf[128];

    ips_show_string(0, 0, "ASSERT Failed!");

    // 显示文件名
    {
        const char *p = file;
        const char *last_slash = file;
        while (*p) {
            if (*p == '/' || *p == '\\') {
                last_slash = p + 1;
            }
            p++;
        }
        ips_show_string(0, 16, last_slash);
    }
    // 行号
    {
        int n = line;
        char temp[16];
        int i = 0;
        int j = 0;
        if (n == 0) {
            buf[0] = '0';
            buf[1] = '\0';
        } else {
            while (n > 0) {
                temp[i++] = '0' + (n % 10);
                n /= 10;
            }
            for (j = 0; j < i; j++) {
                buf[j] = temp[i - 1 - j];
            }
            buf[i] = '\0';
        }
    }
    ips_show_string(0, 32, "Line: ");
    ips_show_string(40, 32, buf);

    // 显示自定义信息
    ips_show_string(0, 48, info);

    while (1) {
        printf("ASSERT Failed!\r\n");
        printf("File: %s, Line: %d\r\n", file, line);
        printf("Info: %s\r\n", info);
        delay_ms(500);
    }
}

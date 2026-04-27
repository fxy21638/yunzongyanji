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
 * 文件名：[ky_utils.c]
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

#include "ky_utils.h"

/***************************************************************
 *  @brief     快速计算 10^N
 **************************************************************/
uint32_t utils_pow10(uint8_t n)
{
    uint32_t r = 1;
    while (n--)
        r *= 10;
    return r;
}

/***************************************************************
 *  @brief     整数转字符串 (有符号)
 **************************************************************/
uint8_t utils_int2str(int32_t num, char *buf)
{
    char temp[12];
    uint8_t i = 0, j = 0;
    uint8_t is_neg = 0;

    if (num == 0)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return 1;
    }

    if (num < 0)
    {
        is_neg = 1;
        num = -num;
    }

    while (num > 0)
    {
        temp[i++] = (num % 10) + '0';
        num /= 10;
    }

    if (is_neg)
        buf[j++] = '-';

    while (i > 0)
    {
        buf[j++] = temp[--i];
    }
    buf[j] = '\0';

    return j;
}

/***************************************************************
 *  @brief     整数转字符串 (无符号)
 **************************************************************/
uint8_t utils_uint2str(uint32_t num, char *buf)
{
    char temp[12];
    uint8_t i = 0, j = 0;

    if (num == 0)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return 1;
    }

    while (num > 0)
    {
        temp[i++] = (num % 10) + '0';
        num /= 10;
    }

    while (i > 0)
    {
        buf[j++] = temp[--i];
    }
    buf[j] = '\0';

    return j;
}

/***************************************************************
 *  @brief     浮点数转字符串
 **************************************************************/
uint8_t utils_float2str(float num, char *buf, uint8_t frac_len)
{
    int32_t int_part;
    uint32_t frac_part;
    uint32_t multiplier;
    uint8_t i, len = 0;

    if (num < 0)
    {
        buf[len++] = '-';
        num = -num;
    }

    int_part = (int32_t)num;
    multiplier = utils_pow10(frac_len);
    frac_part = (uint32_t)((num - int_part) * multiplier + 0.5f);

    if (frac_part >= multiplier)
    {
        int_part++;
        frac_part = 0;
    }

    if (int_part == 0)
    {
        buf[len++] = '0';
    }
    else
    {
        char temp[12];
        uint8_t k = 0;
        int32_t temp_int = int_part;
        while (temp_int > 0)
        {
            temp[k++] = (temp_int % 10) + '0';
            temp_int /= 10;
        }
        while (k > 0)
            buf[len++] = temp[--k];
    }

    if (frac_len > 0)
    {
        buf[len++] = '.';
        {
            char temp[10];
            uint32_t temp_frac = frac_part;
            for (i = 0; i < frac_len; i++)
            {
                temp[i] = (temp_frac % 10) + '0';
                temp_frac /= 10;
            }
            for (i = frac_len; i > 0; i--)
            {
                buf[len++] = temp[i - 1];
            }
        }
    }

    buf[len] = '\0';
    return len;
}

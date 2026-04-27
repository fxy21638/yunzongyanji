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
 * 文件名：[ky_math.c]
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

#include "ky_math.h"

/***************************************************************
 *  @brief     使用 atan 函数模拟实现的 atan2 函数
 *  @param     y       y坐标值
 *  @param     x       x坐标值
 *  @return    float   返回计算出的弧度值
 **************************************************************/
float math_atan2(float y, float x)
{
    float angle;

    if (x > 0.0f)
    {
        angle = (float)atan(y / x);
    }
    else if (x < 0.0f)
    {
        if (y >= 0.0f)
        {
            angle = (float)atan(y / x) + KY_MATH_PI;
        }
        else
        {
            angle = (float)atan(y / x) - KY_MATH_PI;
        }
    }
    else
    {
        if (y > 0.0f)
        {
            angle = KY_MATH_PI / 2.0f;
        }
        else if (y < 0.0f)
        {
            angle = -KY_MATH_PI / 2.0f;
        }
        else
        {
            angle = 0.0f;
        }
    }
    return angle;
}

/***************************************************************
 *  @brief     计算浮点数的绝对值
 **************************************************************/
float math_fabs(float x)
{
    return (x < 0.0f) ? -x : x;
}

/***************************************************************
 *  @brief     快速计算平方根的倒数 (1 / sqrt(x))
 *  @param     x       输入的正浮点数
 *  @return    float   返回 1 / sqrt(x) 的近似值
 **************************************************************/
float math_inv_sqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    int32_t i = *(int32_t *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

/***************************************************************
 *  @brief     将角度转换为弧度
 **************************************************************/
float math_deg_to_rad(float deg)
{
    return deg * (KY_MATH_PI / 180.0f);
}

/***************************************************************
 *  @brief     将弧度转换为角度
 **************************************************************/
float math_rad_to_deg(float rad)
{
    return rad * (180.0f / KY_MATH_PI);
}

/***************************************************************
 *  @brief     查找字符串子串
 **************************************************************/
char *math_strstr(const char *s1, const char *s2)
{
    const char *p1, *p2;

    if (!*s2)
        return (char *)s1;

    while (*s1)
    {
        p1 = s1;
        p2 = s2;
        while (*p1 && *p2 && (*p1 == *p2))
        {
            p1++;
            p2++;
        }
        if (!*p2)
            return (char *)s1;
        s1++;
    }
    return NULL;
}

/***************************************************************
 *  @brief     将字符串转换为整数
 **************************************************************/
int math_atoi(const char *str)
{
    int res = 0;
    int sign = 1;
    if (str == NULL)
        return 0;

    while (*str == ' ')
        str++;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + (*str - '0');
        str++;
    }
    return sign * res;
}

/***************************************************************
 *  @brief     将字符串转换为浮点数
 **************************************************************/
float math_atof(const char *str)
{
    float res = 0.0f;
    float frac = 1.0f;
    int sign = 1;
    int decimal = 0;
    if (str == NULL)
        return 0.0f;

    while (*str == ' ')
        str++;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    while ((*str >= '0' && *str <= '9') || *str == '.')
    {
        if (*str == '.')
        {
            decimal = 1;
            str++;
            continue;
        }
        if (!decimal)
        {
            res = res * 10.0f + (*str - '0');
        }
        else
        {
            frac *= 10.0f;
            res = res * 10.0f + (*str - '0');
        }
        str++;
    }
    if (decimal)
        res /= frac;
    return sign * res;
}

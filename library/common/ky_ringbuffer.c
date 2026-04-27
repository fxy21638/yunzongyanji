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
 * 文件名：[ky_ringbuffer.c]
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

#include "ky_ringbuffer.h"

/***************************************************************
 *  @brief     初始化环形缓冲区
 *  @param     rb          缓冲区结构体指针
 *  @param     buffer      外部分配的存储数组指针
 *  @param     size        缓冲区大小 (必须为 2 的幂次)
 *  @return    操作状态 (RINGBUFFER_SUCCESS 等)
 *  @Sample usage:     ringbuffer_init(&my_rb, buffer, 256);
 **************************************************************/
ringbuffer_state_t ringbuffer_init(RingBuffer_t *rb, uint8_t *buffer, uint32_t size)
{
    if (rb == NULL)
        return RINGBUFFER_ERROR;

    if (buffer == NULL)
        return RINGBUFFER_BUFFER_NULL;

    // 检查 size 是否为 2 的幂次 (size & (size - 1) 为 0)
    if (size == 0 || (size & (size - 1)) != 0)
        return RINGBUFFER_SIZE_INVALID;

    rb->buffer = buffer;
    rb->size = size;
    rb->mask = size - 1;
    rb->in = 0;
    rb->out = 0;

    return RINGBUFFER_SUCCESS;
}

/***************************************************************
 *  @brief     获取环形缓冲区已使用的长度
 *  @param     rb          缓冲区结构体指针
 *  @return    已存储数据的长度
 **************************************************************/
uint32_t ringbuffer_len(RingBuffer_t *rb)
{
    if (rb == NULL)
        return 0;
    return rb->in - rb->out;
}

/***************************************************************
 *  @brief     获取环形缓冲区剩余空间
 *  @param     rb          缓冲区结构体指针
 *  @return    剩余可写入数据的长度
 **************************************************************/
uint32_t ringbuffer_free(RingBuffer_t *rb)
{
    if (rb == NULL)
        return 0;
    return rb->size - ringbuffer_len(rb);
}

/***************************************************************
 *  @brief     检查缓冲区是否为空
 *  @param     rb          缓冲区结构体指针
 *  @return    1 为空，0 不为空
 **************************************************************/
uint8_t ringbuffer_is_empty(RingBuffer_t *rb)
{
    if (rb == NULL)
        return 1;
    return (rb->in == rb->out) ? 1 : 0;
}

/***************************************************************
 *  @brief     检查缓冲区是否已满
 *  @param     rb          缓冲区结构体指针
 *  @return    1 已满，0 未满
 **************************************************************/
uint8_t ringbuffer_is_full(RingBuffer_t *rb)
{
    if (rb == NULL)
        return 0;
    return (ringbuffer_len(rb) >= rb->size) ? 1 : 0;
}

/***************************************************************
 *  @brief     清空环形缓冲区
 *  @param     rb          缓冲区结构体指针
 **************************************************************/
void ringbuffer_clear(RingBuffer_t *rb)
{
    if (rb == NULL)
        return;
    rb->in = 0;
    rb->out = 0;
}

/***************************************************************
 *  @brief     向环形缓冲区写入数据
 *  @param     rb          缓冲区结构体指针
 *  @param     dat         要写入的数据源指针
 *  @param     len         写入长度
 *  @return    实际写入的长度
 **************************************************************/
uint32_t ringbuffer_write(RingBuffer_t *rb, void *dat, uint32_t len)
{
    uint32_t l, off;
    uint32_t unused;

    if (rb == NULL || dat == NULL || len == 0)
        return 0;

    unused = ringbuffer_free(rb);
    if (len > unused)
        len = unused;

    // 计算当前写入偏移 (取模)
    off = rb->in & rb->mask;

    // 第一段长度：到物理末尾的距离
    l = MIN(len, rb->size - off);

    memcpy(rb->buffer + off, dat, (uint16_t)l);

    // 如果还没写完，绕回头部写第二段
    if (len > l)
        memcpy(rb->buffer, (uint8_t *)dat + l, (uint16_t)(len - l));

    rb->in += len;

    return len;
}

/***************************************************************
 *  @brief     从环形缓冲区读取数据 (读后删除)
 *  @param     rb          缓冲区结构体指针
 *  @param     target      保存数据的目标地址
 *  @param     len         读取长度
 *  @return    实际读取的长度
 **************************************************************/
uint32_t ringbuffer_read(RingBuffer_t *rb, void *target, uint32_t len)
{
    uint32_t l, off;
    uint32_t available;

    if (rb == NULL || target == NULL || len == 0)
        return 0;

    available = ringbuffer_len(rb);
    if (len > available)
        len = available;

    // 计算当前读取偏移 (取模)
    off = rb->out & rb->mask;

    l = MIN(len, rb->size - off);

    memcpy(target, rb->buffer + off, (uint16_t)l);

    if (len > l)
        memcpy((uint8_t *)target + l, rb->buffer, (uint16_t)(len - l));

    rb->out += len;

    return len;
}

/***************************************************************
 *  @brief     从环形缓冲区查看数据 (只读不删除)
 *  @param     rb          缓冲区结构体指针
 *  @param     target      保存数据的目标地址
 *  @param     len         查看长度
 *  @return    实际查看的长度
 **************************************************************/
uint32_t ringbuffer_peek(RingBuffer_t *rb, void *target, uint32_t len)
{
    uint32_t l, off;
    uint32_t available;

    if (rb == NULL || target == NULL || len == 0)
        return 0;

    available = ringbuffer_len(rb);
    if (len > available)
        len = available;

    off = rb->out & rb->mask;
    l = MIN(len, rb->size - off);

    memcpy(target, rb->buffer + off, (uint16_t)l);

    if (len > l)
        memcpy((uint8_t *)target + l, rb->buffer, (uint16_t)(len - l));

    return len;
}

/***************************************************************
 *  @brief     丢弃环形缓冲区中指定长度的数据
 *  @param     rb          缓冲区结构体指针
 *  @param     len         丢弃长度
 *  @return    实际丢弃的长度
 **************************************************************/
uint32_t ringbuffer_discard(RingBuffer_t *rb, uint32_t len)
{
    uint32_t available;
    if (rb == NULL)
        return 0;

    available = ringbuffer_len(rb);
    if (len > available)
        len = available;

    rb->out += len;
    return len;
}

/***************************************************************
 *  @brief     写入一个字节
 *  @param     rb          缓冲区结构体指针
 *  @param     dat         要写入的字节数据
 *  @return    1 成功，0 失败 (满)
 **************************************************************/
uint8_t ringbuffer_putc(RingBuffer_t *rb, uint8_t dat)
{
    if (rb == NULL || ringbuffer_is_full(rb))
        return 0;

    rb->buffer[rb->in & rb->mask] = dat;
    rb->in++;
    return 1;
}

/***************************************************************
 *  @brief     读取一个字节
 *  @param     rb          缓冲区结构体指针
 *  @param     dat         保存读取字节的指针
 *  @return    1 成功，0 失败 (空)
 **************************************************************/
uint8_t ringbuffer_getc(RingBuffer_t *rb, uint8_t *dat)
{
    if (rb == NULL || dat == NULL || ringbuffer_is_empty(rb))
        return 0;

    *dat = rb->buffer[rb->out & rb->mask];
    rb->out++;
    return 1;
}

/***************************************************************
 *  @brief     查看一个字节但不移除
 *  @param     rb          缓冲区结构体指针
 *  @param     dat         保存查看字节的指针
 *  @return    1 成功，0 失败 (空)
 **************************************************************/
uint8_t ringbuffer_peekc(RingBuffer_t *rb, uint8_t *dat)
{
    if (rb == NULL || dat == NULL || ringbuffer_is_empty(rb))
        return 0;

    *dat = rb->buffer[rb->out & rb->mask];
    return 1;
}

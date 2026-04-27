/*
 * 项目名称：[AI8052U开源库] 开源组件库
 * 版权所有：[2025] [北京科宇通博科技有限公司江西分公司]
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
 * 文件名：[ky_ringbuffer.h]
 * 开发单位：北京科宇通博科技有限公司江西分公司
 * 适用环境：[Keil MDK 5.36 / STC系列单片机]
 * 官方渠道：
 *   - 代码仓库：[https://gitee.com/xiao_repository/AI8052U_OpenLibrary]
 *   - 淘宝店铺：https://kyznc.taobao.com/
 *   - 技术支持：QQ群 974530818
 *
 * === 修订记录 ===
 * 日期       |  开发者  | 变更说明
 * -----------|----------|----------------------
 * 2025.12.22 |   xiao   | V2.0
 */
#ifndef __KY_RING_BUFFER_H__
#define __KY_RING_BUFFER_H__

#include "ky_typedef.h"
#include <string.h>

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

// 环形缓冲区操作状态
typedef enum {
  RINGBUFFER_SUCCESS = 0, RINGBUFFER_ERROR, RINGBUFFER_SIZE_INVALID,
  RINGBUFFER_BUFFER_NULL, RINGBUFFER_EMPTY, RINGBUFFER_FULL,
  RINGBUFFER_NO_ENOUGH_DATA, RINGBUFFER_NO_ENOUGH_SPACE
} ringbuffer_state_t;

typedef struct {
  uint8_t *buffer;       // 实际缓冲区首地址
  uint32_t size;         // 缓冲区大小 (必须是 2的幂次)
  uint32_t mask;         // 掩码
  volatile uint32_t in;  // 写入位置
  volatile uint32_t out; // 读取位置
} RingBuffer_t;

// 初始化环形缓冲区
ringbuffer_state_t ringbuffer_init(RingBuffer_t *rb, uint8_t *buffer,
                                   uint32_t size);

// 获取环形缓冲区已使用的长度
uint32_t ringbuffer_len(RingBuffer_t *rb);

// 获取环形缓冲区剩余空间
uint32_t ringbuffer_free(RingBuffer_t *rb);

// 检查缓冲区是否为空
uint8_t ringbuffer_is_empty(RingBuffer_t *rb);

// 检查缓冲区是否已满
uint8_t ringbuffer_is_full(RingBuffer_t *rb);

// 清空环形缓冲区
void ringbuffer_clear(RingBuffer_t *rb);

// 向环形缓冲区写入数据
uint32_t ringbuffer_write(RingBuffer_t *rb, void *dat, uint32_t len);

// 从环形缓冲区读取数据 (读后删除)
uint32_t ringbuffer_read(RingBuffer_t *rb, void *target, uint32_t len);

// 从环形缓冲区查看数据 (只读不删除)
uint32_t ringbuffer_peek(RingBuffer_t *rb, void *target, uint32_t len);

// 丢弃环形缓冲区中指定长度的数据
uint32_t ringbuffer_discard(RingBuffer_t *rb, uint32_t len);

// 写入一个字节
uint8_t ringbuffer_putc(RingBuffer_t *rb, uint8_t dat);

// 读取一个字节
uint8_t ringbuffer_getc(RingBuffer_t *rb, uint8_t *dat);

// 查看一个字节但不移除
uint8_t ringbuffer_peekc(RingBuffer_t *rb, uint8_t *dat);

#endif /* __KY_RING_BUFFER_H__ */

/*********************************************************************************
 * 项目名称:[STC32G144K246开源库] 开源组件库
 * 版权所有:[2025] [北京科宇通博科技有限公司]
 *
 * 许可协议:采用 GNU GPL v3.0 开源许可
 * 您可依据协议进行二次开发、传播,但须保留原始版权信息
 * 协议详情参见:https://www.gnu.org/licenses/gpl-3.0.html
 *
 * 免责声明:本组件库仅提供技术参考,使用方需自行验证适用性
 *
 * 协议文件:GPL v3.0 完整文本位于根目录下
 *
 * === 文件信息 ===
 * 文件名:[ky_soft_i2c.h]
 * 开发单位:北京科宇通博科技有限公司
 * 适用环境:[Keil C251 / STC32G系列单片机]
 * 官方渠道:
 *   - 代码仓库:[https://gitee.com/beijing-keyu---jiangxi/KEYU_AI8052U_OpenLibrary]
 *   - 淘宝店铺:https://kyznc.taobao.com/
 *   - 技术支持:QQ群 974530818
 *
 * === 修订记录 ===
 * 日期       |  开发者  | 变更说明
 * -----------|----------|----------------------
 * 2025.12.22 |   xiao   | V2.0
 *********************************************************************************/
#ifndef __KY_SOFT_I2C_H__
#define __KY_SOFT_I2C_H__

#include "ky_gpio.h"
#include "ky_typedef.h"

typedef enum
{
    SOFT_I2C_SPEED_STANDARD = 0,   // 100 kHz 标准模式 (delay_us=5)
    SOFT_I2C_SPEED_FAST = 1,       // 400 kHz 快速模式 (delay_us=1)
    SOFT_I2C_SPEED_CUSTOM = 2      // 自定义速度（使用delay_us字段）
} soft_i2c_speed_t;

typedef struct
{
    GPIO_Pin_t scl_pin;       // SCL（串行时钟）引脚
    GPIO_Pin_t sda_pin;       // SDA（串行数据）引脚
    uint8_t dev_write_addr;   // 设备写地址（8位格式，已包含R/W位）
    uint8_t dev_read_addr;    // 设备读地址（8位格式，已包含R/W位）
    soft_i2c_speed_t speed;   // 时钟速度预设
    uint16_t delay_us;        // 半周期延迟时间（微秒）
                              // 对于100kHz: 使用5us (10us周期)
                              // 对于400kHz: 使用1us (约250kHz)
    uint8_t timeout_ms;       // 事务超时时间（毫秒），默认10
    uint8_t retries;          // 失败重试次数，默认3
} soft_i2c_config_t;

// 初始化软件I2C
void soft_i2c_init(soft_i2c_config_t *config);

// 写数据到I2C设备
// reg_addr: 寄存器地址指针（如果为NULL则不发送寄存器地址）
// dat: 要写入的数据缓冲区
// length: 要写入的字节数
// 返回: SUCCESS成功, ERROR失败
Status soft_i2c_write(soft_i2c_config_t *config, const uint8_t *reg_addr,
                      const uint8_t *dat, uint16_t length);

// 从I2C设备读数据
// reg_addr: 寄存器地址指针（如果为NULL则不发送寄存器地址）
// dat: 存储读取数据的缓冲区
// length: 要读取的字节数
// 返回: SUCCESS成功, ERROR失败
Status soft_i2c_read(soft_i2c_config_t *config, const uint8_t *reg_addr,
                     uint8_t *dat, uint16_t length);

// 写单字节到指定寄存器（便捷函数）
// reg_addr: 寄存器地址
// dat: 要写入的单字节数据
// 返回: SUCCESS成功, ERROR失败
Status soft_i2c_write_byte(soft_i2c_config_t *config, uint8_t reg_addr, uint8_t dat);

// 从指定寄存器读单字节（便捷函数）
// reg_addr: 寄存器地址
// dat: 指向存储读取字节的指针
// 返回: SUCCESS成功, ERROR失败
Status soft_i2c_read_byte(soft_i2c_config_t *config, uint8_t reg_addr, uint8_t *dat);

// 写16位数据到指定寄存器（高字节先发送）
// reg_addr: 寄存器地址
// dat: 要写入的16位数据
// 返回: SUCCESS成功, ERROR失败
Status soft_i2c_write_16bit(soft_i2c_config_t *config, uint8_t reg_addr, uint16_t dat);

// 从指定寄存器读16位数据（高字节先接收）
// reg_addr: 寄存器地址
// dat: 指向存储读取16位数据的指针
// 返回: SUCCESS成功, ERROR失败
Status soft_i2c_read_16bit(soft_i2c_config_t *config, uint8_t reg_addr, uint16_t *dat);

// 探测I2C设备是否存在
// 返回: SUCCESS设备存在, ERROR设备不存在或总线错误
Status soft_i2c_device_probe(soft_i2c_config_t *config);

#endif

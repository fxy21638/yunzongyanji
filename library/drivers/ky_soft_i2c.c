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
 * 文件名:[ky_soft_i2c.c]
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
#include "ky_soft_i2c.h"
#include "ky_delay.h"
#include "ky_gpio.h"
#include "ky_assert.h"

/*********************************************************************************
 *  @brief     设置SCL引脚电平（内部函数）
 *  @param     config    I2C配置指针
 *  @param     level     GPIO电平（GPIO_HIGH或GPIO_LOW）
 *********************************************************************************/
static void _soft_i2c_scl_set(soft_i2c_config_t *config, GPIO_Level_t level)
{
    gpio_write_pin(config->scl_pin, level);
}

/*********************************************************************************
 *  @brief     设置SDA引脚电平（内部函数）
 *  @param     config    I2C配置指针
 *  @param     level     GPIO电平（GPIO_HIGH或GPIO_LOW）
 *********************************************************************************/
static void _soft_i2c_sda_set(soft_i2c_config_t *config, GPIO_Level_t level)
{
    gpio_write_pin(config->sda_pin, level);
}

/*********************************************************************************
 *  @brief     读取SDA引脚电平（内部函数）
 *  @param     config    I2C配置指针
 *  @return    当前SDA引脚电平
 *********************************************************************************/
static GPIO_Level_t _soft_i2c_sda_read(soft_i2c_config_t *config)
{
    return (GPIO_Level_t)gpio_read_pin(config->sda_pin);
}

/*********************************************************************************
 *  @brief     I2C延时（内部函数）
 *  @param     config    I2C配置指针
 *********************************************************************************/
static void _soft_i2c_delay(soft_i2c_config_t *config)
{
    delay_us(config->delay_us);
}

/*********************************************************************************
 *  @brief     生成I2C START信号（内部函数）
 *  @param     config    I2C配置指针
 *  @note      SDA从高到低的跳变，而SCL保持高电平
 *********************************************************************************/
static void _soft_i2c_start(soft_i2c_config_t *config)
{
    _soft_i2c_scl_set(config, GPIO_HIGH);
    _soft_i2c_sda_set(config, GPIO_HIGH);
    _soft_i2c_delay(config);
    _soft_i2c_sda_set(config, GPIO_LOW);   // SDA HIGH->LOW while SCL HIGH
    _soft_i2c_delay(config);
    _soft_i2c_scl_set(config, GPIO_LOW);
    _soft_i2c_delay(config);
}

/*********************************************************************************
 *  @brief     生成I2C STOP信号（内部函数）
 *  @param     config    I2C配置指针
 *  @note      SDA从低到高的跳变，而SCL保持高电平
 *********************************************************************************/
static void _soft_i2c_stop(soft_i2c_config_t *config)
{
    _soft_i2c_scl_set(config, GPIO_LOW);
    _soft_i2c_sda_set(config, GPIO_LOW);
    _soft_i2c_delay(config);
    _soft_i2c_scl_set(config, GPIO_HIGH);
    _soft_i2c_delay(config);
    _soft_i2c_sda_set(config, GPIO_HIGH);   // SDA LOW->HIGH while SCL HIGH
    _soft_i2c_delay(config);
}

/*********************************************************************************
 *  @brief     等待I2C从机ACK信号（内部函数）
 *  @param     config    I2C配置指针
 *  @return    SUCCESS-收到ACK, ERROR-收到NACK或超时
 *********************************************************************************/
static Status _soft_i2c_wait_ack(soft_i2c_config_t *config)
{
    uint16_t timeout;
    uint16_t timeout_limit = config->timeout_ms * 100;  // 近似超时限制

    _soft_i2c_sda_set(config, GPIO_HIGH);  // 释放SDA
    _soft_i2c_delay(config);

    _soft_i2c_scl_set(config, GPIO_HIGH);
    _soft_i2c_delay(config);

    // 等待SDA变为LOW（ACK）
    timeout = 0;
    while (_soft_i2c_sda_read(config) == GPIO_HIGH)
    {
        timeout++;
        if (timeout > timeout_limit)
        {
            _soft_i2c_scl_set(config, GPIO_LOW);
            return ERROR;  // 超时，未收到ACK
        }
    }

    _soft_i2c_scl_set(config, GPIO_LOW);
    _soft_i2c_delay(config);

    return SUCCESS;  // 收到ACK
}

/*********************************************************************************
 *  @brief     写入一个字节（内部函数）
 *  @param     config    I2C配置指针
 *  @param     byte      要写入的字节
 *  @return    SUCCESS-收到ACK, ERROR-收到NACK或超时
 *********************************************************************************/
static Status _soft_i2c_write_byte(soft_i2c_config_t *config, uint8_t byte)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        _soft_i2c_scl_set(config, GPIO_LOW);

        if (byte & 0x80)
            _soft_i2c_sda_set(config, GPIO_HIGH);
        else
            _soft_i2c_sda_set(config, GPIO_LOW);

        byte <<= 1;
        _soft_i2c_delay(config);

        _soft_i2c_scl_set(config, GPIO_HIGH);
        _soft_i2c_delay(config);
    }

    _soft_i2c_scl_set(config, GPIO_LOW);
    return _soft_i2c_wait_ack(config);
}

/*********************************************************************************
 *  @brief     读取一个字节（内部函数）
 *  @param     config    I2C配置指针
 *  @param     ack       1-发送ACK, 0-发送NACK
 *  @return    读取的字节
 *********************************************************************************/
static uint8_t _soft_i2c_read_byte_internal(soft_i2c_config_t *config, uint8_t ack)
{
    uint8_t i;
    uint8_t dat = 0;

    _soft_i2c_sda_set(config, GPIO_HIGH);  // 释放SDA

    for (i = 0; i < 8; i++)
    {
        dat <<= 1;
        _soft_i2c_scl_set(config, GPIO_HIGH);
        _soft_i2c_delay(config);

        if (_soft_i2c_sda_read(config) == GPIO_HIGH)
            dat |= 0x01;

        _soft_i2c_scl_set(config, GPIO_LOW);
        _soft_i2c_delay(config);
    }

    // 发送ACK或NACK
    if (ack)
        _soft_i2c_sda_set(config, GPIO_LOW);   // ACK
    else
        _soft_i2c_sda_set(config, GPIO_HIGH);  // NACK

    _soft_i2c_delay(config);
    _soft_i2c_scl_set(config, GPIO_HIGH);
    _soft_i2c_delay(config);
    _soft_i2c_scl_set(config, GPIO_LOW);
    _soft_i2c_delay(config);
    _soft_i2c_sda_set(config, GPIO_HIGH);  // 释放SDA

    return dat;
}

/*********************************************************************************
 *  @brief     初始化软件I2C
 *  @param     config    I2C配置指针
 *********************************************************************************/
void soft_i2c_init(soft_i2c_config_t *config)
{
    KY_ASSERT(config != NULL);
    KY_ASSERT(config->scl_pin != GPIO_PFF);
    KY_ASSERT(config->sda_pin != GPIO_PFF);
    KY_ASSERT(config->scl_pin != config->sda_pin);
    // KY_ASSERT(config->delay_us > 0 && config->delay_us <= 100);

    // 根据速度预设自动设置delay_us
    if (config->speed == SOFT_I2C_SPEED_STANDARD)
    {
        config->delay_us = 5;  // 100kHz: 10us周期，半周期5us
    }
    else if (config->speed == SOFT_I2C_SPEED_FAST)
    {
        config->delay_us = 1;  // 约250kHz
    }

    // 配置SDA和SCL为开漏输出，初始电平为高
    gpio_init(config->scl_pin, GPIO_MODE_OUT_OD, GPIO_HIGH);
    gpio_init(config->sda_pin, GPIO_MODE_OUT_OD, GPIO_HIGH);

    delay_ms(50);  // 稳定延时
}

/*********************************************************************************
 *  @brief     写数据到I2C设备
 *  @param     config       I2C配置指针
 *  @param     reg_addr     寄存器地址指针（NULL则不发送）
 *  @param     dat          数据缓冲区
 *  @param     length       数据长度
 *  @return    SUCCESS成功, ERROR失败
 *********************************************************************************/
Status soft_i2c_write(soft_i2c_config_t *config, const uint8_t *reg_addr,
                      const uint8_t *dat, uint16_t length)
{
    uint8_t retry;
    uint16_t i;
    Status status;

    KY_ASSERT(config != NULL);
    KY_ASSERT(dat != NULL);
    KY_ASSERT(length > 0);

    // 重试机制
    for (retry = 0; retry <= config->retries; retry++)
    {
        _soft_i2c_start(config);

        // 发送设备写地址
        status = _soft_i2c_write_byte(config, config->dev_write_addr);
        if (status != SUCCESS)
        {
            _soft_i2c_stop(config);
            continue;
        }

        // 发送寄存器地址
        if (reg_addr != NULL)
        {
            status = _soft_i2c_write_byte(config, *reg_addr);
            if (status != SUCCESS)
            {
                _soft_i2c_stop(config);
                continue;
            }
        }

        // 发送数据
        for (i = 0; i < length; i++)
        {
            status = _soft_i2c_write_byte(config, dat[i]);
            if (status != SUCCESS)
            {
                break;
            }
        }

        _soft_i2c_stop(config);

        if (status == SUCCESS)
        {
            return SUCCESS;
        }
    }

    return ERROR;
}

/*********************************************************************************
 *  @brief     从I2C设备读数据
 *  @param     config       I2C配置指针
 *  @param     reg_addr     寄存器地址指针（NULL则不发送）
 *  @param     dat          数据缓冲区
 *  @param     length       数据长度
 *  @return    SUCCESS成功, ERROR失败
 *********************************************************************************/
Status soft_i2c_read(soft_i2c_config_t *config, const uint8_t *reg_addr,
                     uint8_t *dat, uint16_t length)
{
    uint8_t retry;
    uint16_t i;
    Status status;

    KY_ASSERT(config != NULL);
    KY_ASSERT(dat != NULL);
    KY_ASSERT(length > 0);

    // 重试机制
    for (retry = 0; retry <= config->retries; retry++)
    {
        // 如果有寄存器地址，先写入
        if (reg_addr != NULL)
        {
            _soft_i2c_start(config);
            status = _soft_i2c_write_byte(config, config->dev_write_addr);
            if (status != SUCCESS)
            {
                _soft_i2c_stop(config);
                continue;
            }

            status = _soft_i2c_write_byte(config, *reg_addr);
            if (status != SUCCESS)
            {
                _soft_i2c_stop(config);
                continue;
            }
            _soft_i2c_stop(config);
            delay_us(10);
        }

        // 重新开始，读取数据
        _soft_i2c_start(config);
        status = _soft_i2c_write_byte(config, config->dev_read_addr);
        if (status != SUCCESS)
        {
            _soft_i2c_stop(config);
            continue;
        }

        // 读取数据
        for (i = 0; i < length; i++)
        {
            // 最后一个字节发送NACK，其他发送ACK
            dat[i] = _soft_i2c_read_byte_internal(config, (i < length - 1) ? 1 : 0);
        }

        _soft_i2c_stop(config);
        return SUCCESS;
    }

    return ERROR;
}

/*********************************************************************************
 *  @brief     写单字节到寄存器
 *  @param     config       I2C配置指针
 *  @param     reg_addr     寄存器地址
 *  @param     dat          要写入的字节
 *  @return    SUCCESS成功, ERROR失败
 *********************************************************************************/
Status soft_i2c_write_byte(soft_i2c_config_t *config, uint8_t reg_addr, uint8_t dat)
{
    return soft_i2c_write(config, &reg_addr, &dat, 1);
}

/*********************************************************************************
 *  @brief     从寄存器读单字节
 *  @param     config       I2C配置指针
 *  @param     reg_addr     寄存器地址
 *  @param     dat          存储读取字节
 *  @return    SUCCESS成功, ERROR失败
 *********************************************************************************/
Status soft_i2c_read_byte(soft_i2c_config_t *config, uint8_t reg_addr, uint8_t *dat)
{
    return soft_i2c_read(config, &reg_addr, dat, 1);
}

/*********************************************************************************
 *  @brief     写16位数据到寄存器（高字节先发送）
 *  @param     config       I2C配置指针
 *  @param     reg_addr     寄存器地址
 *  @param     dat          要写入的16位数据
 *  @return    SUCCESS成功, ERROR失败
 *********************************************************************************/
Status soft_i2c_write_16bit(soft_i2c_config_t *config, uint8_t reg_addr, uint16_t dat)
{
    uint8_t buffer[2];
    buffer[0] = (uint8_t)(dat >> 8);   // 高字节
    buffer[1] = (uint8_t)dat;           // 低字节
    return soft_i2c_write(config, &reg_addr, buffer, 2);
}

/*********************************************************************************
 *  @brief     从寄存器读16位数据（高字节先接收）
 *  @param     config       I2C配置指针
 *  @param     reg_addr     寄存器地址
 *  @param     dat          存储读取的16位数据
 *  @return    SUCCESS成功, ERROR失败
 *********************************************************************************/
Status soft_i2c_read_16bit(soft_i2c_config_t *config, uint8_t reg_addr, uint16_t *dat)
{
    uint8_t buffer[2];
    Status status;

    status = soft_i2c_read(config, &reg_addr, buffer, 2);
    if (status == SUCCESS)
    {
        *dat = (buffer[0] << 8) | buffer[1];  // 组合成16位
    }
    return status;
}

/*********************************************************************************
 *  @brief     探测I2C设备
 *  @param     config       I2C配置指针
 *  @return    SUCCESS设备存在, ERROR设备不存在
 *********************************************************************************/
Status soft_i2c_device_probe(soft_i2c_config_t *config)
{
    Status status;

    KY_ASSERT(config != NULL);

    _soft_i2c_start(config);
    status = _soft_i2c_write_byte(config, config->dev_write_addr);
    _soft_i2c_stop(config);

    return status;
}

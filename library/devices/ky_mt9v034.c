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
 * 文件名：[ky_mt9v034.c]
 * 开发单位：北京科宇通博科技有限公司
 * 适用环境：[Keil C251 / STC32G系列单片机]
 * 官方渠道：
 *   -
 * 代码仓库：[https://gitee.com/beijing-keyu---jiangxi/KEYU_AI8052U_OpenLibrary]
 *   - 淘宝店铺：https://kyznc.taobao.com/
 *   - 技术支持：QQ群 974530818
 *
 * === 修订记录 ===
 * 日期       |  开发者  | 变更说明
 * -----------|----------|----------------------
 * 2025.12.22 |   xiao   | V2.0
 *********************************************************************************/
#include "ky_mt9v034.h"
#include "ky_delay.h"
#include "ky_soft_i2c.h"
#include "ky_assert.h"
#include "stc32g144k246.h"
#include "stc32g144k246_def.h"
#include "ky_mt9v034_config.h"
#include <stdio.h>

#define MT9V034_ID                  0x1324
#define WRST_HIGH                   P8OUT |= 0x20
#define WRST_LOW                    P8OUT &= ~0x20
#define RRST_HIGH                   MT9V034_PIN_RRST = 1
#define RRST_LOW                    MT9V034_PIN_RRST = 0
#define OE_HIGH                     MT9V034_PIN_OE = 1
#define OE_LOW                      MT9V034_PIN_OE = 0
#define WEN_HIGH                    MT9V034_PIN_WEN = 1
#define WEN_LOW                     MT9V034_PIN_WEN = 0
#define RCLK_HIGH                   MT9V034_PIN_RCLK = 1
#define RCLK_LOW                    MT9V034_PIN_RCLK = 0
#define RE_HIGH                     PAOUT |= 0x40
#define RE_LOW                      PAOUT &= ~0x40

uint8_t xdata mt9v034_image[MT9V034_HEIGHT][MT9V034_WIDTH];
volatile uint8_t far mt9v034_frame_ready = 0;
bit mt9v034_dma_finish_flag = 1;
soft_i2c_config_t mt9v034_i2c = {
    MT9V034_SCCB_SCL,        // scl_pin
    MT9V034_SCCB_SDA,        // sda_pin
    0xB8,                    // dev_write_addr
    0xB9,                    // dev_read_addr
    SOFT_I2C_SPEED_STANDARD, // speed
    10,                       // delay_us
    10,                      // timeout_ms
    3                        // retries
};

/*********************************************************************************
 * @brief     读取MT9V034寄存器
 *********************************************************************************/
static uint16_t _mt9v034_read_reg(uint8_t reg_addr)
{
    uint16_t dat;
//		uint16_t dummy; // 用于接收无用的数据
    soft_i2c_read_16bit(&mt9v034_i2c, reg_addr, &dat);

    return dat;
}

/*********************************************************************************
 * @brief     写入MT9V034寄存器
 *********************************************************************************/
static void _mt9v034_write_reg(uint8_t reg_addr, uint16_t dat)
{
    uint8_t retry;
    uint16_t read_value;
    char error_msg[64];

    // 尝试写入并验证，最多重试10次
    for(retry = 0; retry < 10; retry++)
    {
        // 写入寄存器
        soft_i2c_write_16bit(&mt9v034_i2c, reg_addr, dat);

        // 读回验证
        read_value = _mt9v034_read_reg(reg_addr);

        // 验证是否写入成功
        if(read_value == dat)
        {
            return; // 写入成功，直接返回
        }

        // 写入失败
        delay_ms(1);
    }

    sprintf(error_msg, "Reg:0x%02X Wr:0x%04X Rd:0x%04X", reg_addr, dat, read_value);
    KY_ASSERT_INFO(0, error_msg);
}



// MT9V034寄存器读写宏
#define mt9v034_write_reg(reg_addr, dat) _mt9v034_write_reg(reg_addr, dat)
#define mt9v034_read_reg(reg_addr) _mt9v034_read_reg(reg_addr)

/*********************************************************************************
 * @brief     初始化MT9V034引脚
 * *********************************************************************************/
static void io_init(void)
{
    gpio_init(GPIO_P20, GPIO_MODE_IN_PU, GPIO_LOW);
    gpio_init(GPIO_P21, GPIO_MODE_IN_PU, GPIO_LOW);
    gpio_init(GPIO_P22, GPIO_MODE_IN_PU, GPIO_LOW);
    gpio_init(GPIO_P23, GPIO_MODE_IN_PU, GPIO_LOW);
    gpio_init(GPIO_P24, GPIO_MODE_IN_PU, GPIO_LOW);
    gpio_init(GPIO_P25, GPIO_MODE_IN_PU, GPIO_LOW);
    gpio_init(GPIO_P26, GPIO_MODE_IN_PU, GPIO_LOW);
    gpio_init(GPIO_P27, GPIO_MODE_IN_PU, GPIO_LOW);

    gpio_init(MT9V034_FIFO_WRST, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(MT9V034_FIFO_RRST, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(MT9V034_FIFO_OE, GPIO_MODE_OUT_PP, GPIO_LOW);
    gpio_init(MT9V034_FIFO_WEN, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(MT9V034_FIFO_RE, GPIO_MODE_OUT_PP, GPIO_LOW);
    gpio_init(MT9V034_FIFO_RCLK, GPIO_MODE_OUT_PP, GPIO_HIGH);
    gpio_init(MT9V034_VSYNC, GPIO_MODE_IN_PU, GPIO_LOW);
}

/*********************************************************************************
 *  @brief     初始化LCM DMA接口
 *********************************************************************************/
static void lcm_dma_init(void)
{
    LCMIFCFG = 0x00;
    LCMIFCFG2 = 0;
		//LCMIFCFG2 |= (1) << 2;
    LCMIFPSCR = 0;
    LCMIFSTA = 0x00;
    LCMIFCR = 0x90;
    DMA_LCM_CFG = 0x80 | (3 << 2) | 3;
    DMA_LCM_STA = 0x00;

    DMA_LCM_AMTH = (uint8_t)((MT9V034_IMAGE_SIZE - 1) >> 8);
    DMA_LCM_AMT = (uint8_t)(MT9V034_IMAGE_SIZE - 1);
    DMA_LCM_RXAH = (uint8_t)((uint16_t)(&mt9v034_image) >> 8);
    DMA_LCM_RXAL = (uint8_t)((uint16_t)(&mt9v034_image));
}
/*********************************************************************************
 *  @brief     软复位MT9V034
 *********************************************************************************/
static void mt9v034_reset(void)
{
    mt9v034_write_reg(0xFE, 0xBEEF); // 解锁
    soft_i2c_write_16bit(&mt9v034_i2c, 0x0C, 0x0003); // 复位
}

/*********************************************************************************
 *  @brief     设置自动曝光
 *  @param     enable      使能标志 (0=禁用AEC使用固定曝光, 非0=启用AEC)
 *********************************************************************************/
static void mt9v034_set_auto_exposure(uint8_t enable)
{
    uint16_t reg = mt9v034_read_reg(0xAF);

    if (enable)
    {
        // 启用 AEC - 设置 AEC 使能位 (bit 0)
        mt9v034_write_reg(0xAF, reg | 0x01);
        // 设置目标亮度 (AEC/AGC_DESIRED_BIN 0xA5)
        mt9v034_write_reg(0xA5, MT9V034_EXPOSURE_BRIGHTNESS);
        // 设置最大曝光时间 (MAX_EXPOSE 0xAD)
        mt9v034_write_reg(0xAD, MT9V034_MAX_EXP_TIME);
        // 设置最小曝光时间 (AEC_MIN_EXPOSURE 0xAC)
        mt9v034_write_reg(0xAC, MT9V034_MIN_EXP_TIME);
        // 设置像素计数 (PIXEL_COUNT 0xB0)
        mt9v034_write_reg(0xB0, MT9V034_IMAGE_SIZE);
    }
    else
    {
        // 禁用 AEC - 清除 AEC 使能位
        mt9v034_write_reg(0xAF, reg & ~0x01);
        // 设置固定曝光时间 (TOTAL_SHUTTER_WIDTH 0x0B)
        mt9v034_write_reg(0x0B, MT9V034_EXP_TIME_DEF);
    }
}

/*********************************************************************************
 *  @brief     设置自动增益
 *  @param     enable      使能标志 (0=禁用AGC使用固定增益, 非0=启用AGC)
 *********************************************************************************/
static void mt9v034_set_auto_gain(uint8_t enable)
{
    uint16_t reg = mt9v034_read_reg(0xAF);
    uint8_t gain = MT9V034_GAIN_DEF;

    // 限制增益范围 [16, 64]
    if (gain < 16)
        gain = 16;
    if (gain > 64)
        gain = 64;

    if (enable)
    {
        // 启用 AGC - 设置 AGC 使能位 (bit 1)
        mt9v034_write_reg(0xAF, reg | 0x02);
        // 设置最大增益 (MAX_GAIN 0xAB)
        mt9v034_write_reg(0xAB, gain);
    }
    else
    {
        // 禁用 AGC - 清除 AGC 使能位
        mt9v034_write_reg(0xAF, 0);
        // 设置固定模拟增益 (ANALOG_GAIN 0x35)
        mt9v034_write_reg(0x35, gain);
    }
}

/*********************************************************************************
 *  @brief     应用配置表
 *********************************************************************************/
static void apply_config(void)
{

//			uint8_t i;
    // 软复位MT9V034
    mt9v034_reset();
    // for (i = 0; i < mt9v034_reg_config_table_size; i++)
    // {
    //     mt9v034_write_reg((uint8_t)mt9v034_reg_config_table[i][0],
    //                        mt9v034_reg_config_table[i][1]);
    //     delay_us(10);
    // }
    // 窗口与时序配置
    mt9v034_write_reg(0x01, 0x0001); // 列起始 Context A
    mt9v034_write_reg(0x02, 0x0004); // 行起始 Context A
    mt9v034_write_reg(0x03, 0x01E0); // 窗口高度 Context A
    mt9v034_write_reg(0x04, 0x02F0); // 窗口宽度 Context A
    mt9v034_write_reg(0x05, 0x005E); // 水平消隐 Context A
    mt9v034_write_reg(0x06, (uint16_t)((31914 / MT9V034_MAX_FPS) - 120)); // 垂直消隐 Context A
    mt9v034_write_reg(0x07, 0x0388); // 逐行扫描
    // 读取模式
    mt9v034_write_reg(0x0D, 0x033A); // Bining 4x4 Context A
    // 传感器类型
    mt9v034_write_reg(0x0F, 0x0101);
    // mt9v034_write_reg(0x13, 0x2D2E);
    mt9v034_write_reg(0x1C, 0x0303);
    // 模拟控制
    mt9v034_write_reg(0x20, MT9V034_CONTRAST_DEF); // 图像对比度
    mt9v034_write_reg(0x2C, 0x0003);               // ADC 参考电压 (VREF) 控制
    mt9v034_write_reg(0x2F, 0x0003);
    mt9v034_write_reg(0x2B, 0x0003); // 改进FPN
    mt9v034_write_reg(0x31, 0x0027); // V1 电压控制 Context A
    mt9v034_write_reg(0x32, 0x001A); // V2 电压控制 Context A
    mt9v034_write_reg(0x33, 0x0005); // V3 电压控制 Context A

    // 黑电平校准
    mt9v034_write_reg(0x4C, 0x0002); // 黑电平校准步长
    mt9v034_write_reg(0x47, 0x0081); // 黑电平校准控制
    mt9v034_write_reg(0x48, MT9V034_BLACK_LEVEL_DEF);

    // 曝光控制
    mt9v034_write_reg(0x08, 0x01BB); // 粗调曝光宽度 1 Context A - 第一拐点
    mt9v034_write_reg(0x09, 0x01D9); // 粗调曝光宽度 2 Context A - 第二拐点
    mt9v034_write_reg(0x0A, 0x0164); // 曝光宽度控制 Context A - T2/T3 比率
    mt9v034_set_auto_exposure(MT9V034_AUTO_EXP_DEF);
    mt9v034_set_auto_gain(MT9V034_AUTO_EXP_DEF);
		
	mt9v034_write_reg(0xC2, 0x0840);
	mt9v034_write_reg(0xBF, 0x0016);
    mt9v034_write_reg(0x71, 0x002A); // 行噪声常数
    mt9v034_write_reg(0x72, 0x0010); // 像素时钟、FV、LV控制

    mt9v034_write_reg(0xFE, 0xDEAD); // 寄存器锁
}

/*********************************************************************************
 *  @brief     初始化MT9V034
 *********************************************************************************/
void mt9v034_init(void)
{
    uint16_t id;

    soft_i2c_init(&mt9v034_i2c);
    delay_ms(10);
    // 读取设备ID以验证连接
    id = mt9v034_read_reg(0x00);
    KY_ASSERT(id == MT9V034_ID);

    // 应用配置表
    apply_config();
    
    io_init();
    lcm_dma_init();
    // 配置INT1中断 (VSYNC) - 双边沿触发
    IT1 = 0;
    EX1 = 1; // 使能INT1
    INT1_SetIntPriority(3);
		
		delay_ms(500);
}

/*********************************************************************************
 * @brief     VSYNC中断服务 (INT1)
 *********************************************************************************/
void mt9v034_vsync_isr(void)
{
    if (P33)
    {
        //        if (mt9v034_dma_finish_flag)
        //        {
        //            P8OUT &= ~0x20; // WRST_LOW
        P36 = 1;       // WEN_HIGT
			  //P35 = 0;
        P8OUT |= 0x20; // WRST_HIGT
				// RE_HIGH;

        P34 = 0; // RRST_LOW
        P44 = 0; // RCLK_LOW
        P44 = 1; // RCLK_HIGT
        P44 = 0;     // RCLK_LOW
        P44 = 1;      // RCLK_HIGT
        P34 = 1; // RRST_HIGT

        mt9v034_dma_finish_flag = 1;
        //        }
    }
    else
    {
        if (mt9v034_dma_finish_flag)
        {
            P36 = 0;           // WEN_LOW
						// RE_LOW;
            DMA_LCM_CR = 0x89; //

            P8OUT &= ~0x20; // WRST_LOW
            mt9v034_dma_finish_flag = 0;
        }
    }
}

/*********************************************************************************
 * @brief     LCM DMA中断服务函数
 *********************************************************************************/
void mt9v034_lcm_isr(void) 
{
    DMA_LCM_STA = 0x00; // 清除中断标志位

    // PAOUT |= 0x40;                   // RE_HIGT
     //P35 = 1;                      // OE_HIGT

    mt9v034_dma_finish_flag = 1;
    mt9v034_frame_ready = 1;
}

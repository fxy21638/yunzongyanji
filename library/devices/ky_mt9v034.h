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
 * 文件名：[ky_mt9v034.h]
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
#ifndef __KY_MT9V034_H__
#define __KY_MT9V034_H__

#include "ky_gpio.h"
#include "ky_typedef.h"

// 图像分辨率配置
#define MT9V034_HEIGHT                      120                    // 图像高度
#define MT9V034_WIDTH                       188                    // 图像宽度
#define MT9V034_IMAGE_SIZE   (MT9V034_HEIGHT * MT9V034_WIDTH)      // 图像大小

// MT9V034 默认参数配置
#define MT9V034_MAX_FPS                     (120)                   // 最大帧率
#define MT9V034_BLACK_LEVEL_DEF             (236)                   // 手动黑电平校准值 
#define MT9V034_AUTO_EXP_DEF                (0)                    // 自动曝光设置 [0=关闭-64]
#define MT9V034_EXP_TIME_DEF                (310)                  // 曝光时间 [10-32767]
#define MT9V034_LR_OFFSET_DEF               (0)                    // 图像左右偏移量
#define MT9V034_UD_OFFSET_DEF               (0)                    // 图像上下偏移量
#define MT9V034_GAIN_DEF                    (24)                   // 图像增益 [16-64]
                                                                   // 值越大越亮
#define MT9V034_CONTRAST_DEF                (0x01c7)               // 图像对比度    
                                                                   // 高对比度0x03c7  低对比度0x01c7
#define MT9V034_HDR_EN                      (1)                    // HDR 设置 [0=关闭, 1=开启]
// 开启自动曝光参数
#define MT9V034_EXPOSURE_BRIGHTNESS         (62)                   // 自动亮度校准 [1-64]
#define MT9V034_BRIGHTNESS_DEF              (62)                   // 目标亮度 [1-64]
#define MT9V034_MAX_EXP_TIME                (512)                  // 最大曝光时间
#define MT9V034_MIN_EXP_TIME                (100)                  // 最小曝光时间
#define MT9V034_MAX_GAIN                    (64)                   // 最大增益
#define MT9V034_MIN_GAIN                    (16)                   // 最小增益

extern uint8_t xdata mt9v034_image[MT9V034_HEIGHT][MT9V034_WIDTH];
// 帧数据就绪标志
extern volatile uint8_t far mt9v034_frame_ready;

// 初始化MT9V034
void mt9v034_init(void);

// VSYNC中断服务
void mt9v034_vsync_isr(void);

void mt9v034_lcm_isr(void);


// SCCB接口引脚
#define MT9V034_SCCB_SDA                    GPIO_P14               // SDA
#define MT9V034_SCCB_SCL                    GPIO_P15               // SCL

// 数据位占用P20-P27
#define MT9V034_PIN_DATA                    P20

// FIFO控制引脚
#define MT9V034_FIFO_WRST                   GPIO_P85               // FIFO写复位
#define MT9V034_FIFO_RRST                   GPIO_P34               // FIFO读复位
#define MT9V034_FIFO_OE                     GPIO_P35               // FIFO输出使能
#define MT9V034_FIFO_WEN                    GPIO_P36               // FIFO写使能
#define MT9V034_VSYNC                       GPIO_P33               // VSYNC
#define MT9V034_FIFO_RCLK                   GPIO_P44               // FIFO读时钟
#define MT9V034_FIFO_RE                     GPIO_PA6               // FIFO读使能

// FIFO控制引脚
// MT9V034_PIN_WRST: P85 
#define MT9V034_PIN_RRST                    P34
#define MT9V034_PIN_OE                      P35
#define MT9V034_PIN_WEN                     P36
#define MT9V034_PIN_VSYNC                   P33
#define MT9V034_PIN_RCLK                    P44

#endif

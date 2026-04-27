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
 * 文件名：main.c
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
 * 2025.12.22 |   xiao   | V2.0
 *********************************************************************************/
#include "ky_headfile.h"
#include "main.h"

void System_Init(void);
	
int main()
{
	system_clock_init(SYS_CLK_99MHZ);
	
    gpio_init(LED, GPIO_MODE_OUT_PP, GPIO_HIGH);
    // 系统初始化
	System_Init();

    while (1) 
    {
        // 在这里添加您的应用代码
		
		// 按键扫描 (周期10ms)
        //key_scan(10);
		
		//vofa_image_task();
		//vision_task();
		
		//icm_debug();
		
		//servo_task();
		
		motor_task();
			
        // 在这里添加您的应用代码
		
		//检验：如果主循环正常运行的话，蓝色灯会闪
		gpio_toggle_pin(LED);
        delay_ms(5);
    }
}

void System_Init(void)
{
	//key_system_Init();
	
	//servo_Init();
	
	//vision_Init();
	
	//icm_Init();
	
	//ips_init(IPS_TYPE_200);
	
	motor_Init();
	
	//encoder_Init();
	
	//servo_Init();	//转到中间（90度再启动）
}

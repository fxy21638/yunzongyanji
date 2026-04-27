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
 * 文件名：[ky_pwm.c]
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
#include "ky_pwm.h"
#include "ky_system_clock.h"
#include "stc32g144k246.h"

#define PWM_MOD_A 0
#define PWM_MOD_B 1
#define PWM_MOD_C 2
#define PWM_MOD_D 3
#define PWM_MOD_E 4
#define PWM_MOD_F 5

/*********************************************************************************
 *  @brief     设置 PS 寄存器 (引脚复用)
 *  @param     group 组索引
 *  @param     channel_id 通道号
 *  @param     ps_val PS值
 *  @return    无
 *********************************************************************************/
static void _pwm_set_ps(uint8_t group, uint8_t channel_id, uint8_t ps_val)
{
	uint8_t shift;

	/* PWME 通道5和通道6 使用 PWME_PS2 寄存器 */
	if (group == PWM_MOD_E && channel_id >= 5)
	{
		shift = (channel_id - 5) * 2;
		PWME_PS2 = (PWME_PS2 & ~(0x03 << shift)) | (ps_val << shift);
		return;
	}

	shift = (channel_id > 4 ? (channel_id - 5) : (channel_id - 1)) * 2;

	switch (group)
	{
	case PWM_MOD_A:
		PWMA_PS = (PWMA_PS & ~(0x03 << shift)) | (ps_val << shift);
		break;
	case PWM_MOD_B:
		PWMB_PS = (PWMB_PS & ~(0x03 << shift)) | (ps_val << shift);
		break;
	case PWM_MOD_C:
		PWMC_PS = (PWMC_PS & ~(0x03 << shift)) | (ps_val << shift);
		break;
	case PWM_MOD_D:
		PWMD_PS = (PWMD_PS & ~(0x03 << shift)) | (ps_val << shift);
		break;
	case PWM_MOD_E:
		PWME_PS = (PWME_PS & ~(0x03 << shift)) | (ps_val << shift);
		break;
	case PWM_MOD_F:
		PWMF_PS = (PWMF_PS & ~(0x03 << shift)) | (ps_val << shift);
		break;
	}
}

/*********************************************************************************
 *  @brief     设置 PSC 预分频寄存器
 *  @param     group 组索引
 *  @param     val 预分频值
 *  @return    无
 *********************************************************************************/
static void _pwm_set_psc(uint8_t group, uint16_t val)
{
	switch (group)
	{
	case PWM_MOD_A:
		PWMA_PSCRH = val >> 8;
		PWMA_PSCRL = val;
		break;
	case PWM_MOD_B:
		PWMB_PSCRH = val >> 8;
		PWMB_PSCRL = val;
		break;
	case PWM_MOD_C:
		PWMC_PSCRH = val >> 8;
		PWMC_PSCRL = val;
		break;
	case PWM_MOD_D:
		PWMD_PSCRH = val >> 8;
		PWMD_PSCRL = val;
		break;
	case PWM_MOD_E:
		PWME_PSCRH = val >> 8;
		PWME_PSCRL = val;
		break;
	case PWM_MOD_F:
		PWMF_PSCRH = val >> 8;
		PWMF_PSCRL = val;
		break;
	}
}

/*********************************************************************************
 *  @brief     设置 ARR 自动重载寄存器
 *  @param     group 组索引
 *  @param     val ARR值
 *  @return    无
 *********************************************************************************/
static void _pwm_set_arr(uint8_t group, uint16_t val)
{
	switch (group)
	{
	case PWM_MOD_A:
		PWMA_ARRH = val >> 8;
		PWMA_ARRL = val;
		break;
	case PWM_MOD_B:
		PWMB_ARRH = val >> 8;
		PWMB_ARRL = val;
		break;
	case PWM_MOD_C:
		PWMC_ARRH = val >> 8;
		PWMC_ARRL = val;
		break;
	case PWM_MOD_D:
		PWMD_ARRH = val >> 8;
		PWMD_ARRL = val;
		break;
	case PWM_MOD_E:
		PWME_ARRH = val >> 8;
		PWME_ARRL = val;
		break;
	case PWM_MOD_F:
		PWMF_ARRH = val >> 8;
		PWMF_ARRL = val;
		break;
	}
}

/*********************************************************************************
 *  @brief     获取 ARR 自动重载值
 *  @param     group 组索引
 *  @return    ARR值
 *********************************************************************************/
static uint16_t _pwm_get_arr(uint8_t group)
{
	uint16_t val = 0;
	switch (group)
	{
	case PWM_MOD_A:
		val = ((uint16_t)PWMA_ARRH << 8) | PWMA_ARRL;
		break;
	case PWM_MOD_B:
		val = ((uint16_t)PWMB_ARRH << 8) | PWMB_ARRL;
		break;
	case PWM_MOD_C:
		val = ((uint16_t)PWMC_ARRH << 8) | PWMC_ARRL;
		break;
	case PWM_MOD_D:
		val = ((uint16_t)PWMD_ARRH << 8) | PWMD_ARRL;
		break;
	case PWM_MOD_E:
		val = ((uint16_t)PWME_ARRH << 8) | PWME_ARRL;
		break;
	case PWM_MOD_F:
		val = ((uint16_t)PWMF_ARRH << 8) | PWMF_ARRL;
		break;
	}
	return val;
}

/*********************************************************************************
 *  @brief     设置 CCR 比较值
 *  @param     group 组索引
 *  @param     channel_id 通道号
 *  @param     val CCR值
 *  @return    无
 *********************************************************************************/
static void _pwm_set_ccr(uint8_t group, uint8_t channel_id, uint16_t val)
{
	switch (group)
	{
	case PWM_MOD_A:
		if (channel_id == 1)
		{
			PWMA_CCR1H = val >> 8;
			PWMA_CCR1L = val;
		}
		else if (channel_id == 2)
		{
			PWMA_CCR2H = val >> 8;
			PWMA_CCR2L = val;
		}
		else if (channel_id == 3)
		{
			PWMA_CCR3H = val >> 8;
			PWMA_CCR3L = val;
		}
		else if (channel_id == 4)
		{
			PWMA_CCR4H = val >> 8;
			PWMA_CCR4L = val;
		}
		break;
	case PWM_MOD_B:
		if (channel_id == 5)
		{
			PWMB_CCR5H = val >> 8;
			PWMB_CCR5L = val;
		}
		else if (channel_id == 6)
		{
			PWMB_CCR6H = val >> 8;
			PWMB_CCR6L = val;
		}
		else if (channel_id == 7)
		{
			PWMB_CCR7H = val >> 8;
			PWMB_CCR7L = val;
		}
		else if (channel_id == 8)
		{
			PWMB_CCR8H = val >> 8;
			PWMB_CCR8L = val;
		}
		break;
	case PWM_MOD_C:
		if (channel_id == 1)
		{
			PWMC_CCR1H = val >> 8;
			PWMC_CCR1L = val;
		}
		else if (channel_id == 2)
		{
			PWMC_CCR2H = val >> 8;
			PWMC_CCR2L = val;
		}
		else if (channel_id == 3)
		{
			PWMC_CCR3H = val >> 8;
			PWMC_CCR3L = val;
		}
		else if (channel_id == 4)
		{
			PWMC_CCR4H = val >> 8;
			PWMC_CCR4L = val;
		}
		break;
	case PWM_MOD_D:
		if (channel_id == 5)
		{
			PWMD_CCR5H = val >> 8;
			PWMD_CCR5L = val;
		}
		else if (channel_id == 6)
		{
			PWMD_CCR6H = val >> 8;
			PWMD_CCR6L = val;
		}
		else if (channel_id == 7)
		{
			PWMD_CCR7H = val >> 8;
			PWMD_CCR7L = val;
		}
		else if (channel_id == 8)
		{
			PWMD_CCR8H = val >> 8;
			PWMD_CCR8L = val;
		}
		break;
	case PWM_MOD_E:
		if (channel_id == 1)
		{
			PWME_CCR1H = val >> 8;
			PWME_CCR1L = val;
		}
		else if (channel_id == 2)
		{
			PWME_CCR2H = val >> 8;
			PWME_CCR2L = val;
		}
		else if (channel_id == 3)
		{
			PWME_CCR3H = val >> 8;
			PWME_CCR3L = val;
		}
		else if (channel_id == 4)
		{
			PWME_CCR4H = val >> 8;
			PWME_CCR4L = val;
		}
		else if (channel_id == 5)
		{
			PWME_CCR5H = val >> 8;
			PWME_CCR5L = val;
		}
		else if (channel_id == 6)
		{
			PWME_CCR6H = val >> 8;
			PWME_CCR6L = val;
		}
		break;
	case PWM_MOD_F:
		if (channel_id == 5)
		{
			PWMF_CCR5H = val >> 8;
			PWMF_CCR5L = val;
		}
		else if (channel_id == 6)
		{
			PWMF_CCR6H = val >> 8;
			PWMF_CCR6L = val;
		}
		else if (channel_id == 7)
		{
			PWMF_CCR7H = val >> 8;
			PWMF_CCR7L = val;
		}
		else if (channel_id == 8)
		{
			PWMF_CCR8H = val >> 8;
			PWMF_CCR8L = val;
		}
		break;
	}
}

/*********************************************************************************
 *  @brief     设置 CCMR 模式 (PWM模式1)
 *  @param     group 组索引
 *  @param     channel_id 通道号
 *  @return    无
 *********************************************************************************/
static void _pwm_set_mode(uint8_t group, uint8_t channel_id)
{
	uint8_t target = 0x68;

	switch (group)
	{
	case PWM_MOD_A:
		if (channel_id == 1)
			PWMA_CCMR1 = target;
		else if (channel_id == 2)
			PWMA_CCMR2 = target;
		else if (channel_id == 3)
			PWMA_CCMR3 = target;
		else if (channel_id == 4)
			PWMA_CCMR4 = target;
		break;
	case PWM_MOD_B:
		if (channel_id == 5)
			PWMB_CCMR1 = target;
		else if (channel_id == 6)
			PWMB_CCMR2 = target;
		else if (channel_id == 7)
			PWMB_CCMR3 = target;
		else if (channel_id == 8)
			PWMB_CCMR4 = target;
		break;
	case PWM_MOD_C:
		if (channel_id == 1)
			PWMC_CCMR1 = target;
		else if (channel_id == 2)
			PWMC_CCMR2 = target;
		else if (channel_id == 3)
			PWMC_CCMR3 = target;
		else if (channel_id == 4)
			PWMC_CCMR4 = target;
		break;
	case PWM_MOD_D:
		if (channel_id == 5)
			PWMD_CCMR1 = target;
		else if (channel_id == 6)
			PWMD_CCMR2 = target;
		else if (channel_id == 7)
			PWMD_CCMR3 = target;
		else if (channel_id == 8)
			PWMD_CCMR4 = target;
		break;
	case PWM_MOD_E:
		if (channel_id == 1)
			PWME_CCMR1 = target;
		else if (channel_id == 2)
			PWME_CCMR2 = target;
		else if (channel_id == 3)
			PWME_CCMR3 = target;
		else if (channel_id == 4)
			PWME_CCMR4 = target;
		else if (channel_id == 5)
			PWME_CCMR5 = target;
		else if (channel_id == 6)
			PWME_CCMR6 = target;
		break;
	case PWM_MOD_F:
		if (channel_id == 5)
			PWMF_CCMR1 = target;
		else if (channel_id == 6)
			PWMF_CCMR2 = target;
		else if (channel_id == 7)
			PWMF_CCMR3 = target;
		else if (channel_id == 8)
			PWMF_CCMR4 = target;
		break;
	}
}

/*********************************************************************************
 *  @brief     设置 CCER 输出使能
 *  @param     group 组索引
 *  @param     channel_id 通道号
 *  @param     is_n 是否为N通道
 *  @return    无
 *********************************************************************************/
static void _pwm_enable_output(uint8_t group, uint8_t channel_id,
							   uint8_t is_n)
{
	uint8_t mask = 0;
	uint8_t use_ccer2;
	uint8_t use_ccer3;

	/* PWME 通道5和通道6 使用 CCER3 */
	use_ccer3 = (group == PWM_MOD_E && channel_id >= 5);
	if (use_ccer3)
	{
		/* 通道5: bit0=CC5E, 通道6: bit4=CC6E */
		mask = (channel_id == 5) ? 0x01 : 0x10;
		PWME_CCER3 |= mask;
		return;
	}

	if (channel_id & 0x01)
		mask = (is_n) ? 0x04 : 0x01;
	else
		mask = (is_n) ? 0x40 : 0x10;

	use_ccer2 = (channel_id > 2 && channel_id < 5) || (channel_id > 6);

	switch (group)
	{
	case PWM_MOD_A:
		if (use_ccer2)
			PWMA_CCER2 |= mask;
		else
			PWMA_CCER1 |= mask;
		break;
	case PWM_MOD_B:
		if (use_ccer2)
			PWMB_CCER2 |= mask;
		else
			PWMB_CCER1 |= mask;
		break;
	case PWM_MOD_C:
		if (use_ccer2)
			PWMC_CCER2 |= mask;
		else
			PWMC_CCER1 |= mask;
		break;
	case PWM_MOD_D:
		if (use_ccer2)
			PWMD_CCER2 |= mask;
		else
			PWMD_CCER1 |= mask;
		break;
	case PWM_MOD_E:
		if (use_ccer2)
			PWME_CCER2 |= mask;
		else
			PWME_CCER1 |= mask;
		break;
	case PWM_MOD_F:
		if (use_ccer2)
			PWMF_CCER2 |= mask;
		else
			PWMF_CCER1 |= mask;
		break;
	}
}

/*********************************************************************************
 *  @brief     设置 ENO 寄存器
 *  @param     group 组索引
 *  @param     channel_id 通道号
 *  @param     is_n 是否为N通道
 *  @return    无
 *********************************************************************************/
static void _pwm_set_eno(uint8_t group, uint8_t channel_id, uint8_t is_n)
{
	uint8_t mask = 0;
	uint8_t idx;

	/* PWME 通道5和通道6 使用 ENO2 */
	if (group == PWM_MOD_E && channel_id >= 5)
	{
		idx = channel_id - 5;
		mask = (1 << (idx * 2));
		PWME_ENO2 |= mask;
		return;
	}

	if (group == PWM_MOD_A || group == PWM_MOD_C || group == PWM_MOD_E)
	{
		idx = channel_id - 1;
		if (is_n)
			mask = (1 << (idx * 2 + 1));
		else
			mask = (1 << (idx * 2));
	}
	else
	{
		idx = channel_id - 5;
		mask = (1 << (idx * 2));
	}

	switch (group)
	{
	case PWM_MOD_A:
		PWMA_ENO |= mask;
		break;
	case PWM_MOD_B:
		PWMB_ENO |= mask;
		break;
	case PWM_MOD_C:
		PWMC_ENO |= mask;
		break;
	case PWM_MOD_D:
		PWMD_ENO |= mask;
		break;
	case PWM_MOD_E:
		PWME_ENO |= mask;
		break;
	case PWM_MOD_F:
		PWMF_ENO |= mask;
		break;
	}
}

/*********************************************************************************
 *  @brief     使能主输出和计数器
 *  @param     group 组索引
 *  @return    无
 *********************************************************************************/
static void _pwm_enable_main_output(uint8_t group)
{
	switch (group)
	{
	case PWM_MOD_A:
		PWMA_BKR &= ~0x10;
		PWMA_BKR |= 0x80;
		PWMA_CR1 |= 0x01;
		break;
	case PWM_MOD_B:
		PWMB_BKR &= ~0x10;
		PWMB_BKR |= 0x80;
		PWMB_CR1 |= 0x01;
		break;
	case PWM_MOD_C:
		PWMC_BKR &= ~0x10;
		PWMC_BKR |= 0x80;
		PWMC_CR1 |= 0x01;
		break;
	case PWM_MOD_D:
		PWMD_BKR &= ~0x10;
		PWMD_BKR |= 0x80;
		PWMD_CR1 |= 0x01;
		break;
	case PWM_MOD_E:
		PWME_BKR &= ~0x10;
		PWME_BKR |= 0x80;
		PWME_CR1 |= 0x01;
		break;
	case PWM_MOD_F:
		PWMF_BKR &= ~0x10;
		PWMF_BKR |= 0x80;
		PWMF_CR1 |= 0x01;
		break;
	}
}

/*********************************************************************************
 *  @brief     PWM 初始化
 *  @param     ch PWM 通道
 *  @param     freq PWM 频率
 *  @param     duty PWM 占空比 (0-10000)
 *  @return    无
 *********************************************************************************/
void pwm_init(PWM_Channel_t ch, uint32_t freq, uint16_t duty)
{
	uint8_t group;
	uint8_t channel_id;
	uint8_t is_n;
	uint8_t ps_val;
	GPIO_Pin_t pin;
	uint32_t psc_arr_val;
	uint16_t arr, psc;
	uint8_t channel_pol;

	// 参数检查：占空比范围
	KY_ASSERT(duty <= PWM_MAX_DUTY);
	// 参数检查：PWM 通道组有效性 (0-5)
	group = (ch >> 13) & 0x07;
	KY_ASSERT(group <= 5);

	channel_pol = (ch >> 9) & 0x0F;
	ps_val = (ch >> 7) & 0x03;
	pin = (GPIO_Pin_t)(ch & 0x7F);

	if (group == 0 || group == 2 || group == 4)
	{
		/* PWME 通道5和通道6 (channel_pol = 8, 9) */
		if (group == 4 && channel_pol >= 8)
		{
			channel_id = channel_pol - 3; /* 8->5, 9->6 */
			is_n = 0;
		}
		else
		{
			channel_id = (channel_pol >> 1) + 1;
			is_n = channel_pol & 0x01;
		}
	}
	else
	{
		channel_id = channel_pol + 5;
		is_n = 0;
	}

	gpio_init(pin, GPIO_MODE_OUT_PP, GPIO_LOW);
	_pwm_set_ps(group, channel_id, ps_val);

	if (freq == 0)
		freq = 1000;
	psc_arr_val = system_clock_freq / freq;

	if (psc_arr_val > PWM_MAX_DUTY)
	{
		psc = (uint16_t)((psc_arr_val / PWM_MAX_DUTY) - 1);
		arr = PWM_MAX_DUTY - 1;
	}
	else
	{
		psc = 0;
		arr = (uint16_t)(psc_arr_val - 1);
	}

	_pwm_set_psc(group, psc);
	_pwm_set_arr(group, arr);
	_pwm_set_mode(group, channel_id);
	_pwm_enable_output(group, channel_id, is_n);
	_pwm_set_eno(group, channel_id, is_n);
	_pwm_enable_main_output(group);
	pwm_set_duty(ch, duty);
}

/*********************************************************************************
 *  @brief     设置占空比
 *  @param     ch PWM 通道
 *  @param     duty 占空比 (0-10000)
 *  @return    无
 *********************************************************************************/
void pwm_set_duty(PWM_Channel_t ch, uint16_t duty)
{
	uint8_t group;
	uint8_t channel_id;
	uint32_t arr;
	uint32_t ccr_val;
	uint8_t channel_pol;

	// 参数检查：占空比范围
	KY_ASSERT(duty <= PWM_MAX_DUTY);
	// 参数检查：PWM 通道组有效性 (0-5)
	group = (ch >> 13) & 0x07;
	KY_ASSERT(group <= 5);
	channel_pol = (ch >> 9) & 0x0F;

	if (group == 0 || group == 2 || group == 4)
	{
		/* PWME 通道5和通道6 (channel_pol = 8, 9) */
		if (group == 4 && channel_pol >= 8)
			channel_id = channel_pol - 3; /* 8->5, 9->6 */
		else
			channel_id = (channel_pol >> 1) + 1;
	}
	else
	{
		channel_id = channel_pol + 5;
	}

	if (duty > PWM_MAX_DUTY)
		duty = PWM_MAX_DUTY;

	arr = _pwm_get_arr(group);
	ccr_val = duty * (arr + 1) / PWM_MAX_DUTY;

	_pwm_set_ccr(group, channel_id, (uint16_t)ccr_val);
}

/*********************************************************************************
 *  @brief     设置频率 (会影响同组所有通道)
 *  @param     ch PWM 通道
 *  @param     freq 频率
 *  @return    无
 *********************************************************************************/
void pwm_set_freq(PWM_Channel_t ch, uint16_t freq)
{
	uint8_t group;
	uint32_t psc_arr_val;
	uint16_t arr, psc;

	// 参数检查：PWM 通道组有效性 (0-5)
	group = (ch >> 13) & 0x07;
	KY_ASSERT(group <= 5);

	if (freq == 0)
		freq = 1000;
	psc_arr_val = system_clock_freq / freq;

	if (psc_arr_val > PWM_MAX_DUTY)
	{
		psc = (uint16_t)((psc_arr_val / PWM_MAX_DUTY) - 1);
		arr = PWM_MAX_DUTY - 1;
	}
	else
	{
		psc = 0;
		arr = (uint16_t)(psc_arr_val - 1);
	}

	_pwm_set_psc(group, psc);
	_pwm_set_arr(group, arr);
}

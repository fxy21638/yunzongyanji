/*******************************************************************************
 * 接线说明:
 * -----------------------------------------------------------------------------
 * 模块         | 引脚         | 连接说明
 * -------------|--------------|----------------------------------------------
 * ICM45686 SCL | IMU_SPI_SCL  | 接P0.5 (SPI2 SCLK)
 * ICM45686 SDA | IMU_SPI_SDA  | 接P0.3 (SPI2 MOSI)
 * ICM45686 SDO | IMU_SPI_SDO  | 接P0.4 (SPI2 MISO)
 * ICM45686 CS  | IMU_SPI_CS   | 接P0.2 (片选)
 * -----------------------------------------------------------------------------
 *
 * 实验现象:
 * -----------------------------------------------------------------------------
 * 1. 通过USB CDC虚拟串口输出加速度计数据 (X/Y/Z轴)
 * 2. 通过USB CDC虚拟串口输出陀螺仪数据 (X/Y/Z轴)
 * 3. 通过USB CDC虚拟串口输出温度数据
 * 4. LED指示灯闪烁表示数据正常读取
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#include "icm.h"

// 三轴积分角度
float integral_roll  = 0.0f;  // X轴 横滚角
float integral_pitch = 0.0f;  // Y轴 俯仰角
float integral_yaw   = 0.0f;  // Z轴 偏航角

void icm_Init(void)
{
	icm42686_init();
	
	// 延时等待传感器稳定
    delay_ms(100);
	
	// 启动5ms定时器
    timer_init_ms(0, 5, tim0_callback);
}

void tim0_callback(void)
{
    float raw_x, raw_y, raw_z;

    icm42686_read_gyro();
    icm42686_read_acc();

    // 去除原始值个位数噪声
    raw_x = (float)((icm42686_gyro_raw_x / 10) * 10) / 16.4f;
    raw_y = (float)((icm42686_gyro_raw_y / 10) * 10) / 16.4f;
    raw_z = (float)((icm42686_gyro_raw_z / 10) * 10) / 16.4f;

    // 积分
    integral_roll  += (raw_x ) * 0.005f;
    integral_pitch += (raw_y ) * 0.005f;
    integral_yaw   += (raw_z ) * 0.005f;
}

void icm_debug(void)
{
	printf("Roll:%.2f,Pitch:%.2f,Yaw:%.2f\n", integral_roll, integral_pitch, integral_yaw);
}
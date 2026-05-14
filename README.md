# YG SmartCar — AI8052U 智能循迹小车

基于 AI8052U (STC32G144K246) 的摄像头循迹小车，支持十字路口、直角弯、环岛、断路等多种赛道元素的识别与通过。

## 硬件平台

| 模块 | 型号 |
|------|------|
| MCU | AI8052U (STC32G144K246, 99MHz) |
| 摄像头 | MT9V034 (188×120 灰度, DMA) |
| IMU | ICM-42686 (SPI, 陀螺仪+加速度计) |
| 编码器 | 正交编码器 ×2 (PWMC/PWMD) |
| 电机 | 直流电机 ×2 (PWMB_CH5/CH6) |
| 舵机 | 转向舵机 (PWME_CH5) |
| 显示 | IPS 显示屏 (可选) |
| 调试 | USB CDC 串口 → VOFA 上位机 |

## 代码结构

```
yg_smartcar/
├── main/
│   ├── main.c              # 入口、初始化、主循环
│   ├── main.h              # 全局头文件聚合
│   └── isr.c               # 中断向量表
├── code/
│   ├── vision_track.c/h    # 视觉循迹核心算法
│   ├── vision_isp.c/h      # IPS 显示屏绘制
│   ├── vision_master.c/h   # VOFA 上位机通信
│   ├── vision.c/h          # 视觉任务调度
│   ├── trail.c/h           # 赛道元素判定 + 中线规划
│   ├── control.c/h         # 速度/转向 PID 控制
│   ├── pid.c/h             # PID 控制器实现
│   ├── motor.c/h           # 电机 PWM 驱动
│   ├── servo.c/h           # 舵机驱动
│   ├── encoder.c/h         # 编码器读取
│   ├── icm.c/h             # IMU 姿态解算
│   └── key.c/h             # 按键处理
├── library/                # 开源库 (驱动层)
│   ├── drivers/            # GPIO/PWM/Timer/UART/SPI/I2C/Encoder
│   ├── devices/            # MT9V034/ICM42686/IPS/WiFi
│   ├── common/             # 工具函数
│   └── core/               # MCU 寄存器定义/USB协议栈
└── doc/
    └── CHANGELOG.md
```

## 系统架构

### 中断分配

| 定时器 | 周期 | 用途 |
|--------|------|------|
| TIM_0 | 5ms | ICM-42686 姿态解算 (yaw/roll/pitch) |
| TIM_1 | 10ms | 编码器读取 → 速度PID → 转向PID → PWM输出 |

### 主循环 (仅视觉)

```
track_handle()
  ├─ vision_poll_track()          # 摄像头帧就绪触发
  │    └─ vision_track_process()  # 阈值→二值化→边界→中线
  ├─ track_element_judge()        # 特征分类 → 赛道元素判定
  └─ plan_*_center()              # 按元素类型规划目标中线
```

### 视觉处理管线

```
原始灰度 (188×120)
  → Otsu 阈值 + 分区偏置 (远端行可设独立偏置)
  → 二值化 (赛道=0, 背景=255)
  → 形态学 (闭运算填缝 / 开运算去毛刺 / 4-邻域去椒盐)
  → 逐行边界提取 (中线连续性引导 + 最长跑道搜索)
  → 行间隙线性插值 + 抗眩光突变回退
  → 特征分类 (NORMAL / CROSS / RING_LEFT / RING_RIGHT / LOST)
  → 十字补线 (边界最小二乘拟合 + 向下外推)
  → 前瞻行窗口中位中线 + 帧间 EMA 平滑 + 跳变限幅
  → 输出: center_x, error_x, left[120], right[120], mid[120]
```

### 赛道元素判定与中线规划

| 元素 | 判定条件 | 中线规划 |
|------|---------|---------|
| **直道** STRAIGHT | 默认 | `(近端中线×2 + 远端中线) / 3` |
| **十字** CROSS | bottom 车道宽度突增 | 边界直线拟合外推 |
| **直角弯** RIGHT_ANGLE | 远/近端中线偏移 + 边线丢失 | 内侧边线 − 半车道宽 |
| **环岛** RING | feature == RING_LEFT/RIGHT | 同直道 |
| **断路** BROKEN_RODE | 连续编码器脉冲超阈值 | 陀螺仪 yaw 惯性导航 |

### PID 控制环

| 控制环 | 算法 | 反馈信号 |
|--------|------|---------|
| 左轮速度 | 增量式 PI | `speed_base - encoder_data_dir[0]` |
| 右轮速度 | 增量式 PI | `speed_base - encoder_data_dir[1]` |
| 舵机转向 | 角度 PD | `CENTER_POINT - track_midpoint_target` |
| 惯性导航 | 位置式 PD | `gyro_target - yaw` |

## 编译与烧录

- IDE: **Keil C251**
- Device: STC32G144K246
- Clock: 99MHz (SYS_CLK_99MHZ)
- Memory Model: Huge (STC32_DSP32_HUGE.LIB)
- 使用 `clean.bat` 清理编译产物

## 调试

### VOFA 上位机
`debug_main()` 中切换注释即可在显示模式和控制模式间切换:

```c
void debug_main(void)
{
    //vofa_image_task();   // VOFA 显示模式
    track_handle();         // 控制模式
}
```

上位机同时显示 3 张图: 原始灰度、二值化伪彩、灰度叠加中线。

### 串口输出
控制模式下自动输出赛道元素切换日志:

```
ELEMENT:STRAIGHT center:94 err:0 valid:120
ELEMENT:CROSS center:94 err:0 valid:120
ELEMENT:RIGHT_ANGLE_L center:78 err:-16 valid:115
```

### 按键功能
- KEY1/KEY2: 舵机角度 +/- 10°
- KEY3: 舵机最小角度
- KEY4: 舵机最大角度
- 长按 KEY1/KEY2: 连续调节

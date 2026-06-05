# CLAUDE.md — YG 智能车循迹项目

## 环境

- **MCU**: STC32G144K246 (8051 变种), 99MHz
- **编译器**: Keil C251 — **所有变量声明必须在块开头**（在任何可执行语句之前），不支持 C99 混合声明
- **摄像头**: MT9V034 188×120, 并行 DCMI 接口, 软 I2C 配置 (P14/P15)
- **IMU**: ICM42686 通过 SPI_2 (P02=CS, P03=MOSI, P04=MISO, P05=SCLK, 10MHz Mode 0)
- **舵机**: 转向, 范围 [70,110], 映射: `servo = 90 + wheel_angle × 2.0`, 限制 ±10°
- **构建**: Keil 工程 `KYPROJECT`

## 架构 — 3 层循迹管线

```
vision_track.c  →  trail.c  →  control.c
  (边界提取+中线)    (元素分类)    (转向+速度 PID)
```

### 第 1 层: vision_track.c — 图像处理

1. `Turn_To_Bin` — Otsu 阈值 × 1.075 偏置，亮色→255(赛道), 暗色→0(背景)
2. `Image_Filter` — 8 邻域和阈值滤波（sum ≥ 255×5 → 填白, sum ≤ 255×2 → 填黑）
3. `Image_Draw_Rectan` — 四周 2px 黑边框，防止追踪越界
4. `Get_Start_Point` — 从图像中间向左右搜索黑白交界种子点
5. `Search_L_R` — 双边同步 Moore 8 邻域追踪（左顺时针、右逆时针，同步防交叉）
6. `Get_Left` / `Get_Right` — 点集 → 逐行边界数组
7. `Cross_Fill` — 拐点检测 + 直线拟合补全十字路口缺失边界
8. `Center_Line = (L+R)/2` — 逐行中线
9. `Image_Erro` — 加权平均: `0.375×C[103] + 0.5×C[105] + 0.1×C[106]`
10. 二值图翻转 — 赛道=0, 背景=255（适配 VOFA 显示约定）

**关键内部常量 (188×120 适配)**:

| 常量 | 值 | 说明 |
|------|-----|------|
| `IMG_W` | 188 | 图像宽度 |
| `IMG_H` | 120 | 图像高度 |
| `BORDER_MAX` | 186 | 右边界上限 |
| `USE_NUM` | 360 (=120×3) | Moore 追踪最大步数 |
| `ERRO_ROW_LO/MID/HI` | 103/105/106 | 偏差计算前瞻行 |
| `STRAIGHT_LINE_CNT` | 90 | 直线判断计数 |
| `LOSE_LINE_R_TH` | 184 | 右丢线阈值 |

**已废弃文件** (从工程中移除):

- `boundary_trace.c/h` — 旧的单边追踪，已被 Search_L_R 替代
- `perspective.c/h` — 鸟瞰变换，`VISION_USE_WALLFOLLOW=0` 排除
- `point_set.c/h` — 点集操作，`sqrtf`/`atan2f`/`pts_curvature_3pt` 已迁移至 vision_track.c

### 第 2 层: trail.c — 赛道元素分类

- 分类: STRAIGHT, RIGHT_ANGLE_l/r, CROSS, RING_l/r/c, BROKEN, BROKEN_RODE
- 按元素类型规划目标中点 (`track_midpoint_target`)
- 跳变限制 ±12 px/帧 + EMA 平滑 (25% 新, 75% 旧): `(new + old*3 + 2)/4`
- 十字出口保持: CROSS 结束后保持 CENTER_POINT 3 帧
- VOFA+ 调试输出: `VOFA_FIREWATER=1` 时发送 10 个 float 变量

### 第 3 层: control.c — 电机+转向控制

- 5ms 定时器 ISR (TIM_1): `control_timer_callback()`
- `steering_control()`: 紧急恢复(基于边缘), 正常 PID (Kp=0.40, Kd=0.35, 无 Ki)
- `motor_speed_control()`: 增量 PID 每轮
- `FIXED_SPEED_DEBUG=1` 使用 `FIXED_PWM_DUTY=600` (无速度 PID)
- EMA 转向输出: `steer_smooth * 0.2 + steer_output * 0.8`
- 陀螺仪 (yaw) 仅用于 BROKEN_RODE 航向保持, 不用于普通转弯

## PID 架构 — 禁止修改

- **用户明确声明: "这是一个很成熟的PID架构了，可以不改这个架构实现功能的"**
- `PositionalPID`: 仅 Kp, Kd — 无 Ki, 无积分项, 不要添加字段
- `IncrementalPID`: Kp, Ki, error_prev — 仅用于速度控制
- `AnglePID`: KP, KP2, KD, GKD, error_prev — 当 CASCADE_PID != 1 时使用
- PID 参数定义在 `pid.c`, 不在头文件

## 关键常量

| 常量 | 值 | 位置 |
|----------|-------|----------|
| MT9V034_WIDTH / HEIGHT | 188 / 120 | vision_track.h |
| CENTER_POINT | 94 | trail.h |
| VISION_LOOKAHEAD_Y | HEIGHT-35 = 85 | vision_track.h |
| TRACK_TURN_SHIFT | 28 | trail.c:8 |
| STEER_OUTPUT_LIMIT | 20.0f | control.h |
| FIXED_PWM_DUTY | 600 | control.c:11 |
| CASCADE_PID | 2 (默认) | pid.h:5 |

## 已知陷阱和经验

### C251 编译器

- **所有变量必须在块开头声明** — `int16_t x;` 必须在任何 `if`/`for`/赋值之前。声明后语句 = 语法错误级联
- `(void)param;` 抑制未使用参数警告, 不要用 `param = param;`
- **大局部数组必须声明为 `static`** — 8051 内部 RAM 只有 256 字节, `int HistGram[256]` 这样的局部数组会栈溢出导致编译错误 (C25: syntax error near ';')

### VOFA+ 图像传输

- `debug_main()` 调用 `track_handle()` → `vision_poll_track()` 处理帧, 设置 `g_track_valid`
- 然后 `vofa_image_task()` 发送 3 张图: 原始灰度 (ID=1), 二值化伪彩 (ID=3), 灰度叠加中线 (ID=2)
- `render_pseudo_gray()`: 赛道(0)→220(亮灰), 背景(255)→40(暗灰)
- `render_overlay_mid()`: 拷贝原始灰度, 逐行画 `track->mid[]` 中点, 画当前 center 十字标记
- USB CDC 发送: `vofa_sendGrayscaleImageEx()` 格式 `\nimage:id,size,w,h,bpp\n` + 原始像素数据

### 视觉 / 边缘提取

- Moore 追踪 (`Search_L_R`): 左边界用顺时针 8 邻域种子, 右边界用逆时针, 同步逻辑防止左右交叉
- 同步规则: 右边比左边高时左边等待, 左边方向=7(正上)且高于右边时左边回退
- 停滞检测: 连续 3 次同一点 → 退出追踪
- `Get_Left` 输出 `L_Border = Points_L[j][0] + 1`, `Get_Right` 输出 `R_Border = Points_R[j][0] - 1` (边界点在边界上, 向内偏移 1px)
- 种子点找不到时: 左边界=1, 右边界=186, 中线≈94, 车辆直行

### 十字路口处理 (Cross_Fill)

- 触发条件: `Lose_Line() == 1` (左右边界在中间 40 行范围内各 ≥10 行碰边界)
- 拐点检测: 连续 3 点变化 ≤5, 断点变化 ≥7
- 4 种工况:
  1. 四拐点都找到 → 左右边分别直线拟合填充
  2. 左斜十字 (左两拐点+右上拐点) → 左边填充, 右边用上方趋势外推到底部
  3. 右斜十字 (右上+右下+左上) → 镜像处理
  4. 只有上拐点 → 用上方边界趋势外推到底部
- `Image_Flag_Cross_Fill`: 每帧清零, Case 1-3 设为 1, Case 4 设为 2, 否则保持 0
- 中线 = (L+R)/2, Cross_Fill 已在边界层面处理, 中线直接计算无需额外逻辑

### Trail / 元素分类

- `plan_straight_center` 权重: `(near_mid + far_mid * 2) / 3` — 偏好远点 (67%) 使循迹更平滑
- `plan_turn_center`: 向弯道内侧偏移 `TRACK_TURN_SHIFT/2` (14px) + `lane_w/2`
- 十字检测: `base_w` 从底部行 (HEIGHT-25 到 HEIGHT-5) 计算, 非中间行。阈值: `w > base_w + base_w/3`
- 弯道检测: `dx > lane_w/6` (原 lane_w/5), 需要 ≥9 行丢边

### 控制

- 舵机 `servo_task()` **从未在主循环中调用** — KEY2-4 舵机调整不可达
- `gyro_target = yaw` 仅在 BROKEN_RODE 入口设置; 陀螺仪不用于普通转向
- 紧急恢复: 扫描下半部单边数据, 向可见侧打满舵

### 系统 / 调试

- **LED (PB6) 不闪烁 = `System_Init()` 挂死** 在到达 `main()` while 循环之前
- 最可能的挂死点: SPI_2 传输等待 `SPI2STAT & 0x80` 标志 (ICM42686 不响应)
- 如果没有 "ICM42686 FOUND!" 或 "ICM42686 Init Error!" 打印 = 卡在第一次 SPI 读 `check_id`
- ICM42686 示例代码工作 = 硬件正常, 问题在 smartcar 初始化链
- 初始化顺序: `key → vision(Mt9v034) → icm(IMU) → motor → encoder → servo → control`

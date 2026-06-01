# CLAUDE.md — YG Smart Car Line-Following Project

## Environment
- **MCU**: STC32G144K246 (8051 variant), 99MHz
- **Compiler**: Keil C251 — **requires all variable declarations at the start of each block** (before any executable statement). C99 mixed declarations are NOT supported.
- **Camera**: MT9V034 188×120, parallel DCMI interface, soft I2C config (P14/P15)
- **IMU**: ICM42686 via SPI_2 (P02=CS, P03=MOSI, P04=MISO, P05=SCLK, 10MHz Mode 0)
- **Servo**: steering, range [70,110] servo angle, mapping: `servo = 90 + wheel_angle × 2.0`, clamped to ±10° wheel
- **Build**: Keil project `KYPROJECT`

## Architecture — 3-Layer Tracking Pipeline

```
vision_track.c  →  trail.c  →  control.c
  (edge extraction)  (element classification)  (steering + speed PID)
```

### Layer 1: vision_track.c — 图像处理
1. Otsu 阈值 + 远近分阈
2. 二值化 + 形态学（闭间隙、开毛刺、4邻域去噪）
3. `extract_edges()` — 自底向上逐行扫描，`last_mid` 连续性约束
4. `interpolate_edge_gaps()` — 线性插值填补 ≤5 行的边缘缺失
5. `stabilize_rows_against_glare()` — 回退宽度/中心突变的行
6. `fill_missing_edges_by_width()` — 用中位车道宽度估算缺失边
7. `classify_feature()` — CROSS / RING_LEFT / RING_RIGHT / LOST
8. `project_edges_through_cross()` — 十字锚点区域直线外推（代替 `cross_fill_borders`）
9. `compute_center_error()` — 在 `VISION_LOOKAHEAD_Y`（第85行）取窗口内中位数

### Layer 2: trail.c — Track element classification
- Classifies: STRAIGHT, RIGHT_ANGLE_l/r, CROSS, RING_l/r/c, BROKEN, BROKEN_RODE
- Plans target midpoint per element type (`track_midpoint_target`)
- Jump limiter ±12 px/frame + EMA smoothing (25% new, 75% old): `(new + old*3 + 2)/4`
- Cross exit hold: 3 frames of CENTER_POINT after CROSS ends

### Layer 3: control.c — Motor + steering control
- 5ms timer ISR (TIM_1): `control_timer_callback()`
- `steering_control()`: emergency recovery (edge-based), normal PID (Kp=0.40, Kd=0.35, NO Ki)
- `motor_speed_control()`: IncrementalPID per wheel
- `FIXED_SPEED_DEBUG=1` uses `FIXED_PWM_DUTY=600` (no speed PID)
- EMA steering output: `steer_smooth * 0.2 + steer_output * 0.8`
- Gyro (yaw) only used for BROKEN_RODE heading hold, NOT for normal turns

## PID Architecture — DO NOT MODIFY
- **User explicitly stated: "这是一个很成熟的PID架构了，可以不改这个架构实现功能的"**
- `PositionalPID`: Kp, Kd only — NO Ki, NO integral term. Do not add fields.
- `IncrementalPID`: Kp, Ki, error_prev — exists for speed control only
- `AnglePID`: KP, KP2, KD, GKD, error_prev — used when CASCADE_PID != 1
- PID gains live in `pid.c`, not in headers

## Key Constants
| Constant | Value | Location |
|----------|-------|----------|
| MT9V034_WIDTH / HEIGHT | 188 / 120 | vision_track.h |
| CENTER_POINT | 94 | trail.h or vision config |
| VISION_LOOKAHEAD_Y | HEIGHT-35 = 85 | vision_track.h |
| TRACK_TURN_SHIFT | 28 | trail.c:8 |
| STEER_OUTPUT_LIMIT | 20.0f | control.h |
| FIXED_PWM_DUTY | 600 | control.c:11 |
| CASCADE_PID | 2 (default) | pid.h:5 |

## Known Pitfalls & Lessons Learned

### C251 Compiler
- **All variables must be declared at block start** — `int16_t x;` before any `if`/`for`/assignment. Declaration-after-statement = syntax error cascade.
- `(void)param;` to suppress unused-parameter warnings, NOT `param = param;`

### Vision / Edge Extraction
- `find_widest_run_0()` finds the WIDEST track segment per row — wrong in turns where lane is nearly horizontal (entire image width looks like "track"). Use `find_nearest_run_0()` for fallback when `last_mid` expansion fails.
- **Boundary-touching segments**: when `l <= 2` or `r >= 185`, that edge is likely the image boundary, not a real lane edge. Mark as unknown (-1) so `fill_missing_edges_by_width()` fills it with median lane width.
- `project_edges_through_cross()` — 检测到 CROSS 后，用锚点区域的直线趋势外推替换碰边界的边缘，使中线平滑穿过十字

### Trail / Element Classification
- `plan_straight_center` weights: `(near_mid + far_mid * 2) / 3` — favors far point (67%) for smoother tracking
- `plan_turn_center`: shifts target toward INSIDE of turn by `TRACK_TURN_SHIFT/2` (14px) plus `lane_w/2`
- Cross detection: `base_w` computed from bottom rows (HEIGHT-25 to HEIGHT-5), not middle. Threshold: `w > base_w + base_w/3`
- Turn detection: `dx > lane_w/6` (was lane_w/5), requires ≥9 rows with edge lost

### Control
- Servo `servo_task()` is **never called** in main loop — KEY2-4 servo adjustments are unreachable
- `gyro_target = yaw` only set on BROKEN_RODE entry; gyro NOT used for normal steering
- Emergency recovery: scans bottom half for single-side edge data, applies full-lock steering toward visible side

### System / Debugging
- **LED (PB6) not blinking = `System_Init()` hung** before reaching `main()` while loop
- Most likely hang: SPI_2 transfer waiting for `SPI2STAT & 0x80` flag (ICM42686 not responding)
- If no "ICM42686 FOUND!" or "ICM42686 Init Error!" prints = hang in first SPI read of `check_id`
- ICM42686 example code works = hardware is fine, problem is in smartcar init chain
- Init order: `key → vision(Mt9v034) → icm(IMU) → motor → encoder → servo → control`

### Files NOT to modify
- `pid.h` / `pid.c` struct definitions — mature, user-rejected changes

## 十字路口处理逻辑

### CROSS 检测（classify_feature）
- CROSS 检测使用的边界判断阈值是 **4px**，不是 `VISION_EDGE_NEAR_TH=2`
- 原因：MT9V034 摄像头镜头渐晕（vignette）在 x=183-187 产生伪边界，`r=184` 的行需要被视为碰边界
- 条件：`w > 150（CROSS_WIDE_TH）` 且 `l <= 4` 或 `r >= 183`，连续满足 ≥6 行判定为 CROSS
- 滞回：C 代码中 `cross_hold=4`，检测到 CROSS 后保持 4 帧

### project_edges_through_cross() — 锚点趋势外推
功能：检测到 CROSS 后，替换碰边界的边缘为锚点区域的直线拟合投影。

算法步骤：
1. **找锚点区域**：扫描所有行，收集左右边都不碰边界的行（`l > 4 AND r < 183`）。取最大连续块，需要 ≥20 行，否则跳过
2. **直线拟合**：在锚点区域分别对左边缘和右边缘用最小二乘拟合 `x = k*y + b`，采用 Q10 定点运算
3. **逐行外推**：
   - 缺边行 → 直接用投影值填充
   - 碰边界行（`l <= 4 || r >= 183`）→ 用投影值替换
   - 不碰边界但离锚点区域超过 5 行且中心偏差 >15px → 也用投影值替换
4. 投影值 clamp 到 `[0, 187]`，确保 `l < r`

### 锚点区域注意事项
- 锚点必须是非碰边界的连续可靠行段（通常在 y=32-96）
- 锚点行左边缘 >4，右边缘 <183
- 十字臂残留行（y=0-31，顶部十字臂）会被排除，因为它们虽然不碰边界，但中心偏移且宽度异常
- 锚点不够（<20行）时不处理，保持原始边缘

### 管线流程差异
- **CROSS 帧**：`classify_feature()` → `project_edges_through_cross()` → `rebuild_mid_from_edge_chains()` → `compute_center_error()`
- **非 CROSS 帧**：`classify_feature()` → `fix_boundary_zones()` / `trace_edges_incremental()` → `rebuild_mid_from_edge_chains()` → `compute_center_error()`
- Python 评估脚本中，CROSS 帧会跳过 `trace_edges_incremental()`，因为 2D 骨架追踪会把十字路口当成一个宽区域处理，中心会被拉到图像中心（94），而不是车道原中心（99）

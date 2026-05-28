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

### Layer 1: vision_track.c — Image processing
1. Otsu thresholding + split threshold (near/far regions)
2. Binarization + morphology (close gaps, open spurs, despeckle 4-neighbor)
3. `extract_edges()` — bottom-up row scanning with `last_mid` continuity
4. `interpolate_edge_gaps()` — linear interpolation across ≤5 row gaps
5. `stabilize_rows_against_glare()` — revert rows with width/center jumps
6. `fill_missing_edges_by_width()` — estimate missing edge from median lane width
7. `classify_feature()` — CROSS / RING_LEFT / RING_RIGHT / LOST
8. `cross_fill_borders()` — bidirectional line fitting for cross intersections
9. `compute_center_error()` — windowed median at `VISION_LOOKAHEAD_Y` (row 85)

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
- `cross_fill_borders()` does bidirectional interpolation: finds entry_y (bottom) and break_y (top), fits lines to edges on both sides, interpolates between them.

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

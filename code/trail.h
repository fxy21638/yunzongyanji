#ifndef _TRAIL_H_
#define _TRAIL_H_

#include "ky_headfile.h"
#include "vision_track.h"

/* ---- 常量 ---- */
#define CENTER_POINT (MT9V034_WIDTH / 2)
#define IMAGE_H MT9V034_HEIGHT
#define IMAGE_W MT9V034_WIDTH

#define HUANDAO_ENABLE 1 /* 1=启用环岛检测, 0=跳过 */

/* TRACK_ELEMENT (保持兼容 track_fsm.h) */
typedef enum
{
    NONE,
    START,
    STRAIGHT,
    RIGHT_ANGLE_l,
    RIGHT_ANGLE_r,
    RING_l,
    RING_r,
    RING_c,
    CROSS,
    BROKEN,
    BROKEN_RODE
} TRACK_ELEMENT;

/* 边界搜索参数 */
#define THRESHOLD 15
#define JUMP_NUM 3
#define SEARCH_MAX (IMAGE_W - 2)
#define SEARCH_MIN 1
#define SEARCH_RANGE 10

/* 最长白列参数 */
#define WH_COL_MIN SEARCH_MIN
#define WH_COL_MAX SEARCH_MAX
#define SEARCH_WH_DEN 3
#define WH_COL_NUM ((WH_COL_MAX - WH_COL_MIN) / SEARCH_WH_DEN + 1)
#define WH_WINDOW_SIZE 20
#define WH_ROW_STEP 2
#define WH_COL_STEP 3
#define WH_ROW_MIN 0
#define PHASE1_ROWS 5
#define WH_START_ROW (IMAGE_H - 1 - PHASE1_ROWS)
#define WH_NEXT_OFFSET 10
#define BOTTOM_DARK_GATE 80

/* 前瞻 */
#define TOWPOINT_NORMAL 80
#define TOWPOINT_CROSS 70
#define TOWPOINT_RING 70
#define TOWPOINT_WINDOW 5
#define STRAIGHT_THRESHOLD 60

/* 十字 */
#define CROSS_NONE 0
#define CROSS_CONFIRMED 1
#define CROSS_PHASE_NONE 0
#define CROSS_PHASE_FOUND 1
#define CROSS_PHASE_ENTERING 2
#define CROSS_PHASE_IN_BEND 3
#define CROSS_PHASE_EXITING 4
#define CROSS_INVALID_MIN 10 /* 更快识别, 出弯接十字不误判 */
#define CROSS_ENTERING_TH 35 /* 50→35, 更快进入十字 */
#define CROSS_IN_BEND_TH 25
#define CROSS_EXITING_TH 55
#define DOWN_JUMP_TH 4
#define DOWN_STABLE_TH 5
#define CROSS_STABLE_TH 5
#define UP_JUMP_TH2 6
#define CROSS_TEAR_TH 25

/* 环岛  */
#define HUANDAO_NONE 0
#define HUANDAO_STATE1 1
#define HUANDAO_STATE2 2
#define HUANDAO_STATE2B 3
#define HUANDAO_STATE3 4
#define HUANDAO_STATE4 6
#define HUANDAO_STATE5 7
#define HUANDAO_STATE6 8
#define HUANDAO_STATE7 9
#define HD_R_DOWN_MIN_ROW 35  /* 50→35, 更容易找到拐点 */
#define HD_R_DOWN_MIN_DIST 20 /* 30→20 */
#define HD_R_STABLE_TH 6      /* 8→6, 稳定条件放宽 */
#define HD_R_START_MIN_ROW 110
#define HD_L_CONT_JUMP_TH 3
#define HD_L_EFFECT_MIN 55
#define HD_R_CONT_JUMP_TH 3
#define HD_R_EFFECT_MIN 55
#define HD_L_UP_MAX_COL 8
#define HD_R_UP_STABLE_TH 12
#define HD_R_UP_MAX_COL 180
#define HD_L_UP_INC_TH 20
#define HD_R_UP_INC_TH 20
#define HD_HALF_WIDTH_RIGHT_OFFSET 15

/* 靶子  */
#define TARGET_ROW_START 119
#define TARGET_ROW_END 40
#define TARGET_ROW_STEP 4
#define TARGET_COL_STEP 3
#define TARGET_NEAR_COL_WINDOW 20
#define TARGET_NEAR_COL_WINDOW_WIDE 40
#define TARGET_BORDER_GUARD 4
#define TARGET_MIN_POINTS 2
#define TARGET_ENTER_ROW_LIMIT 110
#define TARGET_LASER_ON_ROW 90
#define TARGET_RED_MAX 256

/* 道路类型 */
struct road_type_t
{
    int8_t straight, bend, cross, l_cross, r_cross, left_cirque, right_cirque;
};

/* 靶子状态 */
typedef enum
{
    TARGET_WAIT_FAR = 0,
    TARGET_TRACK_FAR = 1,
    TARGET_TRACK_NEAR = 2,
    TARGET_FIRE = 3
} target_state_e;

/* ---- 全局变量: 白点+最长白列 ---- */
extern int16_t current_white;
extern int16_t white_length[2][WH_COL_NUM];
extern int16_t white_length_max[2][1];
extern int16_t Search_Stop_Line;
extern int16_t Both_Lost_Time;

/* ---- 全局变量: 边界 ---- */
extern int16_t l_border[IMAGE_H], r_border[IMAGE_H];
extern int16_t image_position[IMAGE_H];
extern int16_t first_end;
extern int8_t l_effect_flag[IMAGE_H], r_effect_flag[IMAGE_H];

/* ---- 全局变量: 误差 ---- */
extern int16_t Image_Error;
extern int16_t posi;

/* ---- 全局变量: 十字 ---- */
extern int16_t l_down_point, r_down_point, l_up_point, r_up_point;
extern uint8_t cross_state, cross_phase;
extern int16_t l_invalid_cnt, r_invalid_cnt;

/* ---- 全局变量: 环岛 ---- */
extern uint8_t huandao_state;
extern int16_t hd_r_down_point, hd_r_up_point, hd_l_up_point, hd_l_turn_point;
extern uint8_t l_huandao_state;

/* ---- 全局变量: 靶子 ---- */
extern volatile target_state_e target_state;
extern volatile int8_t target_flag;
extern int16_t target_center_col, target_center_row, target_focus_col;
extern int16_t target_red_rows[TARGET_RED_MAX];
extern int16_t target_red_cols[TARGET_RED_MAX];
extern int16_t target_red_count;
extern uint8_t g_target_detected;
extern uint8_t g_target_center_x;
extern uint8_t g_target_radius;

/* ---- 全局变量: 道路类型+其他 ---- */
extern struct road_type_t road_type;
extern int16_t sudu_yingzi_val;
extern const uint8_t Half_Road_Wide[120];
extern uint8_t g_track_valid;

/* ---- 函数声明 ---- */
int16_t myabs(int16_t dat);
int16_t limit_ab(int16_t x, int16_t a, int16_t b);
int16_t limit_float(int16_t x, int16_t y);
int16_t calc_diff(int16_t x, int16_t y);

/* ---- extern 变量 ---- */
extern uint8_t g_track_valid;
extern uint8_t g_target_detected, g_target_center_x, g_target_radius;
extern uint8_t g_obstacle_detected, g_obstacle_center_x, g_obstacle_width;
extern int16_t Image_Error, posi;
extern int16_t l_border[IMAGE_H], r_border[IMAGE_H];
extern int16_t image_position[IMAGE_H];
extern int8_t l_effect_flag[IMAGE_H], r_effect_flag[IMAGE_H];
extern int16_t l_effect_num, r_effect_num;
extern int16_t l_invalid_cnt, r_invalid_cnt;
extern uint8_t cross_state, cross_phase, huandao_state;
extern struct road_type_t road_type;
extern const uint8_t Half_Road_Wide[120];

/* ---- 函数声明 ---- */
void search_white(uint8_t *photo, uint16_t point_num);
void search_longest_white_col(void);
void search_border(void);
void GetDet(void);
void search_line(void);
void image_process(void);
void cross_detect(void);
void cross_fill(void);
void huandao_detect(void);
void huandao_fill(void);
void left_huandao_detect(void);
void left_huandao_fill(void);
void target_detect(void);
void laser_off_handler(void);
void element_detect(void);
void debug_ips_display(void); /* IPS 屏幕调试 */

#endif

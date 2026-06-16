#include "ky_headfile.h"
#include "vision_master.h"
#include "vision_track.h"
#include "wireless_vision.h"
#include "trail.h"

// 图像发送总开关: 0=跑车模式(不发图), 1=调试模式(发图)
#define VOFA_IMAGE_ENABLE 1
// 无线图像输出: 0=仅USB, 1=USB+无线
#define WIRELESS_IMAGE_OUTPUT 0
// 图像发送跳帧: 每 N 帧发一次图
#define VOFA_IMAGE_SKIP 3
// 精简图像模式: 0=3张全发, 1=仅发叠加中线图
#define VOFA_IMAGE_LEAN 1

#define DISPLAY_MAX_CHAIN_POINTS MT9V034_HEIGHT
#define DISPLAY_CENTER_POINTS 128
#define DISPLAY_CENTER_Y_BOTTOM (MT9V034_HEIGHT - 20)  // 从底部向上数第20行 = y99
#define DISPLAY_CENTER_Y_TOP    (MT9V034_HEIGHT - 100)  // 从底部向上数第80行 = y39
#define DISPLAY_CENTER_MAX_COUNT (DISPLAY_CENTER_Y_BOTTOM - DISPLAY_CENTER_Y_TOP + 1)
#define DISPLAY_CROSS_BASE_Y0 (MT9V034_HEIGHT - 18)
#define DISPLAY_CROSS_BASE_Y1 (MT9V034_HEIGHT - 6)
#define DISPLAY_CROSS_MIN_STREAK 3
#define DISPLAY_PAIR_Y_GAP_MAX 3
#define DISPLAY_CENTER_X_JUMP_MAX 18
#define DISPLAY_EDGE_NEAR_TH 2
#define DISPLAY_CROSS_TOUCH_MARGIN 4

typedef struct
{
	int16_t x;
	int16_t y;
} display_point_t;

typedef struct
{
	int16_t k_q8;
	int16_t b_q8;
} display_line_q8_t;

extern vision_track_result_t g_track;
extern uint8_t g_track_valid;
extern uint8_t g_vofa_pending;
extern image_t image_data[MT9V034_HEIGHT * MT9V034_WIDTH];
extern uint8_t g_target_detected;
extern uint8_t g_target_center_x;
extern uint8_t g_target_radius;
extern uint8_t g_target_y_mid;

static display_point_t g_left_chain[DISPLAY_MAX_CHAIN_POINTS];
static display_point_t g_right_chain[DISPLAY_MAX_CHAIN_POINTS];
static display_point_t g_center_chain[DISPLAY_CENTER_POINTS];
static uint16_t g_left_count = 0;
static uint16_t g_right_count = 0;
static uint16_t g_center_count = 0;

void image_copy(image_t *img, const uint8_t *src)
{
	memcpy(img, src, MT9V034_IMAGE_SIZE);
}

void vofa_sendGrayscaleImageEx(uint8_t *img, uint16_t width, uint16_t height, uint8_t image_id)
{
	uint8_t header[60];
	uint16_t size = width * height;

	sprintf((char *)header, "\nimage:%d,%d,%d,%d,%d\n",
			image_id, size, width, height, 24);

	usb_cdc_send_buffer(header, strlen((char *)header));
	usb_cdc_send_buffer(img, size);
}

void vofa_sendGrayscaleImage(uint8_t *img, uint16_t width, uint16_t height)
{
	vofa_sendGrayscaleImageEx(img, width, height, VOFA_IMAGE_ID_GRAY);
}

static int16_t abs_i16(int16_t v)
{
	return (v < 0) ? (int16_t)(-v) : v;
}

static int16_t average_lane_width_track(const vision_track_result_t *track, uint16_t y0, uint16_t y1)
{
	uint16_t y;
	long sum = 0;
	uint16_t cnt = 0;

	if (y1 >= MT9V034_HEIGHT)
	{
		y1 = MT9V034_HEIGHT - 1;
	}

	for (y = y0; y <= y1; y++)
	{
		if (track->left[y] >= 0 && track->right[y] >= 0)
		{
			sum += (long)(track->right[y] - track->left[y] + 1);
			cnt++;
		}
	}

	if (cnt == 0)
	{
		return (int16_t)(MT9V034_WIDTH / 3);
	}
	return (int16_t)(sum / cnt);
}

static int16_t detect_cross_break_row_track(const vision_track_result_t *track)
{
	int16_t base_w;
	int16_t y;
	int16_t cross_start = -1;
	uint8_t in_cross = 0;
	uint8_t narrow_streak = 0;

	// 用图像上半部（正常赛道）计算基准宽度，避免十字底部宽行污染 base_w
	base_w = average_lane_width_track(track, (uint16_t)(MT9V034_HEIGHT / 3), (uint16_t)(MT9V034_HEIGHT / 2));
	if (base_w < 8)
	{
		return -1;
	}

	// 从底部向上扫描：先进入十字宽区域，持续追踪最高宽行，
	// 遇到连续窄行（离开十字）后返回十字起始行。
	for (y = (int16_t)(MT9V034_HEIGHT - 1); y >= (int16_t)(MT9V034_HEIGHT / 4); y--)
	{
		if (track->left[(uint16_t)y] >= 0 && track->right[(uint16_t)y] >= 0)
		{
			int16_t w = (int16_t)(track->right[(uint16_t)y] - track->left[(uint16_t)y] + 1);
			if (w > base_w + base_w / 5 ||
				(w > base_w + 12 &&
				 (track->left[(uint16_t)y] <= DISPLAY_CROSS_TOUCH_MARGIN ||
				  track->right[(uint16_t)y] >= (int16_t)(MT9V034_WIDTH - 1 - DISPLAY_CROSS_TOUCH_MARGIN))))
			{
				if (!in_cross)
				{
					in_cross = 1;
				}
				cross_start = y;
				narrow_streak = 0;
			}
			else if (in_cross)
			{
				narrow_streak++;
				if (narrow_streak >= DISPLAY_CROSS_MIN_STREAK)
				{
					return cross_start;
				}
			}
		}
	}

	// 十字延伸到扫描范围顶部
	if (in_cross && cross_start >= 0)
	{
		return cross_start;
	}

	return -1;
}

static uint8_t fit_edge_line_q8_track(const int16_t *edge, uint16_t y0, uint16_t y1, display_line_q8_t *line)
{
	uint16_t y;
	uint16_t n = 0;
	long sum_y = 0;
	long sum_x = 0;
	long sum_yy = 0;
	long sum_xy = 0;
	long denom;
	long numer;

	if (y1 >= MT9V034_HEIGHT)
	{
		y1 = MT9V034_HEIGHT - 1;
	}
	if (y0 > y1)
	{
		return 0;
	}

	for (y = y0; y <= y1; y++)
	{
		if (edge[y] >= 0)
		{
			n++;
			sum_y += y;
			sum_x += edge[y];
			sum_yy += (long)y * y;
			sum_xy += (long)y * edge[y];
		}
	}

	if (n < 4)
	{
		return 0;
	}

	denom = (long)n * sum_yy - sum_y * sum_y;
	if (denom == 0)
	{
		return 0;
	}

	numer = (long)n * sum_xy - sum_y * sum_x;
	line->k_q8 = (int16_t)((numer << 8) / denom);
	line->b_q8 = (int16_t)(((sum_x << 8) - (long)line->k_q8 * sum_y) / (long)n);
	return 1;
}

static int16_t eval_line_q8_track(const display_line_q8_t *line, uint16_t y)
{
	long x_q8 = (long)line->k_q8 * y + line->b_q8;
	if (x_q8 >= 0)
	{
		return (int16_t)((x_q8 + 128) >> 8);
	}
	return (int16_t)((x_q8 - 128) >> 8);
}

static void stabilize_cross_boundaries(const vision_track_result_t *track, int16_t *left_buf, int16_t *right_buf)
{
	int16_t break_row;
	display_line_q8_t left_line;
	display_line_q8_t right_line;
	uint16_t y;
	uint16_t y_fit_start;
	uint16_t y_fit_end;
	static uint8_t cross_hold = 0;

	// 直接使用 trail 层 FSM 过滤后的元素判断，FSM 已含滞回
	if (track_element == CROSS)
	{
		cross_hold = 4;
	}
	else if (cross_hold > 0)
	{
		cross_hold--;
	}

	if (cross_hold == 0)
	{
		return;
	}

	break_row = detect_cross_break_row_track(track);
	if (break_row < 0)
	{
		return;
	}

	// 用十字上方正常赛道的边界做拟合，然后向下外推到十字区域
	if (break_row < 12)
	{
		return;
	}
	y_fit_end = (uint16_t)(break_row - 4);
	y_fit_start = (uint16_t)(break_row - 28);
	if (!fit_edge_line_q8_track(track->left, y_fit_start, y_fit_end, &left_line) ||
		!fit_edge_line_q8_track(track->right, y_fit_start, y_fit_end, &right_line))
	{
		return;
	}

	// 填充十字区域（break_row 往下到底部），保留正常赛道原有边界
	for (y = (uint16_t)break_row; y < MT9V034_HEIGHT; y++)
	{
		left_buf[y] = eval_line_q8_track(&left_line, y);
		right_buf[y] = eval_line_q8_track(&right_line, y);
		if (left_buf[y] < 0)
		{
			left_buf[y] = 0;
		}
		if (right_buf[y] >= (int16_t)MT9V034_WIDTH)
		{
			right_buf[y] = (int16_t)(MT9V034_WIDTH - 1);
		}
		if (left_buf[y] > right_buf[y])
		{
			int16_t t = left_buf[y];
			left_buf[y] = right_buf[y];
			right_buf[y] = t;
		}
	}
}

static void build_boundary_chains(const vision_track_result_t *track)
{
	int16_t y;
	int16_t left_buf[MT9V034_HEIGHT];
	int16_t right_buf[MT9V034_HEIGHT];

	g_left_count = 0;
	g_right_count = 0;

	for (y = 0; y < (int16_t)MT9V034_HEIGHT; y++)
	{
		left_buf[(uint16_t)y] = track->left[(uint16_t)y];
		right_buf[(uint16_t)y] = track->right[(uint16_t)y];
	}

	stabilize_cross_boundaries(track, left_buf, right_buf);

	// 和中线范围一致：从底部向上数第20~80行
	for (y = (int16_t)DISPLAY_CENTER_Y_BOTTOM; y >= (int16_t)DISPLAY_CENTER_Y_TOP; y--)
	{
		if (left_buf[(uint16_t)y] >= 0 && right_buf[(uint16_t)y] >= 0)
		{
			g_left_chain[g_left_count].x = left_buf[(uint16_t)y];
			g_left_chain[g_left_count].y = y;
			g_left_count++;
			g_right_chain[g_right_count].x = right_buf[(uint16_t)y];
			g_right_chain[g_right_count].y = y;
			g_right_count++;
		}
	}
}

static void smooth_chain(display_point_t *chain, uint16_t count)
{
	uint16_t i;
	display_point_t tmp[DISPLAY_MAX_CHAIN_POINTS];

	if (count < 3)
	{
		return;
	}

	for (i = 0; i < count; i++)
	{
		tmp[i] = chain[i];
	}

	for (i = 1; i + 1 < count; i++)
	{
		chain[i].x = (int16_t)((tmp[i - 1].x + tmp[i].x + tmp[i + 1].x) / 3);
		chain[i].y = tmp[i].y;
	}
}

static int16_t find_right_match_x(int16_t y, int16_t left_x)
{
	uint16_t i;
	int16_t best_x = -1;
	int16_t best_score = 32767;

	for (i = 0; i < g_right_count; i++)
	{
		int16_t dy = abs_i16((int16_t)(g_right_chain[i].y - y));
		int16_t dx = (int16_t)(g_right_chain[i].x - left_x);
		int16_t score;

		if (dy > DISPLAY_PAIR_Y_GAP_MAX || dx <= 0)
		{
			continue;
		}

		score = (int16_t)(dy * 8 + abs_i16(dx));
		if (score < best_score)
		{
			best_score = score;
			best_x = g_right_chain[i].x;
		}
	}

	return best_x;
}

static uint8_t row_is_clean_for_center(int16_t left_x, int16_t right_x)
{
	if (left_x <= DISPLAY_EDGE_NEAR_TH)
	{
		return 0;
	}
	if (right_x >= (int16_t)(MT9V034_WIDTH - 1 - DISPLAY_EDGE_NEAR_TH))
	{
		return 0;
	}
	return 1;
}

static void build_center_chain_from_boundaries(const vision_track_result_t *track)
{
	int16_t left_buf[MT9V034_HEIGHT];
	int16_t right_buf[MT9V034_HEIGHT];
	display_line_q8_t left_line;
	display_line_q8_t right_line;
	uint16_t y;
	uint16_t block_start;
	uint16_t block_end;
	uint16_t block_len;
	uint16_t best_start;
	uint16_t best_end;
	uint16_t best_len;
	uint8_t in_block;
	int16_t l;
	int16_t r;
	int16_t proj_l;
	int16_t proj_r;
	uint16_t i;

	g_center_count = 0;
	if (track == NULL)
	{
		return;
	}

	for (y = 0; y < MT9V034_HEIGHT; y++)
	{
		left_buf[y] = track->left[y];
		right_buf[y] = track->right[y];
	}

	best_len = 0;
	in_block = 0;
	block_start = 0;
	for (y = 0; y < MT9V034_HEIGHT; y++)
	{
		if (left_buf[y] >= 0 && right_buf[y] >= 0 && row_is_clean_for_center(left_buf[y], right_buf[y]))
		{
			if (!in_block)
			{
				block_start = y;
				in_block = 1;
			}
		}
		else if (in_block)
		{
			block_end = (uint16_t)(y - 1);
			block_len = (uint16_t)(block_end - block_start + 1);
			if (block_len > best_len)
			{
				best_len = block_len;
				best_start = block_start;
				best_end = block_end;
			}
			in_block = 0;
		}
	}

	if (in_block)
	{
		block_end = (uint16_t)(MT9V034_HEIGHT - 1);
		block_len = (uint16_t)(block_end - block_start + 1);
		if (block_len > best_len)
		{
			best_len = block_len;
			best_start = block_start;
			best_end = block_end;
		}
	}

	if (best_len >= 4 &&
		fit_edge_line_q8_track(left_buf, best_start, best_end, &left_line) &&
		fit_edge_line_q8_track(right_buf, best_start, best_end, &right_line))
	{
		for (y = 0; y < MT9V034_HEIGHT; y++)
		{
			if (left_buf[y] < 0 || right_buf[y] < 0 || !row_is_clean_for_center(left_buf[y], right_buf[y]))
			{
				proj_l = eval_line_q8_track(&left_line, y);
				proj_r = eval_line_q8_track(&right_line, y);
				if (proj_l < 0)
				{
					proj_l = 0;
				}
				if (proj_r >= (int16_t)MT9V034_WIDTH)
				{
					proj_r = (int16_t)(MT9V034_WIDTH - 1);
				}
				if (proj_l > proj_r)
				{
					l = proj_l;
					proj_l = proj_r;
					proj_r = l;
				}
				left_buf[y] = proj_l;
				right_buf[y] = proj_r;
			}
		}

		for (y = DISPLAY_CENTER_Y_BOTTOM; y >= DISPLAY_CENTER_Y_TOP; y--)
		{
			if (left_buf[y] >= 0 && right_buf[y] >= 0 && left_buf[y] < right_buf[y])
			{
				g_center_chain[g_center_count].x = (int16_t)((left_buf[y] + right_buf[y]) / 2);
				g_center_chain[g_center_count].y = (int16_t)y;
				g_center_count++;
			}
		}

		if (g_center_count >= 3)
		{
			smooth_chain(g_center_chain, g_center_count);
		}
		if (g_center_count > 0)
		{
			return;
		}
	}

	if (g_left_count < 2 || g_right_count < 2)
	{
		return;
	}

	smooth_chain(g_left_chain, g_left_count);
	smooth_chain(g_right_chain, g_right_count);

	for (i = 0; i < g_left_count; i++)
	{
		int16_t rx = find_right_match_x(g_left_chain[i].y, g_left_chain[i].x);
		if (rx >= 0)
		{
			if (g_center_count < DISPLAY_CENTER_MAX_COUNT)
			{
				g_center_chain[g_center_count].x = (int16_t)((g_left_chain[i].x + rx) / 2);
				g_center_chain[g_center_count].y = g_left_chain[i].y;
				g_center_count++;
			}
			else
			{
				break;
			}
		}
	}
}

// 虚线横线: dash_len 像素有, gap_len 像素无
static void draw_dashed_hline(uint8_t *out, int16_t y, uint8_t dash_len, uint8_t gap_len)
{
	int16_t x;
	uint8_t phase = 0;
	uint8_t cnt = 0;

	if (y < 0 || y >= (int16_t)MT9V034_HEIGHT) return;

	for (x = 0; x < (int16_t)MT9V034_WIDTH; x++)
	{
		if (cnt == 0)
		{
			cnt = (phase == 0) ? dash_len : gap_len;
			phase = (uint8_t)(1 - phase);
		}
		if (phase == 0)
			out[(uint16_t)y * MT9V034_WIDTH + (uint16_t)x] = 0;
		cnt--;
	}
}

// 绘制关键参考行标记
static void draw_reference_lines(uint8_t *out)
{
	// 中线绘制范围（底部标记）
	draw_dashed_hline(out, (int16_t)DISPLAY_CENTER_Y_BOTTOM, 2, 10);
	draw_dashed_hline(out, (int16_t)DISPLAY_CENTER_Y_TOP,    2, 10);

	// 直道远点 row60（权重67%）
	draw_dashed_hline(out, (int16_t)(MT9V034_HEIGHT / 2), 4, 4);

	// 主前视行 row85（CROSS取中心、compute_center_error主行）
	draw_dashed_hline(out, (int16_t)VISION_LOOKAHEAD_Y, 4, 4);

	// 直道近点 row98（权重33%）
	draw_dashed_hline(out, (int16_t)(MT9V034_HEIGHT - 22), 4, 4);
}

static void draw_thick_point(uint8_t *out, int16_t x, int16_t y)
{
	int16_t xx;

	if (x < 0 || x >= (int16_t)MT9V034_WIDTH || y < 0 || y >= (int16_t)MT9V034_HEIGHT)
	{
		return;
	}

	for (xx = x - 1; xx <= x + 1; xx++)
	{
		if (xx >= 0 && xx < (int16_t)MT9V034_WIDTH)
		{
			out[(uint16_t)y * MT9V034_WIDTH + (uint16_t)xx] = 0;
		}
	}
}

static void draw_segment(uint8_t *out, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
	int16_t dx = abs_i16((int16_t)(x1 - x0));
	int16_t dy = abs_i16((int16_t)(y1 - y0));
	int16_t steps = (dx > dy) ? dx : dy;
	int16_t step;

	if (steps == 0)
	{
		draw_thick_point(out, x0, y0);
		return;
	}

	for (step = 0; step <= steps; step++)
	{
		int16_t px = (int16_t)(x0 + ((x1 - x0) * step) / steps);
		int16_t py = (int16_t)(y0 + ((y1 - y0) * step) / steps);
		draw_thick_point(out, px, py);
	}
}

static void draw_center_chain(uint8_t *out)
{
	uint16_t i;
	int16_t last_x = -1;
	int16_t last_y = -1;
	int16_t x;
	int16_t y;
	int16_t dy;
	int16_t dx;

	if (g_center_count == 0)
	{
		return;
	}

	for (i = 0; i < g_center_count; i++)
	{
		x = g_center_chain[i].x;
		y = g_center_chain[i].y;
		draw_thick_point(out, x, y);

		if (last_x >= 0)
		{
			dy = abs_i16((int16_t)(y - last_y));
			dx = abs_i16((int16_t)(x - last_x));
			if (dy <= DISPLAY_PAIR_Y_GAP_MAX && dx <= DISPLAY_CENTER_X_JUMP_MAX)
			{
				draw_segment(out, last_x, last_y, x, y);
			}
		}

		last_x = x;
		last_y = y;
	}
}

static void draw_boundary_chains(uint8_t *out)
{
	uint16_t i;
	int16_t last_x, last_y;

	if (g_left_count >= 2)
	{
		last_x = g_left_chain[0].x; last_y = g_left_chain[0].y;
		for (i = 1; i < g_left_count; i++)
		{
			if (abs_i16((int16_t)(g_left_chain[i].y - last_y)) <= DISPLAY_PAIR_Y_GAP_MAX)
			{
				draw_segment(out, last_x, last_y, g_left_chain[i].x, g_left_chain[i].y);
			}
			last_x = g_left_chain[i].x; last_y = g_left_chain[i].y;
		}
	}
	if (g_right_count >= 2)
	{
		last_x = g_right_chain[0].x; last_y = g_right_chain[0].y;
		for (i = 1; i < g_right_count; i++)
		{
			if (abs_i16((int16_t)(g_right_chain[i].y - last_y)) <= DISPLAY_PAIR_Y_GAP_MAX)
			{
				draw_segment(out, last_x, last_y, g_right_chain[i].x, g_right_chain[i].y);
			}
			last_x = g_right_chain[i].x; last_y = g_right_chain[i].y;
		}
	}
}

// Draw a single pixel if in bounds
static void overlay_pixel(uint8_t *out, int16_t px, int16_t py, uint8_t val)
{
	if (px < 0 || px >= (int16_t)MT9V034_WIDTH || py < 0 || py >= (int16_t)MT9V034_HEIGHT)
		return;
	out[(uint16_t)py * MT9V034_WIDTH + (uint16_t)px] = val;
}

// Draw a cross marker for corner points (3px arms)
static void draw_corner_cross(uint8_t *out, int16_t cx, int16_t cy, uint8_t val)
{
	int8_t d;
	for (d = -3; d <= 3; d++)
	{
		overlay_pixel(out, (int16_t)(cx + d), cy, val);
		overlay_pixel(out, cx, (int16_t)(cy + d), val);
	}
}

// Draw BEV midline point set as dark dots
static void draw_bev_midline_overlay(uint8_t *out, const vision_track_result_t *track)
{
	uint8_t i;
	for (i = 0; i < track->mid_step; i++)
	{
		int16_t px;
		int16_t py;
		px = (int16_t)track->mid_pts[i][0];
		py = (int16_t)track->mid_pts[i][1];
		// Draw 2x2 dot for visibility
		overlay_pixel(out, px, py, 0);
		overlay_pixel(out, (int16_t)(px + 1), py, 0);
		overlay_pixel(out, px, (int16_t)(py + 1), 0);
		overlay_pixel(out, (int16_t)(px + 1), (int16_t)(py + 1), 0);
	}
}

// Draw BEV boundary points (left=dark, right=bright dots)
static void draw_bev_boundaries_overlay(uint8_t *out, const vision_track_result_t *track)
{
	uint8_t i;
	int16_t px;
	int16_t py;

	for (i = 0; i < track->left_bev_step; i++)
	{
		px = (int16_t)track->left_bev[i][0];
		py = (int16_t)track->left_bev[i][1];
		overlay_pixel(out, px, py, 30);
		overlay_pixel(out, (int16_t)(px + 1), py, 30);
	}
	for (i = 0; i < track->right_bev_step; i++)
	{
		px = (int16_t)track->right_bev[i][0];
		py = (int16_t)track->right_bev[i][1];
		overlay_pixel(out, px, py, 200);
		overlay_pixel(out, (int16_t)(px + 1), py, 200);
	}
}

// Draw per-row mid[] array directly as dots (row by row)
static void draw_per_row_mid_overlay(uint8_t *out, const vision_track_result_t *track)
{
	uint16_t y;
	int16_t prev_valid;
	uint8_t has_prev;

	has_prev = 0;
	prev_valid = 0;

	for (y = 0; y < MT9V034_HEIGHT; y++)
	{
		int16_t m;
		int16_t lb;
		int16_t rb;

		m = track->mid[(uint16_t)y];
		if (m < 0 || m >= (int16_t)MT9V034_WIDTH)
			continue;

		lb = track->left[y];
		rb = track->right[y];
		if (lb >= 0 && rb >= 0 && (m < lb || m > rb))
			continue;

		{
			// Draw 3-pixel bar
			overlay_pixel(out, m, (int16_t)y, 0);
			if (m > 0) overlay_pixel(out, (int16_t)(m - 1), (int16_t)y, 0);
			if (m < (int16_t)(MT9V034_WIDTH - 1)) overlay_pixel(out, (int16_t)(m + 1), (int16_t)y, 0);

			// Fill gap from previous valid row
			if (has_prev)
			{
				int16_t dm;
				dm = (int16_t)(m - prev_valid);
				if (dm < 0) dm = (int16_t)(-dm);
				if (dm > 1 && dm < 50)
				{
					uint8_t k;
					for (k = 1; k < (uint8_t)dm; k++)
					{
						int16_t mx;
						mx = (int16_t)(prev_valid + (int16_t)((m - prev_valid) * (int16_t)k / dm));
						overlay_pixel(out, mx, (int16_t)y, 0);
					}
				}
			}
			prev_valid = m;
			has_prev = 1;
		}
	}
}

static void draw_current_center_overlay(uint8_t *out, const vision_track_result_t *track)
{
	int16_t cx;
	int16_t cy;

	if (track->center_x < 0 || track->center_x >= (int16_t)MT9V034_WIDTH)
	{
		return;
	}

	cx = track->center_x;
	cy = (int16_t)VISION_LOOKAHEAD_Y;
	if (cy < 0)
	{
		cy = 0;
	}
	if (cy >= (int16_t)MT9V034_HEIGHT)
	{
		cy = (int16_t)(MT9V034_HEIGHT - 1);
	}

	draw_corner_cross(out, cx, cy, 0);
}

// 5×7 点阵字库 (仅数字 0-9 + 空格)
// 每字符 5 字节, 列优先, bit0=顶部像素
static const uint8_t s_font_5x7[11][5] =
{
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 空格 (索引10)
};

static void font_draw_char(uint8_t *img, int16_t cx, int16_t cy, uint8_t ch, uint8_t color)
{
    uint8_t col;
    int16_t row;
    uint16_t idx;
    int16_t px;
    int16_t py;

    if (ch > 10) return;

    for (col = 0; col < 5; col++)
    {
        px = cx + (int16_t)col;
        if (px < 0 || px >= (int16_t)MT9V034_WIDTH) continue;

        for (row = 0; row < 7; row++)
        {
            py = cy + row;
            if (py < 0 || py >= (int16_t)MT9V034_HEIGHT) continue;

            if (s_font_5x7[ch][col] & (1 << row))
            {
                idx = (uint16_t)py * MT9V034_WIDTH + (uint16_t)px;
                img[idx] = color;
            }
        }
    }
}

static void draw_element_indicator(uint8_t *out, TRACK_ELEMENT elem)
{
    uint8_t tens;
    uint8_t ones;
    int16_t x0;
    int16_t y0;

    x0 = (int16_t)(MT9V034_WIDTH - 20);
    y0 = (int16_t)(MT9V034_HEIGHT - 12);

    tens = (uint8_t)elem / 10;
    ones = (uint8_t)elem % 10;

    if (tens > 0)
    {
        font_draw_char(out, x0, y0, tens, 220);
        font_draw_char(out, x0 + (int16_t)6, y0, ones, 220);
    }
    else
    {
        font_draw_char(out, x0 + (int16_t)3, y0, ones, 220);
    }
}

/* 靶子绘制: 检测到黑色圆环时, 在叠加图上画十字准心 + 圆环轮廓 */
static void draw_target_overlay(uint8_t *out)
{
    int16_t cx;
    int16_t cy;
    int16_t r;
    int16_t y;
    int16_t d;
    int16_t x0;
    int16_t y0;
    int16_t x;

    if (!g_target_detected)
        return;

    cx = (int16_t)g_target_center_x;
    cy = (int16_t)g_target_y_mid;
    r  = (int16_t)g_target_radius;

    if (cx < 5 || cx >= (int16_t)(MT9V034_WIDTH - 5))
        return;
    if (cy < 5 || cy >= (int16_t)(MT9V034_HEIGHT - 5))
        return;
    if (r < 1 || r > 80)
        return;

    /* 十字准心: 7px 臂长 */
    for (d = -7; d <= 7; d++)
    {
        overlay_pixel(out, (int16_t)(cx + d), cy, 0);
        overlay_pixel(out, cx, (int16_t)(cy + d), 0);
    }

    /* 垂直虚线: 扫描范围内, 标出靶心列 */
    y0 = (int16_t)(MT9V034_HEIGHT - 25);   /* 对应 trail.c TARGET_SCAN_Y_START = 95 */
    for (y = (int16_t)(MT9V034_HEIGHT / 4); y <= y0; y++)  /* TARGET_SCAN_Y_END = 30 */
    {
        if ((y & 3) == 0)
            overlay_pixel(out, cx, y, 0);
    }

    /* 水平虚线: 在靶心行标出靶环宽度 */
    x0 = cx - r;
    if (x0 < 0) x0 = 0;
    for (x = x0; x <= cx + r && x < (int16_t)MT9V034_WIDTH; x++)
    {
        if ((x & 3) == 0)
            overlay_pixel(out, x, cy, 0);
    }

    /* 圆环轮廓: Bresenham 中点画圆, 虚线 */
    {
        int16_t xi;
        int16_t yi;
        int16_t d;

        xi = 0;
        yi = r;
        d = (int16_t)(1 - r);

        while (xi <= yi)
        {
            /* 8 个对称点, 隔点画虚线 */
            if ((xi & 1) == 0)
            {
                overlay_pixel(out, (int16_t)(cx + xi), (int16_t)(cy + yi), 0);
                overlay_pixel(out, (int16_t)(cx - xi), (int16_t)(cy + yi), 0);
                overlay_pixel(out, (int16_t)(cx + xi), (int16_t)(cy - yi), 0);
                overlay_pixel(out, (int16_t)(cx - xi), (int16_t)(cy - yi), 0);
                overlay_pixel(out, (int16_t)(cx + yi), (int16_t)(cy + xi), 0);
                overlay_pixel(out, (int16_t)(cx - yi), (int16_t)(cy + xi), 0);
                overlay_pixel(out, (int16_t)(cx + yi), (int16_t)(cy - xi), 0);
                overlay_pixel(out, (int16_t)(cx - yi), (int16_t)(cy - xi), 0);
            }

            if (d < 0)
            {
                d += (int16_t)(2 * xi + 3);
            }
            else
            {
                d += (int16_t)(2 * (xi - yi) + 5);
                yi--;
            }
            xi++;
        }
    }
}

static void render_overlay_mid(uint8_t *out, const uint8_t *gray, const vision_track_result_t *track)
{
	memcpy(out, gray, MT9V034_IMAGE_SIZE);

	draw_per_row_mid_overlay(out, track);
	draw_bev_boundaries_overlay(out, track);
	draw_bev_midline_overlay(out, track);
	draw_current_center_overlay(out, track);
	draw_element_indicator(out, track_element);
	draw_target_overlay(out);
}

static void render_pseudo_gray(uint8_t *out, const uint8_t *bin, const vision_track_result_t *track)
{
	uint16_t i;

	(void)track;

	for (i = 0; i < MT9V034_IMAGE_SIZE; i++)
	{
		out[i] = (bin[i] == 0) ? 220 : 40;
	}
}

void vofa_image_task(void)
{
	static uint8_t skip_cnt = 0;

#if (VOFA_IMAGE_ENABLE == 0)
	g_vofa_pending = 0;
	return;
#endif

	if (!g_vofa_pending)
		return;

	if (++skip_cnt < VOFA_IMAGE_SKIP)
	{
		g_vofa_pending = 0;
		return;
	}
	skip_cnt = 0;

#if (VOFA_IMAGE_LEAN == 0)
	// 1. 原始灰度图
	vofa_sendGrayscaleImageEx((uint8_t *)mt9v034_image, MT9V034_WIDTH, MT9V034_HEIGHT, VOFA_IMAGE_ID_GRAY);
#if (WIRELESS_IMAGE_OUTPUT == 1)
	wireless_vision_send_image((uint8_t *)mt9v034_image, MT9V034_WIDTH, MT9V034_HEIGHT, VOFA_IMAGE_ID_GRAY);
#endif

	// 2. 二值化伪彩图
	render_pseudo_gray((uint8_t *)image_data, (const uint8_t *)image_data, &g_track);
	vofa_sendGrayscaleImageEx((uint8_t *)image_data, MT9V034_WIDTH, MT9V034_HEIGHT, VOFA_IMAGE_ID_PSEUDO);
#if (WIRELESS_IMAGE_OUTPUT == 1)
	wireless_vision_send_image((uint8_t *)image_data, MT9V034_WIDTH, MT9V034_HEIGHT, VOFA_IMAGE_ID_PSEUDO);
#endif
#endif // VOFA_IMAGE_LEAN

	// 3. 灰度叠加中线图（覆盖 image_data，源图为原始灰度）
	render_overlay_mid((uint8_t *)image_data, (const uint8_t *)mt9v034_image, &g_track);
	vofa_sendGrayscaleImageEx((uint8_t *)image_data, MT9V034_WIDTH, MT9V034_HEIGHT, VOFA_IMAGE_ID_OVERLAY);
#if (WIRELESS_IMAGE_OUTPUT == 1)
	wireless_vision_send_image((uint8_t *)image_data, MT9V034_WIDTH, MT9V034_HEIGHT, VOFA_IMAGE_ID_OVERLAY);
#endif

	g_vofa_pending = 0;
}

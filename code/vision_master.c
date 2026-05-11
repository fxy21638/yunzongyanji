#include "ky_headfile.h"
#include "vision_master.h"
#include "vision_track.h"

#define DISPLAY_MAX_CHAIN_POINTS MT9V034_HEIGHT
#define DISPLAY_CENTER_POINTS 128
#define DISPLAY_CROSS_BASE_Y0 (MT9V034_HEIGHT - 18)
#define DISPLAY_CROSS_BASE_Y1 (MT9V034_HEIGHT - 6)
#define DISPLAY_CROSS_MIN_STREAK 3
#define DISPLAY_PAIR_Y_GAP_MAX 3
#define DISPLAY_CENTER_X_JUMP_MAX 18

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

static vision_track_result_t g_vofa_track;
extern image_t image_data[MT9V034_HEIGHT * MT9V034_WIDTH];

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
	uint8_t streak = 0;

	base_w = average_lane_width_track(track, DISPLAY_CROSS_BASE_Y0, DISPLAY_CROSS_BASE_Y1);
	if (base_w < 20)
	{
		return -1;
	}

	for (y = (int16_t)(DISPLAY_CROSS_BASE_Y0 - 1); y >= (int16_t)(MT9V034_HEIGHT / 4); y--)
	{
		if (track->left[(uint16_t)y] >= 0 && track->right[(uint16_t)y] >= 0)
		{
			int16_t w = (int16_t)(track->right[(uint16_t)y] - track->left[(uint16_t)y] + 1);
			if (w > base_w + base_w / 3)
			{
				streak++;
				if (streak >= DISPLAY_CROSS_MIN_STREAK)
				{
					return y;
				}
			}
			else
			{
				streak = 0;
			}
		}
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
	uint16_t y0;
	uint16_t y1;

	if (track->feature != VISION_FEATURE_CROSS)
	{
		return;
	}

	break_row = detect_cross_break_row_track(track);
	if (break_row < 0)
	{
		return;
	}

	y0 = (uint16_t)(break_row + 4);
	y1 = (uint16_t)(break_row + 24);
	if (!fit_edge_line_q8_track(track->left, y0, y1, &left_line) ||
		!fit_edge_line_q8_track(track->right, y0, y1, &right_line))
	{
		return;
	}

	for (y = 0; y <= (uint16_t)break_row; y++)
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

	for (y = (int16_t)(MT9V034_HEIGHT - 1); y >= 0; y--)
	{
		if (left_buf[(uint16_t)y] >= 0 && right_buf[(uint16_t)y] >= 0)
		{
			if (g_left_count < DISPLAY_MAX_CHAIN_POINTS)
			{
				g_left_chain[g_left_count].x = left_buf[(uint16_t)y];
				g_left_chain[g_left_count].y = y;
				g_left_count++;
			}
			if (g_right_count < DISPLAY_MAX_CHAIN_POINTS)
			{
				g_right_chain[g_right_count].x = right_buf[(uint16_t)y];
				g_right_chain[g_right_count].y = y;
				g_right_count++;
			}
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

static void build_center_chain_from_boundaries(void)
{
	uint16_t i;

	g_center_count = 0;
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
			if (g_center_count < DISPLAY_CENTER_POINTS)
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

	if (g_center_count == 0)
	{
		return;
	}

	for (i = 0; i < g_center_count; i++)
	{
		int16_t x = g_center_chain[i].x;
		int16_t y = g_center_chain[i].y;

		if (last_x >= 0)
		{
			int16_t dy = abs_i16((int16_t)(y - last_y));
			int16_t dx = abs_i16((int16_t)(x - last_x));
			if (dy <= DISPLAY_PAIR_Y_GAP_MAX && dx <= DISPLAY_CENTER_X_JUMP_MAX)
			{
				draw_segment(out, last_x, last_y, x, y);
			}
		}

		last_x = x;
		last_y = y;
	}
}

static void render_overlay_mid(uint8_t *out, const uint8_t *gray, const vision_track_result_t *track)
{
	build_boundary_chains(track);
	build_center_chain_from_boundaries();
	memcpy(out, gray, MT9V034_IMAGE_SIZE);
	draw_center_chain(out);
}

static void render_pseudo_gray(uint8_t *out, const uint8_t *bin, const vision_track_result_t *track)
{
	uint16_t i;

	build_boundary_chains(track);
	build_center_chain_from_boundaries();

	for (i = 0; i < MT9V034_IMAGE_SIZE; i++)
	{
		out[i] = (bin[i] == 0) ? 220 : 40;
	}

	draw_center_chain(out);
}

void vofa_image_task(void)
{
	if (mt9v034_frame_ready)
	{
		vision_track_process((const uint8_t *)mt9v034_image, (uint8_t *)image_data, &g_vofa_track);

		vofa_sendGrayscaleImageEx((uint8_t *)mt9v034_image, MT9V034_WIDTH, MT9V034_HEIGHT, VOFA_IMAGE_ID_GRAY);

		render_overlay_mid((uint8_t *)image_data, (const uint8_t *)mt9v034_image, &g_vofa_track);
		vofa_sendGrayscaleImageEx((uint8_t *)image_data, MT9V034_WIDTH, MT9V034_HEIGHT, VOFA_IMAGE_ID_OVERLAY);

		vision_track_process((const uint8_t *)mt9v034_image, (uint8_t *)image_data, &g_vofa_track);
		render_pseudo_gray((uint8_t *)image_data, (const uint8_t *)image_data, &g_vofa_track);
		vofa_sendGrayscaleImageEx((uint8_t *)image_data, MT9V034_WIDTH, MT9V034_HEIGHT, VOFA_IMAGE_ID_PSEUDO);

		mt9v034_frame_ready = 0;
	}
}

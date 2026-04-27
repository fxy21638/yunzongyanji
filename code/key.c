#include "key.h"

uint8_t key_id;

void key_system_Init(void)
{
	// 按键初始化 (低电平有效)
    key_init(KEY1_ID, KEY1_PIN, KEY_ACTIVE_LOW);
    key_init(KEY2_ID, KEY2_PIN, KEY_ACTIVE_LOW);
    key_init(KEY3_ID, KEY3_PIN, KEY_ACTIVE_LOW);
    key_init(KEY4_ID, KEY4_PIN, KEY_ACTIVE_LOW);
}



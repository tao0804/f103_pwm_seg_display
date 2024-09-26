#ifndef MY_KEY_H
#define MY_KEY_H

#include "stm32f1xx_hal.h"

// 按键状态定义
#define KEY_NOT_PRESSED 0
#define KEY_PRESSED     3

extern uint8_t key1_state;
extern uint8_t key2_state;

void key_init(void);	// 按键初始化
void key_main(void);	// 按键状态刷新
uint8_t key_scan(void);	// 按键扫描

#endif    // KEY_H


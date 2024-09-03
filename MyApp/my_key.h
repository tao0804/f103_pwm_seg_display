#ifndef MY_KEY_H
#define MY_KEY_H

#include "stm32f1xx_hal.h"

// 按键状态定义
#define KEY_NOT_PRESSED   0
#define KEY_PRESSED 	3
#define KEY1        1	// ?
#define KEY2        2

// 有两个方向，一个是key_status = key1/2;另一种是key1/2_status = pressed
// typedef enum {
//     KEY_IDLE = 0,        // 按键空闲（未按下）
//     KEY1_PRESSED,         // 按键按下
//     KEY2_PRESSED,         // 按键按下
//     KEY_HELD,            // 按键保持（长按）
//     KEY_RELEASED         // 按键释放
// } KeyState_t;

extern uint8_t key1_state;
extern uint8_t key2_state;

void key_init(void);         // 按键初始化
void key_main(void);         // 按键状态刷新
uint8_t key_scan(void);      // 按键扫描

#endif // KEY_H

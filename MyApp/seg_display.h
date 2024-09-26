#ifndef __SEG_DISPLAY_H
#define __SEG_DISPLAY_H

#include "stm32f103xb.h"
#include "stdbool.h"

// 段选配置结构体
typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} SegPinConfig;

extern uint8_t currentDigit;
extern uint8_t segCode_index;

// 段选引脚配置 (A-G和DP)
extern const SegPinConfig segPins[8];

// 位选引脚配置 (D1-D4)
extern const SegPinConfig digitPins[4];

// 宏定义：是否显示首位的0
#define SHOW_LEADING_ZERO 1	// 设置为1显示首位0，设置为0不显示

// 函数声明
void seg_init(void);
void digCur_position_change(void);
void increase_value(void);
// void seg_setDisplayNum(uint16_t num);
void seg_main(void);
void seg_setDisplayNum(uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4);
#endif


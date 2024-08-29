#ifndef __SEG_DISPLAY_H
#define __SEG_DISPLAY_H

#include "stm32f103xb.h"


// 段选配置结构体
typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} SegPinConfig;

// 段选引脚配置 (A-G和DP)
extern const SegPinConfig segPins[8];

// 位选引脚配置 (D1-D4)
extern const SegPinConfig digitPins[4];

// 宏定义：是否显示首位的0
#define SHOW_LEADING_ZERO 1    // 设置为1显示首位0，设置为0不显示

#if SHOW_LEADING_ZERO == 0
	if (num == 0 && currentDigit != 3 && leadingZeroFlag == 0) {
		// 如果当前位是0且不是最后一位，且未遇到非零数字，则不显示
		code = 0x00;
	} else {
		leadingZeroFlag = 1;    // 遇到非零数字，后续都显示
	}
#endif

// 函数声明
void seg_init(void);
void seg_setDisplayNum(uint16_t num);
void seg_main(void);

#endif

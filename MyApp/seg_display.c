#include "seg_display.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "math.h"

// 段选引脚配置数组
const SegPinConfig segPins[8] = {
	{GPIOB, GPIO_PIN_9 }, // SEG_A
	{GPIOA, GPIO_PIN_15}, // SEG_B
	{GPIOB, GPIO_PIN_4 }, // SEG_C
	{GPIOB, GPIO_PIN_6 }, // SEG_D
	{GPIOB, GPIO_PIN_7 }, // SEG_E
	{GPIOB, GPIO_PIN_8 }, // SEG_F
	{GPIOB, GPIO_PIN_3 }, // SEG_G
	{GPIOB, GPIO_PIN_5 }  // SEG_DP
};

// 位选引脚配置数组
const SegPinConfig digitPins[4] = {
	{GPIOA, GPIO_PIN_11}, // DIGIT_1
	{GPIOA, GPIO_PIN_12}, // DIGIT_2
	{GPIOC, GPIO_PIN_13}, // DIGIT_3
	{GPIOC, GPIO_PIN_14}  // DIGIT_4
};

// 数码管段码表
static uint8_t segCode[] = {
	0xC0,    // 0
	0xF9,    // 1
	0xA4,    // 2
	0xB0,    // 3
	0x99,    // 4
	0x92,    // 5
	0x82,    // 6
	0xF8,    // 7
	0x80,    // 8
	0x90     // 9
	// 0x00,	//全亮
};

// 当前显示的数字
// static uint16_t displayNum = 0;
// static uint8_t currentDigit = 0;
// static uint8_t segCode_index =0;	// 也即数码管显示数字

uint8_t currentDigit = 0;
uint8_t segCode_index = 0;
uint8_t position = 0;

static uint64_t digLastUpdateTime = 0;

static uint8_t pointState[4] = {0, 0, 0, 0};
static uint8_t displayNum[4] = {0, 0, 0, 0};

void digCur_position_change(void)
{
	// 关闭前一位小数点
	if (position < 4) {
		pointState[position] = 0;
	}
	// 更新位置
	position = (position + 1) % 4; 
	// 打开新位置的小数点
	pointState[position] = 1; 
    // return position;
}

// 增加当前选中的数码管值
void increase_value(void)
{
    // 将当前选中的数码管值加一
	if (pointState[position]) {
    	displayNum[position] = (displayNum[position] + 1) % 10;
	}
}

void seg_setDisplayNum(uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4)
{
    displayNum[3] = digit1 % 10; // 保证为0-9
    displayNum[2] = digit2 % 10;
    displayNum[1] = digit3 % 10;
    displayNum[0] = digit4 % 10;
}

// 数码管显示刷新
void seg_main(void)
{
	// uint32_t currentTime = HAL_GetTick();
	uint32_t currentTime = HAL_GetTick();

	// 检查是否已经过了10ms
	if ((currentTime - digLastUpdateTime) >= 10)
	{
		// 获取当前位需要显示的数字
		uint8_t code = segCode[displayNum[currentDigit]];

		// 如果当前位启用小数点,将小数点段位设置为1
		if (pointState[currentDigit]) {
			code &= 0x7F;
		}

		// 关闭所有位选
		for (int i = 0; i < 4; i++) {
			HAL_GPIO_WritePin(digitPins[i].port, digitPins[i].pin, GPIO_PIN_SET);
		}

		// 设置段选引脚
		for (int i = 0; i < 8; i++) {
			if (code & (1 << i)) {
				HAL_GPIO_WritePin(segPins[i].port, segPins[i].pin, GPIO_PIN_SET);
			} else {
				HAL_GPIO_WritePin(segPins[i].port, segPins[i].pin, GPIO_PIN_RESET);
			}
		}

		// 打开当前位选
		HAL_GPIO_WritePin(digitPins[currentDigit].port, digitPins[currentDigit].pin, GPIO_PIN_RESET);

		// 更新当前位
		currentDigit = (currentDigit + 1) % 4;
		digLastUpdateTime = currentTime;
	}
}

// void seg_setDisplayDecimal(uint32_t decimalValue)
// {
//     // 确保输入值在0到9999范围内
//     if (decimalValue > 9999) {
//         decimalValue = 9999;
//     }

//     // 从最低位开始分解十进制数
//     displayNum[0] = decimalValue % 10; // 个位
//     displayNum[1] = (decimalValue / 10) % 10; // 十位
//     displayNum[2] = (decimalValue / 100) % 10; // 百位
//     displayNum[3] = (decimalValue / 1000) % 10; // 千位
// }
// 获取当前数码管显示的十进制数
uint32_t seg_getDisplayDecimal(void)
{
    // 计算当前显示的四位数码管的十进制值
    return (displayNum[3] * 1000) + (displayNum[2] * 100) + (displayNum[1] * 10) + displayNum[0];
}



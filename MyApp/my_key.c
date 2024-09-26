#include "my_key.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

// GPIO配置:按键连接在 GPIOA 的 PIN5 和 PIN6
// #define key1_Pin GPIO_PIN_5
// #define key1_GPIO_Port GPIOA
// #define key2_Pin GPIO_PIN_6
// #define key2_GPIO_Port GPIOA


// 按键状态变量
// static uint8_t key1_state = KEY_NOT_PRESSED;
// static uint8_t key2_state = KEY_NOT_PRESSED;

uint8_t key1_state = KEY_NOT_PRESSED;
uint8_t key2_state = KEY_NOT_PRESSED;

static uint64_t key1LastReleaseTime = 0;
static uint64_t key2LastReleaseTime = 0;

// 按键1扫描函数
uint8_t key1_scan(void)
{
	uint8_t result = key1_state;
	key1_state = KEY_NOT_PRESSED;    // 清除按键状态,避免重复读取
	return result;
}

// 按键2扫描函数
uint8_t key2_scan(void)
{
	uint8_t result = key2_state;
	key2_state = KEY_NOT_PRESSED;
	return result;
}

// 按键状态刷新函数，需在主循环中调用,时间用HAL_GetTick
void key_main(void)
{
	// 检测按键1状态
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 0) {
		uint32_t currentTime = HAL_GetTick();
		if ((currentTime - key1LastReleaseTime) >= 10) {
			key1_state = KEY_PRESSED;
			// 执行对应按键操作
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
			// key1LastReleaseTime = currentTime;
		}
	} else {
		key1LastReleaseTime = HAL_GetTick();
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);
		key1_state = KEY_NOT_PRESSED;
	}

	// 检测按键2状态
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0) {
		uint32_t currentTime = HAL_GetTick();
		if ((currentTime - key2LastReleaseTime) >= 10) {
			key2_state = KEY_PRESSED;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
			// key2LastReleaseTime = currentTime;
		}
	}
	else
	{
		key2LastReleaseTime = HAL_GetTick();
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
		key2_state = KEY_NOT_PRESSED;
	}
}

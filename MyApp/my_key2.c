#include "my_key.h"
#include "stdint.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f101x6.h"

#define KEY_NOT_PRESSED	0
#define KEY_UP	1
#define KEY_DOWN	2
#define KEY_LEFT	3
#define KEY_RIGHT	4
#define KEY_ENTER	5

// 状态(5个),是否需要增加未按下状态

static KeyCfg_t *pKeyCfg2;
KeyInfo_t keyInfo;

// 检测是否按下,返回对应数字,按键io暂假定A6~10和小灯ioB6~10
uint8_t key_monitorPress()
{
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_SET);
		keyInfo.keyStatus = KEY_UP;
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == GPIO_PIN_SET){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);
		keyInfo.keyStatus = KEY_DOWN;
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,GPIO_PIN_SET);
		keyInfo.keyStatus = KEY_LEFT;
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,GPIO_PIN_SET);
		keyInfo.keyStatus = KEY_RIGHT;
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
		keyInfo.keyStatus = KEY_ENTER;
	}
	else{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
		return KEY_NOT_PRESSED;
	}
}


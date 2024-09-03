#include "my_app.h"
#include "my_key.h"
#include "seg_display.h"


/* @brief 实际51五个按键
#define KEY_UP_PIN      GPIO_PIN_0
#define KEY_DOWN_PIN    GPIO_PIN_1
#define KEY_LEFT_PIN    GPIO_PIN_2
#define KEY_RIGHT_PIN   GPIO_PIN_3
#define KEY_CONFIRM_PIN GPIO_PIN_4

void handleKeyPress(void) {
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_UP_PIN) == GPIO_PIN_SET) {
		// 上键按下逻辑
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_DOWN_PIN) == GPIO_PIN_SET) {
		// 下键按下逻辑
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_LEFT_PIN) == GPIO_PIN_SET) {
		// 左键按下逻辑
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_RIGHT_PIN) == GPIO_PIN_SET) {
		// 右键按下逻辑
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_CONFIRM_PIN) == GPIO_PIN_SET) {
		// 确认键按下逻辑
	}
}
*/


// 初始化函数MyApp_Init(),实际是gpio_init()

// 应用层主循环,在main.c调用
void MyApp_Run(void)
{
	key_main();
	// 读取按键状态
	if(key1_state == KEY_PRESSED){

		currentDigit = (currentDigit + 1) % 4;
		
	}
	else if(key2_state == KEY_PRESSED){
		segCode_index++;

		// 设置段选引脚
	for (int8_t i = 0; i < 8; i++) {
		if (segCode_index & (1 << i)) {
			HAL_GPIO_WritePin(segPins[i].port, segPins[i].pin, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(segPins[i].port, segPins[i].pin, GPIO_PIN_RESET);
		}
	HAL_GPIO_WritePin(digitPins[currentDigit].port, digitPins[currentDigit].pin, GPIO_PIN_RESET);

	}

	}

	// 判断按键状态，并进行相应的操作


	// 其他应用层逻辑处理
}




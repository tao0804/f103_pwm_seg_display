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

bool key1_handled = false;
bool key2_handled = false;
bool duty_cycle_handled = false;


// 应用层主循环,在main.c调用
void MyApp_Run(void)
{
	// 读取按键状态
	key_main();
	if (key1_state == KEY_PRESSED && !key1_handled) {
		digCur_position_change(); 
		key1_handled = true;
	}else if (key1_state == KEY_NOT_PRESSED) {
		key1_handled = false;
	}

	if (key2_state == KEY_PRESSED && !key2_handled) {
		increase_value();
		key2_handled = true;
	}else if (key2_state == KEY_NOT_PRESSED) {
		key2_handled = false;
	}
	seg_main();

    // 检查按键状态
    if (key1_state == KEY_NOT_PRESSED && key2_state == KEY_NOT_PRESSED) {
        // 获取当前显示的十进制值
        uint32_t currentDecimalValue = seg_getDisplayDecimal();

        // 如果数字小于等于100，设置为占空比大小
        if (currentDecimalValue <= 100) {
            user_duty_cycle_set(currentDecimalValue); // 假设你有一个设置占空比的函数
			duty_cycle_handled = true;
        }
    }else
		duty_cycle_handled = false;

}



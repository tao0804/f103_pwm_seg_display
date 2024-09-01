#include "mcu_hal.h"

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




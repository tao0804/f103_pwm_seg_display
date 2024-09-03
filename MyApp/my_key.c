#include "my_key.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

// GPIO配置:按键连接在 GPIOA 的 PIN5 和 PIN6
// #define key1_Pin GPIO_PIN_5
// #define key1_GPIO_Port GPIOA
// #define key2_Pin GPIO_PIN_6
// #define key2_GPIO_Port GPIOA

// 按键防抖时间
#define DEBOUNCE_TIME   5

// 按键状态变量
// static uint8_t key1_state = KEY_NOT_PRESSED;
// static uint8_t key2_state = KEY_NOT_PRESSED;

uint8_t key1_state = KEY_NOT_PRESSED;
uint8_t key2_state = KEY_NOT_PRESSED;

static uint8_t key1_cnt = 0;
static uint8_t key2_cnt = 0;

// 按键初始化,已在gpio_init里初始化过


// 按键1扫描函数
uint8_t key1_scan(void) {
    uint8_t result = key1_state;
    key1_state = KEY_NOT_PRESSED;  // 清除按键状态,避免重复读取
    return result;
}

// 按键2扫描函数
uint8_t key2_scan(void) {
    uint8_t result = key2_state;
    key2_state = KEY_NOT_PRESSED;
    return result;
}

// 按键状态刷新函数，需在主循环中调用
void key_main(void) {			
    // 检测按键1状态
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 0) {
        if (key1_cnt < DEBOUNCE_TIME) {
            key1_cnt++;
            if (key1_cnt == DEBOUNCE_TIME) {
                key1_state = KEY_PRESSED;
                // 执行对应按键操作
		        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
            }
        }
    } else {
        key1_cnt = 0;
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);
        key1_state = KEY_NOT_PRESSED;

    }

    // 检测按键2状态
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0) {
        if (key2_cnt < DEBOUNCE_TIME) {
            key2_cnt++;
            if (key2_cnt == DEBOUNCE_TIME) {
                key2_state = KEY_PRESSED;
                // 同
		        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
            }
        }
    } else {
        key2_cnt = 0;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
        key2_state = KEY_NOT_PRESSED;

    }
}

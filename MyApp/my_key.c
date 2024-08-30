#include "my_key.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

// GPIO配置:按键连接在 GPIOA 的 PIN5 和 PIN6
// #define key1_Pin GPIO_PIN_5
// #define key1_GPIO_Port GPIOA
// #define key2_Pin GPIO_PIN_6
// #define key2_GPIO_Port GPIOA

// #define KEY1_PIN        GPIO_Pin_0
// #define KEY2_PIN        GPIO_Pin_1
// #define KEY_PORT        GPIOA

// 按键防抖时间
#define DEBOUNCE_TIME   5

// 按键状态变量
static uint8_t key1_state = KEY_NOT_PRESSED;
static uint8_t key2_state = KEY_NOT_PRESSED;
static uint8_t key1_cnt = 0;
static uint8_t key2_cnt = 0;

// 按键初始化,已在gpio_init里初始化过

// void key_init(void) {
//     GPIO_InitTypeDef GPIO_InitStructure;

//     // 使能 GPIOA 时钟
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

//     // 配置按键引脚为浮空输入模式
//     GPIO_InitStructure.GPIO_Pin = KEY1_PIN | KEY2_PIN;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//     GPIO_Init(KEY_PORT, &GPIO_InitStructure);
// }

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
        key1_state = KEY_NOT_PRESSED;
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);

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
        key2_state = KEY_NOT_PRESSED;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);

    }
}

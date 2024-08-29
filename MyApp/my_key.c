#include "my_key.h"
#include "stdint.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f101x6.h"

#define KEY1_PRESSED	TRUE
#define KEY1_NOT_PRESSED	FALSE

static KeyCfg_t *pKeyCfg1;
KeyInfo_t keyInfo1;

void key_taskReset(void)
{
	memset(&keyInfo1, 0, sizeof(KeyInfo_t));
}

static void key1_scan(void)
{
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET){
		// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);	// 模块化key与led,分文件
		keyInfo1.keyStatus = KEY1_PRESSED;
	}
	else{
		// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);
		keyInfo1.keyStatus = KEY1_NOT_PRESSED;
	}
}

// getTick and keyCallback
void key_init(KeyCfg_t *pCfg)
{
	pKeyCfg1 = pCfg;
}

// 监测首次按下,放main里while(1)
void key_monitorPress(void)
{
	uint32_t lastTick;
	// 如果按键周期扫描已开启,无需检测首次按下
	if (keyInfo1.taskStatus)
		return;
	key1_scan();
	if (keyInfo1.keyStatus == KEY1_PRESSED) {
		pKeyCfg1->tickStart = HAL_GetTick();
		// 留定
		keyInfo1.pressTime = 0;      // 按下时间清0
		keyInfo1.releaseTime = 0;    // 释放时间清0
		keyInfo1.pressCnt = 0;       // 连按次数清0
		pKeyCfg1->keyEventCB(KEY_PRESS, keyInfo1.pressCnt);
	}
}

// 每10ms一次按键处理
void key_main(void)
{
	uint32_t tickNow;
	tickNow = HAL_GetTick();
	if(tickNow - pKeyCfg1->tickStart > KEY_TICK_PERIOD){
		// every 10ms

	}
}

void key_scanTimerCB(void)
{
	uint8_t lastKeyStatus = keyInfo1.keyStatus;
	uint16_t lastPressTime = keyInfo1.pressTime;
	uint16_t lastReleaseTime = keyInfo1.releaseTime;

	key1_scan();
	if (lastKeyStatus != keyInfo1.keyStatus) {
		if (keyInfo1.keyStatus == KEY1_PRESSED) {
			// 检测到按下
			// 在此次灯亮
			keyInfo1.pressTime = 0;
			keyInfo1.pressCnt++;
			pKeyCfg1->keyEventCB(KEY_PRESS, keyInfo1.pressCnt);
		} else {
			// 检测到释放
			keyInfo1.releaseTime = 0;
			pKeyCfg1->keyEventCB(KEY_RELEASE, keyInfo1.pressCnt);
		}
	}

	if (keyInfo1.keyStatus == KEY1_PRESSED) {
		keyInfo1.pressTime += pKeyCfg1->timerPeriod;
		if (keyInfo1.pressTime >= 100 && lastPressTime < 100) {
			pKeyCfg1->keyEventCB(KEY_PRESS_1SECS, keyInfo1.pressCnt);
		} else if (keyInfo1.pressTime >= 300 && lastPressTime < 300) {
			pKeyCfg1->keyEventCB(KEY_PRESS_3SECS, keyInfo1.pressCnt);
		}
	} else {
		keyInfo1.releaseTime += pKeyCfg1->timerPeriod;
		if (keyInfo1.releaseTime >= pKeyCfg1->pressIntervalTime && lastReleaseTime < pKeyCfg1->pressIntervalTime) {
			pKeyCfg1->keyEventCB(KEY_SCAN_END, keyInfo1.pressCnt);
		}
	}
}

////////////////////////////////////////////key_user/////////////////////////////////////////////
typedef enum KeyUserFlag {
	KEY_NO_FLAG = 0,
	KEY_POWER_ON_FLAG,
	KEY_3SECS_UNLOCK_FLAG,
	KEY_POWER_OFF_FLAG,
} KeyUserFlag_t;

typedef struct KeyUserInfo {
	uint8_t runMode;    // 0:关机 1:开机
	KeyUserFlag_t flag;
} KeyUserInfo_t;

KeyUserInfo_t keyUserInfo;
static KeyCfg_t keyCfg;

void key_eventCB(KeyEvents_t event, uint8_t pressCnt)
{
	// if (event == KEY_PRESSED && pressCnt == 0) {
	// 	// 首次按下清标志位
	// 	keyUserInfo.flag = KEY_NO_FLAG;
	// }

	// if (keyUserInfo.runMode) {
	// 	if (event == KEY_PRESS_3SECS && pressCnt == 0) {
	// 		// 长按3s触发解锁按键
	// 		keyUserInfo.flag = KEY_3SECS_UNLOCK_FLAG;
	// 	} else if (event == KEY_PRESS && pressCnt == 1) {
	// 		if (keyUserInfo.flag == KEY_3SECS_UNLOCK_FLAG) {
	// 			// 解锁后再按下就让POW_EN拉低，在用户释放按键时完全断电
	// 			keyUserInfo.flag = KEY_POWER_OFF_FLAG;
	// 			mcu_gpio_en_pow(FALSE);
	// 		}
	// 	} else if (event == KEY_RELEASE) {
	// 		if (keyUserInfo.flag == KEY_NO_FLAG) {
	// 			// 未解锁按键，在释放按键时重置按键
	// 			key_taskReset();
	// 		}
	// 	}
	// } else {
	// 	if (event == KEY_PRESS_1SECS) {
	// 		// 长按1s开机
	// 		mcu_gpio_en_pow(TRUE);
	// 		keyUserInfo.flag = KEY_POWER_ON_FLAG;
	// 	} else if (event == KEY_RELEASE) {
	// 		if (keyUserInfo.flag == KEY_NO_FLAG) {
	// 			// 未长按1s在释放按键时下电
	// 			mcu_gpio_en_pow(FALSE);
	// 		}
	// 	} else if (event == KEY_SCAN_END) {
	// 		if (keyUserInfo.flag == KEY_POWER_ON_FLAG) {
	// 			// 等按键扫描任务结束再置runMode，防止开机后立马又被按下
	// 			keyUserInfo.runMode = TRUE;
	// 		}
	// 	}
	// }
	
	if (event == KEY_PRESS_1SECS) {
		// 长按3s置关机flag
		keyUserInfo.flag = KEY_POWER_ON_FLAG;
	} else if (event == KEY_PRESS_3SECS) {
		// 长按3s置关机flag
		keyUserInfo.flag = KEY_POWER_OFF_FLAG;
	} else if (event == KEY_RELEASE && keyUserInfo.flag == KEY_POWER_OFF_FLAG) {
		// 松开时关机，防止一直按着，一关机就被唤醒
		sys_power_flag = 1;
		app_var.ext_wakeup_enable = 1;
		key_taskReset();
	} else if (event == KEY_RELEASE && keyUserInfo.flag == KEY_PRESS_1SECS) {
		// 长按1s开机
		sys_power_flag = 0;
		app_var.ext_wakeup_enable = 0;
		key_taskReset();
	}
}

void key_resetInit(void)
{
	keyCfg.keyEventCB = key_eventCB;
	keyCfg.pressIntervalTime = 200;
	keyCfg.timerPeriod = 10;
	key_init(&keyCfg);
	memset(&keyInfo1, 0, sizeof(KeyInfo_t));

	memset(&keyUserInfo, 0, sizeof(KeyUserInfo_t));
}






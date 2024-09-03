#include "my_app.h"
#include "my_key.h"
#include "seg_display.h"


/* @brief ʵ��51�������
#define KEY_UP_PIN      GPIO_PIN_0
#define KEY_DOWN_PIN    GPIO_PIN_1
#define KEY_LEFT_PIN    GPIO_PIN_2
#define KEY_RIGHT_PIN   GPIO_PIN_3
#define KEY_CONFIRM_PIN GPIO_PIN_4

void handleKeyPress(void) {
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_UP_PIN) == GPIO_PIN_SET) {
		// �ϼ������߼�
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_DOWN_PIN) == GPIO_PIN_SET) {
		// �¼������߼�
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_LEFT_PIN) == GPIO_PIN_SET) {
		// ��������߼�
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_RIGHT_PIN) == GPIO_PIN_SET) {
		// �Ҽ������߼�
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_CONFIRM_PIN) == GPIO_PIN_SET) {
		// ȷ�ϼ������߼�
	}
}
*/


// ��ʼ������MyApp_Init(),ʵ����gpio_init()

// Ӧ�ò���ѭ��,��main.c����
void MyApp_Run(void)
{
	key_main();
	// ��ȡ����״̬
	if(key1_state == KEY_PRESSED){

		currentDigit = (currentDigit + 1) % 4;
		
	}
	else if(key2_state == KEY_PRESSED){
		segCode_index++;

		// ���ö�ѡ����
	for (int8_t i = 0; i < 8; i++) {
		if (segCode_index & (1 << i)) {
			HAL_GPIO_WritePin(segPins[i].port, segPins[i].pin, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(segPins[i].port, segPins[i].pin, GPIO_PIN_RESET);
		}
	HAL_GPIO_WritePin(digitPins[currentDigit].port, digitPins[currentDigit].pin, GPIO_PIN_RESET);

	}

	}

	// �жϰ���״̬����������Ӧ�Ĳ���


	// ����Ӧ�ò��߼�����
}




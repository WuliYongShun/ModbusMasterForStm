/*
 * KEYDriver.h
 *
 *  Created on: 2019Äê9ÔÂ29ÈÕ
 *      Author: S
 */

#ifndef KEY_H_
#define KEY_H_

#include "stm32f1xx_hal.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif


#define KEY1_Pin GPIO_PIN_2
#define KEY1_GPIO_Port GPIOE
#define KEY2_Pin GPIO_PIN_3
#define KEY2_GPIO_Port GPIOE
#define KEY3_Pin GPIO_PIN_4
#define KEY3_GPIO_Port GPIOE

#define KEY4_Pin GPIO_PIN_0
#define KEY4_GPIO_Port GPIOA


typedef enum
{
	NoKeyDown = 0,
	KeySureDown,
	OnceKeyDown,
	ContiousKeyDown
}StateStatus;

enum
{
	KeyWake,
	Key1,
	Key2,
	Key3,
	KeyNone
};

void KeyInit(void);
StateStatus ReadKeyStatus(void);


#ifdef __cplusplus
}
#endif
#endif /* KEYDRIVER_H_ */

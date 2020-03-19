/*
 * KYEDriver.c
 *
 *  Created on: 2019��9��29��
 *      Author: S
 */

#include "KEY.h"

#define ReadWake()	HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin)
#define ReadKey1()	HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)
#define ReadKey2()  HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY1_Pin)
#define ReadKey3()	HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)




void KeyInit(void)
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};

	 /* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pins : PEPin PEPin PEPin */
	GPIO_InitStruct.Pin = KEY1_Pin|KEY2_Pin|KEY3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = KEY4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(KEY4_GPIO_Port, &GPIO_InitStruct);
}

uint8_t GetKey(void)
{
	if(ReadWake() == 1)
	{
		return KeyWake;
	}

	if(ReadKey1() == 0)
	{
		return Key1;
	}

	if(ReadKey2() == 0)
	{
		return Key2;
	}

	if(ReadKey3() == 0)
	{
		return Key3;
	}

	return KeyNone;
}


StateStatus ReadKeyStatus(void)
{
	static StateStatus state = NoKeyDown;
	static int TimeCount = 0;
	int KeyPress = ReadWake();
	StateStatus KeyReturn = NoKeyDown;

	switch(state)
	{
	case NoKeyDown:
		if(!KeyPress)
		{
			state = KeySureDown;
		}
		break;

	case KeySureDown:
		if(!KeyPress)
		{
			state = OnceKeyDown;
			TimeCount = 0;

		}
		else
		{
			state = NoKeyDown;
		}
		break;

	case OnceKeyDown:
		if(KeyPress)
		{
			state = NoKeyDown;
			KeyReturn = OnceKeyDown;
		}
		else if(++TimeCount > 100)
		{
			state = ContiousKeyDown;
			TimeCount = 0;
			KeyReturn = ContiousKeyDown;
		}
		break;

	case ContiousKeyDown:
		if(KeyPress)
		{
			state = NoKeyDown;
			KeyReturn = NoKeyDown;
		}
		else if(++TimeCount > 50)
		{
			KeyReturn = ContiousKeyDown;
			TimeCount = 0;
		}
		else
		{
			KeyReturn = NoKeyDown;
		}
		break;
		
	default:
		break;
	}
	return KeyReturn;
}

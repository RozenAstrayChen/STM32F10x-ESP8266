#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"
#define ON 0
#define OFF 1
#define LED1(a) if (a) \
	GPIO_SetBits(GPIOB , GPIO_Pin_9); \
	else	\
	GPIO_ResetBits(GPIOB , GPIO_Pin_9) //LED1 ON

void LED_Configuration(void);




#endif

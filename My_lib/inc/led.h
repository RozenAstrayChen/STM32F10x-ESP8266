#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define ON 0
#define OFF 1

#define LED1(a) if (a)	\
	GPIO_SetBits(GPIOB,GPIO_Pin_9);	\
	else	\
	GPIO_ResetBits(GPIOB,GPIO_Pin_9)
	
/*#define LED2(a) if (a)	\
	GPIO_SetBits(GPIOC,Gpio_Pin_4);	\
	else	\
	GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define LED3(a)	if (a)	\
	GPIO_SetBits(GPIOC,GPIO_Pin_5);\
	else		\
	GPIO_ResetBits(GPIOC,GPIO_Pin_5)*/

void LED_GPIO_Config(void);

					
#endif

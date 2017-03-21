#ifndef __INPUT_H
#define __INPUT_H

#include "stm32f10x.h"
#define KEY_ON	0
#define KEY_OFF	1

void EXTI_PB0Config(void);
void BUTTON_WHILE(void);
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
#endif

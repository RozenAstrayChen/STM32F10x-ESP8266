/******************** (C) COPYRIGHT 2012 WildFire Team **************************

 * Ó²¼þÁ¬½Ó£º-----------------
 *          | PC3 - LED1      |
 *          | PC4 - LED2      |
 *          | PC5 - LED3      |
 *           ----------------- 

**********************************************************************************/

#include "led.h"


void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_9);	 // turn off all led
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

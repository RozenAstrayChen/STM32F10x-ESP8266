/****************************************Copyright (c)****************************************************
**                                        
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			
** Last modified Date:          
** Last Version:		   
** Descriptions:							
**--------------------------------------------------------------------------------------------------------
** Created by:			FiYu
** Created date:		2015-12-15
** Version:			    1.0
** Descriptions:		ESP8266 WiFi无线通信实验				
**--------------------------------------------------------------------------------------------------------
** Modified by:			FiYu
** Modified date:		
** Version:				
** Descriptions:		
** Rechecked by:			
**********************************************************************************************************/
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_SysTick.h"
#include "bsp_esp8266.h"
#include "delay.h"
#include "led.h"
#include "control.h"
#include "input.h"
#include "string.h"



/**************************************************************************************
 * 描  述 : MAIN函数
 * 入  参 : 无
 * 返回值 : 无
 **************************************************************************************/
int main ( void )
{
	//_flag.Connect = false;
	LED_Configuration ();                                       //led configure
	//EXTI_PB0Config();																						//button config
	BUTTON_WHILE();
	GPIO_Config ();  																						//GPIO_UART Config
	USARTx_Config();																						//UART Config
	//DMA2_Config();																							//USART2->DMA1
	SendData_uart2("start testing...");
	SysTick_Init ();                                         //setting SysTick  1ms break
	ESP8266_Init ();                                         //INIT ESP8266
  ESP8266_StaTcpClient_UnvarnishTest ();
	
	/*waiting button push...*/
  while (1)
	{
			if( Key_Scan(GPIOB,GPIO_Pin_0) == KEY_ON  ){
			
		   		//GPIO_WriteBit(GPIOB, GPIO_Pin_9, 
		             //(BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_9))));
				SEND_TCP();
			}   
	}
	
	
}


/*********************************************END OF FILE**********************/

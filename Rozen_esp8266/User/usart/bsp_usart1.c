#include "bsp_usart1.h"
#include "bsp_esp8266.h"
#include <stdarg.h>

uint8_t SendBuff[SENDBUFF_SIZE];

/**
 * @brief NVIC initialize
 */

static void NVIC_Config(void){
   NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置P[A|B|C|D|E]0为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*SEND DATA TO SERIAL PORT*/
void SendData_uart2(char* str){
	  while(*str)
    {
        USART_SendData(USART2, *str++);
        /* loop*/
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    }
}
 /**
  * @brief  USARTx GPIO setting ,use usart1(9,10),usart2(2,3)
  * @param  none
  * @retval none
  */
void GPIO_Config(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
		RCC_APB2PeriphClockCmd(macUSART_CLK, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = macUSART_TX_PIN;//9
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(macUSART_TX_PORT, &GPIO_InitStructure);
	

		GPIO_InitStructure.GPIO_Pin = macUSART_RX_PIN;//10
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		/**************************serial usart********************************/	
	
		RCC_APB1PeriphClockCmd(serialUSART_CLK , ENABLE);
	

		GPIO_InitStructure.GPIO_Pin = serialUSART_TX_PIN  ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(serialUSART_TX_PORT, &GPIO_InitStructure);
		

		GPIO_InitStructure.GPIO_Pin = serialUSART_RX_PIN ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(serialUSART_RX_PORT, &GPIO_InitStructure);
		

}
void USARTx_Config(){
	
				USART_InitTypeDef USART_InitStructure;
				
				USART_InitStructure.USART_BaudRate = 115200;
				USART_InitStructure.USART_WordLength = USART_WordLength_8b;
				USART_InitStructure.USART_StopBits = USART_StopBits_1;
				USART_InitStructure.USART_Parity = USART_Parity_No;
				USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
				USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
				USART_Init(macUSARTx, &USART_InitStructure);
				//interuppurt break?
				USART_ITConfig(macUSARTx, USART_IT_IDLE , ENABLE);
			  /* 第5步：使能 USART， 配置完毕 */
				USART_Cmd(macUSARTx, ENABLE);  
			  /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
				如下语句解决第1个字节无法正确发送出去的问题 */
				USART_ClearFlag(macUSARTx, USART_FLAG_TC); /* ，Transmission Complete flag */
        USART_InitStructure.USART_BaudRate = 115200;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        USART_Init(USART2, &USART_InitStructure);
        USART_ITConfig(USART2, USART_IT_IDLE , ENABLE);//interuppurt break? 
        USART_Cmd(USART2, ENABLE);
        /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
        如下语句解决第1个字节无法正确发送出去的问题 */
        USART_ClearFlag(USART2, USART_FLAG_TC); /*Transmission Complete flag */
}
/*initialize UART1->DMA1 */
void DMA2_Config(){
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//UART2_tx->DMA1_channel7
	NVIC_Config();
	
	DMA_DeInit(DMA1_Channel7);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_DR_BASE; //usart2_base +0x04
	
	DMA_InitStructure.DMA_MemoryBaseAddr =  (uint32_t)SendBuff;
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	
  DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;

	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;

  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular ;	 
	
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	
	
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		   
  DMA_Init(DMA1_Channel7, &DMA_InitStructure); 	   

	DMA_Cmd (DMA1_Channel7,ENABLE);					//ENABLE DMA
	
	DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE); //after config DMA interrupt
	
	
}





int fputc(int ch, FILE *f)
{
		
		USART_SendData(macUSARTx, (uint8_t) ch);
		
		
		while (USART_GetFlagStatus(macUSARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

int fgetc(FILE *f)
{
		
		while (USART_GetFlagStatus(macUSARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(macUSARTx);
}



/*********************************************END OF FILE**********************/

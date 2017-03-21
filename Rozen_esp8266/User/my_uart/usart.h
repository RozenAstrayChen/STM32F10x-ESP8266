#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h"
#include <stdio.h>


#define SENDBUFF_SIZE 32
#define USART1_DR_Base 0x40013804//uart1_address
//extern void GPIO_Configuration();

void UART2_Configuration(void);

void DMA_Configuration(void);

static void NVIC_Config(void);

int fputc(int ch, FILE *f);

void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);

#endif /*__USART_H*/

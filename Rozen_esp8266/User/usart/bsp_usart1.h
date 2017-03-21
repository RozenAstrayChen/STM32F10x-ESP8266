#ifndef __USART1_H
#define	__USART1_H


#include "stm32f10x.h"
#include <stdio.h>

#define SENDBUFF_SIZE 32

/**************************esp8266 usart********************************/
#define             macUSART_BAUD_RATE                       115200

#define             macUSARTx                                USART1
#define             macUSART_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define             macUSART_CLK                             RCC_APB2Periph_USART1
#define             macUSART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             macUSART_GPIO_CLK                        RCC_APB2Periph_GPIOA     
#define             macUSART_TX_PORT                         GPIOA   
#define             macUSART_TX_PIN                          GPIO_Pin_9
#define             macUSART_RX_PORT                         GPIOA 
#define             macUSART_RX_PIN                          GPIO_Pin_10
#define             macUSART_IRQ                             USART1_IRQn
#define             macUSART_INT_FUN                         USART1_IRQHandler
/**************************serial usart********************************/
#define							serialUSARTx															USART2
#define             serialUSART_CLK                           RCC_APB1Periph_USART2
#define             serialUSART_GPIO_CLK                      RCC_APB2Periph_GPIOA
#define             serialUSART_TX_PORT                       GPIOA   
#define             serialUSART_TX_PIN                        GPIO_Pin_2
#define             serialUSART_RX_PORT                       GPIOA 
#define             serialUSART_RX_PIN                        GPIO_Pin_3
#define             serialUSART_IRQ                           USART2_IRQn
#define             serialUSART_INT_FUN                       USART2_IRQHandler
#define USART2_DR_BASE 0x40004404
void                GPIO_Config                           ( void );
void                USARTx_Config                      		( void );
void 								SendData_uart2												(char* str);
void 								DMA2_Config														( void );
#endif /* __USART1_H */

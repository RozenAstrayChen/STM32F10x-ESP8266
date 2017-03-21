#include "usart.h"
#include <stdarg.h>

/** 
  * @brief initialize uart configre
  */
void UART1_Configuration(){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//enable gpio clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_DeInit(GPIOA);//?
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //FLOAT INPUT
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/*USART MODE CONFIG*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No; //ÆæÅ¼Ð£òž
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
	
	
} 
/**
 * @brief reset printf in C Lib from uart1
 */
int fputc(int ch, FILE *f){
	USART_SendData(USART1,(unsigned char)ch);
	/*check data has send over*/
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	
	return(ch);
}
/**
 * @brief integer data to string
 * @input -radix = 10 Decimal,else is 0
					-value Turn value
					-buf	after function data
 */
static char* itoa(int value,char* string ,int radix){
	int i,d;
	int flag =0;
	char *ptr = string;
	/* This implementation only works for decimal numbers. */
	if(radix !=10){
		*ptr =0;
		return string;
	}
	if(!value){
		/*0x30 = 48,48 = ascii 0*/
		*ptr++ = 0x30;
		*ptr = 0;
		return string;
	}
	/* if this is a negative value insert the minus sign. */
	if(value < 0){
		*ptr++ = '-';
		value  = value*-1;
	}
	for(i = 10000; i>0; i/= 10){
			d = value / i;
		/*d has value*/
		if(d || flag){
			*ptr++ = (char)(d +0x30);
			value -= (d*i);
			flag = 1;
		}
	}
	/* Null terminate the string. */
	*ptr = 0;
	
	return string;
}/*atoi */

/**
 * @brief like printf in C lib
 */
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...){
	const char *s;
	int d;
	char buf[16];
	va_list ap;
	va_start(ap,Data);
	while( *Data != 0){
		if(*Data == 0x5c){ // '\'
			switch(*++Data){
				case 'r':// return
					USART_SendData(USARTx,0x0d);//r = 13
					Data++;break;
				
				case 'n': //enter
					USART_SendData(USARTx,0X0a);//n = 10
					Data++;break;
				default:
					Data++;break;
			}
		}else if(*Data == '%'){
			switch(*++Data){
				case 's': //string
					s = va_arg(ap,const char*);
					for(;*s;s++){
						USART_SendData(USARTx,*s);
						while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);
					}
					Data++;break;
				case 'd': //dec
					d = va_arg(ap,int);
				itoa(d,buf,10);
				for(s = buf;*s;s++){
					USART_SendData(USARTx,*s);
						while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);
				}
				Data++;break;
				
				default:
					Data++;break;
			}
		}
		else USART_SendData(USARTx, *Data++);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}
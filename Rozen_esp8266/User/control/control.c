#include "control.h"
#include "bsp_esp8266.h"
#include "bsp_usart1.h"
#include "bsp_SysTick.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "usart.h"
#include "delay.h"
#include "led.h"
struct STRUCT_flag _flag;

/**
  * @brief  ESP8266 Conrtol
  * @param  
  * @retval 
  */
void ESP8266_StaTcpClient_UnvarnishTest ( void )
{

	macESP8266_CH_ENABLE();
	
	ESP8266_AT_Test ();    //测试AT启动,发送联机命令
	
	ESP8266_Net_Mode_Choose ( STA );   //station模式bool  ( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id)
	
	while(!ESP8266_Enable_MultipleId(DISABLE));
	 
	while ( ! ESP8266_JoinAP ( macUser_ESP8266_CwjServer_M , macUser_ESP8266_CwjServer_N) );//connect wifi 
	SendData_uart2(strEsp8266_Fram_Record .Data_RX_BUF);
	
	LED1(ON);
 
	
	
}
/**
  * @brief  useing esp8266 do HTTP/GET
  * @param  
  * @retval 
  */
void SEND_TCP(void){
	
	/*response IP*/
	while ( ! ESP8266_Link_Server ( macUser_ESP8266_TcpServer_Enum, macUser_ESP8266_TcpServer_IP,macUser_ESP8266_TcpServer_Port,Single_ID_0 ) );	
	SendData_uart2(strEsp8266_Fram_Record .Data_RX_BUF);		//return data to uart2
	/*tell esp8266 you need send buff size*/
	while(!ESP8266_HTTP_CIPSEND());
	SendData_uart2(strEsp8266_Fram_Record .Data_RX_BUF);		//return data to uart2
	/*do HTTP/GET*/
	while(!ESP8266_SendString(ENABLE,GET_url,0,5));
	SendData_uart2(strEsp8266_Fram_Record .Data_RX_BUF);		//return data to uart2
}

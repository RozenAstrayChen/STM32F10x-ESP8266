#ifndef  ___CONTROL_H
#define	 ___CONTROL_H



#include "stm32f10x.h"
#include "bsp_esp8266.h"



/********************************** argc**********************************/
#define      macUser_ESP8266_BulitApSsid          "FIYU"         //Ҫ�������ȵ������
#define      macUser_ESP8266_BulitApEcn            OPEN               //Ҫ�������ȵ�ļ��ܷ�ʽ
#define      macUser_ESP8266_BulitApPwd           "fiyu"         //Ҫ�������ȵ����Կ

#define      macUser_ESP8266_CwjServer_M          "CHT9074"  //�����s��������
#define      macUser_ESP8266_CwjServer_N          "43854385"  //�����s���ȵ������




#define      macUser_ESP8266_TcpServer_Enum        enumTCP    //������������IP��ַ
#define      macUser_ESP8266_TcpServer_IP         "54.203.10.255"    //������������IP��ַ
#define      macUser_ESP8266_TcpServer_Port       "80"             //SSL

#define			 GET_url 															"GET /evb/get.php?state=true\r\n"
#define 		 GET_Length 													31



#define      macUser_ESP8266_TcpServer_OverTime           "1800"             //��������ʱʱ�䣨��λ���룩



/********************************** function ***************************************/
void                     ESP8266_StaTcpClient_UnvarnishTest  ( void );
void 											SEND_TCP														(void);
/********************************** flag ***************************************/
extern struct  STRUCT_flag                                 
{
	bool Connect;
	
} _flag;


#endif


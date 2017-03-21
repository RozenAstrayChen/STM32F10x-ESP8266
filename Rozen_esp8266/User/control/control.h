#ifndef  ___CONTROL_H
#define	 ___CONTROL_H



#include "stm32f10x.h"
#include "bsp_esp8266.h"



/********************************** argc**********************************/
#define      macUser_ESP8266_BulitApSsid          "FIYU"         //要建立的热点的名称
#define      macUser_ESP8266_BulitApEcn            OPEN               //要建立的热点的加密方式
#define      macUser_ESP8266_BulitApPwd           "fiyu"         //要建立的热点的密钥

#define      macUser_ESP8266_CwjServer_M          "CHT9074"  //建立硈挡的名称
#define      macUser_ESP8266_CwjServer_N          "43854385"  //建立硈挡热点的密码




#define      macUser_ESP8266_TcpServer_Enum        enumTCP    //服务器开启的IP地址
#define      macUser_ESP8266_TcpServer_IP         "54.203.10.255"    //服务器开启的IP地址
#define      macUser_ESP8266_TcpServer_Port       "80"             //SSL

#define			 GET_url 															"GET /evb/get.php?state=true\r\n"
#define 		 GET_Length 													31



#define      macUser_ESP8266_TcpServer_OverTime           "1800"             //服务器超时时间（单位：秒）



/********************************** function ***************************************/
void                     ESP8266_StaTcpClient_UnvarnishTest  ( void );
void 											SEND_TCP														(void);
/********************************** flag ***************************************/
extern struct  STRUCT_flag                                 
{
	bool Connect;
	
} _flag;


#endif


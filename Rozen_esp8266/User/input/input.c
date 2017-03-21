#include "input.h"
#include "delay.h"
 /*name : NVIC Configuration
 *description: setting inturput NVIC
 *input:
 *output:
 *test:
 */
 
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置P[A|B|C|D|E]0为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/*setting PB_0 interrupted*/
void EXTI_PB0Config(void){
	GPIO_InitTypeDef GPIO_Initstructure;
	EXTI_InitTypeDef EXTI_Initstructure;
	
	/*configure the extiline clock and AFIO clock*/
	/*all gpio is APB2 Handle*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	
	//CONFIGURE NVIC
	NVIC_Configuration();
	//GPIO_configure
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPD; // up input 1
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	//EXIT config
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	EXTI_Initstructure.EXTI_Line = EXTI_Line0;
	EXTI_Initstructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Initstructure.EXTI_Trigger = EXTI_Trigger_Falling; //interrupt when falling
	EXTI_Initstructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_Initstructure);
	
}
void BUTTON_WHILE(void){
	GPIO_InitTypeDef GPIO_Initstructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU; // up input 1
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
}
/*alternative plan...ugly*/
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
		/*检测是否有按键按下 */
   	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	  {	   
	 	 /*延时消抖*/
	  	delay_us(10000);		
	   		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
					{	 
						/*等待按键释放 */
						while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
			 			return 	KEY_ON;	 
					}
			else
					return KEY_OFF;
		}
	else
		return KEY_OFF;
}

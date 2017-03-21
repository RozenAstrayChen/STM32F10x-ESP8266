#include "exit.h"
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
  
  /* ≈‰÷√P[A|B|C|D|E]0Œ™÷–∂œ‘¥ */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/*setting PB_0 interrupted*/
void EXTI_PB0_Config(void){
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
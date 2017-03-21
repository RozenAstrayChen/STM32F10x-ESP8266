#include "delay.h"

#ifndef USE_TIMEMODE
//#else 

void delay_us(u16 us){
	u16 i;
	do{
		i=6;
		while(i--)__nop();
	}while(--us);
}

void delay_ms(u16 ms)
{
  do
  {
    delay_us(250);
    delay_us(250);
    delay_us(250);
    delay_us(250);
  } while (--ms);
}

#endif

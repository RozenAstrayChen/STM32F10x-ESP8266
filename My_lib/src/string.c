#include "string.h"
/**
  * @brief  This function use in uart ,.
  * @param  None
  * @retval None
  */
size_t R_strlen( char *string )
{
    int length = 0;
    // 依次访问字符串的内容，计算字符数，直至遇到NUL终止符
    while( *string++ != '\0' ){
        length += 1;
		}
    return length;
}

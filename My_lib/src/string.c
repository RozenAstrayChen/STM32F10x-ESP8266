#include "string.h"
/**
  * @brief  This function use in uart ,.
  * @param  None
  * @retval None
  */
size_t R_strlen( char *string )
{
    int length = 0;
    // ���η����ַ��������ݣ������ַ�����ֱ������NUL��ֹ��
    while( *string++ != '\0' ){
        length += 1;
		}
    return length;
}

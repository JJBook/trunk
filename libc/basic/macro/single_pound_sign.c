/***********************************************************************
*   Copyright (C) 2016 pilot-lab.inc All rights reserved.
*   
*   @file:       macro.c
*   @brief:      
*   @author:     Pilot labs
*   @maintainer: frank.fu@pilot-lab.com.cn
*   @version:    1.0
*   @date:       2016-09-13
*   
***********************************************************************/
//#include "macro.h"
#include <stdio.h>
#include <stdlib.h>

//C���������ʹ�ú�,C/C++�еĺ꣨Macro�����ڱ�����Ԥ����ķ��룬���ڱ����ڸ�����������ڸ����

//��C���Եĺ��У�#�Ĺ����ǽ������ĺ���������ַ�����������Stringification������˵�����ڱ��滻�ĺ�������Ҹ�����һ��˫���š�
#define PSQR(x) printf("the square of " #x " is %d.\n",(x)*(x))

#define WARN_IF(EXP)    do{ if (EXP)    fprintf(stderr, "Warning: " #EXP "\n"); }   while(0)



int main(int argc, char** argv)
{
	int y =4;
	PSQR(y);
	PSQR(2+4);

	int divider = 0;
	WARN_IF(divider == 0);


	return 0;
}

/***********************************************************************
*   Copyright (C) 2016 pilot-lab.inc All rights reserved.
*   
*   @file:       double_pound_sign.c
*   @brief:      
*   @author:     Pilot labs
*   @maintainer: frank.fu@pilot-lab.com.cn
*   @version:    1.0
*   @date:       2016-09-13
*   
***********************************************************************/
//#include "double_pound_sign.h"
#include <stdio.h>
#include <stdlib.h>

// ##����Ϊ���ӷ���concatenator��������������Token����Ϊһ��Token��ע���������ӵĶ�����Token���У�����һ���Ǻ�ı�����
// ������Ҫ��һ���˵����������ͺ���ָ����ɵĽṹ������飬����ϣ���ں������Ͳ˵���������֮����ֱ�۵ġ������ϵĹ�ϵ��

#define COMMAND(NAME) { #NAME, NAME##_command }
//#define QUIT "quit"

struct command
{
	char* name;
	void (*function) (void);
};

void quit_command()
{
	printf("quit_command\n");
}

void help_command()
{
	printf("help_command\n");
}

int main(int argc, char** argv)
{
	struct command asCommands[] = {
		COMMAND(quit),
		COMMAND(help),
	};

	printf("1 cmd is %s\n", asCommands[0].name);
	asCommands[0].function();
	printf("2 cmd is %s\n", asCommands[1].name);
	asCommands[1].function();

	return 0;
}


/*
��ʱ����д������ܻᶨ�����DEBUGģʽ�µĵ��Դ�ӡ��Ϣ�������ԭ�еĴ�ӡ����,��ʱ�ͻ���ֱ�д�ɱ����������д�����⡣

������gcc��,�Կɱ����������֧��Ҫǿ�Ķ�,һ�����ǿ�����ôд:
#define MACRO_1(fmt, args...) printf(fmt, args)
#define MACRO_2(fmt, ...) printf(fmt, __VA_ARGS__)

������д��������,����һ����ʹ���˹ؼ���__VA_ARGS__,��������г��ֵ�...,��ǰ���д�����Ǹ��ɱ����Ĳ���������һ������,����˵�ڵ�һ��д����,args���Ǵ���ɱ���������
��������:
#include <stdio.h>
#define MACRO_1(fmt, args...) printf(fmt, args)
#define MACRO_2(fmt, ...)     printf(fmt, __VA_ARGS__)
int main()
{
	MACRO_1("MACRO_1:%s\n", "Hello");
	MACRO_2("MACRO_2:%s\n", "Hello");
	return 0;
}
���ǿ�����gcc -E�Ĳ������õ�����ĺ�չ��Դ����,��Ҫ��������:

int main()
{
	printf("MACRO_1:%s\n", "Hello");
	printf("MACRO_2:%s\n", "Hello");
	return 0;
}

��ҿ��Կ�������ĶԱ�.

����һ���������,�������ֻ����һ����������ô��?Ҳ���ǰ�Դ�����д����:
#include <stdio.h>
#define MACRO_1(fmt, args...) printf(fmt, args)
#define MACRO_2(fmt, ...)     printf(fmt, __VA_ARGS__)
int main()
{
	MACRO_1("MACRO_1\n");
	MACRO_2("MACRO_2\n");
	return 0;
}
�����᲻����������,���ǿ�һ�º�չ����Ĵ���:
int main()
{
	printf("MACRO_1\n", );
	printf("MACRO_2\n", );
	return 0;
}
����������һ��",",����Ľ����������args��__VA_ARGS__ǰ���һ��##,##��ʾȥ����ǰ���","����Ȼ����##�ĵڶ������ܣ�����Ϊʲô��ȥ�����������д��о������������Ǵ��ݶ���һ��������ʱ����Ҳ�ܹ����������һ�δ���һ�������ڿ�һ�¼���##֮��Ĵ��뼰��Ӧ��չ����Ĵ��룺
#include <stdio.h>
#define MACRO_1(fmt, args...) printf(fmt, ##args)
#define MACRO_2(fmt, ...)     printf(fmt, ##__VA_ARGS__)
int main()
{
	MACRO_1("MACRO_1\n");
	MACRO_2("MACRO_2\n");
	return 0;
}
չ����֮��
int main()
{
	printf("MACRO_1\n");
	printf("MACRO_2\n");
	return 0;
}

*/

#include"CMyNet.h"
#include<stdio.h>
#include<WinSock2.h>					// 선언부
#include<ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")		// dll import 정보

int main()
{
	try
	{
		CMyNet net;
		net.CreateSocket(9000);
	}
	catch (const char* msg)
	{
		printf("에러 : %s\n", msg);
	}
	
	return 0;
}

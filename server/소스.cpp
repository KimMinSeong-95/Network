#include"CMyNet.h"
#include<stdio.h>
#include<WinSock2.h>					// �����
#include<ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")		// dll import ����

int main()
{
	try
	{
		CMyNet net;
		net.CreateSocket(9000);
	}
	catch (const char* msg)
	{
		printf("���� : %s\n", msg);
	}
	
	return 0;
}

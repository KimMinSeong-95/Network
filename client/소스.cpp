#include<stdio.h>
#include "CMyClient.h"
#include<WinSock2.h>					// 선언부
#include<ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")		// dll import 정보

int main()
{
	CMyClient Client;
	//Client.CreateSocket("192.168.0.93", 9000);
	Client.CreateSocket("192.168.0.88", 9000);

	while (true)
	{
		// 사용자에게 문자열을 입력
		char buf[256] = "\0";
		printf(">> ");
		gets_s(buf, sizeof(buf));
		if (strlen(buf) == 0)
			break;
		Client.SendData(buf, strlen(buf));
	}
	return 0;
}
#include<stdio.h>
#include "CMyClient.h"
#include<WinSock2.h>					// �����
#include<ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")		// dll import ����

int main()
{
	CMyClient Client;
	//Client.CreateSocket("192.168.0.93", 9000);
	Client.CreateSocket("192.168.0.88", 9000);

	while (true)
	{
		// ����ڿ��� ���ڿ��� �Է�
		char buf[256] = "\0";
		printf(">> ");
		gets_s(buf, sizeof(buf));
		if (strlen(buf) == 0)
			break;
		Client.SendData(buf, strlen(buf));
	}
	return 0;
}
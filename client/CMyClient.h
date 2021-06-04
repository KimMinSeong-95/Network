#pragma once

#include<WinSock2.h>					// �����
#pragma comment(lib, "ws2_32.lib")		// dll import ����

class CMyClient
{
private:
	SOCKET sock;

public:
	CMyClient();
	~CMyClient();

public:
	void CreateSocket(const char* ip, int port);
	void RecvMessage(SOCKET sock);
	static DWORD __stdcall recvThread(LPVOID value);
	void SendData(const char* msg, int length);
};


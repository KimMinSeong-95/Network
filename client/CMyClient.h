#pragma once

#include<WinSock2.h>					// 선언부
#pragma comment(lib, "ws2_32.lib")		// dll import 정보

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


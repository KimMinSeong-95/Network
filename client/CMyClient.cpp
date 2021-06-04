#include "CMyClient.h"
#include<stdio.h>
#include <ws2tcpip.h>
#include<WinSock2.h>					// 선언부
#pragma comment(lib, "ws2_32.lib")		// dll import 정보

#pragma warning(disable:4996)
CMyClient::CMyClient()
{
	// 1. 라이브러리 초기화(Winsock 2.2 버전)
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패\n");
		exit(-1);
	}
}

CMyClient::~CMyClient()
{
	// 2. 라이브러리 해제
	WSACleanup();

	exit(-1);
}

DWORD __stdcall CMyClient::recvThread(LPVOID value)
{
	SOCKET sock = (SOCKET)value;

	//수신
	char buf[256];
	int retval = recv(sock, buf, sizeof(buf), 0);
	if (retval == -1 || retval == 0)
	{
		printf("소켓 오류 or 상대방이 종료함\n");
		closesocket(sock);
		return 0;
	}
	buf[retval] = '\0';//상대방이 넘길때 strlen() 만큼만 넘겼다고 가정
	printf(">> [수신데이터] %s\n", buf);

	return 0;
}

void CMyClient::CreateSocket(const char* ip, int port)
{
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		throw "소켓 생성 오류";

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	unsigned int numberadd;
	inet_pton(AF_INET, ip, &numberadd);
	addr.sin_addr.s_addr = inet_addr(ip); 
	int retval = connect(sock, (SOCKADDR*)&addr, sizeof(addr));
	if (retval == SOCKET_ERROR)
		throw "서버 연결 실패";

	// 수신 Thread생성하는 위치
	CloseHandle(CreateThread(NULL, 0, recvThread, (LPVOID*)sock, 0, NULL));
}

void CMyClient::RecvMessage(SOCKET sock)
{
	// 송신
	char buf[256];
	strcpy(buf, "AAAA");
	int retval = send(sock, buf, strlen(buf), 0);
	printf("	[송신] %dbyte\n", retval);

	//수신
	char recvbuf[256];
	int retval1 = recv(sock, recvbuf, sizeof(recvbuf), 0);
	recvbuf[retval1] = '\0';
	printf(">> [수신데이터] %s\n", recvbuf);

}


void CMyClient::SendData(const char* msg, int length)
{
	int retval1 = send(sock, msg, length, 0);
	printf("[송신]%dbyte\n", retval1);
}

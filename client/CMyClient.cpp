#include "CMyClient.h"
#include<stdio.h>
#include <ws2tcpip.h>
#include<WinSock2.h>					// �����
#pragma comment(lib, "ws2_32.lib")		// dll import ����

#pragma warning(disable:4996)
CMyClient::CMyClient()
{
	// 1. ���̺귯�� �ʱ�ȭ(Winsock 2.2 ����)
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		exit(-1);
	}
}

CMyClient::~CMyClient()
{
	// 2. ���̺귯�� ����
	WSACleanup();

	exit(-1);
}

DWORD __stdcall CMyClient::recvThread(LPVOID value)
{
	SOCKET sock = (SOCKET)value;

	//����
	char buf[256];
	int retval = recv(sock, buf, sizeof(buf), 0);
	if (retval == -1 || retval == 0)
	{
		printf("���� ���� or ������ ������\n");
		closesocket(sock);
		return 0;
	}
	buf[retval] = '\0';//������ �ѱ涧 strlen() ��ŭ�� �Ѱ�ٰ� ����
	printf(">> [���ŵ�����] %s\n", buf);

	return 0;
}

void CMyClient::CreateSocket(const char* ip, int port)
{
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		throw "���� ���� ����";

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	unsigned int numberadd;
	inet_pton(AF_INET, ip, &numberadd);
	addr.sin_addr.s_addr = inet_addr(ip); 
	int retval = connect(sock, (SOCKADDR*)&addr, sizeof(addr));
	if (retval == SOCKET_ERROR)
		throw "���� ���� ����";

	// ���� Thread�����ϴ� ��ġ
	CloseHandle(CreateThread(NULL, 0, recvThread, (LPVOID*)sock, 0, NULL));
}

void CMyClient::RecvMessage(SOCKET sock)
{
	// �۽�
	char buf[256];
	strcpy(buf, "AAAA");
	int retval = send(sock, buf, strlen(buf), 0);
	printf("	[�۽�] %dbyte\n", retval);

	//����
	char recvbuf[256];
	int retval1 = recv(sock, recvbuf, sizeof(recvbuf), 0);
	recvbuf[retval1] = '\0';
	printf(">> [���ŵ�����] %s\n", recvbuf);

}


void CMyClient::SendData(const char* msg, int length)
{
	int retval1 = send(sock, msg, length, 0);
	printf("[�۽�]%dbyte\n", retval1);
}

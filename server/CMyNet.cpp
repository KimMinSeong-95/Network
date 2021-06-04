#include "CMyNet.h"
#include<stdio.h>
#include<WinSock2.h>					// 선언부
#pragma comment(lib, "ws2_32.lib")		// dll import 정보
#include <ws2tcpip.h>
#pragma warning(disable:4996)

CMyNet* g_mynet = NULL;

CMyNet::CMyNet() : listen_socket(0)
{
	// 1. 라이브러리 초기화(Winsock 2.2 버전)
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패\n");
		exit(-1);
	}
	g_mynet = this;
}

CMyNet::~CMyNet()
{
	// 2. 라이브러리 해제
	WSACleanup();

	exit(-1);
}

void CMyNet::CreateSocket(int port)
{
	listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_socket == INVALID_SOCKET)
		throw "소켓 생성 오류";

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr)); // API ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // long형을 network byte order로
	int retval = bind(listen_socket, (SOCKADDR*)&addr, sizeof(addr));
	if (retval == SOCKET_ERROR)
		throw "bind 오류";

	retval = listen(listen_socket, SOMAXCONN);
	if(retval == SOCKET_ERROR)
		throw "listen 오류";
	
	Run();

}
DWORD _stdcall CMyNet::workThread(LPVOID value)
{
	SOCKET sock = (SOCKET)value;
	while (true)
	{
		// 수신
		char buf[256];
		// sock에 연결된 상대방으로부터 전달된 메시지를 수신하겠다.
		// 단, 나는 수신을 위해 sizeof(buf)의 크기를 준비했고, 그 버퍼의 시작위치를 전달
		// 리턴을 통해 실제 수신된 byte 크기를 확인할 수 있다.
		int retval = recv(sock, buf, sizeof(buf), 0);

		buf[retval] = '\0'; // 상대방이 넘길 때 strlen 만큼만 넘겼다고 가정
		printf(">> [수신데이터] %s\n", buf);

		for (int i = 0; i < (int)g_mynet->clients.size(); i++)
		{
			SOCKET s = g_mynet->clients[i]; // 연산자재정의
			retval = send(s, buf, retval, 0);
		}
		printf("[1대 다 송신] %dbyte\n", retval);
	}

	//vector 삭제 알고리즘
	for (int i = 0; i < (int)g_mynet->clients.size(); i++)
	{
		SOCKET s = g_mynet->clients[i];
		if (s == sock)
		{
			// erase는 삭제할 배열의 주소(위치)를 요구한다.
			// client.begin() : 배열의 시작주소를 반환
			g_mynet->clients.erase(g_mynet->clients.begin() + i);
			closesocket(sock);
			return 0;
		}
	}


	closesocket(sock);
	return 0;
}

void CMyNet::Run()
{
	SOCKET clientsocket;
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr); // 초기화 (필수)

	printf("클라이언트 연결 대기: 192.168.0.88:9000\n");

	while (true)
	{
		clientsocket = accept(listen_socket, (SOCKADDR*)&clientaddr, &addrlen);
		if (clientsocket == INVALID_SOCKET)
		{
			printf("accept오류\n");
			continue;
		}
		char ip[20];
		int port;
		GetAddress(clientsocket, ip, &port);
		printf("[클라이언트 접속] %s:%d\n", ip, port);

		//vector 에 저장 
		clients.push_back(clientsocket);	// 0번째 인덱스부터 차곡차곡 저장
											// 배열의 크기가 자동으로 증가
		
		// 통신 스레드 생성(접속한 소켓 전달)
		CloseHandle(CreateThread(NULL, 0, workThread, (LPVOID*)clientsocket, 0, NULL));
		//RecvMessage(clientsocket);
	}
}


// 소켓을 이용해서 주소를 획득
// getpeername(상대방), getsockname(자신)
void CMyNet::GetAddress(SOCKET sock, char* ip, int* port)
{
	SOCKADDR_IN addr;
	int addrlenth = sizeof(addr);
	getpeername(sock, (SOCKADDR*)&addr, &addrlenth);

	// inet_ntoa :  정수 주소 -> 문자열
	// #include <ws2tcpip.h> // inet_pton
	inet_ntop(AF_INET, &(addr.sin_addr.s_addr), ip, INET_ADDRSTRLEN);
	//strcpy_s(ip, sizeof(char)*20, inet_ntoa(addr.sin_addr)); 
	*port = ntohs(addr.sin_port);


}

#pragma once
#include<vector>
#include<WinSock2.h>					// 선언부
#pragma comment(lib, "ws2_32.lib")		// dll import 정보
using namespace std;

class CMyNet
{
private:
	SOCKET listen_socket;
	vector<SOCKET> clients; // SOCKET을 저장하는 배열, 크기는 가변적으로 관리된다.

	//생성자 & 소멸자
public:
	CMyNet();
	~CMyNet();

	// 메서드
public:
	void CreateSocket(int port);

public:
	void Run();
	void GetAddress(SOCKET sock, char* ip, int* port);

private:
	static DWORD _stdcall workThread(LPVOID value);
};


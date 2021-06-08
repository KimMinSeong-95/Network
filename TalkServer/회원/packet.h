//packet.h
#pragma once

#define PACK_NEWMEMBER 		1     //아이디, 패스워드, 이름
#define PACK_LOGIN			2	  //아이디, 패스워드
#define PACK_LOGOUT			3     // ID

#define ACK_NEWMEMBER_S     11  // echo
#define ACK_NEWMEMBER_F     12  // echo 
#define ACK_LOGIN_S			13  // 아이디,패스워드, 이름
#define ACK_LOGIN_F			14  // echo
#define ACK_LOGOUT_S		15  // echo
#define ACK_LOGOUT_F		16  // echo


struct PACKETNEWMEMBER
{
	int flag;
	char id[10];
	char pw[10];
	char name[20];	
};

typedef PACKETNEWMEMBER PACKLOGIN;

struct PACKETLOGOUT
{
	int flag;
	char id[10];
};

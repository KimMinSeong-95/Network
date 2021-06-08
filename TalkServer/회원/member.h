//Person.h
#pragma once

//서버가 관리할 데이터 타입!
#include <string.h>

class Member
{
	bool islogin;
	char name[20];
	char id[10];
	char pw[10];

public:
	Member(const char* _name, const char* _id, const char* _pw);

	//get Method(상수맴버함수), 맴버변수 수정 불가!
public:
	bool getIsLogin() const { return islogin;  }
	const char* getName() const { return name; }
	const char* getID() const { return id;  }
	const char* getPW() const { return pw;  }

	void setIsLogin(bool b) { islogin = b;  }
};

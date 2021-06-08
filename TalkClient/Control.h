//control.h

#pragma once
#include "CMyClient.h"


class CMy0608ClientDlg;	//클래스 선언!(전방참조)		//<===========

class Control
{
	//싱글톤 패턴 적용 ---------------------------------------------
private:
	Control();
	static Control* instance;
public:
	static Control* getInsatnce()
	{
		if (instance == NULL)
		{
			instance = new Control();
		}
		return instance;
	}
	//------------------------------------------------------------
	CMyClient client; 
	CMy0608ClientDlg* pForm = NULL;				//<====================

public:
	void RecvData(const char* msg, int size);
	void ParentForm(CMy0608ClientDlg* pDlg);	//<====================

	//Form-> Control호출하는 메서드
public:
	void InsertMember(const char* id, const char* pw, const char* name);
	void LoginMember(const char* id, const char* pw);
	void LogOutMember(const char* id);
};


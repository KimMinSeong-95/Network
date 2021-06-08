//chatcontrol.h

#pragma once

#include "CMyClient.h"

class CChatDlg;	//클래스 선언!(전방참조)		//<===========

class ChatControl
{
	//싱글톤 패턴 적용 ---------------------------------------------
private:
	ChatControl();
	static ChatControl* instance;
public:
	static ChatControl* getInsatnce()
	{
		if (instance == NULL)
		{
			instance = new ChatControl();
		}
		return instance;
	}
	//------------------------------------------------------------
	CMyClient client;
	CChatDlg* pForm = NULL;				//<====================

public:
	void RecvData(const char* msg, int size);
	void ParentForm(CChatDlg* pDlg);	//<====================

	//Form-> Control호출하는 메서드
public:
	void ShortMessage(const char* name, const char* msg);
	void MemoMessage(const char* name, const char* msg);	
};


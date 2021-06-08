// CChatDlg.cpp: 구현 파일
//

#include "pch.h"
#include "0608_Client.h"
#include "CChatDlg.h"
#include "afxdialogex.h"
#include "ChatControl.h"

// CChatDlg 대화 상자

CChatDlg* g_pDlg = NULL;				//<==================1

IMPLEMENT_DYNAMIC(CChatDlg, CDialogEx)

CChatDlg::CChatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_DIALOG, pParent)
	, m_strshortmessage(_T(""))
	, m_strMemo(_T(""))
{
	g_pDlg = this;						//<==================2
}

CChatDlg::~CChatDlg()
{
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_strshortmessage);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlList);
	DDX_Text(pDX, IDC_EDIT4, m_strMemo);
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CChatDlg::OnBnClickedButton1)
	ON_MESSAGE(EVENT_SENDMESSAGE, &CChatDlg::OnMyMessage)
	ON_MESSAGE(EVENT_MEMOMESSAGE, &CChatDlg::OnMyMemoMessage)
	ON_BN_CLICKED(IDC_BUTTON3, &CChatDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CChatDlg 메시지 처리기


void CChatDlg::SendData(CString name)
{
	// TODO: 여기에 구현 코드 추가./
	m_name = name;
}


BOOL CChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString str;
	str.Format("%s님이 로그인하셨습니다.", m_name);
	SetWindowText(str);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//채팅 전송 버튼
void CChatDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_strshortmessage == "")
	{		
		return;
	}

	ChatControl::getInsatnce()->ShortMessage(m_name, m_strshortmessage);
	m_strshortmessage = "";
	UpdateData(FALSE);
}

void CChatDlg::MemoMessage(PACKETMEMO* msg)
{
	//크로스 스레드문제...
	g_pDlg->PostMessage(EVENT_MEMOMESSAGE, (WPARAM)msg, 0);
}

LRESULT CChatDlg::OnMyMemoMessage(WPARAM wParam, LPARAM lParam)
{
	PACKETMEMO* pmsg = (PACKETMEMO*)wParam;
	m_strMemo = pmsg->msg;

	UpdateData(FALSE);	//<-----

	return 0;
}


void CChatDlg::ShortMessage(PACKETSHORTMESSAGE* msg)
{
	// TODO: 여기에 구현 코드 추가.
	g_pDlg->PostMessage(EVENT_SENDMESSAGE, (WPARAM)msg, 0);			//<======= 3
//	DisplayText("[%s]%s(%d:%d:%d)",
//		g_msg->name, g_msg->msg, g_msg->hour, g_msg->min, g_msg->second);
	
}

// 에디트 컨트롤에 문자열 출력
void CChatDlg::DisplayText(char* fmt, ...)
{
	va_list arg;			va_start(arg, fmt);

	char cbuf[512 + 256];	vsprintf_s(cbuf, fmt, arg);

	//크로스 쓰레드 문제 발생!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//컨트롤을 생성한 쓰레드(primary thread)
	//컨트롤을 사용하는 쓰레드가 다를경우 발생하는 문제.
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	int nLength = pEdit->GetWindowTextLength();
	pEdit->SetSel(nLength, nLength);
	pEdit->ReplaceSel(cbuf);

	va_end(arg);
}

LRESULT CChatDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{	
	PACKETSHORTMESSAGE* p = (PACKETSHORTMESSAGE*)wParam;
	DisplayText("[%s]%s(%d:%d:%d)\r\n",
		p->name, p->msg, p->hour, p->min, p->second);
	return 0;
}

//쪽지 보내기
void CChatDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_strMemo == "")
	{
		return;
	}

	ChatControl::getInsatnce()->MemoMessage(m_name, m_strMemo);
	m_strMemo = "";
	UpdateData(FALSE);
}

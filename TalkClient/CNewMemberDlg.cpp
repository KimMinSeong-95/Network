// CNewMemberDlg.cpp: 구현 파일
//

#include "pch.h"
#include "0608_Client.h"
#include "CNewMemberDlg.h"
#include "afxdialogex.h"


// CNewMemberDlg 대화 상자

IMPLEMENT_DYNAMIC(CNewMemberDlg, CDialogEx)

CNewMemberDlg::CNewMemberDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_DIALOG, pParent)
	, m_strID(_T(""))
	, m_strPassword(_T(""))
	, m_strName(_T(""))
{

}

CNewMemberDlg::~CNewMemberDlg()
{
}

void CNewMemberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strID);
	DDX_Text(pDX, IDC_EDIT2, m_strPassword);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
}


BEGIN_MESSAGE_MAP(CNewMemberDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNewMemberDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNewMemberDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CNewMemberDlg 메시지 처리기

//중복체크
void CNewMemberDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_strID;

	//서버로 전송

}


//회원가입
void CNewMemberDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//UpdateData(TRUE).
	//IDOK 반환 설정.
	CDialog::OnOK();
}


void CNewMemberDlg::GetData(CString& id, CString& pw, CString& name)
{
	// TODO: 여기에 구현 코드 추가.
	id = m_strID;
	pw = m_strPassword;
	name = m_strName;
}

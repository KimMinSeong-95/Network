#pragma once


// CNewMemberDlg 대화 상자

class CNewMemberDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewMemberDlg)

public:
	CNewMemberDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNewMemberDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_strID;
	CString m_strPassword;
	CString m_strName;
	void GetData(CString& id, CString& pw, CString& name);
};

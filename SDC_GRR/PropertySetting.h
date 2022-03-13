#pragma once
#include "afxwin.h"
#include "afxpropertygridctrl.h"


// CPropertySetting 대화 상자입니다.

class CPropertySetting : public CDialogEx
{
	DECLARE_DYNAMIC(CPropertySetting)

public:
	CPropertySetting(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPropertySetting();

	virtual void OnFinalRelease();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CButton m_Apply;
	CButton m_Cancel;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CMFCPropertyGridCtrl m_PropGrid1;
};

#pragma once
#include "afxwin.h"
#include "afxpropertygridctrl.h"


// CPropertySetting ��ȭ �����Դϴ�.

class CPropertySetting : public CDialogEx
{
	DECLARE_DYNAMIC(CPropertySetting)

public:
	CPropertySetting(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPropertySetting();

	virtual void OnFinalRelease();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ChartCtrl_source/ChartCtrl.h"




// ResultDialog 대화 상자입니다.

class ResultDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ResultDialog)

public:
	ResultDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ResultDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_grrvalue;
	virtual BOOL OnInitDialog();
	CListCtrl m_grrpercent;
	afx_msg void OnLvnColumnclickList4(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_DirectoryPath;
	afx_msg void OnNMCustomdrawList4(NMHDR *pNMHDR, LRESULT *pResult);
	CString FailItemList;
	BOOL ChangeColorOfListControl1;
	BOOL ChangeColorOfListControl2;
	BOOL ChangeColorOfListControl3;
	BOOL ChangingListControl;
	CButton m_ShowGrrValueFailed;
	afx_msg
		void DrawingGraph(void);
	void OnBnClickedCheck1();
	afx_msg void OnNMCustomdrawList3(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_ComboTester;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnOK();
	virtual void OnCancel();
	CEdit m_TotalPass;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString TotalPass;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CBrush m_backBrush;
	COLORREF m_color;
	CChartCtrl m_ChartCtrl;
	CEdit m_Samplename;
	CEdit m_Itemname;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_summaryList;
	afx_msg void OnNMCustomdrawList5(NMHDR *pNMHDR, LRESULT *pResult);
};

static int CALLBACK CompareDoubleFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam);
static int CALLBACK CompareStringFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam);
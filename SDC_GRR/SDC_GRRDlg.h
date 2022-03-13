
// SDC_GRRDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "calculation.h"


class CSDC_GRRDlgAutoProxy;

#define ERRORALERT AfxMessageBox("ERROR!")
#define SW_VERSION "SDC_GRR_v3.6  "
#define SFT_DISTRIBUTE

// CSDC_GRRDlg 대화 상자
class CSDC_GRRDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSDC_GRRDlg);
	friend class CSDC_GRRDlgAutoProxy;

// 생성입니다.
public:
	CSDC_GRRDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	virtual ~CSDC_GRRDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SDC_GRR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	CSDC_GRRDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
//	virtual void OnOK();
//	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_addfile;
	CButton m_adddirectory;
	CButton m_deleteselected;
	CButton m_deleteall;
	CButton m_pathofresult;
	CButton m_grrstart;
	CEdit m_savepath;
	CListBox m_filelist;
	CEdit m_filenum;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	void SetSavePath(CString strsavePath);
	void ShowFileNum();
	void GetFileList(CString strFolder);
	void CreateHorizontalScroll();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CListCtrl m_listctrl;
	CButton m_CheckItems;
	afx_msg void OnBnClickedButton7();
	CButton m_deleteitem;
	afx_msg void OnBnClickedButton8();
	CEdit m_trialnumber;
	int FileScan(ItemValue unpivot[], SpecValue Spec[], int * Datanumber, int *mode, CString *Log);
	int SpecScan(SpecValue Spec[], int * Datanumber, CString *Log);
	CButton m_SpecButton;
	CEdit m_specpath;
	afx_msg void OnBnClickedButton9();
	void LogPrintinEditControl(CString str);
	CEdit m_goldentester;
	virtual void OnOK();
	virtual void OnCancel();
	CEdit m_logresult;
	CString LogStrPrinting(int Mode, CString PrintingStr);
	void CreateReport(ItemValue unpivotdata[], SpecValue Spec[], CString kind, int Datanumber, CString Path);
	CProgressCtrl m_Progress1;
	CProgressCtrl m_Progress2;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_settingbutton;
	afx_msg void OnBnClickedButtonSetting();
	void TrialNumberChange(void);
	BOOL AdministratorMode;
//	afx_msg void OnHdnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
};

void Wait(DWORD dwMillisecond);
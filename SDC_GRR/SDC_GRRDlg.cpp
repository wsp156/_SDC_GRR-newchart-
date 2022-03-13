
// SDC_GRRDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SDC_GRR.h"
#include "SDC_GRRDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "calculation.h"
#include "ResultDialog.h"
#include "BinaryConverting_Moon.h"
#include "PropertySetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSDC_GRRDlg 대화 상자


IMPLEMENT_DYNAMIC(CSDC_GRRDlg, CDialogEx);

CSDC_GRRDlg::CSDC_GRRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SDC_GRR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CSDC_GRRDlg::~CSDC_GRRDlg()
{
	// 이 대화 상자에 대한 자동화 프록시가 있을 경우 이 대화 상자에 대한
	//  후방 포인터를 NULL로 설정하여
	//  대화 상자가 삭제되었음을 알 수 있게 합니다.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CSDC_GRRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_addfile);
	DDX_Control(pDX, IDC_BUTTON2, m_adddirectory);
	DDX_Control(pDX, IDC_BUTTON3, m_deleteselected);
	DDX_Control(pDX, IDC_BUTTON4, m_deleteall);
	DDX_Control(pDX, IDC_BUTTON5, m_pathofresult);
	DDX_Control(pDX, IDC_BUTTON6, m_grrstart);
	DDX_Control(pDX, IDC_EDIT1, m_savepath);
	DDX_Control(pDX, IDC_LIST1, m_filelist);
	DDX_Control(pDX, IDC_EDIT2, m_filenum);
	DDX_Control(pDX, IDC_LIST2, m_listctrl);
	DDX_Control(pDX, IDC_BUTTON7, m_CheckItems);
	DDX_Control(pDX, IDC_BUTTON8, m_deleteitem);
	DDX_Control(pDX, IDC_EDIT3, m_trialnumber);
	DDX_Control(pDX, IDC_BUTTON9, m_SpecButton);
	DDX_Control(pDX, IDC_EDIT4, m_specpath);
	DDX_Control(pDX, IDC_EDIT5, m_goldentester);
	DDX_Control(pDX, IDC_EDIT6, m_logresult);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress1);
	DDX_Control(pDX, IDC_PROGRESS2, m_Progress2);
	DDX_Control(pDX, IDC_BUTTON_Setting, m_settingbutton);
}

BEGIN_MESSAGE_MAP(CSDC_GRRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSDC_GRRDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSDC_GRRDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSDC_GRRDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSDC_GRRDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CSDC_GRRDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CSDC_GRRDlg::OnBnClickedButton6)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON7, &CSDC_GRRDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CSDC_GRRDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CSDC_GRRDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_Setting, &CSDC_GRRDlg::OnBnClickedButtonSetting)
//	ON_NOTIFY(HDN_ITEMCHANGED, 0, &CSDC_GRRDlg::OnHdnItemchangedList2)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CSDC_GRRDlg::OnLvnItemchangedList2)
END_MESSAGE_MAP()


// CSDC_GRRDlg 메시지 처리기

BOOL CSDC_GRRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetWindowTextA(SW_VERSION);
	m_listctrl .SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSDC_GRRDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSDC_GRRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSDC_GRRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 컨트롤러에서 해당 개체 중 하나를 계속 사용하고 있을 경우
//  사용자가 UI를 닫을 때 자동화 서버를 종료하면 안 됩니다.  이들
//  메시지 처리기는 프록시가 아직 사용 중인 경우 UI는 숨기지만,
//  UI가 표시되지 않아도 대화 상자는
//  남겨 둡니다.

void CSDC_GRRDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CSDC_GRRDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


void CSDC_GRRDlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::OnCancel();
}

BOOL CSDC_GRRDlg::CanExit()
{
	// 프록시 개체가 계속 남아 있으면 자동화 컨트롤러에서는
	//  이 응용 프로그램을 계속 사용합니다.  대화 상자는 남겨 두지만
	//  해당 UI는 숨깁니다.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

// 파일 단위로 추가 버튼
void CSDC_GRRDlg::OnBnClickedButton1()
{
	CString PathRead;
	CStdioFile FileRead;
	CString filename;
	CString strfilelist;
	const int MaxFiles = 400;
	const int BuffSize = (MaxFiles * (MAX_PATH + 1)) + 1;

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, "CSV Files(*.csv)|*.csv|All Files(*.*)|*.*|");

	dlg.GetOFN().lpstrFile = strfilelist.GetBuffer(BuffSize);
	dlg.GetOFN().nMaxFile = BuffSize;

	if (dlg.DoModal() == IDOK)
	{
		for (POSITION pos = dlg.GetStartPosition(); pos != NULL;)
		{
			PathRead = dlg.GetNextPathName(pos);
			m_filelist.AddString(PathRead);
		}
	}
	CreateHorizontalScroll();
	ShowFileNum();
	SetSavePath(PathRead);
}


// 폴더 단위로 추가 버튼
void CSDC_GRRDlg::OnBnClickedButton2()
{
	CString strInitPath = ".\\";
	CString strFolderPath;

	// 폴더 선택 다이얼로그
	CFolderPickerDialog Picker(strInitPath, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, NULL, 0);
	if (Picker.DoModal() == IDOK)
	{
		strFolderPath = Picker.GetPathName();
		GetFileList(strFolderPath);
	}
	CreateHorizontalScroll();
	ShowFileNum();
	SetSavePath(strFolderPath);
}

// 파일 단위로 삭제 버튼
void CSDC_GRRDlg::OnBnClickedButton3()
{
	int count = m_filelist.GetCount();
	for (int i = count - 1; i >= 0; i--)
	{
		if (m_filelist.GetSel(i))
			m_filelist.DeleteString(i);
	}
	ShowFileNum();
}


// 전체 삭제 버튼
void CSDC_GRRDlg::OnBnClickedButton4()
{
	m_filelist.ResetContent();
	ShowFileNum();
}

//저장경로 지정 버튼
void CSDC_GRRDlg::OnBnClickedButton5()
{
	CString strInitPath = ".\\";

	// 폴더 선택 다이얼로그
	CFolderPickerDialog Picker(strInitPath, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, NULL, 0);
	if (Picker.DoModal() == IDOK)
	{
		CString strPath = Picker.GetPathName();
		m_savepath.SetWindowTextA(strPath);
	}
}
//파일 갯수 나타내는 함수
void CSDC_GRRDlg::ShowFileNum()
{
	CString filenum;
	filenum.Format("%d", m_filelist.GetCount());
	m_filenum.SetWindowTextA(filenum);
}

//폴더 내 파일들 불러오기
void CSDC_GRRDlg::GetFileList(CString strFolder)
{
	CFileFind file;
	BOOL b = file.FindFile(strFolder + "\\*.*");  // CString strMusicFilter = ".MP3.OGG.WMA.WAV";   // 필터링 하고 싶으면 이렇게 쓰면 됨
	CString strFolderItem, strFileExt, strTempString;
	while (b)
	{
		b = file.FindNextFile();
		if (file.IsDirectory() && !file.IsDots())   // 디렉토리 발견시 
		{
			strFolderItem = file.GetFilePath();
			GetFileList(strFolderItem);      // 하위폴더를 검색하기 위해 재귀호출 발생  
		}
		strFolderItem = file.GetFilePath();

		strFileExt = strFolderItem.Mid(strFolderItem.ReverseFind('.'));  // 확장자만 추출한다. 
		if (!file.IsDots())         // 파일 탐색 필터 정의에따라 해당 StringList에 추가
		{
			strFileExt.MakeUpper();       // strFileExt 에는 확장자 (.EXE 형태) 가 들어옴. 비교위해 대문자화 함
			if (file.IsDirectory())
				continue;    // 폴더만 남는 경우는 넣으면 안됨 
			if (strFolderItem.Find(".csv") != -1)
				m_filelist.AddString(strFolderItem);
		}
	}
}

//가로스크롤 만드는 함수
void CSDC_GRRDlg::CreateHorizontalScroll()
{
	CString str;
	CSize sz;
	int dx = 0;
	CDC *pDC = m_filelist.GetDC();

	for (int i = 0; i < m_filelist.GetCount(); i++)
	{
		m_filelist.GetText(i, str);
		sz = pDC->GetTextExtent(str);

		if (sz.cx > dx)
			dx = sz.cx;
	}
	m_filelist.ReleaseDC(pDC);

	if (m_filelist.GetHorizontalExtent() < dx)
	{
		m_filelist.SetHorizontalExtent(dx);
		ASSERT(m_filelist.GetHorizontalExtent() == dx);
	}
}
//드래그앤드랍
void CSDC_GRRDlg::OnDropFiles(HDROP hDropInfo)
{
	UINT i = 0;    //Drag&Drop된 파일,폴더의 갯수저장
				   //드롭된 파일의 갯수
	UINT uCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char buffer[400];  //Drag&Drop된 파일,폴더의 절대경로 저장

	for (i = 0; i < uCount; i++)
	{
		// 파일의 경로 얻어옴
		DragQueryFile(hDropInfo, i, buffer, 400);

		if (PathIsDirectory(buffer))
			GetFileList(buffer);
		else
			m_filelist.AddString(buffer);
	}
	CreateHorizontalScroll();
	ShowFileNum();
	SetSavePath(buffer);

	CDialogEx::OnDropFiles(hDropInfo);
}


//GRR 버튼
void CSDC_GRRDlg::OnBnClickedButton6()
{
	AfxGetApp()->DoWaitCursor(1);
	
	m_Progress2.SetRange(0,11);
	m_Progress2.SetPos(0);
	m_logresult.SetWindowTextA("");
	CString LogStr = "";
	BOOL TotalPass = TRUE;
	AdministratorMode = FALSE;
	CString goldentester = "";
	m_goldentester.GetWindowTextA(goldentester);

	if (goldentester == "Administrator")
		AdministratorMode = TRUE;
	/*************************************결과 폴더 생성****************************************************/
	CStdioFile FileWrite;
	CString WriteFilePath = "";

	//시간을 파일명에 추가
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString time_current;
	CString time_report;
	time_current.Format("%02d%02d%02d%02d%02d%02d", st.wYear - 2000, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	time_report.Format("%04d-%02d-%02d %02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	m_savepath.GetWindowTextA(WriteFilePath);
	WriteFilePath += "\\" + time_current + "_GRR_Result";
	if (GetFileAttributes(WriteFilePath) == 0xFFFFFFFF)
	{
		CreateDirectory(WriteFilePath, NULL);
	}
	CString DirectoryPath = WriteFilePath;

	LogStr += LogStrPrinting(MODEINFORM,  "Created Result Directory : " + DirectoryPath + "\n");


	/*****************************GRR 시작!**************************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "GRR Start!!!\n");
	LogStr += LogStrPrinting(MODEINFORM, "SW Version : \n");
	LogStr += LogStrPrinting(MODEINFORM, SW_VERSION);
	LogStr += LogStrPrinting(MODEINFORM, "\n");

	ItemValue unpivot[MAXDATAQUANTITY] = {};
	SpecValue Spec[1] = {};
	CString Serialnumber[MAXSAMPLESIZE] = {};
	CString Tester[MAXSAMPLESIZE] = {};
	int Datanumber = 0;
	int testernumber = 0;
	int serialnumber = 0;
	int trialmin = 0;
	CString trialstring;
	int mode = 1;  //아이템 이름과 value 모두 필요하기에 1로 지정	
	BOOL SFT_TEST = FALSE;

	/*******************************Trial number 구하기********************************************************/
	TrialNumberChange();
	LogStr += LogStrPrinting(MODEINFORM, "Checking Trial number...\n");
	m_trialnumber.GetWindowTextA(trialstring);
	if (trialstring.Find("test") != -1)
	{
		trialstring.Replace("test", "");
		trialmin = atoi(trialstring);
	}
	else
	{
		trialmin = atoi(trialstring);
		if (trialmin < 5 && AdministratorMode == FALSE)
		{
			ERRORALERT;
			LogStr += LogStrPrinting(MODEWARNING, "The number of minimum trial is lower than 5\n");
			TotalPass = FALSE;
			return;
		}
	}
	LogStr += LogStrPrinting(MODEINFORM, "Trial number is " + trialstring + "\n");
	/************************List Contorl Item에 있는 Serialnumber List 구하기*******************************/
	LogStr += LogStrPrinting(MODEINFORM, "Checking Serialnumber List...\n");
	serialnumber = m_listctrl.GetItemCount();
	for (int i = 0; i < serialnumber; i++)
	{
		Serialnumber[i] = m_listctrl.GetItemText(i, 0);
		LogStr += LogStrPrinting(MODERESULT, Serialnumber[i] + "\n");
	}
	if (serialnumber < 5 && AdministratorMode == FALSE)
	{
		ERRORALERT;
		LogStr += LogStrPrinting(MODEWARNING, "Please do GRR with more than 5 samples\n");
		TotalPass = FALSE;
		return;
	}
	/************************Coulumn에 있는 Tester List 구하기*********************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Checking Tester List...\n");
	LVCOLUMN ss;    //변수선언
	char temparary[256] = {};
	ss.mask = LVCF_TEXT | LVCF_WIDTH; //구조체 초기화
	ss.pszText = temparary;//구조체의 문자열 초기화
	ss.cchTextMax = 256;//최대길이
	ss.cx = 0;
	CHeaderCtrl  *pHead = NULL;
	int	nRowCnt = 0;
	pHead = m_listctrl.GetHeaderCtrl();
	nRowCnt = pHead->GetItemCount();

	while (testernumber < nRowCnt - 1)
	{
		m_listctrl.GetColumn(testernumber + 1, &ss);
		Tester[testernumber] = ss.pszText;
		LogStr += LogStrPrinting(MODERESULT, Tester[testernumber] + "\n");
		testernumber++;
	}
	if (testernumber < 2 && AdministratorMode == FALSE)
	{
		ERRORALERT;
		LogStr += LogStrPrinting(MODEWARNING, "Please do GRR with more than 2 testers\n");
		TotalPass = FALSE;
		return;
	}
	m_Progress2.SetPos(m_Progress2.GetPos() + 1);

	/*****************************스펙파일 스캔해서 데이터 가져오기**********************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Spec File Scanning...\n");
	if (SpecScan(Spec, &Datanumber, &LogStr) != 0)
		TotalPass = FALSE;
	m_Progress2.SetPos(m_Progress2.GetPos() + 1);
	if (Spec[0].totalitemnumber == 0)
		return;
	/*****************************데이터파일 스캔해서 데이터 가져오기********************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Data File Scanning...\n");
	m_Progress1.SetRange(0, trialmin * serialnumber * testernumber);
	m_Progress1.SetPos(0);
	if (FileScan(unpivot, Spec, &Datanumber, &mode, &LogStr) != 0)
		TotalPass = FALSE;
	
	m_Progress2.SetPos(m_Progress2.GetPos()+1);
	/*******************데이터 파일과 스펙 파일 FOM 비교하여 모델과 테스터종류 확인*****************************/
	LogStr += LogStrPrinting(MODEINFORM, "Checking Model and Tester type...\n");
	for (int k = 0; k < Datanumber; k++)
	{
		if (unpivot[k].fom != "")
		{
			if (unpivot[k].fom.Find("SFT_TEST") != -1)
				SFT_TEST = TRUE;
			else
				SFT_TEST = FALSE;
		}
		if (unpivot[k].fom != Spec[0].fom)
		{
			ERRORALERT;
			LogStr += LogStrPrinting(MODEWARNING, "The model name of Data file and Spec file is different. " + unpivot[k].fom + " vs " + Spec[0].fom + "\n");
			TotalPass = FALSE;
			return;
		}
	}
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/****************************여기서부터 Golden GRR Value을 위한 계산***********************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Start to calculate Golden GRR Values...\n");
	/************************각 모든 Tester별, Sample 별 평균, std 구하기**************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Calculating \"Average\" and \"Standard deviation\" for each sample and tester...\n");
	ItemValue unpivot_average[MAXDATAQUANTITY] = {};
	ItemValue unpivot_std[MAXDATAQUANTITY] = {};
	LogStr += CalculateUnpivotAverageStd(unpivot, Spec, Serialnumber, Tester, Datanumber, trialmin, unpivot_average, unpivot_std);
	CreateReport(unpivot_average, Spec, "Average", Datanumber, WriteFilePath);
	CreateReport(unpivot_std, Spec, "Std", Datanumber, WriteFilePath);
	m_Progress2.SetPos(m_Progress2.GetPos()+1);

	/************************각 모든 Tester별, Sample 별 median, min, max 구하기**************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Calculating \"Median Values\" for each sample and tester...\n");
	ItemValue unpivot_median[MAXDATAQUANTITY] = {};
	LogStr += CalculateUnpivotMedian(unpivot, Spec, Serialnumber, Tester, Datanumber, trialmin, unpivot_median);
	CreateReport(unpivot_median, Spec, "Median", Datanumber, WriteFilePath);

	LogStr += LogStrPrinting(MODEINFORM, "Calculating \"Min Values\" for each sample and tester...\n");
	ItemValue unpivot_min[MAXDATAQUANTITY] = {};
	LogStr += CalculateUnpivotMin(unpivot, Spec, Serialnumber, Tester, Datanumber, trialmin, unpivot_min);
	CreateReport(unpivot_min, Spec, "Min", Datanumber, WriteFilePath);

	LogStr += LogStrPrinting(MODEINFORM, "Calculating \"Max Values\" for each sample and tester...\n");
	ItemValue unpivot_max[MAXDATAQUANTITY] = {};
	LogStr += CalculateUnpivotMax(unpivot, Spec, Serialnumber, Tester, Datanumber, trialmin, unpivot_max);
	CreateReport(unpivot_max, Spec, "Max", Datanumber, WriteFilePath);

	m_Progress2.SetPos(m_Progress2.GetPos()+1);
	/****************************골든 테스터 가져오거나 선정하기********************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Setting \"Golen Tester\"...\n");

	if (goldentester == "" || goldentester == "Administrator")
	{
		LogStr += LogStrPrinting(MODEINFORM, "Calculating each score of the testers...\n");
		LogStr += SettingGoldenTester(unpivot_average, unpivot_std, unpivot_median, Spec, Serialnumber, Tester, Datanumber, &goldentester);
		LogStr += LogStrPrinting(MODEINFORM, "The Golden Tester is " + goldentester + "\n");
	}
	else
	{
		LogStr += LogStrPrinting(MODEINFORM, "Checking the golen Tester you inserted...\n");
		BOOL FindTester = FALSE;
		for (int j = 0; j < testernumber; j++)
		{
			if (Tester[j] == goldentester)
			{
				FindTester = TRUE;
				LogStr += LogStrPrinting(MODEINFORM, "The Golden Tester is " + goldentester + "\n");
			}
		}
		if (FindTester == FALSE)
		{
			ERRORALERT;
			LogStr += LogStrPrinting(MODEINFORM, "The name of the golden tester is wrong!\n");
			return;
		}
	}
	m_Progress2.SetPos(m_Progress2.GetPos()+1);
	/****************************GoldenTester Median 값 가져오기********************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Extracting \"the golden tester's Median Value\"...\n");
	ItemValue unpivot_median_golden[MAXDATAQUANTITY] = {};
	LogStr += CalculateGoldenMedian(unpivot_median, Spec, Serialnumber, Tester, Datanumber, goldentester, unpivot_median_golden);
	m_Progress2.SetPos(m_Progress2.GetPos()+1);
	/******************************* Golden GRR Value 구하기***********************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Calculating \"Golden GRR Values\"...\n");
	ItemValue unpivot_min_grr_negative[MAXDATAQUANTITY] = {};
	ItemValue unpivot_max_grr_positive[MAXDATAQUANTITY] = {};
	int GrrDatanumber = 0;
	LogStr += CalculateGoldenGRR(unpivot_average, unpivot_std, unpivot_median_golden, Spec, Serialnumber, Tester, goldentester, &GrrDatanumber, unpivot_min_grr_negative, unpivot_max_grr_positive);

	CreateReport(unpivot_min_grr_negative, Spec, "min_grr_negative", GrrDatanumber, WriteFilePath);
	CreateReport(unpivot_max_grr_positive, Spec, "max_grr_positive", GrrDatanumber, WriteFilePath);
	m_Progress2.SetPos(m_Progress2.GetPos()+1);
	/******************************* Golden GRR Value 비교하기***********************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Comparing \"the Golden GRR Value\" to judge Pass or Fail...\n");
	CString TotalFailItem = "";
	double Max_LIMIT[MAXITEMSIZE] = {  };
	double Min_LIMIT[MAXITEMSIZE] = {  };
	CString GRRpassfail[MAXSAMPLESIZE][MAXSAMPLESIZE] = {""};
	CString S2GRRpassfail[MAXSAMPLESIZE][MAXSAMPLESIZE] = { "" };
	CString S3GRRpassfail[MAXSAMPLESIZE][MAXSAMPLESIZE] = { "" };
	CString GoldenGRRpassfailtable = "";
	LogStr += GoldenGRRComparing(unpivot_max_grr_positive, unpivot_min_grr_negative,Spec, Serialnumber, Tester, GrrDatanumber, GRRpassfail, &TotalFailItem);
	LogStr += S2GoldenGRRComparing(unpivot, Spec, Serialnumber, Tester, Datanumber, S2GRRpassfail, &TotalFailItem);
	LogStr += S3GoldenGRRComparing(unpivot, Spec, Serialnumber, Tester, Datanumber, S3GRRpassfail, &TotalFailItem);
	for (int i = 0; i < serialnumber + 1; i++)
	{
		for (int j = 0; j < testernumber + 1; j++)
		{
			GoldenGRRpassfailtable += GRRpassfail[i][j] + ",";
			if (GRRpassfail[i][j] == "FAIL" || S2GRRpassfail[i][j] == "FAIL" || S3GRRpassfail[i][j] == "FAIL")
				TotalPass = FALSE;
		}
		GoldenGRRpassfailtable += "\n";
	}
	LogStr += LogStrPrinting(MODEINFORM, "Calculating the Golden GRR Values is done...!\n");
	m_Progress2.SetPos(m_Progress2.GetPos()+1);
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/****************************여기서부터 %GRR을 위한 계산****************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Start to calculate %GRR Values...\n");
	double RangeAverage = 0;
	double XDiff = 0;
	double Rpart = 0;
	double Tol[MAXITEMSIZE] = {};
	double K1 = 0;
	double K2 = 0;
	double K3 = 0;
	double EV = 0;
	double AV = 0;
	double GRR = 0;
	double PV = 0;
	double TV = 0;
	CString PercentEV[MAXITEMSIZE] = {};
	CString PercentAV[MAXITEMSIZE] = {};
	CString PercentPartperTester[MAXITEMSIZE] = {};
	CString PercentPV[MAXITEMSIZE] = {};
	CString PercentGRR[MAXITEMSIZE] = {};
	CString NDC[MAXITEMSIZE] = {};
	CString PercentGRRTester[MAXSAMPLESIZE] = {};
	CString MIN[MAXITEMSIZE] = {};
	CString MAX[MAXITEMSIZE] = {};
	CString ErrorCount[MAXITEMSIZE] = {};
	CString result = "";
	CString Percent_GRR_result = "";
	CString temppass = "";
	CString nowtester = "";
	
	int PercentGRRtesternumber = 0;
#ifdef SFT_DISTRIBUTE
	if(SFT_TEST == TRUE)
		PercentGRRtesternumber = testernumber;
	else
#endif // SFT_DISTRIBUTE
		PercentGRRtesternumber = 1;
	m_Progress1.SetRange(0, PercentGRRtesternumber);
	m_Progress1.SetPos(0);
	/******************************* EV/AV/PV/%EV/%AV/%P_T/%PV/%GRR/NDC 계산***********************************************************/
	CString TesterResultOfPercentGRR[MAXSAMPLESIZE] = {};
	BOOL testertempresult = TRUE;
	for(int t=0; t<PercentGRRtesternumber; t++)
	{
#ifdef 	SFT_DISTRIBUTE
		if (SFT_TEST == TRUE)
		{
			PercentGRRTester[0] = Tester[t];
			nowtester = PercentGRRTester[0];
		}
		else
		{
#endif
		for (int j = 0; j<testernumber; j++)
			PercentGRRTester[j] = Tester[j];
		nowtester = "ALL";
#ifdef SFT_DISTRIBUTE
		}
#endif
		for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
		{
			double dresult = 0;
			CString tmp = "";
			if (SCORE2)
			{
				PercentEV[Itemindex]= "-";
				PercentAV[Itemindex]= "-";
				PercentPartperTester[Itemindex] = "-";
				PercentPV[Itemindex] = "-";
				NDC[Itemindex] = "-";
				PercentGRR[Itemindex] = "-";
				MAX[Itemindex] = "-";
				MIN[Itemindex] = "-";
				Tol[Itemindex] = atof(Spec[0].USL[Itemindex]) - atof(Spec[0].LSL[Itemindex]);
				LogStr += CalculatingPercentGRR(MODESCORE2, unpivot, atof(Spec[0].USL[Itemindex]), atof(Spec[0].LSL[Itemindex]), NULL, Itemindex, Datanumber, Serialnumber, PercentGRRTester, NULL, &dresult);
				ErrorCount[Itemindex].Format("%.2f", dresult);
				if (atof(ErrorCount[Itemindex]) > 0)
					TotalPass = FALSE;
			}
			else if (SCORE3)
			{
				PercentPartperTester[Itemindex] = "-";
				PercentPV[Itemindex] = "-";
				NDC[Itemindex] = "-";
				PercentEV[Itemindex] = "-";
				PercentAV[Itemindex] = "-";
				PercentGRR[Itemindex] = "-";
				ErrorCount[Itemindex] = "-";
				Tol[Itemindex] = atof(Spec[0].USL[Itemindex]) - atof(Spec[0].LSL[Itemindex]);
				LogStr += CalculatingPercentGRR(MODESCORE3_MAX, unpivot, atof(Spec[0].USL[Itemindex]), atof(Spec[0].LSL[Itemindex]), NULL, Itemindex, Datanumber, Serialnumber, PercentGRRTester, NULL, &dresult);
				MAX[Itemindex].Format("%.2f", dresult);
				LogStr += CalculatingPercentGRR(MODESCORE3_MIN, unpivot, atof(Spec[0].USL[Itemindex]), atof(Spec[0].LSL[Itemindex]), NULL, Itemindex, Datanumber, Serialnumber, PercentGRRTester, NULL, &dresult);
				MIN[Itemindex].Format("%.2f",dresult);
				if((atof(MIN[Itemindex]) >= atof(Spec[0].LSL[Itemindex])) || (atof(MAX[Itemindex]) >= atof(Spec[0].USL[Itemindex])))
					TotalPass = FALSE;
			}
			else
			{
				ErrorCount[Itemindex] = "-";
				MIN[Itemindex] = "-";
				MAX[Itemindex] = "-";
				tmp.Format("Item Name:%s \n", Spec[0].itemname[Itemindex]);
				LogStr += tmp;
				LogStr += CalculatingPercentGRR(MODERANGEAVERAGE, unpivot, NULL, NULL, NULL, Itemindex, Datanumber, Serialnumber, PercentGRRTester, trialmin, &RangeAverage);
				LogStr += CalculatingPercentGRR(MODEXDIFF, unpivot, NULL, NULL, NULL, Itemindex, Datanumber, Serialnumber, PercentGRRTester, trialmin, &XDiff);
				LogStr += CalculatingPercentGRR(MODERPART, unpivot, NULL, NULL, NULL, Itemindex, Datanumber, Serialnumber, PercentGRRTester, trialmin, &Rpart);
				LogStr += CalculatingPercentGRR(MODEK1, NULL, NULL, NULL, NULL, NULL, NULL, Serialnumber, PercentGRRTester, trialmin, &K1);
				LogStr += CalculatingPercentGRR(MODEK2, NULL, NULL, NULL, NULL, NULL, NULL, Serialnumber, PercentGRRTester, NULL, &K2);
				LogStr += CalculatingPercentGRR(MODEK3, NULL, NULL, NULL, NULL, NULL, NULL, Serialnumber, PercentGRRTester, NULL, &K3);
				Tol[Itemindex] = atof(Spec[0].USL[Itemindex]) - atof(Spec[0].LSL[Itemindex]);
				LogStr += CalculatingPercentGRR(MODEEV, NULL, RangeAverage, K1, NULL, NULL, Itemindex, Serialnumber, PercentGRRTester, NULL, &EV);
				LogStr += CalculatingPercentGRR(MODEAV, NULL, XDiff, K2, EV, NULL, Itemindex, Serialnumber, PercentGRRTester, trialmin, &AV);
				LogStr += CalculatingPercentGRR(MODEGRR, NULL, EV, AV, NULL, NULL, Itemindex, Serialnumber, PercentGRRTester, NULL, &GRR);
				LogStr += CalculatingPercentGRR(MODEPV, NULL, Rpart, K3, NULL, NULL, Itemindex, Serialnumber, PercentGRRTester, NULL, &PV);
				LogStr += CalculatingPercentGRR(MODETV, NULL, GRR, PV, NULL, NULL, Itemindex, Serialnumber, PercentGRRTester, NULL, &TV);
				LogStr += CalculatingPercentGRR(MODEPERCENTEV, NULL, EV, Tol[Itemindex] / (6 * atof(Spec[0].TolScale[Itemindex])), NULL, NULL, Itemindex, Serialnumber, PercentGRRTester, NULL, &dresult);
				PercentEV[Itemindex].Format("%.2f", dresult);
				LogStr += CalculatingPercentGRR(MODEPERCENTAV, NULL, AV, Tol[Itemindex] / (6 * atof(Spec[0].TolScale[Itemindex])), NULL, NULL, Itemindex, Serialnumber, PercentGRRTester, NULL, &dresult);
				PercentAV[Itemindex].Format("%.2f", dresult);
				LogStr += CalculatingPercentGRR(MODEPERCENTGRR, NULL, GRR, Tol[Itemindex] / (6 * atof(Spec[0].TolScale[Itemindex])), NULL, NULL, Itemindex, Serialnumber, PercentGRRTester, NULL, &dresult);
				//LogStr += CalculatingPercentGRR(MODEPERCENTGRR, NULL, GRR, TV, NULL, NULL, Itemindex, Serialnumber, PercentGRRTester, NULL, &dresult);
				PercentGRR[Itemindex].Format("%.2f", dresult);
				LogStr += CalculatingPercentGRR(MODEPERCENTPT, NULL, GRR, Tol[Itemindex] / atof(Spec[0].TolScale[Itemindex]), NULL, NULL, Itemindex, Serialnumber, PercentGRRTester, NULL, &dresult);
				if (atof(PercentGRR[Itemindex]) > 30)
					TotalPass = FALSE;
				PercentPartperTester[Itemindex].Format("%.2f", dresult);
				LogStr += CalculatingPercentGRR(MODEPERCENTPV, NULL, PV, Tol[Itemindex], NULL, NULL, Itemindex, Serialnumber, PercentGRRTester, NULL, &dresult);
				PercentPV[Itemindex].Format("%.2f", dresult);
				LogStr += CalculatingPercentGRR(MODENDC, NULL, PV, GRR, NULL, NULL, Itemindex, Serialnumber, PercentGRRTester, NULL, &dresult);
				NDC[Itemindex].Format("%.2f", dresult);
			}

		}
	/*********************************** GRR 결과 파일 생성********************************************************************/
		for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
		{
			if (SCORE1 && atof(PercentGRR[Itemindex]) <= 30)
				temppass = "PASS";
			else if (SCORE2 && atof(ErrorCount[Itemindex]) == 0)
				temppass = "PASS";
			else if (SCORE3 && (atof(MIN[Itemindex]) < atof(Spec[0].LSL[Itemindex])) && (atof(MAX[Itemindex]) < atof(Spec[0].USL[Itemindex])))
				temppass = "PASS";
			else
				temppass = "FAIL";
			Percent_GRR_result += Spec[0].itemname[Itemindex] + "," + PercentEV[Itemindex] + "," + PercentAV[Itemindex] + "," 
									+ PercentPartperTester[Itemindex] + "," + PercentPV[Itemindex] + "," + PercentGRR[Itemindex] + "," 
									+ NDC[Itemindex] + "," + MIN[Itemindex] + "," + MAX[Itemindex] + "," + ErrorCount[Itemindex] + ","
									+ nowtester + "," + temppass + "\n";
			if (temppass == "FAIL")
				testertempresult = FALSE;
			else
				continue;
		}
		Wait(1);
		m_Progress1.SetPos(m_Progress1.GetPos() + 1);
		if (testertempresult == TRUE)
			TesterResultOfPercentGRR[t] = "PASS";
		else
			TesterResultOfPercentGRR[t] = "FAIL";
	}

	result = "";
	WriteFilePath = DirectoryPath + "\\GRR_Result.csv";
	if(TotalPass == TRUE)
		result += "Total Result : PASS \n";
	else
		result += "Total Result : FAIL \n";
	result += "\n";
	
	result += "SW Version : " + unpivot[0].version + "\n";
	result += "Spec Version : " + Spec[0].version + "\n";
	result += "GRR Version : ";
	result += SW_VERSION;
	result += "\n\n";

	result += GoldenGRRpassfailtable;

	result += "\n";
	result += "Item Name,%EV,%AV,%P/T,%PV,%GRR,NDC,MIN,MAX,ErrorCount,Tester,PASS/FAIL\n";
	result += Percent_GRR_result;

	FileWrite.Open(WriteFilePath, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	FileWrite.WriteString(result);
	FileWrite.Close();
	LogStr += result;
	LogStr += LogStrPrinting(MODEINFORM, "Created GRR Result File:" + WriteFilePath + "\n");
	LogStr += LogStrPrinting(MODEINFORM, "Calculating %GRR Values is done...!\n");
	if(TotalPass == TRUE)
	{
		LogStr += LogStrPrinting(MODEINFORM, "********************************************************************************************************\n");
		LogStr += LogStrPrinting(MODEINFORM, "*****************************************Result is \" PASS \"*********************************************\n");
		LogStr += LogStrPrinting(MODEINFORM, "********************************************************************************************************\n");
	}
	else
	{ 
		LogStr += LogStrPrinting(MODEINFORM, "********************************************************************************************************\n");
		LogStr += LogStrPrinting(MODEINFORM, "*****************************************Result is \" FAIL \"*********************************************\n");
		LogStr += LogStrPrinting(MODEINFORM, "********************************************************************************************************\n");
	}
	m_Progress2.SetPos(m_Progress2.GetPos()+1);
	/*********************************** Spec 파일 생성*********************************************************************/
	CString Items = "";
	CString USL = "Upper Limit----->";
	CString LSL = "Lower Limit----->";
	CString ErrorScale = "ErrorScale";
	CString STRMax_LIMIT = "Max_LIMIT";
	CString STRMin_LIMIT = "Min_LIMIT";
	CString tmp;

	for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
	{
		Items += "," + Spec[0].itemname[Itemindex];
		USL += "," + Spec[0].USL[Itemindex] ;
		LSL += "," + Spec[0].LSL[Itemindex] ;
		ErrorScale += "," + Spec[0].ErrorScale[Itemindex] ;
		tmp.Format("%f", (atof(Spec[0].USL[Itemindex]) - atof(Spec[0].LSL[Itemindex])) * atof(Spec[0].ErrorScale[Itemindex]));
		STRMax_LIMIT += "," + tmp;
		tmp.Format("%f", (atof(Spec[0].LSL[Itemindex]) - atof(Spec[0].USL[Itemindex])) * atof(Spec[0].ErrorScale[Itemindex]));
		STRMin_LIMIT += "," + tmp;
	}
	result = Items + "\n" + USL + "\n" + LSL + "\n" + ErrorScale + "\n" + STRMax_LIMIT+ "\n" + STRMin_LIMIT;
	WriteFilePath = DirectoryPath + "\\GRR_Spec.csv";
	FileWrite.Open(WriteFilePath, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	FileWrite.WriteString(result);
	FileWrite.Close();
	LogStr += LogStrPrinting(MODEINFORM, "Created Spec File:" + WriteFilePath + "\n");
	LogStr += LogStrPrinting(MODEINFORM, "The calculation is done...\n");
	m_Progress2.SetPos(m_Progress2.GetPos()+1);
	/****************************************GRR KEY Bin file 생성*************************************************************/

	for (int j = 0; j < testernumber; j++)
	{
		CString GRRkey = "";
		CString WriteFilecsvPath = "";
		CString WriteFilebinPath = "";
		WriteFilecsvPath = DirectoryPath + "\\" + time_current + "_" + Tester[j] + ".csv";
		WriteFilebinPath = WriteFilecsvPath;
		WriteFilebinPath.Replace(".csv", ".bin");

		GRRkey += "TESTERID\t" + Tester[j] + "\n";
		GRRkey += "TOTALTESTER\t";
		for (int i = 0; i < testernumber; i++)
			GRRkey += Tester[i] + ",";
		GRRkey += "\n";
		if (TotalPass == TRUE)
			GRRkey += "RESULT\tPASS\n";
		else
			GRRkey += "RESULT\tFAIL\n";
		GRRkey += "DATADATE\t"+ unpivot[0].time +"\n";
		GRRkey += "REPORTDATE\t" + time_report +"\n";
		GRRkey += "SWVERSION\t" + unpivot[0].version + "\n";
		GRRkey += "PROJECT\t" + unpivot[0].fom +"\n";
		GRRkey += "GRRVERSION\t";
		GRRkey += SW_VERSION;
		GRRkey += "\n";
		GRRkey += "UFPCSERIALNUMBER\t";
		for (int i = 0; i < serialnumber; i++)
			GRRkey += Serialnumber[i] + ",";
		GRRkey += "\n";

		LogStr += LogStrPrinting(MODEINFORM, "Created Log File:" + WriteFilecsvPath + "\n");
		FileWrite.Open(WriteFilecsvPath, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
		FileWrite.WriteString(GRRkey);
		FileWrite.Close();

		BinaryEncoding(LPSTR(LPCTSTR(WriteFilecsvPath)), LPSTR(LPCTSTR(WriteFilebinPath)));
		remove(WriteFilecsvPath);
	}
	/*****************************************LogFile 출력*********************************************************************/
	WriteFilePath = DirectoryPath + "\\GRR_Report.Log";
	LogStr += LogStrPrinting(MODEINFORM, "Created Log File:" + WriteFilePath + "\n");
	FileWrite.Open(WriteFilePath, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	FileWrite.WriteString(LogStr);
	FileWrite.Close();
	
	/*****************************************계산 종료*********************************************************************/
	AfxGetApp()->DoWaitCursor(-1);
	AfxMessageBox("Completed!");

	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/**********************************List Control 1 결과출력**************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	ResultDialog *m_ResultDlg;
	m_ResultDlg = new ResultDialog();
	m_ResultDlg->Create(IDD_DIALOG1, this);
	m_ResultDlg->ShowWindow(SW_SHOW);
	m_ResultDlg->m_DirectoryPath.SetWindowTextA(DirectoryPath);
	m_ResultDlg->m_grrvalue.DeleteAllItems();
	while (m_ResultDlg->m_grrvalue.DeleteColumn(0));

	//Tester로 Column 추가
	m_ResultDlg->m_grrvalue.InsertColumn(0, "Serial Number", LVCFMT_CENTER, 200);
	for (int j = 0; j < testernumber; j++)
	{
		if(Tester[j] == goldentester)
			m_ResultDlg->m_grrvalue.InsertColumn(j + 1, Tester[j] + "*", LVCFMT_CENTER, 80);
		else
			m_ResultDlg->m_grrvalue.InsertColumn(j + 1, Tester[j], LVCFMT_CENTER, 80);
	}

	//Sample별 Row 추가
	for (int i = 0; i < serialnumber; i++)
	{
		m_ResultDlg->m_grrvalue.InsertItem(i, Serialnumber[i]);
	}

	//Test 결과 List CTRL에 채우기
	for (int i = 0; i < serialnumber; i++)
	{
		for (int j = 0; j < testernumber; j++)
		{
			if(GRRpassfail[i + 1][j + 1] == "NA" && S2GRRpassfail[i + 1][j + 1] == "NA" && S3GRRpassfail[i + 1][j + 1] == "NA")
				m_ResultDlg->m_grrvalue.SetItem(i, j + 1, LVIF_TEXT, "NA", NULL, NULL, NULL, NULL);
			else if (GRRpassfail[i + 1][j + 1] == "FAIL" || S2GRRpassfail[i + 1][j + 1] == "FAIL" || S3GRRpassfail[i + 1][j + 1] == "FAIL")
				m_ResultDlg->m_grrvalue.SetItem(i, j + 1, LVIF_TEXT, "FAIL", NULL, NULL, NULL, NULL);
			else
				m_ResultDlg->m_grrvalue.SetItem(i, j + 1, LVIF_TEXT, "PASS", NULL, NULL, NULL, NULL);

		}
	}
	m_ResultDlg->FailItemList = TotalFailItem;
	m_ResultDlg->ChangeColorOfListControl1 = TRUE;
	m_ResultDlg->m_grrvalue.Invalidate(FALSE);

	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/**********************************List Control 2 결과출력**************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	
	m_ResultDlg->m_grrpercent.DeleteAllItems();
	while (m_ResultDlg->m_grrpercent.DeleteColumn(0));

	//Column 추가
	m_ResultDlg->m_grrpercent.InsertColumn(0, "Item Name", LVCFMT_CENTER, 180);
	m_ResultDlg->m_grrpercent.InsertColumn(1, "Status", LVCFMT_CENTER, 80);
	m_ResultDlg->m_grrpercent.InsertColumn(2, "%EV", LVCFMT_CENTER, 80);
	m_ResultDlg->m_grrpercent.InsertColumn(3, "%AV", LVCFMT_CENTER, 80);
	m_ResultDlg->m_grrpercent.InsertColumn(4, "%GRR", LVCFMT_CENTER, 80);
	m_ResultDlg->m_grrpercent.InsertColumn(5, "MIN", LVCFMT_CENTER, 80);
	m_ResultDlg->m_grrpercent.InsertColumn(6, "MAX", LVCFMT_CENTER, 80);
	m_ResultDlg->m_grrpercent.InsertColumn(7, "ErrorCount", LVCFMT_CENTER, 80);
	m_ResultDlg->m_ComboTester.ResetContent();
#ifdef SFT_DISTRIBUTE
	if (SFT_TEST == TRUE)
	{
		for (int j = 0; j < testernumber; j++)
		{
			m_ResultDlg->m_ComboTester.AddString(Tester[j]);
		}
		m_ResultDlg->m_ComboTester.SetCurSel(testernumber - 1);
	}
	else
#endif // SFT_DISTRIBUTE
		m_ResultDlg->m_ComboTester.ShowWindow(SW_HIDE);
	//Item별 GRR 값 추가할때
	int Rowindex = 0;
	for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
	{
		m_ResultDlg->m_grrpercent.InsertItem(Rowindex, Spec[0].itemname[Itemindex]);
		m_ResultDlg->m_grrpercent.SetItem(Rowindex, 2, LVIF_TEXT, PercentEV[Itemindex], NULL, NULL, NULL, NULL);
		m_ResultDlg->m_grrpercent.SetItem(Rowindex, 3, LVIF_TEXT, PercentAV[Itemindex], NULL, NULL, NULL, NULL);
		m_ResultDlg->m_grrpercent.SetItem(Rowindex, 4, LVIF_TEXT, PercentGRR[Itemindex], NULL, NULL, NULL, NULL);
		m_ResultDlg->m_grrpercent.SetItem(Rowindex, 5, LVIF_TEXT, MIN[Itemindex], NULL, NULL, NULL, NULL);
		m_ResultDlg->m_grrpercent.SetItem(Rowindex, 6, LVIF_TEXT, MAX[Itemindex], NULL, NULL, NULL, NULL);
		m_ResultDlg->m_grrpercent.SetItem(Rowindex, 7, LVIF_TEXT, ErrorCount[Itemindex], NULL, NULL, NULL, NULL);
		if(atof(PercentGRR[Itemindex]) <= 30 && SCORE1)
			m_ResultDlg->m_grrpercent.SetItem(Rowindex, 1, LVIF_TEXT, "PASS", NULL, NULL, NULL, NULL);
		else if (atof(ErrorCount[Itemindex]) == 0 && SCORE2)
			m_ResultDlg->m_grrpercent.SetItem(Rowindex, 1, LVIF_TEXT, "PASS", NULL, NULL, NULL, NULL);
		else if (atof(MIN[Itemindex]) < atof(Spec[0].LSL[Itemindex]) && atof(MAX[Itemindex]) < atof(Spec[0].USL[Itemindex]) && SCORE3)
			m_ResultDlg->m_grrpercent.SetItem(Rowindex, 1, LVIF_TEXT, "PASS", NULL, NULL, NULL, NULL);
		else
			m_ResultDlg->m_grrpercent.SetItem(Rowindex, 1, LVIF_TEXT, "FAIL", NULL, NULL, NULL, NULL);
	}	
	m_ResultDlg->ChangeColorOfListControl2 = TRUE;
	m_ResultDlg->m_grrpercent.Invalidate(FALSE);

	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/**********************************List Control 3 결과출력**************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	m_ResultDlg->m_summaryList.DeleteAllItems();
	while (m_ResultDlg->m_summaryList.DeleteColumn(0));

	//Tester로 Column 추가
	m_ResultDlg->m_summaryList.InsertColumn(0, "", LVCFMT_CENTER, 5);
	for (int j = 0; j < testernumber; j++)
	{
		if (Tester[j] == goldentester)
			m_ResultDlg->m_summaryList.InsertColumn(j + 1, Tester[j] + "*", LVCFMT_CENTER, 80);
		else
			m_ResultDlg->m_summaryList.InsertColumn(j + 1, Tester[j], LVCFMT_CENTER, 80);
	}
	//Row에 Result 글자 추가
	m_ResultDlg->m_summaryList.InsertItem(0, "");

	//Test 결과 List CTRL에 채우기
	for (int j = 0; j < testernumber; j++)
	{
		BOOL testerpassOfGRRValue = TRUE;
		CString testerpassOfPercentGRR = "";
		for (int i = 0; i < serialnumber; i++)
		{
			if (GRRpassfail[i + 1][j + 1] == "NA" && S2GRRpassfail[i + 1][j + 1] == "NA" && S3GRRpassfail[i + 1][j + 1] == "NA")
				testerpassOfGRRValue = FALSE;
			else if (GRRpassfail[i + 1][j + 1] == "FAIL" || S2GRRpassfail[i + 1][j + 1] == "FAIL" || S3GRRpassfail[i + 1][j + 1] == "FAIL")
				testerpassOfGRRValue = FALSE;
			else
				continue;
		}
#ifdef SFT_DISTRIBUTE
		if (SFT_TEST == TRUE)
			testerpassOfPercentGRR = TesterResultOfPercentGRR[j];
		else
#endif // SFT_DISTRIBUTE
			testerpassOfPercentGRR = TesterResultOfPercentGRR[0];
		
		if (testerpassOfGRRValue == TRUE && testerpassOfPercentGRR == "PASS")
			m_ResultDlg->m_summaryList.SetItem(0, j + 1, LVIF_TEXT, "PASS", NULL, NULL, NULL, NULL);
		else
			m_ResultDlg->m_summaryList.SetItem(0, j + 1, LVIF_TEXT, "FAIL", NULL, NULL, NULL, NULL);
	}
	m_ResultDlg->ChangeColorOfListControl3 = TRUE;

	if(TotalPass == TRUE)
		m_ResultDlg->m_TotalPass.SetWindowTextA("PASS");
	else
		m_ResultDlg->m_TotalPass.SetWindowTextA("FAIL");
}



//저장파일 경로 자동 지정 기능
void CSDC_GRRDlg::SetSavePath(CString strsavePath)
{
	DWORD ret = GetFileAttributes(strsavePath);
	if (ret != INVALID_FILE_ATTRIBUTES)
	{
			strsavePath = strsavePath.Left(strsavePath.ReverseFind('\\'));
			m_savepath.SetWindowTextA(strsavePath);
	}
}

//Check Items Button
void CSDC_GRRDlg::OnBnClickedButton7()
{
	CString LogStr = "";
	m_listctrl.DeleteAllItems();
	while(m_listctrl.DeleteColumn(0));

	ItemValue check[MAXDATAQUANTITY] = {};
	SpecValue Spec[1] = {};

	int Datanumber = 0;
	int mode = 0;  //아이템 이름과 value는 필요하지 않기에 0로 지정
	LogStr = LogStrPrinting(MODEINFORM, "Data File Scanning...\r\n");
	m_Progress1.SetRange(0, 0);
	m_Progress1.SetPos(0);
	if (FileScan(check, Spec, &Datanumber, &mode, &LogStr) != 0)
	{
		for (int i = 0; i < Datanumber; i++)
			check[i].trial = 0;
	}
	
	LogPrintinEditControl(LogStr);
	CString Serialnumber[100] = {};
	CString Tester[100] = {};
	bool overlap = FALSE;
	int testernumber = 0;
	int serialnumber = 0;

	//중복데이터 제거
	for (int i = 0; i < Datanumber; i++)
	{
		for (int index = 0; index <= testernumber; index++)
		{
			if (Tester[index] == check[i].tester)
				overlap = TRUE;
		}
		if (overlap == TRUE)
		{
			overlap = FALSE;
		}
		else
		{
			Tester[testernumber] = check[i].tester;
			testernumber++;
		}

		for (int index = 0; index <= serialnumber; index++)
		{
			if (Serialnumber[index] == check[i].serialnumber)
				overlap = TRUE;
		}
		if (overlap == TRUE)
		{
			overlap = FALSE;
		}
		else
		{
			Serialnumber[serialnumber] = check[i].serialnumber;
			serialnumber++;
		}
	}

	//Tester로 Column 추가
	m_listctrl.InsertColumn(0, "Serial Number", LVCFMT_LEFT, 200);
	for (int i = 0; i < testernumber; i++)
	{
		m_listctrl.InsertColumn(i+1,Tester[i],LVCFMT_CENTER, 80);
	}

	//SN으로 item 추가
	for (int i = 0; i < serialnumber; i++)
	{
		m_listctrl.InsertItem(i,Serialnumber[i]);
	}

	//각 SN, Tester당 trial 횟수 구하기
	int trial_maxs[100][100] = { 0 };
	for (int i=0; i< serialnumber; i++)
	{
		for (int j = 0; j < testernumber; j++)
		{
			for (int k = 0; k < Datanumber; k++)
			{
				if (Serialnumber[i] == check[k].serialnumber && Tester[j] == check[k].tester)
				{
					trial_maxs[i][j] = check[k].trial;
				}
			}
		}
	}

	CString strtrial = "";
	for (int i = 0; i< serialnumber; i++)
	{
		for (int j = 0; j < testernumber; j++)
		{
			strtrial.Format("%d", trial_maxs[i][j]);
			m_listctrl.SetItem(i, j + 1, LVIF_TEXT, strtrial,NULL,NULL,NULL,NULL);
		}
	}
	TrialNumberChange();
}

//선택된 SerialNumber 지우기 버튼
void CSDC_GRRDlg::OnBnClickedButton8()
{
	POSITION pos = m_listctrl.GetFirstSelectedItemPosition(); // 선택된 첫 번째 위치를 얻어 와서,
	while (pos != NULL)
	{
		int nItem = m_listctrl.GetNextSelectedItem(pos); // 그 위치에 해당하는 item의 index 를 얻고,
		m_listctrl.DeleteItem(nItem); // 그 item 을 지운다.
		pos = m_listctrl.GetFirstSelectedItemPosition(); // 선택된 첫번째 위치를 다시 얻어 온다.
	}
	TrialNumberChange();
}

//csv파일에서 데이터 가져오는 함수
int CSDC_GRRDlg::FileScan(ItemValue unpivot[], SpecValue Spec[], int *Datanumber, int *mode, CString *Log)
{
	CStdioFile FileRead;
	CString ReadFilePath = "";
	int index = 0;
	int filenum = 0;
	filenum = m_filelist.GetCount();

	//Information 추출

	CString tmp;
	CString str;

	BasicInformation temp;

	CString SpecVersion[MAXSAMPLESIZE] = {};
	CString itemnameFOM = "";
	int specversionindex = 0;
	int errorcodecomma = 0;
	int timecomma = 0;
	int testercomma = 0;
	int serialnumbercomma = 0;
	int projnamecomma = 0;
	int totalcommanumber = 0;
	int unpivotnumber = 0;
	int trial = 1;
	bool different = TRUE;

	CHAR inbuffer[20] = "";
	CString iniPath = "";
	CString Serialnumber = "";
	CString TesterID = "";
	CString Time = "";
	CString ErrorCode = "";
	CString Proj_name = "";
	CString ErrorRate = "";

	iniPath = ".\\Information.ini";
	if (PathFileExists(iniPath))
	{
	}
	else
		*Log = LogStrPrinting(MODEWARNING, "Can not find ini file! We set the values as default\n");

	GetPrivateProfileString("Information", "Serialnumber", "SERIALNUMBER", inbuffer, sizeof(inbuffer), iniPath);
	Serialnumber = inbuffer;
	GetPrivateProfileString("Information", "TesterID", "TESTERID", inbuffer, sizeof(inbuffer), iniPath);
	TesterID = inbuffer;
	GetPrivateProfileString("Information", "Time", "STOPTIME", inbuffer, sizeof(inbuffer), iniPath);
	Time = inbuffer;
	GetPrivateProfileString("Information", "ErrorCode", "ERRCODE", inbuffer, sizeof(inbuffer), iniPath);
	ErrorCode = inbuffer;
	GetPrivateProfileString("Information", "Proj_name", "PROJ_NAME", inbuffer, sizeof(inbuffer), iniPath);
	Proj_name= inbuffer;
	GetPrivateProfileString("Information", "ErrorRate", "0.35", inbuffer, sizeof(inbuffer), iniPath);
	ErrorRate = inbuffer;

	while (index != filenum)
	{
		double errorcount = 0;
		double passcount = 0;
		double errorrate = 0;
		CString fom = "";
		m_filelist.GetText(index, ReadFilePath);
		*Log += LogStrPrinting(MODEINFORM, "Opening File : " + ReadFilePath + "\n");
		if (!FileRead.Open(ReadFilePath, CFile::modeRead | CFile::typeText))
		{
			ERRORALERT;
			*Log = LogStrPrinting(MODEWARNING, "The data file is not exist or already opened!\n");
			break;
		}
		else
		{
			int row = 0;
			while (FileRead.ReadString(tmp))
			{
				if (tmp.Find("SerialNumber,") != -1 || tmp.Find("SERIALNUMBER,") != -1)
				{
					tmp.MakeUpper();
					str = tmp;
					str = tmp.Left(tmp.Find(Serialnumber));
					serialnumbercomma = str.Remove(',');
					str = tmp.Left(tmp.Find(TesterID));
					testercomma = str.Remove(',');
					str = tmp.Left(tmp.Find(Time));
					timecomma = str.Remove(',');
					str = tmp.Left(tmp.Find(ErrorCode));
					errorcodecomma = str.Remove(',');
					str = tmp.Left(tmp.Find(Proj_name));
					projnamecomma = str.Remove(',');
					str = tmp;
					itemnameFOM = tmp;
					totalcommanumber = str.Remove(',') +1 ;
					if (*mode == 1)
					{
						CString tempname = "";
						int totalitemnumber = 0;
						int Item_Count = 0;
						while (totalitemnumber < Spec[0].totalitemnumber)
						{
							Item_Count = itemnameFOM.Find(Spec[0].itemname[totalitemnumber]);
							if (Item_Count == -1)
							{
								ERRORALERT;
								*Log = LogStrPrinting(MODEWARNING, "The item \"" + Spec[0].itemname[totalitemnumber] +  "\" is not exist in the Data file. Please the Data file or Spec file\n");
								return 1;
								continue;
							}
							else
							{
								tempname = itemnameFOM.Left(Item_Count);
								Spec[0].commanumber[totalitemnumber] = tempname.Remove(',');
								totalitemnumber++;
							}
						}
					}
				}
				else if (tmp.Find("Upper Limit----->") != -1 || tmp.Find("Lower Limit----->") != -1)
					continue;
				else if (tmp.Find("ETY_TEST,") != -1 || tmp.Find("SFT_TEST,") != -1 || tmp.Find("R-735,") != -1 || tmp.Find("D877,") != -1 || tmp.Find("D879,") != -1)
				{
					if (tmp.Find("ETY_TEST,") != -1)
						fom = "ETY_TEST";
					else if (tmp.Find("SFT_TEST,") != -1)
						fom = "SFT_TEST";
					else if (tmp.Find("R-735,") != -1)
						fom = "R_735";
					else if (tmp.Find("D877,") != -1)
						fom = "D877";
					else if (tmp.Find("D879,") != -1)
						fom = "D879";
					tmp.Remove(',');
					SpecVersion[specversionindex] = tmp;
					if (specversionindex > 0)
					{
						if (SpecVersion[specversionindex] != SpecVersion[specversionindex - 1])
						{
							CString strindex = "";
							strindex.Format("%i", index + 1);
							ERRORALERT;
							*Log = LogStrPrinting(MODEWARNING, "The spec version of data file No." + strindex + " is different. Please input the same spec version data.\n");
							specversionindex++;
							break;
						}
					}
					specversionindex++;
				}
				else if (tmp.Find("NASCA") != -1)
				{
					CString Nascafilenum = "";
					Nascafilenum.Format("%d", index + 1);
					ERRORALERT;
					*Log = LogStrPrinting(MODEWARNING, "The data file No." + Nascafilenum + " is covered by NASCA. Please remove NASCA of this file.\n");
					break;
				}
				else
				{
					row++;
					str = tmp;
					for (int i = 0; i < errorcodecomma; i++)
						str = str.Mid(str.Find(",") + 1);
					temp.errorcode = str.Left(str.Find(","));
					if (temp.errorcode == "0")
					{
						passcount++;
						str = tmp;
						for (int i = 0; i < serialnumbercomma; i++)
							str = str.Mid(str.Find(",") + 1);
						temp.serialnumber = str.Left(str.Find(","));

						str = tmp;
						for (int j = 0; j < timecomma; j++)
							str = str.Mid(str.Find(",") + 1);
						temp.time = str.Left(str.Find(","));

						if (temp.time.Remove(':') < 2)
						{
							CString strindex = "";
							CString strRow = "";
							strindex.Format("%i",index+1);
							strRow.Format("%i", row);
							ERRORALERT;
							*Log = LogStrPrinting(MODEWARNING, "The time value of the file No." + strindex + "~" + strRow +" row is damaged. \nPlease input the original file.\n");
							break;
						}

						str = tmp;
						for (int j = 0; j < testercomma; j++)
							str = str.Mid(str.Find(",") + 1);
						temp.tester = str.Left(str.Find(","));

						str = tmp;
						for (int j = 0; j < projnamecomma; j++)
							str = str.Mid(str.Find(",") + 1);
						temp.proj_name = str.Left(str.Find(","));

						trial = 1;

						for (int a = 0; a <= *Datanumber; a++)
						{
							if (unpivot[a].serialnumber == temp.serialnumber && unpivot[a].time == temp.time && unpivot[a].tester == temp.tester)
							{
								different = FALSE;
								break;
							}
							else if (unpivot[a].serialnumber == temp.serialnumber && unpivot[a].time != temp.time && unpivot[a].tester == temp.tester)
							{
								trial++;
							}
							else
								trial = trial;
						}

						if (different == FALSE)
						{
							different = TRUE;
							continue;
						}
						else
						{
							unpivot[*Datanumber].serialnumber = temp.serialnumber;
							unpivot[*Datanumber].time = temp.time;
							unpivot[*Datanumber].tester = temp.tester;
							unpivot[*Datanumber].trial = trial;
							if (*mode == 1)
							{
								/////CHECK_SUM 확인(20.06.17)//////
								char inputStr[100] = { NULL };
								UINT8 Checksum = 0;
								CString result = "";

								str = tmp;
								str.Replace("\t", "");
								str.Replace("\r\n", "");
								str.Replace("\r", "");

								while (str.Find(",") != -1)
								{
									strcpy_s(inputStr, str.Left(str.Find(",")));
									str = str.Mid(str.Find(",") + 1);
									for (int i = 0; i<100; i++)
									{
										Checksum += inputStr[i];
										inputStr[i] = NULL;
									}
								}
								result.Format("0x%02X", Checksum);
								if (str != result && AdministratorMode == FALSE)
								{
									CString strindex = "";
									CString strRow = "";
									strindex.Format("%i", index + 1);
									strRow.Format("%i", row);
									ERRORALERT;
									*Log = LogStrPrinting(MODEWARNING, "The data of file No." + strindex + "~" + strRow +" row is damaged. \nPlease check that the data value is changed.\n");
									return 1;
									continue;
								}
								/////////////////////////////////
								int specitemcount = 0;
								int commacount = 0;
								CString itemname = tmp;
								while (commacount < totalcommanumber)
								{
									for(int i=0; i<Spec[0].totalitemnumber; i++)
									{
										if (commacount == Spec[0].commanumber[i])
										{
											unpivot[*Datanumber].value[i] = itemname.Left(itemname.Find(","));
											specitemcount++;
											break;
										}
									}
									itemname = itemname.Mid(itemname.Find(",") + 1);
									commacount++;
								}
								/*
								int specitemcount = 0;
								int commacount = 0;
								CString itemname = tmp;
								while(commacount < totalcommanumber)
								{
									if (commacount == Spec[0].commanumber[specitemcount])
									{
										unpivot[*Datanumber].value[specitemcount] = itemname.Left(itemname.Find(","));
										specitemcount++;
									}
									itemname = itemname.Mid(itemname.Find(",")+1);
									commacount++;
								}
								*/
								unpivot[*Datanumber].fom = "//" + fom + "_" + temp.proj_name;
								unpivot[*Datanumber].version = SpecVersion[0];
							}
							*Datanumber = *Datanumber + 1;
							m_Progress1.SetPos(m_Progress1.GetPos() + 1);
							Wait(1);
						}
					}
					else
					{
						errorcount++;
					}
				}
			}
			FileRead.Close();
			
			errorrate = errorcount / (errorcount + passcount);
			if ( errorrate > atof(ErrorRate))
			{
				CString strerrorrate = "";
				CString strindex = "";
				strindex.Format("%i", index + 1);
				strerrorrate.Format("%f",errorrate *100);
				ERRORALERT;
				*Log = LogStrPrinting(MODEWARNING, "The error rate of No." + strindex + "file is too high(" + strerrorrate +  "%). Please check the file .\n");
				return 1;
			}
			index++;
		}
	}
	return 0;
}

int CSDC_GRRDlg::SpecScan(SpecValue Spec[], int *Datanumber, CString *Log)
{
	CStdioFile FileRead;
	CString binPath = "";
	CString csvPath = "";

	//Information 추출
	CString tmp = "";
	CString model_name = "";
	CString specversion = "";

	m_Progress1.SetRange(0, 100);
	m_Progress1.SetPos(0);

	m_specpath.GetWindowTextA(binPath);
	*Log += LogStrPrinting(MODEINFORM, "Opening File : " + binPath + "\n");

	char* inputpath = LPSTR(LPCTSTR(binPath));
	m_specpath.GetWindowTextA(csvPath);
	csvPath.Replace(".bin", ".csv");
	char* outputpath = LPSTR(LPCTSTR(csvPath));

	BinaryDecoding(inputpath, outputpath);

	if (!FileRead.Open(outputpath, CFile::modeRead | CFile::typeText))
	{
		//스펙 없을 시 시그마 공식으로 계산할꺼 생각하자.
		ERRORALERT;
		*Log += LogStrPrinting(MODEWARNING, "The spec file is not exist or already opened!!\n");
		return 1;
	}
	else
	{
		int count = 0;
		while (FileRead.ReadString(tmp))
		{
			if (tmp.Find("//") != -1)
			{
				tmp.Replace(",","");
				tmp.Replace("\t", "");
				if (tmp.Find("_") != -1)
					model_name = tmp;
				else
					specversion = tmp;
			}
			else
			{
				//sscanf(tmp,"%s\t%s\t%s\t%s\t%s", Item1, Item2, Item3, Item4, Item5);
				Spec[0].itemname[count] = tmp.Left(tmp.Find("\t"));
				tmp = tmp.Mid(tmp.Find("\t")+1);
				Spec[0].USL[count] = tmp.Left(tmp.Find("\t"));
				tmp = tmp.Mid(tmp.Find("\t") + 1);
				Spec[0].LSL[count] = tmp.Left(tmp.Find("\t"));
				tmp = tmp.Mid(tmp.Find("\t") + 1);
				Spec[0].Score[count] = tmp.Left(tmp.Find("\t"));
				tmp = tmp.Mid(tmp.Find("\t") + 1);
				Spec[0].ErrorScale[count] = tmp;
				tmp = tmp.Mid(tmp.Find("\t") + 1);
				Spec[0].TolScale[count] = tmp;
				count++;
			}
		}
		Spec[0].totalitemnumber = count;
		Spec[0].fom = model_name;
		Spec[0].version = specversion;
		FileRead.Close();
	}
	DeleteFileA(outputpath);
	return 0;
}

//Spec file load 버튼
void CSDC_GRRDlg::OnBnClickedButton9()
{
	CString PathRead = "";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, "BIN Files(*.bin)|*.bin|All Files(*.*)|*.*|");
	if (dlg.DoModal() == IDOK)
		PathRead = dlg.GetPathName();

	m_specpath.SetWindowTextA(PathRead);
}

//계산결과파일 생성하는 함수
void CSDC_GRRDlg::CreateReport(ItemValue unpivotdata[],SpecValue Spec[], CString kind, int Datanumber, CString Path)
{
	CString Items = ",";

	//헤더 만들기
	for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
	{
		Items += Spec[0].itemname[Itemindex] + ",";
	}
	//파일 만들기
	for (int k = 0; k < Datanumber; k++)
	{
		CString result = "";
		CString tmp1 = "";
		CString tmp2 = "";
		CString values = "";
		CStdioFile FileWrite;
		CString testername = "";
		CString WriteFilePath = Path;

		//데이터가 비어있으면 출력 X
		if (unpivotdata[k].serialnumber == "" && unpivotdata[k].tester == "")
			continue;

		values += unpivotdata[k].serialnumber + ",";
		testername = unpivotdata[k].tester;
		//아이템 값 만들기
		for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
			values += unpivotdata[k].value[Itemindex] + ",";


		//테스터기별 폴더만들기
		WriteFilePath += "\\" + testername;
		if (GetFileAttributes(WriteFilePath) == 0xFFFFFFFF) 
		{
			CreateDirectory(WriteFilePath, NULL);
		}

		//파일 쌓기
		WriteFilePath += "\\" + testername + "_" + kind + ".csv";
		if (!FileWrite.Open(WriteFilePath, CFile::modeReadWrite | CFile::modeNoTruncate))
		{
			result += Items + "\n" + values;
			FileWrite.Open(WriteFilePath, CFile::modeCreate | CFile::modeWrite);
			FileWrite.WriteString(result);
			FileWrite.Close();
			LogStrPrinting(MODEINFORM, "Created CSV File:" + WriteFilePath + "\n");
		}
		else
		{
			while (FileWrite.ReadString(tmp2))
			{
				result += tmp2 + "\n";
			}
			FileWrite.Close();

			result += values;
			FileWrite.Open(WriteFilePath, CFile::modeWrite | CFile::modeNoTruncate);
			FileWrite.WriteString(result);
			FileWrite.Close();		
		}
	}
	
}


void CSDC_GRRDlg::LogPrintinEditControl(CString str)
{
	str.Replace("\r\n", "\n");
	str.Replace("\n", "\r\n");
	m_logresult.SetSel(m_logresult.GetWindowTextLength(), m_logresult.GetWindowTextLength());
	m_logresult.ReplaceSel(str);
}

/*

void CSDC_GRRDlg::SDCLogger(CString Lv1, CString Lv2, CString str)
{
	CString strLog;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str.Replace("\r\n", "\n");
	str.Replace("\n", "\r\n");

	strLog.Format("%04d-%02d-%02d_%02d:%02d:%02d.%03d %s %s %s", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, Lv1, Lv2, str);

	m_edit_LogDetail.SetSel(m_LogDetaildlg->m_edit_LogDetail.GetWindowTextLength(), m_LogDetaildlg->m_edit_LogDetail.GetWindowTextLength());
	m_edit_LogDetail.ReplaceSel(strLog);
}
*/

CString CSDC_GRRDlg::LogStrPrinting(int Mode, CString PrintingStr)
{
	CString strLog;
	CString Lv1;
	SYSTEMTIME st;
	GetLocalTime(&st);

	//PrintingStr.Replace("\r\n", "\n");
	//PrintingStr.Replace("\n", "\r\n");

	switch (Mode)
	{
	case MODEINFORM:
		Lv1 = "[Inform]";
		strLog.Format("%04d-%02d-%02d_%02d:%02d:%02d.%03d %s %s", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, Lv1, PrintingStr);
		break;
	case MODEWARNING:
		Lv1 = "[Warning]";
		strLog.Format("%04d-%02d-%02d_%02d:%02d:%02d.%03d %s %s", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, Lv1, PrintingStr);
		break;
	case MODERESULT:
		strLog.Format("%s", PrintingStr);
		break;
	}
	LogPrintinEditControl(strLog);

	return strLog;
}

void Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

BOOL CSDC_GRRDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			return TRUE;
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

//세팅 버튼
void CSDC_GRRDlg::OnBnClickedButtonSetting()
{
	CPropertySetting dlg;
	dlg.DoModal();
}


void CSDC_GRRDlg::TrialNumberChange(void)
{
	CString strtrial = "";
	int serialnumber = 0;
	CHeaderCtrl  *pHead = NULL;
	int	nRowCnt = 0;
	int minimum = 0;

	pHead = m_listctrl.GetHeaderCtrl();
	nRowCnt = pHead->GetItemCount();
	serialnumber = m_listctrl.GetItemCount();

	for (int i = 0; i< serialnumber; i++)
	{
		for (int j = 0; j < nRowCnt - 1; j++)
		{
			if (i == 0 && j == 0)
				minimum = atoi(m_listctrl.GetItemText(i, j + 1));
			else if (minimum >atoi(m_listctrl.GetItemText(i, j + 1)))
				minimum = atoi(m_listctrl.GetItemText(i, j + 1));
		}
	}
	strtrial.Format("%d", minimum);
	m_trialnumber.SetWindowTextA(strtrial);
}
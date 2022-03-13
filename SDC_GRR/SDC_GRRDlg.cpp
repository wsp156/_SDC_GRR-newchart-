
// SDC_GRRDlg.cpp : ���� ����
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

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CSDC_GRRDlg ��ȭ ����


IMPLEMENT_DYNAMIC(CSDC_GRRDlg, CDialogEx);

CSDC_GRRDlg::CSDC_GRRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SDC_GRR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CSDC_GRRDlg::~CSDC_GRRDlg()
{
	// �� ��ȭ ���ڿ� ���� �ڵ�ȭ ���Ͻð� ���� ��� �� ��ȭ ���ڿ� ����
	//  �Ĺ� �����͸� NULL�� �����Ͽ�
	//  ��ȭ ���ڰ� �����Ǿ����� �� �� �ְ� �մϴ�.
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


// CSDC_GRRDlg �޽��� ó����

BOOL CSDC_GRRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowTextA(SW_VERSION);
	m_listctrl .SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSDC_GRRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSDC_GRRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ��Ʈ�ѷ����� �ش� ��ü �� �ϳ��� ��� ����ϰ� ���� ���
//  ����ڰ� UI�� ���� �� �ڵ�ȭ ������ �����ϸ� �� �˴ϴ�.  �̵�
//  �޽��� ó����� ���Ͻð� ���� ��� ���� ��� UI�� ��������,
//  UI�� ǥ�õ��� �ʾƵ� ��ȭ ���ڴ�
//  ���� �Ӵϴ�.

void CSDC_GRRDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CSDC_GRRDlg::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	//CDialogEx::OnOK();
}


void CSDC_GRRDlg::OnCancel()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDialogEx::OnCancel();
}

BOOL CSDC_GRRDlg::CanExit()
{
	// ���Ͻ� ��ü�� ��� ���� ������ �ڵ�ȭ ��Ʈ�ѷ�������
	//  �� ���� ���α׷��� ��� ����մϴ�.  ��ȭ ���ڴ� ���� ������
	//  �ش� UI�� ����ϴ�.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

// ���� ������ �߰� ��ư
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


// ���� ������ �߰� ��ư
void CSDC_GRRDlg::OnBnClickedButton2()
{
	CString strInitPath = ".\\";
	CString strFolderPath;

	// ���� ���� ���̾�α�
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

// ���� ������ ���� ��ư
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


// ��ü ���� ��ư
void CSDC_GRRDlg::OnBnClickedButton4()
{
	m_filelist.ResetContent();
	ShowFileNum();
}

//������ ���� ��ư
void CSDC_GRRDlg::OnBnClickedButton5()
{
	CString strInitPath = ".\\";

	// ���� ���� ���̾�α�
	CFolderPickerDialog Picker(strInitPath, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, NULL, 0);
	if (Picker.DoModal() == IDOK)
	{
		CString strPath = Picker.GetPathName();
		m_savepath.SetWindowTextA(strPath);
	}
}
//���� ���� ��Ÿ���� �Լ�
void CSDC_GRRDlg::ShowFileNum()
{
	CString filenum;
	filenum.Format("%d", m_filelist.GetCount());
	m_filenum.SetWindowTextA(filenum);
}

//���� �� ���ϵ� �ҷ�����
void CSDC_GRRDlg::GetFileList(CString strFolder)
{
	CFileFind file;
	BOOL b = file.FindFile(strFolder + "\\*.*");  // CString strMusicFilter = ".MP3.OGG.WMA.WAV";   // ���͸� �ϰ� ������ �̷��� ���� ��
	CString strFolderItem, strFileExt, strTempString;
	while (b)
	{
		b = file.FindNextFile();
		if (file.IsDirectory() && !file.IsDots())   // ���丮 �߽߰� 
		{
			strFolderItem = file.GetFilePath();
			GetFileList(strFolderItem);      // ���������� �˻��ϱ� ���� ���ȣ�� �߻�  
		}
		strFolderItem = file.GetFilePath();

		strFileExt = strFolderItem.Mid(strFolderItem.ReverseFind('.'));  // Ȯ���ڸ� �����Ѵ�. 
		if (!file.IsDots())         // ���� Ž�� ���� ���ǿ����� �ش� StringList�� �߰�
		{
			strFileExt.MakeUpper();       // strFileExt ���� Ȯ���� (.EXE ����) �� ����. ������ �빮��ȭ ��
			if (file.IsDirectory())
				continue;    // ������ ���� ���� ������ �ȵ� 
			if (strFolderItem.Find(".csv") != -1)
				m_filelist.AddString(strFolderItem);
		}
	}
}

//���ν�ũ�� ����� �Լ�
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
//�巡�׾ص��
void CSDC_GRRDlg::OnDropFiles(HDROP hDropInfo)
{
	UINT i = 0;    //Drag&Drop�� ����,������ ��������
				   //��ӵ� ������ ����
	UINT uCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char buffer[400];  //Drag&Drop�� ����,������ ������ ����

	for (i = 0; i < uCount; i++)
	{
		// ������ ��� ����
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


//GRR ��ư
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
	/*************************************��� ���� ����****************************************************/
	CStdioFile FileWrite;
	CString WriteFilePath = "";

	//�ð��� ���ϸ� �߰�
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


	/*****************************GRR ����!**************************************************************/
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
	int mode = 1;  //������ �̸��� value ��� �ʿ��ϱ⿡ 1�� ����	
	BOOL SFT_TEST = FALSE;

	/*******************************Trial number ���ϱ�********************************************************/
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
	/************************List Contorl Item�� �ִ� Serialnumber List ���ϱ�*******************************/
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
	/************************Coulumn�� �ִ� Tester List ���ϱ�*********************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Checking Tester List...\n");
	LVCOLUMN ss;    //��������
	char temparary[256] = {};
	ss.mask = LVCF_TEXT | LVCF_WIDTH; //����ü �ʱ�ȭ
	ss.pszText = temparary;//����ü�� ���ڿ� �ʱ�ȭ
	ss.cchTextMax = 256;//�ִ����
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

	/*****************************�������� ��ĵ�ؼ� ������ ��������**********************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Spec File Scanning...\n");
	if (SpecScan(Spec, &Datanumber, &LogStr) != 0)
		TotalPass = FALSE;
	m_Progress2.SetPos(m_Progress2.GetPos() + 1);
	if (Spec[0].totalitemnumber == 0)
		return;
	/*****************************���������� ��ĵ�ؼ� ������ ��������********************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Data File Scanning...\n");
	m_Progress1.SetRange(0, trialmin * serialnumber * testernumber);
	m_Progress1.SetPos(0);
	if (FileScan(unpivot, Spec, &Datanumber, &mode, &LogStr) != 0)
		TotalPass = FALSE;
	
	m_Progress2.SetPos(m_Progress2.GetPos()+1);
	/*******************������ ���ϰ� ���� ���� FOM ���Ͽ� �𵨰� �׽������� Ȯ��*****************************/
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
	/****************************���⼭���� Golden GRR Value�� ���� ���***********************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Start to calculate Golden GRR Values...\n");
	/************************�� ��� Tester��, Sample �� ���, std ���ϱ�**************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Calculating \"Average\" and \"Standard deviation\" for each sample and tester...\n");
	ItemValue unpivot_average[MAXDATAQUANTITY] = {};
	ItemValue unpivot_std[MAXDATAQUANTITY] = {};
	LogStr += CalculateUnpivotAverageStd(unpivot, Spec, Serialnumber, Tester, Datanumber, trialmin, unpivot_average, unpivot_std);
	CreateReport(unpivot_average, Spec, "Average", Datanumber, WriteFilePath);
	CreateReport(unpivot_std, Spec, "Std", Datanumber, WriteFilePath);
	m_Progress2.SetPos(m_Progress2.GetPos()+1);

	/************************�� ��� Tester��, Sample �� median, min, max ���ϱ�**************************************************/
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
	/****************************��� �׽��� �������ų� �����ϱ�********************************************************/
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
	/****************************GoldenTester Median �� ��������********************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Extracting \"the golden tester's Median Value\"...\n");
	ItemValue unpivot_median_golden[MAXDATAQUANTITY] = {};
	LogStr += CalculateGoldenMedian(unpivot_median, Spec, Serialnumber, Tester, Datanumber, goldentester, unpivot_median_golden);
	m_Progress2.SetPos(m_Progress2.GetPos()+1);
	/******************************* Golden GRR Value ���ϱ�***********************************************************/
	LogStr += LogStrPrinting(MODEINFORM, "Calculating \"Golden GRR Values\"...\n");
	ItemValue unpivot_min_grr_negative[MAXDATAQUANTITY] = {};
	ItemValue unpivot_max_grr_positive[MAXDATAQUANTITY] = {};
	int GrrDatanumber = 0;
	LogStr += CalculateGoldenGRR(unpivot_average, unpivot_std, unpivot_median_golden, Spec, Serialnumber, Tester, goldentester, &GrrDatanumber, unpivot_min_grr_negative, unpivot_max_grr_positive);

	CreateReport(unpivot_min_grr_negative, Spec, "min_grr_negative", GrrDatanumber, WriteFilePath);
	CreateReport(unpivot_max_grr_positive, Spec, "max_grr_positive", GrrDatanumber, WriteFilePath);
	m_Progress2.SetPos(m_Progress2.GetPos()+1);
	/******************************* Golden GRR Value ���ϱ�***********************************************************/
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
	/****************************���⼭���� %GRR�� ���� ���****************************************************************/
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
	/******************************* EV/AV/PV/%EV/%AV/%P_T/%PV/%GRR/NDC ���***********************************************************/
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
	/*********************************** GRR ��� ���� ����********************************************************************/
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
	/*********************************** Spec ���� ����*********************************************************************/
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
	/****************************************GRR KEY Bin file ����*************************************************************/

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
	/*****************************************LogFile ���*********************************************************************/
	WriteFilePath = DirectoryPath + "\\GRR_Report.Log";
	LogStr += LogStrPrinting(MODEINFORM, "Created Log File:" + WriteFilePath + "\n");
	FileWrite.Open(WriteFilePath, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	FileWrite.WriteString(LogStr);
	FileWrite.Close();
	
	/*****************************************��� ����*********************************************************************/
	AfxGetApp()->DoWaitCursor(-1);
	AfxMessageBox("Completed!");

	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/**********************************List Control 1 ������**************************************************************/
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

	//Tester�� Column �߰�
	m_ResultDlg->m_grrvalue.InsertColumn(0, "Serial Number", LVCFMT_CENTER, 200);
	for (int j = 0; j < testernumber; j++)
	{
		if(Tester[j] == goldentester)
			m_ResultDlg->m_grrvalue.InsertColumn(j + 1, Tester[j] + "*", LVCFMT_CENTER, 80);
		else
			m_ResultDlg->m_grrvalue.InsertColumn(j + 1, Tester[j], LVCFMT_CENTER, 80);
	}

	//Sample�� Row �߰�
	for (int i = 0; i < serialnumber; i++)
	{
		m_ResultDlg->m_grrvalue.InsertItem(i, Serialnumber[i]);
	}

	//Test ��� List CTRL�� ä���
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
	/**********************************List Control 2 ������**************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	
	m_ResultDlg->m_grrpercent.DeleteAllItems();
	while (m_ResultDlg->m_grrpercent.DeleteColumn(0));

	//Column �߰�
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
	//Item�� GRR �� �߰��Ҷ�
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
	/**********************************List Control 3 ������**************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	/***********************************************************************************************************************/
	m_ResultDlg->m_summaryList.DeleteAllItems();
	while (m_ResultDlg->m_summaryList.DeleteColumn(0));

	//Tester�� Column �߰�
	m_ResultDlg->m_summaryList.InsertColumn(0, "", LVCFMT_CENTER, 5);
	for (int j = 0; j < testernumber; j++)
	{
		if (Tester[j] == goldentester)
			m_ResultDlg->m_summaryList.InsertColumn(j + 1, Tester[j] + "*", LVCFMT_CENTER, 80);
		else
			m_ResultDlg->m_summaryList.InsertColumn(j + 1, Tester[j], LVCFMT_CENTER, 80);
	}
	//Row�� Result ���� �߰�
	m_ResultDlg->m_summaryList.InsertItem(0, "");

	//Test ��� List CTRL�� ä���
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



//�������� ��� �ڵ� ���� ���
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
	int mode = 0;  //������ �̸��� value�� �ʿ����� �ʱ⿡ 0�� ����
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

	//�ߺ������� ����
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

	//Tester�� Column �߰�
	m_listctrl.InsertColumn(0, "Serial Number", LVCFMT_LEFT, 200);
	for (int i = 0; i < testernumber; i++)
	{
		m_listctrl.InsertColumn(i+1,Tester[i],LVCFMT_CENTER, 80);
	}

	//SN���� item �߰�
	for (int i = 0; i < serialnumber; i++)
	{
		m_listctrl.InsertItem(i,Serialnumber[i]);
	}

	//�� SN, Tester�� trial Ƚ�� ���ϱ�
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

//���õ� SerialNumber ����� ��ư
void CSDC_GRRDlg::OnBnClickedButton8()
{
	POSITION pos = m_listctrl.GetFirstSelectedItemPosition(); // ���õ� ù ��° ��ġ�� ��� �ͼ�,
	while (pos != NULL)
	{
		int nItem = m_listctrl.GetNextSelectedItem(pos); // �� ��ġ�� �ش��ϴ� item�� index �� ���,
		m_listctrl.DeleteItem(nItem); // �� item �� �����.
		pos = m_listctrl.GetFirstSelectedItemPosition(); // ���õ� ù��° ��ġ�� �ٽ� ��� �´�.
	}
	TrialNumberChange();
}

//csv���Ͽ��� ������ �������� �Լ�
int CSDC_GRRDlg::FileScan(ItemValue unpivot[], SpecValue Spec[], int *Datanumber, int *mode, CString *Log)
{
	CStdioFile FileRead;
	CString ReadFilePath = "";
	int index = 0;
	int filenum = 0;
	filenum = m_filelist.GetCount();

	//Information ����

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
								/////CHECK_SUM Ȯ��(20.06.17)//////
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

	//Information ����
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
		//���� ���� �� �ñ׸� �������� ����Ҳ� ��������.
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

//Spec file load ��ư
void CSDC_GRRDlg::OnBnClickedButton9()
{
	CString PathRead = "";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, "BIN Files(*.bin)|*.bin|All Files(*.*)|*.*|");
	if (dlg.DoModal() == IDOK)
		PathRead = dlg.GetPathName();

	m_specpath.SetWindowTextA(PathRead);
}

//��������� �����ϴ� �Լ�
void CSDC_GRRDlg::CreateReport(ItemValue unpivotdata[],SpecValue Spec[], CString kind, int Datanumber, CString Path)
{
	CString Items = ",";

	//��� �����
	for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
	{
		Items += Spec[0].itemname[Itemindex] + ",";
	}
	//���� �����
	for (int k = 0; k < Datanumber; k++)
	{
		CString result = "";
		CString tmp1 = "";
		CString tmp2 = "";
		CString values = "";
		CStdioFile FileWrite;
		CString testername = "";
		CString WriteFilePath = Path;

		//�����Ͱ� ��������� ��� X
		if (unpivotdata[k].serialnumber == "" && unpivotdata[k].tester == "")
			continue;

		values += unpivotdata[k].serialnumber + ",";
		testername = unpivotdata[k].tester;
		//������ �� �����
		for (int Itemindex = ITEMSTART; Itemindex < Spec[0].totalitemnumber; Itemindex++)
			values += unpivotdata[k].value[Itemindex] + ",";


		//�׽��ͱ⺰ ���������
		WriteFilePath += "\\" + testername;
		if (GetFileAttributes(WriteFilePath) == 0xFFFFFFFF) 
		{
			CreateDirectory(WriteFilePath, NULL);
		}

		//���� �ױ�
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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

//���� ��ư
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
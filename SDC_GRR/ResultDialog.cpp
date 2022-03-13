// ResultDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SDC_GRR.h"
#include "ResultDialog.h"
#include "afxdialogex.h"
#include "SDC_GRRDlg.h"
#include "ChartCtrl_source/ChartPointsSerie.h"
#include "ChartCtrl_source/ChartLineSerie.h"
#include "ChartCtrl_source/ChartSurfaceSerie.h"
#include "ChartCtrl_source/ChartAxisLabel.h"
// ResultDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ResultDialog, CDialogEx)

BOOL m_bSortAscending = TRUE;
int m_nSortColumn = 1;
CChartStandardAxis* pBottomAxis;
CChartStandardAxis* pLeftAxis;

ResultDialog::ResultDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_grrvalue.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	TotalPass = _T("");
}

ResultDialog::~ResultDialog()
{
}

void ResultDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_grrvalue);
	DDX_Control(pDX, IDC_LIST4, m_grrpercent);
	DDX_Control(pDX, IDC_EDIT9, m_DirectoryPath);
	DDX_Control(pDX, IDC_CHECK1, m_ShowGrrValueFailed);
	DDX_Control(pDX, IDC_COMBO1, m_ComboTester);
	DDX_Control(pDX, IDC_EDIT1, m_TotalPass);
	DDX_Control(pDX, IDC_CHARTCTRL, m_ChartCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_Samplename);
	DDX_Control(pDX, IDC_EDIT3, m_Itemname);
	DDX_Control(pDX, IDC_LIST5, m_summaryList);
}


BEGIN_MESSAGE_MAP(ResultDialog, CDialogEx)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST4, &ResultDialog::OnLvnColumnclickList4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST4, &ResultDialog::OnNMCustomdrawList4)
	ON_BN_CLICKED(IDC_CHECK1, &ResultDialog::OnBnClickedCheck1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST3, &ResultDialog::OnNMCustomdrawList3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST4, &ResultDialog::OnLvnItemchangedList4)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &ResultDialog::OnLvnItemchangedList3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ResultDialog::OnCbnSelchangeCombo1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &ResultDialog::OnBnClickedButton1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST5, &ResultDialog::OnNMCustomdrawList5)
END_MESSAGE_MAP()


// ResultDialog �޽��� ó�����Դϴ�.


BOOL ResultDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_grrvalue.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_grrpercent.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// TODO: Add extra initialization here
	CFont font;
	font.CreatePointFont(400, "HY�߰��");
	GetDlgItem(IDC_EDIT1)->SetFont(&font);
	font.Detach();
	m_color = RGB(0, 0, 0);
	m_backBrush.CreateSolidBrush(m_color);

	FailItemList = "";
	ChangeColorOfListControl1 = FALSE;
	ChangeColorOfListControl2 = FALSE;
	ChangeColorOfListControl3 = FALSE;
	ChangingListControl = FALSE;
	pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetAutomaticMode(CChartAxis::NotAutomatic);
	pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomaticMode(CChartAxis::NotAutomatic);
	pBottomAxis->GetLabel()->SetText("Min_GRR_Negative");
	pBottomAxis->GetLabel()->SetColor(RGB(0, 0, 255));
	pLeftAxis->GetLabel()->SetText("Max_GRR_Positive");
	pLeftAxis->GetLabel()->SetColor(RGB(0, 0, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void ResultDialog::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	//CDialogEx::OnOK();
}
void ResultDialog::OnCancel()
{
	m_backBrush.DeleteObject();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CDialogEx::OnCancel();
}

/**************************************************************************************************************************************************/
/*****************************************************�������� ����********************************************************************************/
/**************************************************************************************************************************************************/
void ResultDialog::OnLvnColumnclickList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	ChangingListControl = TRUE;
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// pNMHDR ���� �߻��� �̺�Ʈ�� ������ ������.

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iColumn = pNMListView->iSubItem; // iSubItem �� ���õ� Column ��ȣ�̴�.

	if (iColumn == m_nSortColumn) { // m_nSortColumn �� ��� ������ ���� �����ߴ� Column ��ȣ�̴�.
		m_bSortAscending = !m_bSortAscending; // ���� �� Columns�� ������������ �����ѰŸ�, ������������ �����Ѵ�.
	}
	else { // ���� �ٸ� Column�̸� �������� ����
		m_bSortAscending = TRUE;
	}
	m_nSortColumn = iColumn; // ������ Column�� ��������� ����.

							 // �� ItemData�� ���ڿ��� �־���� �ϹǷ�
	int nItem = m_grrpercent.GetItemCount(); // Item ������ ���ϰ�

	CString** arStr = new CString*[nItem]; // ���ڿ� ��������� Item���� ��ŭ �����.

	for (int i = 0; i<nItem; i++) {
		arStr[i] = new CString(m_grrpercent.GetItemText(i, iColumn)); // ���ڿ��� �� Item�� ������ �־��ְ�
		m_grrpercent.SetItemData(i, (LPARAM)arStr[i]); // ItemData�� ���ش�.
	}
	// ù ��° �μ��� ������ ���� �Լ�, �� ��° �μ��� ���� ���
	if(iColumn>1)
		m_grrpercent.SortItems(CompareDoubleFunc, (LPARAM)m_bSortAscending); // ���� ����!
	else
		m_grrpercent.SortItems(CompareStringFunc, (LPARAM)m_bSortAscending); // ���� ����!

	for (int i = 0; i<nItem; i++) // ���� �������� �Ʊ� �Ҵ��� ���ڿ� �޸𸮸� �ٽ� ����
		delete arStr[i];
	delete[]arStr;
	ChangingListControl = FALSE;

	*pResult = 0;
}


static int CALLBACK CompareDoubleFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam)
{
	CString* pStr1 = (CString*)lParam1; // ItemData�� ���ڿ��� �� ��ȯ
	CString* pStr2 = (CString*)lParam2;
	BOOL bSortAscending = (BOOL)lParam; // ���� ���
	
	double pDouble1 = atof(*pStr1);
	double pDouble2 = atof(*pStr2);;
	int result = strcmp(*pStr1, *pStr2); // strcmp �� ���ؼ�

	if (pDouble1 > pDouble2)
		result = 1;
	else if (pDouble1 < pDouble2)
		result = -1;
	else
		result = 0;

	if (bSortAscending == TRUE) // ���� �����̸� �׳� ����
		return result;
	else // �ƴϸ� �ݴ�� ����
		return -result;

	return 0;
}

static int CALLBACK CompareStringFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam)
{
	CString* pStr1 = (CString*)lParam1; // ItemData�� ���ڿ��� �� ��ȯ
	CString* pStr2 = (CString*)lParam2;
	BOOL bSortAscending = (BOOL)lParam; // ���� ���

	int result = strcmp(*pStr1, *pStr2); // strcmp �� ���ؼ�

	if (bSortAscending == TRUE) // ���� �����̸� �׳� ����
		return result;
	else // �ƴϸ� �ݴ�� ����
		return -result;

	return 0;
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

/**************************************************************************************************************************************************/
/************************�׷����׸���************************************************************************************************************/
/**************************************************************************************************************************************************/
void ResultDialog::DrawingGraph(void)
{
	//CSV ���� ã������ �ּ� ��������
	CString DirectoryPath = "";
	m_DirectoryPath.GetWindowTextA(DirectoryPath);

	//Column�� �ִ� Tester list ���ϱ�
	CString Tester[MAXSAMPLESIZE] = { "" };
	CString Goldentester = "";
	int testernumber = 0;
	LVCOLUMN ss;    //��������
	char temparary[256] = {};
	ss.mask = LVCF_TEXT | LVCF_WIDTH; //����ü �ʱ�ȭ
	ss.pszText = temparary;//����ü�� ���ڿ� �ʱ�ȭ
	ss.cchTextMax = 256;//�ִ����
	ss.cx = 0;
	CHeaderCtrl  *pHead = NULL;
	int	nRowCnt = 0;
	pHead = m_grrvalue.GetHeaderCtrl();
	nRowCnt = pHead->GetItemCount();
	while (testernumber < nRowCnt - 1)
	{
		m_grrvalue.GetColumn(testernumber + 1, &ss);
		Tester[testernumber] = ss.pszText;
		if (Tester[testernumber].Find('*') != -1)
		{
			Tester[testernumber].Remove('*');
			Goldentester = Tester[testernumber];
		}
		testernumber++;
	}

	//������ �̸� ��������
	CString Itemname = "";
	m_Itemname.GetWindowTextA(Itemname);
	if (Itemname == "")
		return;

	//���� �̸� ��������
	CString Samplename = "";
	m_Samplename.GetWindowTextA(Samplename);
	if (Samplename == "")
		return;

	CString ReadPath = "";
	//Spec ��������
	CString USL = "";
	CString LSL = "";
	CString ErrorScale = "";
	ReadPath = DirectoryPath + "\\GRR_Spec.csv";
	USL = GetValuefromCSV(Itemname, ReadPath, "Upper Limit----->");
	LSL = GetValuefromCSV(Itemname, ReadPath, "Lower Limit----->");
	ErrorScale = GetValuefromCSV(Itemname, ReadPath, "ErrorScale");

	//Graph �׸���
	m_ChartCtrl.RemoveAllSeries();
	m_ChartCtrl.EnableRefresh(false);
	m_ChartCtrl.GetLegend()->SetVisible(true);
	m_ChartCtrl.GetLegend()->SetHorizontalMode(false);
	m_ChartCtrl.GetLegend()->UndockLegend(80, 50);
	

	double GrrMaxData = 0;
	double GrrMinData = 0;
	double Max_Max = 0;
	double Max_Min = 0;
	double Min_Max = 0;
	double Min_Min = 0;
	
	for (int j = 0; j < testernumber; j++)
	{
		ReadPath = DirectoryPath + "\\" + Tester[j] + "\\" + Tester[j] + "_max_grr_positive.csv";
		GrrMaxData = atof(GetValuefromCSV(Itemname, ReadPath, Samplename));
		ReadPath = DirectoryPath + "\\" + Tester[j] + "\\" + Tester[j] + "_min_grr_negative.csv";
		GrrMinData = atof(GetValuefromCSV(Itemname, ReadPath, Samplename));
		if (j == 0)
		{
			Max_Max = GrrMaxData;
			Max_Min = GrrMaxData;
			Min_Max = GrrMinData;
			Min_Min = GrrMinData;
		}
		else
		{
			if (Max_Max < GrrMaxData)
				Max_Max = GrrMaxData;
			if (Max_Min > GrrMaxData)
				Max_Min = GrrMaxData;
			if (Min_Max < GrrMinData)
				Min_Max = GrrMinData;
			if (Min_Min > GrrMinData)
				Min_Min = GrrMinData;
		}
	}
	//Limit �ִ밪 Ȯ��
	double Max_LIMIT = 0;
	double Min_LIMIT = 0;
	Max_LIMIT = (atof(USL) - atof(LSL)) * atof(ErrorScale);
	Min_LIMIT = (atof(LSL) - atof(USL)) * atof(ErrorScale);
	if (Max_Max < Max_LIMIT)
		Max_Max = Max_LIMIT;
	if (Max_Min > Max_LIMIT)
		Max_Min = Max_LIMIT;
	if (Min_Max < Min_LIMIT)
		Min_Max = Min_LIMIT;
	if (Min_Min > Min_LIMIT)
		Min_Min = Min_LIMIT;

	//X��, Y �� ��ü ���� ���ϱ�
	double XInterval = Min_Max - Min_Min;
	double YInterval = Max_Max - Max_Min;
	int BottomMin = int(Min_Min) - int((0.1*XInterval)) - 10;
	int BottomMax = int(Min_Max) + int((0.1*XInterval)) + 10;
	int LeftMin = int(Max_Min) - int((0.1*YInterval)) - 10;
	int LeftMax = int(Max_Max) + int((0.1*YInterval)) + 10;
	pBottomAxis->SetMinMax(BottomMin, BottomMax);
	pLeftAxis->SetMinMax(LeftMin, LeftMax);
	//pBottomAxis->SetTickIncrement(false, 1.0);
	//pBottomAxis->SetDiscrete(true);
	//pLeftAxis->SetTickIncrement(false, 1.0);
	//pLeftAxis->SetDiscrete(true);
	//CString normal;
	//normal.Format("%d\n%d\n%i\n%i\n%i\n%i", Max_LIMIT, Min_LIMIT, aaa,bbb,ccc,ddd);
	//AfxMessageBox(normal);

	//Limit ���߱�
	CChartSurfaceSerie* m_pSurfaceSeries = nullptr;
	m_pSurfaceSeries = m_ChartCtrl.CreateSurfaceSerie();
	m_pSurfaceSeries->AddPoint(Min_LIMIT, Max_LIMIT);
	m_pSurfaceSeries->AddPoint(BottomMax, Max_LIMIT);
	m_pSurfaceSeries->SetColor(RGB(0,255,0));

	CChartPointsSerie* pSeries = nullptr;
	CChartLineSerie* m_pLineSeries = nullptr;
	for (int j = 0; j < testernumber; j++)
	{
		ReadPath = DirectoryPath + "\\" + Tester[j] + "\\" + Tester[j] + "_max_grr_positive.csv";
		GrrMaxData = atof(GetValuefromCSV(Itemname, ReadPath, Samplename));
		ReadPath = DirectoryPath + "\\" + Tester[j] + "\\" + Tester[j] + "_min_grr_negative.csv";
		GrrMinData = atof(GetValuefromCSV(Itemname, ReadPath, Samplename));

		if (Tester[j] == Goldentester)
			Tester[j] = "*" + Goldentester;
		pSeries = m_ChartCtrl.CreatePointsSerie();
		pSeries->AddPoints(&GrrMinData, &GrrMaxData, 1);
		pSeries->SetName((TChartString)Tester[j]);
		pSeries->SetColor(RGB((j%3)*127, ((j/3)%3)*127, ((j/9)%3)*127));
		pSeries->SetPointSize(15, 15);

		m_pLineSeries = m_ChartCtrl.CreateLineSerie();
		m_pLineSeries->AddPoint(GrrMinData*0.5, GrrMinData *2);
		m_pLineSeries->AddPoint(GrrMaxData * 0.5, GrrMaxData * 2);
	}

	m_ChartCtrl.EnableRefresh(true);
}
/***************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************/

/**************************************************************************************************************************************/
/*********************************GRR Value �� Fail �� ��Ÿ���� üũ�ڽ�***************************************************************/
/**************************************************************************************************************************************/
void ResultDialog::OnBnClickedCheck1()
{
	UpdateData(TRUE);
	ChangingListControl = TRUE;
	BOOL chk;
	chk = m_ShowGrrValueFailed.GetCheck();
	if (chk == 1)
	{
		int MaxRow = m_grrpercent.GetItemCount();
		int CheckRow = 0;
		CString PASSFAIL = "";

		for(int i=0; i<MaxRow; i++)
		{
			PASSFAIL = m_grrpercent.GetItemText(CheckRow,1);
			if (FailItemList.Find(m_grrpercent.GetItemText(CheckRow, 0) + ",") == -1 && PASSFAIL == "PASS")
				m_grrpercent.DeleteItem(CheckRow);
			else
				CheckRow++;
			//UpdateData(FALSE);
		}
	}
	else
	{
		CStdioFile FileRead;
		CString DirectoryPath = "";
		m_DirectoryPath.GetWindowTextA(DirectoryPath);
		CString ReadSpecPath = DirectoryPath;
		CString selectedtester = "";
		int cursel = this->m_ComboTester.GetCurSel();
		if (cursel < 0)
			selectedtester = "";
		else
			m_ComboTester.GetLBText(cursel, selectedtester);
		CString tmp;
		CString str;
		CString Itemname[MAXITEMSIZE];
		int EVcommanumber = 0;
		int AVcommanumber = 0;
		int GRRcommanumber = 0;
		int Testercommanumber = 0;
		int Mincommanumber = 0;
		int Maxcommanumber = 0;
		int ErrorCountcommanumber = 0;
		int PassFailcommanumber = 0;
		CString StrPercentEV[MAXITEMSIZE] = { "" };
		CString StrPercentAV[MAXITEMSIZE] = { "" };
		CString StrPercentGRR[MAXITEMSIZE] = { "" };
		CString StrMin[MAXITEMSIZE] = { "" };
		CString StrMax[MAXITEMSIZE] = { "" };
		CString StrErrorCount[MAXITEMSIZE] = { "" };
		CString StrPassFail[MAXITEMSIZE] = { "" };
		BOOL PrintStart = FALSE;

		ReadSpecPath += "\\GRR_Result.csv";

		if (!FileRead.Open(ReadSpecPath, CFile::modeRead | CFile::typeText))
		{
			AfxMessageBox("������ �ջ�Ǿ����ϴ�.");
		}
		else
		{
			int Itemindex = 0;
			while (FileRead.ReadString(tmp))
			{
				
				if (tmp.Find("Item Name,%EV,%AV,%P/T,") != -1)
				{
					str = tmp.Left(tmp.Find("%EV"));
					EVcommanumber = str.Remove(',');
					str = tmp.Left(tmp.Find("%AV"));
					AVcommanumber = str.Remove(',');
					str = tmp.Left(tmp.Find("%GRR"));
					GRRcommanumber = str.Remove(',');
					str = tmp.Left(tmp.Find("Tester"));
					Testercommanumber = str.Remove(',');
					str = tmp.Left(tmp.Find("MIN"));
					Mincommanumber = str.Remove(',');
					str = tmp.Left(tmp.Find("MAX"));
					Maxcommanumber = str.Remove(',');
					str = tmp.Left(tmp.Find("ErrorCount"));
					ErrorCountcommanumber = str.Remove(',');
					str = tmp.Left(tmp.Find("PASS/FAIL"));
					PassFailcommanumber = str.Remove(',');
					PrintStart = TRUE;
				}
				else if (PrintStart == TRUE)
				{
					str = tmp;
					for (int j = 0; j < Testercommanumber; j++)
						str = str.Mid(str.Find(",") + 1);
					if (str.Left(str.Find(",")) == selectedtester || str.Left(str.Find(",")) == "ALL")
					{
						Itemname[Itemindex] = tmp.Left(tmp.Find(","));
						str = tmp;
						for (int j = 0; j < EVcommanumber; j++)
							str = str.Mid(str.Find(",") + 1);
						StrPercentEV[Itemindex] = str.Left(str.Find(","));
						str = tmp;
						for (int j = 0; j < AVcommanumber; j++)
							str = str.Mid(str.Find(",") + 1);
						StrPercentAV[Itemindex] = str.Left(str.Find(","));
						str = tmp;
						for (int j = 0; j < GRRcommanumber; j++)
							str = str.Mid(str.Find(",") + 1);
						StrPercentGRR[Itemindex] = str.Left(str.Find(","));
						str = tmp;
						for (int j = 0; j < Mincommanumber; j++)
							str = str.Mid(str.Find(",") + 1);
						StrMin[Itemindex] = str.Left(str.Find(","));
						str = tmp;
						for (int j = 0; j < Maxcommanumber; j++)
							str = str.Mid(str.Find(",") + 1);
						StrMax[Itemindex] = str.Left(str.Find(","));
						str = tmp;
						for (int j = 0; j < ErrorCountcommanumber; j++)
							str = str.Mid(str.Find(",") + 1);
						StrErrorCount[Itemindex] = str.Left(str.Find(","));
						str = tmp;
						for (int j = 0; j < PassFailcommanumber; j++)
							str = str.Mid(str.Find(",") + 1);
						StrPassFail[Itemindex] = str;
						Itemindex++;
					}
					else
						continue;
				}
				else
					continue;
			}
			FileRead.Close();
		}

		m_grrpercent.DeleteAllItems();

		//Item�� GRR �� �߰��Ҷ�
		int Rowindex = 0;
		for (int Itemindex = 0; Itemindex < MAXITEMSIZE; Itemindex++)
		{
			if (Itemname[Itemindex] == "")
				continue;
			else
			{
				m_grrpercent.InsertItem(Rowindex, Itemname[Itemindex]);
				m_grrpercent.SetItem(Rowindex, 1, LVIF_TEXT, StrPassFail[Itemindex], NULL, NULL, NULL, NULL);
				m_grrpercent.SetItem(Rowindex, 2, LVIF_TEXT, StrPercentEV[Itemindex], NULL, NULL, NULL, NULL);
				m_grrpercent.SetItem(Rowindex, 3, LVIF_TEXT, StrPercentAV[Itemindex], NULL, NULL, NULL, NULL);
				m_grrpercent.SetItem(Rowindex, 4, LVIF_TEXT, StrPercentGRR[Itemindex], NULL, NULL, NULL, NULL);
				m_grrpercent.SetItem(Rowindex, 5, LVIF_TEXT, StrMin[Itemindex], NULL, NULL, NULL, NULL);
				m_grrpercent.SetItem(Rowindex, 6, LVIF_TEXT, StrMax[Itemindex], NULL, NULL, NULL, NULL);
				m_grrpercent.SetItem(Rowindex, 7, LVIF_TEXT, StrErrorCount[Itemindex], NULL, NULL, NULL, NULL);
			}
		}
		ChangeColorOfListControl2 = TRUE;
		m_grrpercent.Invalidate(FALSE);
	}
	ChangingListControl = FALSE;
}

/**********************************************************************************************************************************************/
/********************************����Ʈ��Ʈ�� �ҷ� ��ĥ�ϱ�************************************************************************************/
/**********************************************************************************************************************************************/
void ResultDialog::OnNMCustomdrawList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	if (ChangeColorOfListControl1 == TRUE)
	{
		NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;
		switch (pLVCD->nmcd.dwDrawStage)
		{
		case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;

		case CDDS_ITEMPREPAINT:
			*pResult = CDRF_NOTIFYSUBITEMDRAW;
			break;

		case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
		{
			int nRow = (int)pLVCD->nmcd.dwItemSpec; // �� �ε����� ������
			int nSub = (int)pLVCD->iSubItem; // �� �ε����� ������ 

			if (m_grrvalue.GetItemText(nRow, nSub).Find("FAIL") != -1)
			{
				pLVCD->clrTextBk = RGB(255, 0, 0);
				pLVCD->clrText = RGB(255, 255, 255);
			}
			else
			{
				pLVCD->clrTextBk = RGB(255, 255, 255);
				pLVCD->clrText = RGB(0, 0, 0);
			}

			*pResult = CDRF_DODEFAULT;
			break;
			
		}
		case CDDS_ITEMPOSTPAINT:
			ChangeColorOfListControl1 = FALSE;
			break;
		}
	}
}
void ResultDialog::OnNMCustomdrawList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	
	if (ChangeColorOfListControl2 == TRUE)
	{
		CString selectedtester = "";
		int cursel = this->m_ComboTester.GetCurSel();
		if (cursel < 0)
			selectedtester = "ETY";
		else
			m_ComboTester.GetLBText(cursel, selectedtester);
		NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;
		switch (pLVCD->nmcd.dwDrawStage)
		{
		case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;

		case CDDS_ITEMPREPAINT:
			*pResult = CDRF_NOTIFYSUBITEMDRAW;
			break;

		case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
		{
			int nRow = (int)pLVCD->nmcd.dwItemSpec; // �� �ε����� ������
			int nSub = (int)pLVCD->iSubItem; // �� �ε����� ������ 

			if (FailItemList.Find(m_grrpercent.GetItemText(nRow, nSub) + ",") != -1)
			{
				pLVCD->clrTextBk = RGB(255, 0, 0);
				pLVCD->clrText = RGB(255, 255, 255);
			}
			/*
			else if (selectedtester == "ETY" && FailItemList.Find(m_grrpercent.GetItemText(nRow, nSub) + ",") != -1)
			{
				pLVCD->clrTextBk = RGB(255, 0, 0);
				pLVCD->clrText = RGB(255, 255, 255);
			}
			*/
			else if (m_grrpercent.GetItemText(nRow, 1) == "FAIL")
			{
				pLVCD->clrTextBk = RGB(255, 255, 0);
				pLVCD->clrText = RGB(0, 0, 0);
			}
			else
			{
				pLVCD->clrTextBk = RGB(255, 255, 255);
				pLVCD->clrText = RGB(0, 0, 0);
			}
			*pResult = CDRF_DODEFAULT;
			break;
		}
		case CDDS_ITEMPOSTPAINT:
			ChangeColorOfListControl2 = FALSE;
			break;
		}
	}
	
}

void ResultDialog::OnNMCustomdrawList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	if (ChangeColorOfListControl3 == TRUE)
	{
		NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;
		switch (pLVCD->nmcd.dwDrawStage)
		{
		case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;

		case CDDS_ITEMPREPAINT:
			*pResult = CDRF_NOTIFYSUBITEMDRAW;
			break;

		case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
		{
			int nRow = (int)pLVCD->nmcd.dwItemSpec; // �� �ε����� ������
			int nSub = (int)pLVCD->iSubItem; // �� �ε����� ������ 

			if (m_summaryList.GetItemText(nRow, nSub).Find("FAIL") != -1)
			{
				pLVCD->clrTextBk = RGB(255, 0, 0);
				pLVCD->clrText = RGB(255, 255, 255);
			}
			else
			{
				pLVCD->clrTextBk = RGB(255, 255, 255);
				pLVCD->clrText = RGB(0, 0, 0);
			}

			*pResult = CDRF_DODEFAULT;
			break;

		}
		case CDDS_ITEMPOSTPAINT:
			ChangeColorOfListControl3 = FALSE;
			break;
		}
	}
}

/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/

/**********************************************************************************************************************************************/
/************************List Control ���� Item ��ȭ�� �׷��� �׸���***************************************************************************/
/**********************************************************************************************************************************************/
void ResultDialog::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (ChangingListControl == FALSE)
	{
		LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		int m_nSelectedIndex = pNMListView->iItem;		//int idx = pNMListView -> iItem;// ���õ� �����۰��� �������� (0,1 ... n ��° �ε���) �Ѱ� �����´�.
														//CString sIndexValue;sIndexValue = m_listDataTable.GetItemText(idx, 1);
		CString Samplename = m_grrvalue.GetItemText(m_nSelectedIndex, 0);

		m_Samplename.SetWindowTextA(Samplename);
		DrawingGraph();

		*pResult = 0;
	}
}

void ResultDialog::OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (ChangingListControl == FALSE)
	{
		LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		int m_nSelectedIndex = pNMListView->iItem;		//int idx = pNMListView -> iItem;// ���õ� �����۰��� �������� (0,1 ... n ��° �ε���) �Ѱ� �����´�.
														//CString sIndexValue;sIndexValue = m_listDataTable.GetItemText(idx, 1);
		CString Itemname = m_grrpercent.GetItemText(m_nSelectedIndex, 0);

		m_Itemname.SetWindowTextA(Itemname);
		DrawingGraph();
		*pResult = 0;
	}
}


void ResultDialog::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	ChangingListControl = TRUE;
	CStdioFile FileRead;
	CString DirectoryPath = "";
	m_DirectoryPath.GetWindowTextA(DirectoryPath);
	CString ReadSpecPath = DirectoryPath;
	CString tmp;
	CString str;
	CString Itemname[MAXITEMSIZE];
	int EVcommanumber = 0;
	int AVcommanumber = 0;
	int GRRcommanumber = 0;
	int Testercommanumber = 0;
	int Mincommanumber = 0;
	int Maxcommanumber = 0;
	int ErrorCountcommanumber = 0;
	int PassFailcommanumber = 0;
	CString StrPercentEV[MAXITEMSIZE] = { "" };
	CString StrPercentAV[MAXITEMSIZE] = { "" };
	CString StrPercentGRR[MAXITEMSIZE] = { "" };
	CString StrMin[MAXITEMSIZE] = { "" };
	CString StrMax[MAXITEMSIZE] = { "" };
	CString StrErrorCount[MAXITEMSIZE] = { "" };
	CString StrPassFail[MAXITEMSIZE] = { "" };
	BOOL PrintStart = FALSE;
	CString selectedtester = "";

	m_ComboTester.GetLBText(this->m_ComboTester.GetCurSel(), selectedtester);
	ReadSpecPath += "\\GRR_Result.csv";

	if (!FileRead.Open(ReadSpecPath, CFile::modeRead | CFile::typeText))
	{
		AfxMessageBox("������ �ջ�Ǿ����ϴ�.");
	}
	else
	{
		int Itemindex = 0;
		while (FileRead.ReadString(tmp))
		{
			if (tmp.Find("Item Name,%EV,%AV,%P/T,") != -1)
			{
				str = tmp.Left(tmp.Find("%EV"));
				EVcommanumber = str.Remove(',');
				str = tmp.Left(tmp.Find("%AV"));
				AVcommanumber = str.Remove(',');
				str = tmp.Left(tmp.Find("%GRR"));
				GRRcommanumber = str.Remove(',');
				str = tmp.Left(tmp.Find("Tester"));
				Testercommanumber = str.Remove(',');
				str = tmp.Left(tmp.Find("MIN"));
				Mincommanumber = str.Remove(',');
				str = tmp.Left(tmp.Find("MAX"));
				Maxcommanumber = str.Remove(',');
				str = tmp.Left(tmp.Find("ErrorCount"));
				ErrorCountcommanumber = str.Remove(',');
				str = tmp.Left(tmp.Find("PASS/FAIL"));
				PassFailcommanumber = str.Remove(',');
				PrintStart = TRUE;
			}
			else if (PrintStart == TRUE)
			{
				str = tmp;
				for (int j = 0; j < Testercommanumber; j++)
					str = str.Mid(str.Find(",") + 1);
				if (str.Left(str.Find(",")) == selectedtester || str.Left(str.Find(",")) == "ALL")
				{
					Itemname[Itemindex] = tmp.Left(tmp.Find(","));
					str = tmp;
					for (int j = 0; j < EVcommanumber; j++)
						str = str.Mid(str.Find(",") + 1);
					StrPercentEV[Itemindex] = str.Left(str.Find(","));
					str = tmp;
					for (int j = 0; j < AVcommanumber; j++)
						str = str.Mid(str.Find(",") + 1);
					StrPercentAV[Itemindex] = str.Left(str.Find(","));
					str = tmp;
					for (int j = 0; j < GRRcommanumber; j++)
						str = str.Mid(str.Find(",") + 1);
					StrPercentGRR[Itemindex] = str.Left(str.Find(","));
					str = tmp;
					for (int j = 0; j < Mincommanumber; j++)
						str = str.Mid(str.Find(",") + 1);
					StrMin[Itemindex] = str.Left(str.Find(","));
					str = tmp;
					for (int j = 0; j < Maxcommanumber; j++)
						str = str.Mid(str.Find(",") + 1);
					StrMax[Itemindex] = str.Left(str.Find(","));
					str = tmp;
					for (int j = 0; j < ErrorCountcommanumber; j++)
						str = str.Mid(str.Find(",") + 1);
					StrErrorCount[Itemindex] = str.Left(str.Find(","));
					str = tmp;
					for (int j = 0; j < PassFailcommanumber; j++)
						str = str.Mid(str.Find(",") + 1);
					StrPassFail[Itemindex] = str;
					Itemindex++;
				}
				else
					continue;
			}
			else
				continue;
		}
		FileRead.Close();
	}

	m_grrpercent.DeleteAllItems();

	//Item�� GRR �� �߰��Ҷ�
	int Rowindex = 0;
	for (int Itemindex = 0; Itemindex < MAXITEMSIZE; Itemindex++)
	{
		if (Itemname[Itemindex] == "")
			continue;
		else
		{
			m_grrpercent.InsertItem(Rowindex, Itemname[Itemindex]);
			m_grrpercent.SetItem(Rowindex, 1, LVIF_TEXT, StrPassFail[Itemindex], NULL, NULL, NULL, NULL);
			m_grrpercent.SetItem(Rowindex, 2, LVIF_TEXT, StrPercentEV[Itemindex], NULL, NULL, NULL, NULL);
			m_grrpercent.SetItem(Rowindex, 3, LVIF_TEXT, StrPercentAV[Itemindex], NULL, NULL, NULL, NULL);
			m_grrpercent.SetItem(Rowindex, 4, LVIF_TEXT, StrPercentGRR[Itemindex], NULL, NULL, NULL, NULL);
			m_grrpercent.SetItem(Rowindex, 5, LVIF_TEXT, StrMin[Itemindex], NULL, NULL, NULL, NULL);
			m_grrpercent.SetItem(Rowindex, 6, LVIF_TEXT, StrMax[Itemindex], NULL, NULL, NULL, NULL);
			m_grrpercent.SetItem(Rowindex, 7, LVIF_TEXT, StrErrorCount[Itemindex], NULL, NULL, NULL, NULL);
		}
	}
	ChangeColorOfListControl2 = TRUE;
	m_grrpercent.Invalidate(FALSE);
	ChangingListControl = FALSE;
	OnBnClickedCheck1();
}


HBRUSH ResultDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	switch(nCtlColor)
	{
	case CTLCOLOR_STATIC:
		{
			if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
			{
				CString result = "";
				m_TotalPass.GetWindowTextA(result);
				if (result == "PASS")
				{
					pDC->SetBkColor(RGB(0, 0, 255));
					pDC->SetTextColor(RGB(255, 255, 255));
					m_backBrush.DeleteObject();
					m_color = RGB(0, 0, 255);
					m_backBrush.CreateSolidBrush(m_color);
					hbr = m_backBrush;
				}
				else
				{
					pDC->SetBkColor(RGB(255, 0, 0));
					pDC->SetTextColor(RGB(255, 255, 255));
					m_backBrush.DeleteObject();
					m_color = RGB(255, 0, 0);
					m_backBrush.CreateSolidBrush(m_color);
					hbr = m_backBrush;
				}
			}
		}
	}

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}



BOOL ResultDialog::PreTranslateMessage(MSG* pMsg)
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


void ResultDialog::OnBnClickedButton1()
{
	//CSV ���� ã������ �ּ� ��������
	CString DirectoryPath = "";
	CString Samplename = "";
	CString Itemname = "";
	TChartString strFilename;
	CString SaveFileName = "";

	m_DirectoryPath.GetWindowTextA(DirectoryPath);
	m_Samplename.GetWindowTextA(Samplename);
	m_Itemname.GetWindowTextA(Itemname);
	SaveFileName = DirectoryPath + "\\" + Samplename + "_" + Itemname + ".jpg";
	strFilename = SaveFileName;
	m_ChartCtrl.SaveAsImage(strFilename,NULL,32,GUID_NULL);

	AfxMessageBox("Saved!\n" + SaveFileName);
}



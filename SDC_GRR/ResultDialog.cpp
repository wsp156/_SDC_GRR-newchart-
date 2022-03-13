// ResultDialog.cpp : 구현 파일입니다.
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
// ResultDialog 대화 상자입니다.

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


// ResultDialog 메시지 처리기입니다.


BOOL ResultDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_grrvalue.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_grrpercent.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// TODO: Add extra initialization here
	CFont font;
	font.CreatePointFont(400, "HY견고딕");
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
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void ResultDialog::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//CDialogEx::OnOK();
}
void ResultDialog::OnCancel()
{
	m_backBrush.DeleteObject();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CDialogEx::OnCancel();
}

/**************************************************************************************************************************************************/
/*****************************************************오름차순 정렬********************************************************************************/
/**************************************************************************************************************************************************/
void ResultDialog::OnLvnColumnclickList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	ChangingListControl = TRUE;
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// pNMHDR 에는 발생한 이벤트의 정보를 가진다.

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iColumn = pNMListView->iSubItem; // iSubItem 이 선택된 Column 번호이다.

	if (iColumn == m_nSortColumn) { // m_nSortColumn 은 멤버 변수로 전에 정렬했던 Column 번호이다.
		m_bSortAscending = !m_bSortAscending; // 만약 이 Columns을 오름차순으로 정렬한거면, 내림차순으로 정렬한다.
	}
	else { // 전과 다른 Column이면 오름차순 정렬
		m_bSortAscending = TRUE;
	}
	m_nSortColumn = iColumn; // 정렬한 Column을 멤버변수로 저장.

							 // 각 ItemData에 문자열을 넣어줘야 하므로
	int nItem = m_grrpercent.GetItemCount(); // Item 갯수를 구하고

	CString** arStr = new CString*[nItem]; // 문자열 저장공간을 Item갯수 만큼 만든다.

	for (int i = 0; i<nItem; i++) {
		arStr[i] = new CString(m_grrpercent.GetItemText(i, iColumn)); // 문자열에 각 Item의 내용을 넣어주고
		m_grrpercent.SetItemData(i, (LPARAM)arStr[i]); // ItemData에 넣준다.
	}
	// 첫 번째 인수는 위에서 만든 함수, 두 번째 인수는 정렬 방식
	if(iColumn>1)
		m_grrpercent.SortItems(CompareDoubleFunc, (LPARAM)m_bSortAscending); // 숫자 정렬!
	else
		m_grrpercent.SortItems(CompareStringFunc, (LPARAM)m_bSortAscending); // 문자 정렬!

	for (int i = 0; i<nItem; i++) // 정렬 끝났으면 아까 할당한 문자열 메모리를 다시 삭제
		delete arStr[i];
	delete[]arStr;
	ChangingListControl = FALSE;

	*pResult = 0;
}


static int CALLBACK CompareDoubleFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam)
{
	CString* pStr1 = (CString*)lParam1; // ItemData을 문자열로 형 변환
	CString* pStr2 = (CString*)lParam2;
	BOOL bSortAscending = (BOOL)lParam; // 정렬 방식
	
	double pDouble1 = atof(*pStr1);
	double pDouble2 = atof(*pStr2);;
	int result = strcmp(*pStr1, *pStr2); // strcmp 로 비교해서

	if (pDouble1 > pDouble2)
		result = 1;
	else if (pDouble1 < pDouble2)
		result = -1;
	else
		result = 0;

	if (bSortAscending == TRUE) // 오름 차순이면 그냥 리턴
		return result;
	else // 아니면 반대로 리턴
		return -result;

	return 0;
}

static int CALLBACK CompareStringFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam)
{
	CString* pStr1 = (CString*)lParam1; // ItemData을 문자열로 형 변환
	CString* pStr2 = (CString*)lParam2;
	BOOL bSortAscending = (BOOL)lParam; // 정렬 방식

	int result = strcmp(*pStr1, *pStr2); // strcmp 로 비교해서

	if (bSortAscending == TRUE) // 오름 차순이면 그냥 리턴
		return result;
	else // 아니면 반대로 리턴
		return -result;

	return 0;
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/

/**************************************************************************************************************************************************/
/************************그래프그리기************************************************************************************************************/
/**************************************************************************************************************************************************/
void ResultDialog::DrawingGraph(void)
{
	//CSV 파일 찾을폴더 주소 가져오기
	CString DirectoryPath = "";
	m_DirectoryPath.GetWindowTextA(DirectoryPath);

	//Column에 있는 Tester list 구하기
	CString Tester[MAXSAMPLESIZE] = { "" };
	CString Goldentester = "";
	int testernumber = 0;
	LVCOLUMN ss;    //변수선언
	char temparary[256] = {};
	ss.mask = LVCF_TEXT | LVCF_WIDTH; //구조체 초기화
	ss.pszText = temparary;//구조체의 문자열 초기화
	ss.cchTextMax = 256;//최대길이
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

	//아이템 이름 가져오기
	CString Itemname = "";
	m_Itemname.GetWindowTextA(Itemname);
	if (Itemname == "")
		return;

	//샘플 이름 가져오기
	CString Samplename = "";
	m_Samplename.GetWindowTextA(Samplename);
	if (Samplename == "")
		return;

	CString ReadPath = "";
	//Spec 가져오기
	CString USL = "";
	CString LSL = "";
	CString ErrorScale = "";
	ReadPath = DirectoryPath + "\\GRR_Spec.csv";
	USL = GetValuefromCSV(Itemname, ReadPath, "Upper Limit----->");
	LSL = GetValuefromCSV(Itemname, ReadPath, "Lower Limit----->");
	ErrorScale = GetValuefromCSV(Itemname, ReadPath, "ErrorScale");

	//Graph 그리기
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
	//Limit 최대값 확인
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

	//X축, Y 축 전체 범위 정하기
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

	//Limit 선긋기
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
/*********************************GRR Value 중 Fail 만 나타내기 체크박스***************************************************************/
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
			AfxMessageBox("파일이 손상되었습니다.");
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

		//Item별 GRR 값 추가할때
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
/********************************리스트컨트롤 불량 색칠하기************************************************************************************/
/**********************************************************************************************************************************************/
void ResultDialog::OnNMCustomdrawList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
			int nRow = (int)pLVCD->nmcd.dwItemSpec; // 행 인덱스를 가져옴
			int nSub = (int)pLVCD->iSubItem; // 열 인덱스를 가져옴 

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
			int nRow = (int)pLVCD->nmcd.dwItemSpec; // 행 인덱스를 가져옴
			int nSub = (int)pLVCD->iSubItem; // 열 인덱스를 가져옴 

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
			int nRow = (int)pLVCD->nmcd.dwItemSpec; // 행 인덱스를 가져옴
			int nSub = (int)pLVCD->iSubItem; // 열 인덱스를 가져옴 

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
/************************List Control 선택 Item 변화시 그래프 그리기***************************************************************************/
/**********************************************************************************************************************************************/
void ResultDialog::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (ChangingListControl == FALSE)
	{
		LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		int m_nSelectedIndex = pNMListView->iItem;		//int idx = pNMListView -> iItem;// 선택된 아이템값의 아이템을 (0,1 ... n 번째 인덱스) 한개 가져온다.
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
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		int m_nSelectedIndex = pNMListView->iItem;		//int idx = pNMListView -> iItem;// 선택된 아이템값의 아이템을 (0,1 ... n 번째 인덱스) 한개 가져온다.
														//CString sIndexValue;sIndexValue = m_listDataTable.GetItemText(idx, 1);
		CString Itemname = m_grrpercent.GetItemText(m_nSelectedIndex, 0);

		m_Itemname.SetWindowTextA(Itemname);
		DrawingGraph();
		*pResult = 0;
	}
}


void ResultDialog::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
		AfxMessageBox("파일이 손상되었습니다.");
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

	//Item별 GRR 값 추가할때
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

	// TODO:  여기서 DC의 특성을 변경합니다.
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

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}



BOOL ResultDialog::PreTranslateMessage(MSG* pMsg)
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


void ResultDialog::OnBnClickedButton1()
{
	//CSV 파일 찾을폴더 주소 가져오기
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



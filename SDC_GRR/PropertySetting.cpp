// PropertySetting.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SDC_GRR.h"
#include "PropertySetting.h"
#include "afxdialogex.h"


// CPropertySetting ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPropertySetting, CDialogEx)

CPropertySetting::CPropertySetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

	EnableAutomation();

}

CPropertySetting::~CPropertySetting()
{
}

void CPropertySetting::OnFinalRelease()
{
	// �ڵ�ȭ ��ü�� ���� ������ ������ �����Ǹ�
	// OnFinalRelease�� ȣ��˴ϴ�.  �⺻ Ŭ�������� �ڵ����� ��ü�� �����մϴ�.
	// �⺻ Ŭ������ ȣ���ϱ� ���� ��ü�� �ʿ��� �߰� ���� �۾���
	// �߰��Ͻʽÿ�.

	CDialogEx::OnFinalRelease();
}

void CPropertySetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_Apply);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDC_MFCPROPERTYGRID1, m_PropGrid1);
}


BEGIN_MESSAGE_MAP(CPropertySetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPropertySetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPropertySetting::OnBnClickedCancel)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CPropertySetting, CDialogEx)
END_DISPATCH_MAP()

// ����: IID_IPropertySetting�� ���� ������ �߰��Ͽ�
//  VBA���� ���� ���� ���ε��� �����մϴ�. 
//  �� IID�� .IDL ���Ͽ� �ִ� dispinterface�� GUID�� ��ġ�ؾ� �մϴ�.

// {23EE47A6-B3C3-4FC2-997A-020343919E4F}
static const IID IID_IPropertySetting =
{ 0x23EE47A6, 0xB3C3, 0x4FC2, { 0x99, 0x7A, 0x2, 0x3, 0x43, 0x91, 0x9E, 0x4F } };

BEGIN_INTERFACE_MAP(CPropertySetting, CDialogEx)
	INTERFACE_PART(CPropertySetting, IID_IPropertySetting, Dispatch)
END_INTERFACE_MAP()


// CPropertySetting �޽��� ó�����Դϴ�.



BOOL CPropertySetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HDITEM item;
	item.cxy = 200;  // Size 
	item.mask = HDI_WIDTH;
	m_PropGrid1.GetHeaderCtrl().SetItem(0, &HDITEM(item));  //  m_ctrlGridControl => Control ���� // Header Column Size ����

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CHAR inbuffer[20] = "";
	CString iniPath = "";
	CString Serialnumber = "";
	CString TesterID = "";
	CString Time = "";
	CString ErrorCode = "";
	CString ErrorRate = "";

	iniPath = ".\\Information.ini";
	if(PathFileExists(iniPath))
	{
	}
	else
		AfxMessageBox("There is no INI File");

	GetPrivateProfileString("Information", "Serialnumber", "SERIALNUMBER", inbuffer, sizeof(inbuffer), iniPath);
	Serialnumber = inbuffer;
	GetPrivateProfileString("Information", "TesterID", "TESTERID", inbuffer, sizeof(inbuffer), iniPath);
	TesterID = inbuffer;
	GetPrivateProfileString("Information", "Time", "STOPTIME", inbuffer, sizeof(inbuffer), iniPath);
	Time = inbuffer;
	GetPrivateProfileString("Information", "ErrorCode", "ERRCODE", inbuffer, sizeof(inbuffer), iniPath);
	ErrorCode = inbuffer;
	GetPrivateProfileString("Information", "ErrorRate", "0.35", inbuffer, sizeof(inbuffer), iniPath);
	ErrorRate = inbuffer;

	CMFCPropertyGridProperty* pGroupInformation = new CMFCPropertyGridProperty("Information");
	m_PropGrid1.AddProperty(pGroupInformation);

	CMFCPropertyGridProperty* pPropSerialnumber = new CMFCPropertyGridProperty("Serialnumber", Serialnumber, "Write the Item name that you want to distinguish samples by");
	pPropSerialnumber->AllowEdit(TRUE);
	pGroupInformation->AddSubItem(pPropSerialnumber);
	CMFCPropertyGridProperty* pPropTesterID = new CMFCPropertyGridProperty("TesterID", TesterID, "Write the Item name that you want to distinguish tester by");
	pPropTesterID->AllowEdit(TRUE);
	pGroupInformation->AddSubItem(pPropTesterID);
	CMFCPropertyGridProperty* pPropTime = new CMFCPropertyGridProperty("Time", Time, "Write the Item name that you want to distinguish time by");
	pPropTime->AllowEdit(TRUE);
	pGroupInformation->AddSubItem(pPropTime);
	CMFCPropertyGridProperty* pPropErrorCode = new CMFCPropertyGridProperty("ErrorCode", ErrorCode, "Write the Item name that you want to distinguish samples by");
	pPropErrorCode->AllowEdit(TRUE);
	pGroupInformation->AddSubItem(pPropErrorCode);
	CMFCPropertyGridProperty* pPropErrorRate = new CMFCPropertyGridProperty("ErrorRate", ErrorRate, "Write the Error Rate that you are going to warn.");
	pPropErrorRate->AllowEdit(TRUE);
	pGroupInformation->AddSubItem(pPropErrorRate);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CPropertySetting::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString Item1;
	CString Item2;
	CString Item3;

	//m_ProbGrid_Setting.GetProperty(GroupCnt)->GetPropertyCount();

	for (int GroupCnt = 0; GroupCnt < m_PropGrid1.GetPropertyCount(); GroupCnt++)
	{
		for (int SubItemCnt = 0; SubItemCnt < m_PropGrid1.GetProperty(GroupCnt)->GetSubItemsCount(); SubItemCnt++)
		{
			Item1 = m_PropGrid1.GetProperty(GroupCnt)->GetName();
			Item2 = m_PropGrid1.GetProperty(GroupCnt)->GetSubItem(SubItemCnt)->GetName();
			Item3 = m_PropGrid1.GetProperty(GroupCnt)->GetSubItem(SubItemCnt)->GetValue();
			WritePrivateProfileStringA(Item1, Item2, Item3, ".\\Information.ini");
		}
	}

	CDialogEx::OnOK();
}


void CPropertySetting::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}

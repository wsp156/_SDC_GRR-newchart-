
// DlgProxy.cpp : ���� ����
//

#include "stdafx.h"
#include "SDC_GRR.h"
#include "DlgProxy.h"
#include "SDC_GRRDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDC_GRRDlgAutoProxy

IMPLEMENT_DYNCREATE(CSDC_GRRDlgAutoProxy, CCmdTarget)

CSDC_GRRDlgAutoProxy::CSDC_GRRDlgAutoProxy()
{
	EnableAutomation();
	
	// �ڵ�ȭ ��ü�� Ȱ��ȭ�Ǿ� �ִ� ���� ��� ���� ���α׷��� �����ϱ� ���� 
	//	�����ڿ��� AfxOleLockApp�� ȣ���մϴ�.
	AfxOleLockApp();

	// ���� ���α׷��� �� â �����͸� ���� ��ȭ ���ڿ� ����
	//  �׼����� �����ɴϴ�.  ���Ͻ��� ���� �����͸� �����Ͽ�
	//  ��ȭ ���ڸ� ����Ű�� ��ȭ ������ �Ĺ� �����͸� �� ���Ͻ÷�
	//  �����մϴ�.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CSDC_GRRDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CSDC_GRRDlg)))
		{
			m_pDialog = reinterpret_cast<CSDC_GRRDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CSDC_GRRDlgAutoProxy::~CSDC_GRRDlgAutoProxy()
{
	// ��� ��ü�� OLE �ڵ�ȭ�� ��������� �� ���� ���α׷��� �����ϱ� ����
	// 	�Ҹ��ڰ� AfxOleUnlockApp�� ȣ���մϴ�.
	//  �̷��� ȣ��� �� ��ȭ ���ڰ� ������ �� �ֽ��ϴ�.
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CSDC_GRRDlgAutoProxy::OnFinalRelease()
{
	// �ڵ�ȭ ��ü�� ���� ������ ������ �����Ǹ�
	// OnFinalRelease�� ȣ��˴ϴ�.  �⺻ Ŭ�������� �ڵ����� ��ü�� �����մϴ�.
	// �⺻ Ŭ������ ȣ���ϱ� ���� ��ü�� �ʿ��� �߰� ���� �۾���
	// �߰��Ͻʽÿ�.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CSDC_GRRDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSDC_GRRDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ����: IID_ISDC_GRR�� ���� ������ �߰��Ͽ�
//  VBA���� ���� ���� ���ε��� �����մϴ�.
//  �� IID�� .IDL ���Ͽ� �ִ� dispinterface�� GUID�� ��ġ�ؾ� �մϴ�.

// {544909A9-A5EE-4EE2-B44F-AE4B18AB469B}
static const IID IID_ISDC_GRR =
{ 0x544909A9, 0xA5EE, 0x4EE2, { 0xB4, 0x4F, 0xAE, 0x4B, 0x18, 0xAB, 0x46, 0x9B } };

BEGIN_INTERFACE_MAP(CSDC_GRRDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CSDC_GRRDlgAutoProxy, IID_ISDC_GRR, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ��ũ�ΰ� �� ������Ʈ�� StdAfx.h�� ���ǵ˴ϴ�.
// {2C049595-793A-4542-98B9-CE4247B304AF}
IMPLEMENT_OLECREATE2(CSDC_GRRDlgAutoProxy, "SDC_GRR.Application", 0x2c049595, 0x793a, 0x4542, 0x98, 0xb9, 0xce, 0x42, 0x47, 0xb3, 0x4, 0xaf)


// CSDC_GRRDlgAutoProxy �޽��� ó����


// DlgProxy.cpp : 구현 파일
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
	
	// 자동화 개체가 활성화되어 있는 동안 계속 응용 프로그램을 실행하기 위해 
	//	생성자에서 AfxOleLockApp를 호출합니다.
	AfxOleLockApp();

	// 응용 프로그램의 주 창 포인터를 통해 대화 상자에 대한
	//  액세스를 가져옵니다.  프록시의 내부 포인터를 설정하여
	//  대화 상자를 가리키고 대화 상자의 후방 포인터를 이 프록시로
	//  설정합니다.
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
	// 모든 개체가 OLE 자동화로 만들어졌을 때 응용 프로그램을 종료하기 위해
	// 	소멸자가 AfxOleUnlockApp를 호출합니다.
	//  이러한 호출로 주 대화 상자가 삭제될 수 있습니다.
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CSDC_GRRDlgAutoProxy::OnFinalRelease()
{
	// 자동화 개체에 대한 마지막 참조가 해제되면
	// OnFinalRelease가 호출됩니다.  기본 클래스에서 자동으로 개체를 삭제합니다.
	// 기본 클래스를 호출하기 전에 개체에 필요한 추가 정리 작업을
	// 추가하십시오.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CSDC_GRRDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSDC_GRRDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 참고: IID_ISDC_GRR에 대한 지원을 추가하여
//  VBA에서 형식 안전 바인딩을 지원합니다.
//  이 IID는 .IDL 파일에 있는 dispinterface의 GUID와 일치해야 합니다.

// {544909A9-A5EE-4EE2-B44F-AE4B18AB469B}
static const IID IID_ISDC_GRR =
{ 0x544909A9, 0xA5EE, 0x4EE2, { 0xB4, 0x4F, 0xAE, 0x4B, 0x18, 0xAB, 0x46, 0x9B } };

BEGIN_INTERFACE_MAP(CSDC_GRRDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CSDC_GRRDlgAutoProxy, IID_ISDC_GRR, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 매크로가 이 프로젝트의 StdAfx.h에 정의됩니다.
// {2C049595-793A-4542-98B9-CE4247B304AF}
IMPLEMENT_OLECREATE2(CSDC_GRRDlgAutoProxy, "SDC_GRR.Application", 0x2c049595, 0x793a, 0x4542, 0x98, 0xb9, 0xce, 0x42, 0x47, 0xb3, 0x4, 0xaf)


// CSDC_GRRDlgAutoProxy 메시지 처리기

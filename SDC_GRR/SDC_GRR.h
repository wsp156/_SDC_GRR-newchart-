
// SDC_GRR.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSDC_GRRApp:
// �� Ŭ������ ������ ���ؼ��� SDC_GRR.cpp�� �����Ͻʽÿ�.
//

class CSDC_GRRApp : public CWinApp
{
public:
	CSDC_GRRApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSDC_GRRApp theApp;
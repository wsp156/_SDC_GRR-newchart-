
// DlgProxy.h: ��� ����
//

#pragma once

class CSDC_GRRDlg;


// CSDC_GRRDlgAutoProxy ��� ���

class CSDC_GRRDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CSDC_GRRDlgAutoProxy)

	CSDC_GRRDlgAutoProxy();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.

// Ư���Դϴ�.
public:
	CSDC_GRRDlg* m_pDialog;

// �۾��Դϴ�.
public:

// �������Դϴ�.
	public:
	virtual void OnFinalRelease();

// �����Դϴ�.
protected:
	virtual ~CSDC_GRRDlgAutoProxy();

	// ������ �޽��� �� �Լ�

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CSDC_GRRDlgAutoProxy)

	// ������ OLE ����ġ �� �Լ�

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


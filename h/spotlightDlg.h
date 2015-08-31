#pragma once
//#include "Light.h"
#include "afxwin.h"

// spotlightDlg �Ի���

class spotlightDlg : public CDialog
{
	DECLARE_DYNAMIC(spotlightDlg)
	SpotLight &light;
public:
	spotlightDlg(SpotLight& l, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~spotlightDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SPOTLIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CEdit mEditX;
	CEdit mEditY;
	CEdit mEditZ;
	CEdit mEditAR;
	CEdit mEditAG;
	CEdit mEditAB;
	CEdit mEditAA;
	CEdit mEditDR;
	CEdit mEditDG;
	CEdit mEditDB;
	CEdit mEditDA;
	CEdit mEditSR;
	CEdit mEditSG;
	CEdit mEditSB;
	CEdit mEditSA;
};

// FilterParaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FFT.h"
#include "FilterParaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilterParaDlg dialog


CFilterParaDlg::CFilterParaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterParaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilterParaDlg)
	m_nDis = 0;
	//}}AFX_DATA_INIT
}


void CFilterParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterParaDlg)
	DDX_Text(pDX, IDC_EDIT1, m_nDis);
	DDV_MinMaxInt(pDX, m_nDis, -360, 360);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilterParaDlg, CDialog)
	//{{AFX_MSG_MAP(CFilterParaDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterParaDlg message handlers

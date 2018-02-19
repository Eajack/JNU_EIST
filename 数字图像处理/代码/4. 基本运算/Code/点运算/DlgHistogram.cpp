// DlgHistogram.cpp : implementation file
//

#include "stdafx.h"
#include "PointTrans.h"
#include "DlgHistogram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHistogram dialog



CDlgHistogram::CDlgHistogram(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHistogram::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHistogram)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgHistogram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHistogram)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHistogram, CDialog)
	//{{AFX_MSG_MAP(CDlgHistogram)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHistogram message handlers

extern DWORD H[256];

void Histogram();

BOOL CDlgHistogram::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Histogram();
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHistogram::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	int i;
	DWORD max;

	//绘制方框
	dc.Rectangle(20, 20, 277, 221);

	//求出H数组中的最大值
	max = 0;
	for (i = 0; i < 256; i ++)
	{
		if (H[i] > max)
			max = H[i];
	}

	for (i = 0; i < 256; i ++)
	{
		dc.MoveTo(i + 20, 220);
		dc.LineTo(i + 20, 220 - (int)(H[i] * 200 / max));
	}
	// Do not call CDialog::OnPaint() for painting messages
}

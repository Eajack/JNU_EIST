// PointTransView.cpp : implementation of the CPointTransView class
//

#include "stdafx.h"
#include "PointTrans.h"

#include "PointTransDoc.h"
#include "PointTransView.h"

#include "DlgHistogram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointTransView

IMPLEMENT_DYNCREATE(CPointTransView, CView)

BEGIN_MESSAGE_MAP(CPointTransView, CView)
	//{{AFX_MSG_MAP(CPointTransView)
	ON_COMMAND(ID_LINETRANS, OnLinetrans)
	ON_COMMAND(ID_HISTOGRAM, OnHisDiagram)
	ON_UPDATE_COMMAND_UI(ID_LINETRANS, OnUpdateLinetrans)
	ON_UPDATE_COMMAND_UI(ID_HISTOGRAM, OnUpdateHisDiagram)
	ON_COMMAND(ID_EQUALIZE, OnEqualize)
	ON_UPDATE_COMMAND_UI(ID_EQUALIZE, OnUpdateEqualize)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointTransView construction/destruction

CPointTransView::CPointTransView()
{
	// TODO: add construction code here

}

CPointTransView::~CPointTransView()
{
}

BOOL CPointTransView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPointTransView drawing

extern BITMAPINFO *lpBitsInfo;

void CPointTransView::OnDraw(CDC* pDC)
{
	CPointTransDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if (NULL == lpBitsInfo)
		return;

	LPVOID lpBits = (LPVOID)&lpBitsInfo ->bmiColors[lpBitsInfo ->bmiHeader.biClrUsed];
	StretchDIBits( 
		pDC->GetSafeHdc(),
		0,0,
		lpBitsInfo->bmiHeader.biWidth,
		lpBitsInfo->bmiHeader.biHeight,
		0,0,
		lpBitsInfo->bmiHeader.biWidth,
		lpBitsInfo->bmiHeader.biHeight,
		lpBits,
		lpBitsInfo, // bitmap data 
		DIB_RGB_COLORS,
		SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
// CPointTransView printing

BOOL CPointTransView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPointTransView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPointTransView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPointTransView diagnostics

#ifdef _DEBUG
void CPointTransView::AssertValid() const
{
	CView::AssertValid();
}

void CPointTransView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPointTransDoc* CPointTransView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPointTransDoc)));
	return (CPointTransDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPointTransView message handlers

void LinerTrans(float, float);
void CPointTransView::OnLinetrans() 
{
	// TODO: Add your command handler code here
	LinerTrans(2, -100);
	Invalidate();
}

void CPointTransView::OnHisDiagram() 
{
	// TODO: Add your command handler code here
	CDlgHistogram dlg;
	dlg.DoModal();
}

void Equalize();
void CPointTransView::OnEqualize() 
{
	// TODO: Add your command handler code here
	Equalize();
	Invalidate();
}

void CPointTransView::OnUpdateLinetrans(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

void CPointTransView::OnUpdateHisDiagram(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

void CPointTransView::OnUpdateEqualize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);	
}

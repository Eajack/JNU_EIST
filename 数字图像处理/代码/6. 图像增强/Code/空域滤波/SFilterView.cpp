// SFilterView.cpp : implementation of the CSFilterView class
//

#include "stdafx.h"
#include "SFilter.h"

#include "SFilterDoc.h"
#include "SFilterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSFilterView

IMPLEMENT_DYNCREATE(CSFilterView, CScrollView)

BEGIN_MESSAGE_MAP(CSFilterView, CScrollView)
	//{{AFX_MSG_MAP(CSFilterView)
	ON_COMMAND(ID_RAPLAS_SHARP, OnRaplasSharp)
	ON_UPDATE_COMMAND_UI(ID_RAPLAS_SHARP, OnUpdateRaplasSharp)
	ON_COMMAND(ID_MEDIAN_FILTER, OnMedianFilter)
	ON_UPDATE_COMMAND_UI(ID_MEDIAN_FILTER, OnUpdateMedianFilter)
	ON_COMMAND(ID_GRAD_SHARP, OnGradSharp)
	ON_UPDATE_COMMAND_UI(ID_GRAD_SHARP, OnUpdateGradSharp)
	ON_COMMAND(ID_AVERAGE_FILTER, OnAverageFilter)
	ON_UPDATE_COMMAND_UI(ID_AVERAGE_FILTER, OnUpdateAverageFilter)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSFilterView construction/destruction

CSFilterView::CSFilterView()
{
	// TODO: add construction code here

}

CSFilterView::~CSFilterView()
{
}

BOOL CSFilterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSFilterView drawing

extern BITMAPINFO *lpBitsInfo;

void CSFilterView::OnDraw(CDC* pDC)
{
	CSFilterDoc* pDoc = GetDocument();
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

void CSFilterView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 500;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CSFilterView printing

BOOL CSFilterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSFilterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSFilterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSFilterView diagnostics

#ifdef _DEBUG
void CSFilterView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSFilterView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSFilterDoc* CSFilterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSFilterDoc)));
	return (CSFilterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSFilterView message handlers
void AverageFilter();
void MedianFilter();
void GradSharp();
void RaplasSharp();

void CSFilterView::OnAverageFilter() 
{
	// TODO: Add your command handler code here
	AverageFilter();
	Invalidate();
}

void CSFilterView::OnMedianFilter() 
{
	// TODO: Add your command handler code here
	MedianFilter();
	Invalidate();
}

void CSFilterView::OnGradSharp() 
{
	// TODO: Add your command handler code here
	GradSharp();
	Invalidate();
}

void CSFilterView::OnRaplasSharp() 
{
	// TODO: Add your command handler code here
	RaplasSharp();
	Invalidate();
}

void CSFilterView::OnUpdateAverageFilter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);	
}

void CSFilterView::OnUpdateMedianFilter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);	
}

void CSFilterView::OnUpdateGradSharp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);	
}

void CSFilterView::OnUpdateRaplasSharp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);	
}




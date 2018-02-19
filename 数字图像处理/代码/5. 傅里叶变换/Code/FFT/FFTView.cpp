// FFTView.cpp : implementation of the CFFTView class
//

#include "stdafx.h"
#include "FFT.h"

#include "FFTDoc.h"
#include "FFTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFFTView

IMPLEMENT_DYNCREATE(CFFTView, CScrollView)

BEGIN_MESSAGE_MAP(CFFTView, CScrollView)
	//{{AFX_MSG_MAP(CFFTView)
	ON_COMMAND(ID_FFT, OnFft)
	ON_UPDATE_COMMAND_UI(ID_FFT, OnUpdateFft)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFFTView construction/destruction

CFFTView::CFFTView()
{
	// TODO: add construction code here

}

extern BITMAPINFO *lpDIB;
extern BITMAPINFO *lpDIB_FFT;

CFFTView::~CFFTView()
{
	if (lpDIB)
		free(lpDIB);
	if (lpDIB_FFT)
		free(lpDIB_FFT);
}

BOOL CFFTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFFTView drawing

void CFFTView::OnDraw(CDC* pDC)
{
	CFFTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	LPVOID lpBits;
	if (lpDIB)
	{
		lpBits = (LPVOID)&lpDIB->bmiColors[lpDIB->bmiHeader.biClrUsed];
		StretchDIBits( 
			pDC->GetSafeHdc(),
			0,0,
			lpDIB->bmiHeader.biWidth,
			lpDIB->bmiHeader.biHeight,
			0,0,
			lpDIB->bmiHeader.biWidth,
			lpDIB->bmiHeader.biHeight,
			lpBits,
			lpDIB, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY);
	}

	if (lpDIB_FFT)
	{
		lpBits = (LPVOID)&lpDIB_FFT->bmiColors[lpDIB_FFT->bmiHeader.biClrUsed];
		StretchDIBits( 
			pDC->GetSafeHdc(),
			600,0,
			lpDIB_FFT->bmiHeader.biWidth,
			lpDIB_FFT->bmiHeader.biHeight,
			0,0,
			lpDIB_FFT->bmiHeader.biWidth,
			lpDIB_FFT->bmiHeader.biHeight,
			lpBits,
			lpDIB_FFT, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY);
	}
}

void CFFTView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 1120;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CFFTView printing

BOOL CFFTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFFTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFFTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFFTView diagnostics

#ifdef _DEBUG
void CFFTView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFFTView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFFTDoc* CFFTView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFFTDoc)));
	return (CFFTDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFFTView message handlers

void Fourier();

void CFFTView::OnFft() 
{
	// TODO: Add your command handler code here
	if (lpDIB_FFT)
		free(lpDIB_FFT);

	Fourier();
	Invalidate();	
}

void CFFTView::OnUpdateFft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB != NULL);	
}

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

IMPLEMENT_DYNCREATE(CFFTView, CView)

BEGIN_MESSAGE_MAP(CFFTView, CView)
	//{{AFX_MSG_MAP(CFFTView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFFTView construction/destruction

CFFTView::CFFTView()
{
	// TODO: add construction code here

}

CFFTView::~CFFTView()
{
}

BOOL CFFTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFFTView drawing
extern BITMAPINFO *lpDIB;

void CFFTView::OnDraw(CDC* pDC)
{
	CFFTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if (lpDIB)
	{
		LPVOID lpBits = (LPVOID)&lpDIB->bmiColors[lpDIB->bmiHeader.biClrUsed];
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
	CView::AssertValid();
}

void CFFTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFFTDoc* CFFTView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFFTDoc)));
	return (CFFTDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFFTView message handlers

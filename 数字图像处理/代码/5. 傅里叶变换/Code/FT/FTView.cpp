// FTView.cpp : implementation of the CFTView class
//

#include "stdafx.h"
#include "FT.h"

#include "FTDoc.h"
#include "FTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTView

IMPLEMENT_DYNCREATE(CFTView, CView)

BEGIN_MESSAGE_MAP(CFTView, CView)
	//{{AFX_MSG_MAP(CFTView)
	ON_COMMAND(ID_FOURIER, OnFourier)
	ON_COMMAND(ID_IFOURIER, OnIFourier)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTView construction/destruction

CFTView::CFTView()
{
	// TODO: add construction code here

}

CFTView::~CFTView()
{
}

BOOL CFTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFTView drawing
extern BITMAPINFO *lpBitsInfo;

void CFTView::OnDraw(CDC* pDC)
{
	CFTDoc* pDoc = GetDocument();
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
// CFTView printing

BOOL CFTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFTView diagnostics

#ifdef _DEBUG
void CFTView::AssertValid() const
{
	CView::AssertValid();
}

void CFTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFTDoc* CFTView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFTDoc)));
	return (CFTDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFTView message handlers
void Fourier();
void IFourier();

void CFTView::OnFourier() 
{
	// TODO: Add your command handler code here
	Fourier();
	Invalidate();
}

void CFTView::OnIFourier() 
{
	// TODO: Add your command handler code here
	IFourier();
	Invalidate();
}

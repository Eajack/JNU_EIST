// AlgebraView.cpp : implementation of the CAlgebraView class
//

#include "stdafx.h"
#include "Algebra.h"

#include "AlgebraDoc.h"
#include "AlgebraView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlgebraView

IMPLEMENT_DYNCREATE(CAlgebraView, CView)

BEGIN_MESSAGE_MAP(CAlgebraView, CView)
	//{{AFX_MSG_MAP(CAlgebraView)
	ON_COMMAND(ID_BMP1, OnBmp1)
	ON_COMMAND(ID_BMP2, OnBmp2)
	ON_COMMAND(ID_BMP3, OnBmp3)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlgebraView construction/destruction

CAlgebraView::CAlgebraView()
{
	// TODO: add construction code here

}

CAlgebraView::~CAlgebraView()
{
}

BOOL CAlgebraView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAlgebraView drawing

extern BITMAPINFO *lpBitsInfo1;
extern BITMAPINFO *lpBitsInfo2;
extern BITMAPINFO *lpBitsInfo3;

BITMAPINFO* LoadBmpFile(char*);
BITMAPINFO* Algebra(BITMAPINFO*, BITMAPINFO*);

void CAlgebraView::OnDraw(CDC* pDC)
{
	CAlgebraDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	LPVOID lpBits;
	if (lpBitsInfo1)
	{
		lpBits = (LPVOID)&lpBitsInfo1->bmiColors[lpBitsInfo1->bmiHeader.biClrUsed];
		StretchDIBits( 
			pDC->GetSafeHdc(),
			0,0,
			lpBitsInfo1->bmiHeader.biWidth,
			lpBitsInfo1->bmiHeader.biHeight,
			0,0,
			lpBitsInfo1->bmiHeader.biWidth,
			lpBitsInfo1->bmiHeader.biHeight,
			lpBits,
			lpBitsInfo1, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY);
	}

	if (lpBitsInfo2)
	{
		lpBits = (LPVOID)&lpBitsInfo2->bmiColors[lpBitsInfo2->bmiHeader.biClrUsed];
		StretchDIBits( 
			pDC->GetSafeHdc(),
			420,0,
			lpBitsInfo2->bmiHeader.biWidth,
			lpBitsInfo2->bmiHeader.biHeight,
			0,0,
			lpBitsInfo2->bmiHeader.biWidth,
			lpBitsInfo2->bmiHeader.biHeight,
			lpBits,
			lpBitsInfo2, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY);
	}

	if (lpBitsInfo3)
	{
		lpBits = (LPVOID)&lpBitsInfo3->bmiColors[lpBitsInfo3->bmiHeader.biClrUsed];
		StretchDIBits( 
			pDC->GetSafeHdc(),
			0,300,
			lpBitsInfo3->bmiHeader.biWidth,
			lpBitsInfo3->bmiHeader.biHeight,
			0,0,
			lpBitsInfo3->bmiHeader.biWidth,
			lpBitsInfo3->bmiHeader.biHeight,
			lpBits,
			lpBitsInfo3, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY);
	}
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAlgebraView printing

BOOL CAlgebraView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAlgebraView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAlgebraView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAlgebraView diagnostics

#ifdef _DEBUG
void CAlgebraView::AssertValid() const
{
	CView::AssertValid();
}

void CAlgebraView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAlgebraDoc* CAlgebraView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAlgebraDoc)));
	return (CAlgebraDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAlgebraView message handlers

void CAlgebraView::OnBmp1() 
{
	// TODO: Add your command handler code here
	lpBitsInfo1 = LoadBmpFile("3.bmp");
	Invalidate();	
}

void CAlgebraView::OnBmp2() 
{
	// TODO: Add your command handler code here
	lpBitsInfo2 = LoadBmpFile("4.bmp");
	Invalidate();	
}

void CAlgebraView::OnBmp3() 
{
	// TODO: Add your command handler code here
	lpBitsInfo3 = Algebra(lpBitsInfo1, lpBitsInfo2);
	Invalidate();	
}

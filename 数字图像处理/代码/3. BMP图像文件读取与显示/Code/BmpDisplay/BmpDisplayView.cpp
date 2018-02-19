// BmpDisplayView.cpp : implementation of the CBmpDisplayView class
//

#include "stdafx.h"
#include "BmpDisplay.h"

#include "BmpDisplayDoc.h"
#include "BmpDisplayView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpDisplayView

IMPLEMENT_DYNCREATE(CBmpDisplayView, CView)

BEGIN_MESSAGE_MAP(CBmpDisplayView, CView)
	//{{AFX_MSG_MAP(CBmpDisplayView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpDisplayView construction/destruction

CBmpDisplayView::CBmpDisplayView()
{
	// TODO: add construction code here
}

CBmpDisplayView::~CBmpDisplayView()
{
}

BOOL CBmpDisplayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBmpDisplayView drawing

extern BITMAPINFO *lpBitsInfo;

void CBmpDisplayView::OnDraw(CDC* pDC)
{
	CBmpDisplayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (NULL == lpBitsInfo)
		return;

	/****************更改调色板*****************
	RGBQUAD pal[2];
	pal[0].rgbRed      = 255;
	pal[0].rgbGreen    = 0;
	pal[0].rgbBlue     = 0;
	pal[0].rgbReserved = 0;
	pal[1].rgbRed      = 255;
	pal[1].rgbGreen    = 255;
	pal[1].rgbBlue     = 255;
	pal[1].rgbReserved = 0;
	memcpy(lpBitsInfo->bmiColors,pal,8);
    ********************************************/

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

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBmpDisplayView printing

BOOL CBmpDisplayView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBmpDisplayView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBmpDisplayView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBmpDisplayView diagnostics

#ifdef _DEBUG
void CBmpDisplayView::AssertValid() const
{
	CView::AssertValid();
}

void CBmpDisplayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBmpDisplayDoc* CBmpDisplayView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpDisplayDoc)));
	return (CBmpDisplayDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmpDisplayView message handlers

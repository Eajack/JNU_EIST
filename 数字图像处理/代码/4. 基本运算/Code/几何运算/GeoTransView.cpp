// GeoTransView.cpp : implementation of the CGeoTransView class
//

#include "stdafx.h"
#include "GeoTrans.h"

#include "GeoTransDoc.h"
#include "GeoTransView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeoTransView

IMPLEMENT_DYNCREATE(CGeoTransView, CView)

BEGIN_MESSAGE_MAP(CGeoTransView, CView)
	//{{AFX_MSG_MAP(CGeoTransView)
	ON_COMMAND(ID_ZOOM, OnZoom)
	ON_UPDATE_COMMAND_UI(ID_ZOOM, OnUpdateZoom)
	ON_COMMAND(ID_ROTATE, OnRotate)
	ON_UPDATE_COMMAND_UI(ID_ROTATE, OnUpdateRotate)
	ON_COMMAND(ID_MIRROR, OnMirror)
	ON_UPDATE_COMMAND_UI(ID_MIRROR, OnUpdateMirror)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeoTransView construction/destruction

CGeoTransView::CGeoTransView()
{
	// TODO: add construction code here

}

CGeoTransView::~CGeoTransView()
{
}

BOOL CGeoTransView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGeoTransView drawing
extern BITMAPINFO *lpBitsInfo;

void CGeoTransView::OnDraw(CDC* pDC)
{
	CGeoTransDoc* pDoc = GetDocument();
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
// CGeoTransView printing

BOOL CGeoTransView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGeoTransView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGeoTransView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGeoTransView diagnostics

#ifdef _DEBUG
void CGeoTransView::AssertValid() const
{
	CView::AssertValid();
}

void CGeoTransView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGeoTransDoc* CGeoTransView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeoTransDoc)));
	return (CGeoTransDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGeoTransView message handlers

void Mirror();
void CGeoTransView::OnMirror() 
{
	// TODO: Add your command handler code here
	Mirror();
	Invalidate();	
}

void CGeoTransView::OnUpdateMirror(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

void Zoom(float, float);
void CGeoTransView::OnZoom() 
{
	// TODO: Add your command handler code here
	Zoom((float)1.2, (float)1.2);
	Invalidate();
}

void CGeoTransView::OnUpdateZoom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);	
}

void Rotate(int);
void CGeoTransView::OnRotate() 
{
	// TODO: Add your command handler code here
	Rotate(10);
	Invalidate();
}

void CGeoTransView::OnUpdateRotate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);	
}



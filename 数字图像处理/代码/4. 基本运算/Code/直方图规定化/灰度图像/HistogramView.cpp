// HistogramView.cpp : implementation of the CHistogramView class
//

#include "stdafx.h"
#include "Histogram.h"

#include "HistogramDoc.h"
#include "HistogramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistogramView

IMPLEMENT_DYNCREATE(CHistogramView, CScrollView)

BEGIN_MESSAGE_MAP(CHistogramView, CScrollView)
	//{{AFX_MSG_MAP(CHistogramView)
	ON_COMMAND(ID_SPEC, OnSpec)
	ON_COMMAND(ID_DEST, OnDest)
	ON_COMMAND(ID_EQUA, OnEqua)
	ON_UPDATE_COMMAND_UI(ID_SPEC, OnUpdateSpec)
	ON_UPDATE_COMMAND_UI(ID_DEST, OnUpdateDest)
	ON_UPDATE_COMMAND_UI(ID_EQUA, OnUpdateEqua)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistogramView construction/destruction

CHistogramView::CHistogramView()
{
	// TODO: add construction code here

}

CHistogramView::~CHistogramView()
{
}

BOOL CHistogramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHistogramView drawing
LPBITMAPINFO lpSrc  = NULL;
LPBITMAPINFO lpEqua = NULL;
LPBITMAPINFO lpDest = NULL;
LPBITMAPINFO lpSpec = NULL;

DWORD Src_H[256];
DWORD Equa_H[256];
DWORD Dest_H[256];
DWORD Spec_H[256];

CDC dcMemSrc_H;
CDC dcMemEqua_H;
CDC dcMemDest_H;
CDC dcMemSpec_H;

void CHistogramView::OnDraw(CDC* pDC)
{
	CHistogramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	LPVOID lpBits;
	if (lpSrc)
	{
		lpBits = (LPVOID)&lpSrc->bmiColors[lpSrc->bmiHeader.biClrUsed];

		StretchDIBits( 
			pDC->GetSafeHdc(),
			0,0,
			lpSrc->bmiHeader.biWidth,
			lpSrc->bmiHeader.biHeight,
			0,0,
			lpSrc->bmiHeader.biWidth,
			lpSrc->bmiHeader.biHeight,
			lpBits, // bitmap bits 
			lpSrc, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY
			);

		pDC->BitBlt(520,8,256,200,&dcMemSrc_H,0,0,SRCCOPY);
	}

	if (lpEqua)
	{
		lpBits = (LPVOID)&lpEqua->bmiColors[lpEqua->bmiHeader.biClrUsed];

		StretchDIBits( 
			pDC->GetSafeHdc(),
			784,0,
			lpEqua->bmiHeader.biWidth,
			lpEqua->bmiHeader.biHeight,
			0,0,
			lpEqua->bmiHeader.biWidth,
			lpEqua->bmiHeader.biHeight,
			lpBits, // bitmap bits 
			lpSrc, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY
			);

		pDC->BitBlt(520,304,256,200,&dcMemEqua_H,0,0,SRCCOPY);
	}
/*
	if (lpDest)
	{
		lpBits = (LPVOID)&lpDest->bmiColors[lpDest->bmiHeader.biClrUsed];

		StretchDIBits( 
			pDC->GetSafeHdc(),
			0,520,
			lpDest->bmiHeader.biWidth,
			lpDest->bmiHeader.biHeight,
			0,0,
			lpDest->bmiHeader.biWidth,
			lpDest->bmiHeader.biHeight,
			lpBits, // bitmap bits 
			lpDest, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY
			);

		pDC->BitBlt(520,528,256,200,&dcMemDest_H,0,0,SRCCOPY);
	}
*/
	pDC->BitBlt(520,528,256,200,&dcMemDest_H,0,0,SRCCOPY);

	if (lpSpec)
	{
		lpBits = (LPVOID)&lpSpec->bmiColors[lpSpec->bmiHeader.biClrUsed];

		StretchDIBits( 
			pDC->GetSafeHdc(),
			784,520,
			lpSpec->bmiHeader.biWidth,
			lpSpec->bmiHeader.biHeight,
			0,0,
			lpSpec->bmiHeader.biWidth,
			lpSpec->bmiHeader.biHeight,
			lpBits, // bitmap bits 
			lpSpec, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY
			);

		pDC->BitBlt(520,824,256,200,&dcMemSpec_H,0,0,SRCCOPY);
	}
}

void CHistogramView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 1300;
	sizeTotal.cy = 1200;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CHistogramView printing

BOOL CHistogramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHistogramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHistogramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHistogramView diagnostics

#ifdef _DEBUG
void CHistogramView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CHistogramView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CHistogramDoc* CHistogramView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHistogramDoc)));
	return (CHistogramDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHistogramView message handlers
BITMAPINFO* LoadBmpFile(char* BmpFileName);

void Equalize(LPBITMAPINFO lpDIB);
void Specify(LPBITMAPINFO lpDIB, DWORD dst[]);

void Histogram(LPBITMAPINFO lpDIB, DWORD H[]);
void DrawHistogram(CDC& dcMem, DWORD H[]);

extern LONG size;

void CHistogramView::OnEqua() 
{
	// TODO: Add your command handler code here

	//复制原图像到均衡化图像
	lpEqua = (LPBITMAPINFO)malloc(size);
	memcpy(lpEqua, lpSrc, size);

	//均衡化
	Equalize(lpEqua);

	//计算均衡化图像的直方图
	Histogram(lpEqua, Equa_H);

	//（在内存中）绘制均衡化图像的直方图
	DrawHistogram(dcMemEqua_H, Equa_H);
	Invalidate();
}

void CHistogramView::OnDest() 
{
	// TODO: Add your command handler code here

	//加载规定图像（指定直方图）
//	lpDest = LoadBmpFile("规定化.bmp");

	//计算规定图像的直方图
//	Histogram(lpDest, Dest_H);
	int i;
	DWORD sum = 0;
	for (i = 0; i < 256; i ++)
	{
		Dest_H[i] = 255 - i;
		sum = sum + Dest_H[i];
	}
	for (i = 0; i < 256; i ++)
	{
		double t = 512*512 / sum;
		Dest_H[i] = (DWORD)(Dest_H[i] * t);
	}

	//（在内存中）绘制规定图像的直方图
	DrawHistogram(dcMemDest_H, Dest_H);
	Invalidate();
}

void CHistogramView::OnSpec() 
{
	// TODO: Add your command handler code here
	//复制原图像到规定化图像
	lpSpec = (LPBITMAPINFO)malloc(size);
	memcpy(lpSpec, lpSrc, size);

	//规定化
	Specify(lpSpec, Dest_H);

	//计算规定化后图像的直方图
	Histogram(lpSpec, Spec_H);

	//（在内存中）绘制均衡化图像的直方图
	DrawHistogram(dcMemSpec_H, Spec_H);
	Invalidate();	
}

void CHistogramView::OnUpdateSpec(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->Enable(NULL != lpDest);
}

void CHistogramView::OnUpdateDest(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(NULL != lpSrc);
}

void CHistogramView::OnUpdateEqua(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(NULL != lpSrc);
}

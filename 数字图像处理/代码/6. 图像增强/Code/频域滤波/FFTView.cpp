// FFTView.cpp : implementation of the CFFTView class
//

#include "stdafx.h"
#include "FFT.h"

#include "FFTDoc.h"
#include "FFTView.h"
#include "FilterParaDlg.h"

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
	ON_COMMAND(ID_IFFT, OnIfft)
	ON_UPDATE_COMMAND_UI(ID_IFFT, OnUpdateIfft)
	ON_COMMAND(ID_FFT, OnFft)
	ON_UPDATE_COMMAND_UI(ID_FFT, OnUpdateFft)
	ON_COMMAND(ID_CHANGE_FD, OnChangeFd)
	ON_UPDATE_COMMAND_UI(ID_CHANGE_FD, OnUpdateChangeFd)
	ON_COMMAND(ID_BUTTERWORTH_FILTER, OnButterworthFilter)
	ON_UPDATE_COMMAND_UI(ID_BUTTERWORTH_FILTER, OnUpdateButterworthFilter)
	ON_COMMAND(ID_GAUSS_FILTER, OnGaussFilter)
	ON_UPDATE_COMMAND_UI(ID_GAUSS_FILTER, OnUpdateGaussFilter)
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
extern BITMAPINFO *lpDIB_IFFT;

CFFTView::~CFFTView()
{
	if (lpDIB) delete lpDIB;
	if (lpDIB_FFT) delete lpDIB_FFT;
	if (lpDIB_IFFT) delete lpDIB_IFFT;
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

	if (lpDIB_IFFT)
	{
		lpBits = (LPVOID)&lpDIB_IFFT->bmiColors[lpDIB_IFFT->bmiHeader.biClrUsed];
		StretchDIBits( 
			pDC->GetSafeHdc(),
			0,600,
			lpDIB_IFFT->bmiHeader.biWidth,
			lpDIB_IFFT->bmiHeader.biHeight,
			0,0,
			lpDIB_IFFT->bmiHeader.biWidth,
			lpDIB_IFFT->bmiHeader.biHeight,
			lpBits,
			lpDIB_IFFT, // bitmap data 
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

BITMAPINFO* FFT_Image();
BITMAPINFO* IFFT_Image();

void Ideal_Filter_FFT(int);
void Butterworth_Filter_FFT(int);
void Gauss_Filter_FFT(int);

void CFFTView::OnFft() 
{
	// TODO: Add your command handler code here
	if (lpDIB_FFT)
		free(lpDIB_FFT);

	lpDIB_FFT = FFT_Image();
	Invalidate();
}

void CFFTView::OnUpdateFft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB != NULL);	
}

static BOOL bFlag = TRUE;
void CFFTView::OnIfft() 
{
	// TODO: Add your command handler code here
	if (lpDIB_IFFT)
		free(lpDIB_IFFT);

	lpDIB_IFFT = IFFT_Image();

	bFlag = FALSE;

	Invalidate();
}

void CFFTView::OnUpdateIfft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB_FFT != NULL && bFlag);		
}

void CFFTView::OnChangeFd() 
{
	// TODO: Add your command handler code here
	CFilterParaDlg dlg;
	if (IDOK == dlg.DoModal())
		Ideal_Filter_FFT(dlg.m_nDis);
	Invalidate();
}

void CFFTView::OnUpdateChangeFd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB_FFT != NULL && !bFlag);
}

void CFFTView::OnButterworthFilter() 
{
	// TODO: Add your command handler code here
	CFilterParaDlg dlg;
	if (IDOK == dlg.DoModal())
		Butterworth_Filter_FFT(dlg.m_nDis);
	Invalidate();	
}

void CFFTView::OnUpdateButterworthFilter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB_FFT != NULL && !bFlag);
}

void CFFTView::OnGaussFilter() 
{
	// TODO: Add your command handler code here
	CFilterParaDlg dlg;
	if (IDOK == dlg.DoModal())
		Gauss_Filter_FFT(dlg.m_nDis);
	Invalidate();	
}

void CFFTView::OnUpdateGaussFilter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB_FFT != NULL && !bFlag);	
}

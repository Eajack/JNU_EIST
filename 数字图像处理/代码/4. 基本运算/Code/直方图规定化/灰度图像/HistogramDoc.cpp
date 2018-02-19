// HistogramDoc.cpp : implementation of the CHistogramDoc class
//

#include "stdafx.h"
#include "Histogram.h"

#include "HistogramDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistogramDoc

IMPLEMENT_DYNCREATE(CHistogramDoc, CDocument)

BEGIN_MESSAGE_MAP(CHistogramDoc, CDocument)
	//{{AFX_MSG_MAP(CHistogramDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistogramDoc construction/destruction

CHistogramDoc::CHistogramDoc()
{
	// TODO: add one-time construction code here

}

CHistogramDoc::~CHistogramDoc()
{
}

BOOL CHistogramDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHistogramDoc serialization

void CHistogramDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHistogramDoc diagnostics

#ifdef _DEBUG
void CHistogramDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHistogramDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHistogramDoc commands

extern BITMAPINFO* lpSrc;
extern DWORD Src_H[256];
extern CDC dcMemSrc_H;

BITMAPINFO* LoadBmpFile(char* BmpFileName);
void Histogram(LPBITMAPINFO lpDIB, DWORD H[]);
void DrawHistogram(CDC& dcMem, DWORD H[]);

BOOL CHistogramDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here

	//加载原始图像
	lpSrc = LoadBmpFile((char*) lpszPathName);

	//计算原始图像的直方图
	Histogram(lpSrc, Src_H);

	//（在内存中）绘制原始图像的直方图
	DrawHistogram(dcMemSrc_H, Src_H);

	return TRUE;
}

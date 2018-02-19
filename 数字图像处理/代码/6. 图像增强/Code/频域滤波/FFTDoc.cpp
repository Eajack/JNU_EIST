// FFTDoc.cpp : implementation of the CFFTDoc class
//

#include "stdafx.h"
#include "FFT.h"

#include "FFTDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFFTDoc

IMPLEMENT_DYNCREATE(CFFTDoc, CDocument)

BEGIN_MESSAGE_MAP(CFFTDoc, CDocument)
	//{{AFX_MSG_MAP(CFFTDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFFTDoc construction/destruction

CFFTDoc::CFFTDoc()
{
	// TODO: add one-time construction code here

}

CFFTDoc::~CFFTDoc()
{
}

BOOL CFFTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFFTDoc serialization

void CFFTDoc::Serialize(CArchive& ar)
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
// CFFTDoc diagnostics

#ifdef _DEBUG
void CFFTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFFTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFFTDoc commands

BOOL LoadBmpFile(char* BmpFileName);

BOOL CFFTDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	LoadBmpFile((char*)lpszPathName);
	
	return TRUE;
}
// SFilterDoc.cpp : implementation of the CSFilterDoc class
//

#include "stdafx.h"
#include "SFilter.h"

#include "SFilterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSFilterDoc

IMPLEMENT_DYNCREATE(CSFilterDoc, CDocument)

BEGIN_MESSAGE_MAP(CSFilterDoc, CDocument)
	//{{AFX_MSG_MAP(CSFilterDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSFilterDoc construction/destruction

CSFilterDoc::CSFilterDoc()
{
	// TODO: add one-time construction code here

}

CSFilterDoc::~CSFilterDoc()
{
}

BOOL CSFilterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSFilterDoc serialization

void CSFilterDoc::Serialize(CArchive& ar)
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
// CSFilterDoc diagnostics

#ifdef _DEBUG
void CSFilterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSFilterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSFilterDoc commands
BOOL LoadBmpFile(char* BmpFileName);

BOOL CSFilterDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	LoadBmpFile((char*)lpszPathName);

	return TRUE;
}

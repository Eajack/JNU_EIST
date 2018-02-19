// BmpDisplayDoc.cpp : implementation of the CBmpDisplayDoc class
//

#include "stdafx.h"
#include "BmpDisplay.h"

#include "BmpDisplayDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpDisplayDoc

IMPLEMENT_DYNCREATE(CBmpDisplayDoc, CDocument)

BEGIN_MESSAGE_MAP(CBmpDisplayDoc, CDocument)
	//{{AFX_MSG_MAP(CBmpDisplayDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpDisplayDoc construction/destruction

CBmpDisplayDoc::CBmpDisplayDoc()
{
	// TODO: add one-time construction code here

}

CBmpDisplayDoc::~CBmpDisplayDoc()
{
}

BOOL CBmpDisplayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBmpDisplayDoc serialization

void CBmpDisplayDoc::Serialize(CArchive& ar)
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
// CBmpDisplayDoc diagnostics

#ifdef _DEBUG
void CBmpDisplayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBmpDisplayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmpDisplayDoc commands

BOOL LoadBmpFile(char* BmpFileName);

BOOL CBmpDisplayDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	LoadBmpFile((char*)lpszPathName);

	return TRUE;
}

// GeoTransDoc.cpp : implementation of the CGeoTransDoc class
//

#include "stdafx.h"
#include "GeoTrans.h"

#include "GeoTransDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeoTransDoc

IMPLEMENT_DYNCREATE(CGeoTransDoc, CDocument)

BEGIN_MESSAGE_MAP(CGeoTransDoc, CDocument)
	//{{AFX_MSG_MAP(CGeoTransDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeoTransDoc construction/destruction

CGeoTransDoc::CGeoTransDoc()
{
	// TODO: add one-time construction code here

}

CGeoTransDoc::~CGeoTransDoc()
{
}

BOOL CGeoTransDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGeoTransDoc serialization

void CGeoTransDoc::Serialize(CArchive& ar)
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
// CGeoTransDoc diagnostics

#ifdef _DEBUG
void CGeoTransDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGeoTransDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGeoTransDoc commands
BOOL LoadBmpFile(char* BmpFileName);

BOOL CGeoTransDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here

	LoadBmpFile((char*)lpszPathName);
	
	return TRUE;
}

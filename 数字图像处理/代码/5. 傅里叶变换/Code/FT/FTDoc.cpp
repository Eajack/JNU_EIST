// FTDoc.cpp : implementation of the CFTDoc class
//

#include "stdafx.h"
#include "FT.h"

#include "FTDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTDoc

IMPLEMENT_DYNCREATE(CFTDoc, CDocument)

BEGIN_MESSAGE_MAP(CFTDoc, CDocument)
	//{{AFX_MSG_MAP(CFTDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTDoc construction/destruction

CFTDoc::CFTDoc()
{
	// TODO: add one-time construction code here

}

CFTDoc::~CFTDoc()
{
}

BOOL CFTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFTDoc serialization

void CFTDoc::Serialize(CArchive& ar)
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
// CFTDoc diagnostics

#ifdef _DEBUG
void CFTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFTDoc commands
BOOL LoadBmpFile(char* BmpFileName);

BOOL CFTDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here

	LoadBmpFile((char*)lpszPathName);

	return TRUE;
}

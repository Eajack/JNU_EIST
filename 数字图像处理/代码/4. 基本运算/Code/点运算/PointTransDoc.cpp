// PointTransDoc.cpp : implementation of the CPointTransDoc class
//

#include "stdafx.h"
#include "PointTrans.h"

#include "PointTransDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointTransDoc

IMPLEMENT_DYNCREATE(CPointTransDoc, CDocument)

BEGIN_MESSAGE_MAP(CPointTransDoc, CDocument)
	//{{AFX_MSG_MAP(CPointTransDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointTransDoc construction/destruction

CPointTransDoc::CPointTransDoc()
{
	// TODO: add one-time construction code here

}

CPointTransDoc::~CPointTransDoc()
{
}

BOOL CPointTransDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPointTransDoc serialization

void CPointTransDoc::Serialize(CArchive& ar)
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
// CPointTransDoc diagnostics

#ifdef _DEBUG
void CPointTransDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPointTransDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPointTransDoc commands
BOOL LoadBmpFile(char* BmpFileName);

BOOL CPointTransDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here

	LoadBmpFile((char*)lpszPathName);

	return TRUE;
}

// AlgebraDoc.cpp : implementation of the CAlgebraDoc class
//

#include "stdafx.h"
#include "Algebra.h"

#include "AlgebraDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlgebraDoc

IMPLEMENT_DYNCREATE(CAlgebraDoc, CDocument)

BEGIN_MESSAGE_MAP(CAlgebraDoc, CDocument)
	//{{AFX_MSG_MAP(CAlgebraDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlgebraDoc construction/destruction

CAlgebraDoc::CAlgebraDoc()
{
	// TODO: add one-time construction code here

}

CAlgebraDoc::~CAlgebraDoc()
{
}

BOOL CAlgebraDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAlgebraDoc serialization

void CAlgebraDoc::Serialize(CArchive& ar)
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
// CAlgebraDoc diagnostics

#ifdef _DEBUG
void CAlgebraDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAlgebraDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAlgebraDoc commands

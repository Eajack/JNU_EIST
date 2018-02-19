// AlgebraDoc.h : interface of the CAlgebraDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALGEBRADOC_H__E4C3D6A0_59F3_4295_BBDF_6C580CB2A009__INCLUDED_)
#define AFX_ALGEBRADOC_H__E4C3D6A0_59F3_4295_BBDF_6C580CB2A009__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAlgebraDoc : public CDocument
{
protected: // create from serialization only
	CAlgebraDoc();
	DECLARE_DYNCREATE(CAlgebraDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlgebraDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAlgebraDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAlgebraDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALGEBRADOC_H__E4C3D6A0_59F3_4295_BBDF_6C580CB2A009__INCLUDED_)

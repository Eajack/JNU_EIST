// PointTransDoc.h : interface of the CPointTransDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTTRANSDOC_H__52B229C6_358D_459C_BC1E_5F0EFD3D13D6__INCLUDED_)
#define AFX_POINTTRANSDOC_H__52B229C6_358D_459C_BC1E_5F0EFD3D13D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPointTransDoc : public CDocument
{
protected: // create from serialization only
	CPointTransDoc();
	DECLARE_DYNCREATE(CPointTransDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointTransDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPointTransDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPointTransDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTTRANSDOC_H__52B229C6_358D_459C_BC1E_5F0EFD3D13D6__INCLUDED_)

// SFilterDoc.h : interface of the CSFilterDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SFILTERDOC_H__18B31C33_8FB2_437D_94E6_5F794E542171__INCLUDED_)
#define AFX_SFILTERDOC_H__18B31C33_8FB2_437D_94E6_5F794E542171__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSFilterDoc : public CDocument
{
protected: // create from serialization only
	CSFilterDoc();
	DECLARE_DYNCREATE(CSFilterDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSFilterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSFilterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSFilterDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFILTERDOC_H__18B31C33_8FB2_437D_94E6_5F794E542171__INCLUDED_)

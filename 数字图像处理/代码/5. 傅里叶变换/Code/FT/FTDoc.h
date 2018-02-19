// FTDoc.h : interface of the CFTDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTDOC_H__2DA84293_F49B_40A2_A71A_06614CA7A54D__INCLUDED_)
#define AFX_FTDOC_H__2DA84293_F49B_40A2_A71A_06614CA7A54D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFTDoc : public CDocument
{
protected: // create from serialization only
	CFTDoc();
	DECLARE_DYNCREATE(CFTDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFTDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTDOC_H__2DA84293_F49B_40A2_A71A_06614CA7A54D__INCLUDED_)

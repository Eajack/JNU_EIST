// BmpDisplayDoc.h : interface of the CBmpDisplayDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPDISPLAYDOC_H__B25F2486_A65B_427F_8586_496AD15175AF__INCLUDED_)
#define AFX_BMPDISPLAYDOC_H__B25F2486_A65B_427F_8586_496AD15175AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBmpDisplayDoc : public CDocument
{
protected: // create from serialization only
	CBmpDisplayDoc();
	DECLARE_DYNCREATE(CBmpDisplayDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpDisplayDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBmpDisplayDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBmpDisplayDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPDISPLAYDOC_H__B25F2486_A65B_427F_8586_496AD15175AF__INCLUDED_)

// GeoTransDoc.h : interface of the CGeoTransDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOTRANSDOC_H__8FD05D7F_2F13_4A36_A917_F63C54918B10__INCLUDED_)
#define AFX_GEOTRANSDOC_H__8FD05D7F_2F13_4A36_A917_F63C54918B10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGeoTransDoc : public CDocument
{
protected: // create from serialization only
	CGeoTransDoc();
	DECLARE_DYNCREATE(CGeoTransDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoTransDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGeoTransDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGeoTransDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEOTRANSDOC_H__8FD05D7F_2F13_4A36_A917_F63C54918B10__INCLUDED_)

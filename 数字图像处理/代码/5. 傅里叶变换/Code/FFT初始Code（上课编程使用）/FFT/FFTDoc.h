// FFTDoc.h : interface of the CFFTDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FFTDOC_H__31EA486A_D191_4677_8C13_0BD66BA4A0F2__INCLUDED_)
#define AFX_FFTDOC_H__31EA486A_D191_4677_8C13_0BD66BA4A0F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFFTDoc : public CDocument
{
protected: // create from serialization only
	CFFTDoc();
	DECLARE_DYNCREATE(CFFTDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFFTDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFFTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFFTDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFTDOC_H__31EA486A_D191_4677_8C13_0BD66BA4A0F2__INCLUDED_)

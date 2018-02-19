// FFTView.h : interface of the CFFTView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FFTVIEW_H__319F4E07_AB0C_4B9C_A17A_095DC62E36F2__INCLUDED_)
#define AFX_FFTVIEW_H__319F4E07_AB0C_4B9C_A17A_095DC62E36F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFFTView : public CView
{
protected: // create from serialization only
	CFFTView();
	DECLARE_DYNCREATE(CFFTView)

// Attributes
public:
	CFFTDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFFTView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFFTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFFTView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FFTView.cpp
inline CFFTDoc* CFFTView::GetDocument()
   { return (CFFTDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFTVIEW_H__319F4E07_AB0C_4B9C_A17A_095DC62E36F2__INCLUDED_)

// AlgebraView.h : interface of the CAlgebraView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALGEBRAVIEW_H__57A47B37_EEBB_4CFC_884D_C43AF78F8CFC__INCLUDED_)
#define AFX_ALGEBRAVIEW_H__57A47B37_EEBB_4CFC_884D_C43AF78F8CFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAlgebraView : public CView
{
protected: // create from serialization only
	CAlgebraView();
	DECLARE_DYNCREATE(CAlgebraView)

// Attributes
public:
	CAlgebraDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlgebraView)
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
	virtual ~CAlgebraView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAlgebraView)
	afx_msg void OnBmp1();
	afx_msg void OnBmp2();
	afx_msg void OnBmp3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AlgebraView.cpp
inline CAlgebraDoc* CAlgebraView::GetDocument()
   { return (CAlgebraDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALGEBRAVIEW_H__57A47B37_EEBB_4CFC_884D_C43AF78F8CFC__INCLUDED_)

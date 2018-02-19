// FTView.h : interface of the CFTView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTVIEW_H__3A77C871_5D9B_4490_B168_ACB492A7B166__INCLUDED_)
#define AFX_FTVIEW_H__3A77C871_5D9B_4490_B168_ACB492A7B166__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFTView : public CView
{
protected: // create from serialization only
	CFTView();
	DECLARE_DYNCREATE(CFTView)

// Attributes
public:
	CFTDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTView)
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
	virtual ~CFTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFTView)
	afx_msg void OnFourier();
	afx_msg void OnIFourier();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FTView.cpp
inline CFTDoc* CFTView::GetDocument()
   { return (CFTDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTVIEW_H__3A77C871_5D9B_4490_B168_ACB492A7B166__INCLUDED_)

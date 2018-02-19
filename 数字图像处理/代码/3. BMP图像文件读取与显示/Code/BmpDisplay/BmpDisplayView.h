// BmpDisplayView.h : interface of the CBmpDisplayView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPDISPLAYVIEW_H__8E5BEB2F_C538_4A4B_A36C_E6FC392D006D__INCLUDED_)
#define AFX_BMPDISPLAYVIEW_H__8E5BEB2F_C538_4A4B_A36C_E6FC392D006D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBmpDisplayView : public CView
{
protected: // create from serialization only
	CBmpDisplayView();
	DECLARE_DYNCREATE(CBmpDisplayView)

// Attributes
public:
	CBmpDisplayDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpDisplayView)
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
	virtual ~CBmpDisplayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBmpDisplayView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BmpDisplayView.cpp
inline CBmpDisplayDoc* CBmpDisplayView::GetDocument()
   { return (CBmpDisplayDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPDISPLAYVIEW_H__8E5BEB2F_C538_4A4B_A36C_E6FC392D006D__INCLUDED_)

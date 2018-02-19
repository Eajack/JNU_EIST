// PointTransView.h : interface of the CPointTransView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTTRANSVIEW_H__63D9F254_ABF1_4163_8A88_354824B0B1A6__INCLUDED_)
#define AFX_POINTTRANSVIEW_H__63D9F254_ABF1_4163_8A88_354824B0B1A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPointTransView : public CView
{
protected: // create from serialization only
	CPointTransView();
	DECLARE_DYNCREATE(CPointTransView)

// Attributes
public:
	CPointTransDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointTransView)
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
	virtual ~CPointTransView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPointTransView)
	afx_msg void OnLinetrans();
	afx_msg void OnHisDiagram();
	afx_msg void OnUpdateLinetrans(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHisDiagram(CCmdUI* pCmdUI);
	afx_msg void OnEqualize();
	afx_msg void OnUpdateEqualize(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PointTransView.cpp
inline CPointTransDoc* CPointTransView::GetDocument()
   { return (CPointTransDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTTRANSVIEW_H__63D9F254_ABF1_4163_8A88_354824B0B1A6__INCLUDED_)

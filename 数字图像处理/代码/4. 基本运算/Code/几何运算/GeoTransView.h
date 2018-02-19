// GeoTransView.h : interface of the CGeoTransView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOTRANSVIEW_H__2F99943A_E0F0_4343_BFC9_B01C06314799__INCLUDED_)
#define AFX_GEOTRANSVIEW_H__2F99943A_E0F0_4343_BFC9_B01C06314799__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGeoTransView : public CView
{
protected: // create from serialization only
	CGeoTransView();
	DECLARE_DYNCREATE(CGeoTransView)

// Attributes
public:
	CGeoTransDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoTransView)
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
	virtual ~CGeoTransView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGeoTransView)
	afx_msg void OnZoom();
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnRotate();
	afx_msg void OnUpdateRotate(CCmdUI* pCmdUI);
	afx_msg void OnMirror();
	afx_msg void OnUpdateMirror(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GeoTransView.cpp
inline CGeoTransDoc* CGeoTransView::GetDocument()
   { return (CGeoTransDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEOTRANSVIEW_H__2F99943A_E0F0_4343_BFC9_B01C06314799__INCLUDED_)

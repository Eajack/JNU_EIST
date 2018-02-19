// PointTrans.h : main header file for the POINTTRANS application
//

#if !defined(AFX_POINTTRANS_H__4DF7FF48_340A_4BDC_9894_138EAED0E1D8__INCLUDED_)
#define AFX_POINTTRANS_H__4DF7FF48_340A_4BDC_9894_138EAED0E1D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPointTransApp:
// See PointTrans.cpp for the implementation of this class
//

class CPointTransApp : public CWinApp
{
public:
	CPointTransApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointTransApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPointTransApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTTRANS_H__4DF7FF48_340A_4BDC_9894_138EAED0E1D8__INCLUDED_)

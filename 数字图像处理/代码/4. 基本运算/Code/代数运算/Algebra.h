// Algebra.h : main header file for the ALGEBRA application
//

#if !defined(AFX_ALGEBRA_H__057CC8D4_E677_4608_86AF_BD75A7C8138C__INCLUDED_)
#define AFX_ALGEBRA_H__057CC8D4_E677_4608_86AF_BD75A7C8138C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAlgebraApp:
// See Algebra.cpp for the implementation of this class
//

class CAlgebraApp : public CWinApp
{
public:
	CAlgebraApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlgebraApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAlgebraApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALGEBRA_H__057CC8D4_E677_4608_86AF_BD75A7C8138C__INCLUDED_)

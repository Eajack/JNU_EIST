// SFilter.h : main header file for the SFILTER application
//

#if !defined(AFX_SFILTER_H__99840013_2A44_4AF7_992E_83DCF94C91AE__INCLUDED_)
#define AFX_SFILTER_H__99840013_2A44_4AF7_992E_83DCF94C91AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSFilterApp:
// See SFilter.cpp for the implementation of this class
//

class CSFilterApp : public CWinApp
{
public:
	CSFilterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSFilterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSFilterApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFILTER_H__99840013_2A44_4AF7_992E_83DCF94C91AE__INCLUDED_)

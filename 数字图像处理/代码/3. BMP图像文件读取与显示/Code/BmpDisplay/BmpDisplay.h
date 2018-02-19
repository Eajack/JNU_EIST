// BmpDisplay.h : main header file for the BMPDISPLAY application
//

#if !defined(AFX_BMPDISPLAY_H__DFE488A4_53DA_4C98_9C1C_57791822B40E__INCLUDED_)
#define AFX_BMPDISPLAY_H__DFE488A4_53DA_4C98_9C1C_57791822B40E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBmpDisplayApp:
// See BmpDisplay.cpp for the implementation of this class
//

class CBmpDisplayApp : public CWinApp
{
public:
	CBmpDisplayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpDisplayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBmpDisplayApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPDISPLAY_H__DFE488A4_53DA_4C98_9C1C_57791822B40E__INCLUDED_)

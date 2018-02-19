// GeoTrans.h : main header file for the GEOTRANS application
//

#if !defined(AFX_GEOTRANS_H__7FD6A82B_B952_42BF_9148_2D37613D61B2__INCLUDED_)
#define AFX_GEOTRANS_H__7FD6A82B_B952_42BF_9148_2D37613D61B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGeoTransApp:
// See GeoTrans.cpp for the implementation of this class
//

class CGeoTransApp : public CWinApp
{
public:
	CGeoTransApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeoTransApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGeoTransApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEOTRANS_H__7FD6A82B_B952_42BF_9148_2D37613D61B2__INCLUDED_)

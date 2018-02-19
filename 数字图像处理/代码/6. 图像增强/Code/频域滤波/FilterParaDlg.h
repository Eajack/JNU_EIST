#if !defined(AFX_FILTERPARADLG_H__9A74926B_058A_40FE_B408_03DFD29D1648__INCLUDED_)
#define AFX_FILTERPARADLG_H__9A74926B_058A_40FE_B408_03DFD29D1648__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilterParaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilterParaDlg dialog

class CFilterParaDlg : public CDialog
{
// Construction
public:
	CFilterParaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFilterParaDlg)
	enum { IDD = IDD_DIALOG1 };
	int		m_nDis;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterParaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilterParaDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERPARADLG_H__9A74926B_058A_40FE_B408_03DFD29D1648__INCLUDED_)

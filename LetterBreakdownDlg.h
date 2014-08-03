#if !defined(AFX_LETTERBREAKDOWNDLG_H__B23B28E1_6B56_11D7_8E77_C05955C10000__INCLUDED_)
#define AFX_LETTERBREAKDOWNDLG_H__B23B28E1_6B56_11D7_8E77_C05955C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LetterBreakdownDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLetterBreakdownDlg dialog

class CLetterBreakdownDlg : public CDialog
{
// Construction
public:
	CLetterBreakdownDlg(CWnd* pParent = NULL);   // standard constructor

	void SetText(const CString &text) const;
// Dialog Data
	//{{AFX_DATA(CLetterBreakdownDlg)
	enum { IDD = IDD_LETTERBREAKDOWNDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLetterBreakdownDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLetterBreakdownDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LETTERBREAKDOWNDLG_H__B23B28E1_6B56_11D7_8E77_C05955C10000__INCLUDED_)

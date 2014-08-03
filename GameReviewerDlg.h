#if !defined(AFX_GAMEREVIEWERDLG_H__21BDFE83_70DA_11D7_8E77_F07455C10000__INCLUDED_)
#define AFX_GAMEREVIEWERDLG_H__21BDFE83_70DA_11D7_8E77_F07455C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameReviewerDlg.h : header file
//

#include "WrabbleGameHistory.h"
#include "WrabbleDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CGameReviewerDlg dialog

class CGameReviewerDlg : public CDialog
{
// Construction
public:
	CGameReviewerDlg(CWrabbleDlg *p, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGameReviewerDlg)
	enum { IDD = IDD_GAMEREVIEWERDLG };
	CListBox	m_gamelist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameReviewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	ExArray<WrabbleGameHistory> gamehistories;
	CWrabbleDlg *pdlg;

	int currentstep;

	// Generated message map functions
	//{{AFX_MSG(CGameReviewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeGamelist();
	afx_msg void OnGamestep();
	afx_msg void OnReviewfindbestplays();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEREVIEWERDLG_H__21BDFE83_70DA_11D7_8E77_F07455C10000__INCLUDED_)

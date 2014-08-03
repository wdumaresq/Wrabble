// WrabbleDlg.h : header file
//

#if !defined(AFX_WRABBLEDLG_H__DD93C3E7_6457_11D7_8E77_E06F55C10000__INCLUDED_)
#define AFX_WRABBLEDLG_H__DD93C3E7_6457_11D7_8E77_E06F55C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WrabbleBoard.h"
#include "gridctrl_src/gridctrl.h"
#include "ExArray.h"
#include "Dictionary.h"
#include "WrabbleLetterBag.h"
#include "LetterBreakdownDlg.h"
#include "WrabbleGameHistory.h"

/////////////////////////////////////////////////////////////////////////////
// CWrabbleDlg dialog



class CWrabbleDlg : public CDialog
{

	friend class CGameReviewerDlg;

// Construction
public:
	CWrabbleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWrabbleDlg)
	enum { IDD = IDD_WRABBLE_DIALOG };
	CProgressCtrl	m_progress;
	CListCtrl	m_turnlog;
	CGridCtrl	m_grid;
	CGridCtrl   m_rack2;
	int		m_acrossdownradio;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWrabbleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWrabbleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFindbestplays();
	afx_msg void OnStartgame();
	afx_msg void OnHiderack1();
	afx_msg void OnDblClickGrid(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickRack2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRightClickRack2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPass();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnNumlettersleft();
	afx_msg void OnGameReviewer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	void InitializeGameConditions();

	void DrawBoard();
	void FindBestPlays(const CString &rack, CStringList &words, ExArray<int> &xlocs,
						ExArray<int> &ylocs, 
						ExArray<int> &acrossdown,
						ExArray<int> &values);

	BOOL playWord(int turn, const CString &word, int col, int row, int hv);

	void putWordOnBoard(const CString &word, int row, int col, int hv,
								 CString &lettersused, BOOL reallyputletterson = TRUE);


	void exchangeLetters(int turn, CString &letters, BOOL throwback);

	void ComputerPlay();
	void SetTurnPointer(int turn);
	void Pass(int turn);

	void AddTurnLogEntry(const CString &word, int value, int score, int turn = 0);
	void EndGame();

	void GetRack2(CString &rack) const;
	void SetRack2(const CString &rack);
	int oldrackclick;

	CDictionary dictionary;
	WrabbleBoard board;
	WrabbleLetterBag letterbag;
	int passcount;
	int turnlogpointer;

	BOOL gameinprogress, reviewinprogress;
	BOOL computerturn;

	// clock-related members
	long time1, time2;
	time_t reftime1, reftime2;
	BOOL running1, running2;

	void Stop1(time_t &time);
	void Stop2(time_t &time);
	void UpdateTimeDisplays();

	void OnReset();
	void OnStart1();
	void OnStop();
	void OnStart2();

	CLetterBreakdownDlg lettersleftdlg;

	WrabbleGameHistory gamelog;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRABBLEDLG_H__DD93C3E7_6457_11D7_8E77_E06F55C10000__INCLUDED_)

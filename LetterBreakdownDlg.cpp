// LetterBreakdownDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Wrabble.h"
#include "LetterBreakdownDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLetterBreakdownDlg dialog


CLetterBreakdownDlg::CLetterBreakdownDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLetterBreakdownDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLetterBreakdownDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLetterBreakdownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLetterBreakdownDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLetterBreakdownDlg, CDialog)
	//{{AFX_MSG_MAP(CLetterBreakdownDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLetterBreakdownDlg message handlers


void CLetterBreakdownDlg::SetText(const CString &text) const
{

	this->GetDlgItem(IDC_LETTERSDISPLAY)->SetWindowText(text);


}
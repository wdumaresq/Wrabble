// GameReviewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Wrabble.h"
#include "GameReviewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameReviewerDlg dialog


CGameReviewerDlg::CGameReviewerDlg(CWrabbleDlg *p, CWnd* pParent /*=NULL*/)
	: pdlg(p), CDialog(CGameReviewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGameReviewerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGameReviewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameReviewerDlg)
	DDX_Control(pDX, IDC_GAMELIST, m_gamelist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGameReviewerDlg, CDialog)
	//{{AFX_MSG_MAP(CGameReviewerDlg)
	ON_LBN_SELCHANGE(IDC_GAMELIST, OnSelchangeGamelist)
	ON_BN_CLICKED(IDC_GAMESTEP, OnGamestep)
	ON_BN_CLICKED(IDC_REVIEWFINDBESTPLAYS, OnReviewfindbestplays)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameReviewerDlg message handlers

BOOL CGameReviewerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	WrabbleGameHistory::ReadFromFile("gamelogs.dat", this->gamehistories);
	
	unsigned int i;
	CString temp;
	
	for (i = 0; i < this->gamehistories.len(); i++)
	{
		temp.Format("%s vs. %s, %d-%d, Level %s, %s %s",
					this->gamehistories[i].name1,
					this->gamehistories[i].name2,
					this->gamehistories[i].score1,
					this->gamehistories[i].score2,
					this->gamehistories[i].level,
					this->gamehistories[i].date,
					this->gamehistories[i].time);

		this->m_gamelist.AddString(temp);
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGameReviewerDlg::OnSelchangeGamelist() 
{

	int nItem = this->m_gamelist.GetCurSel();
	
	if (nItem == LB_ERR)
		return;

	this->pdlg->reviewinprogress = FALSE;
	
	this->pdlg->board.init();

	unsigned int i;

	int row, col, hv;
	CString temp;

	const WrabbleGameTurn *turn;

	this->pdlg->GetDlgItem(IDC_PLAYER1NAME)->SetWindowText(this->gamehistories[nItem].name1);
	this->pdlg->GetDlgItem(IDC_PLAYER2NAME)->SetWindowText(this->gamehistories[nItem].name2);
	
	for (i = 0; i < this->gamehistories[nItem].gameturns.len(); i++)
	{
		turn = &this->gamehistories[nItem].gameturns[i];
		
		if (turn->EPW == 'W')
		{
			col = turn->pos[0] - 'A';
			row = atoi(turn->pos.Right(turn->pos.GetLength() - 1)) - 1;
			hv = turn->DA == 'A' ? ROW : COLUMN;		

			this->pdlg->putWordOnBoard(turn->word, row, col, hv, temp);
		}

	}

	this->pdlg->DrawBoard();



}

void CGameReviewerDlg::OnGamestep() 
{


	int nItem = this->m_gamelist.GetCurSel();
	
	if (nItem == LB_ERR)
		return;

	const WrabbleGameHistory *history = &this->gamehistories[nItem];
	

	if (! this->pdlg->reviewinprogress)
	{
		this->pdlg->reviewinprogress = TRUE;
		this->pdlg->InitializeGameConditions();

		// wipe out the letter bag
		this->pdlg->letterbag.getLetters(100);

		this->currentstep = 0;

		if (history->firstturn == 2)
			this->pdlg->AddTurnLogEntry("", 0, 0);
	}
	else
		this->currentstep++;

	const WrabbleGameTurn *turn;

	int currentturn = ((this->currentstep + history->firstturn) % 2) + 1;
	this->pdlg->SetTurnPointer(3 - currentturn);
	
	int row, col, hv;

	if (this->currentstep > 0)
	{
		turn = &history->gameturns[this->currentstep - 1];
	
		switch (turn->EPW)
		{
		case 'W':
			col = turn->pos[0] - 'A';
			row = atoi(turn->pos.Right(turn->pos.GetLength() - 1)) - 1;
			hv = turn->DA == 'A' ? ROW : COLUMN;		

			this->pdlg->playWord(currentturn, turn->word, col, row, hv);
			break;

		case 'E':
			this->pdlg->AddTurnLogEntry("Exchange", 0, 0);
			break;

		case 'P':
			this->pdlg->AddTurnLogEntry("Pass", 0, 0);
			break;
		}


	}

	if (this->currentstep >= history->gameturns.len())
	{
		this->pdlg->EndGame();

		this->pdlg->reviewinprogress = FALSE;
		
		/*
		CString message;
		message.Format("Final score:\r\n%s: %d\r\n%s: %d\r\n",
			history->name1, history->score1, history->name2, history->score2);
		AfxMessageBox(message);
		*/

	}
	else
	{
		turn = &history->gameturns[this->currentstep];
	
		if (currentturn == 2)
			this->pdlg->GetDlgItem(IDC_RACK1)->SetWindowText(turn->rack);
		else
			this->pdlg->SetRack2(turn->rack);

		if (this->currentstep < history->gameturns.len() - 1)
		{
			turn = &history->gameturns[this->currentstep + 1];
	
			if (currentturn == 1)
				this->pdlg->GetDlgItem(IDC_RACK1)->SetWindowText(turn->rack);
			else
				this->pdlg->SetRack2(turn->rack);

		}

	}
	
}


void CGameReviewerDlg::OnReviewfindbestplays() 
{

	this->pdlg->OnFindbestplays();	

}

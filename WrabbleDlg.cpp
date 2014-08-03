// WrabbleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Wrabble.h"
#include "WrabbleDlg.h"

#include "GameReviewerDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWrabbleDlg dialog

CWrabbleDlg::CWrabbleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWrabbleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWrabbleDlg)
	m_acrossdownradio = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWrabbleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWrabbleDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_TURNLOG, m_turnlog);
	DDX_GridControl(pDX, IDC_BOARD, m_grid);
	DDX_GridControl(pDX, IDC_RACK2, m_rack2);
	DDX_Radio(pDX, IDC_ACROSSRADIO, m_acrossdownradio);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWrabbleDlg, CDialog)
	//{{AFX_MSG_MAP(CWrabbleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FINDBESTPLAYS, OnFindbestplays)
	ON_BN_CLICKED(IDC_STARTGAME, OnStartgame)
	ON_BN_CLICKED(IDC_HIDERACK1, OnHiderack1)
	ON_NOTIFY(NM_DBLCLK, IDC_BOARD, OnDblClickGrid)
	ON_NOTIFY(NM_CLICK, IDC_RACK2, OnClickRack2)
	ON_NOTIFY(NM_RCLICK, IDC_RACK2, OnRightClickRack2)
	ON_BN_CLICKED(IDC_PASS, OnPass)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_NUMLETTERSLEFT, OnNumlettersleft)
	ON_BN_CLICKED(IDC_GAMEREVIEWER, OnGameReviewer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWrabbleDlg message handlers

BOOL CWrabbleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	this->lettersleftdlg.Create(CLetterBreakdownDlg::IDD);

	this->m_rack2.SetColumnCount(7);
	this->m_rack2.SetRowCount(1);
	this->m_rack2.SetFixedRowCount(0);
	this->m_rack2.SetFixedColumnCount(0);	

	this->m_rack2.EnableToolTips(FALSE);
	this->m_rack2.EnableTitleTips(FALSE);
	this->m_rack2.SetEditable(FALSE);
	this->m_rack2.EnableSelection(FALSE);

	this->m_rack2.ExpandToFit(FALSE);

	this->m_rack2.SetGridLineColor(RGB(160, 160, 160));


	this->m_grid.SetColumnCount(16);
	this->m_grid.SetRowCount(16);
	this->m_grid.SetFixedRowCount(1);
	this->m_grid.SetFixedColumnCount(1);	

	this->m_grid.EnableToolTips(FALSE);
	this->m_grid.EnableTitleTips(FALSE);
	this->m_grid.SetEditable(FALSE);
	this->m_grid.EnableSelection(FALSE);

	this->m_grid.SetColumnWidth(0, 25);
	this->m_grid.ExpandToFit(FALSE);




	this->m_grid.SetGridLineColor(RGB(160, 160, 160));
	

	int i;
	char temp[2], temp2[3];
	temp[1] = '\0';
	for (i = 0; i < 15; i++)
	{
		temp[0] = 'A' + i;
		this->m_grid.SetItemText(0, i + 1, temp);
		sprintf(temp2, "%d", i + 1);
		this->m_grid.SetItemText(i + 1, 0, temp2);
	}

	//this->m_grid.SetColumnWidth(0, 160);
	//this->m_grid.SetColumnWidth(1, 356);
	//this->m_grid.SetColumnWidth(2, 80);
	//this->m_grid.SetColumnWidth(3, 100);

	this->board.init();
	this->DrawBoard();

	
	this->GetDlgItem(IDC_PLAYER1NAME)->SetWindowText(AfxGetApp()->GetProfileString("GENERAL", "PLAYER1NAME", "Computer"));
	this->GetDlgItem(IDC_PLAYER2NAME)->SetWindowText(AfxGetApp()->GetProfileString("GENERAL", "PLAYER2NAME", "Player"));
	this->GetDlgItem(IDC_LEVEL)->SetWindowText(AfxGetApp()->GetProfileString("GENERAL", "LEVEL", "0"));


	this->GetDlgItem(IDC_RACK1)->ShowWindow(SW_HIDE);
	this->SetTurnPointer(0);
	

	this->gameinprogress = FALSE;
	this->reviewinprogress = FALSE;
	this->computerturn = FALSE;




	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWrabbleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWrabbleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWrabbleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CWrabbleDlg::DrawBoard()
{

	int i, j;
	char c[2];
	c[1] = '\0';
	char sp;

	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
		{
			c[0] = this->board.getLetter(i, j);

			if (c[0] == '\0')
			{
				c[0] = ' ';
				sp = this->board.getSpecial(i, j);

				switch(sp)
				{
				case '2':
					this->m_grid.SetItemBkColour(i + 1, j + 1, RGB(164, 242, 247));
					break;
				case '3':
					this->m_grid.SetItemBkColour(i + 1, j + 1, RGB(0, 0, 127));
					break;
				case '*':
					this->m_grid.SetItemBkColour(i + 1, j + 1, RGB(248, 169, 163));
					break;
				case '$':
					this->m_grid.SetItemBkColour(i + 1, j + 1, RGB(255, 0, 0));
					break;
				default:
					this->m_grid.SetItemBkColour(i + 1, j + 1, RGB(230, 230, 230));
				}
			}
			else
			{
				if (c[0] >= 'a' && c[0] <= 'z')
					this->m_grid.SetItemBkColour(i + 1, j + 1, RGB(255, 255, 0));
				
				if (c[0] >= 'A' && c[0] <= 'Z')
					this->m_grid.SetItemBkColour(i + 1, j + 1, RGB(200, 200, 0));
			
				if (this->m_grid.GetItemData(i + 1, j + 1) == 1)
				{
					this->m_grid.SetItemFgColour(i + 1, j + 1, RGB(255, 0, 0));
					this->m_grid.SetItemData(i + 1, j + 1, 0);
				}
				else
					this->m_grid.SetItemFgColour(i + 1, j + 1, RGB(0, 0, 0));
			}

			c[0] = toupper(c[0]);
			this->m_grid.SetItemText(i + 1, j + 1, c);
			
		}

	this->m_grid.Refresh();
	//this->Invalidate();

}

void CWrabbleDlg::OnFindbestplays() 
{

	if (! this->gameinprogress && ! this->reviewinprogress)
		return;

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	/*
	int i, j;
	CString temp;
	char c;

	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
		{
			temp = this->m_grid.GetItemText(i + 1, j + 1);
			c = temp[0];
			if (! ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
				c = '\0';
			
			this->board.setLetter(i, j, c);
		}
	*/


	CStringList words;
	ExArray<int> xlocs, ylocs, acrossdown, values;

	CString rack;
	//this->GetDlgItem(IDC_RACK2)->GetWindowText(rack);
	this->GetRack2(rack);
	
	this->FindBestPlays(rack, words, xlocs, ylocs, acrossdown, values);

	CString output;
	
	POSITION pos = words.GetHeadPosition();

	int i;
	CString temp;

	for (i = 0; i < words.GetCount() && i < 100; i++)
	{
		
		temp.Format("%c%d %c %s %d\r\n", xlocs[i] + 'A', ylocs[i] + 1, acrossdown[i] * 3 + 'A',
						words.GetNext(pos).GetBuffer(0), values[i]);

		//temp = words.GetNext(pos) + "\r\n";
		output += temp;
	}

	this->GetDlgItem(IDC_BESTPLAYSOUTPUT)->SetWindowText(output);


	
}

void CWrabbleDlg::FindBestPlays(const CString &rack,
								CStringList &retwords,
								ExArray<int> &retxlocs,
								ExArray<int> &retylocs, 
								ExArray<int> &retacrossdown,
								ExArray<int> &retvalues)
{

	int hv, i, j, wi, score, row, col;
	CString temp, rfi, pattern;
	CStringArray wordlist;

	CStringList words, otherwords;
	ExArray<int> xlocs, ylocs, acrossdown, values;


	this->m_progress.SetRange(0, 32);
	this->m_progress.SetPos(0);
	this->m_progress.SetStep(1);
	

	for (hv = COLUMN; hv <= ROW; hv++)
	{
		
		for (i = 0; i < 15; i++)
		{
			this->m_progress.StepIt();  

			if (! this->board.canPlayIn(hv, i))
				continue;
		
			/*
			for (wordlength = 2; wordlength <= 15; wordlength++)
			{

				for (j = 0; j < 16 - wordlength; j++)
				{
					
					if (hv == COLUMN)
					{
						row = j;
						col = i;
					}
					else
					{
						row = i;
						col = j;
					}
					
					if (!this->board.doesWordFit(row, col, hv, wordlength, temp))
						continue;

					this->board.getPatternAt(row, col, hv, wordlength, pattern);

					temp = pattern;
					temp.Remove('?');
					temp += rack;
					temp.MakeLower();

					this->dictionary.getWords(wordlist, wordlength, wordlength, pattern, NULL, temp);
					
					for (wi = 0; wi < wordlist.GetSize(); wi++)
					{

						wordlist[wi].MakeUpper();
						score = this->board.IsValidPlay(wordlist[wi], rack, row, col, hv, FALSE, this->dictionary, otherwords, rfi);
						if (score > 0)
						{
							words.AddTail(wordlist[wi]);
							xlocs += col;
							ylocs += row;
							acrossdown += 2 - hv;
							values += score;
						}
						
					}
				


				}
			
			}
			
			*/
			
			this->board.getLettersIn(hv, i, temp);
			temp += rack;
			temp.MakeLower();

			this->dictionary.getWords(wordlist, 0, temp.GetLength(), NULL, NULL, temp);
			
			for (wi = 0; wi < wordlist.GetSize(); wi++)
			{

				for (j = 0; j < 16 - wordlist[wi].GetLength(); j++)
				{
					if (hv == COLUMN)
					{
						row = j;
						col = i;
					}
					else
					{
						row = i;
						col = j;
					}
					
			
					wordlist[wi].MakeUpper();
					score = this->board.IsValidPlay(wordlist[wi], rack, row, col, hv,
										this->dictionary, otherwords, rfi);
					if (score > 0)
					{
						words.AddTail(wordlist[wi]);
						xlocs += col;
						ylocs += row;
						acrossdown += 2 - hv;
						values += score;
					}
				}
			}
			
			this->UpdateTimeDisplays();
		
		}

	}

	this->m_progress.StepIt();

	int highestscore, highestindex;
	BOOL *used;
	used = new BOOL[words.GetCount()];

	for (i = 0; i < words.GetCount(); i++)
		used[i] = FALSE;

	for (i = 0; i < words.GetCount(); i++)
	{
		highestscore = 0;
		
		for (j = 0; j < words.GetCount(); j++)
		{
			if (!used[j] && values[j] > highestscore)
			{
				highestscore = values[j];
				highestindex = j;
			}
		}

		used[highestindex] = TRUE;

		retwords.AddTail(words.GetAt(words.FindIndex(highestindex)));
		retxlocs += xlocs[highestindex];
		retylocs += ylocs[highestindex];
		retacrossdown += acrossdown[highestindex];
		retvalues += values[highestindex];

	}

	this->m_progress.StepIt();

	delete[] used;

}

void CWrabbleDlg::OnStartgame() 
{

	if (this->gameinprogress && AfxMessageBox("Quit current game?", MB_YESNO) == IDNO)
			return;


	this->InitializeGameConditions();

	this->gameinprogress = TRUE;

	this->SetTimer(1, 500, NULL);

	if (rand() < 16384)
	{
		this->SetTurnPointer(1);
		this->computerturn = TRUE;
		this->gamelog.firstturn = 1;

	}
	else
	{
		this->SetTurnPointer(2);
		this->AddTurnLogEntry("", 0, 0);
		this->gamelog.firstturn = 2;
	}


	this->SetTimer(0, 2000, NULL);   // computer play
	

}


void CWrabbleDlg::InitializeGameConditions()
{
	srand((unsigned)time(NULL));

	this->letterbag.init();
	this->board.init();

	this->DrawBoard();

	this->GetDlgItem(IDC_RACK1)->SetWindowText(this->letterbag.getLetters(7));
	//this->GetDlgItem(IDC_RACK2)->SetWindowText(this->letterbag.getLetters(7));
	this->SetRack2(this->letterbag.getLetters(7));

	this->GetDlgItem(IDC_SCORE1)->SetWindowText("0");
	this->GetDlgItem(IDC_SCORE2)->SetWindowText("0");

		
	CString name1, name2;
	
	this->GetDlgItem(IDC_PLAYER1NAME)->GetWindowText(name1);
	this->GetDlgItem(IDC_PLAYER2NAME)->GetWindowText(name2);

	this->m_turnlog.DeleteAllItems();
	while (this->m_turnlog.DeleteColumn(0));
	
	this->m_turnlog.InsertColumn(0, name1, LVCFMT_LEFT, 80, 1);
	this->m_turnlog.InsertColumn(1, "", LVCFMT_RIGHT, 30, 2);
	this->m_turnlog.InsertColumn(2, "", LVCFMT_RIGHT, 30, 3);
	this->m_turnlog.InsertColumn(3, name2, LVCFMT_LEFT, 80, 4);
	this->m_turnlog.InsertColumn(4, "", LVCFMT_RIGHT, 30, 5);
	this->m_turnlog.InsertColumn(5, "", LVCFMT_RIGHT, 30, 6);

	this->gamelog.gameturns.resize(0);

	this->passcount = 0;

	this->turnlogpointer = 0;

	this->computerturn = FALSE;
	
	this->OnReset();
}
	
void CWrabbleDlg::SetTurnPointer(int turn)
{
	
	
	if (turn == 1)
	{
		this->GetDlgItem(IDC_TURNPOINTER)->SetWindowText("<-- Turn");
		this->OnStart1();
	}
	else if (turn == 2)
	{
		this->GetDlgItem(IDC_TURNPOINTER)->SetWindowText("Turn -->");
		this->OnStart2();
	}
	else
		this->GetDlgItem(IDC_TURNPOINTER)->SetWindowText("");

	CString message;
	message.Format("Letters in bag: %d", this->letterbag.getLetterCount());

	this->GetDlgItem(IDC_NUMLETTERSLEFT)->SetWindowText(message);

	CString rack;
	this->GetDlgItem(IDC_RACK1)->GetWindowText(rack);
	this->lettersleftdlg.SetText(this->letterbag.getLetterBreakdown(rack));

}

void CWrabbleDlg::Pass(int turn)
{

	this->AddTurnLogEntry("Pass", 0, 0);

	CString rack;
	if (turn == 1)
		this->GetDlgItem(IDC_RACK1)->GetWindowText(rack);
	else
		this->GetRack2(rack);

	WrabbleGameTurn gameturn;
	gameturn.rack = rack;
	gameturn.EPW = 'P';
	this->gamelog.gameturns += gameturn;

	
	if (turn == 1)
	{
		AfxMessageBox("Computer passes.");
		this->SetTurnPointer(2);
	}
	else
	{
		this->SetTurnPointer(1);
		//this->ComputerPlay();
		this->computerturn = TRUE;
	}



	if (this->passcount == 5)
		this->EndGame();

	this->passcount++;

}


void CWrabbleDlg::ComputerPlay()
{

	if (! this->gameinprogress)
		return;

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	CStringList words;
	ExArray<int> xlocs, ylocs, acrossdown, values;

	CString rack;
	this->GetDlgItem(IDC_RACK1)->GetWindowText(rack);
	
	this->FindBestPlays(rack, words, xlocs, ylocs, acrossdown, values);
	
	int lettercount = this->letterbag.getLetterCount();

	if (words.GetCount() == 0 && lettercount < 7)
	{
		this->Pass(1);
		return;
	}

	CString temp;
	this->GetDlgItem(IDC_LEVEL)->GetWindowText(temp);
	int level = atoi(temp);

	if (level < 0)
		level = 0;
	if (level > 10)
		level = 10;

	
	//int scoretoplay = (int)(((float)values[0] / 2.0) * (float)level / 10.0 + ((float)values[0] / 2.0));

	

	CString word;

	int wordtoplay = 0, good = 0;
	

	if (words.GetCount() > 1)
	{
		
		POSITION pos = words.GetHeadPosition();
		CString lettersused;

		int scoretoplay = (int)((float)values[0] * ((float)level * 0.075 + 0.25));
		
		do
		{
			word = words.GetNext(pos);
			
			if (values[wordtoplay] > scoretoplay)
				continue;

			this->putWordOnBoard(word, ylocs[wordtoplay], xlocs[wordtoplay], 2 - acrossdown[wordtoplay], 
							lettersused, FALSE);

			// using blank must score at least level * 3 + 20 points
			if (lettercount > 2 &&
					lettersused.Find('?') != -1
							&& values[wordtoplay] < level * 4 + 15)
				continue;
			

			// using S must score at least level * 2 + 10 points
			if (lettercount > 2 &&
					lettersused.Find('S') != -1
							&& values[wordtoplay] < level * 3 + 5)
				continue;
			

			good = 1;

		}
		while (!good && wordtoplay++ < words.GetCount() - 2);
	}		
		
	//int wordtoplay = words.GetCount() / 10 * (10 - level);
	//if (level == 0)
	//	wordtoplay = words.GetCount() - 1;

//---------------------------------
/*
	CString output;
	
	pos = words.GetHeadPosition();

	int i;

	for (i = 0; i < words.GetCount() && i < 100; i++)
	{
		
		temp.Format("%c%d %c %s %d\r\n", xlocs[i] + 'A', ylocs[i] + 1, acrossdown[i] * 3 + 'A',
						words.GetNext(pos).GetBuffer(0), values[i]);

		//temp = words.GetNext(pos) + "\r\n";
		output += temp;
	}

	this->GetDlgItem(IDC_BESTPLAYSOUTPUT)->SetWindowText(output);
	*/
//-----------------------------


	// do an exchange if no good plays available
	if (lettercount >= 7 && (words.GetCount() == 0 || values[wordtoplay] < 4 + level))
	{
		int i;
		word = "";

		for (i = 0; i < rack.GetLength(); i++)
		{
			if (rack[i] != '?' && rack[i] != 'S' && rack[i] != 'Z' && rack[i] != 'J'
				&& rack[i] != 'X' && rack[i] != 'Q')
				word += rack[i];

		}

		// if have a Q, keep one U
		int p;
		if (rack.Find('Q') != -1 && (p = word.Find('U') != -1))
			word = word.Left(p) + word.Right(word.GetLength() - p - 1);			

		this->exchangeLetters(1, word, TRUE);

		CString message;
		message.Format("Computer exchanges %d letters.", word.GetLength());

		
		AfxMessageBox(message);
	
	}
	
	else

		this->playWord(1, words.GetAt(words.FindIndex(wordtoplay)),
					xlocs[wordtoplay], ylocs[wordtoplay], 2 - acrossdown[wordtoplay]);
	
			
	this->SetTurnPointer(2);

	
}

BOOL CWrabbleDlg::playWord(int turn, const CString &inword, int col, int row, int hv)
{

	CString word = inword;

	if (!this->dictionary.isAWord(word))
	{
		word.MakeUpper();
		AfxMessageBox(word + " is not a word.");
		return FALSE;
	}

	CString rack;
	if (turn == 1)
		this->GetDlgItem(IDC_RACK1)->GetWindowText(rack);
	else
		//this->GetDlgItem(IDC_RACK2)->GetWindowText(rack);
		this->GetRack2(rack);

	
	CStringList otherwords;
	CString reasonforinvalid;

	word.MakeUpper();
	int value = this->board.IsValidPlay(word, rack, row, col, hv,
					this->dictionary, otherwords, reasonforinvalid);

	if (value == 0)
	{
		AfxMessageBox(reasonforinvalid);
		return FALSE;
	}

	int currentscore;

	CString temp;
	if (turn == 1)
		this->GetDlgItem(IDC_SCORE1)->GetWindowText(temp);
	else
		this->GetDlgItem(IDC_SCORE2)->GetWindowText(temp);
	currentscore = atoi(temp);

	currentscore += value;
	temp.Format("%d", currentscore);

	if (turn == 1)
		this->GetDlgItem(IDC_SCORE1)->SetWindowText(temp);
	else
		this->GetDlgItem(IDC_SCORE2)->SetWindowText(temp);

	CString wordsplayed = word;
	
	POSITION pos = otherwords.GetHeadPosition();

	while (pos)
	{
		wordsplayed += ", ";
		wordsplayed += otherwords.GetNext(pos);
	}
	
	wordsplayed.MakeUpper();
	this->AddTurnLogEntry(wordsplayed, value, currentscore);

	WrabbleGameTurn gameturn;
	gameturn.rack = rack;
	gameturn.EPW = 'W';
	gameturn.pos.Format("%c%d", 'A' + col, row + 1);
	gameturn.DA = hv == ROW ? 'A' : 'D';
	gameturn.word = word;
	this->gamelog.gameturns += gameturn;


	CString lettersused;	

	this->putWordOnBoard(word, row, col, hv, lettersused);
	
	this->DrawBoard();
	
	this->exchangeLetters(turn, lettersused, FALSE);
	
	this->passcount = 0;

	return TRUE;
}

void CWrabbleDlg::putWordOnBoard(const CString &word, int row, int col, int hv,
								 CString &lettersused, BOOL reallyputletterson)
{

	lettersused = "";

	int i, trow, tcol;
	for (i = 0; i < word.GetLength(); i++)
	{
		trow = hv == ROW ? row : row + i;
		tcol = hv == COLUMN ? col : col + i;

		if (! this->board.getLetter(trow, tcol))
		{
			if (reallyputletterson)
			{
				this->board.setLetter(trow, tcol, word[i]);
				if (this->gameinprogress || this->reviewinprogress)
					this->m_grid.SetItemData(trow + 1, tcol + 1, 1);
			}
			
			if (word[i] >= 'a' && word[i] <= 'z')
				lettersused += '?';
			else
				lettersused += word[i];
						
		}

	}
}


void CWrabbleDlg::exchangeLetters(int turn, CString &letters, BOOL throwback)
{

	CString rack, oldrack;
	if (turn == 1)
		this->GetDlgItem(IDC_RACK1)->GetWindowText(rack);
	else
		//this->GetDlgItem(IDC_RACK2)->GetWindowText(rack);
		this->GetRack2(rack);

	oldrack = rack;

	int i, j, rl[7];
	CString baglet;

	for (i = 0; i < letters.GetLength(); i++)
	{
		rl[i] = rack.Find(letters[i]);

		if (rl[i] == -1)
			AfxMessageBox("Letter not found on rack.");
		else
			rack.SetAt(rl[i], '-');
	}
	
	for (i = 0; i < letters.GetLength(); i++)
	{
	
		baglet = this->letterbag.getLetters(1);
		if (baglet == "")
		{
			rack = rack.Left(rl[i]) + rack.Right(rack.GetLength() - rl[i] - 1);
			for (j = i + 1; j < letters.GetLength(); j++)
				if (rl[j] > rl[i])
					rl[j]--;
		}
		else
			rack.SetAt(rl[i], baglet[0]);

	}

	if (throwback)
	{
		this->letterbag.throwBack(letters);
		this->AddTurnLogEntry("Exchange", 0, 0);

		WrabbleGameTurn gameturn;
		gameturn.rack = oldrack;
		gameturn.EPW = 'E';
		this->gamelog.gameturns += gameturn;

		if (this->passcount == 5)
			this->EndGame();

		this->passcount++;

		
	}

	if (turn == 1)
		this->GetDlgItem(IDC_RACK1)->SetWindowText(rack);
	else
		//this->GetDlgItem(IDC_RACK2)->SetWindowText(rack);
		this->SetRack2(rack);


	if (! this->reviewinprogress && rack == "")
		this->EndGame();


}


void CWrabbleDlg::OnHiderack1() 
{

	if (this->GetDlgItem(IDC_RACK1)->IsWindowVisible())
	{
		this->GetDlgItem(IDC_RACK1)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_HIDERACK1)->SetWindowText("< Show");
	}
	else
	{
		this->GetDlgItem(IDC_RACK1)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_HIDERACK1)->SetWindowText("< Hide");
	}

}

void CWrabbleDlg::OnRightClickRack2(NMHDR* pNMHDR, LRESULT* pResult)
{

	NM_GRIDVIEW *nmgv = (NM_GRIDVIEW*)pNMHDR;

	int row = nmgv->iRow;
	int col = nmgv->iColumn;

	CString rack;
	this->GetRack2(rack);

	if (row != 0 || col >= rack.GetLength())
		return;

	if (! this->gameinprogress)
		return;

	if (this->letterbag.getLetterCount() < 7)
	{
		AfxMessageBox("There must be at least 7 tiles in the bag in order to exchange.");
		return;
	}


	CString word = rack.Left(col + 1);
	
	CString message;
	message.Format("Exchange %s?", word);

	if (AfxMessageBox(message, MB_YESNO) == IDNO)
		return;
	
	this->exchangeLetters(2, word, TRUE);

	
	this->GetDlgItem(IDC_WORDTOPLAY)->SetWindowText("");
	
	this->SetTurnPointer(1);
	this->computerturn = TRUE;


}

void CWrabbleDlg::OnClickRack2(NMHDR* pNMHDR, LRESULT* pResult)
{

	NM_GRIDVIEW *nmgv = (NM_GRIDVIEW*)pNMHDR;

	int row = nmgv->iRow;
	int col = nmgv->iColumn;

	CString rack;
	this->GetRack2(rack);

	if (row != 0 || col >= rack.GetLength())
		return;

	if (this->oldrackclick == -1)
		this->oldrackclick = col;
	else
	{
		char c = rack[col];
		rack.SetAt(col, rack[oldrackclick]);
		rack.SetAt(oldrackclick, c);

		this->SetRack2(rack);
	}

}

void CWrabbleDlg::OnDblClickGrid(NMHDR* pNMHDR, LRESULT* pResult) 
{

	if (! this->gameinprogress)
		return;

	NM_GRIDVIEW *nmgv = (NM_GRIDVIEW*)pNMHDR;

	int row = nmgv->iRow;
	int col = nmgv->iColumn;
	int hv;

	if (row < 1 || col < 1)
		return;

	CString word;
	this->GetDlgItem(IDC_WORDTOPLAY)->GetWindowText(word);

	if (((CButton*)(this->GetDlgItem(IDC_ACROSSRADIO)))->GetCheck())
		hv = ROW;
	else
		hv = COLUMN;

	if (this->playWord(2, word, col - 1, row - 1, hv))
	{

		this->GetDlgItem(IDC_WORDTOPLAY)->SetWindowText("");
		
		this->SetTurnPointer(1);
		//this->ComputerPlay();
		this->computerturn = TRUE;
	}


}

void CWrabbleDlg::OnPass() 
{
	if (! this->gameinprogress)
		return;

	this->Pass(2);	
}

void CWrabbleDlg::EndGame()
{

	this->KillTimer(0);
	this->KillTimer(1);

	this->OnStop();


	CString rack1, rack2;
	this->GetDlgItem(IDC_RACK1)->GetWindowText(rack1);
	//this->GetDlgItem(IDC_RACK2)->GetWindowText(rack2);
	this->GetRack2(rack2);

	CString temp;
	int score1, score2;
	this->GetDlgItem(IDC_SCORE1)->GetWindowText(temp);
	score1 = atoi(temp);
	this->GetDlgItem(IDC_SCORE2)->GetWindowText(temp);
	score2 = atoi(temp);

	int rackvalue1 = 0, rackvalue2 = 0, i;
	for (i = 0; i < rack1.GetLength(); i++)
		rackvalue1 += this->letterbag.getLetterValue(rack1[i]);
	for (i = 0; i < rack2.GetLength(); i++)
		rackvalue2 += this->letterbag.getLetterValue(rack2[i]);

	
	if (rackvalue1 > 0)
	{
		score1 -= rackvalue1;
		this->AddTurnLogEntry("Unplayed Letters", -rackvalue1, score1, 1);
	}

	if (rackvalue2 > 0)
	{
		score2 -= rackvalue2;
		this->AddTurnLogEntry("Unplayed Letters", -rackvalue2, score2, 2);
	}

	if (rack1 == "")
	{
		score1 += rackvalue2;
		this->AddTurnLogEntry("Letter Bonus", rackvalue2, score1, 1);
	}

	if (rack2 == "")
	{
		score2 += rackvalue1;
		this->AddTurnLogEntry("Letter Bonus", rackvalue1, score2, 2);
	}
	
	if (! this->reviewinprogress)
	{
		int timepenalty;
		if (this->time1 > 25 * 60)
		{
			timepenalty = (int)((this->time1 - (24 * 60 + 1)) / 60) * 10;
			score1 -= timepenalty;
			this->AddTurnLogEntry("Time Penalty", -timepenalty, score1, 1);
		}

		if (this->time2 > 25 * 60)
		{
			timepenalty = (int)((this->time2 - (24 * 60 + 1)) / 60) * 10;
			score2 -= timepenalty;
			this->AddTurnLogEntry("Time Penalty", -timepenalty, score2, 2);
		}
	}


	temp.Format("%d", score1);
	this->GetDlgItem(IDC_SCORE1)->SetWindowText(temp);
	temp.Format("%d", score2);
	this->GetDlgItem(IDC_SCORE2)->SetWindowText(temp);


	CString name1, name2, message;
	
	this->GetDlgItem(IDC_PLAYER1NAME)->GetWindowText(name1);
	this->GetDlgItem(IDC_PLAYER2NAME)->GetWindowText(name2);

	message.Format("Final score:\r\n%s: %d\r\n%s: %d\r\n", name1, score1, name2, score2);

	AfxMessageBox(message);

	this->gameinprogress = FALSE;


	if (! this->reviewinprogress)
	{
		
		COleDateTime timeNow;
		timeNow = COleDateTime::GetCurrentTime();
					
		this->gamelog.date = timeNow.Format(VAR_DATEVALUEONLY);
		this->gamelog.time = timeNow.Format(VAR_TIMEVALUEONLY);
		this->gamelog.time.Remove(' ');

		this->GetDlgItem(IDC_LEVEL)->GetWindowText(this->gamelog.level);

		this->gamelog.name1 = name1;
		this->gamelog.name2 = name2;
		this->gamelog.score1 = score1;
		this->gamelog.score2 = score2;
			
		this->gamelog.WriteToFile("gamelogs.dat");
	}	
		
}



void CWrabbleDlg::AddTurnLogEntry(const CString &word, int value, int score, int turn)
{

	if (turn && (this->turnlogpointer % 2) + 1 != turn)
			this->AddTurnLogEntry("", 0, 0);
	
	if (this->turnlogpointer % 2 == 0)
		this->m_turnlog.InsertItem(turnlogpointer / 2, word);
	else
		this->m_turnlog.SetItemText(turnlogpointer / 2, 3, word);
	

	CString temp1, temp2;
	temp1.Format("%d", value);
	temp2.Format("%d", score);
	
	if (value == 0)
		temp1 = "--";

	if (score == 0)
		temp2 = "--";
	
	this->m_turnlog.SetItemText(turnlogpointer / 2, (turnlogpointer % 2) * 3 + 1, temp1);
	this->m_turnlog.SetItemText(turnlogpointer / 2, (turnlogpointer % 2) * 3 + 2, temp2);

	this->m_turnlog.EnsureVisible(turnlogpointer / 2, FALSE);

	this->turnlogpointer++;


}

void CWrabbleDlg::OnOK() 
{
	// do nothing
}

void CWrabbleDlg::OnCancel() 
{
	if (this->gameinprogress && AfxMessageBox("Quit current game?", MB_YESNO) == IDNO)
			return;
	
	CString temp;

	this->GetDlgItem(IDC_PLAYER1NAME)->GetWindowText(temp);
	AfxGetApp()->WriteProfileString("GENERAL", "PLAYER1NAME", temp);
	this->GetDlgItem(IDC_PLAYER2NAME)->GetWindowText(temp);
	AfxGetApp()->WriteProfileString("GENERAL", "PLAYER2NAME", temp);
	this->GetDlgItem(IDC_LEVEL)->GetWindowText(temp);
	AfxGetApp()->WriteProfileString("GENERAL", "LEVEL", temp);
		
	CDialog::OnCancel();	
	
}

void CWrabbleDlg::OnTimer(UINT nIDEvent) 
{

	switch (nIDEvent)
	{
	case 0:
		if (this->computerturn)
		{
			this->computerturn = FALSE;
			this->ComputerPlay();
		}
		break;
	case 1:
		this->UpdateTimeDisplays();
		break;
	}

	CDialog::OnTimer(nIDEvent);
}



void CWrabbleDlg::OnReset() 
{

	this->time1 = 0;
	this->time2 = 0;

	this->running1 = FALSE;
	this->running2 = FALSE;

	this->UpdateTimeDisplays();

}



void CWrabbleDlg::OnStart1() 
{

	this->reftime1 = ::time(NULL);
	this->Stop2(this->reftime1);
	
	this->running1 = TRUE;

}


void CWrabbleDlg::OnStop() 
{

	time_t temp = ::time(NULL);
	this->Stop1(temp);
	this->Stop2(temp);

}

void CWrabbleDlg::OnStart2() 
{
	this->reftime2 = ::time(NULL);
	this->Stop1(this->reftime2);

	this->running2 = TRUE;

}

void CWrabbleDlg::Stop1(time_t &stoptime) 
{
	if (this->running1)
	{	
		this->running1 = FALSE;

		this->time1 += (stoptime - this->reftime1);
	}
	
}

void CWrabbleDlg::Stop2(time_t &stoptime) 
{

	if (this->running2)
	{
		this->running2 = FALSE;

		this->time2 += (stoptime - this->reftime2);
	}


}


void CWrabbleDlg::UpdateTimeDisplays()
{
	time_t temp = ::time(NULL);

	CString string;

	long disp = this->time1;
	if (this->running1)
		disp += (temp - this->reftime1);

	string.Format("%02d:%02d", disp / 60, disp % 60);
	this->GetDlgItem(IDC_TIME1)->SetWindowText(string);

	disp = this->time2;
	if (this->running2)
		disp += (temp - this->reftime2);

	string.Format("%02d:%02d", disp / 60, disp % 60);
	this->GetDlgItem(IDC_TIME2)->SetWindowText(string);


}

void CWrabbleDlg::GetRack2(CString &rack) const
{

	rack = "";
	
	int i;
	for (i = 0; i < 7; i++)
		rack += this->m_rack2.GetItemText(0, i);

}

void CWrabbleDlg::SetRack2(const CString &rack)
{
	int i;
	for (i = 0; i < 7; i++)
	{
		if (i < rack.GetLength())
		{
			this->m_rack2.SetItemText(0, i, rack.Mid(i, 1));
			this->m_rack2.SetItemBkColour(0, i, RGB(200, 200, 0));
		}
		else
		{
			this->m_rack2.SetItemText(0, i, "");
			this->m_rack2.SetItemBkColour(0, i, RGB(100, 100, 100));
		}
	}

	this->oldrackclick = -1;
	this->m_rack2.Refresh();
}


void CWrabbleDlg::OnNumlettersleft() 
{

	this->lettersleftdlg.ShowWindow(! this->lettersleftdlg.IsWindowVisible());
	

}

void CWrabbleDlg::OnGameReviewer() 
{
	if (this->gameinprogress && AfxMessageBox("Quit current game?", MB_YESNO) == IDNO)
		return;

	this->gameinprogress = FALSE;

	CGameReviewerDlg dlg(this);
	dlg.DoModal();

	this->reviewinprogress = FALSE;

}

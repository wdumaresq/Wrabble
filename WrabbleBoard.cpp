// WrabbleBoard.cpp: implementation of the WrabbleBoard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wrabble.h"
#include "WrabbleBoard.h"
#include "Dictionary.h"
#include "WrabbleLetterBag.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



WrabbleBoard::WrabbleBoard()
{

	
	this->init();	

	strcpy(ROWCOL[ROW], "row");
	strcpy(ROWCOL[COLUMN], "column");



}

void WrabbleBoard::init()
{

	int i, j;

	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
		{
			this->letters[i][j] = '\0';
			this->specials[i][j] = ' ';
		}

	// triple word scores
	this->specials[0][0] = '$';
	this->specials[7][0] = '$';
	this->specials[14][0] = '$';
	this->specials[0][7] = '$';
	this->specials[14][7] = '$';
	this->specials[0][14] = '$';
	this->specials[7][14] = '$';
	this->specials[14][14] = '$';
	
	// double word scores
	this->specials[1][1] = '*';
	this->specials[2][2] = '*';
	this->specials[3][3] = '*';
	this->specials[4][4] = '*';
	this->specials[13][1] = '*';
	this->specials[12][2] = '*';
	this->specials[11][3] = '*';
	this->specials[10][4] = '*';
	this->specials[7][7] = '*';
	this->specials[1][13] = '*';
	this->specials[2][12] = '*';
	this->specials[3][11] = '*';
	this->specials[4][10] = '*';
	this->specials[10][10] = '*';
	this->specials[11][11] = '*';
	this->specials[12][12] = '*';
	this->specials[13][13] = '*';

	// triple letter scores
	this->specials[5][1] = '3';
	this->specials[9][1] = '3';
	this->specials[1][5] = '3';
	this->specials[5][5] = '3';
	this->specials[9][5] = '3';
	this->specials[13][5] = '3';
	this->specials[1][9] = '3';
	this->specials[5][9] = '3';
	this->specials[9][9] = '3';
	this->specials[13][9] = '3';
	this->specials[5][13] = '3';
	this->specials[9][13] = '3';

	// double letter scores
	this->specials[3][0] = '2';
	this->specials[11][0] = '2';
	this->specials[6][2] = '2';
	this->specials[8][2] = '2';
	this->specials[0][3] = '2';
	this->specials[7][3] = '2';
	this->specials[14][3] = '2';
	this->specials[2][6] = '2';
	this->specials[6][6] = '2';
	this->specials[8][6] = '2';
	this->specials[12][6] = '2';
	this->specials[3][7] = '2';
	this->specials[11][7] = '2';
	this->specials[2][8] = '2';
	this->specials[6][8] = '2';
	this->specials[8][8] = '2';
	this->specials[12][8] = '2';
	this->specials[0][11] = '2';
	this->specials[7][11] = '2';
	this->specials[14][11] = '2';
	this->specials[6][12] = '2';
	this->specials[8][12] = '2';
	this->specials[3][14] = '2';
	this->specials[11][14] = '2';

}


WrabbleBoard::~WrabbleBoard()
{

}

BOOL WrabbleBoard::canPlayIn(int rowcol, int index)
{
	if (index == 7)
		return TRUE;
	
	CString temp;

	int i;
	for (i = index - 1; i < index + 2; i++)
	{
		if (i >= 0 && i < 15)
		{
			this->getLettersIn(rowcol, i, temp);
			if (temp != "")
				return TRUE;
		}
	}

	return FALSE;
}

void WrabbleBoard::getLettersIn(int rowcol, int index, CString &retletters)
{
	retletters = "";

	int j, row, col;
	char c;

	for (j = 0; j < 15; j++)
	{
		row = j;
		col = j;

		if (rowcol == ROW)
			row = index;
		else
			col = index;

		c = this->getLetter(row, col);

		if (c != '\0')
			retletters += c;

	}

	
}

void WrabbleBoard::getPatternAt(int row, int col, int hv,
								int wordlength, CString &pattern) const
{
	int j, trow = row, tcol = col;
	char c;

	pattern = "???????????????";
	pattern = pattern.Left(wordlength);		

	for (j = 0; j < wordlength; j++)
	{
		if (hv == COLUMN)
			trow = row + j;
		else
			tcol = col + j;

		c = this->getLetter(row, col);

		if (c != '\0')
			pattern.SetAt(j, c);

	}


}


int WrabbleBoard::IsValidPlay(CString &word, const CString &rack, int row, int col,
							  int hv, CDictionary &dict,
							  CStringList &additionalwords, CString &reasonforinvalid)
{

	additionalwords.RemoveAll();

	// ensure that word can actually be played on the board, and uses at least one letter
	// from the rack
	
	int totalvalue = 0, mainwordvalue = 0, multiplier = 1, lettermultiplier, value;

	int i, rl, trow, tcol; //, ip;
	//ip = (hv == ROW ? col : row);
	char c, sp;

	CString rackcopy = rack, tempword;

	int numrackused = 0;
	BOOL touchesexistingword = FALSE;

	for (i = 0; i < word.GetLength(); i++)
	{
		lettermultiplier = 1;

		trow = hv == ROW ? row : row + i;
		tcol = hv == COLUMN ? col : col + i;
		c = this->getLetter(trow, tcol);

		if (c == '\0')
		{
			// search rack

			rl = rackcopy.Find(word[i]);
			if (rl == -1)
			{
				rl = rackcopy.Find('?');
				word.SetAt(i, word[i] + ('a' - 'A'));
			}

			if (rl == -1)
			{
				reasonforinvalid = "Your rack does not contain the required letters to make that word.";
				return 0;
			}
			
			if (trow == 7 && tcol == 7)
				touchesexistingword = TRUE;

			numrackused++;
			// remove letter from rack
			rackcopy = rackcopy.Left(rl) + rackcopy.Right(rackcopy.GetLength() - rl - 1);

			// check perpendicular direction
			
			value = this->getPotentialWord(trow, tcol, 3 - hv, word[i], tempword);
			if (tempword.GetLength() > 1 && ! dict.isAWord(tempword))
			{
				tempword.MakeUpper();
				reasonforinvalid = tempword + " is not a word.";				
				return 0;
			}

			if (tempword.GetLength() > 1)
			{
				totalvalue += value;
				touchesexistingword = TRUE;
				additionalwords.AddTail(tempword);
			}

			sp = this->getSpecial(trow, tcol);

			if (sp == '2')
				lettermultiplier = 2;

			if (sp == '3')
				lettermultiplier = 3;

			if (sp == '*')
				multiplier *= 2;

			if (sp == '$')
				multiplier *= 3;

			c = word[i];

		}
		else
		{
			if (toupper(c) != word[i])
			{
				reasonforinvalid = "Specified word does not fit on board in that location.";
				return 0;
			}

			touchesexistingword = TRUE;
		}

		mainwordvalue += WrabbleLetterBag::getLetterValue(c) * lettermultiplier;
		
	}

	if (numrackused == 0 || !touchesexistingword)
	{
		reasonforinvalid = "Word must touch an existing word.";
		return 0;	
	}

	if (!this->doesWordFit(row, col, hv, word.GetLength(), reasonforinvalid))
		return 0;

	
	if (numrackused == 7)   // bingo
		totalvalue += 50;

	return totalvalue + mainwordvalue * multiplier;


}

BOOL WrabbleBoard::doesWordFit(int row, int col,
							   int hv, int length, CString &reasonforinvalid) const
{

		// ensure blank spaces on either side of the word

	if (hv == ROW)
	{
		if (col > 0 && this->getLetter(row, col - 1))
		{
			reasonforinvalid = "Specified word does not fit on board in that location.";
			return FALSE;
		}

		if (col < 15 - length && this->getLetter(row, col + length))
		{
			reasonforinvalid = "Specified word does not fit on board in that location.";
			return FALSE;
		}

		if (col > 15 - length)
		{
			reasonforinvalid = "Word cannot extend off side of board.";
			return FALSE;
		}
	}

	if (hv == COLUMN)
	{
		if (row > 0 && this->getLetter(row - 1, col))
		{
			reasonforinvalid = "Specified word does not fit on board in that location.";
			return FALSE;
		}


		if (row < 15 - length && this->getLetter(row + length, col))
		{
			reasonforinvalid = "Specified word does not fit on board in that location.";
			return FALSE;
		}


		if (row > 15 - length)
		{
			reasonforinvalid = "Word cannot extend off bottom of board.";
			return FALSE;
		}
	}

	return TRUE;

}


int WrabbleBoard::getPotentialWord(int row, int col, 
									int hv, char c, CString &retword)
{

	int value = 0, multiplier = 1, lettermultiplier = 1;
	
	int i, trow, tcol;
	retword = "";

	BOOL passedpoint = FALSE;
	char tc, sp;

	for (i = 0; i < 15; i++)
	{
		trow = hv == ROW ? row : i;
		tcol = hv == COLUMN ? col : i;
		
		if (trow == row && tcol == col)
		{	
			tc = c;
			passedpoint = TRUE;

			sp = this->getSpecial(row, col);

			if (sp == '2')
				lettermultiplier = 2;

			if (sp == '3')
				lettermultiplier = 3;

			if (sp == '*')
				multiplier = 2;

			if (sp == '$')
				multiplier = 3;


		}			
		else
		{
			tc = this->getLetter(trow, tcol);
		}
	
		if (tc)
		{
			retword += tc;
			value += WrabbleLetterBag::getLetterValue(tc) * lettermultiplier;
			lettermultiplier = 1;
		}
		else
		{
			if (passedpoint)
				break;

			retword = "";
			value = 0;
		}
	}

	return value * multiplier;
}


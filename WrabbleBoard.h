// WrabbleBoard.h: interface for the WrabbleBoard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WRABBLEBOARD_H__DD93C3EF_6457_11D7_8E77_E06F55C10000__INCLUDED_)
#define AFX_WRABBLEBOARD_H__DD93C3EF_6457_11D7_8E77_E06F55C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define COLUMN  1
#define ROW  2


class CDictionary;

class WrabbleBoard  
{

	

public:

	char ROWCOL[3][7];

	WrabbleBoard();
	virtual ~WrabbleBoard();

	void setLetter(int row, int column, char c)   { this->letters[row][column] = c; }
	char getLetter(int row, int column) const  { return this->letters[row][column]; }
	char getSpecial(int row, int column) const  { return this->specials[row][column]; }

	BOOL canPlayIn(int rowcol, int index);
	void getLettersIn(int rowcol, int index, CString &retletters);

	void getPatternAt(int row, int col, int hv, int wordlength, CString &pattern) const;

	int IsValidPlay(CString &word, const CString &rack,
					int row, int col, int hv, CDictionary &dict,
					CStringList &additionalwords, CString &reasonforinvalid);

	int getPotentialWord(int row, int col, 
									int hv, char c, CString &retword);
	
	

	BOOL doesWordFit(int row, int col, int hv, int length, CString &reasonforinvalid) const;

	void init();

private:

	char letters[15][15];
	char specials[15][15];


};

#endif // !defined(AFX_WRABBLEBOARD_H__DD93C3EF_6457_11D7_8E77_E06F55C10000__INCLUDED_)

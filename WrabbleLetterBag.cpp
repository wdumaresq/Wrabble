// WrabbleLetterBag.cpp: implementation of the WrabbleLetterBag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wrabble.h"
#include "WrabbleLetterBag.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WrabbleLetterBag::WrabbleLetterBag()
{

}

WrabbleLetterBag::~WrabbleLetterBag()
{

}

void WrabbleLetterBag::init()
{

	letters = "AAAAAAAAABBCCDDDDEEEEEEEEEEEEFFGGGHHIIIIIIIIIJKLLLLMMNNNNNNOOOOOOOOPPQRRRRRRSSSSTTTTTTUUUUVVWWXYYZ??";


	this->mix();

}



CString WrabbleLetterBag::getLetters(int num)
{

	CString ret;

	if (num > this->letters.GetLength())
	{
		ret = letters;
		this->letters = "";
	}
	else
	{
		ret = this->letters.Left(num);
		this->letters = this->letters.Right(this->letters.GetLength() - num);
	}

	return ret;


}



void WrabbleLetterBag::throwBack(const CString &lets)
{
	this->letters += lets;

	this->mix();

}

void WrabbleLetterBag::mix()
{

	float nl = (float)this->letters.GetLength();

	int i, pos1, pos2;
	char c;

	for (i = 0; i < 1000; i++)
	{
		pos1 = (int)((float)(rand()) / 32767.0 * nl);
		pos2 = (int)((float)(rand()) / 32767.0 * nl);

		if (pos1 >= nl)
			pos1 = nl - 1;
		
		if (pos2 >= nl)
			pos2 = nl - 1;
		
		c = this->letters[pos1];
		this->letters.SetAt(pos1, this->letters[pos2]);
		this->letters.SetAt(pos2, c);
	}



}


int WrabbleLetterBag::getLetterCount(char c, CString rack) const
{
	if (c == '\0')
		return this->letters.GetLength();
	
	int ret = 0, start = 0;
	
	CString temp = this->letters + rack;

	while ((start = temp.Find(c, start) + 1) != 0)
		ret++;

	return ret;		

}


CString WrabbleLetterBag::getLetterBreakdown(CString rack) const
{
	CString ret, temp;
	int i;

	for (i = 0; i < 13; i++)
	{
		temp.Format("%c(%d) - %d\t%c(%d) - %d\r\n",
					'A' + i, this->getLetterValue('A' + i), this->getLetterCount('A' + i, rack),
					'N' + i, this->getLetterValue('N' + i), this->getLetterCount('N' + i, rack));

		ret += temp;
	}

	temp.Format("?(0) - %d", this->getLetterCount('?', rack));
	ret += temp;

	return ret;


}

int WrabbleLetterBag::getLetterValue(char c)
{

	if (c >= 'A' && c <= 'Z')
	{

		if (c == 'D' || c == 'G')
			return 2;

		if (c == 'B' || c == 'C' || c == 'M' || c == 'P')
			return 3;

		if (c == 'F' || c == 'H' || c == 'V' || c == 'W' || c == 'Y')
			return 4;

		if (c == 'K')
			return 5;

		if (c == 'X' || c == 'J')
			return 8;

		if (c == 'Q' || c == 'Z')
			return 10;
		

		return 1;
	}

	return 0;
}


// WrabbleLetterBag.h: interface for the WrabbleLetterBag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WRABBLELETTERBAG_H__C3B9A446_6627_11D7_8E77_B07055C10000__INCLUDED_)
#define AFX_WRABBLELETTERBAG_H__C3B9A446_6627_11D7_8E77_B07055C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class WrabbleLetterBag  
{
public:
	WrabbleLetterBag();
	virtual ~WrabbleLetterBag();

	void init();
	CString getLetters(int num);

	void throwBack(const CString &lets);

	int getLetterCount(char c = '\0', CString rack = "") const;

	static int getLetterValue(char c);

	CString getLetterBreakdown(CString rack) const;

protected:

	void mix();

private:

	CString letters;


};

#endif // !defined(AFX_WRABBLELETTERBAG_H__C3B9A446_6627_11D7_8E77_B07055C10000__INCLUDED_)

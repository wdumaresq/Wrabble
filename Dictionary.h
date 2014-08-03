// Dictionary.h: interface for the CDictionary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DICTIONARY_H__17E7C2E1_36EE_11D7_8E77_F05F55C10000__INCLUDED_)
#define AFX_DICTIONARY_H__17E7C2E1_36EE_11D7_8E77_F05F55C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define DICTNUMWORDS  152405


class CDictionary  
{
public:
	CDictionary();
	virtual ~CDictionary();

	void getWords(CStringArray &wordlist, int minletters = 0, int maxletters = 0,
				const char *pattern = NULL, const char *contains = NULL,
				const char *canbemadefrom = NULL) const;

	BOOL isAWord(CString &word) const;

private:

	//CStringArray words;
	char *words;

	int numwords;


};

#endif // !defined(AFX_DICTIONARY_H__17E7C2E1_36EE_11D7_8E77_F05F55C10000__INCLUDED_)

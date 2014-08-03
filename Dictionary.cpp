// Dictionary.cpp: implementation of the CDictionary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dictionary.h"

#include <fstream.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


int compare( char *arg1, char *arg2 )
{
   /* Compare all of both strings: */
   return strcmp( arg1, arg2 );
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDictionary::CDictionary()
{

	char temp[80];


	ifstream dict("wrabble.dic");

	dict >> temp;
	this->numwords = 0;
	while (! dict.eof())
	{
		this->numwords++;
		dict >> temp;
	}

	dict.close();

	this->words = new char[this->numwords * 16];

	dict.open("wrabble.dic");
	
	int i;
	for (i = 0; i < this->numwords; i++)
	{
		dict >> temp;
		strcpy(&this->words[i * 16], temp);
	}

	dict.close();



}

CDictionary::~CDictionary()
{
	delete[] words;
}

void CDictionary::getWords(CStringArray &wordlist, int minletters, int maxletters,
						   const char *pattern,
					const char *contains, const char *canbemadefrom) const
{

	const char *word;
	char wordcopy[80], madefromcopy[80];


	int length, i, containslength, patternlength, wi;

	char *tmp;

	wordlist.RemoveAll();

	//while (! dict.eof())
	for (wi = 0; wi < this->numwords; wi++)
	{
		//dict >> word;
		word = &this->words[wi * 16];

		strcpy(wordcopy, word);

		length = strlen(word);

		if (minletters > 0 && length < minletters)
			continue;

		if (maxletters > 0 && length > maxletters)
			continue;

		if (contains)
		{
			containslength = strlen(contains);
			for (i = 0; i < containslength; i++)
			{
				if (tmp = strchr(wordcopy, contains[i]))
					tmp[0] = '?';
				else
					break;
			}

			if (i < containslength)
				continue;
		}

		if (canbemadefrom && strlen(canbemadefrom) != 0)
		{
			strcpy(madefromcopy, canbemadefrom);
			for (i = 0; i < length; i++)
			{
				if (tmp = strchr(madefromcopy, word[i]))
					tmp[0] = '-';
				else
				{
					if (tmp = strchr(madefromcopy, '?'))
						tmp[0] = '-';
					else
						break;
				}
			}

			if (i < length)
				continue;
		}

		if (pattern && strlen(pattern) != 0)
		{
			
			patternlength = strlen(pattern);
			if (length < patternlength)
				continue;

			for (i = 0; i < patternlength; i++)
			{
				if (pattern[i] != '?' && pattern[i] != word[i])
					break;
			}

			if (i < patternlength)
				continue;

		}

		wordlist.Add(word);

				

	}

	




}


BOOL CDictionary::isAWord(CString &word) const
{
	
	word.MakeLower();

	if (bsearch(word.GetBuffer(0), this->words, this->numwords, 16,
		(int (*)(const void*, const void*))compare))
		return TRUE;

	return FALSE;

}

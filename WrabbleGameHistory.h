
#if !defined(WRABBLEGAMEHISTORY_H)
#define WRABBLEGAMEHISTORY_H


#include "ExArray.h"


struct WrabbleGameTurn
{
	CString rack;
	char EPW;
	CString pos;
	char DA;
	CString word;


};


class WrabbleGameHistory
{

public:
	CString name1, name2, date, time, level;
	int score1, score2;
	int firstturn;

	ExArray<WrabbleGameTurn> gameturns;



	void WriteToFile(const char *filename) const;

	static void ReadFromFile(const char *filename, ExArray<WrabbleGameHistory> &histories);


};


#endif
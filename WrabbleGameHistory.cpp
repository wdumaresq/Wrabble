#include "stdafx.h"
#include "WrabbleGameHistory.h"

#include <fstream.h>

void WrabbleGameHistory::WriteToFile(const char *filename) const
{

	ofstream file(filename, ios::app);	
	
	file << name1 << " " << name2 << " " << score1 << " " << score2 << " ";
	file << date << " " << time << " " << level << endl;
	
	file << firstturn << endl;

	unsigned int i;

	for (i = 0; i < gameturns.len(); i++)
	{
		file << gameturns[i].rack << " " << gameturns[i].EPW;
		if (gameturns[i].EPW == 'W')
			file << " " << gameturns[i].pos << " " << gameturns[i].DA << " " << gameturns [i].word;

		file << endl;
	}

	file << "@@" << endl;
	

	file.close();

}



void WrabbleGameHistory::ReadFromFile(const char *filename, ExArray<WrabbleGameHistory> &histories)
{

	histories.resize(0);

	ifstream file(filename);

	WrabbleGameHistory temp;
	WrabbleGameTurn turn;

	char string[100];
	
	file >> string;
	temp.name1 = string;

	while (! file.eof())
	{
		file >> string;
		temp.name2 = string;
		file >> temp.score1 >> temp.score2;
		file >> string;
		temp.date  = string;
		file >> string;
		temp.time = string;
		file >> string;
		temp.level = string;
		file >> temp.firstturn;

		file >> string;
		turn.rack = string;

		temp.gameturns.resize(0);

		while (turn.rack != "@@")
		{
			file >> turn.EPW;

			if (turn.EPW == 'W')
			{
				file >> string;
				turn.pos = string;
				file >> turn.DA;
				file >> string;
				turn.word = string;
			}

			temp.gameturns += turn;

			file >> string;
			turn.rack = string;
		}

		
		histories += temp;
		

		file >> string;
		temp.name1 = string;

	}

	file.close();

}
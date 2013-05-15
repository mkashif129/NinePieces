/*
Name: Muhammad Kashif
Date: 14 May, 2013
File: mkScore.h
*/



#ifndef MK_SCORE_H
#define MK_SCORE_H
#pragma once

#include "mk.h"

struct  ScoreLine
{
	string name1,name2;
	int score1, score2;

	ScoreLine()
	{

	}
	ScoreLine(string nm1, int sc1, string nm2, int sc2)
	{
		name1 = nm1;
		score1 = sc1;
		name2 = nm2;
		score2 = sc2;
	}

	int GetDiff()
	{
		return abs(score1 - score2);
	}

	string getString()
	{
		string line = "";
		line = name1 +"   " + to_string(score1) +"   vs   "+ name2 +"   "+ to_string(score2);
		return line;
	}
};

class mkScore
{
private:

	vector<ScoreLine> score_line;

public:
	mkScore()
	{
		LoadFile();
	}

	void LoadFile()
	{
		ifstream fs("res//scoreboard.txt");

		while (!fs.eof())
		{
			ScoreLine sl;

			fs>>sl.name1 >> sl.score1 >> sl.name2 >>sl.score2;
			score_line.push_back(sl);
		}
		score_line.erase(score_line.end()-1);

		fs.close();
	}

	void ClearScoreBoard()
	{
		score_line.clear();
	}


	vector <ScoreLine> getScoreList()
	{
		return score_line;
	}


	void SaveScore(string p1, int s1, string p2, int s2)
	{
		score_line.push_back(ScoreLine(p1,s1,p2,s2));

		// now if remove the smallest defrence

		if(score_line.size()>5)
		{
			int ind = 0;
			int smallest_dif = score_line[0].GetDiff();
			for(int j=0; j<score_line.size(); j++)
			{
				for(int i=1; i<score_line.size(); i++)
				{
					int temp = score_line[i].GetDiff();
					if(smallest_dif >= temp)
					{
						smallest_dif = temp;
						ind = i;
					}

				}
			}

			score_line.erase(score_line.begin() + ind);

			// now save the scores

			ofstream os("res//scoreboard.txt");

			for(int i=0; i<score_line.size(); i++)
			{
				os<<score_line[i].name1 <<" "<<score_line[i].score1<<" "<<score_line[i].name2<<" "<<score_line[i].score2<<"\n";
			}

			os.close();

		}
		else
		{
			ofstream os("res//scoreboard.txt");

			for(int i=0; i<score_line.size(); i++)
			{
				os<<score_line[i].name1 <<" "<<score_line[i].score1<<" "<<score_line[i].name2<<" "<<score_line[i].score2<<"\n";
			}

			os.close();
		}



	}


};


#endif
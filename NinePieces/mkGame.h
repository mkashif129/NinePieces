/*
Name: Muhammad Kashif
Date: 02 May, 2013
File: mkGame
*/


#ifndef MK_GAME_H
#define MK_GAME_H
#pragma once

#include "mk.h"
#include "mkPlayer.h"
#include "mkScene.h"

class mkGame : public mkScene
{
private:
	static mkPlayer *players[2];
	int turn;

	vector <vec2> left_points,right_points;
	static vector <mkGrid> grid_points;

	static mkPiece *blink_complete;
	//bool is_blink;

	thread p1_back_thread,p2_back_thread;



	static  mutex consegitive_mutex;

	static const int consegitive_point = 64; // UNUSED_VARIABLE: add 64 points per pick 
	static const int reduce_by_shuffle = 48; // reduce 48 points by each shuffle


	static int won;

	mkText *clock_text;
	mkTimer *clock_timer;
	int milli, sec;

	string s_sec;
	string s_milli;

public:
	mkGame()
	{
		turn = 0;
		LoadLeftRightBoxPoints(); // loading box player box points
		LoadGridPoints();


		players[0] = new mkPlayer("res//pblue.png","res//pblue_blink.png",left_points,&grid_points);
		players[1] = new mkPlayer("res//pred.png","res//pred_blink.png",right_points,&grid_points);

		players[1]->EnabledPlayer(false);
		blink_complete = new mkPiece("res//blink1.png","res//blink2.png");


		players[0]->SetOpponent(players[1]);
		players[1]->SetOpponent(players[0]);
		players[0]->SetTurnBlinkPos(vec2(112,130));
		players[1]->SetTurnBlinkPos(vec2(885,130));

		players[0]->SetScoreText("0000",32,mkColor(64,0,0),vec2(110,190));
		players[1]->SetScoreText("0000",32,mkColor(0,0,64),vec2(885,190));

		//players[0]->SetPicktTextPosition(vec2(100,400));
		//players[1]->SetPicktTextPosition(vec2(890,400));

		players[0]->SetPicktTextPosition(vec2(491,397));
		players[1]->SetPicktTextPosition(vec2(491,397));


		p1_back_thread =  thread(mkGame::CheckConsegitivePieces,players[0],0);
		p2_back_thread =  thread(mkGame::CheckConsegitivePieces,players[1],1);

		clock_timer = new mkTimer(1);
		clock_text = new mkText("res//fonts//clockb.ttf",42);
		clock_text->SetPos(vec2(490,300));
		clock_text->SetColor(180,180,180);
		clock_text->SetText("00:00");
		milli = 0;
		sec = 0;
		s_sec = "00";
		s_milli = "00";
	}
	void Skip()
	{
		players[turn]->AddScore(-24);
		players[turn]->EnabledPlayer(false);
		turn++;
		ResetTime();
		turn = turn%2;
		players[turn]->EnabledPlayer(true);

	}
	void Shuffle()
	{
		players[turn]->AddScore(-32);
		players[(turn+1)%2]->Shuffle();
	}

	void ResetGame()
	{
		milli = 0;
		sec = 0;
		won = -1;
		turn = 0;
		players[0]->ResetPlayer();
		players[1]->ResetPlayer();

		players[1]->EnabledPlayer(false);

		players[0]->SetOpponent(players[1]);
		players[1]->SetOpponent(players[0]);
		players[0]->SetTurnBlinkPos(vec2(112,130));
		players[1]->SetTurnBlinkPos(vec2(885,130));

		players[0]->SetScoreText("0000",32,mkColor(64,0,0),vec2(110,190));
		players[1]->SetScoreText("0000",32,mkColor(0,0,64),vec2(885,190));

	}

	
	void SetPlayerNames(string player1_name, string player2_name)
	{
		players[0]->SetNamePad(player1_name,0,vec2(0,50),vec2(100,50),mkColor(64,0,0));
		players[1]->SetNamePad(player2_name,1,vec2(1000,50),vec2(890,50),mkColor(0,0,64));
	}

	void JoinThreads()
	{
		p1_back_thread.join();
		p2_back_thread.join();
	}
	void DetachThreads()
	{
		p1_back_thread.detach();
		p2_back_thread.detach();
	}

	void LoadGridPoints()
	{
		ifstream f("res//grid//grid_points.txt");

		for (int i=0; i<24; i++)
		{
			int __skip_int;
			char __skip_char;
			int __x,__y;

			f>>__skip_int>>__skip_char;
			f>>__x>>__skip_char>>__y;


			mkGrid __temp(vec2(__x,__y));
			grid_points.push_back(__temp);
		}
		f.close();
	}

	// if a piece move on grid the grid points must be upto date
	void UpdateGridPoints()
	{
		vector <mkPiece*> temp_grid_pices;
		vector <mkGrid> temp = grid_points;

		// collecting both player ongrid pieces
		for(int k=0; k<2; k++)
		{
			for(int i=0; i<players[k]->getPieces()->size(); i++)
			{
				if(players[k]->getPieces()->at(i)->IsOnGrid(grid_points))
				{
					temp_grid_pices.push_back(players[k]->getPieces()->at(i));
				}
			}
		}


		//updating gridpoints
		for(int i=0; i<temp_grid_pices.size(); i++)
		{
			for(int j=0; j<temp.size(); j++)
			{
				int ind = mk::FindElement(grid_points,temp[j]);
				if(temp_grid_pices[i]->getPos() == temp[j].point)
				{
					grid_points[ind].is_on = false;
					temp.erase(temp.begin()+j);
				}
				else
				{
					grid_points[ind].is_on = true;
				}
			} 
		}


	}
	void LoadLeftRightBoxPoints()
	{
		ifstream f1("res//grid//left_points.txt");

		// loading file
		for (int i=0; i<9; i++)
		{
			int __x,__y;
			int __skip_int=0;
			char __skip_char=',';

			f1 >>__skip_int >> __skip_char;
			f1 >>__x >> __skip_char;
			f1 >>__y;

			vec2 temp = vec2(__x,__y);

			left_points.push_back(temp);
		}






		ifstream f2("res//grid//right_points.txt");
		// loading file for right points
		for (int i=0; i<9; i++)
		{
			int __x,__y;
			int __skip_int=0;
			char __skip_char=',';

			f2 >>__skip_int >> __skip_char;
			f2 >>__x >> __skip_char;
			f2 >>__y;

			vec2 temp = vec2(__x,__y);

			right_points.push_back(temp);
		}

		f2.close();

	}

	void ResetTime()
	{
		milli = 0;
		sec = 0;
	}

	void HandleGameEvents(SDL_Event event)
	{

		players[turn]->HandleEvent(event);
		if(players[turn]->IsTurnCompleted())
		{
			int t = mk::CheckTime.getSeconds();
			players[turn]->AddScore((-t)/5); // 1/5 per sceond

			players[turn]->TurnCompleted(false); 
			players[turn]->EnabledPlayer(false);
			
			ResetTime();

			turn++;
			turn = turn%2;
			players[turn]->EnabledPlayer(true);

			mk::CheckTime.Start(); // timer start

		}

	}



	void ApplyGameEvents()
	{

		UpdateGridPoints();
		players[turn]->ApplyEvents();

	}


	static void DrawCompleteBlinks(vector<mkCompleteRow> cr)
	{

		blink_complete->Blink(true);
		for(int i=0; i<cr.size(); i++)
		{
			blink_complete->SetPos(cr[i].getPositions(grid_points)[0]);
			blink_complete->draw();
			blink_complete->SetPos(cr[i].getPositions(grid_points)[1]);
			blink_complete->draw();
			blink_complete->SetPos(cr[i].getPositions(grid_points)[2]);
			blink_complete->draw();
		}

	}

	int IsWon()
	{
		return won;
	}

	int GetPlayerScore(int index)
	{
		return players[index]->GetScore();
	}

	string GetPlayerName(int index)
	{
		return players[index]->GetPlayerName();
	}

	static void CheckConsegitivePieces(mkPlayer *p, int p_num)
	{
		while(true)
		{
			
			consegitive_mutex.lock();
			p->total_rows_completed.clear();
			bool iscomplete = false;
			// for player one
			vector <mkPiece*> pieces_on_board;
			for(int i=0; i<p->getPieces()->size(); i++)
			{
				mkPiece *pe = p->getPieces()->at(i);
				if(pe->IsOnGrid(grid_points))
				{
					pieces_on_board.push_back(pe);
				}
			}

			// now check completed row
			for(int j=0; j<pieces_on_board.size(); j++)
			{
				mkPiece *pe = pieces_on_board[j];
				int ind = mk::FindElement(grid_points,pe->getPos());
				int row1[3] = {p->consegitive_pieces[ind].row1[0],p->consegitive_pieces[ind].row1[1],p->consegitive_pieces[ind].row1[2]};
				int row2[3] = {p->consegitive_pieces[ind].row2[0],p->consegitive_pieces[ind].row2[1],p->consegitive_pieces[ind].row2[2]};

				if(p->FindRow(row1))
				{
					p->total_rows_completed.push_back(mkCompleteRow(row1));
					iscomplete = true;
				}
				if(p->FindRow(row2))
				{
					p->total_rows_completed.push_back(mkCompleteRow(row2));
					iscomplete = true;
				}
			}


			/*sort( vec.begin(), vec.end() );
			vec.erase( unique( vec.begin(), vec.end() ), vec.end() );*/

			std::sort(p->total_rows_completed.begin(),p->total_rows_completed.end());
			p->total_rows_completed.erase(unique(p->total_rows_completed.begin(),p->total_rows_completed.end()),p->total_rows_completed.end());

			// removing redundency
			for(int i=0; i<p->total_rows_completed.size(); i++)
			{
				for(int j=1; j<p->total_rows_completed.size(); j++)
				{
					if(i!=j)
					{
						if(p->total_rows_completed[i].IsMatched(p->total_rows_completed[j]))
						{
							p->total_rows_completed.erase(p->total_rows_completed.begin() + j);
						}
					}

				}
			}

			if(p->backup_row_completed == p->total_rows_completed)
				iscomplete = false;

			p->backup_row_completed = p->total_rows_completed;
			pieces_on_board.clear();

			if(iscomplete){
				players[p_num]->Consegitive(true);
				players[(p_num+1)%2]->SetPick(1);

			}
			consegitive_mutex.unlock();

		}// end while

	}// end checking conseigitive


	void BindWithScene()
	{

		players[0]->SetScenePos(scene_pos);
		players[1]->SetScenePos(scene_pos);

	}
	// this will display all elements of both players
	void DisplayGame()
	{
		if(clock_timer->getPulse() && !players[(turn+1)%2]->IsConsegitive())
		{
			
			if(milli<10)
				s_milli = "0"+to_string(milli);
			else
				s_milli = to_string(milli);

			if(milli>=59)
			{
				sec++;
				milli = 0;
				s_sec = to_string(sec);
			}

			milli+=1;
		}
		else if(players[(turn+1)%2]->IsConsegitive())
		{
			milli = 0;
			sec = 0;
			s_milli = "00";
			s_sec = "00";
		}

		clock_text->SetScenePos(scene_pos);
		clock_text->SetText(s_sec+" : "+s_milli);
		clock_text->Draw();
		
		// Check first the wining status
		if(players[0]->getPieces()->size()<3)
		{
			won = 1;
		}
		else if(players[1]->getPieces()->size()<3)
		{
			won = 0;
		}

	
		BindWithScene();

		ApplyGameEvents();
		consegitive_mutex.lock();
		if(players[0]->IsConsegitive())
		{
			vector <mkCompleteRow> cr = players[0]->getCompletedRows();
			DrawCompleteBlinks(cr);
		}

		if(players[1]->IsConsegitive())
		{
			vector <mkCompleteRow> cr = players[1]->getCompletedRows();
			DrawCompleteBlinks(cr);
		}


		// the turn blink is here
		if(players[(turn+1)%2]->IsConsegitive())
		{
			players[(turn+1)%2]->DisplayTurnBlink();

			// draw pick here
			players[(turn+1)%2]->DisplayPickText();

		}
		else
			players[turn]->DisplayTurnBlink();


		

		players[0]->Display();
		players[1]->Display();

		consegitive_mutex.unlock();


		


	}



};

vector <mkGrid> mkGame::grid_points;
mutex mkGame::consegitive_mutex;
mkPlayer *mkGame::players[2];
mkPiece *mkGame::blink_complete;
int mkGame::won = -1;

#endif
/*
Name: Muhammad Kashif
Date: 01 May, 2013
File: mkPlayer.h
*/



#ifndef MK_PLAYER_H
#define MK_PLAYER_H
#pragma once

#include "mk.h"
#include "mkPiece.h"
#include "mkText.h"
#include "mkSound.h"

class mkPlayer
{
private:
	vector <mkPiece*> pieces;
	mkPiece *mouse_pointer; // pointer on grid
	vector <vec2> box_points;
	vector <mkGrid> *grid_points;
	int grid_index;

	vector <mkPath> possible_paths;
	mkPath blink_path;
	mkPiece *blink_pointer;
	bool is_blink;

	vec2 mouse;
	vec2 motion;
	int clicks;
	int selected;

	bool is_enable_player;
	bool turn_completed;

	mkPiece *turn_blink;
	mkPiece *name_pad;
	mkText *text;
	int score;

	int pick;
	bool is_consegitive;
	mkPlayer *opponent;

	vec2 scenepos;
	
	string piec1,piec2;
	mkText *picktext;

	string player_name;
	mkSound *sound;
	bool is_play_sound;
public:
	vector <mkConsegitivePieces> consegitive_pieces;
	vector <mkCompleteRow> total_rows_completed, backup_row_completed;


public:
	mkPlayer(){}
	
	
	mkPlayer(string img1, string img2, vector <vec2> points, vector <mkGrid> *grid_p)
	{
		is_play_sound = true;
		player_name = "player";
		piec1 = img1;
		piec2 = img2;
		grid_points = grid_p;
		box_points = points;
		for(int i=0; i<points.size(); i++)
		{
			mkPiece *p = new mkPiece(img1,img2);
			p->SetPos(points[i]);
			pieces.push_back(p);
		}


		mouse = vec2(0,0);
		clicks = 0;
		selected =0;
		is_enable_player = true;
		turn_completed = false;
		grid_index = 0;
		is_blink = false;
		pick = 0;

		mouse_pointer = new mkPiece("res//mptr.png","res//mptr.png");
		blink_pointer = new mkPiece("res//blink1.png","res//blink2.png");
		turn_blink = new mkPiece("res//on1.png","res//on2.png");
		turn_blink->SetPos(vec2(100,100));
		turn_blink->Blink(true);
		turn_blink->SetTimerDelay(0.5);

		
		LoadPossiblePaths(); // loading single piece possible paths
		LoadConsegitivePieces();
		opponent = NULL;
		is_consegitive = false;

		text = NULL;
		score = 0;
		scenepos = vec2(0,0);
		picktext = new mkText("res//fonts//clockb.ttf",36);
		picktext->SetText("PICK");
		picktext->SetColor(10,255,10);

		
		sound = new mkSound();
		sound->AddSound("res//audio//beep1.wav");
		sound->AddSound("res//audio//beep2.wav");
		sound->AddSound("res//audio//ting1.wav");
		sound->AddSound("res//audio//ting2.wav");
		sound->AddSound("res//audio//click1.wav");
		
	}

	void SetPicktTextPosition(vec2 pos)
	{
		picktext->SetPos(pos);
	}
	void DisplayPickText()
	{
		picktext->Draw();
	}
	int GetScore()
	{
		return score;
	}
	void ResetPlayer()
	{
		//making on all grids points
		for(int i=0; i<grid_points->size(); i++)
		{
			grid_points->at(i).is_on = true;
		}

		pieces.clear();

		for(int i=0; i<box_points.size(); i++)
		{
			mkPiece *p = new mkPiece(piec1,piec2);
			p->SetPos(box_points[i]);
			pieces.push_back(p);
		}



		mouse = vec2(0,0);
		clicks = 0;
		selected =0;
		is_enable_player = true;
		turn_completed = false;
		grid_index = 0;
		is_blink = false;
		pick = 0;

		turn_blink->SetPos(vec2(100,100));
		turn_blink->Blink(true);
		turn_blink->SetTimerDelay(0.5);

		
		opponent = NULL;
		is_consegitive = false;

		text = NULL;
		score = 0;
		scenepos = vec2(0,0);
	}

	void SetScenePos(vec2 sp)
	{
		scenepos =  sp;
	}

	

	void SetScoreText(string txt, int size, mkColor col, vec2 pos)
	{
		text = new mkText("res//fonts//segb.ttf",size);
		text->SetColor(col.r,col.g,col.b);
		text->SetPos(pos);
		text->SetText(txt);
	}
	
	void AddScore(int scr)
	{
		score += scr;
		string temp = "";
		if(score<10)
			temp = "000";
		if(score>9 && score<100)
			temp = "00";
		if(score > 99 && score<1000)
			temp = "0";
		
		if(score<0)
			score = 0;

		temp += to_string(score); // i thinks this concatination also in c++11
		text->SetText(temp); // std::to_string() c++11
	}

	void SetNamePad(string txt, int pl, vec2 strt, vec2 end,mkColor col)
	{
		if(pl==0)
		{
			name_pad = new mkPiece("res//name_pad_left.png","res//name_pad_left.png");
			
		}
		else
		{
			name_pad = new mkPiece("res//name_pad_right.png","res//name_pad_right.png");
		}

		name_pad->SetPos(strt);
		name_pad->Move(true);
		name_pad->MoveTo(end);
		name_pad->SetText(txt,24,col);
		player_name = txt;
	}

	string GetPlayerName()
	{
		return player_name;
	}

	void SetTurnBlinkPos(vec2 pos)
	{
		turn_blink->SetPos(pos);
	}
	void DisplayTurnBlink()
	{
		turn_blink->draw();
	}

	bool IsConsegitive()
	{
		return is_consegitive;
	}

	void Consegitive(bool con)
	{
		is_consegitive = con;
	}

	void SetOpponent(mkPlayer *p)
	{
		opponent = p;
	}
	void SetPick(int pick)
	{
		this->pick = pick;
	}
	int getPick()
	{
		return pick;
	}
	void LoadPossiblePaths()
	{
		ifstream f("res//grid//possible_paths.txt");

		for(int i=0; i<24; i++)
		{
			int a,b,c,d;
			int skip;
			f>>skip;
			f>>a>>b>>c>>d;
			mkPath path = mkPath(a,b,c,d);
			possible_paths.push_back(path);
		}

		f.close();
	}
	void LoadConsegitivePieces()
	{
		ifstream f("res//grid//consegitive_pieces.txt");

		for(int i=0; i<24; i++)
		{
			int skip;
			int a,b,c,d,e;
			f>>a>>b>>c>>d>>e;
			consegitive_pieces.push_back(mkConsegitivePieces(a,b,c,a,d,e));
		}

		f.close();
	}

	
	vector<mkCompleteRow> getCompletedRows()
	{
		return total_rows_completed;
	}
	bool FindRow(int row[3])
	{
		int found = 0;
		for (int k=1; k<3; k++)
		{
			for(int i=0; i<pieces.size(); i++)
			{
				if(pieces[i]->getPos() == grid_points->at(row[k]).point)
				{
					found++;
				}
			}
		}

		if(found == 2)
		{
			return true;
		}
		else
			return false;

	}

	
	void FindBlinkPath(vec2 piece)
	{
		int ind = mk::FindElement(*grid_points,piece);
		blink_path = possible_paths[ind];

		// removing off grids points DONE
		for (int i=0; i<4; i++)
		{
			if(blink_path.paths[i] != -1)
			{
				if(grid_points->at(blink_path.paths[i]).is_on == false)
				{
					blink_path.paths[i] = -1;
				}
			}
		}

	}
	void ShowBlinks()
	{
		for(int i=0; i<4; i++)
		{
			if(blink_path.paths[i] != -1)
			{
				vec2 p = grid_points->at(blink_path.paths[i]).point;
				blink_pointer->SetPos(p);
				blink_pointer->Blink(true);
				blink_pointer->draw();
			}
		}
	}

	void Shuffle()
	{
		vector <mkPiece*> pieces_on_board;
		for(int i=0; i<this->getPieces()->size(); i++)
		{
			mkPiece *p = this->getPieces()->at(i);
			if(p->IsOnGrid(*grid_points))
			{
				pieces_on_board.push_back(p);
			}
		}

		vector <vec2> locations;

		for(int i=0; i<grid_points->size(); i++)
		{
			if(grid_points->at(i).is_on) 
			{
				locations.push_back(grid_points->at(i).point);
			}
		}

		srand(time(0));
		for(int i=0; i<locations.size(); i++)
		{
			swap(locations[rand()%locations.size()],locations[rand()%locations.size()]);
		}

		// now move to
		if(locations.size()<=pieces_on_board.size())
		{
			for(int i=0; i<locations.size(); i++)
			{
				pieces_on_board[i]->Move(true);
				pieces_on_board[i]->MoveTo(locations[i]);
			}
		}
		else if(locations.size()>pieces_on_board.size())
		{
			for(int i=0; i<pieces_on_board.size(); i++)
			{
				pieces_on_board[i]->Move(true);
				pieces_on_board[i]->MoveTo(locations[i]);
			}
		}

		
	}




	vec2 AttractToGrid(vec2 any)
	{
		vec2 nearpoint = grid_points->at(0).point;
		for(int i=0; i<grid_points->size(); i++)
		{
			for(int j=1; j<grid_points->size(); j++)
			{
				vec2 p2 = grid_points->at(j).point;
				if(abs(FindDistance(any,p2)) < abs(FindDistance(nearpoint,any)))
					nearpoint = p2;
			}
		}

		// finding grid index
		for(int i=0; i<grid_points->size(); i++)
		{
			if(grid_points->at(i).point == nearpoint)
			{
				grid_index = i;
				break;
			}
		}

		return nearpoint;
	}

	float FindDistance(vec2 p1, vec2 p2)
	{
		float dx2 = pow (p1.x - p2.x,2);
		float dy2 = pow (p1.y - p2.y,2);
		float dist = sqrt(dx2 + dy2);
		return dist;
	}


	void HandleEvent(SDL_Event event)
	{
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			motion.x = event.motion.x;
			motion.y = event.motion.y;

			// restricting to grid
			mouse_pointer->SetPos(AttractToGrid(motion));

			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse.x = event.button.x;
			mouse.y = event.button.y;
			clicks++;
			is_play_sound = true;
			break;
		case SDL_MOUSEBUTTONUP:



			break;


		default:
			break;
		}
	}

	bool FindClick()
	{
		for(int i=0; i<pieces.size(); i++)
		{
			if(pieces[i]->IsEnabled()) // if a piece itself is enabled
			{
				if(mk::detectMouse(pieces[i]->getRect(),mouse))
				{
					selected = i;
					return true;
				}
			}

		}

		return false;
	}

	void ApplyEvents()
	{


		if(is_enable_player)
		{
			if(clicks == 1 && pick == 1 && FindClick()) // piking event
			{
				if(pieces[selected]->IsOnGrid(*grid_points))
				{
					pieces.erase(pieces.begin() + selected);
					grid_points->at(grid_index).is_on = true;
					clicks = 0;
					pick = 2; // picked
					//Consegitive(false);
					//opponent->Shuffle();
					
					opponent->AddScore(64);
					opponent->Consegitive(false);

					if(is_play_sound){
						sound->Play(1);
						is_play_sound = false;
					}
				}
				else
				{
					clicks = 0;
				}
			}
			else if(clicks == 1 && FindClick())
			{
				pieces[selected]->Blink(true);
				UnBlinkWithout(selected);

				if(pieces[selected]->IsOnGrid(*grid_points))
				{
					is_blink = true;
					FindBlinkPath(pieces[selected]->getPos());
				}

				if(is_play_sound){
					sound->Play(2);
					is_play_sound = false;
				}


			}
			else if(clicks == 2 && FindClick())
			{
				pieces[selected]->Blink(true);
				UnBlinkWithout(selected);
				clicks = 1;
			}
			else if(clicks == 2 && !FindClick())
			{
				if(pieces[selected]->IsBlink() && grid_points->at(grid_index).is_on)
				{
					// moving on path if its on grid
					if(pieces[selected]->IsOnGrid(*grid_points))
					{

						if(is_play_sound){
							sound->Play(3);
							is_play_sound = false;
						}

						for(int i=0; i<4; i++)
						{
							if(blink_path.paths[i] != -1)
							{
								if(grid_points->at(blink_path.paths[i]).point == mouse_pointer->getPos())
								{
									pieces[selected]->Move(true);
									pieces[selected]->MoveTo(mouse_pointer->getPos());


									// making off grid point
									grid_points->at(grid_index).is_on = false;


									turn_completed = true;
									is_blink = false;
									pick = 0;

								}else
								{
									clicks = 1;
								}
							}
						}
					}
					else
					{
						// moving from left rigth box
						pieces[selected]->Move(true);
						pieces[selected]->MoveTo(mouse_pointer->getPos());
						// making off grid point
						grid_points->at(grid_index).is_on = false;

						turn_completed = true;
						is_blink = false;

						if(is_play_sound){
							sound->Play(3);
							is_play_sound = false;
						}

					}



				}
				clicks = 0;

				

			}// end click 2 !find move

		}

	}


	int getSelectedIndex()
	{
		return selected;
	}


	vector <mkPiece*> *getPieces()
	{
		return &pieces;
	}

	void UnBlinkWithout(int j)
	{
		for(int i=0; i<pieces.size(); i++)
		{
			if(i!=j)
			{
				pieces[i]->Blink(false);

			}
		}
	}

	void TurnCompleted(bool turnc)
	{
		turn_completed = turnc;
	}

	bool IsTurnCompleted()
	{
		return turn_completed;
	}

	void EnabledPlayer(bool enable)
	{
		is_enable_player = enable;
	}
	bool IsEnabled()
	{
		return is_enable_player;
	}

	void BindWidthScene()
	{
		name_pad->SetScenePos(scenepos);
		turn_blink->SetScenePos(scenepos);
		text->SetScenePos(scenepos);
		for(int i=0; i<pieces.size(); i++)
		{
			pieces[i]->SetScenePos(scenepos);
			
		}
		
	}

	void Display()
	{
		BindWidthScene();

		if(is_enable_player)
		{

			// drwing mouse pointer
			if(abs(FindDistance(motion,mouse_pointer->getPos())<50) && grid_points->at(grid_index).is_on)
				mouse_pointer->draw();

			if(is_blink)
			{
				ShowBlinks();
			}

			for(int i=0; i<pieces.size(); i++)
			{
				pieces[i]->draw();
			}


		}
		else
		{
			for(int i=0; i<pieces.size(); i++)
			{
				pieces[i]->draw();
			}
		}

		name_pad->draw();
		if(text!=NULL)
			text->Draw();

	}
};


#endif

/*
Name: Muhammad Kashif
Date: 01 May, 2013
File: mkPlayer.h
*/



#ifndef MK_NINEPIECES_H
#define MK_NINEPIECES_H
#pragma once

#include "mk.h"
#include "mkPiece.h"
#include "mkText.h"
#include "mkGame.h"
#include "mkScene.h"
#include "mkSound.h"
#include "mkScore.h"

class mkNinePieces
{
private:
	enum GameScene {START,INTRO,MENU,SINGLE,MULTI,SCORE,ABOUT,GAME};

private:
	mkScene *game_scenes[8];
	int current_scene,previous_scene,comming_scene;
	

	mkTimer *start_timer;
	mkLogo *logo;
	mkWindow *window;

	mkSound *sounds;

	mkScore *score_board;

public:
	mkNinePieces(mkWindow *win)
	{
		sounds = new mkSound();
		sounds->AddSound("res//audio//outgame.it");
		sounds->AddSound("res//audio//beep1.wav");
		sounds->AddSound("res//audio//beep2.wav");
		sounds->AddSound("res//audio//tick1.wav");
		sounds->AddSound("res//audio//tick2.wav");
		sounds->AddSound("res//audio//ting1.wav");
		sounds->AddSound("res//audio//ting2.wav");
		sounds->AddSound("res//audio//ingame.it");
		sounds->Play(0);
		

		score_board = new mkScore();


		logo = new mkLogo(vec2(460,280));
		window = win;
		previous_scene = current_scene = 0; // sajid lala style
		comming_scene = 1;

		start_timer = new mkTimer(5);
		start_timer->start();

		for(int i=0; i<7; i++){
			game_scenes[i] = new mkScene();
		}
		
		

		// start scene
		game_scenes[0]->SetBackgroundImage("res//start_bg.png"); // game start
		game_scenes[0]->LogoDisplay(true);
		game_scenes[1]->SetBackgroundImage("res//intro_bg.png"); // introduction
		game_scenes[1]->SetPosition(vec2(1000,0));


		// MENU SCREEN =================================== STARTS
		game_scenes[2]->SetBackgroundImage("res//menu_bg.png"); // menu screen
		game_scenes[2]->SetPosition(vec2(1000,0));

		int t = 60;
		mkButton *play = new mkButton("res//cntrl//play11.png","res//cntrl//play22.png",vec2(517,240 + t*1),0);
		mkButton *score = new mkButton("res//cntrl//score1.png","res//cntrl//score2.png",vec2(517,240 + t*2),2);
		mkButton *about = new mkButton("res//cntrl//about1.png","res//cntrl//about2.png",vec2(517,240 + t*3 ),3);
		mkButton *exit   = new mkButton("res//cntrl//exit1.png","res//cntrl//exit2.png",vec2(517,240 + t*4),4);

		game_scenes[2]->AddButtons(play)->AddButtons(score)->AddButtons(about)->AddButtons(exit);

		mkScene *menu_scene = game_scenes[2];
		mkScene *single_scene = game_scenes[3];
		mkScene *multi_scene = game_scenes[4];
		mkScene *saved_scene = game_scenes[5];
		mkScene *about_scene = game_scenes[6];



		// 0: start
		// 1: intro
		// 2: menu
		// 3: play
		// 4: multi
		// 5: saved
		// 6: about
		// 7: Game

		int *current = &current_scene;
		int *previous = &previous_scene;
		int *comming = &comming_scene;

		// Menu play 
		play->onClicks.push_back([this,multi_scene, menu_scene,current, previous, comming](mkInterface *obj, int id){
			
			multi_scene->MoveIn();
			menu_scene->MoveLeftOut();

			*previous = *current;
			*current = this->MULTI;
			this->sounds->Play(2);
		});

		play->onOvers.push_back([this](){
			this->sounds->Play(1);
		});


		score->onOvers.push_back([this](){
			this->sounds->Play(1);
		});

		about->onOvers.push_back([this](){
			this->sounds->Play(1);
		});
		exit->onOvers.push_back([this](){
			this->sounds->Play(1);
		});

		
		// Menu Saved
		score->onClicks.push_back([this,saved_scene, menu_scene,current, previous, comming](mkInterface *obj, int id){
			saved_scene->MoveIn();
			menu_scene->MoveLeftOut();
			*previous = *current;
			*current = 5;
			*comming = -1;
			this->sounds->Play(2);

			this->score_board->ClearScoreBoard();
			this->score_board->LoadFile();
			
			vector <ScoreLine> score_list = this->score_board->getScoreList();
			this->game_scenes[this->SCORE]->ClearText();

			if(score_list.size()>0)
			{
				for(int i=0; i<score_list.size(); i++)
				{
					this->game_scenes[this->SCORE]->AddText(score_list[i].getString());
				}
			}
			else
			{
				this->game_scenes[this->SCORE]->AddText("EMPTY");
			}

		});

		// Menu About
		about->onClicks.push_back([this,about_scene, menu_scene,current, previous, comming](mkInterface *obj, int id){
			
			about_scene->MoveIn();
			menu_scene->MoveLeftOut();
			*previous = *current;
			*current = 6;
			*comming = -1;
			this->sounds->Play(2);
		});

		exit->onClicks.push_back([this](mkInterface *obj, int id){
			
			this->sounds->Play(2);
			this->sounds->Stop();
			this->ExitWindow();
		});

		// ENDS MENU SCREEN


		// SNGLE PLAYER SCREEN =========================== STARTS
		game_scenes[3]->SetBackgroundImage("res//single_bg.png");
		game_scenes[3]->SetPosition(vec2(1000,0));
		mkButton *play1 = new mkButton("res//cntrl//play1.png","res//cntrl//play2.png",vec2(865,480),5);
		mkButton *back1 = new mkButton("res//cntrl//back1.png","res//cntrl//back2.png",vec2(150,480),6);
		mkFreeType *player_bx = new mkFreeType(vec2(614,365));
		mkButton *edit = new mkButton("res//cntrl//edit1.png","res//cntrl//edit1.png",vec2(750,370),7);
		game_scenes[3]->AddButtons(play1)->AddButtons(back1)->AddButtons(edit)->AddFreeType(player_bx);
		// END SNGLE SCREEN


		// MULTI PLAYER SCREEN =========================== STARTS
		game_scenes[4]->SetBackgroundImage("res//multi_bg.png");
		game_scenes[4]->SetPosition(vec2(1000,0));
		mkButton *play2 = new mkButton("res//cntrl//play1.png","res//cntrl//play2.png",vec2(865,480),8);
		mkButton *back2 = new mkButton("res//cntrl//back1.png","res//cntrl//back2.png",vec2(150,480),9);

		mkFreeType *player1_bx = new mkFreeType(vec2(614,337));
		mkFreeType *player2_bx = new mkFreeType(vec2(614,337+60));
		mkButton *editp11 = new mkButton("res//cntrl//edit1.png","res//cntrl//edit1.png",vec2(750,337),10);
		mkButton *editp12 = new mkButton("res//cntrl//edit1.png","res//cntrl//edit1.png",vec2(750,337+65),11);

		

		game_scenes[4]->AddFreeType(player1_bx)->AddFreeType(player2_bx);
		game_scenes[4]->AddButtons(play2)->AddButtons(back2);
		game_scenes[4]->AddButtons(editp11)->AddButtons(editp12);
		
		// edit button functions
		editp11->onClicks.push_back([this](mkInterface *obj, int id){
			
			mkScene * scn = (mkScene*)obj;
			scn->getFreeType()[0]->Select(true);
			scn->getFreeType()[1]->Select(false);
			
			this->sounds->Play(2);
		});
		// edit button for textbox 2
		editp12->onClicks.push_back([this](mkInterface *obj, int id){
			
			mkScene * scn = (mkScene*)obj;
			scn->getFreeType()[1]->Select(true);
			scn->getFreeType()[0]->Select(false);
			this->sounds->Play(2);
		});

		play2->onClicks.push_back([this, previous,current](mkInterface *obj, int id){
		
			((mkGame*)this->game_scenes[this->GAME])->ResetGame();
			((mkScene*)obj)->MoveLeftOut();
			this->game_scenes[7]->MoveIn();
			
			string name1 = ((mkScene*)obj)->getFreeType()[0]->getText();
			string name2 = ((mkScene*)obj)->getFreeType()[1]->getText();
			
			if(name1 == "" || name1 == "enter name"){name1 = "Player1";}
			if(name2 == "" || name2 == "enter name"){name2 = "Player2";}
			

			((mkGame*)this->game_scenes[7])->SetPlayerNames(name1,name2);

			*previous = *current;
			*current = 7;
			
			this->sounds->Stop();
			this->sounds->Play(2);
			this->sounds->Play(7);
		
		});

		back2->onClicks.push_back([this,menu_scene,current, previous, comming](mkInterface *obj, int id){
			
			((mkScene*)obj)->MoveRightOut();
			menu_scene->MoveIn();

			*previous = *current;
			*current = 2;
			*comming = -1;
			this->sounds->Play(2);

		});

		// ENDS MULTI SCREEN DONE



		// SCORE SCREEN ========================================== STARTS
		game_scenes[5]->SetBackgroundImage("res//score_bg.png");
		game_scenes[5]->SetPosition(vec2(1000,0));

		mkButton *back_button_svd = new mkButton("res//cntrl//back1.png","res//cntrl//back1.png",vec2(130,580),9);
		game_scenes[5]->AddButtons(back_button_svd);
		back_button_svd->onClicks.push_back([this,menu_scene,current, previous, comming](mkInterface *obj, int id){
			
			((mkScene*)obj)->MoveRightOut();
			menu_scene->MoveIn();

			*previous = *current;
			*current = 2;
			*comming = -1;
			this->sounds->Play(2);

			
		});
	
		// ENDS SCORE SCREEN 

		// ABOUT SCREEN ========================================== STARTS
		game_scenes[6]->SetBackgroundImage("res//about.png");
		game_scenes[6]->SetPosition(vec2(1000,0));

		mkButton *back_button_abt = new mkButton("res//cntrl//back1.png","res//cntrl//back1.png",vec2(140,550),9);
		game_scenes[6]->AddButtons(back_button_abt);
		back_button_abt->onClicks.push_back([this,menu_scene,current, previous, comming](mkInterface *obj, int id){
			
			((mkScene*)obj)->MoveRightOut();
			menu_scene->MoveIn();

			*previous = *current;
			*current = 2;
			*comming = -1;
			this->sounds->Play(2);
		});
	
		// ENDS SAVED SCREEN 
		SetGame(previous,current);
	

	}
	
	void SetGame(int *previous, int *current)
	{
		// GAME SCREEN  ======================================== STARTS
		game_scenes[7] = new mkGame();
		game_scenes[7]->SetBackgroundImage("res//background3.png");
		game_scenes[7]->SetPosition(vec2(1000,0));

		int t = 40;

		mkButton *wexit = new mkButton("res//cntrl//wexit.png","res//cntrl//wexit.png",vec2(t+400, 605),20);
		mkButton *wshuffle = new mkButton("res//cntrl//wshuffle.png","res//cntrl//wshuffle.png",vec2(t+450, 605),20);
		mkButton *wskip = new mkButton("res//cntrl//wskip.png","res//cntrl//wskip.png",vec2(t+500, 605),20);

		game_scenes[7]->AddButtons(wexit)->AddButtons(wshuffle)->AddButtons(wskip);


		wexit->onClicks.push_back([this, previous, current](mkInterface *obj, int id){
		
			this->game_scenes[this->MENU]->MoveIn();
			this->game_scenes[this->GAME]->MoveRightOut();
			
			*previous = *current;
			*current = 2;
			this->sounds->Play(2);
			this->sounds->Stop();
			this->sounds->Play(0);
		});


		wshuffle->onClicks.push_back([this,previous,current](mkInterface *obj, int id){
			
			((mkGame*)this->game_scenes[this->GAME])->Shuffle();
			this->sounds->Play(2);
		});

		wskip->onClicks.push_back([this,previous,current](mkInterface *obj, int id){
			
			((mkGame*)this->game_scenes[this->GAME])->Skip();
			this->sounds->Play(2);
		});


		// ENDS GAME SCREEN

	}

	void HandleEvents(SDL_Event events)
	{
		if(current_scene == 7)
			((mkGame*)game_scenes[7])->HandleGameEvents(events);

		game_scenes[current_scene]->HandleEvents(events); // displaying scene 

	}

	void SaveScore()
	{
		mkGame *gm = ((mkGame*)game_scenes[this->GAME]);
		ofstream os("scoreboard.txt",fstream::out | fstream::app);
		os<<gm->GetPlayerName(0) << " "<<gm->GetPlayerScore(0);
		os<<gm->GetPlayerName(1) << " "<<gm->GetPlayerScore(1);

		os.close();
	}


	// display game scenes
	void DisplayGame()
	{
	
		

		game_scenes[previous_scene]->Display(); // previuos  scene
		game_scenes[current_scene]->Display(); // displaying scene 

		if(current_scene == 7)
		{
			((mkGame*)game_scenes[7])->DisplayGame(); //=============== *WINNIND POINT* ===============//
			int w = ((mkGame*)game_scenes[7])->IsWon();
			if(w!=-1)
			{
				mkGame *gm = ((mkGame*)game_scenes[this->GAME]);
				string p1 = gm->GetPlayerName(0);
				int s1 = gm->GetPlayerScore(0);
				string p2 = gm->GetPlayerName(1);
				int s2 = gm->GetPlayerScore(1);

				score_board->SaveScore(p1,s1,p2,s2);

				this->game_scenes[this->MENU]->MoveIn();
				this->game_scenes[this->GAME]->MoveRightOut();

				previous_scene = current_scene;
				current_scene = 2;
			}
		
		}

		if(comming_scene != -1)
			game_scenes[comming_scene]->Display(); // waiting scene
		
		

		
		if(start_timer->getPulse())
		{
			game_scenes[current_scene]->MoveLeftOut();
			game_scenes[comming_scene]->MoveIn();
			previous_scene = current_scene;
			current_scene = comming_scene;

			comming_scene++;
			if(comming_scene == 3)
			{
				start_timer->stop();
			}
			
		}

		if(current_scene == this->START)
			logo->Draw();
		
	}

	mkGame *getGame()
	{
		return (mkGame*)game_scenes[7];
	}

	void ExitWindow()
	{
		window->StopRunning();
	}
};


#endif
/*
Name: Muhammad Kashif
Date: 08 May, 2013
File: mkFreeType

Desc: Singleton class
*/

#ifndef MK_LOGO_H
#define MK_LOGO_H
#pragma once

#include "mk.h"
#include "mkTimer.h"
#include "mkPiece.h"


class mkLogo
{
private:
	vec2 pos;
	mkPiece *logo[7]; // 9 logo pieces and 1 logo background
	mkPiece *text[7];  // 9 Pieces = 7
	mkTimer *timer;

	int logo_index;

	
public:
	mkLogo(vec2 p)
	{
		// 450,280
		pos = p;
		

		mkImage *logo_p = new mkImage("res//logo//logo_p.png");
		mkImage *nine = new mkImage("res//logo//9.png");
		mkImage *pp = new mkImage("res//logo//p.png");
		mkImage *i = new mkImage("res//logo//i.png");
		mkImage *e = new mkImage("res//logo//e.png");
		mkImage *c = new mkImage("res//logo//c.png");
		mkImage *s = new mkImage("res//logo//s.png");
		

		for(int i=1; i<7; i++){
			logo[i] = new mkPiece(new mkImage(*logo_p));
		}
		logo[0] = new mkPiece(new mkImage("res//logo//logo_bck.png"));

		text[0] = new mkPiece(nine);
		text[1] = new mkPiece(pp);
		text[2] = new mkPiece(i);
		text[3] = new mkPiece(e);
		text[4] = new mkPiece(c);
		text[5] = new mkPiece(new mkImage(*e));
		text[6] = new mkPiece(s);

		srand(time(0));
		// now setting logo
		for(int i=0; i<7; i++)
		{
			int x = rand()%2000;
			int y = rand()%2000;

			logo[i]->SetPos(vec2(x,y));
		}

		MoveTo();
		timer = new mkTimer(0.3);
		logo_index = 0;
	}

	void MoveTo()
	{
		logo[0]->MoveTo(vec2(-1,26)+pos);
		logo[1]->MoveTo(vec2(0,51)+pos);
		logo[2]->MoveTo(vec2(-25,51)+pos);
		logo[3]->MoveTo(vec2(-25,25)+pos);
		logo[4]->MoveTo(vec2(25,25)+pos);
		logo[5]->MoveTo(vec2(25,0)+pos);
		logo[6]->MoveTo(vec2(0,0)+pos);

		text[0]->MoveTo(vec2(-80,40)+pos); // 9
		text[1]->MoveTo(vec2(60,20)+pos);  // p 
		text[2]->MoveTo(vec2(90,20)+pos);  // i 
		text[3]->MoveTo(vec2(115,20)+pos); // e
		text[4]->MoveTo(vec2(150,20)+pos); // c
		text[5]->MoveTo(vec2(185,20)+pos); // e
		text[6]->MoveTo(vec2(220,20)+pos); // s



	}

	void Draw()
	{
		for(int i=0; i<7; i++)
		{
			logo[i]->draw();
			text[i]->draw();
		}

		if(timer->getPulse() && logo_index<7)
		{
			logo[logo_index]->Move(true);
			text[logo_index]->Move(true);
			logo_index++;
		}

			
		
	}


};


#endif
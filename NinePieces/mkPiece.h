/*
Name: Muhammad Kashif
Date: 01 May, 2013
File: mkPices
*/


#ifndef MK_PIECE_H
#define MK_PIECE_H
#pragma once

#include "mk.h"
#include "mkImage.h"
#include "mkTimer.h"
#include "mkText.h"


class mkPiece
{
private:
	mkImage *piece[2];
	int index;
	mkTimer *timer;
	bool is_blink;
	
	
	vec2 pos,pos_backup,pos_to;
	float speed, acc;
	float anim_index;// interpolation 0->1
	bool is_move;
	bool is_enabled;

	mkText *text;
	
	vec2 scenepos;

	
public:
	mkPiece(){}


	mkPiece(string img1,string img2)
	{
		
		piece[0] = new mkImage(img1); // loading images
		piece[1] = new mkImage(img2);
		index = 0;
		is_blink = false;
		timer = new mkTimer(0.1);
		pos = vec2(0,0);
		pos_to = pos_backup = pos;
		is_move = false;
		anim_index = 0;

		speed = 0;
		acc = 0.001;
		is_enabled = true;
		scenepos = vec2(0,0);
		text  = NULL;


	}

	
	mkPiece(mkImage *img)
	{
		piece[0] = new mkImage(*img);  // pre loaded images
		piece[1] = new mkImage(*img);
		index = 0;
		is_blink = false;
		timer = new mkTimer(0.1);
		pos = vec2(0,0);
		pos_to = pos_backup = pos;
		is_move = false;
		anim_index = 0;

		speed = 0;
		acc = 0.001;
		is_enabled = true;

		text  = NULL;
	}

	vec2 getPosBackUp()
	{
		return pos_backup;
	}

	void SetText(string txt,int size,mkColor col)
	{
		text = new mkText("res//fonts//segb.ttf",size);
		text->SetPos(pos);
		text->SetText(txt);
		text->SetColor(col.r,col.g,col.b);

	}

	void SetTimerDelay(double millisecond)
	{
		delete []timer;
		timer = new mkTimer(millisecond);
	}

	~mkPiece()
	{
		delete []piece;
		delete []timer;
	}

	
	bool IsOnGrid(vector <mkGrid> grid_points)
	{
		for(int i=0; i<grid_points.size(); i++)
		{
			if(pos == grid_points[i].point)
				return true;
		}

		return false;
	}

	vec2 getPosOnGrid(vector<mkGrid> grid)
	{
		for(int i=0; i<grid.size(); i++)
		{
			if(pos == grid[i].point)
				return pos;
		}

		return vec2(-1,-1);
	}

	void Enabled(bool enable)
	{
		is_enabled = enable;
	}
	bool IsEnabled()
	{
		return is_enabled;
	}
	void SetPos(vec2 pos)
	{
		this->pos_backup = this->pos = pos;
	}
	void SetScenePos(vec2 sp)
	{
		scenepos = sp;
	}
	void Blink(bool blink)
	{
		if(blink == false)
			index = 0;
		this->is_blink = blink;
	}

	bool IsBlink()
	{
		return is_blink;
	}


	void Move(bool move)
	{
		is_move = move;
	}
	bool IsMove()
	{
		return is_move;
	}
	void MoveTo(vec2 to)
	{
		pos_to = to;
		// P = (1-i)*P1 + i*P2
	
	}

	SDL_Rect getRect()
	{
		SDL_Rect rect = {pos.x,pos.y,piece[0]->getWidth(),piece[1]->getHeight()};
		return rect;
	}

	vec2 getPos()
	{
		return pos;
	}
	vec2 getPosTo()
	{
		return pos_to;
	}


	
	void draw()
	{
		if(is_enabled)
		{
			piece[index]->draw(pos+scenepos);
		
			// moving 
			if(is_move)
			{
				pos = (1-anim_index)*pos_backup + anim_index*pos_to;
				anim_index+=speed;
				speed+=acc;

				if(anim_index>1)
				{
					anim_index = 0;
					pos_backup = pos;
					is_move = false;
					pos = pos_to;
					speed = 0;
					is_blink = false;

					index  = 0;
				}
			}


			if(is_blink)
			{
				if(timer->getPulse())
				{
					index++;
					index = index%2;
				}
			}
		}
		else
		{
			piece[1]->draw(pos+scenepos); // showing disabled
		}

		if(text!=NULL)
			text->Draw(pos-vec2(0,5)+scenepos);
	}


};


#endif
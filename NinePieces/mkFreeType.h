/*
Name: Muhammad Kashif
Date: 07 May, 2013
File: mkFreeType

Desc: Not effecient load each time on text change
*/


#ifndef MK_FREETYPE_H
#define MK_FREETYPE_H
#pragma once

#include "mk.h"
#include "mkText.h"
#include "mkInterface.h"
#include "mkSound.h"

class mkFreeType : public mkInterface
{
private:
	mkText *text;
	string txt;

	bool is_key;
	char c;
	bool is_selected;

	vec2 pos, display_pos;
	int mx, my;

	mkSound *type_sound;

public:
	mkFreeType(vec2 pos)
	{
		text = new mkText("res//fonts//segb.ttf",24);
		setPos(pos);
		text->SetColor(64,64,46);
		text->SetText("enter name");
		is_key = false;
		c =' ';
		is_selected = false;
		mx = 0;
		my = 0;

		type_sound = new mkSound();
		type_sound->AddSound("res//audio//click1.wav");
	}

	void HandleEvents(SDL_Event events)
	{
		switch (events.type)
		{
		case SDL_MOUSEBUTTONUP:

			mx = events.button.x;
			my = events.button.y;
			break;

		case SDL_KEYDOWN:
			c = events.key.keysym.unicode;
			is_key = true;
			break;

		case SDL_KEYUP:
			is_key = false;
			break;
		default:
			break;
		}
	}

	void Select(bool select)
	{
		is_selected  = select;

		if(select)
		{
			txt = "___";
			text->SetText(txt);
		}
		else if(txt == "" || txt == "___")
		{
			txt = "enter name";
			text->SetText(txt);
		}
	}
	bool IsSelected()
	{
		return is_selected;
	}

	void ApplyEvents()
	{
		if(is_key & is_selected)
		{
			type_sound->Play(0);
			this->AddChar(c);
			is_key = false;
		}
	}

	

	string getText()
	{
		return txt;
	}
	void setPos(vec2 pos)
	{
		this->display_pos =  this->pos = pos;
	}
	vec2 getPos()
	{
		return pos;
	}
	void setDisplayPos(vec2 pos)
	{
		 display_pos = pos;
		 text->SetPos(display_pos);
	}
	vec2 getDisplayPos()
	{
		return display_pos;
	}

	void AddChar(char c)
	{
		if(c == 8)
		{
			if(txt.size()!=0)
			{
				txt.erase(txt.begin() + txt.size()-1);
			}
		}
		if(txt.size()<11)
		{
			if(FilterChar(c))
			{
				txt+=c;
			}
			

			text->SetText(txt);
		}

		
	}

	bool FilterChar(char c)
	{
		for(char i='0'; i<='z'; i++)
		{
			if(c==i)
			return true;
		}
		
		return false;
	}
	void Draw()
	{
		ApplyEvents();
		text->Draw();
	
	}

};

#endif
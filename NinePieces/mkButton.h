/*
Name: Muhammad Kashif
Date: 07 May, 2013
File: mkButton
*/


#ifndef MK_BUTTON_H
#define MK_BUTTON_H
#pragma once

#include "mk.h"
#include "mkPlayer.h"
#include "mkInterface.h"


class mkButton : public mkInterface
{
private:
	mkImage *button[2];
	vec2 pos,display_pos;
	bool is_clicked;
	bool is_over;

	bool call_on_click;
	bool call_on_over;
	vec2 mouse;
	int id;
	mkInterface *button_parent;

public:
	vector <function<void(mkInterface *obj, int this_id)>> onClicks;
	vector <function<void()>> onOvers;

public:
	mkButton(string img1, string img2, vec2 pos, int id)
	{
		button[0] = new mkImage(img1);
		button[1] = new mkImage(img2);
		setPos(pos);
		mouse = vec2(0,0);

		is_clicked  = false;
		is_over = false;
		call_on_click = false;
		call_on_over = false;

		button_parent = NULL;
		this->id =  id;
	}

	void setParent(mkInterface *p)
	{
		button_parent = p;
	}

	mkInterface *getParent()
	{
		return button_parent;
	}

	void setPos(vec2 pos)
	{
		this->pos = pos;
		this->display_pos = pos;
	}
	void setDisplayPos(vec2 pos)
	{
		display_pos = pos;
	}

	void setId(int id)
	{
		this->id = id;
	}
	int getId()
	{
		return id;

	}
	vec2 getPos()
	{
		return this->pos;
	}
	vec2 getDisplayPos()
	{
		return display_pos;
	}
	void HandleEvents(SDL_Event event)
	{
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			mouse.x = (float)event.motion.x;
			mouse.y = (float)event.motion.y;

			break;
		case SDL_MOUSEBUTTONDOWN:
			is_clicked = true;
			call_on_click = true;
			break;
		case SDL_MOUSEBUTTONUP:
			is_clicked = false;
			break;
		default:
			break;
		}
	}

	void ApplyEvents()
	{
		vec2 p = display_pos;
		SDL_Rect rect = {p.x,p.y,button[0]->getWidth(),button[0]->getHeight()};
		
		if(mk::detectMouse(rect,mouse.x,mouse.y))
		{
			is_over = true;

			if(call_on_over && onOvers.size() != 0)
			{
				for(int i=0; i<onOvers.size(); i++)
				{
					onOvers[i]();
				}
				call_on_over = false;
			}

		}
		else
		{
			is_over = false;
			call_on_over = true;
		}
	}

	void Display()
	{
		ApplyEvents();
		if(is_over) // clicked on button
		{
			if(is_clicked)
			{
				button[1]->draw(display_pos+vec2(0,2)); // emulate click
				if(call_on_click && onClicks.size() != 0)
				{
					for(int i=0; i<onClicks.size(); i++)
					{
						onClicks[i](button_parent,this->id);
					}
					call_on_click = false;
				}
			}
			else
			{
				button[1]->draw(display_pos); // display over
			}
		}
		else
		{
			button[0]->draw(display_pos); // display normal
		}

		
	}

};

#endif
/*
Name: Muhammad Kashif
Date: 07 May, 2013
File: mkScene
*/


#ifndef MK_SCENE_H
#define MK_SCENE_H
#pragma once

#include "mk.h"
#include "mkFreeType.h"
#include "mkInterface.h"
#include "mkButton.h"
#include "mkImage.h"

class mkScene : public mkInterface
{
protected:
	mkImage *background;
	vector <mkFreeType*> free_types;
	vector <mkButton*> buttons; 
	vec2 scene_pos,pos_to,scene_pos_backup;
	bool is_hide;

	// animation stuff
	float spd,acc;
	float anim_index;
	bool is_complete_anim;

	bool is_logo_display;
	vec2 logo_pos;


	vector <string> scene_text;
	mkText *text;


public:
	mkScene()
	{
		is_hide = false;
		acc = 0.001;
		is_complete_anim = true;
		anim_index = 0;
		spd = 0;

		is_logo_display = false;
		logo_pos = vec2(460,280);

		text = new mkText("res//fonts//pan.ttf",32);
		text->SetColor(80,64,64);
	
	}
	void AddText(string txt)
	{
		scene_text.push_back(txt);
	}
	void ClearText()
	{
		scene_text.clear();
	}
	mkScene *LogoDisplay(bool is_dis)
	{
		is_logo_display =  is_dis;	
		return this;
	}

	mkScene *setLogoPosition(vec2 at_pos)
	{
		logo_pos = at_pos;
		return this;
	}

	


	bool IsLogoDisplay()
	{
		return is_logo_display;
	}

	void SetAnimComplete(bool comp)
	{
		is_complete_anim = comp;
	}

	bool IsAnimComplete()
	{
		return is_complete_anim;
	}

	mkScene *SetPosition(vec2 pos)
	{
		scene_pos_backup = scene_pos = pos;
		return this;
	
	}

	vector<mkFreeType*> getFreeType()
	{
		return free_types;
	}

	vector<mkButton*> getButons()
	{
		return buttons;
	}

	mkScene *MoveIn()
	{	
		pos_to = vec2(0,0);
		is_complete_anim = false;
		return this;
	}
	
	mkScene *MoveUpOut()
	{
		pos_to = vec2(0,-1000);
		is_complete_anim = false;
		return this;
	}
	

	mkScene *MoveDownOut()
	{
		pos_to = vec2(0,1000);
		is_complete_anim = false;
		return this;
	}

	mkScene *MoveLeftOut()
	{
		pos_to = vec2(-1000,0);
		is_complete_anim = false;
		return this;
	}
	
	mkScene *MoveRightOut()
	{
		pos_to = vec2(1000,0);
		is_complete_anim = false;
		return this;
	}

	

	mkScene *SetBackgroundImage(string bg_file)
	{
		background = new mkImage(bg_file);
		return this;
	}

	mkScene *AddButtons(mkButton *button)
	{
		button->setParent(this);
		buttons.push_back(button);

		return this;
	}
	mkScene *AddFreeType(mkFreeType *f_type)
	{
		free_types.push_back(f_type);
		return this;
	}

	void HandleEvents(SDL_Event events)
	{
		for(int i=0; i<buttons.size(); i++)
		{
			buttons[i]->HandleEvents(events);
		}

		for(int i=0; i<free_types.size(); i++)
		{
			free_types[i]->HandleEvents(events);
		}
	}

	void Display()
	{
		if(!is_hide)
		{
			if(!is_complete_anim)
			{
				// P = (1-i)*P1 + i*P2
				scene_pos = (1-anim_index)*scene_pos_backup  + anim_index*pos_to;
				anim_index += spd;
				spd += acc;

				if(anim_index>1)
				{
					anim_index = 0;
					is_complete_anim = true;
					scene_pos = pos_to;
					scene_pos_backup = pos_to;
					spd=0;
				}
			}

			if(background!=NULL)
				background->draw(scene_pos + vec2(background->getWidth()/2,background->getHeight()/2));

			for(int i=0; i<free_types.size(); i++)
			{
				free_types[i]->setDisplayPos(free_types[i]->getPos()+scene_pos);
				free_types[i]->Draw();
			}
			for(int i=0; i<buttons.size(); i++)
			{
			
				buttons[i]->setDisplayPos(buttons[i]->getPos()+scene_pos);
				buttons[i]->Display();
			}

			if(is_logo_display)
			{
				////mkLogo::getInstance( logo_pos + scene_pos )->Draw();
			}

			if(scene_text.size()>0)
			{
				for(int i=0; i<scene_text.size(); i++)
				{
					text->SetPos(vec2(scene_pos.x+500,i*50 + 250));
					text->SetText(scene_text[i]);
					text->Draw();
				}
			}
		}

	}

	void Hide()
	{
		is_hide = true;
	}
	void Show()
	{
		is_hide = false;
	}
	bool IsHide()
	{
		return is_hide;
	}
};


#endif
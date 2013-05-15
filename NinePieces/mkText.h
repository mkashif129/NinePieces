/*
Name: Muhammad Kashif
Date: 06 May, 2013
File: mkText
*/


#ifndef MK_TEXT_H
#define MK_TEXT_H
#pragma once

#include "mk.h"


class mkText
{
private:
	SDL_Surface *text_surface;
	int width,height;
	vec2 pos;
	SDL_Color color;
	TTF_Font *font;
	string text;

	vec2 scenepos;
public:
	mkText(string font_file, int size)
	{
		TTF_Init();
		
		font = TTF_OpenFont( font_file.c_str(), size);
		if(font == NULL){
			cout <<"Font not found";
			exit(0);
		}

		SetText("");
		SetColor(200,200,200);
		SetPos(vec2(100,100));
		scenepos = vec2(0,0);
	}
	void SetScenePos(vec2 sp)
	{
		scenepos = sp;
	}
	void SetPos(vec2 p)
	{
		pos = p;
	}
	vec2 GetPos()
	{
		return pos;
	}
	int getWidth()
	{
		return width;
	}
	int getHeight()
	{
		return height;
	}
	void SetText(string txt)
	{
		text = txt;
		if(text.size() !=0)
		{
			text_surface = TTF_RenderText_Blended(font,text.c_str(),color);
		}
		else
			text_surface = NULL;
		UpdateSize();
	}

	void UpdateSize()
	{
		if(text_surface != NULL)
		{
			width = text_surface->w;
			height = text_surface->h;
		}
	}

	void SetColor(int r, int g, int b)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		text_surface = TTF_RenderText_Blended(font,text.c_str(),color);
		UpdateSize();
	
	}

	void Draw()
	{
		if(text_surface!=NULL)
		{
			SDL_Rect rect = {0,0,width,height};
			SDL_Rect distRect = {pos.x - width/2 + scenepos.x ,  pos.y - height/2 + scenepos.y,0,0};
			mk::BlitOnGL(text_surface,&rect,mk::screen,&distRect);
		}
	}

	void Draw(vec2 pos)
	{

		if(text_surface!=NULL)
		{
			SDL_Rect rect = {0,0,width,height};
			SDL_Rect distRect = {pos.x - width/2 + scenepos.x,pos.y + scenepos.y - height/2,0,0};
			mk::BlitOnGL(text_surface,&rect,mk::screen,&distRect);
		}
	}

};

#endif
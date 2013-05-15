/*
Name: Muhammad Kashif
Date: 16 January, 2013
File: mkWindow.h (main window class)
Desc: it creates sdl window

Status: completed
Reviewd: 19 Jan, 2013
: 09 Apr, 2013

Pointer Error Not found
*/


#ifndef MK_WINDOW_H
#define MK_WINDOW_H
#pragma once

#include "mk.h"

// base class
class mkWindow : public mk
{
protected:
	bool running;
	long int start;

	SDL_Event event;

public:
	mkWindow()
	{
		SetSize(640,480);
	}

	mkWindow(int width, int height)
	{
		SetSize(width,height);
		Init();
	}

	void Init()
	{

		SDL_Init(SDL_INIT_EVERYTHING);
		screen = SDL_SetVideoMode(WIDTH,HEIGHT,32,SDL_SWSURFACE);
		start = 0;
		running = true;
	}
	void SetSize(int w, int h)
	{
		WIDTH = w;
		HEIGHT = h;
	}


	void StartTimer()
	{
		start = SDL_GetTicks();
	}
	void ClearScreen()
	{
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = WIDTH;
		rect.h =HEIGHT;

		SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,0,0,0));
	}
	void UpdateScreen()
	{
		SDL_UpdateRect(screen, 0,0, 1, 1);
			if(1000/400>(SDL_GetTicks()-start))SDL_Delay(1000/400-(SDL_GetTicks()-start));
	}
	void StopRunning()
	{
		running = false;
	}
	bool Run()
	{
		return running;
	}
	void Quit()
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		}
	}

	SDL_Surface *getScreen()
	{
		return screen;
	}
	int getPollEvent()
	{
		return SDL_PollEvent(&event);
	}
	SDL_Event getEvent()
	{
		return event;
	}

	void Clean()
	{
		SDL_FreeSurface(screen);
		SDL_Quit();
	}
};





#endif


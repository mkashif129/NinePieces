/*
Name: Muhammad Kashif
Proj: IceTanks
Date: 08 March, 2011
File: Timer.h

Copyright (c) mkashif - Rahbar, 2011
*/


#ifndef MK_TIMER_H
#define MK_TIMER_H
#pragma once

#include "External\SDL\SDL.h"

//The timer
class mkTimer
{   
private:
	//The clock time when the timer started
	int startTicks;

	//The ticks stored when the timer was paused
	int pausedTicks;

	//The timer status
	bool paused;
	bool started;


	long int t_start;
	long int t_end;
	long int milliseconds;

public:
	mkTimer()
	{
		//Initialize the variables
		startTicks = 0;
		pausedTicks = 0;
		paused = false;
		started = true;
	}


	mkTimer(double second)
	{ 
		//Initialize the variables
		startTicks = 0;
		pausedTicks = 0;
		paused = false;
		started = true;

		milliseconds = 1000*second;

		//setTime(second);
	}


	void setTime(double seconds)
	{
		milliseconds = seconds*1000;
		start();
	}


	double getTime()
	{
		return milliseconds/1000;
	}

	bool getPulse()
	{
		t_end = get_ticks(); 

		if (t_end - t_start > milliseconds)
		{
			t_start = t_end;
			return true;   
		}
		else
			return false;
	}

	double getTimeElapsed()
	{
		return double(SDL_GetTicks() - t_start)/double(1000);
	}

	// my function
	void applyFrameRate(int frames_per_second)
	{
		//If we want to cap the frame rate
		if(get_ticks() < 1000 / frames_per_second ) 
		{
			//Sleep the remaining frame time
			SDL_Delay( ( 1000 / frames_per_second ) - get_ticks() );
		}

	}// end applyFrameRate


	void start()
	{
		//Start the timer
		started = true;

		//Unpause the timer
		paused = false;

		//Get the current clock time
		t_start = startTicks = SDL_GetTicks();

	}

	void stop()
	{
		//Stop the timer
		started = false;

		//Unpause the timer
		paused = false;
	}

	void pause()
	{
		//If the timer is running and isn't already paused
		if( ( started == true ) && ( paused == false ) )
		{
			//Pause the timer
			paused = true;

			//Calculate the paused ticks
			pausedTicks = SDL_GetTicks() - startTicks;
		}
	}

	void unpause()
	{
		//If the timer is paused
		if( paused == true )
		{
			//Unpause the timer
			paused = false;

			//Reset the starting ticks
			startTicks = SDL_GetTicks() - pausedTicks;

			//Reset the paused ticks
			pausedTicks = 0;
		}
	}

	int get_ticks()
	{
		//If the timer is running
		if( started == true )
		{
			//If the timer is paused
			if( paused == true )
			{
				//Return the number of ticks when the timer was paused
				return pausedTicks;
			}
			else
			{
				//Return the current time minus the start time
				return SDL_GetTicks() - startTicks;
			}
		}

		//If the timer isn't running
		return 0;
	}

	bool is_started()
	{
		return started;
	}

	bool is_paused()
	{
		return paused;
	}
};
// end class Timer
#endif 
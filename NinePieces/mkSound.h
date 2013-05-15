/*
Name: Muhammad Kashif
Date: 14 May, 2013
File: mkSound.h
*/



#ifndef MK_SOUND_H
#define MK_SOUND_H
#pragma once

#include "mk.h"


class mkSound
{
private:	
	ISoundEngine *sound_engine;
	vector <ISoundSource*> sounds;
public:
	mkSound()
	{
		 sound_engine = irrklang::createIrrKlangDevice();
	}


	void AddSound(string soundfile)
	{
		sounds.push_back(sound_engine->addSoundSourceFromFile(soundfile.c_str()));
	}

	void Play(int index)
	{
		if(index>=0 && index<sounds.size())
			sound_engine->play2D(sounds[index]);
	}
	void Stop()
	{
		sound_engine->stopAllSounds();
	}
	void SetVolume(float vol)
	{
		sound_engine->setSoundVolume(vol);
	}

};

#endif
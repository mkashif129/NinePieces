/*
Name: Muhammad Kashif
Date: 16 January, 2013
File: mkImage.h ( side class)
Desc: image loader

Status:  completed
Reviewd: 19 Jan, 2013,
	   : 22 Jan, 2013.
	   : 09 Apr, 2013

Pointer Error Removed
*/



#ifndef MK_IMAGE_H
#define MK_IMAGE_H
#pragma once

#include "mk.h"

class mkImage
{
private:
	SDL_Surface *imageSurface;
	mkArray <Uint8> *image8;
	int width,height;

public:
	mkImage()
	{
		imageSurface =  NULL;
	}

	mkImage(string filename)
	{
		imageSurface = IMG_Load(filename.c_str());
		// error detection
		if(imageSurface==NULL){
			
			cout <<"Error: Image ("<<filename.c_str()<<") is not found..!!\n";
		}
		else {
			cout <<"Image ("<<filename.c_str()<<")  ("<<imageSurface->w<<"x"<<imageSurface->h<<") is loaded Succesfully\n";
			
		
			this->width = imageSurface->w;
			this->height = imageSurface->h;

			// now copying to image Uint8 array
			Uint8 *ptr =  (Uint8*)imageSurface->pixels;
			int numberOfPixels = this->width * this->height; 
			image8 = new mkArray<Uint8>(ptr,numberOfPixels*imageSurface->format->BytesPerPixel);
		}
	}

	~mkImage()
	{
		cout <<"Image is deleted, Out of Scope..!\n";
		image8->Delete();
	}

	mkImage(SDL_Surface *img)
	{
		imageSurface = img;

		this->width = imageSurface->w;
		this->height = imageSurface->h;

		// now copying to image Uint8 array
		Uint8 *ptr =  (Uint8*)imageSurface->pixels;
		int numberOfPixels = this->width * this->height; 
		image8 = new mkArray<Uint8>(ptr,numberOfPixels*imageSurface->format->BytesPerPixel);
	}

	SDL_Surface *getImageSurface()
	{
		return imageSurface;
	}
	int getBitsPerPixel()
	{
		return (int)imageSurface->format->BitsPerPixel;
	}

	Uint8 *operator[] (int index)
	{
		return (*image8)[index];
	}

	int getWidth()
	{
		return width;
	}
	int getHeight()
	{
		return height;
	}

	Uint32 getNumberOfPixels()
	{
		return (Uint32)width*height;
	}


public: // drawing functions SDL
	void draw(SDL_Surface *dist,vec2 pos)
	{
		SDL_Rect rect = {pos.x,pos.y,width,height};
		SDL_Rect distRect = {0,0,0,0};
		mk::BlitOnGL(this->getImageSurface(),&rect,dist,&distRect);
	}
	void draw(vec2 pos)
	{
		SDL_Rect rect = {0,0,width,height};
		SDL_Rect distRect = {pos.x - width/2,pos.y - height/2,0,0};
		mk::BlitOnGL(this->getImageSurface(),&rect,mk::screen,&distRect);
	}

	void draw()
	{
		SDL_Rect rect = {0,0,width,height};
		SDL_Rect distRect = {0,0,0,0};
		mk::BlitOnGL(this->getImageSurface(),&rect,mk::screen,&distRect);
	}
};

#endif
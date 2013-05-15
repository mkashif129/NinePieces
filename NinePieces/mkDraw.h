/*
Name: Muhammad Kashif
Date: 30 April, 2013
File: mkDraw.h

Disc: Singleton class

*/


#ifndef MK_DRAW_H
#define MK_DRAW_H
#pragma once

#include "mk.h"

class mkDraw : public mk
{
private:
	mkColor color;
	static mkDraw *instance;

public: 
	mkDraw()
	{
		color = mkColor(255,255,255);
		instance = NULL;
	}
	void SetColor(mkColor color)
	{
		this->color = color;
	}

public: //drwaing functions
	void PutPixel(int x, int y)
	{
		if(x<0 || x>=WIDTH || y<0 || y>=HEIGHT)
		{
			//cout <<"Pixel: X,Y Value Out of Range..!\n\n";
			//exit(0);
		}
		else
		{

			vec3 finalColor = color.getColor3();

			if(finalColor.x>1)
				finalColor.x = 1;
			if(finalColor.y>1)
				finalColor.y = 1;
			if(finalColor.z>1)
				finalColor.z = 1;

			Uint32 pixel = mkColor(finalColor).getUint32(screen);

			int bpp = screen->format->BytesPerPixel;
			/* Here p is the address to the pixel we want to set */
			Uint8 *p = (Uint8 *)screen->pixels +(int)y * screen->pitch +(int)x * bpp;

			switch(bpp) {
			case 1:
				*p = pixel;
				break;

			case 2:
				*(Uint16 *)p = pixel;
				break;

			case 3:
				if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
					p[0] = (pixel >> 16) & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = pixel & 0xff;
				} else {
					p[0] = pixel & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = (pixel >> 16) & 0xff;
				}
				break;

			case 4:
				*(Uint32 *)p = pixel;
				break;
			}
		}
	}
	void Point(float x, float y)
	{
		x = x/2 + 0.5;
		y = -y/2 + 0.5;

		PutPixel(x*(HEIGHT-1)+(WIDTH-HEIGHT)/2,y*(HEIGHT-1));
	}
	void Line(vec2 p1, vec2 p2, vec3 col1, vec3 col2)
	{

		////setting coordinates
		//p1.x = p1.x/2 + 0.5;
		//p1.y = -p1.y/2 + 0.5;
		//p2.x = p2.x/2 + 0.5;
		//p2.y = -p2.y/2 + 0.5;


		//// maping on screen
		//p1.x = p1.x*(HEIGHT-1)+(WIDTH-HEIGHT)/2;
		//p1.y = p1.y*(HEIGHT-1);
		//p2.x = p2.x*(HEIGHT-1)+(WIDTH-HEIGHT)/2;
		//p2.y = p2.y*(HEIGHT-1);

		float mag = sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2));
		mag = 1/mag;

		for(float t=0; t<=1; t+=mag)
		{
			vec3 color = col1*(1-t) + col2*(t);
			SetColor(color);
			vec2 p = p1*(1-t) + p2*(t);
			PutPixel(p.x,p.y);
		}
	}
	void Triangle(vec2 p1,vec2 p2 , vec2 p3, vec3 col1, vec3 col2, vec3 col3)
	{

		for(float t=0; t<=1; t+=0.001)
		{
			vec2 l = p1*(1-t) + p2*t;
			vec2 r = p1*(1-t) + p3*t;

			vec3 colL = col1*(1-t) + col2*t;
			vec3 colR = col1*(1-t) + col3*t;

			Line(l,r,colL,colR);
		}

	}

	static mkDraw *getInstance()
	{
		if(instance == NULL)
		{
			 instance =  new mkDraw();;
			 return instance;
		}
		else
			return instance;
	}
};

mkDraw *mkDraw::instance = NULL;




#endif
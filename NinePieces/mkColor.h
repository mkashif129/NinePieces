/*
Name: Muhammad Kashif
Date: 8 January, 2013
File: mkColor.h (color structs)


Status: completed
Reviewd: 19 Jan, 2013
	   : 09 Apr, 2013

Pointer Error Removed
*/

#ifndef MK_COLOR_H
#define MK_COLOR_H
#pragma once

#include "External\GL\glew.h"
#include "External\GL\glut.h"

#include "External\glm\glm.hpp"
#include "External\glm\gtc\matrix_transform.hpp"


using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using glm::dot;
using glm::max;
using glm::perspective;
using glm::lookAt;
using glm::translate;
using glm::rotate;
using glm::scale;

// 32 bits || 4 bytes per pixel
struct mkColor
{
	Uint8 r,g,b,a;

	mkColor()
	{
		r=g=b=a=255;
	}

	mkColor(Uint32 color32)
	{
		Uint8 *ptr = (Uint8*)color32;
		this->r = *ptr++;
		this->g = *ptr++;
		this->b = *ptr++;
		this->a = *ptr;
	}

	mkColor(Uint8 r,Uint8 g=255,Uint8 b=255,Uint8 a=255)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	mkColor(vec4 col)
	{
		this->r = (Uint8)col.r*255;
		this->g = (Uint8)col.g*255;
		this->b = (Uint8)col.b*255;
		this->a = (Uint8)col.a*255;
	}
	mkColor(vec3 col)
	{
		this->r = (Uint8)col.r*255;
		this->g = (Uint8)col.g*255;
		this->b = (Uint8)col.b*255;
		this->a = (Uint8)255;
	}


	vec3 getColor3()
	{
		return vec3(this->r/255,this->g/255,this->b/255);
	}
	vec4 getColor4()
	{
		return vec4(this->r/255,this->g/255,this->b/255,this->a/255);
	}

	Uint32 getUint32(SDL_Surface* screen)
	{
		return SDL_MapRGB(screen->format,r,g,b);
	}
};

// 32 bits || 4 bytes per pixel
struct mkColor32
{
	Uint8 r,g,b,a;

	mkColor32()
	{
		r=g=b=a=255;
	}

	mkColor32(Uint32 color32)
	{
		Uint8 *ptr = (Uint8*)color32;
		this->r = *ptr; ptr++;
		this->g = *ptr; ptr++;
		this->b = *ptr; ptr++;
		this->a = *ptr;
	}

	mkColor32(Uint8 r,Uint8 g=255,Uint8 b=255,Uint8 a=255)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	mkColor32(vec4 col)
	{
		this->r = (Uint8)col.r*255;
		this->g = (Uint8)col.g*255;
		this->b = (Uint8)col.b*255;
		this->a = (Uint8)col.a*255;
	}
	mkColor32(vec3 col)
	{
		this->r = (Uint8)col.r*255;
		this->g = (Uint8)col.g*255;
		this->b = (Uint8)col.b*255;
		this->a = (Uint8)255;
	}


	vec3 getColor3()
	{
		return vec3(this->r/255,this->g/255,this->b/255);
	}
	vec4 getColor4()
	{
		return vec4(this->r/255,this->g/255,this->b/255,this->a/255);
	}

};

// 24 bits || 3 bytes per pixel
struct mkColor24
{
	Uint8 r,g,b;

	mkColor24()
	{
		r=g=b=255;
	}

	mkColor24(Uint32 color32)
	{
		Uint8 *ptr = (Uint8*)color32;
		this->r = *ptr++;
		this->g = *ptr++;
		this->b = *ptr++;
	}

	mkColor24(Uint8 r,Uint8 g=255,Uint8 b=255)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	mkColor24(vec4 col)
	{
		this->r = (Uint8)col.r*255;
		this->g = (Uint8)col.g*255;
		this->b = (Uint8)col.b*255;
	}
	mkColor24(vec3 col)
	{
		this->r = (Uint8)col.r*255;
		this->g = (Uint8)col.g*255;
		this->b = (Uint8)col.b*255;
	}


	vec3 getColor3()
	{
		return vec3(this->r/255,this->g/255,this->b/255);
	}
	vec4 getColor4()
	{
		return vec4(this->r/255,this->g/255,this->b/255,1);
	}

};

#endif
/*
Name: Muhammad Kashif
Date: 8 January, 2013
File: mk.h (super base class)


Status: completed
Reviewd: 19 Jan, 2013
	   : 09 Apr, 2013

Pointer Error Removed
*/

#ifndef MK_H
#define MK_H
#pragma once

// headers
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
#include <math.h>
#include <algorithm>    // std::unique, std::distance
// sdl 

#include "External\SDL\SDL.h"
#include "External\irrKlang\irrKlang.h"
#include  "External\SDL\SDL_image.h"
#include "External\SDL\SDL_ttf.h"
// glew
#include "External\GL\glew.h"
#include "External\GL\glut.h"
// glm
#include "External\glm\glm.hpp"
#include "External\glm\gtc\matrix_transform.hpp"

// my own
#include "mkArray.h"
#include "mkColor.h"

// c++ 11
#include <thread>
#include <mutex>
#include <functional>
#include <array>

// adding library
#pragma comment (lib,"SDL.lib")
#pragma comment (lib,"SDLmain.lib")
#pragma comment (lib,"SDL_image.lib")
#pragma comment (lib,"SDL_ttf.lib")
#pragma comment (lib,"glew32.lib")
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"irrklang.lib")


using namespace std;
using namespace irrklang;
using glm::vec2;
using glm::ivec2;
using glm::vec3;
using glm::ivec3;
using glm::vec4;
using glm::ivec4;
using glm::mat3;
using glm::mat4;
using glm::dot;
using glm::max;
using glm::perspective;
using glm::lookAt;
using glm::translate;
using glm::rotate;
using glm::scale;


struct mkPath
{
	int paths[4];
	mkPath()
	{
		for(int i=0; i<4; i++)
			paths[i] = -1;
	}

	mkPath(int a,int b,int c, int d)
	{
		paths[0] = a; paths[1] = b;
		paths[2] = c; paths[3] = d;
	}

	mkPath(int path[4])
	{
		for(int i=0; i<4; i++)
		{
			paths[i] =  path[i];
		}
	}

	void Show()
	{
		for(int i=0; i<4; i++)
			cout <<paths[i]<<" ";
		cout <<"\n";
	}
};

struct mkGrid
{
	vec2 point;
	bool is_on;
	mkGrid()
	{
		is_on = true;
	}
	mkGrid(vec2 v)
	{
		point = v;
	}
};

struct mkConsegitivePieces
{
	int row1[3];
	int row2[3];
	
	mkConsegitivePieces(){
	
		row1[0] = -1; row1[1] = -1; row1[2] = -1;
		row2[0] = -1; row2[1] = -1; row1[2] = -1;
	}

	mkConsegitivePieces(int a, int b, int c, int d, int e, int f)
	{
		row1[0] = a; row1[1] = b; row1[2] = c;
		row2[0] = d; row2[1] = e; row2[2] = f;
	}
	mkConsegitivePieces(int r1[3],int r2[3])
	{
		row1[0] = r1[0]; row1[1] = r1[1]; row1[2] = r1[2];
		row2[0] = r2[0]; row2[1] = r2[1]; row2[2] = r2[2];
	}
	void SetRow1(int r1[3])
	{
		row1[0] = r1[0]; row1[1] = r1[1]; row1[2] = r1[2];
	}

	void SetRow2(int r2[2])
	{
		row2[0] = r2[0]; row2[1] = r2[1]; row2[2] = r2[2];
	}

	mkGrid getRow1Pos1(vector<mkGrid> grid)
	{
		return grid[row1[0]];
	}
	mkGrid getRow1Pos2(vector<mkGrid> grid)
	{
		return grid[row1[1]];
	}
	mkGrid getRow1Pos3(vector<mkGrid> grid)
	{
		return grid[row1[2]];
	}


	mkGrid getRow2Pos1(vector<mkGrid> grid)
	{
		return grid[row2[0]];
	}
	mkGrid getRow2Pos2(vector<mkGrid> grid)
	{
		return grid[row2[1]];
	}
	mkGrid getRow2Pos3(vector<mkGrid> grid)
	{
		return grid[row2[2]];
	}
};


struct mkCompleteRow
{
	int row[3];

	mkCompleteRow()
	{
		row[0] = -1; row[1] = -1; row[2] = -1;
	}

	mkCompleteRow(int a, int b, int c)
	{
		row[0] = a; row[1] = b; row[2] = c;
		Sort();
	}

	mkCompleteRow(int r[3])
	{
		row[0] = r[0]; row[1] = r[1]; row[2] = r[2];
		Sort();
	}


	void Sort()
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<2; j++)
			{
				if(row[j] > row[j+1])
				{
					swap(row[j],row[j+1]);
				}
			}
		}
	}

	bool IsMatched(mkCompleteRow cr)
	{
		if(	cr.row[0] == this->row[0] &&
			cr.row[1] == this->row[1] &&
			cr.row[2] == this->row[2]  )
		{
			return true;
		}
		else 
			return false;

	}

	vector<vec2> getPositions(vector<mkGrid> grid)
	{
		vector <vec2> pos;
		
		pos.push_back(grid[row[0]].point);
		pos.push_back(grid[row[1]].point);
		pos.push_back(grid[row[2]].point);
		return pos;
	}

	bool operator<( const mkCompleteRow& val ) const { 
		int x = row[0] + row[1] + row[2];
		int y = val.row[0] + val.row[1] + val.row[2];
		return x < y; 
    }
	bool operator==(const mkCompleteRow& cr)const
	{
		if(	cr.row[0] == this->row[0] &&
			cr.row[1] == this->row[1] &&
			cr.row[2] == this->row[2]  )
		{
			return true;
		}
		else 
			return false;
	}
};


class mkCheckTime
{
private:
	clock_t begin, end;

public:
	mkCheckTime()
	{
		begin = end =  0;
	}

	void Start()
	{
		begin = clock();
	}

	double getSeconds()
	{
		end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		return time_spent;
	}

	long int getMilliSeconds()
	{
		end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		return (long int)(time_spent*1000);
	}
		
};



class mk
{
public: // static constant variables
static const double PI;
static const double Half_PI;
static const double Two_PI;
static mkCheckTime CheckTime;

public: // nostatic variables
	static SDL_Surface *screen;
	static unsigned int WIDTH,HEIGHT;


	//bool running;
	//long int start;

protected:
	mk(){}





public: // some static functions


	static Uint32 MapRGB(mkColor color, SDL_Surface *screen)
	{

		return  SDL_MapRGBA(screen->format, color.r,color.g,color.b,color.a);
	}
	static Uint32 GetPixel(SDL_Surface *surface, int x, int y)
	{
		int bpp = surface->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to retrieve */
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

		switch(bpp) {
		case 1:
			return *p;
			break;

		case 2:
			return *(Uint16 *)p;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			break;

		case 4:
			return *(Uint32 *)p;
			break;

		default:
			return 0;       /* shouldn't happen, but avoids warnings */
		}
	}
	static vec3 GetPixelColor(SDL_Surface *img, int x, int y)
	{
		Uint32 col = GetPixel(img,x,y);
		Uint8 r,g,b;
		SDL_GetRGB(col,img->format,&r,&g,&b);
		return vec3((float)r/255,(float)g/255,(float)b/255);
	}
	static vec4 Uint32ToRGBA(Uint32 color32)
	{
		Uint8 *ptr = (Uint8*)color32;
		Uint8 r = *ptr++;
		Uint8 g = *ptr++;
		Uint8 b = *ptr++;
		Uint8 a = *ptr;

		return vec4((float)r/255,(float)g/255,(float)b/255,(float)a/255);
	}


	static void SetUniform4x4(string name, float *att,GLuint programHandle)
	{
		GLuint loc = glGetUniformLocation(programHandle,name.c_str());
		glUniformMatrix4fv(loc,1,GL_FALSE,att);	
	}
	static void SetUniform1(string name,float f,GLuint programHandle)
	{
		GLuint loc = glGetUniformLocation(programHandle,name.c_str());
		glUniform1f(loc,f);
	}
	static void SetUniform2(string name,vec2 v,GLuint programHandle)
	{
		GLuint loc = glGetUniformLocation(programHandle,name.c_str());
		glUniform2f(loc,v.x,v.y);
	}
	static void SetUniform3(string name,vec3 v,GLuint programHandle)
	{
		GLuint loc = glGetUniformLocation(programHandle,name.c_str());
		glUniform3f(loc,v.x,v.y,v.z);
	}
	static void SetUniform4(string name,vec4 v,GLuint programHandle)
	{
		GLuint loc = glGetUniformLocation(programHandle,name.c_str());
		glUniform4f(loc,v.x,v.y,v.z,v.w);
	}

	static void SetUnformTexture(string name,int textureNumber,GLuint programHandle)
	{
		int loc =  glGetUniformLocation(programHandle,name.c_str());
		glUniform1i(loc, textureNumber);

	}


	//----------------------------
	// detectMouse
	//----------------------------
	static bool detectMouse(SDL_Rect rect, int mx, int my)
	{
		rect.x -= rect.w/2;
		rect.y -= rect.h/2;

		rect.w = rect.x + rect.w ;
		rect.h = rect.y + rect.h;



		if (mx > rect.x && mx <rect.w && my > rect.y && my <rect.h)
			return true;
		else
			return false;

	}// end detectMouse

	//----------------------------
	// detectMouse
	//----------------------------
	static bool detectMouse(SDL_Rect rect, vec2 m)
	{
		rect.x -= rect.w/2;
		rect.y -= rect.h/2;

		rect.w = rect.x + rect.w ;
		rect.h = rect.y + rect.h;



		if (m.x > rect.x && m.x <rect.w && m.y > rect.y && m.y <rect.h)
			return true;
		else
			return false;

	}// end detectMouse


	static void BlitOnGL(SDL_Surface *img, SDL_Rect *rect, SDL_Surface *scren,SDL_Rect *dstrect)
	{
		SDL_BlitSurface(img,rect,scren,dstrect);
	}

	static int FindElement(vector <mkGrid> vec, mkGrid el)
	{
		for(int i=0; i<vec.size(); i++)
		{
			if(vec[i].point == el.point)
			{
				return i;
			}
		}

		return -1;
	}

	static int FindElement(vector <mkGrid> vec, vec2 el)
	{
		for(int i=0; i<vec.size(); i++)
		{
			if(vec[i].point == el)
			{
				return i;
			}
		}

		return -1;
	}

};


// initializing static variable
const double mk::PI = 3.14159265359;
const double mk::Half_PI = mk::PI/2;
const double mk::Two_PI = mk::PI*2;
mkCheckTime mk::CheckTime;

// alocating memory
unsigned int mk::WIDTH = 640;
unsigned int mk::HEIGHT = 640;

SDL_Surface * mk::screen = NULL;




#endif
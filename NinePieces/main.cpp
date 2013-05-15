/*
Name: Muhammad kashif
File: main.cpp
Date: 5 May, 2013

Proj: NinePiece - Game
*/

#include "mkWindow.h"
#include "mkDraw.h"
#include "mkImage.h"
#include "mkPiece.h"
#include "mkTimer.h"
#include "mkGame.h"
#include "mkText.h"
#include "mkFreeType.h"
#include "mkButton.h"
#include "mkLogo.h"
#include "mkScene.h"
#include "mkNinePieces.h"


// 0: start
// 1: intro
// 2: menu
// 3: single
// 4: multi
// 5: saved
// 6: about
// 7: Game


// main 
int main(int argc, char **argv) 
{
	mkWindow window(1000,650);
	window.Init();

	
	mkNinePieces *game = new mkNinePieces(&window);
	


	
	int mx=0,my=0;


	while(window.Run()){
		window.StartTimer();
		while(window.getPollEvent()){
			window.Quit();

			game->HandleEvents(window.getEvent());
			switch (window.getEvent().type)
			{
			case SDL_MOUSEBUTTONUP:

				mx = window.getEvent().button.x;
				my = window.getEvent().button.y;
				/*system("cls");
				cout <<mx<<" "<<my;*/
				break;

			case SDL_KEYDOWN:
				
				break;

			case SDL_KEYUP:
				break;
			default:
				break;
			}
		}

		window.ClearScreen();

		
		game->DisplayGame();

		

		window.UpdateScreen();

	}// end main LOOP


	
	SDL_Quit();
	game->getGame()->JoinThreads();


	
	return 0;
}
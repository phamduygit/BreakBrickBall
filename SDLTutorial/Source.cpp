#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Functions.h"
#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {
	// Kiểm tra xem SDL có hoạt động hay chưa và đưa ra lỗi 
	const int FPS = 120;
	const int DELAY_TIME = 1000 / FPS;
	Uint32 frameStart;
	Uint32 frameTime;
	Game* game = Game::Instance();
	game->Init("Break Brick Ball", 500, 800);
	while (game->getRunning()) {
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->render();
		game->update();
		//game->render();
		/*time = (clock() - time)/CLOCKS_PER_SEC;*/
	//	frameTime = SDL_GetTicks() - frameStart;
		/*if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}*/
		SDL_Delay(10);
		
	}
	
	return 0;
}
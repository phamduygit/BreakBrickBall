#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Functions.h"
#include "Game.h"
using namespace std;

int main(int argc, char* argv[]) {
	// Kiểm tra xem SDL có hoạt động hay chưa và đưa ra lỗi 
	
	Game* game = Game::Instance();
	game->Init("Break Brick Ball", 500, 800);
	while (game->getRunning()) {
		game->handleEvents();
		game->update();
		game->render();
		SDL_Delay(3);
	}
	
	return 0;
}
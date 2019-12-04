#pragma once
#include "GameOver.h"
#include <SDL.h>
#include "Functions.h"
class EndScreen:public GameOver
{
private:
public:
	EndScreen(){}
	EndScreen(SDL_Renderer *& renderer):GameOver(renderer){}
	void draw() {
		auto tempImage = image;
		image = LoadImage("EndScreen.png", renderer);
		SDL_RenderCopy(renderer, image, NULL, NULL);
		SDL_DestroyTexture(image);
		SDL_DestroyTexture(tempImage);
	}

};

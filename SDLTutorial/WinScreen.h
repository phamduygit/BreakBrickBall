#pragma once
#include "GameOver.h"
#include "Player.h"

class WinScreen:public GameOver
{
private:
	SDL_Texture* nextButton;
	SDL_Texture* retryButton;


public:
	WinScreen():GameOver(){}
	WinScreen(SDL_Renderer* renderer):GameOver(renderer){}
	void draw(int xMouse, int yMouse, bool& mouseActionClicked) {
		auto tempImage = image;
		auto tempNextButton = nextButton;
		auto tempRetryButton = retryButton;
		nextButton = LoadImage("Next.png", renderer);
		retryButton = LoadImage("Retry.png", renderer);
		image = LoadImage("WinScreen.png", renderer);
		SDL_Rect destinationNext, destinationRetry;
		destinationRetry.x = 69;
		destinationRetry.y = 631;
		destinationNext.x = 354;
		destinationNext.y = 631;
		destinationNext.w = destinationNext.h = destinationRetry.h = destinationRetry.w = 80;
		//cout << "Mouse" << mouseActionClicked << endl;
		if (mouseActionClicked) {
			if (xMouse >= 69 && xMouse <= 69 + 80 && yMouse >= 631 && yMouse <= 631 + 80) {
				action = retry;
			}
			else if (xMouse >= 354 && xMouse <= 354 + 80 && yMouse >= 631 && yMouse <= 631 + 80) {
				action = nextMap;
			}

			mouseActionClicked = false;
		}


		SDL_RenderCopy(renderer, image, NULL, NULL);
		SDL_RenderCopy(renderer, nextButton, NULL, &destinationNext);
		SDL_RenderCopy(renderer, retryButton, NULL, &destinationRetry);


		SDL_DestroyTexture(tempImage);
		SDL_DestroyTexture(tempRetryButton);
		SDL_DestroyTexture(tempNextButton);
	}
	~WinScreen(){}

};


#pragma once
#include "SDL.h"
#include "Functions.h"
enum Action {
	nextMap,
	retry,
	back,
	setting,
	none
	
};
class GameOver
{
protected:
	SDL_Renderer* renderer;
	SDL_Texture* image;
	Action action;

public:
	GameOver() {
		action = none;
	}
	GameOver(SDL_Renderer* renderer) {
		this->renderer = renderer;
		action = none;
	}
	virtual void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
	virtual Action getAction() {
		return  action;
	}
	virtual void setAction(Action value) {
		action = value;
	}
	virtual void draw(int xMouse,int yMouse,bool &mouseActionClicked) {
		auto temp = image;
		image = LoadImage("GameOver.png", renderer); 
		//cout << "Mouse" << mouseActionClicked << endl;
		if (mouseActionClicked) {
			if (xMouse >= 210 && xMouse <= 210 + 80 && yMouse >= 390 && yMouse <= 390 + 80) {
				action = retry;
			}
			else if (xMouse >= 210 && xMouse <= 210 + 80 && yMouse >= 525 && yMouse <= 525 + 80) {
				action = back;

			}
			else if ((xMouse >= 210 && xMouse <= 210 + 80 && yMouse >= 685 && yMouse <= 685 + 80)) {
				action = setting;
			}
			mouseActionClicked = false;
		}

		
		SDL_RenderCopy(renderer, image, NULL, NULL);
		SDL_DestroyTexture(temp);
	}
	virtual ~GameOver(){}
};


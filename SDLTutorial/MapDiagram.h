#pragma once
#include <SDL.h>
#include "Functions.h"
class MapDiagram
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* mapDiagramImage;
	int selectedMap;
public:
	MapDiagram() {}
	void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
	MapDiagram(SDL_Renderer* renderer) {
		this->renderer = renderer;
		selectedMap = 0;
	}
	int getSelectedMap() {
		return selectedMap;

	}
	void setSelectedMap(int value) {
		selectedMap = value;
	}
	bool isInCircle(int xMouse, int yMouse, int xCircle, int yCircle, int radius) {
		float deltaX = xMouse - xCircle;
		float deltaY = yMouse - yCircle;
		float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
		if (distance <= radius) {
			//d
			return true;
		}
		else {

			return false;
		}

	}
	void draw(int xMouse, int yMouse, bool& mouseActionClicked) {
		auto temp = mapDiagramImage;
		mapDiagramImage = LoadImage("MapDiagram.png", renderer);
		if (mouseActionClicked) {
			if (isInCircle(xMouse, yMouse, 83, 562, 72)) {
				selectedMap = 1;
			}
			else if (isInCircle(xMouse, yMouse, 83, 236, 72)) {
				selectedMap = 2;
			}
			else if (isInCircle(xMouse, yMouse, 421, 236, 72)) {
				selectedMap = 3;
			}
			mouseActionClicked = false;
		}
		SDL_RenderCopy(renderer, mapDiagramImage, NULL, NULL);
		SDL_DestroyTexture(temp);
	}

};


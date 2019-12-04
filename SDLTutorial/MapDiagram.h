#pragma once
#include <SDL.h>
#include "Functions.h"
class MapDiagram
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* mapDiagramImage;
	int selectedMap;
	int unlockedMap;
public:

	MapDiagram() {}
	void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
	MapDiagram(SDL_Renderer* renderer) {
		this->renderer = renderer;
		selectedMap = 0;
	}
	void resetData() {
		selectedMap = 0;
	}
	void setUnlockedMap(int value) {
		unlockedMap = value;
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
	bool isInRectangle(int xMouse, int yMouse, int x, int y, int width, int height) {
		if (xMouse >= x && xMouse <= x + width && yMouse >= y && yMouse <= y + height) {
			return true;
		}
		return false;
	}
	void draw(int xMouse, int yMouse, bool& mouseActionClicked) {
		auto temp = mapDiagramImage;
		mapDiagramImage = LoadImage("MapDiagram.png", renderer);
		if (isInRectangle(xMouse, yMouse, 322, 535, 340 - 322, 575 - 535)) {
			//Phong to
			if (mouseActionClicked && unlockedMap >= 1) {
				selectedMap = 1;
			}
		}
		else if (isInRectangle(xMouse, yMouse, 242, 564, 272 - 242, 615 - 564)) {
			//Phong to 

			if (mouseActionClicked && unlockedMap >= 2) {
				selectedMap = 2;
			}
		}
		else if (isInRectangle(xMouse, yMouse, 153, 535, 182 - 153, 583 - 535)) {
			if (mouseActionClicked && unlockedMap >= 3) {
				selectedMap = 3;
			}
		}
		else if (isInRectangle(xMouse, yMouse, 85, 453, 130 - 85, 510 - 453)) {
			if (mouseActionClicked && unlockedMap >= 4) {
				selectedMap = 4;
			}
		}
		else if (isInRectangle(xMouse, yMouse, 87, 332, 129 - 87, 386 - 332)) {
			if (mouseActionClicked && unlockedMap >= 5) {
				selectedMap = 5;
			}
		}
		else if (isInRectangle(xMouse, yMouse, 87, 215, 125 - 87, 266 - 215)) {
			if (mouseActionClicked && unlockedMap >= 6) {

				selectedMap = 6;

			}
		}
		else if (isInRectangle(xMouse, yMouse, 364, 212, 414 - 364, 281 - 212)) {
			if (mouseActionClicked && unlockedMap >= 7) {
				selectedMap = 7;
			}
		}
		else if (isInRectangle(xMouse, yMouse, 364, 334, 409 - 364, 385 - 334)) {
			if (mouseActionClicked && unlockedMap >= 8) {
				selectedMap = 8;
			}
		}
		else if (isInRectangle(xMouse, yMouse, 366, 453, 405 - 366, 506 - 453)) {
			if (mouseActionClicked && unlockedMap >= 9) {
				selectedMap = 9;
			}
		}
		mouseActionClicked = false;

		SDL_RenderCopy(renderer, mapDiagramImage, NULL, NULL);
		SDL_DestroyTexture(mapDiagramImage);
		SDL_DestroyTexture(temp);
	}

};


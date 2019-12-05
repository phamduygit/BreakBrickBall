#pragma once
#include <SDL.h>
#include "Functions.h"
#include <memory>
#define  pt shared_ptr
#define mk make_shared
class MapDiagram
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* mapDiagramImage;
	int selectedMap;
	int unlockedMap;
public:

	MapDiagram() {}
	void setRenderer(SDL_Renderer*& renderer) {
		this->renderer = renderer;
	}
	MapDiagram(SDL_Renderer* &renderer) {
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
		SDL_RenderCopy(renderer, mapDiagramImage, NULL, NULL);
		if (isInRectangle(xMouse, yMouse, 322, 535, (340 - 322), (575 - 535) * 1)) {
			SDL_Texture* Image1 = LoadImage("Image/1.png", renderer);
			DrawInRenderer(renderer, Image1, 322 - 10, 535 - 10, (340 - 322) * 1.6, (575 - 535) * 1.6);
			if (mouseActionClicked && unlockedMap >= 1) {
				selectedMap = 1;
			}
			SDL_DestroyTexture(Image1);
		}
		else if (isInRectangle(xMouse, yMouse, 242, 564, (272 - 242) * 1, (615 - 564) * 1)) {
			SDL_Texture* Image2 = LoadImage("Image/2.png", renderer);
			DrawInRenderer(renderer, Image2, 242 - 10, 564 - 10, (272 - 242) * 1.6, (615 - 564) * 1.6);
			if (mouseActionClicked && unlockedMap >= 2) {
				selectedMap = 2;
			}
			SDL_DestroyTexture(Image2);
		}
		else if (isInRectangle(xMouse, yMouse, 153, 535, (182 - 153) * 1, (583 - 535) * 1)) {
			SDL_Texture* Image3 = LoadImage("Image/3.png", renderer);
			DrawInRenderer(renderer, Image3, 153 - 10, 535 - 10, (182 - 153) * 1.6, (583 - 535) * 1.6);
			if (mouseActionClicked && unlockedMap >= 3) {
				selectedMap = 3;
			}
			SDL_DestroyTexture(Image3);
		}
		else if (isInRectangle(xMouse, yMouse, 85, 453, (130 - 85) * 1, (510 - 453) * 1)) {
			SDL_Texture* Image4 = LoadImage("Image/4.png", renderer);
			DrawInRenderer(renderer, Image4, 85 - 10, 453 - 10, (130 - 85) * 1.6, (510 - 453) * 1.6);
			if (mouseActionClicked && unlockedMap >= 4) {
				selectedMap = 4;
			}
			SDL_DestroyTexture(Image4);
		}
		else if (isInRectangle(xMouse, yMouse, 87, 332, (129 - 87) * 1, (386 - 332) * 1)) {
			SDL_Texture* Image5 = LoadImage("Image/5.png", renderer);
			DrawInRenderer(renderer, Image5, 87 - 10, 332 - 10, (129 - 87) * 1.6, (386 - 332) * 1.6);
			if (mouseActionClicked && unlockedMap >= 5) {
				selectedMap = 5;
			}
			SDL_DestroyTexture(Image5);
		}
		else if (isInRectangle(xMouse, yMouse, 87, 215, (125 - 87) * 1, (266 - 215) * 1)) {
			SDL_Texture* Image6 = LoadImage("Image/6.png", renderer);
			DrawInRenderer(renderer, Image6, 87 - 10, 215 - 10, (125 - 87) * 1.6, (266 - 215) * 1.6);
			if (mouseActionClicked && unlockedMap >= 6) {
				selectedMap = 6;

			}
			SDL_DestroyTexture(Image6);
		}
		else if (isInRectangle(xMouse, yMouse, 364, 212, (414 - 364) * 1, (281 - 212) * 1)) {
			SDL_Texture* Image7 = LoadImage("Image/7.png", renderer);
			DrawInRenderer(renderer, Image7, 364 - 10, 212 - 10, (414 - 364) * 1.6, (281 - 212) * 1.6);
			if (mouseActionClicked && unlockedMap >= 7) {
				selectedMap = 7;
			}
			SDL_DestroyTexture(Image7);
		}
		else if (isInRectangle(xMouse, yMouse, 364, 334, (409 - 364) * 1, (385 - 334) * 1)) {
			SDL_Texture* Image8 = LoadImage("Image/8.png", renderer);
			DrawInRenderer(renderer, Image8, 364 - 10, 334 - 10, (409 - 364) * 1.6, (385 - 334) * 1.6);
			if (mouseActionClicked && unlockedMap >= 8) {
				selectedMap = 8;
			}
			SDL_DestroyTexture(Image8);
		}
		else if (isInRectangle(xMouse, yMouse, 366, 453, (405 - 366) * 1, (506 - 453) * 1)) {
			SDL_Texture* Image9 = LoadImage("Image/9.png", renderer);
			DrawInRenderer(renderer, Image9, 366 - 10, 453 - 10, (405 - 366) * 1.6, (506 - 453) * 1.6);
			if (mouseActionClicked && unlockedMap >= 9) {
				selectedMap = 9;
			}
			SDL_DestroyTexture(Image9);
		}
		mouseActionClicked = false;


		SDL_DestroyTexture(mapDiagramImage);
		SDL_DestroyTexture(temp);
	}
	~MapDiagram() {
		delete mapDiagramImage;
	}

};


#pragma once
#include <SDL.h>
#include <string>
#include "Functions.h"
using namespace std;

class Brick
{
protected:
	//Vi tri 
	int x;
	int y;
	int size;
	SDL_Texture* image;
	SDL_Renderer* renderer;

public:
	Brick(SDL_Renderer*& renderValue) {
		renderer = renderValue;
	}
	int getX() {
		return x;
	}
	void setX(int xValue) {
		x = xValue;
	}
	int getY() {
		return y;
	}
	void setY(int yValue) {
		y = yValue;
	}
	int getSize() {
		return size;
	}
	void setSize(int sizeValue) {
		size = sizeValue;
	}
	void setImage(string name) {
		image = LoadImage(name, renderer);
	}
	void draw() {
		DrawInRenderer(renderer, image, x, y, size, size);
	}


};


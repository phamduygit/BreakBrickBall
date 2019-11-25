#pragma once
#include <SDL.h>
#include <string>
#include "Functions.h"
using namespace std;

class Brick
{
protected: 
	float x;
	float y;
	float size;
	SDL_Texture* image;
	SDL_Renderer* renderer;
public:
	Brick() {
		x = 100;
		y = 100;
		size = 50;
		image = NULL;
		renderer = NULL;
	}
	Brick(SDL_Renderer*& renderValue) {
		x = 100;
		y = 100;
		size = 50;
		image = NULL;
		renderer = renderValue;
	}
	float getX() {
		return x;
	}
	void setX(float xValue) {
		x = xValue;
	}
	float getY() {
		return y;
	}
	void setY(float yValue) {
		y = yValue;
	}
	float getSize() {
		return size;
	}
	void setSize(float sizeValue) {
		size = sizeValue;
	}
	void setImage(string name) {
		image = LoadImage(name, renderer);
	}
	void draw() {
		DrawInRenderer(renderer, image, x, y, size, size);
	}


};


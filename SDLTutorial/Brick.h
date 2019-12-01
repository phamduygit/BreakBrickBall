#pragma once
#include <SDL.h>
#include <string>
#include "Functions.h"
#include "TextureManager.h"
using namespace std;

class Brick
{
protected: 
	 float x;
	 float y;
	 float size;
	SDL_Texture* image;
	SDL_Renderer* renderer;
	 float currentFrame;
	 float currentRow;
public:
	Brick() {
		x = 100;
		y = 100;
		size = 50;
		image = NULL;
		renderer = NULL;
		currentRow = 1;
		currentFrame = 4;
	}
	Brick(SDL_Renderer*& renderValue) {
		
		x = 370;
		y = 50;
		size =50 ;
		image = NULL;
		renderer = renderValue;
		currentRow = 1;
		currentFrame = 1;
	}
	Brick(SDL_Renderer*& renderValue, float _x, float _y) {

		x = _x;
		y = _y;
		size = 50;
		image = NULL;
		renderer = renderValue;
		currentRow = 1;
		currentFrame = 1;
	}
	 float getX() {
		return x;
	}
	void setX( float xValue) {
		x = xValue;
	}
	 float getY() {
		return y;
	}
	void setY( float yValue) {
		y = yValue;
	}
	 float getSize() {
		return size;
	}
	void setSize( float sizeValue) {
		size = sizeValue;
	}
	void setImage(string name) {
		image = LoadImage(name, renderer);
	}
	void setFrame( float val) {

		currentFrame = val;

	}
	 float getFrame() {
		return currentFrame;
	}
	void update() {

	}
	
	void draw() {
		//DrawInRenderer(renderer, image, x, y, size, size);
		TextureManager::GetInstance()->drawFrame("Brick", x, y, size, size, 1, currentFrame, renderer);
	}


};


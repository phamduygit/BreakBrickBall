#pragma once
#include <SDL.h>
#include <string>
#include "Functions.h"
#include "TextureManager.h"
#include "MagicBall.h"
#include <string>
#include <sstream>

using namespace std;

class Brick
{
protected: 
	int x;
	int y;
	float size;
	//SDL_Texture* image;
	SDL_Renderer* renderer;
	int currentFrame;
	int currentRow;
public:
	virtual string toString() {
		stringstream out;
		out << x << " " << y << " " << currentFrame;
		return out.str();

	}
	Brick() {
		x = 100;
		y = 100;
		size = 50;
		//image = NULL;
		renderer = NULL;
		currentRow = 1;
		currentFrame = 4;
	}
	Brick(SDL_Renderer*& renderValue) {
		
		x = 370;
		y = 50;
		size =50 ;
		//image = NULL;
		renderer = renderValue;
		currentRow = 1;
		currentFrame = 1;
	}
	Brick(SDL_Renderer*& renderValue,int _x,int _y) {

		x = _x;
		y = _y;
		size = 50;
	//	image = NULL;
		renderer = renderValue;
		currentRow = 1;
		currentFrame = 1;
	}
	virtual int getX() {
		return x;
	}
	virtual void setX(int xValue) {
		x = xValue;
	}
	virtual int getY() {
		return y;
	}
	virtual void setY(int yValue) {
		y = yValue;
	}
	virtual float getSize() {
		return size;
	}
	virtual void setSize(float sizeValue) {
		size = sizeValue;
	}
	void setImage(string name) {
	//	image = LoadImage(name, renderer);
	}
	virtual void setFrame(int val) {

		currentFrame = val;
	}
	virtual int getFrame() {
		return currentFrame;
	}
	virtual void update() {

	}
	
	virtual void draw() {
		//DrawInRenderer(renderer, image, x, y, size, size);
		TextureManager::GetInstance()->drawFrame("Brick", float(x), float(y), size, size, 1, currentFrame, renderer);
	}


};


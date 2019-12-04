#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Functions.h"
#include <string>
#include "SettingScreen.h"
using namespace std;
class Paddle
{
protected:
	float x;
	float y;
	float width;
	float height;
	float speed;
	float deltaX;
	float previousX;
	SDL_Texture* image;
	SDL_Renderer* renderer;
	static Paddle* instance;
	Paddle() {
		x = 150;
		y = 700;
		width = 80;
		height = 10;
		speed = 5;
		image = NULL;
		renderer = NULL;
		deltaX = 0;

		previousX = 0;

	}
	Paddle(SDL_Renderer* &RenderValue) {
		x = 150;
		y = 750;
		width = 150;
		height = 20;
		speed = 5;
		image = NULL;
		renderer = RenderValue;

		deltaX = 0;
		previousX = 0;

	}
public:
	static Paddle* Instance(SDL_Renderer* &renderer) {
		if (instance == NULL) {
			instance = new  Paddle(renderer);

		}
		return instance;
	}


	virtual float getHeight() {
		return height;
	}
	virtual float getWidth() {
		return width;
	}
	void setWidth(float newwidth) {
		this->width = newwidth;
	}
	virtual float getX() {
		return x;
	}
	virtual void setX(float value) {
		x = value;
	}
	virtual float getY() {
		return y;
	}
	virtual void setY(float value) {
		y = value;
	}
	virtual void setSpeed(float value) {
		speed = value;
	}
	virtual float getSpeed() {
		return speed;
	}
	virtual void setImage(string name) {
		image = LoadImage(name, renderer);
	}
	virtual void draw() {
		DrawInRenderer(renderer, image, x, y, width, height);
	}
	//vector <int > generateXPos(float xBall) {
	//	vector <int > result;
	//	int start = xBall

	//}

	void move(float xMouse, bool moveLR[],float xBall, SettingAction setting) {
		previousX = x;
		if (setting == autoPlay) {
			
			if(xBall-width/2>=0&&xBall+width/2<=500)
				x = xBall - width / 2;	

		}
		else if (setting == playWithMouse) {
			xMouse = xMouse - width / 2;
			if (xMouse < 0) {
				this->x = 0;
			}
			else if (xMouse + width > 500) {
				this->x = 500 - width;

			}
			else {
				x = xMouse;
			}
			deltaX = x - previousX;
		}
		else if (setting == playWithKeyboard) {
			if (moveLR[0]) {
				if (x > 0) {
					x -= speed;
				}
			}

			if (moveLR[1]) {
				if (x + width < 500) {
					x += speed;
				}
			}

		}
		deltaX = x - previousX;


	}
	float getDeltaX() {
		return deltaX;
	}
	void resetDeltaX() {
		deltaX = 0;
	}

};


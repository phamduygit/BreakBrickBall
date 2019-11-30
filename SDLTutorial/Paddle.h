#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Functions.h"
#include <string>
using namespace std;
class Paddle
{
protected:
	float x;
	float y;
	float w;
	float h;
	float speed;
	SDL_Texture* image;
	SDL_Renderer* renderer;
public:
	Paddle() {
		x = 150;
		y = 700;
		w = 80;
		h = 10;
		speed = 5;
		image = NULL;
		renderer = NULL;
	}
	Paddle(SDL_Renderer* RenderValue) {
		x = 150;
		y = 750;
		w = 120;
		h = 20;
		speed = 5;
		image = NULL;
		renderer = RenderValue;
	}
	virtual int getSize() {
		return w;
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
		DrawInRenderer(renderer, image, x, y, w, h);
	}
	virtual void Move(bool moveLR[]) {
		if (moveLR[0]) {
			if (x > 0) {
				x -= speed;
			}
			else {
				x += 0;
			}
		}
		else {
			x = x;
		}
		if (moveLR[1]) {
			if (x + 120 < 500) {
				x += speed;
			}
			else {
				x += 0;
			}
		}
		else {
			x = x;
		}
	}
};


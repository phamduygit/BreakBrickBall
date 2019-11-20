#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include "Functions.h"
using namespace std;
class Ball
{
private:
	int x;
	int y;
	int radius;
	int speed;
	SDL_Texture* image;
	SDL_Renderer* renderer;
public:
	Ball();
	Ball(SDL_Renderer*& rendererValue) {
		x = 250;
		y = 700;
		radius = 20;
		speed = 3;
		image = NULL;
		renderer = rendererValue;
	}
	~Ball();
	int getX() {
		return x;
	}
	void setX(int value) {
		x = value;
	}
	int getY() {
		return y;
	}
	void setY(int value) {
		y = value;
	}
	void setSpeed(int value) {
		speed = value;
	}
	int getSpeed() {
		return speed;
	}
	int getRadius() {
		return radius;
	}
	void setRadius(int value) {
		radius = value;
	}
	void setImage(string name) {
		image = LoadImage(name, renderer);
	}
	void draw() {
		DrawInRenderer(renderer, image, x - radius, y - radius, radius * 2, 100);
	}
};


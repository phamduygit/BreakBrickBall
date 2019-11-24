#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <cmath>
#include "Functions.h"
using namespace std;
class Ball
{
private:
	float x;
	float y;
	float radius;
	float speed;
	float degree;
	SDL_Texture* image;
	SDL_Renderer* renderer;
public:
	Ball();
	Ball(SDL_Renderer*& rendererValue) {
		x = 250;
		y = 700;
		radius = 15;
		speed = 3;
		image = NULL;
		degree = 60;
		renderer = rendererValue;
	}
	~Ball();
	float getX() {
		return x;
	}
	void setX(float value) {
		x = value;
	}
	float getY() {
		return y;
	}
	void setY(float value) {
		y = value;
	}
	void setSpeed(float value) {
		speed = value;
	}
	float getSpeed() {
		return speed;
	}
	float getRadius() {
		return radius;
	}
	void setRadius(float value) {
		radius = value;
	}
	float getDegree() {
		return degree;
	}
	void setDegree(float value) {
		degree = value;
	}
	void setImage(string name) {
		image = LoadImage(name, renderer);
	}
	void draw() {
		//DrawInRenderer(renderer, image, x - radius, y - radius, radius * 2, 100);
		DrawInRendererRotate(renderer, image, x - radius, y - radius, radius * 2, 100.0, radius, 90 - degree);
	}
	void move() {
		x += float(cos(degree * 3.14 / 180) * speed);
		y -= float(sin(degree * 3.14 / 180) * speed);
	}
};


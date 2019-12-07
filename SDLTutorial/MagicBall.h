#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <cmath>
#include "Functions.h"
//#include"Game.h"
struct Point2D {
	float x;
	float y;

};
struct Cirle {
	float x;
	float y;
	float r;
};

using namespace std;
class Ball
{
private:
	float x;
	float y;
	float radius;
	float speed;
	float degree;
	float backupSpeed;
	SDL_Texture* image;
	SDL_Renderer* renderer;
	bool isLaunch;
	float backupDegree;	
	Ball(SDL_Renderer*& rendererValue) {
		x = 250;
		y = 700;
		radius = 15;
		speed =6;
		image = NULL;
		degree = 60;
		renderer = rendererValue;
		isLaunch = false;
	}
	static Ball* instance;
public:
	float getBackupSpeed() {
		return backupSpeed;
	}
	float getBackupDegree() {
		return backupDegree;
	}
	void setBackupDegree(float value) {
		backupDegree = value;

	}
	void setBackupSpeed(float value) {
		backupSpeed = value;
	}
	void reset(float x,float y) {
		this->x = x ;
		this->y = y;
	
		isLaunch = false;
	}
	static Ball* Instance(SDL_Renderer*& rendererValue) {
		if (instance == NULL) {
			instance = new Ball(rendererValue);
		}
		return instance;
	}
	Ball();

	~Ball();
	bool getIsLaunch() {
		return isLaunch;
	}
	void setIsLaunch(bool val) {
		isLaunch = val;

	}
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
	float distanceSquared(float x1, float y1, float x2, float y2)
	{
		float deltaX = x2 - x1;
		float deltaY = y2 - y1;
		return deltaX * deltaX + deltaY * deltaY;
	}
	//Hàm kiểm soát việc va chạm giữa viên gạch và quả bóng 
	//_x,_y size là tọa độ và kích thước của viên gạch
	//
	bool isCollision(float _x,float _y,float size) {
		//Vòng tròn a 
		Cirle a;
		a.x =x;
		a.y = y;
		a.r = radius;
		//Hình chữ nhật b 

		SDL_FRect b;
		b.x = _x;
		b.y = _y;
		b.w = size;
		b.h = size;
		float cX, cY;
		//Tìm điểm gần tâm quả bóng nhất
		if (a.x < b.x)
		{
			cX = b.x;
		}
		else if (a.x > b.x + b.w)
		{
			cX = b.x + b.w;
		}
		else
		{
			cX = a.x;
		}

		//Tìm y gần tâm quả bóng nhất 
		if (a.y < b.y)
		{
			cY = b.y;
		}
		else if (a.y > b.y + b.h)
		{
			cY = b.y + b.h;
		}
		else
		{
			cY = a.y;
		}

		//Nếu khoảng cách từ điểm gần với tâm vòng tròn đến tâm vòng tròng nhỏ hơn bán kính thì kết luận 
		//xảy ra va chạm
		if (distanceSquared(a.x, a.y, cX, cY) < a.r *a.r)
		{
		
			return true;
		}

		//Ngược lại thì kết luận là không xảy ra va chạm
		return false;



	}
	//bool isCollision(float _x, float _y, float width,float height) {
	//	Cirle a;
	//	a.x = this->x;
	//	a.y = y;
	//	a.r = radius;
	//	SDL_FRect b;
	//	b.x = _x;
	//	b.y = _y;
	//	b.w = width;
	//	b.h = height;
	//	float cX, cY;

	//	//Find closest x offset
	//	if (a.x < b.x)
	//	{
	//		cX = b.x;
	//	}
	//	else if (a.x > b.x + b.w)
	//	{
	//		cX = b.x + b.w;
	//	}
	//	else
	//	{
	//		cX = a.x;
	//	}

	//	//Find closest y offset
	//	if (a.y < b.y)
	//	{
	//		cY = b.y;
	//	}
	//	else if (a.y > b.y + b.h)
	//	{
	//		cY = b.y + b.h;
	//	}
	//	else
	//	{
	//		cY = a.y;
	//	}

	//	//If the closest pofloat is inside the circle
	//	if (distanceSquared(a.x, a.y, cX, cY) < a.r * a.r)
	//	{
	//		//This box and the circle have collided
	//		return true;
	//	}

	//	//If the shapes have not collided
	//	return false;



	//}
	//Khởi tạo hình ảnh cho quả bóng
	void setImage(string name) {
		image = LoadImage(name, renderer);
	}
	//Vẽ quả bóng lên màn hình game
	void draw() {
		//DrawInRenderer(renderer, image, x - radius, y - radius, radius * 2, 100);
		DrawInRendererRotate(renderer, image, x - radius, y - radius, radius * 2, radius * 2, radius, 90 - degree);

	}
	//Hàm di chuyển quả bóng
	void move() {
		//Khi nhận tín hiệu được bay thì mới bắt đầu di chuyển
		if (isLaunch) {
			x += float(cos(degree * 3.14 / 180) * speed);
			y -= float(sin(degree * 3.14 / 180) * speed);
		}
	}
};


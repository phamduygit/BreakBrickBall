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
	//Tọa độ hiện tại của quả bóng
	float _x;
	float _y;
	//Bán kính của quả bóng
	float _radius;
	//Tốc độ di chuyển của quả bóng
	float _speed;
	//Góc bay quả quả bóng
	float _degree;
	//Tốc độ sao lưu lại 
	float _backupSpeed;
	//Struct lưu trữ hình ảnh quả bóng
	SDL_Texture* _image;
	//Struct chưa thông tin những thứ sẽ render lên màn hình 
	SDL_Renderer* _renderer;
	//Trạng thái quả bóng đã bay chưa 
	bool _isLaunch;
	//Sao lưu gốc bay quả bóng 
	float _backupDegree;	
	//Hàm khởi tạo có đối số 
	float _backupRadius;
	Ball(SDL_Renderer*& value) {
		_x = 250;
		_y = 700;
		_radius = 15;
		_speed =6;
		_image = NULL;
		_degree = 60;
		this->_renderer = value;
		_isLaunch = false;
	}
	//Thể hiện của đối tượng
	static Ball* instance;

public:

	void setBackupRadius(float value) {
		_backupRadius = value;
	}
	float getBackupRadius() {
		return _backupRadius;
	}
	float getBackupSpeed() {
		return _backupSpeed;
	}
	float getBackupDegree() {
		return _backupDegree;
	}
	void setBackupDegree(float value) {
		_backupDegree = value;

	}
	void setBackupSpeed(float value) {
		_backupSpeed = value;
	}
	void reset(float x,float y) {
		this->_x = x ;
		this->_y = y;
	
		_isLaunch = false;
	}
	static Ball* Instance(SDL_Renderer*& value) {
		if (instance == NULL) {
			instance = new Ball(value);
		}
		return instance;
	}
	Ball();

	~Ball();
	bool getIsLaunch() {
		return _isLaunch;
	}
	void setIsLaunch(bool val) {
		_isLaunch = val;

	}
	float getX() {
		return _x;
	}
	void setX(float value) {
		_x = value;
	}
	float getY() {
		return _y;
	}
	void setY(float value) {
		_y = value;
	}
	void setSpeed(float value) {
		_speed = value;
		
	}
	float getSpeed() {
		return _speed;
	}
	float getRadius() {
		return _radius;
	}
	void setRadius(float value) {
		_radius = value;
	}
	float getDegree() {
		return _degree;
	}
	void setDegree(float value) {
		_degree = value;
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
	bool isCollision(float x,float y,float size) {
		//Vòng tròn a 
		Cirle a;
		a.x =_x;
		a.y = _y;
		a.r = _radius;
		//Hình chữ nhật b 

		SDL_FRect b;
		b.x = x;
		b.y = y;
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
		_image = LoadImage(name, _renderer);
	}
	//Vẽ quả bóng lên màn hình game
	void draw() {
		//DrawInRenderer(renderer, image, x - radius, y - radius, radius * 2, 100);
		DrawInRendererRotate(_renderer, _image, _x - _radius, _y - _radius, _radius * 2, _radius * 2, _radius, 90 - _degree);

	}
	//Hàm di chuyển quả bóng
	void move() {
		//Khi nhận tín hiệu được bay thì mới bắt đầu di chuyển
		if (_isLaunch) {
			_x += float(cos(_degree * 3.14 / 180) * _speed);
			_y -= float(sin(_degree * 3.14 / 180) * _speed);
		}
	}
};


#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <cmath>
#include "Functions.h"
#include "Ball.h"
#include "TextureManager.h"

struct Cirle {
	float x;
	float y;
	float r;
};

using namespace std;
class MagicBall:public Ball
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
	float trigonometric_angle;
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
	int explodeFrame;
	bool isExplode;
	MagicBall(SDL_Renderer*& value):Ball() {
		_x = 250;
		_y = 700;
		_radius = 20;
		_speed =6;
		_image = NULL;
		trigonometric_angle = 60;
		this->_renderer = value;
		_isLaunch = false;
		_backupRadius = 20;
		explodeFrame = 1;
		isExplode = false;
	}
	//Thể hiện của đối tượng
	static MagicBall* instance;

public:
	//Thiết bán kính đã được sao lưu từ trước
	void setBackupRadius(float value) {
		_backupRadius = value;
	}
	//Lấy ra bán kính đã sao lưu
	float getBackupRadius() {
		return _backupRadius;
	}
	//Lấy ra tốc độ đã sao lưu từ trước
	float getBackupSpeed() {
		return _backupSpeed;
	}
	//Lấy ra gốc bay đã sao lưu từ trước 
	float getBackupDegree() {
		return _backupDegree;
	}
	//Thiết lập gốc bay sao lưu lại
	void setBackupDegree(float value) {
		_backupDegree = value;

	}
	//Thiết lập tốc độ sao lưu lại
	void setBackupSpeed(float value) {
		_backupSpeed = value;
	}
	//Khôi phục lại trạng thái cho trái bóng
	void reset(float x,float y) {
		this->_x = x ;
		this->_y = y;	
		_isLaunch = false;
	}
	//Phương thức lấy thể hiện của singleton
	static MagicBall* Instance(SDL_Renderer*& value) {
		if (instance == NULL) {
			instance = new MagicBall(value);
		}
		return instance;
	}
	//Hàm khởi tạo không đối số
	MagicBall();
	//Hàm khởi tạo có đối số
	~MagicBall();
	//Lấy ra thông tin trái bóng đã bay chưa 
	bool getIsLaunch() {
		return _isLaunch;
	}
	//Thiết lập trạng thái trái bóng đã bay hay chưa
	void setIsLaunch(bool val) {
		_isLaunch = val;

	}
	//Lấy ra tọa độ x cho quả bóng
	float getX() {
		return _x;
	}
	//Thiết lập tọa độ X cho quả bóng
	void setX(float value) {
		_x = value;
	}
	//Lấy ra tọa độ y cho quả bóng
	float getY() {
		return _y;
	}
	//Thiết lập tọa độ y cho quả bóng
	void setY(float value) {
		_y = value;
	}
	//Thiết lập tốc độ cho quả bóng
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
		return trigonometric_angle;
	}
	void setDegree(float value) {
		trigonometric_angle = value;
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
	bool isCollision(float x, float y, float width,float height) {
		Cirle a;
		a.x = this->_x;
		a.y = _y;
		a.r = _radius;
		SDL_FRect b;
		b.x = x;
		b.y = y;
		b.w = width;
		b.h = height;
		float cX, cY;

		//Find closest x offset
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

		//Find closest y offset
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

		//If the closest pofloat is inside the circle
		if (distanceSquared(a.x, a.y, cX, cY) < a.r * a.r)
		{
			//This box and the circle have collided
			return true;
		}

		//If the shapes have not collided
		return false;



	}
	void explode() {
		isExplode = true;
	}
	void restoreFromExplosion() {
		isExplode = false;
	}
	//Khởi tạo hình ảnh cho quả bóng
	void setImage(string name) {
		_image = loadImage(name, _renderer);
	}
	bool getIsExplode() {
		return isExplode;
	}
	//Vẽ quả bóng lên màn hình quả bóng
	void draw() {
		if (!isExplode) {
			//DrawInRenderer(renderer, image, x - radius, y - radius, radius * 2, 100);
			DrawInRendererRotate(_renderer, _image, _x - _radius, _y - _radius, _radius * 2, _radius * 2, _radius, 90 - trigonometric_angle);
			
		}
		else {
			//SDL_Texture* _explodeImage = loadImage("Explosion.png",_renderer);
			TextureManager::GetInstance()->drawFrame("Explosion", _x -50, _y - 50,100, 100,1, explodeFrame, _renderer);
			explodeFrame++;
			SDL_Delay(50);
			cout << "called";
			if (explodeFrame == 6) {
				explodeFrame = 1;
				isExplode = false;
			}
		}
	}
	//Hàm di chuyển quả bóng
	void move() {
		//Khi nhận tín hiệu được bay thì mới bắt đầu di chuyển
		if (_isLaunch) {
			_x += float(cos(trigonometric_angle * 3.14 / 180) * _speed);
			_y -= float(sin(trigonometric_angle * 3.14 / 180) * _speed);
		}
	}
};


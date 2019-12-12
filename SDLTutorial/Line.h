#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include "MagicBall.h"

using namespace std;
class Line
{
private:
	//Là chiều rộng của màn hình game
	float _width;
	//Là chiều cao của màn hình game
	float _height;
	//Vị trí hiện tại của paddle
	SDL_FPoint _paddle;
	//Tọa độ của con trỏ chuột
	SDL_Point _mouse;
	//Struct renderer
	SDL_Renderer* _renderer;
	//Hệ số góc nối giữa paddle và con trỏ chuột
	float _heSoGoc;
	//Kích thước của paddle
	float _paddleSize;
public:
	//Hàm khỏi tạo không đối số
	Line() {
		_width = 500;
		_height = 800;
		_heSoGoc = 0;
		_mouse = { 0, 0 };
		_paddle = { 0 , 0 };
		_paddleSize = 0;
		_renderer = NULL;

	}
	//Lấy ra hệ số gốc
	float getHeSoGoc() {
		return _heSoGoc;

	}
	//Thiết lập renderer cho đối tượng
	void setRenderer(SDL_Renderer*& value) {
		_width = 500;
		_height = 800;
		this->_renderer = value;
		_heSoGoc = 0;
		_mouse = { 0, 0 };
		_paddle = { 0 , 0 };
		_paddleSize = 120;
	}
	//Sét thống tin cho paddle gồm vị trí và kích thước
	void setPaddle(float x, float y, float paddleSize) {
		_paddle.x = x;
		_paddle.y = y;
		_paddleSize = paddleSize;
	}
	//Set tọa độ con trỏ chuột
	void setMouse(int x, int y) {
		_mouse.x = x;
		_mouse.y = y;
	}

	//Tính giá trị khi thay điểm c vào đường thẳng được vẽ bởi hai điểm a b 
	float calc(SDL_FPoint a, SDL_FPoint b, SDL_FPoint c) {
		return (c.x - a.x) / (b.x - a.x) - (c.y - a.y) / (b.y - a.y);

	}
	float calc(SDL_FPoint a, SDL_FPoint b, SDL_Point c) {
		return (c.x - a.x) / (b.x - a.x) - (c.y - a.y) / (b.y - a.y);

	}
	float calc(SDL_FPoint a, SDL_Point b, SDL_Point c) {
		return (c.x - a.x) / (b.x - a.x) - (c.y - a.y) / (b.y - a.y);

	}

	void draw(float hsGoc, float hsTuDo) {
		SDL_FPoint A;
		SDL_FPoint B;
		SDL_FPoint topLeft = { 0,0 };
		SDL_FPoint bottomLeft = { 0,_height };
		SDL_FPoint topRight = { _width,0 };
		SDL_FPoint bottomRight = { _width,_height };
		SDL_Point mouseF = { _mouse.x,_mouse.y };
		//Kiểm tra xem con trỏ chuột và điểm bên dưới bên trái màn hình và vị trí con trỏ chuột có nằm cùng 
		//bờ với đường thẳng vẽ từ paddle đến diểm trên cùng bên trái
		//tương tự như vậy đối với bên phải 
		if (calc(_paddle, topLeft, bottomLeft) * calc(_paddle, topLeft, _mouse) > 0 || calc(_paddle, topRight, bottomRight) * calc(_paddle, topRight, _mouse) > 0) {
			if (hsGoc >= 0) {

				A.x = _paddle.x;
				A.y = _paddle.y;
				B.x = 0;
				B.y = hsTuDo;
				SDL_RenderDrawLineF(_renderer, A.x + _paddleSize / 2, A.y - MagicBall::Instance(_renderer)->getRadius(), B.x, B.y);
				//Vẽ tia đối xứng

				hsGoc = -hsGoc;
				A.x = 0;
				A.y = A.x * hsGoc + hsTuDo;
				B.y = 0;
				B.x = (B.y - hsTuDo) / hsGoc;
				SDL_RenderDrawLineF(_renderer, A.x, A.y, B.x, B.y);
			}
			//Ngược lại thì tia Ox sẽ là phần phản xạ đường thẳng từ paddle đến con trỏ chuột 
			else
			{
				A.x = _paddle.x;
				A.y = _paddle.y;
				B.x = _width;
				B.y = hsGoc * B.x + hsTuDo;
				SDL_RenderDrawLineF(_renderer, A.x + _paddleSize / 2, A.y - MagicBall::Instance(_renderer)->getRadius(), B.x, B.y);
				hsGoc = -hsGoc;
				hsTuDo = B.y - B.x * hsGoc;
				A.y = 0;
				A.x = (A.y - hsTuDo) / hsGoc;
				SDL_RenderDrawLineF(_renderer, A.x, A.y, B.x, B.y);
			}
		}
		else {
			if (hsGoc >= 0) {
				A.x = _paddle.x;
				A.y = _paddle.y;
				B.x = -hsTuDo / hsGoc;
				B.y = 0;
				SDL_RenderDrawLineF(_renderer, A.x + _paddleSize / 2, A.y - MagicBall::Instance(_renderer)->getRadius(), B.x, B.y);
				//Vẽ tia đối xứng
				hsGoc = -hsGoc;
				hsTuDo = B.y - hsGoc * B.x;
				A.x = 0;
				A.y = hsTuDo;
				SDL_RenderDrawLineF(_renderer, A.x, A.y, B.x, B.y);
			}
			else
			{
				A.x = _paddle.x;
				A.y = _paddle.y;
				B.x = -hsTuDo / hsGoc;
				B.y = 0;
				SDL_RenderDrawLineF(_renderer, A.x + _paddleSize / 2, A.y - MagicBall::Instance(_renderer)->getRadius(), B.x, B.y);
				hsGoc = -hsGoc;
				hsTuDo = B.y - hsGoc * B.x;
				A.x = _width;
				A.y = A.x * hsGoc + hsTuDo;
				SDL_RenderDrawLineF(_renderer, A.x, A.y, B.x, B.y);
			}

		}
	}

	void draw() {
		_heSoGoc = (_paddle.y - (float)_mouse.y) / (_paddle.x + _paddleSize / 2 - (float)_mouse.x);
		float hsTuDo = _mouse.y - _heSoGoc * _mouse.x;
		draw(_heSoGoc, hsTuDo);
	}





};


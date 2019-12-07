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
	float width;
	//Là chiều cao của màn hình game
	float height;
	//Vị trí hiện tại của paddle
	SDL_FPoint paddle;
	//Tọa độ của con trỏ chuột
	SDL_Point mouse;
	//Struct renderer
	SDL_Renderer* renderer;
	//Hệ số góc nối giữa paddle và con trỏ chuột
	float heSoGoc;
	//Kích thước của paddle
	float paddleSize;
public:
	//Hàm khỏi tạo không đối số
	Line() {
		width = 500;
		height = 800;
		heSoGoc = 0;
		mouse = { 0, 0 };
		paddle = { 0 , 0 };
		paddleSize = 0;
		renderer = NULL;

	}
	//Lấy ra hệ số gốc
	float getHeSoGoc() {
		return heSoGoc;

	}
	//Thiết lập renderer cho đối tượng
	void setRenderer(SDL_Renderer*& renderer) {
		width = 500;
		height = 800;
		this->renderer = renderer;
		heSoGoc = 0;
		mouse = { 0, 0 };
		paddle = { 0 , 0 };
		paddleSize = 120;
	}
	//Sét thống tin cho paddle gồm vị trí và kích thước
	void setPaddle(float x, float y, float _paddleSize) {
		paddle.x = x;
		paddle.y = y;
		paddleSize = _paddleSize;
	}
	//Set tọa độ con trỏ chuột
	void setMouse(int x, int y) {
		mouse.x = x;
		mouse.y = y;
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
		SDL_FPoint bottomLeft = { 0,height };
		SDL_FPoint topRight = { width,0 };
		SDL_FPoint bottomRight = { width,height };
		SDL_Point mouseF = { mouse.x,mouse.y };
		//Kiểm tra xem con trỏ chuột và điểm bên dưới bên trái màn hình và vị trí con trỏ chuột có nằm cùng 
		//bờ với đường thẳng vẽ từ paddle đến diểm trên cùng bên trái
		//tương tự như vậy đối với bên phải 
		if (calc(paddle, topLeft, bottomLeft) * calc(paddle, topLeft, mouse) > 0 || calc(paddle, topRight, bottomRight) * calc(paddle, topRight, mouse) > 0) {
			if (hsGoc >= 0) {

				A.x = paddle.x;
				A.y = paddle.y;
				B.x = 0;
				B.y = hsTuDo;
				SDL_RenderDrawLineF(renderer, A.x + paddleSize / 2, A.y - Ball::Instance(renderer)->getRadius(), B.x, B.y);
				//Vẽ tia đối xứng

				hsGoc = -hsGoc;
				A.x = 0;
				A.y = A.x * hsGoc + hsTuDo;
				B.y = 0;
				B.x = (B.y - hsTuDo) / hsGoc;
				SDL_RenderDrawLineF(renderer, A.x, A.y, B.x, B.y);
			}
			//Ngược lại thì tia Ox sẽ là phần phản xạ đường thẳng từ paddle đến con trỏ chuột 
			else
			{
				A.x = paddle.x;
				A.y = paddle.y;
				B.x = width;
				B.y = hsGoc * B.x + hsTuDo;
				SDL_RenderDrawLineF(renderer, A.x + paddleSize / 2, A.y - Ball::Instance(renderer)->getRadius(), B.x, B.y);
				hsGoc = -hsGoc;
				hsTuDo = B.y - B.x * hsGoc;
				A.y = 0;
				A.x = (A.y - hsTuDo) / hsGoc;
				SDL_RenderDrawLineF(renderer, A.x, A.y, B.x, B.y);
			}
		}
		else {
			if (hsGoc >= 0) {
				A.x = paddle.x;
				A.y = paddle.y;
				B.x = -hsTuDo / hsGoc;
				B.y = 0;
				SDL_RenderDrawLineF(renderer, A.x + paddleSize / 2, A.y - Ball::Instance(renderer)->getRadius(), B.x, B.y);
				//Vẽ tia đối xứng
				hsGoc = -hsGoc;
				hsTuDo = B.y - hsGoc * B.x;
				A.x = 0;
				A.y = hsTuDo;
				SDL_RenderDrawLineF(renderer, A.x, A.y, B.x, B.y);
			}
			else
			{
				A.x = paddle.x;
				A.y = paddle.y;
				B.x = -hsTuDo / hsGoc;
				B.y = 0;
				SDL_RenderDrawLineF(renderer, A.x + paddleSize / 2, A.y - Ball::Instance(renderer)->getRadius(), B.x, B.y);
				hsGoc = -hsGoc;
				hsTuDo = B.y - hsGoc * B.x;
				A.x = width;
				A.y = A.x * hsGoc + hsTuDo;
				SDL_RenderDrawLineF(renderer, A.x, A.y, B.x, B.y);
			}

		}
	}

	void draw() {
		heSoGoc = (paddle.y - (float)mouse.y) / (paddle.x + paddleSize / 2 - (float)mouse.x);
		float hsTuDo = mouse.y - heSoGoc * mouse.x;
		draw(heSoGoc, hsTuDo);
	}





};


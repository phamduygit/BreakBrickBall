#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
using namespace std;
class Line
{
private:
	float width;
	float height;
	SDL_FPoint paddle;
	SDL_Point mouse;
	SDL_FPoint target;
	int sizePaddle;
	SDL_Renderer* renderer;
	float heSoGoc;
	float paddleSize;
public:
	Line() {
		sizePaddle = 120;
		width = 500;
		height = 800;
		heSoGoc = 0;
		mouse = { 0, 0 };
		paddle = { 0.0, 0.0 };
		paddleSize = 0;
		renderer = NULL;
		target = { 0.0, 0.0 };
		//heSoGoc;
	}
	float getHeSoGoc() {
		return heSoGoc;

	}
	Line(SDL_Renderer* renderer) {
		sizePaddle = 120;
		paddleSize = 0;
		width = 500;
		height = 800;
		sizePaddle = 120;
		heSoGoc = 0;
		mouse = { 0, 0 };
		paddle = { 0.0, 0.0 };
		renderer = NULL;
		target = { 0.0, 0.0 };
		this->renderer = renderer;
	}

	void setPaddle(float x, float y,float _paddleSize) {
		paddle.x = x;
		paddle.y = y;
		paddleSize = _paddleSize;
	}
	void setMouse(int x, int y) {
		mouse.x = x;
		mouse.y = y;
	}
	
	
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
		if (calc(paddle, topLeft, bottomLeft) * calc(paddle, topLeft, mouse) > 0 || calc(paddle, topRight, bottomRight) * calc(paddle, topRight, mouse) > 0) {
			if (hsGoc >= 0) {

				A.x = paddle.x;
				A.y = paddle.y;
				B.x = 0;
				B.y = hsTuDo;
				SDL_RenderDrawLineF(renderer, A.x + paddleSize/2, A.y, B.x, B.y);
				//Vẽ tia đối xứng
				hsGoc = -hsGoc;
				A.x = 0;
				A.y = A.x * hsGoc + hsTuDo;
				B.y = 0;
				B.x = (B.y - hsTuDo) / hsGoc;
				SDL_RenderDrawLineF(renderer, A.x, A.y, B.x, B.y);
			}
			else
			{
				A.x = paddle.x;
				A.y = paddle.y;
				B.x = width;
				B.y = hsGoc * B.x + hsTuDo;
				SDL_RenderDrawLineF(renderer, A.x + paddleSize/2, A.y, B.x, B.y);
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
				B.x = -hsTuDo/hsGoc;
				B.y = 0;
				SDL_RenderDrawLineF(renderer, A.x + paddleSize/2, A.y, B.x, B.y);
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
				B.x = -hsTuDo/hsGoc;
				B.y = 0;
				SDL_RenderDrawLineF(renderer, A.x + paddleSize/2, A.y, B.x, B.y);
				hsGoc = -hsGoc;
				hsTuDo = B.y - hsGoc * B.x;
				A.x = width;
				A.y = A.x * hsGoc + hsTuDo;
				SDL_RenderDrawLineF(renderer, A.x, A.y, B.x, B.y);
			}

		}
	}

		void draw() {
			heSoGoc = (paddle.y - (float)mouse.y) / (paddle.x + paddleSize/2 - (float)mouse.x);
			float hsTuDo = mouse.y - heSoGoc * mouse.x;
			draw(heSoGoc, hsTuDo);		
		}
	







	
	void render() {

	}




};


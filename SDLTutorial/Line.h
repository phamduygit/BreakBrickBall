#pragma once
#include <SDL.h>
#include <iostream>
using namespace std;
class Line
{
private:
	int width;
	int height;
	SDL_FPoint paddle;
	SDL_Point mouse;
	SDL_FPoint target;
	int sizePaddle;
	SDL_Renderer* renderer;
public:
	Line() {
		sizePaddle = 120;
		width = 500;
		height = 800;
	}
	Line(SDL_Renderer* renderer) {
		sizePaddle = 120;

		width = 500;
		height = 800;
		sizePaddle = 120;
		this->renderer = renderer;
	}

	void setPaddlePoint(double x, double y) {
		paddle.x = x;
		paddle.y = y;
	}
	void setMouse(int x, int y) {
		mouse.x = x;
		mouse.y = y;
	}
	/*float calc(float heSoGoc, float heSoTuDo, SDL_FPoint p) {
		return heSoGoc * p.x + heSoTuDo - p.y;
	}
	float calc(float heSoGoc, float heSoTuDo, SDL_Point p) {
		return heSoGoc * p.x + heSoTuDo - p.y;
	}*/
	float calc(SDL_FPoint a, SDL_FPoint b, SDL_FPoint c) {
		return (c.x - a.x) / (b.x - a.x) - (c.y - a.y) / (b.y - a.y);

	}
	float calc(SDL_FPoint a, SDL_FPoint b, SDL_Point c) {
		return (c.x - a.x) / (b.x - a.x) - (c.y - a.y) / (b.y - a.y);

	}
	float calc(SDL_FPoint a, SDL_Point b, SDL_Point c) {
		return (c.x - a.x) / (b.x - a.x) - (c.y - a.y) / (b.y - a.y);

	}
	void drawLine(float x1, float y1, float x2, float y2) {

	}
	void draw(float hsGoc, float hsTuDo) {
		SDL_FPoint A;
		SDL_FPoint B;
		//cout << hsGoc<<endl;
		SDL_Point topLeft = { 0,0 };
		SDL_Point bottomLeft = { 0,height };
		SDL_Point topRight = { width,0 };
		SDL_Point bottomRight = { width,height };
		SDL_FPoint mouseF = { mouse.x,mouse.y };
		if (calc(paddle, topLeft, bottomLeft) * calc(paddle, topLeft, mouse) > 0 || calc(paddle, topRight, bottomRight) * calc(paddle, topRight, mouse) > 0) {
			if (hsGoc >= 0) {

				A.x = paddle.x;
				A.y = paddle.y;
				B.x = 0;
				B.y = hsTuDo;
				//	SDL_RenderDrawLineF(renderer, 0, 0, 200, 200);
				SDL_RenderDrawLineF(renderer, A.x + 60, A.y, B.x, B.y);
				hsGoc = -hsGoc;
				A.x = 0;
				A.y = A.x * hsGoc + hsTuDo;
				//y= a*x+b
				B.y = 0;
				B.x = (B.y - hsTuDo) / hsGoc;
				SDL_RenderDrawLineF(renderer, A.x, A.y, B.x, B.y);
				cout << "He so goc trai: " << hsGoc << endl;
			}
			else
			{
				A.x = paddle.x;
				A.y = paddle.y;
				B.x = width;
				B.y = hsGoc * B.x + hsTuDo;
				//	SDL_RenderDrawLineF(renderer, 0, 0, 200, 200);
				SDL_RenderDrawLineF(renderer, A.x + 60, A.y, B.x, B.y);
				hsGoc = -hsGoc;
				hsTuDo = B.y - B.x * hsGoc;
				/*	A.x = width;
					A.y = A.x * hsGoc + hsTuDo;*/
				A.y = 0;
				A.x = (A.y - hsTuDo) / hsGoc;
				//	cout << A.y<<endl;

					//y= a*x+b
					/*B.y = 0;
					B.x = (B.y - hsTuDo) / hsGoc;*/
				SDL_RenderDrawLineF(renderer, A.x, A.y, B.x, B.y);
				cout << "Hs goc phai: " << hsGoc << endl;
			}
		}
		else {
			if (hsGoc >= 0) {
				cout << "hs";
				A.x = paddle.x;
				A.y = paddle.y;
				B.x = -hsTuDo/hsGoc;
				B.y = 0;
				//	SDL_RenderDrawLineF(renderer, 0, 0, 200, 200);
				SDL_RenderDrawLineF(renderer, A.x + 60, A.y, B.x, B.y);
				hsGoc = -hsGoc;
				hsTuDo = B.y - hsGoc * B.x;
				A.x = 0;
				A.y = hsTuDo;

				//hsGoc = -hsGoc;
				//A.x = 0;

				//A.y = A.x * hsGoc + hsTuDo;
				////y= a*x+b
				//B.y = 0;
				//B.x = (B.y - hsTuDo) / hsGoc;
				SDL_RenderDrawLineF(renderer, A.x, A.y, B.x, B.y);
				//cout << "He so goc trai: " << hsGoc << endl;
			}
			else
			{
				A.x = paddle.x;
				A.y = paddle.y;
				B.x = -hsTuDo/hsGoc;
				B.y = 0;
				//	SDL_RenderDrawLineF(renderer, 0, 0, 200, 200);
				SDL_RenderDrawLineF(renderer, A.x + 60, A.y, B.x, B.y);
				hsGoc = -hsGoc;
				hsTuDo = B.y - hsGoc * B.x;
				A.x = width;
				A.y = A.x * hsGoc + hsTuDo;
				//hsGoc = -hsGoc;
				//hsTuDo = B.y - B.x * hsGoc;
				///*	A.x = width;
				//	A.y = A.x * hsGoc + hsTuDo;*/
				//A.y = 0;
				//A.x = (A.y - hsTuDo) / hsGoc;
				////	cout << A.y<<endl;

				//	//y= a*x+b
				//	/*B.y = 0;
				//	B.x = (B.y - hsTuDo) / hsGoc;*/
				SDL_RenderDrawLineF(renderer, A.x, A.y, B.x, B.y);
				//cout << "Hs goc phai: " << hsGoc << endl;
			}

		}
	}

		void draw() {
			SDL_FPoint bottomLeft;
			bottomLeft.x = 0;
			bottomLeft.y = height;
			SDL_FPoint topLeft;
			SDL_FPoint topRight;
			SDL_FPoint bottomRight;
			bottomRight.x = width;
			bottomRight.y = height;
			topRight.x = width;
			topRight.y = 0;
			topLeft.x = 0;
			topLeft.y = 0;

			float hesoGoc = (paddle.y - (float)mouse.y) / (paddle.x + 60 - (float)mouse.x);
			float hsTuDo = mouse.y - hesoGoc * mouse.x;

			draw(hesoGoc, hsTuDo);
			//if (haiDiemNamCungPhiaDuongThang(paddle, topLeft, mouse, bottomLeft)) {
			//draw(-hesoGoc, hsTuDo);
			/*}
			if (haiDiemNamCungPhiaDuongThang(paddle, topRight, mouse, bottomRight)) {

			}*/
		}
	







	
	void render() {

		//	SDL_RenderDrawLines()

	}




};


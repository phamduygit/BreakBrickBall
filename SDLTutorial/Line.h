#pragma once
#include "Point2D.h"
#include <SDL.h>

class Line
{
private:
	int width;
	int height;
	SDL_FPoint paddle;
	SDL_FPoint mouse;
	SDL_FPoint target;
public:
	Line() {
		width = 500;
		height = 800;
	}
	
	void setPaddlePoint(SDL_FPoint& p) {
		paddle = p;
	}
	void setPaddlePoint(double x, double y) {
		paddle.x = x;
		paddle.y = y;

	}
	double calcLine(SDL_FPoint a, SDL_FPoint b, SDL_FPoint c) {
		
		return (c.x - a.x) / (b.x - a.x) - (c.y - a.y) / (b.y - a.y);
	}
	bool haiDiemNamCungPhiaDuongThang(SDL_FPoint a,SDL_FPoint b,SDL_FPoint c,SDL_FPoint d) {
		if (calcLine(a, b, c) * calcLine(a, b, d) > 0) {
			return true;

		}
		return false;
		
		

	}
	void updateLine() {
		SDL_FPoint bottomLeft;
		bottomLeft.x = 0;
		bottomLeft.y = height;
		SDL_FPoint topLeft;
		topLeft.x = 0;
		topLeft.y = 0;
		if (haiDiemNamCungPhiaDuongThang(paddle, topLeft, mouse, bottomLeft)) {

		}
		




		

	}
	void render() {

	//	SDL_RenderDrawLines()

	}

	
	

};


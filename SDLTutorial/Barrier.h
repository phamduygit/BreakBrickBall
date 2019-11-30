#pragma once
#include "Paddle.h"
class Barrier:public Paddle
{
private:
	int deltaX;
public:
	Barrier(){}
	Barrier(SDL_Renderer*&,int ,int );
	void move() {
		
		cout << x << endl;
		if (x +w> 500||x<0) {
			deltaX = -deltaX;
		}
		this->x += deltaX;
	}


};


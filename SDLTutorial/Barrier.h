#pragma once
#include "Paddle.h"
class Barrier:public Paddle
{
private:
	float deltaX;
public:
	Barrier(){
		deltaX = 0;
	}
	Barrier(SDL_Renderer*&,float ,float );
	void move() {
	
		if (x +width> 500||x<0) {
			deltaX = -deltaX;
		}
		this->x += deltaX;
	}


};


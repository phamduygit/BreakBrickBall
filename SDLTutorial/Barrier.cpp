#include "Barrier.h"

Barrier::Barrier(SDL_Renderer*& renderer,int x,int y):Paddle(renderer)
{
	this->x = x;
	this->y = y;
	deltaX = 1;
}

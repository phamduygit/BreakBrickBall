#include "Barrier.h"

Barrier::Barrier(SDL_Renderer*& renderer,float x,float y):Paddle(renderer)
{
	this->x = x;
	this->y = y;
	deltaX = 1;
}

#include "Ball.h"

Ball::Ball() {
	x = 0;
	y = 0;
	radius = 0;
	speed = 0;
	image = NULL;
	renderer = NULL;
}

Ball::~Ball() {
	SDL_DestroyTexture(image);
}

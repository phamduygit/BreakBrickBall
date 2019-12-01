#include "MagicBall.h"
Ball* Ball::instance = NULL;
Ball::Ball() {
	x = 0;
	y = 0;
	radius = 0;
	speed = 0;
	image = NULL;
	renderer = NULL;
	degree = 0;
	isLaunch = false;
}

Ball::~Ball() {
	SDL_DestroyTexture(image);
}


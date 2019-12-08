#include "MagicBall.h"
Ball* Ball::instance = NULL;
Ball::Ball() {
	_x = 0;
	_y = 0;
	_radius = 0;
	_speed = 0;
	_image = NULL;
	_renderer = NULL;
}

Ball::~Ball() {
	SDL_DestroyTexture(_image);
}

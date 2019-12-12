#include "MagicBall.h"
MagicBall* MagicBall::instance = NULL;
MagicBall::MagicBall() {
	_x = 0;
	_y = 0;
	_radius = 0;
	_speed = 0;
	_image = NULL;
	_renderer = NULL;
}

MagicBall::~MagicBall() {
	SDL_DestroyTexture(_image);
}

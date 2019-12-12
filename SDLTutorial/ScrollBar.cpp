#include "ScrollBar.h"

ScrollBar::ScrollBar()
{
	vx = WIDTH_SCROLL_BAR / 5;;
}

void ScrollBar::HandleInputAction(SDL_Event events)
{
	if (events.type == SDL_KEYDOWN)
	{
		if (events.key.keysym.sym == SDLK_LEFT)
		{
			this->HandleMove(-vx);
			//TODO
		}
		else if (events.key.keysym.sym == SDLK_RIGHT)
		{
			this->HandleMove(vx);
			//TODO
		}
	}
}
void ScrollBar::HandleInputAct(SDL_Event events)
{
	if (events.type == SDL_KEYDOWN)
	{
		if (events.key.keysym.sym == SDLK_z)
		{
			this->HandleMove(-vx);
		}
		else if (events.key.keysym.sym == SDLK_c)
		{
			this->HandleMove(vx);
		}
	}
}
void ScrollBar::HandleMove(int vx)
{
	float x = rect.X() + vx;
	if (x < HORIZONTAL_MARGIN)
	{
		rect.Set_X(HORIZONTAL_MARGIN);

	}
	else if (x > SCREEN_WIDTH - (WIDTH_SCROLL_BAR + HORIZONTAL_MARGIN))
	{
		rect.Set_X(SCREEN_WIDTH - (WIDTH_SCROLL_BAR + HORIZONTAL_MARGIN));
	}
	else
		rect.Set_X(x);
}
void ScrollBar::AutoMove(float x_ball)
{
	float x = x_ball - WIDTH_SCROLL_BAR / 2;
	if (x < HORIZONTAL_MARGIN)
	{
		rect.Set_X(HORIZONTAL_MARGIN);

	}
	else if (x > SCREEN_WIDTH - (WIDTH_SCROLL_BAR + HORIZONTAL_MARGIN))
	{
		rect.Set_X(SCREEN_WIDTH - (WIDTH_SCROLL_BAR + HORIZONTAL_MARGIN));
	}
	else
		rect.Set_X(x);
}
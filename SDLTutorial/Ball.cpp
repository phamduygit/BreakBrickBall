#include "Ball.h"
#include<math.h>
#include "function.h"

Ball::Ball()
{
	/*srand(time(NULL));
	goc = minN + rand() / RAND_MAX * (maxN - minN);*/
	trigonometric_angle = pi / 6;
	v =	2;
	vx = v * cos(trigonometric_angle);
	vy = v * sin(trigonometric_angle);
}
void Ball::HandleMove(Point2D& top_left, Point2D& bottom_left)
{
	int max;
	float x, y;
	if (abs(vx) > abs(vy))
		max = abs(vx);
	else
		max = abs(vy);
	for (int i = 0; i <= max/2; i++)
	{
		x = rect.X() + 2*vx / max;
		y = rect.Y() + 2*vy / max;
		if (x <= HORIZONTAL_MARGIN)
		{
			rect.Set_X(HORIZONTAL_MARGIN);
			this->HandleBorderColision();
			break;
		}
		else if (x >= SCREEN_WIDTH - HORIZONTAL_MARGIN - WIDTH_BALL)
		{
			rect.Set_X(SCREEN_WIDTH - HORIZONTAL_MARGIN - WIDTH_BALL);
			this->HandleBorderColision(); 
			break;
		}
		else
		{
			rect.Set_X(x);
		}
		if (y <= top_left.Y() + HEIGHT_SCROLL_BAR)
		{
			if (x >= top_left.X() && x <= (top_left.X() + WIDTH_SCROLL_BAR))
			{
				rect.Set_Y(top_left.Y() + HEIGHT_SCROLL_BAR);
				this->HandleScrollBarCollision();
			}
			else if (y <= VERTICAL_MARGIN)
			{
				vx = 0;
				vy = 0;
				rect.Set_Y(VERTICAL_MARGIN);
			}
			else
				rect.Set_Y(y);
			break;
		}
		else if (y >= bottom_left.Y() - HEIGHT_BALL)
		{
			if (x >= bottom_left.X() && x <= (bottom_left.X() + WIDTH_SCROLL_BAR))
			{
				rect.Set_Y(bottom_left.Y() - HEIGHT_BALL);
				this->HandleScrollBarCollision();
			}
			else if (y >= SCREEN_HEIGHT - VERTICAL_MARGIN - HEIGHT_BALL)
			{
				vx = 0;
				vy = 0;
				rect.Set_Y(SCREEN_HEIGHT - HEIGHT_BALL - VERTICAL_MARGIN);
			}
			else
				rect.Set_Y(y);
			break;
		}
		else
			rect.Set_Y(y);

	}
	
}
void Ball::HandleBorderColision()
{
	trigonometric_angle = pi - trigonometric_angle;
	v *= 1.1;
	vx = v * cos(trigonometric_angle);
	vy = v * sin(trigonometric_angle);
}
void Ball::HandleScrollBarCollision()
{
	trigonometric_angle = -trigonometric_angle;
	v *= 1.1;
	vx = v * cos(trigonometric_angle);
	vy = v * sin(trigonometric_angle);
}
int Ball::Collision()
{
	if (rect.Y() <= VERTICAL_MARGIN)
	{
		return 1;
	}
	if (rect.Y() >= SCREEN_HEIGHT - VERTICAL_MARGIN - HEIGHT_BALL)
	{
		return 2;
	}
	return 0;
}
#ifndef BALL_H
#define BALL_H
#include"BaseObject.h"
//#include"ScrollBar.h"
#include <cstdlib>
#include<time.h>
#include<iostream>
using namespace std;

class Ball :public BaseObject
{
protected:
	float v;
	float vx, vy;
	float trigonometric_angle;

public:
	Ball();
	virtual void HandleMove(Point2D& top_left, Point2D& bottom_left);
	virtual void HandleBorderColision();
	virtual void HandleScrollBarCollision();
	virtual int Collision();
	virtual ~Ball(){}
};
#endif

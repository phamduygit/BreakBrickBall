#pragma once
#include <cmath>
#include <SDL.h>
class Point2D
{
private:
	double _x;
	double _y;
public:
	Point2D(){
	
		_x = 0;
		_y = 0;
	}
	Point2D(const SDL_FPoint& p) {
		_x = p.x;
		_y = p.y;
	}
	Point2D operator =(const SDL_FPoint& p) {
		_x = p.x;
		_y = p.y;
		return *this;
	}

	Point2D(double x, double y) {
		_x = x;
		_y = y;
	}
	double getX() {
		return _x;
	}
	double getY() {
		return _y;
	}
	friend Point2D operator +(const Point2D& a, const Point2D& b) {
		return Point2D(a._x + b._x, a._y + b._y);
	}
	friend Point2D operator - (const Point2D& a, const Point2D& b){
		return Point2D(a._x - b._x, a._y - b._y);
	}
	friend Point2D operator * (const Point2D& a, const double x) {
		return  Point2D(a._x * x, a._y * x);
	}
	double Distance(const Point2D& a, const Point2D& b) {
		Point2D result;
		double deltaX = a._x - b._x;
		double deltaY = a._y - b._y;
		return sqrt(deltaX * deltaX + deltaY * deltaY);
	}


};


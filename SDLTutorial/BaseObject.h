#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include"function.h"
#include"Point2D.h"

using namespace std;
const int WIDTH_BALL = 20;
const int HEIGHT_BALL = 20;
const int WIDTH_SCROLL_BAR = 100;
const int HEIGHT_SCROLL_BAR = 11;
const float pi = 3.14;
const float minN = 0;
const float maxN = pi;
class BaseObject
{
protected:
	SDL_Surface* object;
	Point2D rect;
public:
	BaseObject();
	~BaseObject();
	void SetRect(float x, float y) {
		rect.Set_X(x);
		rect.Set_Y(y);
	}
	Point2D& Rect() { return rect; }
	SDL_Surface* Object() { return object; }
public:
	void LoadImg(string);
	void Show(SDL_Surface*);
};
#endif // !BASEOBJECT_H




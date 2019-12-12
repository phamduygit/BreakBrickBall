#ifndef SCROLLBAR_H
#define SCROLLBAR_H
#include"BaseObject.h"


class ScrollBar :public BaseObject
{
protected:
	float vx;
public:
	ScrollBar();
	//~ScrollBar();
public:
	virtual void HandleInputAct(SDL_Event event);
	virtual void HandleInputAction(SDL_Event event);
	virtual void HandleMove(int x);
	virtual void AutoMove(float x);
};

#endif
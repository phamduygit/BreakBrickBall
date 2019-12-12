#ifndef POINT2D_H
#define POINT2D_H
class Point2D
{
private:
	float x;
	float y;
public:
	Point2D();
public:
	void Set_X(float value) { x = value; }
	float X() { return x; }
	void Set_Y(float value) { y = value; }
	float Y() { return y; }
};

#endif
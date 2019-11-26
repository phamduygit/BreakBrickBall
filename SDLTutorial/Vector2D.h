#pragma once
#include <cmath>
class Vector2D
{
public:
	Vector2D(){}
	Vector2D(float x, float y) {
		_x = x;
		_y = y;


	}
	float getX() {
		return _x;
	}
	float getY() {
		return _y;
	}
	void setX(float val) {
		_x = val;
	}
	void setY(float val) {
		_y = val;
	}
	float length() {
		return sqrt(_x * _x - _y * _y);
	}
	 Vector2D operator+(const Vector2D& v2) {
		return Vector2D(_x + v2._x, _y + v2._y);
	}
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2) {
		v1._x += v2._x;
		v1._y += v2._y;
		return v1;
	}
	Vector2D operator*(float number) {
		return Vector2D(_x * number, _y *number);

	}
	Vector2D& operator *=(float number) {
		_x *= number;
		_y *= number;
		return *this;
	}
	Vector2D operator-(const Vector2D& v2) const {
		return Vector2D(_x - v2._x, _y - v2._y);


	}
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2) {
		v1._x -= v2._x;
		v1._y -= v2._y;
		return v1;
	}
	Vector2D operator/(float scalar) {
		return Vector2D(_x / scalar, _y / scalar);

	}
	Vector2D& operator/=(float scalar) {
		_x /= scalar;
		_y /= scalar;
		return *this;

	}
	void normalize() {
		float leng = this->length();
		if (leng > 0) {
			*this *= 1 / leng;
		}

	}
private:
	int _x;
	int _y;

};


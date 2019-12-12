#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Functions.h"
#include <string>
#include "SettingScreen.h"
#include "ScrollBar.h"
using namespace std;
//Đối tượng paddle
class Paddle:public ScrollBar
{
protected:
	//Tọa độ của đối tượng
	float _x;
	float _y;
	//Kích thước của đối tượng
	float _width;
	float _height;
	//Độ dịch chuyển theo phương ox
	//Nếu khoảng thời gian tương đối ngắn thì có thể xem đó là vận tốc paddle
	float _deltaX;
	//Tọa độ lúc trước của paddle
	float _previousX;
	//Hình ảnh của paddle
	SDL_Texture* _image;
	//Biến lưu giữ các thông số sẽ render lên màn hình game
	SDL_Renderer* _renderer;
	//Thể hiện của paddle
	static Paddle* _instance;
	//Hàm khởi tạo không đối số
	Paddle():ScrollBar() {
		_x = 150;
		_y = 700;
		_width = 80;
		_height = 10;
		//_speed = 5;
		_image = NULL;
		this->_renderer = NULL;
		_deltaX = 0;
		_previousX = 0;

	}
	//Hàm khởi tạo có đối số
	Paddle(SDL_Renderer*& RenderValue):ScrollBar() {
		_x = 150;
		_y = 750;
		_width = 150;
		_height = 20;
		//_speed = 5;
		_image = NULL;
		this->_renderer = RenderValue;

		_deltaX = 0;
		_previousX = 0;

	}
public:
	//Phương thức lấy ra thể hiện của một singleton
	 static Paddle* Instance(SDL_Renderer*& value) {
		if (_instance == NULL) {
			_instance = new  Paddle(value);

		}
		return _instance;
	}
	//Lấy ra chiều cao của paddle
	float getHeight() {
		return _height;
	}
	//Lấy chiều rộng của paddle
	float getWidth() {
		return _width;
	}
	//Thiết lập chiều rộng cho paddle
	void setWidth(float newwidth) {
		this->_width = newwidth;
	}
	//Lấy ra tọa độ x của paddle
	float getX() {
		return _x;
	}
	//Thiết lập tọa độ x cho đối tượng
	void setX(float value) {
		_x = value;
	}
	//Lấy ra tọa độ y của đối tượng
	float getY() {
		return _y;
	}
	//Thiết lập tọa độ y cho đối tượng
	void setY(float value) {
		_y = value;
	}
	//Thiết lập speed cho đối tượng
	virtual void setSpeed(float value) {
		vx = value;
	}
	//Lấy ra speed của đối tượng
	float getSpeed() {
		return vx;
	}
	//Cài đặt hình ảnh cho đối tượng
	void setImage(string name) {
		_image = loadImage(name, _renderer);
	}
	//Vẽ đối tượng lên mặt phẳng chơi game
	void draw() {
		
		DrawInRenderer(_renderer, _image, _x, _y, _width, _height);

	}
	//Hàm di chuyển paddle
	// trong đó nhận vao đối số là chơi bằng chuột
	//hoặc là mảng gồm 2 trạng thái nhấn nút và thả nút a và d khi người chơi bằng bàn phím
	//Và chế độ máy tự chơi nhận vào thông tin của quả bóng
	void move(float xMouse, bool moveLR[], float xBall, SettingAction setting) {
		_previousX = _x;
		if (setting == autoPlay) {
			if (xBall - _width / 2 >= 0 &&
				xBall + _width / 2 <= 500) {				
					_x = xBall - _width / 2;				
			}

		}
		else if (setting == playWithMouse) {
			xMouse = xMouse - _width / 2;
			if (xMouse < 0) {
				this->_x = 0;
			}
			else if (xMouse + _width > 500) {
				this->_x = 500 - _width;

			}
			else {
				_x = xMouse;
			}
			_deltaX = _x - _previousX;
		}
		else if (setting == playWithKeyboard) {
			if (moveLR[0]) {
				if (_x > 0) {
					_x -= vx;
				}
			}

			if (moveLR[1]) {
				if (_x + _width < 500) {
					_x += vx;
				}
			}

		}
		_deltaX = _x - _previousX;
	}
	//Lấy ra độ dời của paddle so với vị trí trước theo phương ox
	float getDeltaX() {
		return _deltaX;
	}
	//Khôi phục lại deltaX
	void resetDeltaX() {
		_deltaX = 0;
	}

};


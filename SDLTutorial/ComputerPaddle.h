#pragma once
#include "Paddle.h"
#include "MagicBall.h"
#include "TextureManager.h"
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
class ComputerPaddle
{
private:
	int _x;
	int _y;
	//Kích thước của đối tượng
	float _width;
	float _height;
	//Tốc độ của paddle
	int _speed;
	//Biến lưu giữ các thông số sẽ render lên màn hình game
	SDL_Renderer* _renderer;
	int _currentFrame;
	bool isEnable;
	int startTime;
public:
	///Thiết lập tọa độ x cho paddle
	void setX(float value) {
		_x = value;
	}
	//Thiết lập tọa đô y cho paddle
	void setY(float value) {
		_y = value;
	}
	//Hàm khởi tọa không đối số
	ComputerPaddle() {
		_x = -300;
		_y = 0;
		_width = 188;
		_height = 20;
		_currentFrame = 1;
		_speed = 2;
		isEnable = true;
	}
	//Hàm khởi tạo có đối số
	ComputerPaddle(SDL_Renderer* renderer, int x, int y) {
		this->_renderer = renderer;
		this->_x = x;
		this->_y = y;
		_width = 188;
		_height = 20;
		_currentFrame = 1;
		_speed = 2;
		isEnable = true;
	}
	//vô hiệu hóa paddle
	void disable() {
		isEnable = false;
	}
	//Kích hoạt paddle
	void enable() {
		isEnable = true;
		startTime = clock();
	}
	int getTime() {
		return (int)clock() - startTime;
	}
	//Kiểm tra xem có sự giao nhau không 
	//sử dụng trong sử lí va chạm
	bool intersectionLineAndCircle(float xS, float yS, float xE, float yE) {
		//Tọa độ của quả bóng hiện tại
		float xBall = MagicBall::Instance(_renderer)->getX();
		float yBall = MagicBall::Instance(_renderer)->getY();
		//Bán kính quả bóng
		float radius = MagicBall::Instance(_renderer)->getRadius();
		//Delta x giữa điểm bắt đầu và điểm kết thúc của một đoạn thẳng
		float dx = xE - xS;
		//Delta y giữa điểm bắt đầu và kết thức của một đoạn thẳng
		float dy = yE - yS;
		// Thay vào công thức tính khoảng cách giữa đoạn thẳng và một điểm ta có 
		//ta được phương trình a*x^2+b*x+c <=r^2
		float a = dx * dx + dy * dy;
		float b = 2 * (xS * dx - xBall * dx + yS * dy - yBall * dy);
		float c = xS * xS + xBall * xBall + yS * yS + yBall * yBall - 2 *
			(xS * xBall + yS * yBall) - radius * radius;
		float delta = b * b - 4 * a * c;
		if (delta >= 0) {
			float x1 = (-b + sqrt(delta)) / (2 * a);
			float x2 = (-b - sqrt(delta)) / (2 * a);
			if ((x1 >= 0 && x1 <= 1) || (x2 >= 0 && x2 <= 1)) {
				return true;
			}
		}
		return false;
	}
	//Thiết lập thuộc tính render cho đối tượng
	void setRenderer(SDL_Renderer*& value) {
		this->_renderer = value;
	}
	//xử lí va chạm
	void handleCollision() {
		if (isEnable) {
			MagicBall* ball = MagicBall::Instance(_renderer);
			//Kiểm tra khi bóng bay từ bên trái sang và có va chạm
			if (_currentFrame == 1 && ball->isCollision(_x, _y, _width, _height) && _currentFrame >= 1 && _currentFrame <= 100) {
				if (ball->getX() + ball->getRadius() > _x&&
					ball->getX() < _x&&
					intersectionLineAndCircle(_x, _y, _x, _y + _height)
					) { 
					float offset = abs(ball->getX() + ball->getRadius() - _x);
					ball->setX(ball->getX() - float(1.1) * offset);
					ball->setDegree(180 - ball->getDegree());


				}
				//Kiểm tra bóng bay từ bên trên xuống và có va chạm
				else if (ball->getY() + ball->getRadius() > _y&&
					ball->getY() < _y&& intersectionLineAndCircle(_x, _y, _x + _width, _y)

					) {
					float offset = abs(ball->getY() + ball->getRadius() - _y);
					ball->setY(ball->getY() - float(1.1) * offset);
					ball->setDegree(-ball->getDegree());

				}
				//Kiểm tra bóng bay từ bên phải sang và có va chạm
				else if (ball->getX() - ball->getRadius() < _x + _width &&
					ball->getX() > _x + _width &&
					intersectionLineAndCircle(_x + _width, _y, _x + _width, _y + _height)) {//Bong ben  phai
					float offset = abs(ball->getX() - ball->getRadius() - _x - _width);
					ball->setX(ball->getX() + float(1.1) * offset);
					ball->setDegree(180 - ball->getDegree());

				}
				//Kiểm tra bóng bay từ bên dưới và có sự va chạm với paddle
				else if (ball->getY() - ball->getRadius() <= _y + _height &&
					ball->getY() > _y + _height &&
					intersectionLineAndCircle(_x, _y + _height, _x + _width, _y + _height)) {
					float offset = abs(ball->getY() - ball->getRadius() - _y);
					ball->setY(ball->getY() + float(1.1) * offset);
					ball->setDegree(-ball->getDegree());

				}
			}
		}
	}
	//Thiết lập tốc độ di chuyển cho paddle
	void setSpeed(float value) {
		_speed = value;
	}
	//Hàm vẽ đối tượng lên màn hình game
	void draw() {
		if (isEnable) {
			TextureManager::GetInstance()->drawFrame("ComputerPaddle", _x, _y, _width, _height, 1, _currentFrame, _renderer);
		}
		if (getTime() <= 10000) {
			_currentFrame = 1;
		}
		else {
			_currentFrame = 2;
		}
		if (getTime() >= 20000) {
			startTime = clock();
		}
	}
	//Hàm di chuyển
	//cập nhật lại tọa độ của đối tượng sau mỗi vòng lập
	void move() {
		if (isEnable) {
			_x += _speed;

			if (_x <= 0) {
				_speed = abs(_speed);
			}
			else if (_x + _width >= 500) {
				_speed = -abs(_speed);

			}
		}
		
		
	}
	//Load dữ liệu từ file map
	void load(string fileName) {
		fstream file(fileName, ios::in);
		if (!file) {
			cout << "\nKhong tim  dc file";
			return;

		}
		bool found = false;
		
		vector <int> map;
		while (!file.eof()) {
			string buff;
			getline(file, buff);
			if (buff == "") {
				break;
			}
			stringstream source(buff);
			string dat;
			while (getline(source, dat, ' ')) {
				map.push_back(stoi(dat));
			}		
		}
		for (int k = 0; k < map.size(); k++) {
			if (map[k] == 9) {
				found = true;
				int i = k % 10;
				int j = k/10;
				_x = i * 50;
				_y = (j + 1) * 50;
			}
		}
		if (found) {
			enable();
		}
		else {
			disable();
		}
	}
	//Chuyển đổi dữ liệu thành dạng chuỗi để lưu trữ trạng thái sau khi thoát game
	string toString() {
		stringstream out;
		out << _x << " " << int(_y) << " " << int(_speed)<< " "<<isEnable;
		return out.str();
	}

};


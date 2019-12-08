#pragma once
#include <SDL.h>
#include <string>
#include "Functions.h"
#include "TextureManager.h"
#include "MagicBall.h"
#include <string>
#include <sstream>

using namespace std;

class Brick
{
protected: 
	//x y là vị trí sẽ render đối tượng lên màn hình game
	int _x;
	int _y;
	//Kích thước của vật thể 
	//ở đây ta dùng size do gạch là một hình vuông
	float _size;
	SDL_Renderer* _renderer;
	//Khung hiện tại của gạch trên ảnh có kích thước 150x50
	//Trong đó ứng với một khung có width 50 thì ta có một trạng thái của gạch
	int _currentFrame;
	int _currentRow;
	bool _isFinal;
public:
	//Xuất ra những thuộc tính cần thiết của gạch để save game
	virtual string toString() {
		stringstream out;
		out << _x << " " << _y << " " << _currentFrame;
		return out.str();

	}

	//Hàm khỏi tạo mặc định cho gạch
	Brick() {
		_x = 100;
		_y = 100;
		_size = 50;
		_renderer = NULL;
		_currentRow = 1;
		_currentFrame = 4;
	}
	//Khỏi tạo gạch với đối số là con trỏ renderer
	Brick(SDL_Renderer*& renderer) {
		
		_x = 370;
		_y = 50;
		_size =50 ;
		this->_renderer = renderer;
		_currentRow = 1;
		_currentFrame = 1;
	}
	Brick(SDL_Renderer*& renderer,int x,int y) {

		_x = x;
		_y = y;
		_size = 50;
	//	image = NULL;
		this->_renderer = renderer;
		_currentRow = 1;
		_currentFrame = 1;
	}
	//Lấy ra vị trí x của đối tượng
	virtual int getX() {
		return _x;
	}
	//Cài đặt vị trí x của đối tượng
	virtual void setX(int xValue) {
		_x = xValue;
	}
	//Lấy ra vị trí y của đối tượng
	virtual int getY() {
		return _y;
	}
	//Cài đặt vị trí y của đối tượng
	virtual void setY(int yValue) {
		_y = yValue;
	}
	//Lấy ra kích thước của gạch
	virtual float getSize() {
		return _size;
	}
	//Cài đặt size cho gạch
	virtual void setSize(float sizeValue) {
		_size = sizeValue;
	}
	//Cài đặt khung ảnh cho gạch
	virtual void setFrame(int val) {

		_currentFrame = val;
	}
	//Lấy ra thông tin cụ thể cho khung gạch
	virtual int getFrame() {
		return _currentFrame;
	}	
	//Vẽ gạch lên màn hình game
	virtual void draw(bool isFinalBrick = false) {
		if (!isFinalBrick) {
			TextureManager::GetInstance()->drawFrame("Brick", float(_x), float(_y), _size, _size, 1, _currentFrame, _renderer);
		}
		else {
			TextureManager::GetInstance()->drawFrame("FinalBrick", float(_x), float(_y), _size, _size, 1, _currentFrame, _renderer);
		}
	}
	//Hàm hủy cho đối tượng gạch
	virtual ~Brick() {
		//Error
		//SDL_DestroyRenderer(_renderer);

	}

};


#pragma once
#include "Brick.h"
#include "MagicBall.h"
enum TypeAmulet {
	//Nhân hai điểm 
	Double = 2,
	//Bùa nam châm
	Magnet = 3,
	//Tăng kích thước paddle
	IncreasePaddle = 4,
	//Tăng kích thước của bóng
	IncreaseSizeBall = 5,
	//Giảm tỉ lệ điểm xuống một nửa
	HalveScore = 6,
	//Giảm tốc độ bóng
	DecreaseSpeedBall =7,
	//Tăng mạng
	IncreaseLife = 8,
	//9 là vật cản
	//Hố đén 
	//Khi quả bóng người chơi lọt vào hố đen thì 
	//sẽ bay ra ở hố trắng
	BlackHole = 10,
	//Hố trắng là nơi mà trái banh sẽ bay ra 
	WhiteHole = 11


};

class Amulet:public Brick
{
private:
	//Thời gian bắt đầu cho hiệu ứng của bùa
	int _startTime;
	//Loại amulet
	TypeAmulet _typeAmulet;
	int _MAXTIME = 6000;
public:
	//Khỏi tạo thời gian bắt đầu bằng 0
	Amulet() { _startTime = 0; }
	//Hàm khởi tạo cho amulet nhận các tham số
	//x, y là vị trí của bùa trên hệ trục tọa độ đề các
	Amulet(SDL_Renderer* &value, int x, int y,TypeAmulet typeAmulet) :Brick(value, x, y) {
		//currentFrame là khung hình hiện tại trong file png 
		// Do trong cấu trúc file gạch kí hiệu là 1
		// Do đó bùa ta sẽ tính từ 2 đến 8
		// 9 là vật cản
		//10 là hố đen
		//11 là hố trắng
		if (_typeAmulet != BlackHole && _typeAmulet != WhiteHole) {
			this->_currentFrame = typeAmulet - 1;
		}
		else {
			this->_currentFrame = 1;
		}	

		this->_typeAmulet = typeAmulet;
		//Sét mốc thời gian lúc đầu bằng 0
		_startTime = 0;
	}
	//Hàm để xuất dữ liệu dạng string theo cấu trúc x y loại bùa
	//Trong đó loại bùa được ép về kiểu số nguyên
	string toString() {
		stringstream out;
		out << _x << " " << _y << " " << int(_typeAmulet);
		return out.str();
	}
	//Đặt thời gian lớn nhất mà vật phẩm có thể có hiệu ứng
	void setMaxTime(int value) {
		_MAXTIME = value;
	}
	//Lấy ra thời gian lớn nhất mà hiệu ứng có thể có 
	//tác dụng đối với các vật phẩm của người chơi
	int getMaxTime() {
		return _MAXTIME;
	}
	//Bấm giờ thời điểm bắt đầu hiệu ứng
	void setStartTime(int value) {
		_startTime = value;
	}
	//Lấy ra loại bùa
	TypeAmulet getType() {
		return _typeAmulet;
	}
	//Vẽ bùa lên màn hình
	void draw(bool finalMap = false) {
		//Nếu bùa không phải là hố đen và hố trắng thì vẽ theo khung trên sprite sheet
		if (_typeAmulet != BlackHole && _typeAmulet != WhiteHole) {
			TextureManager::GetInstance()->drawFrame("Amulet", float(_x), float(_y), float(_size), float(_size), 1, _currentFrame, _renderer);
		}
		//ngược lại nếu bùa là hố đen thì vẽ theo khung hình riêng tính từ 1 đến 120 
		else if (_typeAmulet == BlackHole) {
			TextureManager::GetInstance()->drawFrame("BlackHole", float(_x), float(_y), float(_size), float(_size), 1, _currentFrame, _renderer);
			_currentFrame = (_currentFrame + 1) % 121;
			if (_currentFrame == 0) {
				_currentFrame = 1;
			}
		}
		//nếu là hố trắng thì vẽ tương tự hố đen khung hình chạy từ 1 đến 120
		else if (_typeAmulet == WhiteHole) {
			TextureManager::GetInstance()->drawFrame("WhiteHole", float(_x), float(_y), float(_size), float(_size), 1, _currentFrame, _renderer);
			_currentFrame = (_currentFrame + 1) % 121;
			if (_currentFrame == 0) {
				_currentFrame = 1;
			}

		}
	}
};


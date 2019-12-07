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
	IncreaseLife = 8

};

class Amulet:public Brick
{
private:
	//Thời gian bắt đầu cho hiệu ứng của bùa
	int startTime;
	//Loại amulet
	TypeAmulet typeAmulet;
	int MAXTIME = 10000;
public:
	//Khỏi tạo thời gian bắt đầu bằng 0
	Amulet() { startTime = 0; }
	//Hàm khởi tạo cho amulet nhận các tham số
	//x, y là vị trí của bùa trên hệ trục tọa độ đề các
	Amulet(SDL_Renderer* &renderer, int x, int y,TypeAmulet typeAmulet) :Brick(renderer, x, y) {
		//currentFrame là khung hình hiện tại trong file png 
		// Do trong cấu trúc file gạch kí hiệu là 1
		// Do đó bùa ta sẽ tính từ 2 đến 7

		this->_currentFrame = typeAmulet - 1;

		this->typeAmulet = typeAmulet;
		//Sét mốc thời gian lúc đầu bằng 0
		startTime = 0;
	}
	//Hàm để xuất dữ liệu dạng string theo cấu trúc x y loại bùa
	//Trong đó loại bùa được ép về kiểu số nguyên
	string toString() {
		stringstream out;
		out << _x << " " << _y << " " << int(typeAmulet);
		return out.str();
	}
	//Đặt thời gian lớn nhất mà vật phẩm có thể có hiệu ứng
	void setMaxTime(int value) {
		MAXTIME = value;
	}
	//Lấy ra thời gian lớn nhất mà hiệu ứng có thể có 
	//tác dụng đối với các vật phẩm của người chơi
	int getMaxTime() {
		return MAXTIME;
	}
	//Bấm giờ thời điểm bắt đầu hiệu ứng
	void setStartTime(int value) {
		startTime = value;
	}
	//Lấy ra loại bùa
	TypeAmulet getType() {
		return typeAmulet;
	}
	//Vẽ bùa lên màn hình
	void draw() {
		TextureManager::GetInstance()->drawFrame("Amulet", float(_x), float(_y), float(_size), float(_size), 1, _currentFrame, _renderer);
	}
};


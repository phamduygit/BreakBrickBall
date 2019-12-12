#pragma once
#include "Brick.h"
#include <vector>
#include "MagicBall.h"
#include <string>
#include <sstream>
#include "Player.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class ListBrick
{
private:
	//Mạng chứa thông tin của những viên gạch sẽ render lên màn hình chơi game
	vector<Brick> _list;
	//Struct renderer của thư viện lưu giữ các thông tin sẽ render lên màn hình chơi game
	SDL_Renderer* _renderer;
	//Trạng thái bật tắt nhạc
	bool _isMusicOn;

public:
	//Hàm khởi tạo không đối số của đối tượng
	ListBrick() {
		_renderer = NULL;
		_isMusicOn = true;
	}
	//Xuất ra dạng chuỗi thông tin của mảng brick khi người chơi thoát sẽ lưu vào file
	//khi người chơi bật lại game thì có thể chơi lại
	string toString() {
		stringstream out;
		for (auto brick : _list) {			
			out<< brick.toString() << endl;
		}
		return out.str();

	}
	size_t getSize() {
		return _list.size();
	}
	//Hàm khởi tạo có đối của của đối tượng nhận vào con trỏ của struct renderer
	ListBrick(SDL_Renderer* &value) {
		this->_renderer = value;
		_isMusicOn = true;
	}
	//Thiết lập renderer cho đối tượng để vẽ lên màn hình chơi game
	void setRenderer(SDL_Renderer* &value) {
		this->_renderer = value;
	}
	//Thiết lập trạng thái của âm thanh game khi trái bóng của người chơi va chạm vào gạch
	void setIsMusicOn(bool value) {
		_isMusicOn = value;
	}
	//Xóa tất cả các khối gạch trong mảng
	void clearAllBrick() {
		_list.clear();
	}
	//Vẽ mảng gạch lên màn hình chơi game
	void drawBrickMap(bool isFinal = false) {

			for (size_t i = 0; i < _list.size(); i++) {
				_list[i].draw(isFinal);
			}
	}
	//Đọc từ file thông tin map gạch để load ở lần chơi mới
	void createListWithMapText(string fileName) {
		vector<int> map;
		fstream file(fileName, ios::in);
		while (!file.eof()) {
			string data;
			getline(file, data);
			if (data == "") {
				break;
			}
			stringstream dat(data);
			string temp;
			while (getline(dat, temp, ' ')) {
				map.push_back(stoi(temp));
			}

		}
		for (int k = 0; k < int(map.size()); k++) {
			int i = k % 10;
			int j = k / 10;
			if (map[k] == 1) {
				Brick brick(_renderer);
				brick.setX(i * 50);
				brick.setY((j+1) * 50);
				_list.push_back(brick);			
			}
		}



	}
	//Thêm gạch vào map 
	void addBrick(const Brick brick) {
		_list.push_back(brick);
	}
	//Kiểm tra sự giao nhau giữa đường thẳng và vòng tròn
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
		float c = xS*xS + xBall * xBall + yS*yS + yBall * yBall - 2 * 
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
	//Kiểm soát việc va chạm
	void handleCollision(bool isFinalMap = false) {
		//Tạo tạm một đối tượng ball đối tượng này với đối tượng trong game là một

		MagicBall* ball = MagicBall::Instance(_renderer);
		//Duyệt va lần lượt từ 0 đến hết mảng brick
		for (size_t i = 0; i < _list.size(); i++) {
			//Khi phát hiện có va chạm 
			if (ball->isCollision(float(_list[i].getX()), float(_list[i].getY()), _list[i].getSize())) {
				//cout << "co" << endl;
				//Kiểm soát việc có cho phép việc xuất ra âm thanh khi va chạm với gạch không
				if (_isMusicOn) {
					Mix_PlayChannel(-1, LoadSound("medium.wav"), 0);
				}
				//Khi quả bóng bay từ bên dưới và có xẩy ra va chạm
				if (ball->getY() - ball->getRadius() < float(_list[i].getY()) + _list[i].getSize() &&
					ball->getY() > float(_list[i].getY()) + _list[i].getSize()
					&& 
					intersectionLineAndCircle(float(_list[i].getX()),float(_list[i].getY())+_list[i].getSize(),
						float(_list[i].getX())+_list[i].getSize(), float(_list[i].getY()) + _list[i].getSize())
					) {
					//Phần bù để làm cho điều kiện va chạm bị sai
					float offset = abs(ball->getY() - ball->getRadius() - (float(_list[i].getY()) + _list[i].getSize()));
					//Thay đổi góc cho quả bóng 
					ball->setDegree(-ball->getDegree());
					//Thay đổi phần bù cho quả bóng
					ball->setY(ball->getY() + offset * float(1.1));
					
				}
				//Khi quả bóng bay từ trên xuống và va chạm với vật thể
				else if (ball->getY() + ball->getRadius() > float(_list[i].getY()) &&
					ball->getY() < float(_list[i].getY())
					&&
					intersectionLineAndCircle(float(_list[i].getX()),float(_list[i].getY()),
						float(_list[i].getX())+_list[i].getSize(), float(_list[i].getY()))
					) {
					//Phần bù để thoát khỏi điều kiện va chạm ở lần lặp tiếp theo
					float offset = abs(ball->getY() + ball->getRadius() - float(_list[i].getY()));
					//Đảo góc quả bóng
					ball->setDegree(-ball->getDegree());
					//Thay đổi lại tọa độ y để cho điều kiện bị sai
					ball->setY(ball->getY() - offset * float(1.1));
				}
				//Khi banh bay từ bên phải sang và va chạm với gạch
				else if (
					ball->getX() - ball->getRadius() < float(_list[i].getX()) + _list[i].getSize() &&
					ball->getX() > float(_list[i].getX())+_list[i].getSize()&&
					intersectionLineAndCircle(float(_list[i].getX())+_list[i].getSize(),float(_list[i].getY()),
						float(_list[i].getX()) + _list[i].getSize(), float(_list[i].getY())+_list[i].getSize())
					) {
					//Phần bù để thoát khỏi điều kiện va chạm
					float offset = abs(ball->getX() - ball->getRadius() - float(_list[i].getX()) - _list[i].getSize());
					//Đổi hướng cho trái bóng
					ball->setDegree(180 - ball->getDegree());
					//Thay đổi tọa độ X cho quả bóng 

					ball->setX(ball->getX() + offset * float(1.1));

				}
				//Khi quả bóng bay từ bên trái sang và gặp viên gạch 
				else if (ball->getX() + ball->getRadius() > float(_list[i].getX()) &&
					ball->getX() < float(_list[i].getX()) &&
					intersectionLineAndCircle(float(_list[i].getX()),float(_list[i].getY()), float(_list[i].getX()), float(_list[i].getY())+_list[i].getSize())
					) { 
					//Phần bù để thoát khỏi điều kiện va chạm
					float offset = abs(ball->getX() + ball->getRadius() - float(_list[i].getX()));
					ball->setDegree(180 - ball->getDegree());
					ball->setX(ball->getX() - offset * float(1.1));
				}
				//Khi xẩy ra việc va chạm ta cập nhật lại khung hình cho brick
				if (!isFinalMap) {
					_list[i].setFrame(_list[i].getFrame() + 1);
					//Khi mà khung hình là 4 nghĩa là viên gạch bị biến mất 
					//Khi đó xem như là đã phá hủy gạch thành công
					//ta tiến hành xóa viên gạch ra khỏi danh sách gạch
					//đồng thời người chơi ghi điểm 
					//debug
					if (_list[i].getFrame() == 4) {
						_list.erase(_list.begin() + i);
						Player::Instance()->increaseScore();
					}
				}
				break;
			}
		}
	}

};


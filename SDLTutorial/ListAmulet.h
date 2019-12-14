#pragma once
#include "Amulet.h"
#include <vector>
#include<fstream>
#include "Paddle.h"
#include "Player.h"
#include <time.h>
#include <sstream>
#include <string>
#include <map>
#include <queue>
using namespace std;

class ListAmulet
{
private:
	//Giữ một mảng các bùa
	vector <Amulet> _list;
	//Struct renderer lưu giữ các thông tin sẽ vẽ lên màn hình
	SDL_Renderer* _renderer;
	//Vector chứa các bùa vẫn còn trong thời gian có hiệu ứng;
	queue<Amulet> waitForEndTimeAmulet;
	//tín hiệu khi va chạm vào bùa magnet
	bool isTouchedMagnet = false;
public:
	//Hàm khỏi tạo không đối số của mảng bùa
	ListAmulet() {
		this->_renderer = NULL;
	}
	//Hàm xuất mảng các bùa về dạng string có thể lưu thông 
	//tin vào file
	//phục vụ cho việc lưu file và chơi tiếp tục của người chơi
	string toString() {
		stringstream out;
		for (size_t i = 0; i < _list.size(); i++) {
			out << _list[i].toString() << endl;
		}
		return out.str();
	}
	//Hàm khỏi tạo có đối số
	ListAmulet(SDL_Renderer*& value) {
		
		this->_renderer = value;
	}
	//Cài đặt renderer cho đối tượng
	void setRenderer(SDL_Renderer* &renderer) {
		this->_renderer = renderer;
	}
	//Xóa tất cả các bùa có trong mảng bùa
	void clearAllAmulet() {
		_list.clear();
	}
	//Vẽ danh sách bùa lên màn hình
	void drawListAmulet() {
		for(size_t i = 0; i < _list.size(); i++) {
			_list[i].draw();
		}
	}
	//Tạo ra map game bằng file map text
	void createListWithMapText(string fileName) {
		vector<int > map;
		fstream file(fileName, ios::in);
		if (!file) {
			cout << "\nCan't open file map data";

		}
		else {
			while (!file.eof()) {
				int data;
				file >> data;
				map.push_back(data);
			}
		}
		
		file.close();
		for (int k = 0; k < int(map.size()); k++) {
			if (map[k] != 0 && map[k] != 1&&map[k]!=9) {
				int i = k % 10;
				int j = k / 10;
				Amulet amulet(_renderer, i * 50, (j + 1) * 50, TypeAmulet(map[k]));
				_list.push_back(amulet);
			}
		}
		/*vector<int> map;
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
				Amulet amulet(_renderer, i * 50,(j + 1) * 50,TypeAmulet(map[k]));
				
				_list.push_back(amulet);
			}
		}*/
	}
	//Thêm bùa vào trong list bùa
	void addAmulet(const Amulet amulet) {
		_list.push_back(amulet);
	}
	//Kiểm soát việc xẩy ra va chạm giữa banh 
	// với các bùa
	void  handleCollision() {
		//Khi xẩy ra hiệu ứng của bùa nam châm thì sét vị trí của banh luôn nằm 
		//ở chính giữa của paddle		
		for (size_t i = 0; i < _list.size(); i++) {
			//Nếu có va chạm
			if (MagicBall::Instance(_renderer)->isCollision(float(_list[i].getX()), float(_list[i].getY()), _list[i].getSize())) {
				//Nếu loại bùa là bùa tăng điểm gấp đôi
				//d
				_list[i].activeAmulet();
				if (_list[i].getType() == Double) {
					//Gấp đôi tỉ lệ điểm khi người chơi ăn một viên gạch
					int rateOfScore = Player::Instance()->getRateOfScore();
					rateOfScore *= 2;
					Player::Instance()->setRateOfScore(rateOfScore);
				}
				//Nếu loại bùa đó là nam châm
				else if (_list[i].getType() == Magnet) {
					isTouchedMagnet = true;					
					//Lưu giữ lại tốc độ khi xẩy ra hiệu ứng 
					MagicBall::Instance(_renderer)->explode();
					MagicBall::Instance(_renderer)->setBackupSpeed(MagicBall::Instance(_renderer)->getSpeed());
					//Cập nhật lại vị trí quả bóng 
					MagicBall::Instance(_renderer)->setX(Paddle::Instance(_renderer)->getX() + Paddle::Instance(_renderer)->getWidth() / 2);
					MagicBall::Instance(_renderer)->setY(Paddle::Instance(_renderer)->getY()+10);
					//Khi đó quả bóng sẽ không di chuyển
					//FIX
					MagicBall::Instance(_renderer)->setSpeed(0);



				}
				//Nếu gặp loại bùa tăng kích thước paddle
				else if (_list[i].getType() == IncreasePaddle) {
					Paddle::Instance(_renderer)->setWidth(Paddle::Instance(_renderer)->getWidth() * float(1.5));

				}
				//Nếu gặp tín hiệu tăng kích thước trái bóng
				else if (_list[i].getType() == IncreaseSizeBall) {
					MagicBall::Instance(_renderer)->setRadius(MagicBall::Instance(_renderer)->getRadius() * float(2));

				}
				//Nếu gặp phải loại bùa giảm 50 phần trăm số điểm 
				else if (HalveScore == _list[i].getType()) {
					int rateOfScore = Player::Instance()->getRateOfScore();
					rateOfScore /= 2;
					Player::Instance()->setRateOfScore(rateOfScore);

				}
				else if (DecreaseSpeedBall == _list[i].getType()) {
					MagicBall::Instance(_renderer)->setSpeed(MagicBall::Instance(_renderer)->getSpeed() * float(0.6));
					
				}
				//Nếu gặp bùa tăng mạng
				else if (IncreaseLife == _list[i].getType()) {
					int life = Player::Instance()->getLife();
					life++;
					Player::Instance()->setLife(life);
				}
				else if (BlackHole == _list[i].getType()&&_list[i].getFrame()>=1&& _list[i].getFrame() <=120) {
					Amulet whiteHole;

					for (auto amulet : _list) {
						if (amulet.getType() == WhiteHole) {
							whiteHole = amulet;
							break;
						}
					}
					MagicBall::Instance(_renderer)->setX(whiteHole.getX() + whiteHole.getSize() / 2);
					MagicBall::Instance(_renderer)->setY(whiteHole.getY() + whiteHole.getSize() / 2);
				}
				//Sau khi trái banh va chạm vào bùa thì bùa biến mất
				if (_list[i].getType() != BlackHole && _list[i].getType() != WhiteHole) {
					if (_list[i].getType() != IncreaseLife) {
						waitForEndTimeAmulet.push(_list[i]);
					}
					_list.erase(_list.begin() + i);		
				}
				break;

			}
		}
		//Kiểm tra xem bóng ăn được bùa magnet chưa
		//nếu có thì thực hiện đoạn lệnh bên trong
		//set vị trí bóng về trung tâm paddle
		if (isTouchedMagnet) {
			MagicBall* ball = MagicBall::Instance(_renderer);
			ball->setX(Paddle::Instance(_renderer)->getX() + Paddle::Instance(_renderer)->getWidth() / 2);
			ball->setY(Paddle::Instance(_renderer)->getY() - ball->getRadius());
		}
		//Khi hàng đợi queue chưa trống 
		//nghĩa là vẫn còn bùa còn thời gian hoạt động 
		//ta kiểm tra xem thời gian chạy của bùa xem đã quá thời gian cực trị chưa 
		//nếu rồi thì ta xóa bùa 
		//nếu là bùa magnet thì ta cho trạng thái chạm và magnet là false
		if (!waitForEndTimeAmulet.empty()) {
			if (waitForEndTimeAmulet.front().getTime() >= waitForEndTimeAmulet.front().getMaxTime()) {
				waitForEndTimeAmulet.front().reset();
				if (waitForEndTimeAmulet.front().getType() == Magnet) {
					isTouchedMagnet = false;
				}
				waitForEndTimeAmulet.pop();
			}
		}

	
	}
	
};


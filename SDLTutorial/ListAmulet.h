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
using namespace std;

class ListAmulet
{
private:
	//Giữ một mảng các bùa
	vector <Amulet> _list;
	//Struct renderer lưu giữ các thông tin sẽ vẽ lên màn hình
	SDL_Renderer* _renderer;
	//Thời gian bắt đầu bấm giờ
	int _startTime;
	//Thơi gian kết thúc bấm giờ
	int _endTime;
	//Một map các hiệu ứng của bùa
	map <string, bool> _mapAmuletEffect;
public:
	//Hàm khỏi tạo không đối số của mảng bùa
	ListAmulet() {
		_startTime = 0;
		_endTime = 0;
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
		_startTime = 0;
		_endTime = 0;
		this->_renderer = value;
	}
	//Lấy ra thông tin các effect đã được kích hoạt hay chưa trong map
	map<string, bool> getMapEffect() {
		return _mapAmuletEffect;
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
	//Lấy ra khoảng thời gian mà bùa có tác dụng kể từ thời điểm có hiệu ứng
	int getTime() {
		_endTime = clock();
		return _endTime - _startTime;
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
		if (this->getTime() < 6000 && _mapAmuletEffect["Magnet"]&&Ball::Instance(_renderer)->getIsLaunch()) {
			Ball* ball = Ball::Instance(_renderer);
			Paddle* paddle = Paddle::Instance(_renderer);
			ball->setX(paddle->getX() + paddle->getWidth() / 2);
		}
		for (size_t i = 0; i < _list.size(); i++) {
			//Nếu có va chạm
			if (Ball::Instance(_renderer)->isCollision(float(_list[i].getX()), float(_list[i].getY()), _list[i].getSize())) {
				//Nếu loại bùa là bùa tăng điểm gấp đôi
				if (_list[i].getType() == Double) {
					//Cập nhật lại biến tín hiệu là đã kích hoạt hiệu ứng
					_mapAmuletEffect["Double"] = true;
					//Bấm thời gian tại thời điểm xẩy ra hiệu ứng
					_startTime = clock();
					//Gấp đôi tỉ lệ điểm khi người chơi ăn một viên gạch
					int rateOfScore = Player::Instance()->getRateOfScore();
					rateOfScore *= 2;
					Player::Instance()->setRateOfScore(rateOfScore);
				}
				//Nếu loại bùa đó là nam châm
				else if (_list[i].getType() == Magnet) {
					//Cập nhật lại biến tín hiệu 
					_mapAmuletEffect["Magnet"] = true;
					//Bấm thời gian kể từ khi xẩy ra hiệu ứng
					_startTime = clock();
					//Lưu giữ lại tốc độ khi xẩy ra hiệu ứng 
					Ball::Instance(_renderer)->setBackupSpeed(Ball::Instance(_renderer)->getSpeed());
					//Cập nhật lại vị trí quả bóng 

					Ball::Instance(_renderer)->setX(Paddle::Instance(_renderer)->getX() + Paddle::Instance(_renderer)->getWidth() / 2);
					Ball::Instance(_renderer)->setY(Paddle::Instance(_renderer)->getY()+10);
					//Khi đó quả bóng sẽ không di chuyển
					//FIX
					Ball::Instance(_renderer)->setSpeed(0);
					//Ball::Instance(_renderer)->setIsLaunch(false);


				}
				//Nếu gặp loại bùa tăng kích thước paddle
				else if (_list[i].getType() == IncreasePaddle) {
					//Cập nhật lại biến tín hiệu
					_mapAmuletEffect["IncreasePaddle"] = true;
					//Bắt đầu bấm giờ tại thời điểm có hiệu ứng
					_startTime = clock();
					Paddle::Instance(_renderer)->setWidth(Paddle::Instance(_renderer)->getWidth() * float(1.5));

				}
				//Nếu gặp tín hiệu tăng kích thước trái bóng
				else if (_list[i].getType() == IncreaseSizeBall) {
					//Cập nhật lại biến tín hiệu
					_mapAmuletEffect["IncreaseSizeBall"] = true;
					//Bắt đầu bắm thời gian tại lúc chạm vào bùa 
					_startTime = clock();
					//Ball::Instance(_renderer)->setBackupRadius(Ball::Instance(_renderer)->getRadius());
					Ball::Instance(_renderer)->setRadius(Ball::Instance(_renderer)->getRadius() * float(2));

				}
				//Nếu gặp phải loại bùa giảm 50 phần trăm số điểm 
				else if (HalveScore == _list[i].getType()) {
					//Cập nhật lại biến tín hiệu
					_mapAmuletEffect["HalveScore"] = true;
					//Bắt đầu bắm giờ tại thời điểm có hiệu ứng 
					_startTime = clock();
					int rateOfScore = Player::Instance()->getRateOfScore();
					rateOfScore /= 2;
					Player::Instance()->setRateOfScore(rateOfScore);

				}
				else if (DecreaseSpeedBall == _list[i].getType()) {
					//Cập nhật lại biến tín hiệu
					_mapAmuletEffect["SlowSpeed"] = true;
					//Bắt đầu bấm giờ 
					_startTime = clock();
					Ball::Instance(_renderer)->setSpeed(Ball::Instance(_renderer)->getSpeed() * float(0.6));
					
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
					Ball::Instance(_renderer)->setX(whiteHole.getX() + whiteHole.getSize() / 2);
					Ball::Instance(_renderer)->setY(whiteHole.getY() + whiteHole.getSize() / 2);
				}
				//Sau khi trái banh va chạm vào bùa thì bùa biến mất
				if (_list[i].getType() != BlackHole && _list[i].getType() != WhiteHole) {
					_list.erase(_list.begin() + i);
				}
				break;

			}
		}
	
	}
	//Sét lại góc bay và tốc độ trái bóng sau khi hết thời gian bùa có hiệu ứng
	void resetMagnet() {
		//d
		//Ball::Instance(_renderer)->setIsLaunch(true);
		Ball::Instance(_renderer)->setDegree(120);
		Ball::Instance(_renderer)->setSpeed(Ball::Instance(_renderer)->getBackupSpeed());
		_mapAmuletEffect["Magnet"] = false;
	}
	//Trả lại kích thước cho trái banh sau khi hết thời gian
	void resetSizeBall() {
		Ball* ball = Ball::Instance(_renderer);
		ball->setRadius(ball->getBackupRadius());
		_mapAmuletEffect["IncreaseSizeBall"] = false;


	}
	//Trả lại kích thước của paddle sau khi hết thời gian xảy ra hiệu ứng
	void resetWidthPaddle() {
		Paddle* paddle = Paddle::Instance(_renderer);
		paddle->setWidth(paddle->getWidth() / float(1.5));
		_mapAmuletEffect["IncreasePaddle"] = false;

	}
	//Trả lại vận tốc trước đó cho quả bóng sau khi hết thời gian xẩy ra hiệu ứng
	void resetSpeed() {
		Ball* ball = Ball::Instance(_renderer);		
		ball->setSpeed(ball->getSpeed()/float(0.6));
		_mapAmuletEffect["SlowSpeed"] = false;
	}
	//Trả lại tỉ lệ điểm lúc trước sau khi bùa hết hiệu lực
	void resetDoubleScore() {
		_mapAmuletEffect["Double"] = false;
		Player::Instance()->setRateOfScore(Player::Instance()->getRateOfScore() / 2);

	}
	//Trả lại tỉ lệ điểm như lúc trước sau khi bùa hết hiệu lực
	void resetHalveScore() {
		_mapAmuletEffect["HalveScore"] = false;
		Player::Instance()->setRateOfScore(Player::Instance()->getRateOfScore() * 2);

	}

};


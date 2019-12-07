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
	vector <Amulet> list;
	//Struct renderer lưu giữ các thông tin sẽ vẽ lên màn hình
	SDL_Renderer* renderer;
	//Thời gian bắt đầu bấm giờ
	int startTime;
	//Thơi gian kết thúc bấm giờ
	int endTime;
	//Một map các hiệu ứng của bùa
	map <string, bool> mapAmuletEffect;
public:
	//Hàm khỏi tạo không đối số của mảng bùa
	ListAmulet() {
		startTime = 0;
		endTime = 0;
		this->renderer = NULL;
	}
	//Hàm xuất mảng các bùa về dạng string có thể lưu thông 
	//tin vào file
	//phục vụ cho việc lưu file và chơi tiếp tục của người chơi
	string toString() {
		stringstream out;
		for (size_t i = 0; i < list.size(); i++) {
			out << list[i].toString() << endl;
		}
		return out.str();
	}
	//Hàm khỏi tạo có đối số
	ListAmulet(SDL_Renderer*& renderer) {
		startTime = 0;
		endTime = 0;
		this->renderer = renderer;
	}
	//Lấy ra thông tin các effect đã được kích hoạt hay chưa trong map
	map<string, bool> getMapEffect() {
		return mapAmuletEffect;
	}
	//Cài đặt renderer cho đối tượng
	void setRenderer(SDL_Renderer* &renderer) {
		this->renderer = renderer;
	}
	//Xóa tất cả các bùa có trong mảng bùa
	void clearAllAmulet() {
		list.clear();

	}
	//Vẽ danh sách bùa lên màn hình
	void drawListAmulet() {
		for(size_t i = 0; i < list.size(); i++) {
			list[i].draw();
		}
	}
	//Lấy ra khoảng thời gian mà bùa có tác dụng kể từ thời điểm có hiệu ứng
	int getTime() {
		endTime = clock();
		return endTime - startTime;
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
			if (map[k] != 0 && map[k] != 1) {
				int i = k % 10;
				int j = k / 10;
				Amulet amulet(renderer, i * 50, (j + 1) * 50, TypeAmulet(map[k]));
				list.push_back(amulet);
			}
		}
	}
	//Thêm bùa vào trong list bùa
	void addAmulet(const Amulet amulet) {
		list.push_back(amulet);
	}
	//Kiểm soát việc xẩy ra va chạm giữa banh 
	// với các bùa
	void  handleCollision() {
		//Khi xẩy ra hiệu ứng của bùa nam châm thì sét vị trí của banh luôn nằm 
		//ở chính giữa của paddle
		if (this->getTime() < 6000 && mapAmuletEffect["Magnet"]) {
			Ball* ball = Ball::Instance(renderer);
			Paddle* paddle = Paddle::Instance(renderer);
			ball->setX(paddle->getX() + paddle->getWidth() / 2);
		}
		for (size_t i = 0; i < list.size(); i++) {
			//Nếu có va chạm
			if (Ball::Instance(renderer)->isCollision(float(list[i].getX()), float(list[i].getY()), list[i].getSize())) {
				//Nếu loại bùa là bùa tăng điểm gấp đôi
				if (list[i].getType() == Double) {
					//Cập nhật lại biến tín hiệu là đã kích hoạt hiệu ứng
					mapAmuletEffect["Double"] = true;
					//Bấm thời gian tại thời điểm xẩy ra hiệu ứng
					startTime = clock();
					//Gấp đôi tỉ lệ điểm khi người chơi ăn một viên gạch
					int rateOfScore = Player::Instance()->getRateOfScore();
					rateOfScore *= 2;
					Player::Instance()->setRateOfScore(rateOfScore);
				}
				//Nếu loại bùa đó là nam châm
				else if (list[i].getType() == Magnet) {
					//Cập nhật lại biến tín hiệu 
					mapAmuletEffect["Magnet"] = true;
					//Bấm thời gian kể từ khi xẩy ra hiệu ứng
					startTime = clock();
					//Lưu giữ lại tốc độ khi xẩy ra hiệu ứng 
					Ball::Instance(renderer)->setBackupSpeed(Ball::Instance(renderer)->getSpeed());
					//Cập nhật lại vị trí quả bóng 

					Ball::Instance(renderer)->setX(Paddle::Instance(renderer)->getX() + Paddle::Instance(renderer)->getWidth() / 2);
					Ball::Instance(renderer)->setY(Paddle::Instance(renderer)->getY()+10);
					//Khi đó quả bóng sẽ không di chuyển
					Ball::Instance(renderer)->setSpeed(0);


				}
				//Nếu gặp loại bùa tăng kích thước paddle
				else if (list[i].getType() == IncreasePaddle) {
					//Cập nhật lại biến tín hiệu
					mapAmuletEffect["IncreasePaddle"] = true;
					//Bắt đầu bấm giờ tại thời điểm có hiệu ứng
					startTime = clock();
					Paddle::Instance(renderer)->setWidth(Paddle::Instance(renderer)->getWidth() * float(1.5));

				}
				//Nếu gặp tín hiệu tăng kích thước trái bóng
				else if (list[i].getType() == IncreaseSizeBall) {
					//Cập nhật lại biến tín hiệu
					mapAmuletEffect["IncreaseSizeBall"] = true;
					//Bắt đầu bắm thời gian tại lúc chạm vào bùa 
					startTime = clock();
					Ball::Instance(renderer)->setRadius(Ball::Instance(renderer)->getRadius() * float(2));

				}
				//Nếu gặp phải loại bùa giảm nửa phần trăm số điểm 
				else if (HalveScore == list[i].getType()) {
					//Cập nhật lại biến tín hiệu
					mapAmuletEffect["HalveScore"] = true;
					//Bắt đầu bắm giờ tại thời điểm có hiệu ứng 
					startTime = clock();
					int rateOfScore = Player::Instance()->getRateOfScore();
					rateOfScore /= 2;
					Player::Instance()->setRateOfScore(rateOfScore);

				}
				else if (DecreaseSpeedBall == list[i].getType()) {
					//Cập nhật lại biến tín hiệu
					mapAmuletEffect["SlowSpeed"] = true;
					//Bắt đầu bấm giờ 
					startTime = clock();
					Ball::Instance(renderer)->setSpeed(Ball::Instance(renderer)->getSpeed() * float(0.6));
					
				}
				//Nếu gặp bùa tăng mạng
				else if (IncreaseLife == list[i].getType()) {
					int life = Player::Instance()->getLife();
					life++;
					Player::Instance()->setLife(life);
				}
				//Sau khi trái banh va chạm vào bùa thì bùa biến mất 
				list.erase(list.begin() + i);
				break;

			}
		}
	
	}
	//Sét lại góc bay và tốc độ trái bóng sau khi hết thời gian bùa có hiệu ứng
	void resetMagnet() {
		Ball::Instance(renderer)->setDegree(120);
		Ball::Instance(renderer)->setSpeed(Ball::Instance(renderer)->getBackupSpeed());
		mapAmuletEffect["Magnet"] = false;
	}
	//Trả lại kích thước cho trái banh sau khi hết thời gian
	void resetSizeBall() {
		Ball* ball = Ball::Instance(renderer);
		ball->setRadius(ball->getRadius() / float(2));
		mapAmuletEffect["IncreaseSizeBall"] = false;


	}
	//Trả lại kích thước của paddle sau khi hết thời gian xảy ra hiệu ứng
	void resetWidthPaddle() {
		Paddle* paddle = Paddle::Instance(renderer);
		paddle->setWidth(paddle->getWidth() / float(1.5));
		mapAmuletEffect["IncreasePaddle"] = false;

	}
	//Trả lại vận tốc trước đó cho quả bóng sau khi hết thời gian xẩy ra hiệu ứng
	void resetSpeed() {
		Ball* ball = Ball::Instance(renderer);		
		ball->setSpeed(ball->getSpeed()/float(0.6));
		mapAmuletEffect["SlowSpeed"] = false;
	}
	//Trả lại tỉ lệ điểm lúc trước sau khi bùa hết hiệu lực
	void resetDoubleScore() {
		mapAmuletEffect["Double"] = false;
		Player::Instance()->setRateOfScore(Player::Instance()->getRateOfScore() / 2);

	}
	//Trả lại tỉ lệ điểm như lúc trước sau khi bùa hết hiệu lực
	void resetHalveScore() {
		mapAmuletEffect["HalveScore"] = false;
		Player::Instance()->setRateOfScore(Player::Instance()->getRateOfScore() * 2);

	}

};


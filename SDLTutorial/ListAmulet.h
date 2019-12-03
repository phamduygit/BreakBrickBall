#pragma once
#include "Amulet.h"
#include <vector>
#include<fstream>
#include "Paddle.h"
#include "Player.h"
#include <time.h>
#include <map>
using namespace std;

class ListAmulet
{
private:
	vector <Amulet> list;
	SDL_Renderer* renderer;
	int numberOfBrick;
	float currentBallSpeed;
	int startTime;
	int endTime;

	map <string, bool> mapEffect;
public:
	ListAmulet() {
		startTime = 0;
		endTime = 0;
		this->renderer = NULL;
		currentBallSpeed = 0;
		numberOfBrick = 0;
	}
	ListAmulet(SDL_Renderer* renderer) {
		mapEffect["Magnet"] = false;
		mapEffect["IncreasePaddle"] = false;
		mapEffect["IncreaseSizeBall"] = false;
		mapEffect["SlowSpeed"] = false;
		startTime = 0;
		endTime = 0;
		this->renderer = renderer;
		currentBallSpeed = 0;
		numberOfBrick = 0;
	}
	map<string, bool> getMapEffect() {
		return mapEffect;
	}

	void setMapEffectToFalse(string key) {
		mapEffect[key] = false;
	}
	void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
	void clearAllAmulet() {
		list.clear();

	}
	void drawListAmulet() {

		
		for(size_t i = 0; i < list.size(); i++) {
			list[i].draw();
		}
	}
	int getTime() {
		endTime = clock();
		return endTime - startTime;
	}
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
		//Debug

		file.close();
		//numberOfBrick = 0;
		for (int k = 0; k < int(map.size()); k++) {
			if (map[k] != 0 && map[k] != 1) {
				int i = k % 10;
				int j = k / 10;
				Amulet amulet(renderer, i * 50, j * 50, map[k]);
				list.push_back(amulet);
			}
		}
	}
	void addAmulet(const Amulet amulet) {
		list.push_back(amulet);
	}
	bool  handleCollision() {
		for (size_t i = 0; i < list.size(); i++) {
			if (Ball::Instance(renderer)->isCollision(float(list[i].getX()), float(list[i].getY()), list[i].getSize())) {

				if (list[i].getType() == Double) {
					int rateOfScore = Player::Instance()->getRateOfScore();
					rateOfScore *= 2;
					Player::Instance()->setRateOfScore(rateOfScore);
				}
				else if (list[i].getType() == Magnet) {
				
					mapEffect["Magnet"] = true;
					startTime = clock();
					Ball::Instance(renderer)->setX(Paddle::Instance(renderer)->getX() + Paddle::Instance(renderer)->getWidth() / 2);
					Ball::Instance(renderer)->setY(Paddle::Instance(renderer)->getY());
					Ball::Instance(renderer)->setSpeed(0);


				}
				else if (list[i].getType() == IncreasePaddle) {
					mapEffect["IncreasePaddle"] = true;
					startTime = clock();
					Paddle::Instance(renderer)->setWidth(Paddle::Instance(renderer)->getWidth() * float(1.5));

				}
				else if (list[i].getType() == IncreaseSizeBall) {
					//	havingEffection = true;
					mapEffect["IncreaseSizeBall"] = true;
					startTime = clock();
					Ball::Instance(renderer)->setRadius(Ball::Instance(renderer)->getRadius() * float(1.3));

				}
				else if (HalveScore == list[i].getType()) {


					int rateOfScore = Player::Instance()->getRateOfScore();
					rateOfScore /= 2;
					Player::Instance()->setRateOfScore(rateOfScore);

				}
				else if (DecreaseSpeedBall == list[i].getType()) {
					//havingEffection = true;
					mapEffect["SlowSpeed"] = true;
					Ball::Instance(renderer)->setSpeed(Ball::Instance(renderer)->getSpeed() * float(0.6));

				}
				else if (IncreaseLife == list[i].getType()) {
					int life = Player::Instance()->getLife();
					life++;
					Player::Instance()->setLife(life);

				}
				list.erase(list.begin() + i);

			}
		}
		return false;
	}
	void resetMagnet() {
		Ball::Instance(renderer)->setDegree(40);
		Ball::Instance(renderer)->setSpeed(Ball::Instance(renderer)->getBackupSpeed());
		//d
		// << "Speed" << Ball::Instance(renderer)->getSpeed();
		mapEffect["Magnet"] = false;
	}
	void resetSizeBall() {
		Ball* ball = Ball::Instance(renderer);
		ball->setRadius(ball->getRadius() / float(1.3));
		mapEffect["IncreaseSizeBall"] = false;


	}
	void resetWidthPaddle() {
		Paddle* paddle = Paddle::Instance(renderer);
		paddle->setWidth(paddle->getWidth() / float(1.5));
		mapEffect["IncreasePaddle"] = false;

	}
	void resetSpeed() {
		Ball* ball = Ball::Instance(renderer);
		ball->setSpeed(ball->getBackupSpeed());
		mapEffect["SlowSpeed"] = false;
	}


};


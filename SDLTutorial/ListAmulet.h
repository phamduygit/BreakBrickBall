#pragma once
#include "Amulet.h"
#include <vector>
#include<fstream>
#include "Paddle.h"
#include "Player.h"
using namespace std;
//enum ActionToHandle {
//	Done,
//	Magnet,
//	IncreaseLife,
//	HalveScore,
//	DoubleScore
//
//};
class ListAmulet
{
private:
	vector <Amulet> list;
	SDL_Renderer* renderer;
	int numberOfBrick;
public:
	ListAmulet(){}
	ListAmulet(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
	void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
	void clearAllAmulet() {
		list.clear();

	}
	void drawListAmulet() {
		for (int i = 0; i < list.size(); i++) {
			list[i].draw();
		}
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
		for (int k = 0; k < map.size(); k++) {
			
			if (map[k] == 1) {
			//	numberOfBrick++;
			}

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
	bool  handleCollision(){
		/*enum TypeAmulet {
			Double = 2,
			Magnet = 3,
			IncreasePaddle = 4,
			IncreaseSizeBall = 5,
			HalveScore = 6,
			DecreaseSpeedBall = 7,
			IncreaseLife = 8

		};*/
//		Game::time = clock-
		//ActionToHandle action = Done;
		for (int i = 0; i < list.size(); i++) {
			if (Ball::Instance(renderer)->isCollision(list[i].getX(), list[i].getY(), list[i].getSize())) {
				
			
				if (list[i].getType() == Double) {		   
					int rateOfScore = Player::Instance()->getRateOfScore();
					rateOfScore *= 2;
					Player::Instance()->setRateOfScore(rateOfScore);
				}
				else if (list[i].getType() == Magnet) {
					Ball::Instance(renderer)->setX(Paddle::Instance(renderer)->getX() + Paddle::Instance(renderer)->getWidth() / 2);

					Ball::Instance(renderer)->setY(Paddle::Instance(renderer)->getY());
					Ball::Instance(renderer)->setSpeed(0);


				}
				else if (list[i].getType() == IncreasePaddle) {
					Paddle::Instance(renderer)->setWidth(Paddle::Instance(renderer)->getWidth() * 1.5);
					
				}
				else if (list[i].getType() == IncreaseSizeBall) {
					Ball::Instance(renderer)->setRadius(Ball::Instance(renderer)->getRadius() * 1.3);
									   
				}
				else if (HalveScore == list[i].getType()) {
					int rateOfScore = Player::Instance()->getRateOfScore();
					rateOfScore /= 2;
					Player::Instance()->setRateOfScore(rateOfScore);

				}
				else if (DecreaseSpeedBall == list[i].getType()) {
					Ball::Instance(renderer)->setSpeed(Ball::Instance(renderer)->getSpeed() * 0.6);

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


};


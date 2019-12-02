#pragma once
#include "Brick.h"
#include <vector>
#include "MagicBall.h";
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
class ListBrick
{
private:
	vector<Brick> list;
	SDL_Renderer* renderer;

public:
	ListBrick(){}
	ListBrick(SDL_Renderer* _renderer) {
		renderer = _renderer;
	}
	void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
	void ClearMap() {
		list.clear();
	}
	void drawBrickMap() {
		for (int i = 0; i < list.size(); i++) {
			list[i].draw();
		}
	}
	void createWithMapText(string fileName) {
		vector<int> map;
		fstream file(fileName, ios::in);
		while (!file.eof()) {
			string data;
			getline(file, data);
			stringstream dat(data);
			string temp;
			while (getline(dat, temp, ' ')) {
				map.push_back(stoi(temp));
			}

		}
		
		for (int k = 0; k < map.size(); k++) {
			int i = k % 10;
			int j = k / 10;
			if (map[k] == 1) {
				Brick brick(renderer);
				brick.setX(i * 50);
				brick.setY(j * 50);
				list.push_back(brick);
			}
		}
		


	}
	void addBrick(const Brick brick) {
		list.push_back(brick);
	}
	void handleCollision() {
		Ball *ball= Ball::Instance(renderer);
		for (int i = 0; i < list.size(); i++) {
			//Khi phát hiện có va chạm 
			if (ball->isCollision(list[i].getX(), list[i].getY(), list[i].getSize())) {
				//
				if (ball->getY() - ball->getRadius() < list[i].getY() + list[i].getSize() &&
					ball->getY() > list[i].getY() + list[i].getSize()
					) {//Dưới
					//cout << "Duoi\n";
					float offset = abs(ball->getY() - ball->getRadius() - (list[i].getY() + list[i].getSize()));
					ball->setDegree(-ball->getDegree());
					ball->setY(ball->getY() + offset * 2);
				}
				else {
					if (ball->getY() + ball->getRadius() >= list[i].getY() &&
						ball->getY() < list[i].getY()
						) {//trên 
					//	cout << "\nTren";
						ball->setDegree(-ball->getDegree());
						ball->setY(ball->getY() - ball->getSpeed());
					}
				}
				if (
					ball->getX() - ball->getRadius() <= list[i].getX() + list[i].getSize() &&
					ball->getX() < list[i].getX()) { // Bên phải
					//cout << "\nTrai";
					ball->setDegree(180 - ball->getDegree());
					ball->setX(ball->getX() - ball->getSpeed());
				}
				else {
					if (ball->getX() + ball->getRadius() >= list[i].getX() &&
						ball->getX() > list[i].getX() + list[i].getSize()
						) { //Bên trái
						//cout << "\nPhai";
						ball->setDegree(180 - ball->getDegree());
						ball->setX(ball->getX() + ball->getSpeed());

					}

				}
				list[i].setFrame(list[i].getFrame() + 1);

				if (list[i].getFrame() == 4) {
					list.erase(list.begin() + i);
				}
			}
		}
	}

};


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
	vector<Brick> list;
	SDL_Renderer* renderer;
	bool isMusicOn;

public:
	ListBrick() {
		renderer = NULL;
		isMusicOn = true;
	}
	string toString() {
		stringstream out;
		for (auto brick : list) {			
			out<< brick.toString() << endl;
		}
		return out.str();

	}
	int getSize() {
		return int(list.size());
	}
	ListBrick(SDL_Renderer* &_renderer) {
		renderer = _renderer;
		isMusicOn = true;
	}
	void setRenderer(SDL_Renderer* &renderer) {
		this->renderer = renderer;
	}
	void setIsMusicOn(bool value) {
		isMusicOn = value;
	}
	void clearAllBrick() {
		list.clear();
	}
	void drawBrickMap() {
		for (size_t i = 0; i < list.size(); i++) {
			list[i].draw();
		}
	}
	void createListWithMapText(string fileName) {
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
		for (int k = 0; k < int(map.size()); k++) {
			int i = k % 10;
			int j = k / 10;
			if (map[k] == 1) {
				Brick brick(renderer);
				brick.setX(i * 50);
				brick.setY((j+1) * 50);
				list.push_back(brick);			}
		}



	}
	void addBrick(const Brick brick) {
		list.push_back(brick);
	}
	bool intersectionLineAndCircle(float xS, float yS, float xE, float yE) {
		// x = xstart + (endx-startx)t
		// y = ystart +  (endy-starty)t
		// (xStart +(endx-startx-xBall)*t)^2+(yStart +(endy-starty)*t-yBall)^2  = R^2
		float xBall = Ball::Instance(renderer)->getX();
		float yBall = Ball::Instance(renderer)->getY();
		float radius = Ball::Instance(renderer)->getRadius();
		float dx = xE - xS;
		float dy = yE - yS;
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
	void handleCollision() {
		Ball* ball = Ball::Instance(renderer);
		for (size_t i = 0; i < list.size(); i++) {
			//Khi phát hiện có va chạm 
			if (ball->isCollision(float(list[i].getX()), float(list[i].getY()), list[i].getSize())) {
				if (isMusicOn) {
					Mix_PlayChannel(-1, LoadSound("medium.wav"), 0);
				}
				if (ball->getY() - ball->getRadius() < float(list[i].getY()) + list[i].getSize() &&
					ball->getY() > float(list[i].getY()) + list[i].getSize()
					&& 
					intersectionLineAndCircle(float(list[i].getX()),float(list[i].getY())+list[i].getSize(),
						float(list[i].getX())+list[i].getSize(), float(list[i].getY()) + list[i].getSize())
					) {
					//Vi tri cua banh khi va cham la o ben duoi 
					float offset = abs(ball->getY() - ball->getRadius() - (float(list[i].getY()) + list[i].getSize()));
					ball->setDegree(-ball->getDegree());
					ball->setY(ball->getY() + offset * float(1.1));
					
				}else if (ball->getY() + ball->getRadius() > float(list[i].getY()) &&
					ball->getY() < float(list[i].getY())
					&&
					intersectionLineAndCircle(float(list[i].getX()),float(list[i].getY()),
						float(list[i].getX())+list[i].getSize(), float(list[i].getY()))
					) {//Vi tri cua trai banh khi va cham la o ben tren vat the
					float offset = abs(ball->getY() + ball->getRadius() - float(list[i].getY()));
					ball->setDegree(-ball->getDegree());
					ball->setY(ball->getY() - offset * float(1.1));
					//Mix_PlayChannel(-1, LoadSound("medium.wav"), 0);
				}else if (
					ball->getX() - ball->getRadius() < float(list[i].getX()) + list[i].getSize() &&
					ball->getX() > float(list[i].getX())+list[i].getSize()&&
					intersectionLineAndCircle(float(list[i].getX())+list[i].getSize(),float(list[i].getY()),
						float(list[i].getX()) + list[i].getSize(), float(list[i].getY())+list[i].getSize())
					) { // Bên phải
					float offset = abs(ball->getX() - ball->getRadius() - float(list[i].getX()) - list[i].getSize());
					ball->setDegree(180 - ball->getDegree());
					ball->setX(ball->getX() + offset * float(1.1));
				//	Mix_PlayChannel(-1, LoadSound("medium.wav"), 0);
				}
				else if (ball->getX() + ball->getRadius() > float(list[i].getX()) &&
					ball->getX() < float(list[i].getX()) &&
					intersectionLineAndCircle(float(list[i].getX()),float(list[i].getY()), float(list[i].getX()), float(list[i].getY())+list[i].getSize())
					) { //Bên trái
					float offset = abs(ball->getX() + ball->getRadius() - float(list[i].getX()));
					ball->setDegree(180 - ball->getDegree());
					ball->setX(ball->getX() - offset * float(1.1));
				//	Mix_PlayChannel(-1, LoadSound("medium.wav"), 0);
				}
				list[i].setFrame(list[i].getFrame() + 1);

				if (list[i].getFrame() == 4) {
					list.erase(list.begin() + i);
					int currentScore = Player::Instance()->getScore();
					currentScore = currentScore+Player::Instance()->getRateOfScore();
					Player::Instance()->setScore(currentScore);
				}
				break;
			}
		}
	}

};


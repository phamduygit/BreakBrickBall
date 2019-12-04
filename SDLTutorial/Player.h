#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Functions.h"
#include <SDL.h>
using namespace std;
//PlayerData.txt
class Player
{
private:
	int _score;
	int _unlockedMap;
	int _currentMap;
	int _life;
	int _rateOfScore;
	SDL_Renderer* renderer;
	SDL_Texture* scoreTexture;
	SDL_Texture* lifeTexture;

	Player() {
		_score = 0;
		_currentMap = 1;
		_life = 1;
		_rateOfScore = 10;
		renderer = 0;
		scoreTexture = 0;
		lifeTexture = 0;
		_unlockedMap = 1;
	}
	static Player* instance;

public:
	static Player* Instance() {
		if (instance == NULL) {
			instance = new Player();
		}

		return instance;
	}
	void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
	//score
	//currentMap
	//life
	//highScore
	void setScore(int newScore) {
		_score = newScore;
	}
	void setLife(int newValue) {
		_life = newValue;
	}
	int getUnlockedMap() {
		return _unlockedMap;
	}
	int getLife() { return _life; }
	int getScore() {
		return _score;
	}
	void setRateOfScore(int newRate) {
		this->_rateOfScore = newRate;
	}
	int getRateOfScore() {
		return _rateOfScore;
	}
	void setUnlockedMap(int value) {
		if (value > _unlockedMap) {
			_unlockedMap = value;
		}
	}
	void writeDataToFile() {
		string fileName = "PlayerData.txt";
		fstream file(fileName, ios::out);
		file << _score << endl;
		file << _unlockedMap << endl;
		file << _currentMap << endl;
		file << _life << endl;	
		file.close();
	}
	void loadDataFromFile() {
		string fileName = "PlayerData.txt";
		fstream file(fileName, ios::in);
		if (!file) {
			cout << "\nKhong the mo file";
		}
		else {
			string buffer;
			getline(file, buffer);
			//Doc diem player
			_score = stoi(buffer);			
			//Doc map da unlocked
			getline(file, buffer);
			_unlockedMap = stoi(buffer);
			//Doc map hien tai nguoi choi dang choi
			getline(file, buffer);
			_currentMap = stoi(buffer);
			//Doc 
			getline(file, buffer);
			_life = stoi(buffer);
		}

	}
	int getCurrentMap() {
		return _currentMap;
	}
	void draw() {
		SDL_Texture* temp1, *temp2;
		temp1 = scoreTexture;
		temp2 = lifeTexture;

		scoreTexture = LoadFont("Score: "+to_string(_score), renderer, "MachineGunk-nyqg.ttf");
		lifeTexture = LoadFont("Life: " + to_string(_life), renderer, "MachineGunk-nyqg.ttf");
		SDL_Rect destOfScore;
		destOfScore.x = 0;
		destOfScore.y = 0;
		destOfScore.w = 150;
		destOfScore.h = 50;
		SDL_RenderCopy(renderer, scoreTexture, NULL, &destOfScore);
		SDL_Rect destOfLife;
		destOfLife.x = 200;
		destOfLife.y = 0;
		destOfLife.w = 120;
		destOfLife.h = 50;
		SDL_RenderCopy(renderer, lifeTexture, NULL, &destOfLife);
		SDL_DestroyTexture(temp1);
		SDL_DestroyTexture(temp2);
	}

	~Player() {}

};


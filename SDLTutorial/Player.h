#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
//PlayerData.txt
class Player
{
private:
	int _score;
	int _currentMap;
	int _life;
public:
	//score
	//currentMap
	//life
	Player() {
		_score = 0;
		_currentMap = 1;
		_life = 3;
	}
	int getLife() { return _life; }
	int getScore() {
		return _score;
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
			_score = stoi(buffer);
			getline(file, buffer);
			_currentMap = stoi(buffer);
			getline(file, buffer);
			_life = stoi(buffer);
		}



	}
	int getCurrentMap() {
		return _currentMap;
	}


	~Player() {}

};


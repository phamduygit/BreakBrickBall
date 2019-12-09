#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Functions.h"
#include <SDL.h>
using namespace std;
//Lớp Player
class Player
{
private:
	//Điểm của người chơi
	int _score;
	//Máp đã unlocked
	int _unlockedMap;
	//Map hiện tại người chơi đang chơi
	int _currentMap;
	//Mạng của người chơi
	int _life;
	//Tỉ lệ điểm của người chơi
	int _rateOfScore;
	//Struct chứa các thông tin sẽ render lên màn hình
	SDL_Renderer* _renderer;
	//Lưu struct chứa thông tin sẽ render lên màn hình 
	//ở dây lưu thông tin đưa lên màn hình là chuỗi string
	SDL_Texture* _scoreTexture;
	//Lưu string render lên màn hình game
	SDL_Texture* _lifeTexture;
	//Hàm khởi tạo không đối số của đối tượng
	Player() {
		_score = 0;
		_currentMap = 1;
		_life = 3;
		_rateOfScore = 10;
		this->_renderer = 0;
		_scoreTexture = 0;
		_lifeTexture = 0;
		_unlockedMap = 1;
	}
	//Thê hiện của đối tượng
	static Player* instance;

public:
	//Phương thức tĩnh lấy ra thể hiện của đối tượng
	static Player* Instance() {
		if (instance == NULL) {
			instance = new Player();
		}

		return instance;
	}
	//thiết lập renderer cho đối tượng
	void setRenderer(SDL_Renderer*& value) {
		this->_renderer = value;
	}
	//Thiết lập điểm cho người chơi
	void setScore(int newScore) {
		_score = newScore;
	}
	//Thiết lập mạng cho người chơi
	void setLife(int newValue) {
		_life = newValue;
	}
	//Lấy ra map mà người chơi đã unlocked
	int getUnlockedMap() {
		return _unlockedMap;
	}
	//Lấy ra mạng hiện tại mà người chơi có 
	int getLife() {
		return _life;
	}
	//Lấy ra số điểm của người chơi
	int getScore() {
		return _score;
	}
	//Thiết lập tỉ lệ điểm  của người chơi
	void setRateOfScore(int newRate) {
		this->_rateOfScore = newRate;
	}
	//Lấy ra tỉ lệ điểm của người chơi
	int getRateOfScore() {
		return _rateOfScore;
	}
	//Thiết lập máp hiện tại của người chơi
	void setCurrentMap(int value) {
		_currentMap = value;
	}
	//Thiết lập map đã unlocked
	void setUnlockedMap(int value) {
		if (value > _unlockedMap&& value <= 9) {
			_unlockedMap = value;
		}
	}
	//Xuất ra file thông tin người chơi
	void writeDataToFile() {
		string fileName = "PlayerData.txt";
		fstream file(fileName, ios::out);
		file << _score << endl;
		file << _unlockedMap << endl;
		file << _currentMap << endl;
		file << _life << endl;
		file.close();
	}
	//Tải thông tin từ file về người chơi
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
	//Lấy ra map hiện tại mà người chơi đang chơi
	int getCurrentMap() {
		return _currentMap;
	}
	//Vẽ chữ lên màn hình chơi game
	void draw() {
		SDL_Texture* temp1;
		SDL_Texture* temp2;
		temp1 = _scoreTexture;
		temp2 = _lifeTexture;
		_scoreTexture = LoadFont("Score: " + to_string(_score), _renderer, "MachineGunk-nyqg.ttf");
		_lifeTexture = LoadFont("Life: " + to_string(_life), _renderer, "MachineGunk-nyqg.ttf");
		SDL_Rect destOfScore;
		destOfScore.x = 0;
		destOfScore.y = 0;
		destOfScore.w = 150;
		destOfScore.h = 50;
		SDL_RenderCopy(_renderer, _scoreTexture, NULL, &destOfScore);
		SDL_DestroyTexture(_scoreTexture);
		SDL_Rect destOfLife;
		destOfLife.x = 200;
		destOfLife.y = 0;
		destOfLife.w = 120;
		destOfLife.h = 50;
		SDL_RenderCopy(_renderer, _lifeTexture, NULL, &destOfLife);
		SDL_DestroyTexture(_lifeTexture);

		SDL_DestroyTexture(temp1);
		SDL_DestroyTexture(temp2);
	}
	//Hàm hủy 
	~Player() {}

};


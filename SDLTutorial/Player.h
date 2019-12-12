#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Functions.h"
#include <SDL.h>
#include <map>
#include <vector>
#include <sstream>
using namespace std;
//Lớp Player
class Player
{
private:
	//Tổng điểm của người chơi
	int _totalScore;
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
	//map chứa điểm cao của từng vòng chơi
	map<string, int > highScore;
	//Biến lưu giữ điểm vòng trước của người chơi
	int currentMapScore;
	map<int, int> roundScore;
	map<string, SDL_Texture*> image;


	//Hàm khởi tạo không đối số của đối tượng
	Player() {
		_totalScore = 0;
		_currentMap = 1;
		_life = 3;
		_rateOfScore = 10;
		this->_renderer = 0;
		_scoreTexture = 0;
		_lifeTexture = 0;
		_unlockedMap = 1;
		currentMapScore = 0;
		for (int i = 1; i <= 9; i++) {
			roundScore[i] = 0;
		}
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
	//Thiết lập điểm từng vòng cho người chơi
	void setCurrentMapScore(int value) {
		currentMapScore = value;
	}
	//Thiết lập điểm tổng
	void setTotalScore(int value) {
		_totalScore = value;
	}
	//Tăng điểm map chơi hiện tại
	//Đồng thời tăng tổng điểm 
	void increaseScore() {
		currentMapScore += _rateOfScore;
		_totalScore += _rateOfScore;
	}
	//Reset lai diem vòng hiện tại của người chơi về 0
	//Reset lại điểm vòng hiện tại cho người chơi chơi lại từ đầu 
	void reupdateTotalScore(int currentMap) {
		int result = 0;
		for (int i = 1; i < currentMap; i++) {
			result += roundScore[i];
		}
		_totalScore = result;
		currentMapScore = 0;
	}
	//Cập nhật lại map điểm từng vòng của người chơi
	void updateScoreToRoundScore(int currentMap) {
		roundScore[currentMap] = currentMapScore;
	}
	// Reset lại điểm mỗi vòng để người chơi chơi vòng mới
	void resetMapScoreForPlayAgain() {
		currentMapScore = 0;
	}
	//Sét lại điểm vòng hiện tại vào map điểm từng vòng của người chơi
	//đồng thời reset lại điểm mỗi vòng của người chơi
	void resetMapScoreForNextMap(int currentMap) {
		roundScore[currentMap] = currentMapScore;
		currentMapScore = 0;
	}
	
	//Lấy ra điểm ở vòng chơi hiện tại của người chơi
	int getCurrentMapScore() {
		return currentMapScore;
	}
	//Xuất ra điểm người chơi trước rồi mới cập nhật lại điểm cao nhất tại vòng hiện tại
	void updateHighScore(int currentMap) {
		string key = "v" + to_string(currentMap);
		if (highScore[key] < getCurrentMapScore()) {
			highScore[key] = getCurrentMapScore();
		}
		if (highScore["HighScore"] < getTotalScore()) {
			highScore["HighScore"] = getTotalScore();
		}
	}
	//thiết lập renderer cho đối tượng
	void setRenderer(SDL_Renderer*& value) {
		this->_renderer = value;
	}
	//Thiết lập điểm cho người chơi
	void setScore(int newScore) {
		_totalScore = newScore;
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
	//Lấy ra tổng số điểm của người chơi
	int getTotalScore() {
		return _totalScore;
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
		file << _totalScore << endl;
		file << _unlockedMap << endl;
		file << _currentMap << endl;
		file << _life << endl;
		file << currentMapScore << endl;
		file << "----------------" << endl;
		for (int i = 1; i <= 9; i++) {
			file << roundScore[i] << endl;
		}
		file.close();
		fileName = "HighScore.txt";
		file.open(fileName, ios::out);
		for (auto item : highScore) {
			file << item.first << ":" << item.second << endl;
		}

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
			_totalScore = stoi(buffer);
			//Doc map da unlocked
			getline(file, buffer);
			_unlockedMap = stoi(buffer);
			//Doc map hien tai nguoi choi dang choi
			getline(file, buffer);
			_currentMap = stoi(buffer);
			//Doc 
			getline(file, buffer);
			_life = stoi(buffer);
			getline(file, buffer);
			currentMapScore = stoi(buffer);
			getline(file, buffer);
			int i = 1;
			while (!file.eof()) {
				getline(file, buffer);
				if (buffer == "") {
					break;
				}
				roundScore[i] = stoi(buffer);
				i++;

			}
		}
		file.close();
		fileName = "HighScore.txt";
		file.open(fileName, ios::in);
		if (!file) {
			cout << "\nKhong tim thay file high score";
		}
		else {
			vector<string> token;
			string buff;
			while (!file.eof()) {
				getline(file, buff);
				if (buff == "") {
					break;
				}
				cout << "Tim thay file";
				stringstream source(buff);
				string dat;

				while (getline(source, dat, ':')) {
					token.push_back(dat);
				}
				cout << token[0] << endl;
				highScore[token[0]] = stoi(token[1]);
				token.clear();

			}

		}
		file.close();

	}
	//Lấy ra map hiện tại mà người chơi đang chơi
	int getCurrentMap() {
		return _currentMap;
	}
	
	auto getMapHighScore() {
		return highScore;
	}
	//Vẽ chữ lên màn hình chơi game
	void draw() {
		SDL_Texture* temp1;
		SDL_Texture* temp2;
		temp1 = _scoreTexture;
		temp2 = _lifeTexture;
		_scoreTexture = LoadFont("Score: " + to_string(_totalScore), _renderer, "zorque.ttf");
		_lifeTexture = LoadFont("Life: " + to_string(_life), _renderer, "zorque.ttf");
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
	void drawCurrentResult(float verticalHeight = 0) {
		string key = "v" + to_string(_currentMap);
		auto vongTT = LoadFont("Round: " + to_string(_currentMap), _renderer, "zorque.ttf");
		auto diemHienTai = LoadFont("Your current map score: " + to_string(currentMapScore), _renderer, "zorque.ttf");
		auto tongDiem = LoadFont("Your total score: " + to_string(_totalScore), _renderer, "zorque.ttf");
		auto diemCaoHienTai = LoadFont("Old high score:  " + to_string(highScore[key]), _renderer, "zorque.ttf");
		auto tongDiemCaoNhat = LoadFont("Old high score: " + to_string(highScore["HighScore"]), _renderer, "zorque.ttf");
		DrawInRenderer(_renderer, vongTT, 75, 290+verticalHeight, 12 * (("Round: " + to_string(_currentMap)).length()), 40);
		DrawInRenderer(_renderer, diemHienTai, 75, 290 + 45+verticalHeight, 12 * ("Your current map score: " + to_string(currentMapScore)).length(), 40);
		DrawInRenderer(_renderer, diemCaoHienTai, 75, 290 + 90+verticalHeight, 12 * ("Old high score: " + to_string(highScore[key])).length(), 40);
		DrawInRenderer(_renderer, tongDiem,75, 290 + 90 + 45+verticalHeight, 12 * ("Your total score: " + to_string(_totalScore)).length(), 40);
		DrawInRenderer(_renderer, tongDiemCaoNhat, 75, 290 + 90 + 90+verticalHeight, 12 * ("Old high score: " + to_string(highScore["HighScore"])).length(), 40);


		/*DrawInRenderer(_renderer, vongTT2, 80 + 100 + 10, 290, 20 * to_string(_currentMap).length(), 40);
		DrawInRenderer(_renderer, diemHienTai, 80, 290+45,300, 40);*/
		//DrawInRenderer(_renderer, diemCaoHienTai2, 80, 290+45, 30, 40);


		SDL_DestroyTexture(vongTT);
		SDL_DestroyTexture(diemHienTai);
		SDL_DestroyTexture(tongDiem);
		SDL_DestroyTexture(diemCaoHienTai);
		SDL_DestroyTexture(tongDiemCaoNhat);



	}
	//Hàm hủy 
	~Player() {}

};


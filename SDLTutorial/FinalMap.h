#pragma once
#include "ListBrick.h"
#include "TextureManager.h"
#include <SDL.h>
#include "Brick.h"
class FinalMap
{
private:
	//Struct chứa các thông tin sẽ render lên màn hình
	SDL_Renderer* _renderer;
	//Tọa độ của hố đỏ
	int _xRedHole;
	int _yRedHole;
	//Khung hình hiện tại 
	int _currentRedHoleFrame;
	//Danh sách những viên gạch
	ListBrick _listBrick;

public:
	//Hàm khởi tạo không đối số 
	FinalMap(){}
	//Hàm khởi tạo có đối số 
	FinalMap(SDL_Renderer*& renderer) {
		this->_renderer = renderer;
		_listBrick.setRenderer(renderer);
		_currentRedHoleFrame = 1;
	}
	//Load file FinalMap.txt từ tệp tin
	void loadData(string fileName) {
		fstream file(fileName, ios::in);
		if (!file) {
			cout << "\nFile not found";
			return;
		}
		vector<int > map;
		int temp;
		int k = 0;
		while (!file.eof()) {

			int i =k % 10;
			int j = k / 10;
			file >> temp;
			if (temp == 1) {
				//T				
				Brick* brick = new Brick(_renderer, i * 50, (j+1) * 50);
				_listBrick.addBrick(*brick);
				delete brick;
			}
			else if (temp == 8) {
				_xRedHole = i * 50;
				_yRedHole = (j+1) * 50;
			}
			k++;
		}
		

	}

	//Khi va chạm vào gạch thì viên gạch phản xạ lại 
	void update() {
		_listBrick.handleCollision(true);		

	}
	//Kiểm tra xem quả bóng có ở trong hố đỏ không
	bool isBallInRedHole() {
		Ball* ball = Ball::Instance(_renderer);
		float xBall = ball->getX();
		float yBall = ball->getY();
		if (xBall >= _xRedHole &&
			xBall <= _xRedHole + 50 &&
			yBall >= _yRedHole &&
			yBall <= _yRedHole + 50
			&&_currentRedHoleFrame<=120
			) {
			
			return true;
		}
		return false;
	}
	//Hàm vẽ những viên gạch và hố đen lên màn hình chơi game
	void draw() {
		_listBrick.drawBrickMap(true);
		TextureManager::GetInstance()->drawFrame("Hole", _xRedHole, _yRedHole, 50, 50, 1, _currentRedHoleFrame, _renderer);
		_currentRedHoleFrame = (_currentRedHoleFrame + 1) % 500;
	}

};


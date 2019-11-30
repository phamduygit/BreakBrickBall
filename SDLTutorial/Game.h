#pragma once
#include "Functions.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "MagicBall.h"
#include "Brick.h"
#include <vector>
#include "Paddle.h"
#include "Line.h"
#include "Barrier.h"
#include <cmath>
#include <math.h>


#define PI 3.141592
using namespace std;
class Game
{
private:
	Line line;
	SDL_Surface* _screenSurface;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	bool _running;
	SDL_Texture* _grassBackground;
	Ball* ball;
	vector<Brick> listBrick;
	double degrees;
	Paddle _paddle;
	Barrier barrier;
	bool MoveLR[2] = { false, false };
	int x;
	int y;
	//Theo thứ tự là click 
	bool mouseActionClicked = false;
	bool isResetState = true;

	Game() {

		_screenSurface = NULL;
		_window = NULL;
		_renderer = NULL;
		_running = false;
		_grassBackground = NULL;
		degrees = 0;


	}
	static Game* instance;
public:
	static Game* Instance() {
		if (instance == NULL) {
			instance = new Game();
		}
		return instance;
	}


	void Init(string title, int Width, int Height) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			cout << "SDL could not initialize! SDL Error: " << SDL_GetError();
			_running = false;
		}
		else {
			// Kiểm tra xem có hỗ trợ OpenGL và Direct3D không
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
				cout << "Warning: Linear texture filtering not enabled!" << endl;
				_running = false;
			}
			// Tạo cửa sỗ mới 
			_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
			if (_window == NULL) {
				cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			}
			else {
				// Tạo nền cho của sổ mới 
				_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
				if (_renderer == NULL) {
					cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				}
				else {
					// Khỡi tạo màu nền ban dầu 
					SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
					// Khỡi tạo để thực hiện tải hình ảnh
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags)) {
						cout << "SDL_image could not initilialize! SDL_image Error: " << IMG_GetError() << endl;
					}
					// Khởi tạo để tải chữ viết lên màn hình
					if (TTF_Init()) {
						cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
					}
				}
				_running = true;
			}
			TextureManager::GetInstance()->load("Brick.png", "Brick", _renderer);
			_grassBackground = LoadImage("GrassBackground.png", _renderer);
			ball = Ball::Instance(_renderer);

			ball->setImage("Ball.png");
			line = Line(_renderer);
			Brick _brick;
			for (int i = 0; i < 10; i++) {
				_brick = Brick(_renderer, i * 50, 7 * 50);
				listBrick.push_back(_brick);

			}
			for (int i = 0; i < 10; i++) {
				_brick = Brick(_renderer, i * 50, 4*50);
				listBrick.push_back(_brick);

			}
			for (int i = 0; i < 10; i++) {
				_brick = Brick(_renderer, i * 50, 1 * 50);
				listBrick.push_back(_brick);

			}
			barrier = Barrier(_renderer,0,200);
			barrier.setImage("Paddle.png");
			_paddle = Paddle(_renderer);
			_paddle.setImage("Paddle.png");



		}
	}
	void render() {
		SDL_RenderClear(_renderer);
		DrawInRenderer(_renderer, _grassBackground);
		ball->draw();
		for (auto _brick : listBrick)
			_brick.draw();
		SDL_SetRenderDrawColor(_renderer, 255, 0, 255, NULL);
	
		if (!ball->getIsLaunch()) {
			line.draw();
		}
		_paddle.draw();
		barrier.draw();
	



		SDL_RenderPresent(_renderer);
		//delete[] p;
	}
	bool isBoundFromPaddle() {
		float t1;
		float t2;
		if (ball->getRadius() * ball->getRadius() - (_paddle.getY() - ball->getY())* (_paddle.getY() - ball->getY()) >= 0) {
			float sq = sqrt(abs(ball->getRadius() * ball->getRadius() - (_paddle.getY() - ball->getY()) * (_paddle.getY() - ball->getY())));
				t1 = (sq - _paddle.getX() + ball->getX()) / 120.0;
				t2 = (-sq - _paddle.getX() + ball->getX()) / 120.0;
				if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1))
					return true;
		}
		return false;

	
		
	}
	void update() {

		line.setMouse(x, y);
		line.setPaddlePoint(_paddle.getX(), _paddle.getY());
		//Khi nhan duoc tin hieu click chuot va trai banh chua bay
		if (mouseActionClicked == true && !ball->getIsLaunch()) {
			ball->setIsLaunch(true);
			float degree = atan(line.getHeSoGoc()) * 180 / PI;
			if (degree > 0) {
				degree = 180 - degree;
			}
			else {
				degree = abs(degree);
			}
			//cout << degree << endl;
			ball->setDegree(degree);
			//cout << degree << endl;
		}
		//Khi bi reset va chuot chua nhan
		if (isResetState == true) {
			if (!mouseActionClicked) {
				ball->setX(_paddle.getX() + _paddle.getSize() / 2);
				ball->setY(_paddle.getY() - ball->getRadius());
			}
			else {
				isResetState = false;
			}
		}
		if (ball->getIsLaunch()) {
			/*if (mouseActionClicked) {
				ball->setSpeed(ball->getSpeed() + 1);

			}*/
			if (ball->getY() - ball->getRadius() <= 0) {
				ball->setDegree(-ball->getDegree());

			}
			if (ball->getY() + ball->getRadius() > 800) {

				ball->reset(_paddle.getX() + 60, _paddle.getY());
				isResetState = true;

			}
			if (ball->getX() - ball->getRadius() < 0 || ball->getX() + ball->getRadius() > 500) {
				ball->setDegree(180 - ball->getDegree());
			}
		}
		//
		//Debug
		//
		//cout << ball->getDegree() << endl;
		//cout <<ball->getX() << endl << ball->getY();
		for (int i = 0; i < listBrick.size(); i++) {
			//Khi phát hiện có va chạm 
			if (ball->isCollision(listBrick[i].getX(), listBrick[i].getY(), listBrick[i].getSize())) {
				//
				if (ball->getY() - ball->getRadius() < listBrick[i].getY() + listBrick[i].getSize() &&
					ball->getY() > listBrick[i].getY() + listBrick[i].getSize()
					) {//Dưới
					//cout << "Duoi\n";
					float offset = abs(ball->getY() - ball->getRadius() - (listBrick[i].getY() + listBrick[i].getSize()));
					ball->setDegree(-ball->getDegree());
					ball->setY(ball->getY() +offset*2);
				}
				else {
					if (ball->getY() + ball->getRadius() >= listBrick[i].getY() &&
						ball->getY() < listBrick[i].getY()
						) {//trên 
					//	cout << "\nTren";
						ball->setDegree(-ball->getDegree());
						ball->setY(ball->getY() - ball->getSpeed());
					}
				}
				if (
					ball->getX() - ball->getRadius() <= listBrick[i].getX() + listBrick[i].getSize() &&
					ball->getX() < listBrick[i].getX()) { // Bên phải
					//cout << "\nTrai";
					ball->setDegree(180 - ball->getDegree());
					ball->setX(ball->getX() - ball->getSpeed());
				}
				else {
					if (ball->getX() + ball->getRadius() >= listBrick[i].getX() &&
						ball->getX() > listBrick[i].getX() + listBrick[i].getSize()
						) { //Bên trái
						//cout << "\nPhai";
						ball->setDegree(180 - ball->getDegree());
						ball->setX(ball->getX() + ball->getSpeed());

					}

				}

				listBrick[i].setFrame(listBrick[i].getFrame() + 1);

				if (listBrick[i].getFrame() == 4) {
					listBrick.erase(listBrick.begin() + i);

				}

			}
		}

		ball->move();
		//Kiểm soát ball va cham với paddle
		/*if (ball->getY() > _paddle.getY() - ball->getRadius() &&
			ball->getX() > _paddle.getX() &&
			ball->getX() < _paddle.getX() + _paddle.getSize()) {
			ball->setDegree(-ball->getDegree());
			ball->setY(ball->getY() - ball->getSpeed());
		}*/
		//Va cham voi vat can
		/*if (ball->getY() - ball->getRadius() < barrier.getY() + barrier.getHeight() &&
			ball->getX() > barrier.getX() &&
			ball->getX() < barrier.getX() + barrier.getSize()) {
			cout << "HIHI";
			float offset = (ball->getY() - ball->getRadius() - (barrier.getY() + barrier.getHeight())) + 10;
			ball->setDegree(-ball->getDegree());
			ball->setY(ball->getY() + offset);


		}*/
		//Va cham voi paddle

		//Sua chua
		if(isBoundFromPaddle()){
		/*if (ball->getY() + ball->getRadius() > _paddle.getY() &&
			ball->getX() > _paddle.getX()-ball->getRadius() &&
			ball->getX() < _paddle.getX() + _paddle.getSize()+ball->getRadius()) {*/
			float offset = abs(ball->getY() + ball->getRadius() - _paddle.getY())*2;


		
			ball->setY(ball->getY() - offset);
			if (_paddle.getDeltaX() != 0) {
				if (ball->getDegree() < 0) {
					if (_paddle.getDeltaX() > 0) {
						if(-ball->getDegree()<180-15)
							ball->setDegree(-ball->getDegree() + 15);
					}
					else {
						if (-ball->getDegree() > 30) {
							ball->setDegree(-ball->getDegree() - 15);
						}
						
					}
				}
			}
			else {
				ball->setDegree(-ball->getDegree());
			}
		


		}
		barrier.move();
		if (ball->getIsLaunch()) {
			_paddle.move(x);
		}
	}

	void handleEvents() {
		SDL_Event Events;
		SDL_PollEvent(&Events);
		if (Events.type == SDL_QUIT)
		{
			_running = false;
		}
		else if (Events.type == SDL_KEYDOWN)
		{
			switch (Events.key.keysym.sym)
			{
			case SDLK_a:
				MoveLR[0] = true;
				break;
			case SDLK_d:
				MoveLR[1] = true;
				break;
			}
		}
		else if (Events.type == SDL_KEYUP)
		{
			switch (Events.key.keysym.sym)
			{
			case SDLK_a:
				MoveLR[0] = false;
				break;
			case SDLK_d:
				MoveLR[1] = false;
				break;
			}
		}
		else if (Events.type == SDL_MOUSEMOTION || Events.type == SDL_MOUSEBUTTONUP || Events.type == SDL_MOUSEBUTTONDOWN) {
			SDL_GetMouseState(&x, &y);
			switch (Events.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				mouseActionClicked = true;
				break;
			case SDL_MOUSEBUTTONUP:
				mouseActionClicked = false;
				break;
			default:
				break;
			}
		}
	}
	bool getRunning() {
		return _running;
	}
};


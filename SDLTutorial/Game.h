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
#include "ListBrick.h"
#include "Map.h"
#include "Menu.h"

#define PI 3.141592
using namespace std;
class Game
{
private:
	Line line;
	Menu _menu;
	SDL_Surface* _screenSurface;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	bool _running;
	SDL_Texture* _grassBackground;
	Ball* ball;
	/*vector<Brick> listBrick;*/
	ListBrick listBrick;
	double degrees;
	Paddle _paddle;
	Barrier barrier;
	bool MoveLR[2] = { false, false };
	int xMouse;
	int yMouse;
	//Theo thứ tự là click 
	bool mouseActionClicked = false;
	bool isResetState = true;
	int currentMap = 0;
	bool isEnteredGame = false;
	bool isCollision = false;

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
			_menu = Menu(_renderer);
			TextureManager::GetInstance()->load("Brick.png", "Brick", _renderer);
			_grassBackground = LoadImage("GrassBackground.png", _renderer);
			ball = Ball::Instance(_renderer);
			ball->setImage("Ball.png");
			line = Line(_renderer);
			listBrick.setRenderer(_renderer);
			listBrick.createWithMapText("map.txt");
			_menu.setFont("MachineGunk-nyqg.ttf");
			_menu.setImage("GrassBackground.png");

			barrier = Barrier(_renderer, 0, 200);
			barrier.setImage("Paddle.png");
			_paddle = Paddle(_renderer);
			_paddle.setImage("Paddle.png");



		}
	}
	void render() {

		SDL_RenderClear(_renderer);
		if (_menu.getChose()) {
			DrawInRenderer(_renderer, _grassBackground);
			ball->draw();
			listBrick.drawBrickMap();
			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, NULL);
			if (!ball->getIsLaunch()) {
				line.draw();
			}
			_paddle.draw();
		}
		else {
			_menu.draw(xMouse, yMouse, mouseActionClicked);
		}

		SDL_RenderPresent(_renderer);
		//delete[] p;
	}
	bool isBoundFromPaddle() {
		float t1;
		float t2;
		if (ball->getRadius() * ball->getRadius() - (_paddle.getY() - ball->getY()) * (_paddle.getY() - ball->getY()) >= 0) {
			float sq = sqrt(abs(ball->getRadius() * ball->getRadius() - (_paddle.getY() - ball->getY()) * (_paddle.getY() - ball->getY())));
			t1 = (sq - _paddle.getX() + ball->getX()) / 120.0;
			t2 = (-sq - _paddle.getX() + ball->getX()) / 120.0;
			if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1))
				return true;
		}
		return false;



	}
	void update() {
		if (_menu.getChose()) {
			line.setMouse(xMouse, yMouse);
			line.setPaddle(_paddle.getX(), _paddle.getY(), _paddle.getSize());
			//Khi nhan duoc tin hieu click chuot va trai banh chua bay
			if (mouseActionClicked == true && !ball->getIsLaunch() &&
				(_menu.getCurrentChoose() == 1 || _menu.getCurrentChoose() == 2)) {
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
			listBrick.handleCollision();

			ball->move();
			//cout << _paddle.getDeltaX() << endl;
			//if (ball->getDegree() < 0) cout << ball->getDegree() << endl;
			if (isBoundFromPaddle()&&ball->getIsLaunch()) {
				int degree = (int)ball->getDegree()%360;
				if (degree > 0) {
					degree -= 360;

				}
				//cout << degreeTest << endl;
				
			
				float offset = abs(ball->getY() + ball->getRadius() - _paddle.getY());
				ball->setY(ball->getY() - offset);
				//Doi huong cho bong trong dieu kien paddle khong co van toc
				if(_paddle.getDeltaX()!=0){
					cout << "\nXuoc";
					if (_paddle.getDeltaX() > 0) {
						
						if (abs(degree)+15<160) {
							ball->setDegree(-degree + 15);

						}
					}
					else if(_paddle.getDeltaX()<0) {
						if (abs(degree)-15>30) {
							ball->setDegree(-degree - 15);
						}

					}

				}
				else {
					ball->setDegree(-ball->getDegree());
				}

				if (ball->getSpeed() <= 15) {
					ball->setSpeed(ball->getSpeed() * 1.1);
				}
			//	cout << ball->getSpeed()<<endl;
			}

			if (ball->getIsLaunch()) {
				_paddle.move(ball->getX(), true);
			}

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
			SDL_GetMouseState(&xMouse, &yMouse);
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


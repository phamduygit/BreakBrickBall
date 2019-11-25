#pragma once
#include "Functions.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "MagicBall.h"
#include "Brick.h"
#include <vector>

using namespace std;
class Game
{
private:
	SDL_Surface* _screenSurface;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	bool _running;
	SDL_Texture* _grassBackground;
	Ball* ball;
	vector<Brick> listBrick;
	double degrees;
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
	
	
	void Init(string title, int Width , int Height) {
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
			Brick _brick;
			for (int i = 0; i < 10; i++) {
				_brick = Brick(_renderer,i*50,0);
				listBrick.push_back(_brick);

			}
				
		//	_brick.setImage("Brick.png");
		}
	}
	void render() {
		SDL_RenderClear(_renderer);
		DrawInRenderer(_renderer, _grassBackground);
		ball->draw();
		for(auto _brick:listBrick)
			_brick.draw();
		SDL_RenderPresent(_renderer);
	}
	void update() {

		if (ball->getY() < 0 + ball->getRadius() || ball->getY() > 800 - ball->getRadius() ) {
			ball->setDegree(-ball->getDegree());

		}
		if (ball->getX() - ball->getRadius() < 0 || ball->getX() + ball->getRadius() > 500) {
			ball->setDegree(180 - ball->getDegree());
		}
		cout <<ball->getX() << endl << ball->getY();
		for (int i = 0;i< listBrick.size();i++) {
			if (ball->isCollision(listBrick[i].getX(), listBrick[i].getY(), listBrick[i].getSize())) {
				if (ball->getY() < listBrick[i].getY() + listBrick[i].getSize() + ball->getRadius()) {
					ball->setDegree(-ball->getDegree());

				}
				listBrick[i].setFrame(listBrick[i].getFrame() + 1);
				if (listBrick[i].getFrame() == 4) {
					listBrick.erase(listBrick.begin() + i);

				}
				
			}
		}

		ball->move();
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
			/*case SDLK_a:
				_brick.setFrame(_brick.getFrame()+1);
				break;
			case SDLK_d:
				_brick.setFrame(_brick.getFrame()-1);
				break;*/
			}
		}
	}
	bool getRunning() {
		return _running;
	}
};


#pragma once
#include "Functions.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "MagicBall.h"
#include "Brick.h"
using namespace std;
class Game
{
private:
	SDL_Surface* _screenSurface;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	bool _running;
	SDL_Texture* _grassBackground;
	Ball _ball;
	Brick _brick;
	double degrees;
public:
	Game() {
		_screenSurface = NULL;
		_window = NULL;
		_renderer = NULL;
		_running = false;
		_grassBackground = NULL;
		degrees = 0;
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
			_grassBackground = LoadImage("GrassBackground.png", _renderer);
			_ball = Ball(_renderer);
			_ball.setImage("Ball.png");
			_brick = Brick(_renderer);
			_brick.setImage("Brick1.png");
		}
	}
	void render() {
		SDL_RenderClear(_renderer);
		DrawInRenderer(_renderer, _grassBackground);
		_ball.draw();
		_brick.draw();
		SDL_RenderPresent(_renderer);
	}
	void update() {
		if (_ball.getY() < 0 + _ball.getRadius() || _ball.getY() > 800 - _ball.getRadius() ) {
			_ball.setDegree(-_ball.getDegree());

		}
		if (_ball.getX() - _ball.getRadius() < 0 || _ball.getX() + _ball.getRadius() > 500) {
			_ball.setDegree(180 - _ball.getDegree());
		}
		_ball.move();
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
				degrees -= 15;
				break;
			case SDLK_d:
				degrees += 15;
				break;
			}
		}
	}
	bool getRunning() {
		return _running;
	}
};


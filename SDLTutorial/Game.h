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
	Paddle _paddle;
	bool MoveLR[2] = { false, false };
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
			for (int i = 0; i < 10; i++) {
				_brick = Brick(_renderer, i * 50, 1*50);
				listBrick.push_back(_brick);

			}
			_paddle = Paddle(_renderer);
			_paddle.setImage("Paddle.png");

				
		
		}
	}
	void render() {
		SDL_RenderClear(_renderer);
		DrawInRenderer(_renderer, _grassBackground);
		ball->draw();
		for(auto _brick:listBrick)
			_brick.draw();
		//SDL_RenderDrawLine(_renderer, 0, 0, 200, 300);
		SDL_Point p[200];
		for (int i = 0; i < 200; i++) {
			p[i].x = p[i].y = i;
		}
		_paddle.draw();
		

	//	SDL_RenderDrawPoints(_renderer, p, 200);
		SDL_RenderPresent(_renderer);
		//delete[] p;
	}
	void update() {

		if (ball->getY() - ball->getRadius() <= 0 ) {
			ball->setDegree(-ball->getDegree());

		}
		if (ball->getY() > 800 - ball->getRadius()) {
			ball->reset();

		}
		if (ball->getX() - ball->getRadius() < 0 || ball->getX() + ball->getRadius() > 500) {
			ball->setDegree(180 - ball->getDegree());
		}
		//cout <<ball->getX() << endl << ball->getY();
		for (int i = 0;i< listBrick.size();i++) {
			//Khi phát hiện có va chạm 
			//
			if (ball->isCollision(listBrick[i].getX(), listBrick[i].getY(), listBrick[i].getSize())) {
				//
				if (ball->getY() - ball->getRadius()<= listBrick[i].getY() + listBrick[i].getSize()&&
					ball->getY()>listBrick[i].getY()+listBrick[i].getSize()
					     ) {//Dưới
					cout << "Duoi\n";
					ball->setDegree(-ball->getDegree());
					ball->setY(ball->getY() + ball->getSpeed());
					

				}
				else {
					if (ball->getY() + ball->getRadius() >= listBrick[i].getY()&&
						ball->getY()<listBrick[i].getY()
						) {//trên 
						cout << "\nTren";
						ball->setDegree(-ball->getDegree());
						ball->setY(ball->getY() - 6);



					}
				}
				if (
					ball->getX()-ball->getRadius()<=listBrick[i].getX()+listBrick[i].getSize()&&
					ball->getX()<listBrick[i].getX()) { // Bên phải
					cout << "\nTrai";
					ball->setDegree(180 - ball->getDegree());
					ball->setX(ball->getX() - 6);
				}
				else {
					if (ball->getX() + ball->getRadius() >= listBrick[i].getX()&&
						ball->getX()>listBrick[i].getX()+listBrick[i].getSize()
						) { //Bên trái
						cout << "\nPhai";
						ball->setDegree(180 - ball->getDegree());
						ball->setX(ball->getX() + 6);

					}

				}

				listBrick[i].setFrame(listBrick[i].getFrame() + 1);
				if (listBrick[i].getFrame() == 4) {
					listBrick.erase(listBrick.begin() + i);

				}
				
			}
		}

		ball->move();
		if (ball->getY() > _paddle.getY() - ball->getRadius() && ball->getX() > _paddle.getX() && ball->getX() < _paddle.getX() + 120) {
			ball->setDegree(-ball->getDegree());
			ball->setY(ball->getY() - ball->getSpeed());
		}
		_paddle.Move(MoveLR);
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
			int x, y;
			SDL_GetMouseState(&x, &y);
			cout << x << " " << y << endl;
			switch (Events.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				cout << "Kick Xuong" << endl;
				break;
			case SDL_MOUSEBUTTONUP:
				cout << "Kick Tha" << endl;
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


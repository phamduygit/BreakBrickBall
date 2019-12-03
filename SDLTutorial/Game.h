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
#include <cmath>
#include <math.h>
#include "ListBrick.h"
#include "Map.h"
#include "Menu.h"
#include "Player.h"
#include <map>
#include "MapDiagram.h"
#include "GameOver.h"
#include "WinScreen.h"
#include "EndScreen.h"
#define PI 3.141592

//int time = 0;
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
//	ListBrick listBrick;
	Map _map;
	double degrees;
	Paddle* _paddle;
	bool MoveLR[2] = { false, false };
	int xMouse;
	int yMouse;
	//Theo thứ tự là click 
	bool mouseActionClicked = false;
	bool isResetState = true;
	int currentMap = 0;
	bool isEnteredGame = false;
	bool isCollision = false;
	int _currentMap = 1;
	vector<string> fileMapName;
	map<string, bool > listScreen;
	MapDiagram mapDiagram;
	GameOver gameOver;
	WinScreen winScreen;
	EndScreen endScreen;
	/*
	-["MenuScreen"]
	-["MapDiagramScreen"]
	-["SettingScreen"]
	-["GameOverScreen"]
	-["GamePlayScreen"]
	*/
	Player* player;
	Game() {
		player = Player::Instance();
		ball = NULL;
		_screenSurface = NULL;
		_window = NULL;
		_renderer = NULL;
		_running = false;
		_grassBackground = NULL;
		degrees = 0;

		listScreen["MenuScreen"] = true;
		//	listScreen["MapDiagramScreen"] = true;

		xMouse = 0;
		yMouse = 0;
		_paddle = NULL;
    
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
					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
					{
						cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError();
					}
				}
				_running = true;
			}
			_menu = Menu(_renderer);
			//Set renderer cho object

			mapDiagram.setRenderer(_renderer);
			winScreen.setRenderer(_renderer);
			gameOver.setRenderer(_renderer);
			player->setRenderer(_renderer);
			endScreen.setRenderer(_renderer);

			TextureManager::GetInstance()->load("Brick.png", "Brick", _renderer);
			TextureManager::GetInstance()->load("amulet.png", "Amulet", _renderer);
			_grassBackground = LoadImage("GrassBackground.png", _renderer);
			ball = Ball::Instance(_renderer);
			ball->setImage("Ball.png");
			line = Line(_renderer);
			_map = Map(_renderer, "map2.txt");
			//	listBrick.setRenderer(_renderer);
			//	listBrick.createWithMapText("map.txt");
			_menu.setFont("MachineGunk-nyqg.ttf");
			_menu.setImage("GrassBackground.png");
			_paddle = Paddle::Instance(_renderer);
			_paddle->setImage("Paddle.png");

			fileMapName.push_back("");
			fileMapName.push_back("map1.txt");
			fileMapName.push_back("map2.txt");
			fileMapName.push_back("map3.txt");

		}
	}

	void render() {
		/*
	-["MenuScreen"]
	-["MapDiagramScreen"]
	-["SettingScreen"]
	-["GameOverScreen"]
	-["GamePlayScreen"]
	*/
		SDL_RenderClear(_renderer);
		if (listScreen["MenuScreen"]) {
			_menu.draw(xMouse, yMouse, mouseActionClicked);
		}
		else if (listScreen["MapDiagramScreen"]) {
			mapDiagram.draw(xMouse, yMouse, mouseActionClicked);

		}
		else if (listScreen["SettingScreen"]) {


		}
		else if (listScreen["GameOverScreen"]) {		
			gameOver.draw(xMouse, yMouse, mouseActionClicked);
		}
		else if (listScreen["GamePlayScreen"]) {

			DrawInRenderer(_renderer, _grassBackground);
			ball->draw();
			_map.draw();
			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, NULL);
			if (!ball->getIsLaunch()) {
				line.draw();
			}
			_paddle->draw();			
			player->draw();

		}
		else if (listScreen["WinScreen"]) {			
			winScreen.draw(xMouse, yMouse, mouseActionClicked);

		}
		else if (listScreen["EndScreen"]) {
			endScreen.draw();

		}
		SDL_RenderPresent(_renderer);
	}
	bool isBoundFromPaddle() {
		float t1;
	//	float t2;
		if (ball->getRadius() * ball->getRadius() - (_paddle->getY() - ball->getY()) * (_paddle->getY() - ball->getY()) >= 0) {
			float sq = sqrt(abs(ball->getRadius() * ball->getRadius() - (_paddle->getY() - ball->getY()) * (_paddle->getY() - ball->getY())));
			t1 = (sq - _paddle->getX() + ball->getX()) / (float)_paddle->getWidth();
			//t2 = (-sq - _paddle->getX() + ball->getX()) / (float)_paddle->getWidth();
			/*if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1)) {
				return true;
			}*/
			if ((t1 >= 0 && t1 <= 1)) {
				return true;
			}
		}
		return false;



	}
	void update() {

		if (listScreen["MenuScreen"]) {
			if (_menu.getChose()) {

				if (_menu.getCurrentChoose() == 1) {
					listScreen["MapDiagramScreen"] = true;
					listScreen["MenuScreen"] = false;
				}
				else if (_menu.getCurrentChoose() == 2) {
					listScreen["MapDiagramScreen"] = true;
					listScreen["MenuScreen"] = false;
				}
				else if (_menu.getCurrentChoose() == 3) {
					listScreen["SettingScreen"] = true;
					listScreen["MenuScreen"] = false;
				}
				else if (_menu.getCurrentChoose() == 4) {
					exit(0);
				}
				
			}
		}
		else if (listScreen["MapDiagramScreen"]) {
			if (mapDiagram.getSelectedMap() != 0) {
				listScreen["MapDiagramScreen"] = false;
				currentMap = mapDiagram.getSelectedMap();
				_map.loadData(fileMapName[currentMap]);
				listScreen["GamePlayScreen"] = true;
			}

		}
		else if (listScreen["SettingScreen"]) {

		}
		else if (listScreen["EndScreen"]) {

		}
		else if (listScreen["GameOverScreen"]) {

			if (gameOver.getAction() == retry) {
				
				_map.loadData(fileMapName[currentMap]);				
				listScreen["GamePlayScreen"] = true;
				listScreen["GameOverScreen"] = false;
				//cout << "D" << listScreen["GamePlayScreen"];
				player->setLife(3);
				player->setScore(0);
				ball->reset(_paddle->getX() + 0.5 * _paddle->getWidth() / 2, _paddle->getY());
				isResetState = true;
				gameOver.setAction(none);
				
			}
			else if (gameOver.getAction() == back) {

				listScreen["MapDiagramScreen"] = true;
				listScreen["GameOverScreen"] = false;
				player->setLife(3);
				player->setScore(0);
				mapDiagram.setSelectedMap(0);
				gameOver.setAction(none);

			}
			



		}else if(listScreen["WinScreen"]){
			if (winScreen.getAction() == retry) {
				listScreen["WinScreen"] = false;
				listScreen["GamePlayScreen"] = true;
				player->setLife(3);
				player->setScore(0);
				player->setRateOfScore(10);
				winScreen.setAction(none);
				ball->reset(_paddle->getX() + 0.5 * _paddle->getWidth() / 2, _paddle->getY());
				isResetState = true;
				//ball->reset();
				_map.loadData(fileMapName[currentMap]);

			}
			else if (winScreen.getAction() == nextMap) {
				listScreen["WinScreen"] = false;
				listScreen["GamePlayScreen"] = true;
				player->setLife(3);
				player->setRateOfScore(10);
				currentMap = (currentMap+1);
				winScreen.setAction(none);
				//ball->reset();
				if (currentMap == fileMapName.size()) {
					listScreen["WinScreen"] = false;
					listScreen["EndScreen"] = true;
					listScreen["GamePlayScreen"] = false;

				}
				else {
					_map.loadData(fileMapName[currentMap]);
					ball->reset(_paddle->getX() + 0.5 * _paddle->getWidth() / 2, _paddle->getY());
					isResetState = true;
				}

			}

		}

		else if (listScreen["GamePlayScreen"]) {

			if (Mix_PlayingMusic() == 0)
			{
				Mix_PlayMusic(LoadMusic("Theme.mp3"), -1);
			}
			//If music is being played
			if (_menu.getChose()) {
				if (_map.isCompleted()) {
					listScreen["GamePlayScreen"] = false;
					listScreen["WinScreen"] = true;
				}
				if (player->getLife() == 0) {
					listScreen["GamePlayScreen"] = false;
					listScreen["GameOverScreen"] = true;
				}
				line.setMouse(xMouse, yMouse);
				line.setPaddle(_paddle->getX(), _paddle->getY(), _paddle->getWidth());
				//Khi nhan duoc tin hieu click chuot va trai banh chua bay
				if (mouseActionClicked == true && !ball->getIsLaunch()) {
					ball->setIsLaunch(true);
					float degree = atan(line.getHeSoGoc()) * 180 / float(PI);
					if (degree > 0) {
						degree = 180 - degree;
					}
					else {
						degree = abs(degree);
					}

					ball->setDegree(degree);
				}
				if (isResetState == true) {

					if (!mouseActionClicked) {
						ball->setX(_paddle->getX() + _paddle->getWidth() / 2);
						ball->setY(_paddle->getY() - ball->getRadius());
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

						ball->reset(_paddle->getX() + _paddle->getWidth() / 2, _paddle->getY());
						
						player->setLife(player->getLife() - 1);
						isResetState = true;

					}
					if (ball->getX() - ball->getRadius() < 0 || ball->getX() + ball->getRadius() > 500) {
						ball->setDegree(180 - ball->getDegree());
					}
				}
				_map.update();
				ball->move();
				if (isBoundFromPaddle() && ball->getIsLaunch() == true) {
					int degree = (int)ball->getDegree() % 360;
					if (degree > 0 && degree < 300) {
						degree -= 360;
					}
					float offset = abs(ball->getY() + ball->getRadius() - _paddle->getY());

					ball->setY(ball->getY() - float(1.1) * offset);

					//Doi huong cho bong trong dieu kien paddle khong co van toc
					if (_paddle->getDeltaX() > 0 && abs(degree) + 15 < 180) {
						ball->setDegree(-degree + 15);

					}
					else if (_paddle->getDeltaX() < 0 && abs(degree) - 15 > 0) {
						ball->setDegree(-degree - 15);


						if (_paddle->getDeltaX() > 0) {
							if (abs(degree) + 15 < 160) {
								ball->setDegree(float(-degree + 15));

							}
							else {
								ball->setDegree(-ball->getDegree());

							}
						}
						else if (_paddle->getDeltaX() < 0) {
							if (abs(degree) - 15 > 45) {
								ball->setDegree(float(-degree - 15));
							}
							else {
								ball->setDegree(-ball->getDegree());
							}

						}


					}
					else {
						ball->setDegree(-ball->getDegree());
					}
					
					//ball->setDegree(-ball->getDegree());
				}

				if (ball->getIsLaunch()) {

					_paddle->move(xMouse);
				}
			}
			//////////////////////////////////////////////////////
		}
	}

	void handleEvents() {
		SDL_Event Events;
		SDL_PollEvent(&Events);
		if (Events.type == SDL_QUIT)
		{/*
			fstream fileDataPlayer("dataplayer.txt", ios::out);
			fileDataPlayer << "Hello 1";
			fileDataPlayer.close();*/
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
			//d
			//cout << "X:" << xMouse << endl << "Y:" << yMouse << endl;
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


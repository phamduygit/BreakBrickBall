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
#include "SettingScreen.h"

#define PI 3.141592
using namespace std;
class Game
{
private:
	//Đối tượng đường nhắm từ quả bóng đến mục tiêu cần nhắm bắn
	Line _line;
	//Đối tượng màn hình menu game
	Menu _menuScreen;
	SDL_Window* _window;
	//Struct chứa thông tin những thứ cần vẽ lên màn hình
	SDL_Renderer* _renderer;
	//Biến thế hiện trạng thái hoạt động của game
	//Biến là true khi game còn hoạt động 
	//Khi biến là false thì game kết thúc
	bool _running;
	//Đối tượng chứa texture background
	SDL_Texture* _background;
	//Đối tượng quả bóng là một con trỏ được thiết kế ở dạng singleton
	//do trong game ta chỉ tạo một quả bóng duy nhất nên thiết kế dạng singleton để dễ quản lí dữ liệu

	Ball* _ball;
	//Đối tượng map chứ thông tin map game đang chơi gồm những thứ như là 
	//danh sách các viên gạch, danh sách bùa và vị trí của chúng

	Map _map;
	//Đối tượng paddle cũng như đối tượng map do trong game có duy nhất một đối tượng này
	//nên ta thiết kế ở dạng singleton
	Paddle* _paddle;
	//Lưu trữ trạng thái nhấn phím A và D
	//khi di chuyển qua bên phải thì phần tử đầu có giá trị là true,
	//khi không di chuyển thì giá trị của phần tử này có giá trị là false
	//tương tụ đối với phần tử thứ hai
	bool _MoveLR[2] = { false, false };
	//Lưu tọa độ của chuột 
	int xMouse;
	int yMouse;

	//Biến cho ta biến trạng thái click của chuột
	//giá trị true là đã click
	//giá trị false là chưa click

	bool mouseActionClicked = false;

	//Trạng thái reset banh 
	//Biến là true nghĩa là trái banh của bay không có vận tốc 
	//
	bool isResetState = true;

	//Lưu lại máp hiện tại người chơi đã và đang chơi 
	//khi người chơi thoát ra khỏi game thì sau khi load lại game thì biến currentMap sẽ 
	//được cập nhật
	int currentMap = 0;
	//<Mảng lưu lại tên của các file map sẽ load vào game ứng với từng dòng của người  chơi

	vector<string> fileMapName;
	//Danh sách các màn hình chơi của người chơi
	map<string, bool > listScreen;
	//Đối tượng lưu màn hình cho phép người chơi sẽ chọn map để chơi
	MapDiagram mapDiagram;
	//Đối tượng lưu màn hình khi người chơi thua game
	GameOver gameOver;
	//Đối tượng lưu màn hình khi người chơi thắng một vòng
	WinScreen winScreen;
	//Đối tượng lưu màn hình khi người chơi đã chơi hết các map của game
	EndScreen endScreen;
	//Đối tượng lưu màn hình cài đặt các tính năng của game
	SettingScreen settingScreen;
	//Biến kiểm soát việc bật tắt âm thanh của game
	bool isMusicOn;
	//Lưu lại tên của màn hình trước khi người chơi ấn back hoặc next

	string previousScreen;
	//Chế độ chơi của người chơi 
	//có ba chế độ chơi có thể lựa chọn
	//thứ nhất là chế độ chơi tự động 
	//thứ hai là chế độ chơi bằng chuột
	//thứ ba là chế độ chơi bằng bàn phím
	SettingAction gameMode;
	/*
	-["MenuScreen"]
	-["MapDiagramScreen"]
	-["SettingScreen"]
	-["GameOverScreen"]
	-["GamePlayScreen"]
	*/
	//Đối tượng player lưu các thông tin của người chơi
	//cũng như đối tượng paddle và đối tượng ball ở đây ta thiết kế ở dạng
	//singleton vì trong game ta chỉ có một người chơi duy nhất
	Player* player;
	//Hàm khỏi tạo không đối số của đối tượng game
	Game() {
		player = Player::Instance();
		_ball = NULL;
		_window = NULL;
		_renderer = NULL;
		_running = false;
		_background = NULL;
		//Ban đầu ta cho trạng thái có nhạc là true nghĩa là trong game có nhạc
		//d
		isMusicOn = false;
		currentMap = 1;
		previousScreen = "";
		//Ban đầu khi vào game thì ta hiện thị màn hình Menu đầu tiên
		listScreen["MenuScreen"] = true;
		//Thiết lập tương đối tọa độ cho chuột
		xMouse = 0;
		yMouse = 0;
		_paddle = NULL;
		//Mặc định thì game được chơi bằng chuột 
		//người chơi có thế đổi chế độ chơi trong phần cài đặt
		gameMode = playWithMouse;

	}
	//Đối tượng  của game để tạo theo mô hình singleton
	static Game* instance;
public:
	//Hàm hủy các đối tượng khi đối tượng game bị hủy
	~Game() {

		delete _ball, _paddle, player, _window, _background, _renderer;

	}
	//Hàm lấy đối tượng singleton 
	static Game* Instance() {
		if (instance == NULL) {
			instance = new Game();
		}
		return instance;
	}
	//Hàm khỏi tạo màn hình game với các thông số ban đầu và load data cho các đối tượng
	//là thuộc tính private của đối tượng game

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
			_window = (SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN));
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
				//Khởi tạo trạng thái chạy cho game là true để game có thể chạy

				_running = true;
			}

			//Sét renderer cho tất cả các đối tượng cần thiết
			//Trong đó bao gồm các màn hình và đối tượng player
			_menuScreen.setRenderer(_renderer);
			mapDiagram.setRenderer(_renderer);
			winScreen.setRenderer(_renderer);
			gameOver.setRenderer(_renderer);
			player->setRenderer(_renderer);
			endScreen.setRenderer(_renderer);
			settingScreen.setRenderer(_renderer);
			_ball = Ball::Instance(_renderer);
			_line.setRenderer(_renderer);
			//Load ảnh và gắn id cho những bức ảnh cho singleton TextureManager
			TextureManager::GetInstance()->load("Brick.png", "Brick", _renderer);
			TextureManager::GetInstance()->load("amulet.png", "Amulet", _renderer);
			//Load hình ảnh cho background

			_background = LoadImage("GrassBackground.png", _renderer);
			_ball->setImage("Ball.png");

			_map = Map(_renderer, "map2.txt");
			//_map.setRenderer(_renderer);
			//Cài đặt font cho màn hình menu game
			_menuScreen.setFont("MachineGunk-nyqg.ttf");
			//Cài đặt background cho game
			_menuScreen.setImage("GrassBackground.png");
			_paddle = Paddle::Instance(_renderer);
			//Cài đặt hình ảnh cho paddle
			_paddle->setImage("Paddle.png");


			//Thêm và tên các file text chứa thông tin map vào vector

			fileMapName.push_back("");
			fileMapName.push_back("map1.txt");
			fileMapName.push_back("map2.txt");
			fileMapName.push_back("map3.txt");
			fileMapName.push_back("map4.txt");
			fileMapName.push_back("map5.txt");
			fileMapName.push_back("map6.txt");
			fileMapName.push_back("map7.txt");
			fileMapName.push_back("map8.txt");
			fileMapName.push_back("map9.txt");


		}
	}
	//Kích hoạt một màn hình nào đó 
	void enableScreen(string nameScreen) {
		vector<string> screenName;

		for (auto screen : listScreen) {
			if (screen.first != nameScreen)
			{
				cout << screen.first << endl;
				screenName.push_back(screen.first);
			}

		}
		for (int i = 0; i < screenName.size(); i++) {
			listScreen[screenName[i]] = false;
		}
		listScreen[nameScreen] = true;
		nameScreen.clear();
	}

	void render() {

		//Xóa thông tin lưu trên renderer ở vòng lặp trước
		SDL_RenderClear(_renderer);
		//Hiển thị màn hình menu game

		if (listScreen["MenuScreen"]) {
			_menuScreen.draw(xMouse, yMouse, mouseActionClicked);
		}
		//Hiển thị màn hình chọn map
		else if (listScreen["MapDiagramScreen"]) {
			mapDiagram.draw(xMouse, yMouse, mouseActionClicked);
		}
		//Hiển thị màn hình cài đặt
		else if (listScreen["SettingScreen"]) {
			settingScreen.draw(xMouse, yMouse, mouseActionClicked);
		}
		//Hiển thị màn hình chơi game chính
		else if (listScreen["GamePlayScreen"]) {
			DrawInRenderer(_renderer, _background);
			//Vẽ banh lên màn hình game
			_ball->draw();
			//Vẽ map gồm gạch và bùa lên màn hình chơi
			_map.draw();
			//Sét màu cho đường thẳng nhắm tới mục tiêu
			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, NULL);
			if (!_ball->getIsLaunch()) {
				_line.draw();
			}
			//Vẽ paddle lên màn hình chơi game
			_paddle->draw();
			//Vẽ thông tin người chơi lên màn hình chơi game
			//Thông tin gồm điểm 
			//Số mạng hiện tại mà người chơi có
			player->draw();
		}
		//Hiển thị màn hình khi người chơi bị thua game
		else if (listScreen["GameOverScreen"]) {
			//Vẽ màn hình kết thúc game
			//khi người chơi bị hêt mạng
			//nhận vào cử chỉ chuột để kiểm soát xem người chơi có muốn chơi lại không hay là chọn cài đặt
			//hay là người chơi muốn trở lại màn hình chọn map chơi

			gameOver.draw(xMouse, yMouse, mouseActionClicked);
		}
		//Hiển thị màn hình chơi khi người chơi thắng một màn
		else if (listScreen["WinScreen"]) {

			winScreen.draw(xMouse, yMouse, mouseActionClicked);
			//Set up animation
			winScreen.drawStar(player->getLife());
		}
		//Hiển thị màn hình kết thúc game khi người chơi qua hết tất cả các map của game
		else if (listScreen["EndScreen"]) {
			endScreen.draw();
		}

		//Hiện thị những thông tin copy vào renderer lên màn hình chính
		SDL_RenderPresent(_renderer);
	}
	//Hàm kiểm tra xem quả bóng có tiếp xúc với paddle không
	bool isBoundFromPaddle() {
		float t1;
		if (_ball->getRadius() * _ball->getRadius() - (_paddle->getY() - _ball->getY()) * (_paddle->getY() - _ball->getY()) >= 0) {
			float sq = sqrt(abs(_ball->getRadius() * _ball->getRadius() - (_paddle->getY() - _ball->getY()) * (_paddle->getY() - _ball->getY())));
			t1 = (sq - _paddle->getX() + _ball->getX()) / (float)_paddle->getWidth();
			if ((t1 >= 0 && t1 <= 1)) {
				return true;
			}
		}
		return false;



	}
	void update() {
		for (auto i = listScreen.begin(); i != listScreen.end(); i++) {
			cout << i->first << ":" << i->second << endl;
		}
		//Kiểm tra nêu chưa chơi nhạc thì ta tiến hành load nhạc
		if (Mix_PlayingMusic() == 0)
		{

			Mix_PlayMusic(LoadMusic("Theme.mp3"), -1);

		}
		//Khi nhạc đã được chơi 
		else {
			//Khi nhận tín hiệu tắt nhạc
			if (!isMusicOn) {
				Mix_PauseMusic();
			}

		}
		//Màn hình menu game
		if (listScreen["MenuScreen"]) {

			if (_menuScreen.getIsChose()) {
				//New Game nếu người chơi chọn 1
				if (_menuScreen.getCurrentChoose() == NewGame) {
					//Reset tất cả các tùy chọn trước ở mapdiagram ở những vòng lặp trước
					mapDiagram.resetData();
					//Tiến hành kích hoạt màn hình map diagram
					enableScreen("MapDiagramScreen");
				}
				//Load dữ liệu người chơi từ file
				//Cập nhật lại màn chơi hiện tại của người chơi vào biến currentMap 
				//Sau đó kích hoạt màn hình map diagram

				else if (_menuScreen.getCurrentChoose() == Continue) {

					player->loadDataFromFile();
					currentMap = player->getCurrentMap();
					enableScreen("MapDiagramScreen");
				}

				//Kích hoạt màn hình cài đặt
				else if (_menuScreen.getCurrentChoose() == Setting) {
					enableScreen("SettingScreen");
					settingScreen.resetData();
				}
				//Thoát game
				else if (_menuScreen.getCurrentChoose() == Exit) {
					exit(0);
				}
			}
		}
		//Hiện thị màn hình map diagram
		else if (listScreen["MapDiagramScreen"]) {
			//Sét giới hạn những map mà người chơi có thể tích chọn khi người chơi muốn chơi lại
			//với điều kiện những map mà người chơi được chọn là những map nhỏ hơn hoặc bằng 
			//map mà người chơi đã unlock 
			mapDiagram.setUnlockedMap(player->getUnlockedMap());
			//Khi nhận tín hiệu là người chơi đã tích chọn một map
			if (mapDiagram.getSelectedMap() != 0) {
				//Nếu mà người chơi chọn chơi tiếp tục
				if (_menuScreen.getCurrentChoose() == 2) {
					//Khi đó ta cặp nhật lại biến mapCurrent bằng map mà người chơi chọn 
					currentMap = mapDiagram.getSelectedMap();
					//Khi mà máp người chơi chọn trùng với map mà người chơi đã chơi ở lần chơi trước 
					//nghĩa là người chơi muốn chơi lại ở vòng chơi trước khi thoát 
					//ta tiến hành load dữ liệu đã lưu từ file
					if (currentMap == player->getCurrentMap()) {
						_map.loadData();
					}
					//Ngược lại là người chơi muốn chơi lại những khác
					else {
						_map.loadData(fileMapName[currentMap]);
					}
				}
				//Ngược lại người chơi chọn 1 nghĩa là người chơi muốn chơi mới luôn
				//do đó ta load map 1 
				else if (_menuScreen.getCurrentChoose() == 1) {

					currentMap = 1;
					_map.loadData(fileMapName[currentMap]);
				}
				//Reset lại acction để những vòng lặp sau có thể vào đúng điều kiện
				mapDiagram.resetData();
				//Kích hoạt màn hình chơi game sau khi đã load đầy đủ dữ liệu
				enableScreen("GamePlayScreen");
			}
		}
		//Màn hình cài đặt 
		//Gồm các cài đặt như
		//Bật tắt âm thanh
		//Hiển thị mapdiagram
		//trở về màn hình trước
		//thay đổi chơi độ chơi
		//gồm chế độ chơi bằng chuột,
		//chế độ chơi bằng bàn phím,
		//chế độ máy tự động chơi

		else if (listScreen["SettingScreen"]) {
			//Khi màn hình chạy hàm vẽ đồng thời bắt các sự kiện của chuột
			//do đó ta xác định được nhu cầu của người dùng 
			//Nếu hành độ trả về là turnOnSpeaker
			//nghĩa là người dùng muốn bật âm thanh
			if (settingScreen.getSettingAction() == turnOnSpeaker) {
				//Kích hoạt tín hiệu âm thanh
				isMusicOn = true;
				//gọi phương thức bật âm thanh cho đối tượng map
				//do đối tượng map lưu giữ âm thanh khi quả bóng va chạm vào gạch
				_map.turnOnMusic();
				Mix_ResumeMusic();
				//reset lại thuộc tính settingAction cho đối tượng để  những lần sau có thể chọn lại 
				// mà không nhẩy thẳng vào dòng if 
				settingScreen.setSettingAction(noneSetting);
			}
			//Khi người dùng chọn turnOffSpeaker
			//nghĩa là người dùng muốn tắt âm thanh
			else if (settingScreen.getSettingAction() == turnOffSpeaker) {
				//cài đặt biến tín hiệu âm thanh là false
				isMusicOn = false;
				//Gọi phương thức tắt âm thanh của đối tượng map
				//do khi bóng va chạm vào gạch xuất hiện âm thanh vỡ gạch
				_map.turnOffMusic();
				//Reset lại phương thuộc tính của đối tượng để sau này khi gọi lại màn hình không
				//nhảy thẳng vào if
				settingScreen.setSettingAction(noneSetting);

			}
			//Khi người dùng chọn icon play nghĩa là người dùng muốn vào màn hình map diagram
			else if (settingScreen.getSettingAction() == loadMapDiagramScreen) {
				//Do đó ta kích hoạt màn hình map diagram
				enableScreen("MapDiagramScreen");
				//Trước khi sử dụng ta reset lại các thuộc tính trong Mapdiagram
				mapDiagram.resetData();
				//Ta cũng reset lại thuộc tính của setting để những lần sau dùng không bị nhảy
				//thẳng vào if khi chưa chọn
				settingScreen.setSettingAction(noneSetting);

			}
			//Khi người dùng chọn trở về 
			else if (settingScreen.getSettingAction() == backToMenu) {
				if (previousScreen == "") {
					enableScreen("MenuScreen");
					//listScreen["MenuScreen"] = true;
					//listScreen["SettingScreen"] = false;
					_menuScreen.resetData();
				}
				else {
					enableScreen(previousScreen);
					//listScreen[previousScreen] = true;
					//listScreen["SettingScreen"] = false;
				}
				//Sau khi chuyển màn hình thì ta reset lại thuộc tính get hành động người dùng 
				//để không bị nhảy vào if ngay khi vòng lặp tiếp theo gọi màn hình này
				settingScreen.setSettingAction(noneSetting);
			}
			//Khi người chơi chọn chế độ tự động chơi
			else if (settingScreen.getSettingAction() == autoPlay) {
				gameMode = autoPlay;
			}
			//Khi người chơi chọn chế độ chơi với bàn phím
			else if (settingScreen.getSettingAction() == playWithKeyboard) {
				gameMode = playWithKeyboard;
			}
			//Khi người chơi chọn chế dộ chơi với chuột
			else if (settingScreen.getSettingAction() == playWithMouse) {
				gameMode = playWithMouse;
			}
		}
		//Màn hình kết thúc game không có gì để cập nhật
		else if (listScreen["EndScreen"]) {
			//Exit


		}
		//Khi load màn hình game over 
		else if (listScreen["GameOverScreen"]) {
			//Thiết lặp lại tốc độ cho quả bóng
			_ball->setSpeed(4);
			//Khi người chơi chọn chơi lại
			if (gameOver.getAction() == retry) {

				currentMap = player->getCurrentMap();
				_map.loadData(fileMapName[currentMap]);
				enableScreen("GamePlayScreen");
				//Khi choi lại sét lại mạng cho người chơi là 3 mạng
				player->setLife(3);
				//reset lại điểm của người chơi
				player->setScore(0);
				//Thiết lặp lại vị trí của quả bóng
				_ball->reset(_paddle->getX() + 0.5 * _paddle->getWidth() / 2, _paddle->getY());
				isResetState = true;
				gameOver.setAction(none);
			}
			//Khi người chơi muốn quay trở lại chọn vòng khác để chơi
			else if (gameOver.getAction() == back) {
				//Kích hoạt màn hình map diagram
				enableScreen("MapDiagramScreen");

				player->setLife(3);
				player->setScore(0);
				//reset lại thuộc tính của map diagram

				mapDiagram.setSelectedMap(0);
				gameOver.setAction(none);


			}
			//Nếu người chơi chọn cài đặt
			else if (gameOver.getAction() == setting) {
				//Kích hoạt màn hình setting
				enableScreen("SettingScreen");
				//Lưu lại tên màn hình vào biến previous
				previousScreen = "GameOverScreen";
				gameOver.setAction(none);
			}
		}
		else if (listScreen["WinScreen"]) {
			//Khi người chơi thắng set lại tốc độ cho quả bóng
			_ball->setSpeed(4);
			//Người chơi chọn nút chơi lại
			if (winScreen.getAction() == retry) {
				enableScreen("GamePlayScreen");
				player->setLife(3);
				player->setRateOfScore(10);
				//Reset lại action cho màn hình chiến thắng
				winScreen.setAction(none);
				//Set vị trí cho trái banh ngay giữa paddle
				_ball->reset(_paddle->getX() + 0.5 * _paddle->getWidth() / 2, _paddle->getY());
				//Điều kiện cho trái banh dính vào paddle
				isResetState = true;
				//Khi người chơi muốn chơi lại load lại map 
				_map.loadData(fileMapName[currentMap]);
			}

			else if (winScreen.getAction() == nextMap) {
				enableScreen("GamePlayScreen");
				player->setCurrentMap(currentMap + 1);
				player->setUnlockedMap(currentMap + 1);
				//reset lại mạng cho người chơi
				player->setLife(3);
				//Reset lại tỉ lệ điểm cho người chơi
				player->setRateOfScore(10);
				//Reset lại action của màn hình win screen
				winScreen.setAction(none);
				//Tăng máp lên một đơn vị
				currentMap = (currentMap + 1);
				//Nếu map hiện tại mà bằng kích thước của mạng các map
				//Nghĩa là người chơi đã đi qua hết các map của game
				//Khi đó ta sẽ chuyển người chơi đến màn hình kết thúc game
				if (currentMap == fileMapName.size()) {
					enableScreen("EndScreen");
				}
				//Ngược lại nếu mà người chơi vẫn chưa chơi hết các map trong game
				else {
					//Tải dữ liều từ các tập tin vào map
					_map.loadData(fileMapName[currentMap]);
					//Reset lại vị trí của paddle
					_ball->reset(_paddle->getX() + 0.5 * _paddle->getWidth() / 2, _paddle->getY());
					isResetState = true;
				}
			}
		}
		//Hiện thị màn hình chơi game
		else if (listScreen["GamePlayScreen"]) {
			//Kiểm tra xem người chơi phá hủy hết gạch chưa
			if (_map.isCompleted()) {
				//Kích hoạt màn hình chiến thắng game
				enableScreen("WinScreen");
			}
			//Kiểm tra khi người chơi chết 
			if (player->getLife() == 0) {
				//Thì ta kích hoạt màn hình kết thúc game
				enableScreen("GameOverScreen");
			}
			//Cập nhật vị trí của chuột để vẽ đường thẳng nhắm bắn 
			_line.setMouse(xMouse, yMouse);
			//Cập nhật vị trí của paddle
			_line.setPaddle(_paddle->getX(), _paddle->getY(), _paddle->getWidth());

			//Khi click chuột và banh chưa bay 
			if (mouseActionClicked == true && !_ball->getIsLaunch()) {
				//Sét trạng thái cho trái banh bay lên
				_ball->setIsLaunch(true);
				//Tính toán góc bay lên của quả bóng dựa vào hệ số góc
				float degree = atan(_line.getHeSoGoc()) * 180 / float(PI);
				if (degree > 0) {
					degree = 180 - degree;
				}
				else {
					degree = abs(degree);
				}

				_ball->setDegree(degree);
			}
			//Khi trái banh trở lại vị trí ban đầu thì ta sét lại vị trí cho trái banh
			if (isResetState == true) {
				//Khi ngươi chơi chưa nhấn click chuột
				if (!mouseActionClicked) {
					_ball->setX(_paddle->getX() + _paddle->getWidth() / 2);
					_ball->setY(_paddle->getY() - _ball->getRadius());
				}
				else {
					isResetState = false;
				}
			}
			//Khi quả bóng đã bay lên
			if (_ball->getIsLaunch()) {
				//Kiểm soát xem quả bóng va chạm vào biên trên
				if (_ball->getY() - _ball->getRadius() < 0) {
					_ball->setDegree(-_ball->getDegree());

				}
				//Kiểm soát quả bóng khi quả bóng va chạm biên dưới
				if (_ball->getY() + _ball->getRadius() > 800) {

					_ball->reset(_paddle->getX() + _paddle->getWidth() / 2, _paddle->getY());

					player->setLife(player->getLife() - 1);
					isResetState = true;

				}
				//Kiểm soát quả bóng khi quả bóng va chạm biên trái và biên phải 
				if (_ball->getX() - _ball->getRadius() < 0 || _ball->getX() + _ball->getRadius() > 500) {
					_ball->setDegree(180 - _ball->getDegree());
				}
			}
			//Cập nhật các trạng thái va chạm của trái bóng và các vật thể có trong map

			_map.update();
			//Di chuyển trái bóng
			_ball->move();
			//Kiểm tra sự va chạm trái bóng với paddle
			if (isBoundFromPaddle() && _ball->getIsLaunch() == true) {
				int degree = (int)_ball->getDegree() % 360;
				if (degree > 0 && degree < 300) {
					degree -= 360;
				}
				//Phần bù để cho quả bóng phản xạ lại  làm cho điều kiện va chạm bị sai
				float offset = abs(_ball->getY() + _ball->getRadius() - _paddle->getY());
				_ball->setY(_ball->getY() - float(1.1) * offset);
				//Đổi hướng cho quả bóng theo chiều rơi của quả bóng
				//khi paddle có vận tốc và có va chạm thì ta
				//deltaX > 0 nghĩa là paddle đang dịch chuyển qua phải và có va chạm với quả bóng

				if (_paddle->getDeltaX() > 0 && -degree + 15 < 135) {
					_ball->setDegree(-degree + 15);
				}
				//khi quả bóng có vận tốc và di chuyển về phía bên trái
				else if (_paddle->getDeltaX() < 0 && -degree - 15 > 180 - 135) {
					_ball->setDegree(-degree - 15);

				}
				//Ngược lại khi paddle không di chuyển
				else {
					_ball->setDegree(-_ball->getDegree());
				}
				//Kiểm soát speed của trái banh ở mức tối đa 
				//speed <11
				if (_ball->getSpeed() <= 10) {

					_ball->setSpeed(_ball->getSpeed() * (float)1.1);

				}
		
			}
			//Khi trái banh đã được di chuyển ta mới cho phép di chuyển paddle
			if (_ball->getIsLaunch()) {

				_paddle->move(xMouse, _MoveLR, _ball->getX(), gameMode);
			}
		}
		//////////////////////////////////////////////////////
	//}
	}

	void handleEvents() {
		SDL_Event Events;
		SDL_PollEvent(&Events);
		if (Events.type == SDL_QUIT)
		{
			//Khi có tín hiệu người chơi thoát game
			//ta tiến hành lưu thông tin người chơi
			//sau đó lưu lại dữ liệu map đang chơi
			player->writeDataToFile();
			if (player->getLife() != 0) {
				_map.saveData();
			}
			_running = false;
		}
		else if (Events.type == SDL_KEYDOWN)
		{
			switch (Events.key.keysym.sym)
			{
				//Khi nhấn phím a nghĩa là người chơi muốn paddle di chuyển sang bên trái
			case SDLK_a:
				_MoveLR[0] = true;
				break;
				//Khi nhấn phím d nghĩa là người chơi muốn dịch chuyển paddle sang bên phải
			case SDLK_d:
				_MoveLR[1] = true;
				break;
			}
		}
		else if (Events.type == SDL_KEYUP)
		{
			switch (Events.key.keysym.sym)
			{
				//Khi không nhấn a thì khóa trạng thái di chuyển của paddle về 
				//phía bên trai
			case SDLK_a:
				_MoveLR[0] = false;
				break;
				//Khi không nhấn d thì ta khóa trạng thái di chuyển của paddle
				// về phía bên phải
			case SDLK_d:
				_MoveLR[1] = false;
				break;
			}
		}
		//Bắt sự kiện chuột
		else if (Events.type == SDL_MOUSEMOTION || Events.type == SDL_MOUSEBUTTONUP || Events.type == SDL_MOUSEBUTTONDOWN) {
			//Lấy ra tính hiệu chuột mà đưa vào hai thuộc tính xMouse và yMouse
			SDL_GetMouseState(&xMouse, &yMouse);
			switch (Events.type)
			{
				//Kiểm soát xem người chơi có nhấn chuột xuống không
				//Nếu nhấn thì ta cặp nhât mouseActionClicked là true
				//người chơi không nhấn chuột thì biến đó có giá trị là false
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
	//Trả về trạng thái hoạt động của game
	//true là game đang hoạt động
	//false là game không hoạt động
	bool getRunning() {
		return _running;
	}
};


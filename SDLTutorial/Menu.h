#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Functions.h"
using namespace std;
enum MenuButton {
	None,
	NewGame,
	Continue,
	Setting,
	Exit
};
class Menu
{
private:
	//Lưu giữ ảnh nền
	SDL_Texture* _backGround;
	//Lưu giữ biến lưu struct chứa các thông tin renderer  lên màn hình
	SDL_Renderer* renderer;
	//Lưu giữ hình ảnh button new game
	SDL_Texture* _BT_NewGame;
	//Lưu giữ hình ảnh button continue
	SDL_Texture* BT_Continue;
	//Lưu giữ hình ảnh button setting
	SDL_Texture* _BT_Setting;
	//Lưu giữ hình ảnh button exit
	SDL_Texture* _BT_Exit;
	//Lưu lại giá trị mà người chơi chọn
	// với 1 là new game
	// với 2 là continue
	// với 3 là setting
	// với 4 là exit
	MenuButton _currentChoose; // 1 New Game, 2 Continue, 3 Setting, 4 Exit
	//Lưu giữ kích thước button new game
	SDL_FRect _sizeNewGame;
	//Lưu giữ kích thước button continue 
	SDL_FRect _sizeContinue;
	//Lưu giữ kích thước nút setting
	SDL_FRect _sizeSetting;
	//Lưu giữ kích thước nút exit
	SDL_FRect _sizeExit;
	//Trạng thái đã chọn 
	//mặc định là người chơi chưa chọn 

	bool _isChose = false;
public:
	//Lấy ra trạng thái menu đã được chọn hay chưa
	bool getIsChose() {
		return _isChose;
	}
	//Thiết lập hình ảnh cho  menu
	void setImage(string NameImage) {
		_backGround = LoadImage(NameImage, renderer);
	}
	//Thiết lập font cho menu
	void setFont(string NameFont) {
		_BT_NewGame = LoadFont("NEW GAME", renderer, NameFont);
		BT_Continue = LoadFont("CONTINUE", renderer, NameFont);
		_BT_Setting = LoadFont("SETTING", renderer, NameFont);
		_BT_Exit = LoadFont("EXIT", renderer, NameFont);
	}
	//Thiết lập biến _renderer cho menu
	void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
	//Khôi phục lại menu như lúc ban đầu 
	void resetData() {
		_currentChoose = None;
		_isChose = false;
	}
	//Vẽ menu lên màn hình chơi game
	void draw(int x, int y, bool &mouseActionClick) {
		DrawInRenderer(renderer, _backGround);
		if (x > _sizeNewGame.x && x < _sizeNewGame.x + _sizeNewGame.w && y > _sizeNewGame.y && y < _sizeNewGame.y + _sizeNewGame.h) {
			_sizeNewGame.w = 250 * 1.3;
			_sizeNewGame.h = 50 * 1.3;
			DrawInRenderer(renderer, _BT_NewGame, 80, 100, 250 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				_currentChoose = NewGame;
				_isChose = true;
				mouseActionClick = false;			
			}		
		}
		else {
			_sizeNewGame.w = 250;
			_sizeNewGame.h = 50;
			DrawInRenderer(renderer, _BT_NewGame, 80, 100, 250 * 1, 50 * 1);
		}
		if (x > 80 && x < 80 + 300 && y > 200 && y < 200 + 50) {
			DrawInRenderer(renderer, BT_Continue, 80, 200, 300 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				_currentChoose = Continue;
				_isChose = true;
				mouseActionClick = false;
			}
		}
		else {
			DrawInRenderer(renderer, BT_Continue, 80, 200, 300 * 1, 50 * 1);
		}
		if (x > 80 && x < 80 + 250 && y > 300 && y < 300 + 50) {
			DrawInRenderer(renderer, _BT_Setting, 80, 300, 250 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				_currentChoose = Setting;
				_isChose = true;
				mouseActionClick = false;
			}
		}
		else {
			DrawInRenderer(renderer, _BT_Setting, 80, 300, 250 * 1, 50 * 1);
		}
		if (x > 80 && x < 80 + 150 && y >400 && y < 400 + 50) {
			DrawInRenderer(renderer, _BT_Exit, 80, 400, 150 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				_currentChoose = Exit;
				_isChose = true;
				mouseActionClick = false;
				exit(0);
			}
		}
		else {
			DrawInRenderer(renderer, _BT_Exit, 80, 400, 150 * 1, 50 * 1);
		}	
	}
	//Lấy ra loại menu mà người chơi chọn
	int getCurrentChoose() {
		return _currentChoose;
	}
	//Hàm khỏi tạo không đối số 
	Menu() {
		renderer = NULL;
		_sizeNewGame = { 80, 100, 250, 50 };
		_sizeContinue = { 80, 100, 300, 50 };
		_sizeSetting = { 80, 300, 250, 50 };
		_sizeExit = { 80, 400, 150, 50 };
		BT_Continue = NULL;
		_BT_NewGame = NULL;
		_BT_Setting = NULL;
		_BT_Exit = NULL;
		_isChose = false;
		_backGround = NULL;
		_currentChoose = None;
	}
	//Hàm hủy 
	~Menu() {
		delete _backGround,renderer, _BT_NewGame, BT_Continue, _BT_Setting,_BT_Exit;
	}
};


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
	SDL_Texture* backGround;
	//Lưu giữ biến lưu struct chứa các thông tin renderer  lên màn hình
	SDL_Renderer* renderer;
	//Lưu giữ hình ảnh button new game
	SDL_Texture* BT_NewGame;
	//Lưu giữ hình ảnh button continue
	SDL_Texture* BT_Continue;
	//Lưu giữ hình ảnh button setting
	SDL_Texture* BT_Setting;
	//Lưu giữ hình ảnh button exit
	SDL_Texture* BT_Exit;
	//Lưu lại giá trị mà người chơi chọn
	// với 1 là new game
	// với 2 là continue
	// với 3 là setting
	// với 4 là exit
	MenuButton currentChoose; // 1 New Game, 2 Continue, 3 Setting, 4 Exit
	//Lưu giữ kích thước button new game
	SDL_FRect SizeNewGame;
	//Lưu giữ kích thước button continue 
	SDL_FRect SizeContinue;
	//Lưu giữ kích thước nút setting
	SDL_FRect SizeSetting;
	//Lưu giữ kích thước nút exit
	SDL_FRect SizeExit;
	//Trạng thái đã chọn 
	//mặc định là người chơi chưa chọn 

	bool isChose = false;
public:
	//Lấy ra trạng thái menu đã được chọn hay chưa
	bool getIsChose() {
		return isChose;
	}
	//Thiết lập hình ảnh cho  menu
	void setImage(string NameImage) {
		backGround = LoadImage(NameImage, renderer);
	}
	//Thiết lập font cho menu
	void setFont(string NameFont) {
		BT_NewGame = LoadFont("NEW GAME", renderer, NameFont);
		BT_Continue = LoadFont("CONTINUE", renderer, NameFont);
		BT_Setting = LoadFont("SETTING", renderer, NameFont);
		BT_Exit = LoadFont("EXIT", renderer, NameFont);
	}
	//Thiết lập biến _renderer cho menu
	void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}
	//Khôi phục lại menu như lúc ban đầu 
	void resetData() {
		currentChoose = None;
		isChose = false;
	}
	//Vẽ menu lên màn hình chơi game
	void draw(int x, int y, bool &mouseActionClick) {
		DrawInRenderer(renderer, backGround);
		if (x > SizeNewGame.x && x < SizeNewGame.x + SizeNewGame.w && y > SizeNewGame.y && y < SizeNewGame.y + SizeNewGame.h) {
			SizeNewGame.w = 250 * 1.3;
			SizeNewGame.h = 50 * 1.3;
			DrawInRenderer(renderer, BT_NewGame, 80, 100, 250 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				currentChoose = NewGame;
				isChose = true;
				mouseActionClick = false;			
			}		
		}
		else {
			SizeNewGame.w = 250;
			SizeNewGame.h = 50;
			DrawInRenderer(renderer, BT_NewGame, 80, 100, 250 * 1, 50 * 1);
		}
		if (x > 80 && x < 80 + 300 && y > 200 && y < 200 + 50) {
			DrawInRenderer(renderer, BT_Continue, 80, 200, 300 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				currentChoose = Continue;
				isChose = true;
				mouseActionClick = false;
			}
		}
		else {
			DrawInRenderer(renderer, BT_Continue, 80, 200, 300 * 1, 50 * 1);
		}
		if (x > 80 && x < 80 + 250 && y > 300 && y < 300 + 50) {
			DrawInRenderer(renderer, BT_Setting, 80, 300, 250 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				currentChoose = Setting;
				isChose = true;
				mouseActionClick = false;
			}
		}
		else {
			DrawInRenderer(renderer, BT_Setting, 80, 300, 250 * 1, 50 * 1);
		}
		if (x > 80 && x < 80 + 150 && y >400 && y < 400 + 50) {
			DrawInRenderer(renderer, BT_Exit, 80, 400, 150 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				currentChoose = Exit;
				isChose = true;
				mouseActionClick = false;
				exit(0);
			}
		}
		else {
			DrawInRenderer(renderer, BT_Exit, 80, 400, 150 * 1, 50 * 1);
		}	
	}
	//Lấy ra loại menu mà người chơi chọn
	int getCurrentChoose() {
		return currentChoose;
	}
	//Hàm khỏi tạo không đối số 
	Menu() {
		renderer = NULL;
		SizeNewGame = { 80, 100, 250, 50 };
		SizeContinue = { 80, 100, 300, 50 };
		SizeSetting = { 80, 300, 250, 50 };
		SizeExit = { 80, 400, 150, 50 };
		BT_Continue = NULL;
		BT_NewGame = NULL;
		BT_Setting = NULL;
		BT_Exit = NULL;
		isChose = false;
		backGround = NULL;
		currentChoose = None;
	}
	//Hàm hủy 
	~Menu() {
		delete backGround,renderer, BT_NewGame, BT_Continue, BT_Setting,BT_Exit;
	}
};


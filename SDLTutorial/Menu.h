#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Functions.h"
using namespace std;
class Menu
{
private:
	SDL_Texture* backGround;
	SDL_Renderer* renderer;
	SDL_Texture* BT_NewGame;
	SDL_Texture* BT_Continue;
	SDL_Texture* BT_Setting;
	SDL_Texture* BT_Exit;
<<<<<<< HEAD
	SDL_FRect SizeNewGame;
	SDL_FRect SizeContinue;
	SDL_FRect SizeSetting;
	SDL_FRect SizeExit;
=======
>>>>>>> 8ed4979a960d86868c4f5c94c5f4598a6e12cf39
	int currentChoose; // 1 New Game, 2 Continue, 3 Setting, 4 Exit
	bool Chose = false;
public:
	bool getChose() {
		return Chose;
	}
	void setImage(string NameImage) {
		backGround = LoadImage(NameImage, renderer);
	}
	void setFont(string NameFont) {
		BT_NewGame = LoadFont("NEW GAME", renderer, NameFont);
		BT_Continue = LoadFont("CONTINUE", renderer, NameFont);
		BT_Setting = LoadFont("SETTING", renderer, NameFont);
		BT_Exit = LoadFont("EXIT", renderer, NameFont);
	}
	Menu(SDL_Renderer* Renderer) {
		renderer = Renderer;
<<<<<<< HEAD
		backGround = NULL;
		BT_Continue = NULL;
		BT_NewGame = NULL;
		BT_Exit = NULL;
		BT_Setting = NULL;
		Chose = false;
		SizeNewGame = { 80,100,250,50 };
		SizeContinue = { 80,200,300,50 };
		SizeSetting = { 80,300,250,50 };
		SizeExit = { 80,400,150,50 };
		currentChoose = 0;
	}
	void draw(int x, int y, bool mouseActionClick) {
		DrawInRenderer(renderer, backGround);
		if (x > SizeNewGame.x&& x < SizeNewGame.x + SizeNewGame.w && y > SizeNewGame.y&& y < SizeNewGame.y + SizeNewGame.h) {
			SizeNewGame.w = 250 * 1.3;
			SizeNewGame.h = 50 * 1.3;
			DrawInRenderer(renderer, BT_NewGame, &SizeNewGame);
			if (mouseActionClick) {
				currentChoose = 1;
				Chose = true;
			}
		}
		else {
			SizeNewGame.w = 250;
			SizeNewGame.h = 50;
			DrawInRenderer(renderer, BT_NewGame, &SizeNewGame);
		}
		if (x > SizeContinue.x&& x < SizeContinue.x + SizeContinue.w && y > SizeContinue.y&& y < SizeContinue.y + SizeContinue.h) {
			SizeContinue.w = 300 * 1.3;
			SizeContinue.h = 50 * 1.3;
			DrawInRenderer(renderer, BT_Continue, &SizeContinue);
			if (mouseActionClick) {
				currentChoose = 1;
				Chose = true;
			}
		}
		else {
			SizeContinue.w = 300;
			SizeContinue.h = 50;
			DrawInRenderer(renderer, BT_Continue, &SizeContinue);
		}
		if (x > SizeSetting.x&& x < SizeSetting.x + SizeSetting.w && y > SizeSetting.y&& y < SizeSetting.y + SizeSetting.h) {
			SizeSetting.w = 250 * 1.3;
			SizeSetting.h = 50 * 1.3;
			DrawInRenderer(renderer, BT_Setting, &SizeSetting);
			if (mouseActionClick) {
				currentChoose = 1;
				Chose = true;
			}
		}
		else {
			SizeSetting.w = 250;
			SizeSetting.h = 50;
			DrawInRenderer(renderer, BT_Setting, &SizeSetting);
		}
		if (x > SizeExit.x&& x < SizeExit.x + SizeExit.w && y > SizeExit.y&& y < SizeExit.y + SizeExit.h) {
			SizeExit.w = 150 * 1.3;
			SizeExit.h = 50 * 1.3;
			DrawInRenderer(renderer, BT_Exit, &SizeExit);
			if (mouseActionClick) {
				currentChoose = 1;
				Chose = true;
			}
		}
		else {
			SizeExit.w = 150;
			SizeExit.h = 50;
			DrawInRenderer(renderer, BT_Exit, &SizeExit);
		}


=======
	}
	void draw(int x, int y, bool &mouseActionClick) {
		DrawInRenderer(renderer, backGround);
		if (x > 80 && x < 80 + 250 && y > 100 && y < 100 + 50) {
			DrawInRenderer(renderer, BT_NewGame, 80, 100, 250 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				//cout << "1";
				currentChoose = 1;
				Chose = true;
				mouseActionClick = false;
			

			}		
		}
		else {
			DrawInRenderer(renderer, BT_NewGame, 80, 100, 250 * 1, 50 * 1);
		}
		if (x > 80 && x < 80 + 300 && y > 200 && y < 200 + 50) {
			DrawInRenderer(renderer, BT_Continue, 80, 200, 300 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				cout << "1";
				currentChoose = 2;
				Chose = true;
				mouseActionClick = false;
			}
		}
		else {
			DrawInRenderer(renderer, BT_Continue, 80, 200, 300 * 1, 50 * 1);
		}
		if (x > 80 && x < 80 + 250 && y > 300 && y < 300 + 50) {
			DrawInRenderer(renderer, BT_Setting, 80, 300, 250 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				currentChoose = 3;
				Chose = true;
				mouseActionClick = false;
			}
		}
		else {
			DrawInRenderer(renderer, BT_Setting, 80, 300, 250 * 1, 50 * 1);
		}
		if (x > 80 && x < 80 + 150 && y >400 && y < 400 + 50) {
			DrawInRenderer(renderer, BT_Exit, 80, 400, 150 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				currentChoose = 4;
				Chose = true;
				mouseActionClick = false;

			}
		}
		else {
			DrawInRenderer(renderer, BT_Exit, 80, 400, 150 * 1, 50 * 1);
		}
		
		
>>>>>>> 8ed4979a960d86868c4f5c94c5f4598a6e12cf39
	}
	int getCurrentChoose() {
		return currentChoose;
	}
	Menu() {
<<<<<<< HEAD
		renderer = NULL;
		backGround = NULL;
		BT_Continue = NULL;
		BT_NewGame = NULL;
		BT_Exit = NULL;
		BT_Setting = NULL;
		Chose = false;
		SizeNewGame = { 80,100,250,50 };
		SizeContinue = { 80,200,300,50 };
		SizeSetting = { 80,300,250,50 };
		SizeExit = { 80,400,150,50 };
		currentChoose = 0;
	}
	~Menu() {

=======
	}
	~Menu() {
		
>>>>>>> 8ed4979a960d86868c4f5c94c5f4598a6e12cf39
	}
};


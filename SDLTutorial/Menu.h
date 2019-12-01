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
	SDL_FRect SizeNewGame;
	SDL_FRect SizeContinue;
	SDL_FRect SizeSetting;
	SDL_FRect SizeExit;
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


	}
	int getCurrentChoose() {
		return currentChoose;
	}
	Menu() {
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

	}
};


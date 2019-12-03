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
	int currentChoose; // 1 New Game, 2 Continue, 3 Setting, 4 Exit
	SDL_FRect SizeNewGame;
	SDL_FRect SizeContinue;
	SDL_FRect SizeSetting;
	SDL_FRect SizeExit;
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
		SizeNewGame = { 80, 100, 250, 50 };
		SizeContinue = { 80, 100, 300, 50 };
		SizeSetting = { 80, 300, 250, 50 };
		SizeExit = { 80, 400, 150, 50 };
		BT_Continue = NULL;
		BT_NewGame = NULL;
		BT_Setting = NULL;
		BT_Exit = NULL;
		backGround = NULL;
		Chose = false;
		currentChoose = 0;
	}
	void draw(int x, int y, bool &mouseActionClick) {
		DrawInRenderer(renderer, backGround);
		if (x > SizeNewGame.x && x < SizeNewGame.x + SizeNewGame.w && y > SizeNewGame.y && y < SizeNewGame.y + SizeNewGame.h) {
			SizeNewGame.w = 250 * 1.3;
			SizeNewGame.h = 50 * 1.3;
			DrawInRenderer(renderer, BT_NewGame, 80, 100, 250 * 1.2, 50 * 1.2);
			if (mouseActionClick) {
				currentChoose = 1;
				Chose = true;
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
		
		
	}
	int getCurrentChoose() {
		return currentChoose;
	}
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
		Chose = false;
		backGround = NULL;
		currentChoose = 0;
	}
	~Menu() {
		
	}
};


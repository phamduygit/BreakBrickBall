#pragma once
#include "GameOver.h"
enum SettingAction {
	turnOnSpeaker,
	turnOffSpeaker,
	noneSetting,
	backToMenu,
	loadMapDiagramScreen


};
class SettingScreen:public GameOver
{
private:
	SettingAction settingAction = noneSetting;

public:
	SettingScreen(){}
	SettingScreen(SDL_Renderer* renderer) :GameOver(renderer) {
	//	settingAction = noneSetting;

	}
	void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
		settingAction = noneSetting;
	}
	void resetData() {
		settingAction = noneSetting;
	}
	void setSettingAction(SettingAction value) {
		settingAction = value;
	}
	SettingAction getSettingAction() {
		return settingAction;
	}
	void draw(int xMouse, int yMouse, bool& mouseActionClicked) {
		auto temp = image;
		image = LoadImage("SettingScreen.png", renderer);
		if (mouseActionClicked) {
			if (xMouse >= 67 && xMouse <= 67 + 76 && yMouse >= 81 && yMouse <= 81 + 76) {
				settingAction = turnOnSpeaker;

			}
			else if (xMouse >= 204 && xMouse <= 204 + 76 && yMouse >= 81 && yMouse <= 81 + 76) {
				settingAction = turnOffSpeaker;

			}
			else if (xMouse >= 367 && xMouse <= 367 + 76 && yMouse >= 81 && yMouse <= 81 + 76) {
				settingAction = loadMapDiagramScreen;


			}
			else if (xMouse >= 67 && xMouse <= 67 + 76 && yMouse >= 218 && yMouse <= 218 + 76) {
				settingAction = backToMenu;
			}
			mouseActionClicked = false;
		}
		SDL_RenderCopy(renderer,image, NULL, NULL);
		SDL_DestroyTexture(temp);
	}

};


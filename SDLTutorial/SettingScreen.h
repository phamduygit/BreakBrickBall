#pragma once
#include "GameOver.h"
#include <memory>
#define  pt shared_ptr
#define mk make_shared
enum SettingAction {
	turnOnSpeaker,
	turnOffSpeaker,
	noneSetting,
	backToMenu,
	loadMapDiagramScreen,
	playWithMouse,
	autoPlay,
	playWithKeyboard


};
class SettingScreen :public GameOver
{
private:
	SettingAction settingAction = noneSetting;

public:
	SettingScreen() {}
	SettingScreen(SDL_Renderer*& renderer) :GameOver(renderer) {
		//	settingAction = noneSetting;

	}
	void setRenderer(SDL_Renderer*& renderer) {
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
		SDL_RenderCopy(renderer, image, NULL, NULL);
		//if (mouseActionClicked) {
		if (xMouse >= 67 && xMouse <= 67 + 76 && yMouse >= 81 && yMouse <= 81 + 76) {
			SDL_Texture* speakerOn = LoadImage("SpeakerOn.png", renderer);
			//delta  10 y 10 
			DrawInRenderer(renderer, speakerOn, 57, 71, 120, 120);
			if (mouseActionClicked) {
				settingAction = turnOnSpeaker;
			}
			SDL_DestroyTexture(speakerOn);

		}
		else if (xMouse >= 204 && xMouse <= 204 + 76 && yMouse >= 81 && yMouse <= 81 + 76) {

			SDL_Texture* speakerOff = LoadImage("SpeakerOff.png", renderer);
			DrawInRenderer(renderer, speakerOff, 194, 71, 120, 120);
			if (mouseActionClicked) {
				settingAction = turnOffSpeaker;
			}
			SDL_DestroyTexture(speakerOff);

		}
		else if (xMouse >= 367 && xMouse <= 367 + 76 && yMouse >= 81 && yMouse <= 81 + 76) {
			SDL_Texture* play = LoadImage("Play.png", renderer);
			DrawInRenderer(renderer,play, 357, 71, 120, 120);
			if (mouseActionClicked) {
				settingAction = loadMapDiagramScreen;
			}
			SDL_DestroyTexture(play);

		}
		else if (xMouse >= 67 && xMouse <= 67 + 76 && yMouse >= 218 && yMouse <= 218 + 76) {
			SDL_Texture* back = LoadImage("Back.png", renderer);
			DrawInRenderer(renderer, back, 57, 208, 120, 120);
			if (mouseActionClicked) {
				settingAction = backToMenu;
			}
			SDL_DestroyTexture(back);
		}
		else if (xMouse >= 204 && xMouse <= 204 + 76 && yMouse >= 218 && yMouse <= 218 + 76) {
			SDL_Texture* googleImage = LoadImage("Google.png", renderer);
			DrawInRenderer(renderer, googleImage, 197, 208, 120, 120);
			SDL_DestroyTexture(googleImage);
		}
		else if (xMouse >= 367 && xMouse <= 367 + 76 && yMouse >= 218 && yMouse <= 218 + 76) {
			SDL_Texture* facebookImage = LoadImage("Facebook.png", renderer);
			DrawInRenderer(renderer, facebookImage, 357, 208, 120, 120);
			SDL_DestroyTexture(facebookImage);

		}
		else if (xMouse >= 67 && xMouse <= 145 && yMouse >= 350 && yMouse <= 430) {
			//
			SDL_Texture* playWithMouseTT = LoadImage("PlayWithMouse.png", renderer);
			DrawInRenderer(renderer, playWithMouseTT, 57, 340, 120, 120);
			SDL_DestroyTexture(playWithMouseTT);
			if (mouseActionClicked) {
				settingAction = playWithMouse;
			}
			
		}
		else if (xMouse >= 208 && xMouse <= 383 && yMouse >= 350 && yMouse <= 430) {
			SDL_Texture* autoPlayTT = LoadImage("AutoPlay.png", renderer);
			DrawInRenderer(renderer, autoPlayTT, 198, 340, 120, 120);
			if (mouseActionClicked) {
				settingAction = autoPlay;
			}
			SDL_DestroyTexture(autoPlayTT);
		}
		else if (xMouse >= 365 && xMouse <= 447 && yMouse >= 347 && yMouse <= 430) {
			SDL_Texture* playWithKeyboardTT = LoadImage("PlayWithKeyboard.png", renderer);
			DrawInRenderer(renderer, playWithKeyboardTT, 355, 340, 120, 120);
			if (mouseActionClicked) {
				settingAction = playWithKeyboard;
			}
			SDL_DestroyTexture(playWithKeyboardTT);

		}
			   		 	  	  	   
		mouseActionClicked = false;
		//	}

		SDL_DestroyTexture(image);
		SDL_DestroyTexture(temp);
	}

};


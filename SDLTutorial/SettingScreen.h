#pragma once
#include "GameOver.h"

enum SettingAction {
	//Bật âm thanh
	turnOnSpeaker,
	//Tắt âm thanh
	turnOffSpeaker,
	//Không có cài đặt gì hết
	noneSetting,
	//Trở lại
	backToMenu,
	//Tải mapdiagram 
	loadMapDiagramScreen,
	//Chơi bằng chuột
	playWithMouse,
	//Máy tự động chơi
	autoPlay,
	//Chơi bằng bàn phím
	playWithKeyboard


};
//Lớp SettingScreen kế thừa từ lớp GameOver
class SettingScreen :public GameOver
{

private:
	SettingAction _settingAction = noneSetting;

public:
	//Hàm khởi tạo không đối số của đối tượng
	SettingScreen() {}
	//Hàm khởi tạo có đối số của đối tượng
	SettingScreen(SDL_Renderer*& value) :GameOver(value) {
		//	settingAction = noneSetting;

	}
	//Thiết lập renderer cho đối tượng
	void setRenderer(SDL_Renderer*& renderer) {
		this->_renderer = renderer;
		_settingAction = noneSetting;
	}
	//Khôi phục tất cả các cài đặt  của đối tượng
	void resetData() {
		_settingAction = noneSetting;
	}
	//Cài đăt thuộc tính settingAction cho đối tượng
	void setSettingAction(SettingAction value) {
		_settingAction = value;
	}
	//Lấy ra thông số mà người dùng muốn cài đặt 
	SettingAction getSettingAction() {
		return _settingAction;
	}
	//Vẽ màn hình cài đặt đồng thời nhận vào các thông số chuột để thao tác
	void draw(int xMouse, int yMouse, bool& mouseActionClicked) {
		//Lưu giữ texture ở vòng lặp trước 
		//sau đó giải phóng vùng nhớ
		auto temp = _image;
		//Load hình ảnh cho biến image
		_image = LoadImage("SettingScreen.png", _renderer);
		//Copy thông tin vào renderer
		SDL_RenderCopy(_renderer, _image, NULL, NULL);
		//Nếu chuột rê vào vùng 
		//thì các vùng tương ứng sẽ phóng to lên

		if (xMouse >= 67 && xMouse <= 67 + 76 && yMouse >= 81 && yMouse <= 81 + 76) {
			SDL_Texture* speakerOn = LoadImage("SpeakerOn.png", _renderer);
			//Phóng to
			DrawInRenderer(_renderer, speakerOn, 57, 71, 120, 120);
			if (mouseActionClicked) {
				_settingAction = turnOnSpeaker;
			}
			//Giải phóng vùng nhớ cho biến con trỏ
			SDL_DestroyTexture(speakerOn);

		}
		else if (xMouse >= 204 && xMouse <= 204 + 76 && yMouse >= 81 && yMouse <= 81 + 76) {
			//Phóng to hình ảnh
			SDL_Texture* speakerOff = LoadImage("SpeakerOff.png", _renderer);
			DrawInRenderer(_renderer, speakerOff, 194, 71, 120, 120);
			if (mouseActionClicked) {
				_settingAction = turnOffSpeaker;
			}
			//Giải phòng vùng nhớ
			SDL_DestroyTexture(speakerOff);

		}
		else if (xMouse >= 367 && xMouse <= 367 + 76 && yMouse >= 81 && yMouse <= 81 + 76) {
			//Phóng to hình ảnh
			SDL_Texture* play = LoadImage("Play.png", _renderer);
			DrawInRenderer(_renderer,play, 357, 71, 120, 120);
			if (mouseActionClicked) {
				_settingAction = loadMapDiagramScreen;
			}
			//Giải phóng vùng nhớ
			SDL_DestroyTexture(play);

		}
		else if (xMouse >= 67 && xMouse <= 67 + 76 && yMouse >= 218 && yMouse <= 218 + 76) {
			SDL_Texture* back = LoadImage("Back.png", _renderer);
			//Phóng to hình ảnh
			DrawInRenderer(_renderer, back, 57, 208, 120, 120);
			if (mouseActionClicked) {
				_settingAction = backToMenu;
			}
			//Giải phóng vùng nhớ
			SDL_DestroyTexture(back);
		}
		else if (xMouse >= 204 && xMouse <= 204 + 76 && yMouse >= 218 && yMouse <= 218 + 76) {
			SDL_Texture* googleImage = LoadImage("Google.png", _renderer);
			//Phóng to hình ảnh
			DrawInRenderer(_renderer, googleImage, 197, 208, 120, 120);
			//Giải phóng vùng nhớ
			SDL_DestroyTexture(googleImage);
		}
		else if (xMouse >= 367 && xMouse <= 367 + 76 && yMouse >= 218 && yMouse <= 218 + 76) {
			SDL_Texture* facebookImage = LoadImage("Facebook.png", _renderer);
			//phóng to hình ảnh 
			DrawInRenderer(_renderer, facebookImage, 357, 208, 120, 120);
			//Giải phóng vùng nhớ
			SDL_DestroyTexture(facebookImage);

		}
		else if (xMouse >= 67 && xMouse <= 145 && yMouse >= 350 && yMouse <= 430) {
			//Phóng to hình ảnh 
			SDL_Texture* playWithMouseTT = LoadImage("PlayWithMouse.png", _renderer);
			DrawInRenderer(_renderer, playWithMouseTT, 57, 340, 120, 120);
			//Giải phóng vùng nhớ
			SDL_DestroyTexture(playWithMouseTT);
			if (mouseActionClicked) {
				_settingAction = playWithMouse;
			}
			
		}
		else if (xMouse >= 208 && xMouse <= 383 && yMouse >= 350 && yMouse <= 430) {
			SDL_Texture* autoPlayTT = LoadImage("AutoPlay.png", _renderer);
			//Phóng to hình ảnh 
			DrawInRenderer(_renderer, autoPlayTT, 198, 340, 120, 120);
			if (mouseActionClicked) {
				_settingAction = autoPlay;
			}
			//Giải phóng vùng nhớ
			SDL_DestroyTexture(autoPlayTT);
		}
		else if (xMouse >= 365 && xMouse <= 447 && yMouse >= 347 && yMouse <= 430) {
			SDL_Texture* playWithKeyboardTT = LoadImage("PlayWithKeyboard.png", _renderer);
			//Phóng to hình ảnh

			DrawInRenderer(_renderer, playWithKeyboardTT, 355, 340, 120, 120);
			if (mouseActionClicked) {
				_settingAction = playWithKeyboard;
			}
			//Giải phóng vùng nhớ
			SDL_DestroyTexture(playWithKeyboardTT);

		}
			   		 	  	  	   
		mouseActionClicked = false;
		//Giải phóng vùng nhớ tạm

		SDL_DestroyTexture(_image);
		SDL_DestroyTexture(temp);
	}

};


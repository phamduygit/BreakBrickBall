#pragma once
#include "SDL.h"
#include "Functions.h"
enum Action {
	nextMap,
	retry,
	back,
	setting,
	none
	
};
class GameOver
{
protected:
	SDL_Renderer* _renderer;
	SDL_Texture* _image;
	Action _action;

public:
	//Hàm tạo không đối số
	GameOver() {
		_action = none;
	}
	//Hàm tạo có đối số
	GameOver(SDL_Renderer*& value) {
		this->_renderer = value;
		_action = none;
	}
	//Sét struct renderer cho đối tượng
	virtual void setRenderer(SDL_Renderer*& value) {
		this->_renderer = value;
	}
	//Lấy ra hành động mà màn hình muốn Class game thực hiện
	virtual Action getAction() {
		return  _action;
	}
	//Thiết lập hành động
	//Hàm này thượng dùng để reset tránh bị chạy thẳng vào 
	//if ở vòng lặp tiếp theo gọi màn hình này 
	virtual void setAction(Action value) {
		_action = value;
	}
	//Vẽ lên màn hình chơi game đồng thời nhận vào các thông số như vị trí con trỏ chuột và 
	// hành động click chuột
	virtual void draw(int xMouse,int yMouse,bool &mouseActionClicked) {
		auto temp = _image;
		_image = loadImage("Image/GameOver.png", _renderer); 
		if (mouseActionClicked) {
			//Vùng button retry
			if (xMouse >= 210 && xMouse <= 210 + 80 && yMouse >= 390 && yMouse <= 390 + 80) {
				_action = retry;
			}
			///Vùng button back
			else if (xMouse >= 210 && xMouse <= 210 + 80 && yMouse >= 525 && yMouse <= 525 + 80) {
				_action = back;

			}
			//Vùng button setting
			else if ((xMouse >= 210 && xMouse <= 210 + 80 && yMouse >= 685 && yMouse <= 685 + 80)) {
				_action = setting;
			}

			
			
		}
		//Copy tất cả hình ảnh vào renderer		
		SDL_RenderCopy(_renderer, _image, NULL, NULL);
		//Giải phóng vùng nhớ các con trỏ tam để tránh gây ra hiện tượng
		//Memory leaks
		SDL_DestroyTexture(_image);
		SDL_DestroyTexture(temp);
		//d
		//SDL_Delay(50);
		//cout << mouseActionClicked;

		mouseActionClicked = false;
	}
	virtual ~GameOver(){}
};


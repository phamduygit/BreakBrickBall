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
	SDL_Renderer* renderer;
	SDL_Texture* image;
	Action action;

public:
	//Hàm tạo không đối số
	GameOver() {
		action = none;
	}
	//Hàm tạo có đối số
	GameOver(SDL_Renderer*& renderer) {
		this->renderer = renderer;
		action = none;
	}
	//Sét struct renderer cho đối tượng
	virtual void setRenderer(SDL_Renderer*& renderer) {
		this->renderer = renderer;
	}
	//Lấy ra hành động mà màn hình muốn Class game thực hiện
	virtual Action getAction() {
		return  action;
	}
	//Thiết lập hành động
	//Hàm này thượng dùng để reset tránh bị chạy thẳng vào 
	//if ở vòng lặp tiếp theo gọi màn hình này 
	virtual void setAction(Action value) {
		action = value;
	}
	//Vẽ lên màn hình chơi game đồng thời nhận vào các thông số như vị trí con trỏ chuột và 
	// hành động click chuột
	virtual void draw(int xMouse,int yMouse,bool &mouseActionClicked) {
		auto temp = image;
		image = LoadImage("GameOver.png", renderer); 
		if (mouseActionClicked) {
			//Vùng button retry
			if (xMouse >= 210 && xMouse <= 210 + 80 && yMouse >= 390 && yMouse <= 390 + 80) {
				action = retry;
			}
			///Vùng button back
			else if (xMouse >= 210 && xMouse <= 210 + 80 && yMouse >= 525 && yMouse <= 525 + 80) {
				action = back;

			}
			//Vùng button setting
			else if ((xMouse >= 210 && xMouse <= 210 + 80 && yMouse >= 685 && yMouse <= 685 + 80)) {
				action = setting;
			}
			mouseActionClicked = false;
		}
		//Copy tất cả hình ảnh vào renderer		
		SDL_RenderCopy(renderer, image, NULL, NULL);
		//Giải phóng vùng nhớ các con trỏ tam để tránh gây ra hiện tượng
		//Memory leaks
		SDL_DestroyTexture(image);
		SDL_DestroyTexture(temp);
	}
	virtual ~GameOver(){}
};


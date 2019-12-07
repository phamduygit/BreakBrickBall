#pragma once
#include "GameOver.h"
#include <SDL.h>
#include "Functions.h"
//Màn hình kết thúc game khi người chơi chiến thắng
class EndScreen:public GameOver
{
private:
public:
	//Hàm tạo không đối số của đối tượng
	EndScreen(){}
	//Hàm tạo nhận vào đối số renderer của đối tượng
	EndScreen(SDL_Renderer*& renderer):GameOver(renderer){}
	//Hàm vẽ đối tượng ra màn hình game
	void draw() {
		//Khởi tạo một biến tạm để lưu lại con trỏ image cũ tránh bị rò rĩ bộ nhớ

		auto tempImage = image;
		image = LoadImage("EndScreen.png", renderer);
		//Sao chép hình ảnh vào vùng nhớ mà renderer trỏ tới
		SDL_RenderCopy(renderer, image, NULL, NULL);
		//Sau khi xong tiến hành phá hủy các đối tượng
		SDL_DestroyTexture(image);
		SDL_DestroyTexture(tempImage);
	}

};


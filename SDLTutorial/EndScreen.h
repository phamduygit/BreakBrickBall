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

		auto tempImage = _image;
		_image = LoadImage("EndScreen.png", _renderer);
		//Sao chép hình ảnh vào vùng nhớ mà renderer trỏ tới
		SDL_RenderCopy(_renderer, _image, NULL, NULL);
		//Sau khi xong tiến hành phá hủy các đối tượng
		SDL_DestroyTexture(_image);
		SDL_DestroyTexture(tempImage);
	}

};


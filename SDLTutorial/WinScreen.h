#pragma once
#include "GameOver.h"
#include "Player.h"
class WinScreen :public GameOver
{
private:
	//Chứa hình ảnh các nút 
	//Nút  next
	SDL_Texture* _nextButton;
	//Nút chơi lại
	SDL_Texture* _retryButton;
	//hình ảnh số sao người chơi đặt được 
	SDL_Texture* _imageOfStar;


public:
	//Hàm khởi tạo không đối số
	WinScreen() :GameOver() {}
	//Hàm khởi tạo có đối số 
	WinScreen(SDL_Renderer*& value) :GameOver(value) {}
	//Vẽ màn hình lên màn hình game
	//nhận vào tọa độ chuột kiểm soát thao tác người chơi chọn sau khi chiến
	//thắng một vongf
	void draw(int xMouse, int yMouse, bool& mouseActionClicked) {
		auto tempImage = _image;
		auto tempNextButton = _nextButton;
		auto tempRetryButton = _retryButton;
		_nextButton = LoadImage("Next.png", _renderer);
		_retryButton = LoadImage("Retry.png", _renderer);
		_image = LoadImage("WinScreen.png", _renderer);
		SDL_Rect destinationNext, destinationRetry;
		destinationRetry.x = 69;
		destinationRetry.y = 631;
		destinationNext.x = 354;
		destinationNext.y = 631;
		destinationNext.w = destinationNext.h = destinationRetry.h = destinationRetry.w = 80;
		//cout << "Mouse" << mouseActionClicked << endl;
		if (mouseActionClicked) {
			if (xMouse >= 69 && xMouse <= 69 + 80 && yMouse >= 631 && yMouse <= 631 + 80) {
				_action = retry;
			}
			else if (xMouse >= 354 && xMouse <= 354 + 80 && yMouse >= 631 && yMouse <= 631 + 80) {
				_action = nextMap;
			}

			mouseActionClicked = false;
		}


		SDL_RenderCopy(_renderer, _image, NULL, NULL);
		SDL_DestroyTexture(_image);
		SDL_RenderCopy(_renderer, _nextButton, NULL, &destinationNext);
		SDL_DestroyTexture(_nextButton);
		SDL_RenderCopy(_renderer, _retryButton, NULL, &destinationRetry);
		SDL_DestroyTexture(_retryButton);
		SDL_DestroyTexture(tempImage);
		SDL_DestroyTexture(tempRetryButton);
		SDL_DestroyTexture(tempNextButton);
	}
	//Vẽ star

	void drawStar(int life) {
		auto imageTemp = _imageOfStar;
		SDL_Rect dest;
		dest.x = 250-210/2;
		dest.y = 172;
		dest.w = 210;
		dest.h = 90;
		switch (life)
		{
		case 1:
			_imageOfStar = LoadImage("1start.png", _renderer);
			break;
		case 2:
			_imageOfStar = LoadImage("2start.png", _renderer);
			break;
		case 3:
			_imageOfStar = LoadImage("3start.png", _renderer);
			break;
		default:
			_imageOfStar = LoadImage("1start.png", _renderer);
			break;
		}

		SDL_RenderCopy(_renderer, _imageOfStar, NULL, &dest);
		SDL_DestroyTexture(_imageOfStar);
		SDL_DestroyTexture(imageTemp);



	}
	//Hàm hủy đối tượng

	~WinScreen() {

	}

};


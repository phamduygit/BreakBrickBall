#pragma once
#include "GameOver.h"
#include "Player.h"
class WinScreen :public GameOver
{
private:
	//Chứa hình ảnh các nút 
	//Nút  next
	SDL_Texture* nextButton;
	//Nút chơi lại
	SDL_Texture* retryButton;
	//hình ảnh số sao người chơi đặt được 
	SDL_Texture* imageOfStar;


public:
	//Hàm khởi tạo không đối số
	WinScreen() :GameOver() {}
	//Hàm khởi tạo có đối số 
	WinScreen(SDL_Renderer*& renderer) :GameOver(renderer) {}
	//Vẽ màn hình lên màn hình game
	//nhận vào tọa độ chuột kiểm soát thao tác người chơi chọn sau khi chiến
	//thắng một vongf
	void draw(int xMouse, int yMouse, bool& mouseActionClicked) {
		auto tempImage = image;
		auto tempNextButton = nextButton;
		auto tempRetryButton = retryButton;
		nextButton = LoadImage("Next.png", renderer);
		retryButton = LoadImage("Retry.png", renderer);
		image = LoadImage("WinScreen.png", renderer);
		SDL_Rect destinationNext, destinationRetry;
		destinationRetry.x = 69;
		destinationRetry.y = 631;
		destinationNext.x = 354;
		destinationNext.y = 631;
		destinationNext.w = destinationNext.h = destinationRetry.h = destinationRetry.w = 80;
		//cout << "Mouse" << mouseActionClicked << endl;
		if (mouseActionClicked) {
			if (xMouse >= 69 && xMouse <= 69 + 80 && yMouse >= 631 && yMouse <= 631 + 80) {
				action = retry;
			}
			else if (xMouse >= 354 && xMouse <= 354 + 80 && yMouse >= 631 && yMouse <= 631 + 80) {
				action = nextMap;
			}

			mouseActionClicked = false;
		}


		SDL_RenderCopy(renderer, image, NULL, NULL);
		SDL_DestroyTexture(image);
		SDL_RenderCopy(renderer, nextButton, NULL, &destinationNext);
		SDL_DestroyTexture(nextButton);
		SDL_RenderCopy(renderer, retryButton, NULL, &destinationRetry);
		SDL_DestroyTexture(retryButton);
		SDL_DestroyTexture(tempImage);
		SDL_DestroyTexture(tempRetryButton);
		SDL_DestroyTexture(tempNextButton);
	}
	//Vẽ star

	void drawStar(int life) {
		auto imageTemp = imageOfStar;
		SDL_Rect dest;
		dest.x = 150;
		dest.y = 360;
		dest.w = 210;
		dest.h = 100;
		switch (life)
		{
		case 1:
			imageOfStar = LoadImage("1start.png", renderer);
			break;
		case 2:
			imageOfStar = LoadImage("2start.png", renderer);
			break;
		case 3:
			imageOfStar = LoadImage("3start.png", renderer);
			break;
		default:
			imageOfStar = LoadImage("1start.png", renderer);
			break;
		}

		SDL_RenderCopy(renderer, imageOfStar, NULL, &dest);
		SDL_DestroyTexture(imageOfStar);
		SDL_DestroyTexture(imageTemp);



	}
	//Hàm hủy đối tượng

	~WinScreen() {

	}

};


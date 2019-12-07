#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Functions.h"
#include <string>
#include "SettingScreen.h"
using namespace std;
//Đối tượng paddle
class Paddle
{
protected:
	//Tọa độ của đối tượng
	float x;
	float y;
	//Kích thước của đối tượng
	float width;
	float height;
	//Tốc độ của paddle khi người chơi chơi bằng bàn phím
	float speed;
	//Độ dịch chuyển theo phương ox
	//Nếu khoảng thời gian tương đối ngắn thì có thể xem đó là vận tốc paddle
	float deltaX;
	//Tọa độ lúc trước của paddle
	float previousX;
	//Hình ảnh của paddle
	SDL_Texture* image;
	//Biến lưu giữ các thông số sẽ render lên màn hình game
	SDL_Renderer* renderer;
	//Thể hiện của paddle
	static Paddle* instance;
	//Hàm khởi tạo không đối số
	Paddle() {
		x = 150;
		y = 700;
		width = 80;
		height = 10;
		speed = 5;
		image = NULL;
		renderer = NULL;
		deltaX = 0;
		previousX = 0;

	}
	//Hàm khởi tạo có đối số
	Paddle(SDL_Renderer*& RenderValue) {
		x = 150;
		y = 750;
		width = 150;
		height = 20;
		speed = 5;
		image = NULL;
		renderer = RenderValue;

		deltaX = 0;
		previousX = 0;

	}
public:
	//Phương thức lấy ra thể hiện của một singleton
	static Paddle* Instance(SDL_Renderer*& renderer) {
		if (instance == NULL) {
			instance = new  Paddle(renderer);

		}
		return instance;
	}
	//Lấy ra chiều cao của paddle
	float getHeight() {
		return height;
	}
	//Lấy chiều rộng của paddle
	float getWidth() {
		return width;
	}
	//Thiết lập chiều rộng cho paddle
	void setWidth(float newwidth) {
		this->width = newwidth;
	}
	//Lấy ra tọa độ x của paddle
	float getX() {
		return x;
	}
	//Thiết lập tọa độ x cho đối tượng
	void setX(float value) {
		x = value;
	}
	//Lấy ra tọa độ y của đối tượng
	float getY() {
		return y;
	}
	//Thiết lập tọa độ y cho đối tượng
	void setY(float value) {
		y = value;
	}
	//Thiết lập speed cho đối tượng
	virtual void setSpeed(float value) {
		speed = value;
	}
	//Lấy ra speed của đối tượng
	float getSpeed() {
		return speed;
	}
	//Cài đặt hình ảnh cho đối tượng
	void setImage(string name) {
		image = LoadImage(name, renderer);
	}
	//Vẽ đối tượng lên mặt phẳng chơi game
	void draw() {
		
		DrawInRenderer(renderer, image, x, y, width, height);

	}
	//Hàm di chuyển paddle
	// trong đó nhận vao đối số là chơi bằng chuột
	//hoặc là mảng gồm 2 trạng thái nhấn nút và thả nút a và d khi người chơi bằng bàn phím
	//Và chế độ máy tự chơi nhận vào thông tin của quả bóng
	void move(float xMouse, bool moveLR[], float xBall, SettingAction setting) {
		previousX = x;
		if (setting == autoPlay) {
			if (xBall - width / 2 >= 0 &&
				xBall + width / 2 <= 500) {				
					x = xBall - width / 2;				
			}

		}
		else if (setting == playWithMouse) {
			xMouse = xMouse - width / 2;
			if (xMouse < 0) {
				this->x = 0;
			}
			else if (xMouse + width > 500) {
				this->x = 500 - width;

			}
			else {
				x = xMouse;
			}
			deltaX = x - previousX;
		}
		else if (setting == playWithKeyboard) {
			if (moveLR[0]) {
				if (x > 0) {
					x -= speed;
				}
			}

			if (moveLR[1]) {
				if (x + width < 500) {
					x += speed;
				}
			}

		}
		deltaX = x - previousX;
	}
	//Lấy ra độ dời của paddle so với vị trí trước theo phương ox
	float getDeltaX() {
		return deltaX;
	}
	//Khôi phục lại deltaX
	void resetDeltaX() {
		deltaX = 0;
	}

};


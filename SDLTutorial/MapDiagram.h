#pragma once
#include <SDL.h>
#include "Functions.h"
class MapDiagram
{
private:
	//Con trỏ chứ các thông tin sẽ render lên màn hình game
	SDL_Renderer* renderer;
	//Chứa texture hình ảnh của map
	SDL_Texture* mapDiagramImage;
	//Máp đã được chọn 
	int selectedMap;
	//Máp đã unlock
	int unlockedMap;
public:
	//Hàm khỏi tạo không đối số của đối tượng
	MapDiagram() {}
	//Thiết lập biến con trỏ cho đối tượng
	void setRenderer(SDL_Renderer*& renderer) {
		this->renderer = renderer;
	}
	//Hàm khởi tạo có đối số của đối tượng
	MapDiagram(SDL_Renderer* &renderer) {
		this->renderer = renderer;
		selectedMap = 0;
	}
	//Reset lại dữ liệu
	void resetData() {
		selectedMap = 0;
	}
	//thiết lập map đã unlock cho đối tượng
	void setUnlockedMap(int value) {
		unlockedMap = value;
	}
	//Lấy ra máp đã được chon
	int getSelectedMap() {
		return selectedMap;

	}
	void setSelectedMap(int value) {
		selectedMap = value;
	}
	//Kiểm tra xem con trỏ chuột có nằm trong hình chữ nhật nào đó không
	bool isInRectangle(int xMouse, int yMouse, int x, int y, int width, int height) {
		if (xMouse >= x && xMouse <= x + width && yMouse >= y && yMouse <= y + height) {
			return true;
		}
		return false;
	}
	//Hàm vẽ màn hình map diagram lên màn hình
	//Nhận vào các biến chứa thông số của chuột
	void draw(int xMouse, int yMouse, bool& mouseActionClicked) {
		//Chứa texture trước đó lưu lại để giải phóng hạn chế tình trạng memory leaks
		auto temp = mapDiagramImage;
		mapDiagramImage = LoadImage("MapDiagram.png", renderer);
		SDL_RenderCopy(renderer, mapDiagramImage, NULL, NULL);
		//Nếu con trỏ di chuyển qua nút số 1 
		//thì ta phóng to nút số 1 khi mà click thì ta set biến selectedMap
		if (isInRectangle(xMouse, yMouse, 322, 535, (340 - 322), (575 - 535) * 1)) {
			SDL_Texture* Image1 = LoadImage("Image/1.png", renderer);
			if (unlockedMap >= 1) {
				DrawInRenderer(renderer, Image1, 322 - 10, 535 - 10, (340 - 322) * 1.6, (575 - 535) * 1.6);
				if (mouseActionClicked) {
					selectedMap = 1;
				}
			}
			SDL_DestroyTexture(Image1);
		}
		//Nếu con trỏ chuột di chuyển qua số 2 
		//thì ta phóng to nút số 1 khi mà click thì ta set biến selectedMap
		else if (isInRectangle(xMouse, yMouse, 242, 564, (272 - 242) * 1, (615 - 564) * 1)) {
			SDL_Texture* Image2 = LoadImage("Image/2.png", renderer);
			if (unlockedMap >= 2) {
				DrawInRenderer(renderer, Image2, 242 - 10, 564 - 10, (272 - 242) * 1.6, (615 - 564) * 1.6);
				if (mouseActionClicked) {
					selectedMap = 2;
				}
			}
			SDL_DestroyTexture(Image2);
		}
		//Nếu con trỏ chuột di chuyển qua số 3
		//thì ta phóng to nút số 1 khi mà click thì ta set biến selectedMap
		else if (isInRectangle(xMouse, yMouse, 153, 535, (182 - 153) * 1, (583 - 535) * 1)) {
			SDL_Texture* Image3 = LoadImage("Image/3.png", renderer);
			if (unlockedMap >= 3) {
				DrawInRenderer(renderer, Image3, 153 - 10, 535 - 10, (182 - 153) * 1.6, (583 - 535) * 1.6);
				if (mouseActionClicked) {
					selectedMap = 3;
				}
			}
			SDL_DestroyTexture(Image3);
		}
		//Nếu con trỏ chuột di chuyển qua số 4
		//thì ta phóng to nút số 1 khi mà click thì ta set biến selectedMap
		else if (isInRectangle(xMouse, yMouse, 85, 453, (130 - 85) * 1, (510 - 453) * 1)) {
			SDL_Texture* Image4 = LoadImage("Image/4.png", renderer);
			if (unlockedMap >= 4) {
				DrawInRenderer(renderer, Image4, 85 - 10, 453 - 10, (130 - 85) * 1.6, (510 - 453) * 1.6);
				if (mouseActionClicked) {
					selectedMap = 4;
				}
			}
			SDL_DestroyTexture(Image4);
		}
		//Nếu con trỏ chuột di chuyển qua số 5 
		//thì ta phóng to nút số 1 khi mà click thì ta set biến selectedMap
		else if (isInRectangle(xMouse, yMouse, 87, 332, (129 - 87) * 1, (386 - 332) * 1)) {
			SDL_Texture* Image5 = LoadImage("Image/5.png", renderer);
			if (unlockedMap >= 5) {
				DrawInRenderer(renderer, Image5, 87 - 10, 332 - 10, (129 - 87) * 1.6, (386 - 332) * 1.6);
				if (mouseActionClicked) {
					selectedMap = 5;
				}
			}
			SDL_DestroyTexture(Image5);
		}
		//Nếu con trỏ chuột di chuyển qua số 6
		//thì ta phóng to nút số 1 khi mà click thì ta set biến selectedMap
		else if (isInRectangle(xMouse, yMouse, 87, 215, (125 - 87) * 1, (266 - 215) * 1)) {
			SDL_Texture* Image6 = LoadImage("Image/6.png", renderer);
			if(unlockedMap>=6){
				DrawInRenderer(renderer, Image6, 87 - 10, 215 - 10, (125 - 87) * 1.6, (266 - 215) * 1.6);
				if (mouseActionClicked) {
					selectedMap = 6;

				}
			}
			SDL_DestroyTexture(Image6);
		}
		//Nếu con trỏ chuột di chuyển qua số 7
		//thì ta phóng to nút số 1 khi mà click thì ta set biến selectedMap
		else if (isInRectangle(xMouse, yMouse, 364, 212, (414 - 364) * 1, (281 - 212) * 1)) {
			SDL_Texture* Image7 = LoadImage("Image/7.png", renderer);
			if (unlockedMap >= 7) {
				DrawInRenderer(renderer, Image7, 364 - 10, 212 - 10, (414 - 364) * 1.6, (281 - 212) * 1.6);
				if (mouseActionClicked) {
					selectedMap = 7;
				}
			}
			SDL_DestroyTexture(Image7);
		}
		//Nếu con trỏ chuột di chuyển qua số 8
		//thì ta phóng to nút số 1 khi mà click thì ta set biến selectedMap
		else if (isInRectangle(xMouse, yMouse, 364, 334, (409 - 364) * 1, (385 - 334) * 1)) {
			SDL_Texture* Image8 = LoadImage("Image/8.png", renderer);
			if (unlockedMap >= 8) {
				DrawInRenderer(renderer, Image8, 364 - 10, 334 - 10, (409 - 364) * 1.6, (385 - 334) * 1.6);
				if (mouseActionClicked ) {
					selectedMap = 8;
				}
			}
			SDL_DestroyTexture(Image8);
		}
		//Nếu con trỏ chuột di chuyển qua số 9
		//thì ta phóng to nút số 1 khi mà click thì ta set biến selectedMap
		else if (isInRectangle(xMouse, yMouse, 366, 453, (405 - 366) * 1, (506 - 453) * 1)) {
			SDL_Texture* Image9 = LoadImage("Image/9.png", renderer);
			if ( unlockedMap >= 9) {
				DrawInRenderer(renderer, Image9, 366 - 10, 453 - 10, (405 - 366) * 1.6, (506 - 453) * 1.6);
				if (mouseActionClicked && unlockedMap >= 9) {
					selectedMap = 9;
				}
			}
			SDL_DestroyTexture(Image9);
		}
		mouseActionClicked = false;


		SDL_DestroyTexture(mapDiagramImage);
		SDL_DestroyTexture(temp);
	}
	//Hàm hủy map diagram
	~MapDiagram() {
		delete mapDiagramImage;
	}

};


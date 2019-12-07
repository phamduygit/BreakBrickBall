#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
using namespace std;
//Quản lí hình ảnh chuyển khung 
//và hình ảnh được gắn nhãn 
class TextureManager {
private:
	static TextureManager* instance;
	//Hàm khởi tạo mặc định cho đối tượng
	TextureManager() {};
	map<string, SDL_Texture*> textureMap;
public:
	//Phương thức lấy ra thể hiện của đối tượng
	static TextureManager* GetInstance() {
		if (instance == NULL) {
			instance = new  TextureManager();
		}
		return instance;

	}
	//Tải hình ảnh từ file sau đó gắn nhãn cho hình đó 
	bool load(string fileName, string id, SDL_Renderer* &renderer) {
		SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
		if (!tempSurface) {
			return false;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		//Giai phong tempSurface
		SDL_FreeSurface(tempSurface);
		if (texture) {
			textureMap[id] = texture;
			//SDL_DestroyTexture(texture);
			return true;
		}
		return false;
	}
	//Vẽ hình ảnh dựa vào id đã load từ trước theo khung 
	//với height và width điền vào sao cho chia khung một cách thích hợp
	void drawFrame(string id, float x, float y, float width, float height, int currentRow, int currentFrame, SDL_Renderer* &renderer, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		SDL_Rect source;
		SDL_FRect dest;
		source.x = int(width * (currentFrame-1));
		source.y = int(height * (currentRow - 1));
		source.w = int(width);
		source.h = int(height);
		dest.w = width;
		dest.h = height;
		dest.x = x;
		dest.y = y;
		SDL_RenderCopyExF(renderer, textureMap[id], &source, &dest, 0, 0, flip);
	}
};

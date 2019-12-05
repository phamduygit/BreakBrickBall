#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#define  pt shared_ptr
#define mk make_shared
using namespace std;
class TextureManager {
private:
	static TextureManager* instance;
	TextureManager() {};

public:

	static TextureManager* GetInstance() {
		if (instance == NULL) {
			instance = new  TextureManager();
		}
		return instance;

	}
	map<string, SDL_Texture*> textureMap;
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

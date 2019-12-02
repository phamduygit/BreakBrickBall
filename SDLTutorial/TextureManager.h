#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
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
	bool load(string fileName, string id, SDL_Renderer* renderer) {
		SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
		if (!tempSurface) {
			return false;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		if (texture) {
			textureMap[id] = texture;
			return true;
		}
		return false;

	}
	void draw(string id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		SDL_Rect source, destination;
		source.x = 0;
		source.y = 0;
		source.w = destination.w = width;
		source.h = destination.h = height;
		destination.x = x;
		destination.y = y;
		SDL_RenderCopyEx(renderer, textureMap[id], &source, &destination, 0, 0, flip);

	}
	void drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		SDL_Rect source, dest;
		source.x = width * (currentFrame-1);
		source.y = height * (currentRow - 1);
		source.w = dest.w = width;
		source.h = dest.h = height;
		dest.x = x;
		dest.y = y;
		SDL_RenderCopyEx(renderer, textureMap[id], &source, &dest, 0, 0, flip);
	}
};

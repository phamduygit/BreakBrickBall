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
		//float x, y;
		//SDL_QueryTexture(texture, NULL, NULL, &x, &y);
		//cout << x << "   " << y;
		if (texture) {
			textureMap[id] = texture;
			return true;
		}
		return false;

	}
	void draw(string id, float x, float y, float width, float height, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		cout << "call";
		SDL_FRect destination;
		SDL_Rect source;
		source.x = 0;
		source.y = 0;
		source.w = int(width);
		source.h = int(height);
		destination.w = width;
		destination.h = height;
		destination.x = x;
		destination.y = y;
		SDL_RenderCopyExF(renderer, textureMap[id], &source, &destination, 0, 0, flip);

	}
	void drawFrame(string id, float x, float y, float width, float height, float currentRow, float currentFrame, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		SDL_FRect dest;
		SDL_Rect source;
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

#include "Functions.h"

SDL_Texture* LoadImage(std::string NameImage, SDL_Renderer* Renderer) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadSurface = IMG_Load(NameImage.c_str());
	if (loadSurface == NULL) {
		std::cout << "Unable to load image " << NameImage << "! SDL_image error: " << IMG_GetError() << std::endl;
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(Renderer, loadSurface);
		if (newTexture == NULL) {
			std::cout << "Unable to create texture from " << NameImage << "! SDL error: " << SDL_GetError() << std::endl;
		}
		SDL_FreeSurface(loadSurface);
	}
	return newTexture;
}
SDL_Texture* LoadFont(std::string Text, SDL_Renderer* Renderer, std::string Font) {
	SDL_Texture* newTexture = NULL;
	TTF_Font* font = TTF_OpenFont(Font.c_str(), 200);
	if (font == NULL) {
		std::cout << "Not open ttf!" << std::endl;
	}
	SDL_Color fg = { 255, 255, 255 };

	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, Text.c_str(), fg);
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error : " << TTF_GetError() << std::endl;
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture from" << Font.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* Texture, int x, int y, int w, int h) {
	SDL_Rect Size;
	Size.x = x;
	Size.y = y;
	Size.w = w;
	Size.h = h;
	SDL_RenderCopy(Renderer, Texture, NULL, &Size);
}
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* Texture) {
	SDL_RenderCopy(Renderer, Texture, NULL, NULL);
}
#include "Functions.h"

SDL_Texture* LoadImage(string NameImage, SDL_Renderer* Renderer) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadSurface = IMG_Load(NameImage.c_str());
	if (loadSurface == NULL) {
		cout << "Unable to load image " << NameImage << "! SDL_image error: " << IMG_GetError() << endl;
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(Renderer, loadSurface);
		if (newTexture == NULL) {
			cout << "Unable to create texture from " << NameImage << "! SDL error: " << SDL_GetError() << endl;
		}
		SDL_FreeSurface(loadSurface);
	}
	return newTexture;
}
SDL_Texture* LoadFont(string Text, SDL_Renderer* Renderer, string Font) {
	SDL_Texture* newTexture = NULL;
	TTF_Font* font = TTF_OpenFont(Font.c_str(), 200);
	if (font == NULL) {
		cout << "Not open ttf!" << endl;
	}
	SDL_Color fg = { 255, 255, 255 };

	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, Text.c_str(), fg);
	if (loadedSurface == NULL)
	{
		cout << "Unable to render text surface! SDL_ttf Error : " << TTF_GetError() << endl;
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Unable to create texture from" << Font.c_str() << "! SDL Error: " << SDL_GetError() << endl;
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* Texture, float x, float y, float w, float h) {
	SDL_FRect Size;
	Size.x = x;
	Size.y = y;
	Size.w = w;
	Size.h = h;
	SDL_RenderCopyF(Renderer, Texture, NULL, &Size);
}
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* Texture, SDL_FRect Size) {
	SDL_RenderCopyF(Renderer, Texture, NULL, &Size);
}
void DrawInRendererRotate(SDL_Renderer* Renderer, SDL_Texture* Texture, float x, float y, float w, float h, float radius, float degree) {
	SDL_FRect Size;
	Size.x = x;
	Size.y = y;
	Size.w = w;
	Size.h = h;
	SDL_RenderCopyF(Renderer, Texture, NULL, &Size);
}
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* Texture) {
	SDL_RenderCopyF(Renderer, Texture, NULL, NULL);
}
Mix_Chunk* LoadSound(string filepath) {
	Mix_Chunk* Sound = Mix_LoadWAV(filepath.c_str());
	return Sound;
}
Mix_Music* LoadMusic(string filepath) {
	Mix_Music* Music = Mix_LoadMUS(filepath.c_str());
	return Music;
}
void PlaySound(Mix_Chunk* Sound) {
	Mix_PlayChannel(-1, Sound, 0);
}

void PlayMusic(Mix_Music* Music) {
	Mix_PlayMusic(Music, -1);
}

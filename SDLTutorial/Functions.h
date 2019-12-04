#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
using namespace std;
SDL_Texture* LoadImage(string NameImage, SDL_Renderer* Renderer);
SDL_Texture* LoadFont(string Text, SDL_Renderer* Renderer, string Font);
Mix_Chunk* LoadSound(string filepath);
Mix_Music* LoadMusic(string filepath);
SDL_Texture* LoadImage(string NameImage, SDL_Renderer* Renderer);
SDL_Texture* LoadFont(string Text, SDL_Renderer* Renderer, string Font);
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* &Texture, float x, float y, float w, float h);
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* &Texture, SDL_FRect Size);
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* &Texture);
void DrawInRendererRotate(SDL_Renderer* Renderer, SDL_Texture* &Texture, float x, float y, float w, float h, float radius, float degree);


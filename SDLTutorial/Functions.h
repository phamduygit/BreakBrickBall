#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;
SDL_Texture* LoadImage(string NameImage, SDL_Renderer* Renderer);
SDL_Texture* LoadFont(string Text, SDL_Renderer* Renderer, string Font);
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* Texture, int x, int y, int w, int h);
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* Texture);
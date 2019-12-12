#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
using namespace std;
//Tải hình ảnh từng file
SDL_Texture* LoadImage(string nameImage, SDL_Renderer*Renderer);
//Tải font chữ từ file .ttf
SDL_Texture* LoadFont(string text, SDL_Renderer* Renderer, string Font);
//Tải file âm thanh từ file
Mix_Chunk* LoadSound(string filePath);
//Tải file âm thanh từ file
Mix_Music* LoadMusic(string filepath);
//Tải file hình ảnh từ file
SDL_Texture* LoadImage(string NameImage, SDL_Renderer*Renderer);
//Tải file font từ file
SDL_Texture* LoadFont(string Text, SDL_Renderer* Renderer, string Font);
//Copy nội dung từ texture sang renderer
void DrawInRenderer(SDL_Renderer*Renderer, SDL_Texture* &Texture, float x, float y, float w, float h);
//Overload hàm trên copy nội dung từ texture vào renderer
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* &Texture, SDL_FRect Size);
//Overload hàm trên copy nội dung từ texture sang renderer sau đó vẽ lên toàn màn hình 
void DrawInRenderer(SDL_Renderer* Renderer, SDL_Texture* &Texture);
//Vẽ lên màn hình và xoay với gốc tương ứng
void DrawInRendererRotate(SDL_Renderer*Renderer, SDL_Texture* &Texture, float x, float y, float w, float h, float radius, float degree);


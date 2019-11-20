#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Functions.h"


SDL_Surface* _screenSurface;
SDL_Window* _window;
SDL_Renderer* _renderer;
int Width = 500;
int Height = 800;
bool _running = false;
SDL_Texture* GrassBackground;
SDL_Texture* Text;
SDL_Texture* Ball;
int main(int argc, char* argv[]) {
	// Kiểm tra xem SDL có hoạt động hay chưa và đưa ra lỗi 
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError();
		_running = false;
	}
	else {
		// Kiểm tra xem có hỗ trợ OpenGL và Direct3D không
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
			_running = false;
		}
		// Tạo cửa sỗ mới 
		_window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
		if (_window == NULL) {
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		}
		else {
			// Tạo nền cho của sổ mới 
			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
			if (_renderer == NULL) {
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
			}
			else {
				// Khỡi tạo màu nền ban dầu 
				SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				// Khỡi tạo để thực hiện tải hình ảnh
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "SDL_image could not initilialize! SDL_image Error: " << IMG_GetError() << std::endl;
				}
				// Khởi tạo để tải chữ viết lên màn hình
				if (TTF_Init()) {
					std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
				}
			}
			_running = true;
		}
		GrassBackground = LoadImage("GrassBackground.png", _renderer);
		Text = LoadFont("duy", _renderer, "LemonMilk.otf");
		Ball = LoadImage("Ball.png", _renderer);
	}
	double degrees = 0;
	while (_running) {
		SDL_Event Events;
		SDL_PollEvent(&Events);
		if (Events.type == SDL_QUIT)
		{
			_running = false;
		}
		else if (Events.type == SDL_KEYDOWN)
		{
			switch (Events.key.keysym.sym)
			{
			case SDLK_a:
				degrees -= 15;
				break;
			case SDLK_d:
				degrees += 15;
				break;
			}
		}
		SDL_RenderClear(_renderer);
		DrawInRenderer(_renderer, GrassBackground);

		DrawInRenderer(_renderer, Text, 0, 0, 100, 30);


		SDL_Rect Size = { 100, 100, 40, 120 };
		SDL_Point P = {  + 20,  + 20 };
		SDL_RenderCopyEx(_renderer, Ball, NULL, &Size, degrees, &P, SDL_FLIP_NONE);
		
		
		SDL_RenderPresent(_renderer);
	}
	return 0;
}
#include "function.h"
#include<iostream>
#include <SDL.h>
//
//bool SDL_FUNCTION::Init()
//{
//	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
//		return false;
//	gscreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
//	if (gscreen == NULL)
//		return false;
//	return true;
//}
SDL_Surface* LoadImage(string file_path) {
	SDL_Surface* load_image = NULL;
	SDL_Surface* optimize_image = NULL;

	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL) {
		optimize_image = SDL_ConvertSurfaceFormat(load_image,
			SDL_PIXELFORMAT_RGBA32,0);
		SDL_FreeSurface(load_image);
	}

	return optimize_image;
}
//void SDL_FUNCTION::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
//{
//	SDL_Rect offset;
//	offset.x = x;
//	offset.y = y;
//	SDL_BlitSurface(src, NULL, des, &offset);
//}
//void SDL_FUNCTION::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
//{
//	SDL_Rect offset;
//	offset.x = x;
//	offset.y = y;
//	SDL_BlitSurface(src, clip, des, &offset);
//}
//bool SDL_FUNCTION::ButtonStart(SDL_Event events,Point2D& button)
//{
//	int xmouse = 0;
//	int ymouse = 0;
//	if (events.type == SDL_MOUSEBUTTONDOWN)
//	{
//		if (events.button.button == SDL_BUTTON_LEFT)
//		{
//
//			xmouse = events.motion.x;
//			ymouse = events.motion.y;
//			//cout << xmouse << "," << ymouse << endl;
//			if (CheckMouseWithButton(button, xmouse, ymouse))
//				return true;
//		}
//	}
//	return false;
//}
//bool SDL_FUNCTION::CheckMouseWithButton(Point2D& button, int x, int y)
//{
//	if (x >= button.X() && x <= button.X() + WIDTH_BUTTON && y >= button.Y() && y <= button.Y() + HEIGHT_BUTTON)
//	{
//		return true;
//	}
//	return false;
//}
//void CleanUp()
//{
//	SDL_FreeSurface(gscreen);
//	SDL_FreeSurface(gbkground);
//}
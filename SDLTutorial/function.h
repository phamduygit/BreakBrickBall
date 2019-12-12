#pragma once
#include<Windows.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include<SDL_ttf.h>


using namespace std;


static SDL_Surface* gscreen = NULL;
static SDL_Surface* gbkground = NULL;
static SDL_Surface* gbkMenu = NULL;
static SDL_Event geven;

const int SCREEN_WIDTH = 340;
const int SCREEN_HEIGHT = 560;
const int SCREEN_BPP = 32;
const int HORIZONTAL_MARGIN = 12;
const int VERTICAL_MARGIN = 20;
const int WIDTH_BUTTON = 100;
const int HEIGHT_BUTTON = 37;
bool Init();
SDL_Surface* LoadImage(string file_path);
/*void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);*/
//bool ButtonStart(SDL_Event events,Point2D& button);
//bool CheckMouseWithButton(Point2D& button, int x, int y);
//void CleanUp();


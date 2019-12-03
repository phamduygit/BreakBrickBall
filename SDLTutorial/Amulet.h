#pragma once
#include "Brick.h"
#include "MagicBall.h"
enum TypeAmulet {
	Double = 2,
	Magnet = 3,
	IncreasePaddle = 4,
	IncreaseSizeBall = 5,
	HalveScore = 6,
	DecreaseSpeedBall =7,
	IncreaseLife = 8

};
class Amulet:public Brick
{
private:
	int startTime;

public:

	Amulet() { startTime = 0; }
	Amulet(SDL_Renderer* renderer, int x, int y,int typeAmulet) :Brick(renderer, x, y) {
		this->currentFrame = typeAmulet - 1;
		startTime = 0;
	}
	void setStartTime(int value) {
		startTime = value;
	}
	TypeAmulet getType() {
		int result = currentFrame + 1;
		return TypeAmulet(result);
	}
	void draw() {
		TextureManager::GetInstance()->drawFrame("Amulet", float(x), float(y), float(size), float(size), 1, currentFrame, renderer);
	}
};


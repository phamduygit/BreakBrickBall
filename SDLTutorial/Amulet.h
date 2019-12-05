#pragma once
#include "Brick.h"
#include "MagicBall.h"
#include <memory>
#define  pt shared_ptr
#define mk make_shared
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
	TypeAmulet typeAmulet;
public:

	Amulet() { startTime = 0; }
	Amulet(SDL_Renderer* &renderer, int x, int y,int typeAmulet) :Brick(renderer, x, y) {
		this->currentFrame = typeAmulet - 1;
		this->typeAmulet = TypeAmulet(typeAmulet);
		startTime = 0;
	}
	string toString() {
		stringstream out;
		out << x << " " << y << " " << int(typeAmulet);
		return out.str();
	}
	void setStartTime(int value) {
		startTime = value;
	}
	TypeAmulet getType() {
		return typeAmulet;
	}
	void draw() {
		TextureManager::GetInstance()->drawFrame("Amulet", float(x), float(y), float(size), float(size), 1, currentFrame, renderer);
	}
};


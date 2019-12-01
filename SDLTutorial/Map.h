#pragma once
#include "ListBrick.h"
class Map
{
protected:
	ListBrick listBrick;
	string dataFileName;

public:
	Map(){}
	Map(SDL_Renderer* _renderer,string dataFileName) {
		this->dataFileName = dataFileName;
		listBrick.setRenderer(_renderer);
		listBrick.createWithMapText(dataFileName);
	}
	virtual void draw() {
		listBrick.drawBrickMap();
	}
	virtual void update() {
		listBrick.handleCollision();
	}
	virtual ~Map() {}

};


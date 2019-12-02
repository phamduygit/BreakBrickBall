#pragma once
#include "ListBrick.h"
class Map
{
protected:

	ListBrick listBrick;
	string dataFileName;
	SDL_Renderer* renderer;

public:
	Map(){}
	
	Map(SDL_Renderer* _renderer,string dataFileName) {
		this->dataFileName = dataFileName;
		listBrick.setRenderer(_renderer);
		renderer = _renderer;
		listBrick.createWithMapText(dataFileName);
	}
	void loadData(string fileName) {
		listBrick.setRenderer(renderer);
		listBrick.createWithMapText(fileName);

	}
	bool isCompleted() {
		if (listBrick.getSize() == 0) {
			return true;
		}
		return false;
	}
	virtual void draw() {
		listBrick.drawBrickMap();
	}
	virtual void update() {
		listBrick.handleCollision();
	}
	virtual ~Map() {}

};


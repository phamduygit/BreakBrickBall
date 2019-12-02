#pragma once
#include "ListBrick.h"
#include "ListAmulet.h"
class Map
{
protected:

	ListBrick listBrick;
	ListAmulet listAmulet;
	string dataFileName;
	SDL_Renderer* renderer;

public:
	Map(){}
	
	Map(SDL_Renderer* _renderer,string dataFileName) {
		this->dataFileName = dataFileName;
		listBrick.setRenderer(_renderer);
		listAmulet.setRenderer(_renderer);
		renderer = _renderer;
		listBrick.createListWithMapText(dataFileName);
		listAmulet.createListWithMapText(dataFileName);
	}
	void loadData(string fileName) {
		listBrick.setRenderer(renderer);
		listBrick.createListWithMapText(fileName);
		listAmulet.createListWithMapText(fileName);

	}
	bool isCompleted() {
		if (listBrick.getSize() == 0) {
			return true;
		}
		return false;
	}
	virtual void draw() {
		listBrick.drawBrickMap();
		listAmulet.drawListAmulet();
	}
	virtual void update() {
		listBrick.handleCollision();
		listAmulet.handleCollision();
	}
	int getNumberOfBrick() {
		return listBrick.getSize();
	}
	virtual ~Map() {}

};


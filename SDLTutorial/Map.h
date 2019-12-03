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
	Map(){
		renderer = NULL;
	}
	
	Map(SDL_Renderer* _renderer,string dataFileName) {
		this->dataFileName = dataFileName;
		listBrick.setRenderer(_renderer);
		listAmulet.setRenderer(_renderer);
		renderer = _renderer;
		listBrick.createListWithMapText(dataFileName);
		listAmulet.createListWithMapText(dataFileName);
	}
	void loadData(string fileName) {
		listBrick.ClearMap();
		listAmulet.clearAllAmulet();
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
		int limitTime = 6000;
		//d
		cout << listAmulet.getTime()<<endl;
		map<string, bool> mapEffect = listAmulet.getMapEffect();
		if (listAmulet.getTime() >= limitTime) {
		
			if (mapEffect["Magnet"]) {
				cout << "Magnet" << endl;
				listAmulet.resetMagnet();
			}
			if (mapEffect["IncreasePaddle"]) {
				listAmulet.resetWidthPaddle();

			}
			if (mapEffect["IncreaseSizeBall"]) {
				listAmulet.resetSizeBall();
			}
			if (mapEffect["SlowSpeed"]) {
				cout << "SlowSpeed\n";
				listAmulet.resetSpeed();
			}
			if (mapEffect["Double"]) {
				listAmulet.resetDoubleScore();
			}
			if (mapEffect["HalveScore"]) {
				listAmulet.resetHalveScore();
			}
			

		}
	}
	int getNumberOfBrick() {
		return listBrick.getSize();
	}
	virtual ~Map() {}

};


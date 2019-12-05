#pragma once
#include "ListBrick.h"
#include "ListAmulet.h"
#include <fstream>
#include <memory>
#define  pt shared_ptr
#define mk make_shared


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

	void turnOffMusic() {
		listBrick.setIsMusicOn(false);
	}
	void saveData() {
		fstream file("MapSavedData.txt",ios::out);
		file << listBrick.toString()<<endl << listAmulet.toString();
		file.close();
		
	}
	void clearMap() {
		listAmulet.clearAllAmulet();
		listBrick.clearAllBrick();
	}
	void loadData() {
		fstream file("MapSavedData.txt", ios::in);
		if (!file) {
			cout << "\nFile not found";
			return;
		}
		string buffer;
		vector <string> token;
		while (!file.eof()) {
			getline(file, buffer);
			if (buffer == "") {
				break;
			}
			stringstream source(buffer);
			while (getline(source, buffer, ' ')) {
				token.push_back(buffer);
			}
			Brick *brick = new Brick(renderer, stoi(token[0]), stoi(token[1]));
			brick->setFrame(stoi(token[2]));
			listBrick.addBrick(*brick);
			delete brick;
			token.clear();

		}
		while (!file.eof()) {
			getline(file, buffer);
			if (buffer == "") {
				break;
			}
			stringstream source(buffer);
			while (getline(source, buffer, ' ') ){
				token.push_back(buffer);
			}
			Amulet* amulet = new Amulet(renderer, stoi(token[0]), stoi(token[1]), stoi(token[2]));
			listAmulet.addAmulet(*amulet);
			delete amulet;
			token.clear();
		}

	}
	void turnOnMusic() {
		listBrick.setIsMusicOn(true);
	}
	Map(SDL_Renderer* &_renderer,string dataFileName) {
		this->dataFileName = dataFileName;
		listBrick.setRenderer(_renderer);
		listAmulet.setRenderer(_renderer);
		renderer = _renderer;
		listBrick.createListWithMapText(dataFileName);
		listAmulet.createListWithMapText(dataFileName);
	}
	void loadData(string fileName) {
		listBrick.clearAllBrick();
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
		//cout << listAmulet.getTime()<<endl;
		map<string, bool> mapEffect = listAmulet.getMapEffect();
		if (listAmulet.getTime() >= limitTime) {
		
			if (mapEffect["Magnet"]) {
				//cout << "Magnet" << endl;
				listAmulet.resetMagnet();
			}
			if (mapEffect["IncreasePaddle"]) {
				listAmulet.resetWidthPaddle();

			}
			if (mapEffect["IncreaseSizeBall"]) {
				listAmulet.resetSizeBall();
			}
			if (mapEffect["SlowSpeed"]) {
				//cout << "SlowSpeed\n";
				listAmulet.resetSpeed();
			}
			if (mapEffect["Double"]) {
				listAmulet.resetDoubleScore();
			}
			if (mapEffect["HalveScore"]) {
				listAmulet.resetHalveScore();
			}
			

		}
		mapEffect.clear();
	}
	int getNumberOfBrick() {
		return listBrick.getSize();
	}
	virtual ~Map() {
	}

};


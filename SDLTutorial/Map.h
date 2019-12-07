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
	//Đối tượng chứa danh sách những viên gạch
	ListBrick listBrick;
	//Đối tượng chứa danh sách bùa 
	ListAmulet listAmulet;
	//Tên file chứa tên máp
	string dataFileName;
	//Biến renderer
	SDL_Renderer* renderer;

public:
	//Hàm khỏi tạo không đối số 
	Map(){
		renderer = NULL;
	}
	//hàn động tắt nhạc
	void turnOffMusic() {
		listBrick.setIsMusicOn(false);
	}
	//Lưu dữ liệu cho game khi người chơi thoát khỏi game
	void saveData() {
		fstream file("MapSavedData.txt",ios::out);
		file << listBrick.toString()<<endl << listAmulet.toString();
		file.close();
		
	}
	//Xóa tất cả các item xuất hiên trên màn hình
	void clearMap() {
		listAmulet.clearAllAmulet();
		listBrick.clearAllBrick();
	}
	//Tải dữ liệu
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
			Amulet* amulet = new Amulet(renderer, stoi(token[0]), stoi(token[1]), TypeAmulet(stoi(token[2])));
			listAmulet.addAmulet(*amulet);
			delete amulet;
			token.clear();
		}

	}
	//Bật nhạc khi bóng chạm vào gạch
	void turnOnMusic() {
		listBrick.setIsMusicOn(true);
	}
	//Hàm khởi tạo cho đối tượng có đối số
	Map(SDL_Renderer* &_renderer,string dataFileName) {
		this->dataFileName = dataFileName;
		listBrick.setRenderer(_renderer);
		listAmulet.setRenderer(_renderer);
		renderer = _renderer;
		listBrick.createListWithMapText(dataFileName);
		listAmulet.createListWithMapText(dataFileName);
	}
	//Tải dữ liệu từ file
	void loadData(string fileName) {
		listBrick.clearAllBrick();
		listAmulet.clearAllAmulet();
		listBrick.setRenderer(renderer);
		listBrick.createListWithMapText(fileName);
		listAmulet.createListWithMapText(fileName);

	}
	//Kiểm tra xem map còn gạch không
	bool isCompleted() {
		if (listBrick.getSize() == 0) {
			return true;
		}
		return false;
	}
	//Vẽ gạch lên màn hình game
	virtual void draw() {
		listBrick.drawBrickMap();
		listAmulet.drawListAmulet();
	}
	//Cập nhật các trạng thái  các list
	virtual void update() {
		listBrick.handleCollision();
		listAmulet.handleCollision();
		int limitTime = 6000;
		//d
		//cout << listAmulet.getTime()<<endl;
		map<string, bool> mapEffect = listAmulet.getMapEffect();
		//Thời gian giơi hạn là 6s sau khi hết thời gian giới hạn thì ta 
		//reset các biến chứa thuộc tính đồng thời trả lại trạng thái trước đó cho người chơi
		if (listAmulet.getTime() >= limitTime) {
		
			if (mapEffect["Magnet"]) {
				listAmulet.resetMagnet();
			}
			if (mapEffect["IncreasePaddle"]) {
				listAmulet.resetWidthPaddle();

			}
			if (mapEffect["IncreaseSizeBall"]) {
				listAmulet.resetSizeBall();
			}
			if (mapEffect["SlowSpeed"]) {
				listAmulet.resetSpeed();
			}
			if (mapEffect["Double"]) {
				listAmulet.resetDoubleScore();
			}
			if (mapEffect["HalveScore"]) {
				listAmulet.resetHalveScore();
			}
		}
		//Do biên mapEffect dùng để chứa dữ liệu lấy từ hàm nên sau khi dùng ta giải 
		//phóng để tránh rò rĩ bộ nhớ 
		mapEffect.clear();
	}
	//lấy ra số lương gạch hiện có 
	int getNumberOfBrick() {
		return listBrick.getSize();
	}
	
	virtual ~Map() {
	}

};


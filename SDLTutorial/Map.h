#pragma once
#include "ListBrick.h"
#include "ListAmulet.h"
#include <fstream>
#include <memory>
#define  pt shared_ptr
#define mk make_shared


class Map
{
private:
	//Đối tượng chứa danh sách bùa 
	ListAmulet _listAmulet;
protected:
	//Đối tượng chứa danh sách những viên gạch
	ListBrick _listBrick;	
	//Tên file chứa tên máp
	string _dataFileName;
	//Biến renderer
	SDL_Renderer* _renderer;

public:
	//Hàm khỏi tạo không đối số 
	Map(){
		_renderer = NULL;
	}
	//hàn động tắt nhạc
	virtual void turnOffMusic() {
		_listBrick.setIsMusicOn(false);
	}
	//Lưu dữ liệu cho game khi người chơi thoát khỏi game
	void saveData() {
		fstream file("MapSavedData.txt",ios::out);
		file << _listBrick.toString()<<endl << _listAmulet.toString();
		file.close();
		
	}
	//Xóa tất cả các item xuất hiên trên màn hình
	void clearMap() {
		_listAmulet.clearAllAmulet();
		_listBrick.clearAllBrick();
	}
	//Tải dữ liệu từ dữ liệu ở lần chơi trước 
	void loadData() {
		_listAmulet.clearAllAmulet();
		_listBrick.clearAllBrick();
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
			Brick *brick = new Brick(_renderer, stoi(token[0]), stoi(token[1]));
			brick->setFrame(stoi(token[2]));
			_listBrick.addBrick(*brick);
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
			Amulet* amulet = new Amulet(_renderer, stoi(token[0]), stoi(token[1]), TypeAmulet(stoi(token[2])));
			_listAmulet.addAmulet(*amulet);
			delete amulet;
			token.clear();
		}

	}
	//Bật nhạc khi bóng chạm vào gạch
	virtual void turnOnMusic() {
		_listBrick.setIsMusicOn(true);
	}
	//Hàm khởi tạo cho đối tượng có đối số
	Map(SDL_Renderer* &value,string dataFileName) {
		this->_dataFileName = dataFileName;
		this->_renderer = value;
		_listBrick.setRenderer(value);
		_listAmulet.setRenderer(value);		
		_listBrick.createListWithMapText(dataFileName);
		_listAmulet.createListWithMapText(dataFileName);
	}
	//Tải dữ liệu từ file
	virtual void loadData(string fileName) {
		_listBrick.clearAllBrick();
		_listAmulet.clearAllAmulet();
		_listBrick.setRenderer(_renderer);
		_listBrick.createListWithMapText(fileName);
		_listAmulet.createListWithMapText(fileName);

	}
	//Kiểm tra xem map còn gạch không
	bool isCompleted() {
		if (_listBrick.getSize() == 0) {
			return true;
		}
		return false;
	}
	//Vẽ gạch lên màn hình game
	void draw() {
		_listBrick.drawBrickMap();
		_listAmulet.drawListAmulet();
	}
	//Cập nhật các trạng thái  các list
	virtual void update() {

		_listBrick.handleCollision();
		_listAmulet.handleCollision();
		int limitTime = 6000;
		//d
		//cout << listAmulet.getTime()<<endl;
		map<string, bool> mapEffect = _listAmulet.getMapEffect();
		//Thời gian giơi hạn là 6s sau khi hết thời gian giới hạn thì ta 
		//reset các biến chứa thuộc tính đồng thời trả lại trạng thái trước đó cho người chơi
		if (_listAmulet.getTime() >= limitTime) {
		
			if (mapEffect["Magnet"]) {
				_listAmulet.resetMagnet();
			}
			if (mapEffect["IncreasePaddle"]) {
				_listAmulet.resetWidthPaddle();

			}
			if (mapEffect["IncreaseSizeBall"]) {
				_listAmulet.resetSizeBall();
			}
			if (mapEffect["SlowSpeed"]) {
				_listAmulet.resetSpeed();
			}
			if (mapEffect["Double"]) {
				_listAmulet.resetDoubleScore();
			}
			if (mapEffect["HalveScore"]) {
				_listAmulet.resetHalveScore();
			}
		}
		//Do biên mapEffect dùng để chứa dữ liệu lấy từ hàm nên sau khi dùng ta giải 
		//phóng để tránh rò rĩ bộ nhớ 
		mapEffect.clear();
	}
	//lấy ra số lương gạch hiện có 
	int getNumberOfBrick() {
		return _listBrick.getSize();
	}
	
	virtual ~Map() {
	}

};


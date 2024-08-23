#pragma once


/*
�����ͣ�
	�������ǣ���δ����������磺
	����ģʽ������ģʽ��Builder������ģʽ
*/

#include<string>
using std::string;

//������ģʽ
class House {
public:
	string wall;
	string tile;
	string window;
};

class HouseBuilder {
public:
	virtual House* GetHouse() = 0;

	virtual void setWall(const string& str) = 0;
	virtual void setWindow(const string& str) = 0;
	virtual void setTile(const string& str) = 0;

};
class HouseBuilderApp :public HouseBuilder{
private:
	House* house;//����Ľӿ�
public:
	HouseBuilderApp() {
		house = new House();
	}
public:
	void setWall(const string& str) override {
		house->wall = str;
	}
	void setWindow(const string& str) override {
		house->window = str;
	}
	void setTile(const string& str) override {
		house->tile = str;
	}
public:
	House* GetHouse() override {//����Ľӿ�
		return house;
	}
};
//
//int main() {
//	HouseBuilderApp* app = new HouseBuilderApp();
//	app->setTile("tile_1");
//	//app->setWindow("window_1");
//
//	House* house = app->GetHouse();
//}

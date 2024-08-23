#pragma once


/*
创建型：
	描述的是：如何创建对象，例如：
	单例模式、工厂模式、Builder构建者模式
*/

#include<string>
using std::string;

//构建者模式
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
	House* house;//对外的接口
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
	House* GetHouse() override {//对外的接口
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

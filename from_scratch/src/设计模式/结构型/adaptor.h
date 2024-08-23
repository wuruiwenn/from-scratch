#pragma once
#include<iostream>
using std::cout;

/*
适配器：
	将某接口功能，适配为，所需要的接口功能
*/

//（将被）适配者
//已经存在的原始接口
//相当于 STL deque 双向线性结构
class Adaptee {
public:
	void specRequest() {
		cout << "Adaptee spec Request.\n";
	}
};

//需要适配得到的 目标接口函数 (所属于的基类)
class Target {
public:
	virtual void request() = 0;//相当于STL一些接口函数，如pop、push
};

//适配器，完成适配工作
//相当于 STL stack、queue
class Adaptor: public Target {
private:
	Adaptee* adaptee;//将等待被适配 的目标对象 作为 适配者的 成员属性
public:
	Adaptor(Adaptee* a) :adaptee(a) {

	}
public:
	void request() override {//定制(适配) 接口函数
		adaptee->specRequest();
	}
	//...
};
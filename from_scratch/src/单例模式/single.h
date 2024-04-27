#pragma once


class Single {
private:
	Single();
	static Single ins;//单例的声明
public:
	static Single* GetIns();
	//static Single& GetIns();//指针，引用都可以
};
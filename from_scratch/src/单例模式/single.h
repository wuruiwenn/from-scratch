#pragma once


class Single {
private:
	Single();
	static Single ins;//����������
public:
	static Single* GetIns();
	//static Single& GetIns();//ָ�룬���ö�����
};
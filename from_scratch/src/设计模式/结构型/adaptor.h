#pragma once
#include<iostream>
using std::cout;

/*
��������
	��ĳ�ӿڹ��ܣ�����Ϊ������Ҫ�Ľӿڹ���
*/

//��������������
//�Ѿ����ڵ�ԭʼ�ӿ�
//�൱�� STL deque ˫�����Խṹ
class Adaptee {
public:
	void specRequest() {
		cout << "Adaptee spec Request.\n";
	}
};

//��Ҫ����õ��� Ŀ��ӿں��� (�����ڵĻ���)
class Target {
public:
	virtual void request() = 0;//�൱��STLһЩ�ӿں�������pop��push
};

//��������������乤��
//�൱�� STL stack��queue
class Adaptor: public Target {
private:
	Adaptee* adaptee;//���ȴ������� ��Ŀ����� ��Ϊ �����ߵ� ��Ա����
public:
	Adaptor(Adaptee* a) :adaptee(a) {

	}
public:
	void request() override {//����(����) �ӿں���
		adaptee->specRequest();
	}
	//...
};

#include<iostream>
#include"./impl/����ָ��/unique_ptr.h"

int main() {
	
	Entity* e = new Entity(12);
	wrw::unique_ptr<Entity> up(e);
	cout << "e = " << e << endl;
	cout << "up = " << up << endl;

	//������
}
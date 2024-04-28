
#include<iostream>
#include"./type_traits/type_traits.h"
#include"./����ָ��/unique_ptr.h"
#include"./����ģʽ/single.h"
#include"./���ݽṹ/single_list.h"

class User {
	int id;
public:
	User(int d):id(d){}
	explicit operator bool() {
		return id != 0;
	}
	friend std::ostream& operator<<(std::ostream& out, const User& u);
};
std::ostream& operator<<(std::ostream& out, const User& u) {
	out << "[user:" << u.id << "]\n";
	return out;
}

int main() {
	using namespace wrw;
	SingleList* s = new SingleList();
	for (int i = 1; i <= 5; i++)
	{
		s->addLast(i);
	}
	cout << *s;
	cout << "reverse...\n";
	s->reverse();
	cout << *s;

}
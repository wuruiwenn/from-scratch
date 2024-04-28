
#include<iostream>
#include"./type_traits/type_traits.h"
#include"./智能指针/unique_ptr.h"
#include"./单例模式/single.h"
#include"./数据结构/single_list.h"

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
	s->addLast(1);
	s->addLast(3);
	s->addLast(3);
	s->addLast(3);
	s->removeVal(3);
	cout << *s;
	cout << "size = " << s->GetSize();

}
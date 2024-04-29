
#include<iostream>
#include"./type_traits/type_traits.h"
#include"./智能指针/unique_ptr.h"
#include"./单例模式/single.h"
#include"./数据结构/single_list.h"
#include"./数据结构/string.h"

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
	/*SingleList* s = new SingleList();
	for (int i = 1; i <= 5; i++)
	{
		s->addLast(i);
	}
	cout << *s;
	cout << "reverse...\n";
	s->reverse();
	cout << *s;*/
	String s("abcdef");
	String s1(s);//执行之前，s1此时并没有被构造出来，正是通过s来构造s1的

	String s2("DEG");
	String s3("XYZ");
	s2 = s3;

	cout << s;
	cout << s1;
	cout << s2;
	cout << s3;

	cout << "...\n";
	String s5("ABCDEF");
	String s6(std::move(s5));

	if (s5) {
		cout << "s5 = " << s5;
	}else {
		cout << "s5 NULL\n";
	}
	if (s6) {
		cout << "s6 = " << s6;
	}else {
		cout << "s6 NULL\n";
	}
	cout << ".........\n";
	String s7("ABCDEF");
	String s8("abcdef");
	s7 = std::move(s8);
	if (s7) {
		cout << "s7 = " << s7;
	}
	else {
		cout << "S7 NULL\n";
	}

	if (s8) {
		cout << "s8 = " << s8;
	}
	else {
		cout << "s8 NULL\n";
	}
}
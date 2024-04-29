
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

//拷贝构造函数调用的场景
void transObj(wrw::String s) {
	cout << "s = " << s;
}
wrw::String& returObj() {
	wrw::String s("DEF");
	return s;//此处应该是会先默认调用move构造，没有则调用拷贝构造
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

	//String s("abcdef");
	//String s1(s);//执行之前，s1此时并没有被构造出来，正是通过s来构造s1的

	//cout << " s = " << s;
	//cout << "s1 = " << s1;
	//String s1 = returObj();
	//cout << "s1 = " << s1;
	String s("anc");
	String s1("dd");
	s = s1;
}
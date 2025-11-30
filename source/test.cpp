
#include<iostream>
#include"./type_traits/type_traits.h"
#include"./智能指针/unique_ptr.h"
#include"./单例模式/single.h"
#include"./数据结构/single_list.h"
#include"./数据结构/string.h"
#include"STL/single_with_iterator.h"

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
	using wrw::string;
	string s("abcdef");
	//string::iterator it = s.begin();
	for (string::iterator it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}
	cout << endl << endl;
	for (const auto& cur : s) {
		cout << cur << " ";
	}
	cout << endl;
}
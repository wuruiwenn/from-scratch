
#include<iostream>
#include"./type_traits/type_traits.h"
#include"./����ָ��/unique_ptr.h"
#include"./����ģʽ/single.h"
#include"./���ݽṹ/single_list.h"
#include"./���ݽṹ/string.h"
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

//�������캯�����õĳ���
void transObj(wrw::String s) {
	cout << "s = " << s;
}
wrw::String& returObj() {
	wrw::String s("DEF");
	return s;//�˴�Ӧ���ǻ���Ĭ�ϵ���move���죬û������ÿ�������
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
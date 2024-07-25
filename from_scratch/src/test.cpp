
#include<iostream>
#include"./type_traits/type_traits.h"
#include"./����ָ��/unique_ptr.h"
#include"./����ģʽ/single.h"
#include"./���ݽṹ/single_list.h"
#include"./���ݽṹ/string.h"
#include"./STL/string.h"

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
	string s("abc");
	cout << s.c_str() << endl;
	string s1;
	cout << s1.c_str() << endl;

	cout << s[2] << endl;
	s[1] = '&';
	cout << s.c_str() << endl;
}

#include<iostream>
#include"./type_traits/type_traits.h"
#include"./����ָ��/unique_ptr.h"
#include"./����ģʽ/single.h"
#include"./���ݽṹ/single_list.h"
#include"./���ݽṹ/string.h"

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
	//String s1(s);//ִ��֮ǰ��s1��ʱ��û�б��������������ͨ��s������s1��

	//cout << " s = " << s;
	//cout << "s1 = " << s1;
	//String s1 = returObj();
	//cout << "s1 = " << s1;
	String s("anc");
	String s1("dd");
	s = s1;
}
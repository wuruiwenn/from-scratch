
#include<iostream>
#include"./智能指针/unique_ptr.h"
#include"./type_traits/type_traits.h"

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
#include"./单例模式/single.h"
int main() {

	Single* s1 = Single::GetIns();
	Single* s2 = Single::GetIns();
	cout << s1 << endl;//00007FF65CF6E160
	cout << s2 << endl;//00007FF65CF6E160
}
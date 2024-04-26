
#include<iostream>
#include"./÷«ƒ‹÷∏’Î/unique_ptr.h"
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
int main() {

	//Entity* e = new Entity(12);
	////Entity* e2 = new Entity(24);
	//wrw::unique_ptr<Entity> p(e);
	//p.reset();
	//using namespace wrw;
	//wrw::unique_ptr<Entity> up;
	//wrw::unique_ptr<Entity> up1();
	//wrw::unique_ptr<Entity> up2(new Entity(9));

	//≤‚ ‘type_traits.h
	//cout << wrw::is_int<int>::value << endl;
	//cout << wrw::is_int<float>::value << endl;
	//cout << wrw::is_int<const int>::value << endl;
	//cout << wrw::is_int_helper<const int>::value << endl;

	
	//wrw::unique_ptr<Entity> up(e);
	//cout << "e = " << e << endl;
	//cout << "up = " << up << endl;
	/*Entity* e = new Entity(12);
	Entity* e2 = new Entity(24);

	wrw::unique_ptr<Entity> up1(e);
	up1.reset();
	wrw::unique_ptr<Entity> up2(e2);
	cout << "*e = " << *e;
	cout << "*up1 = " << *up1;
	cout << "*up2 = " << *up2;
	cout << "*e2 = " << *e2;
	up1.swap(up2);
	cout << "swap....\n";
	cout << "*e = " << *e;
	cout << "*up1 = " << *up1;
	cout << "*up2 = " << *up2;
	cout << "*e2 = " << *e2;*/
	/*wrw::unique_ptr<Entity> up(e);
	up.reset();*/

	//cout << "*e = " << *e;
	////cout << "*e1 = " << *e1;
	//cout << "*up = " << *up;
	//std::unique_ptr<Entity> up(e);
	//up.reset();
	//cout << "*up = " << *up;
	Entity* e = new Entity(2);
	cout << "*e = " << *e;
	std::unique_ptr<Entity> up(e);
	up.reset();
	cout << "*e = " << *e;
	cout << "*up="<<*up;
}
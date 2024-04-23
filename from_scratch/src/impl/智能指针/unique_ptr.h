#pragma once
#include<iostream>

class Entity {
private:
	int id;
public:
	Entity(int d) :id(d) { std::cout << "Entity构造\n"; }
	~Entity() { std::cout << "Entity析构\n"; }
	friend std::ostream& operator<<(std::ostream& out, const Entity& obj);
};
std::ostream& operator<<(std::ostream& out, const Entity& obj) {
	out << "[" << obj.id << "]\n";
	return out;
}
namespace wrw
{
	template<class T>
	class unique_ptr {
	private:
		T* obj;
	public:

		//构造
		unique_ptr() :obj(nullptr) {}
		unique_ptr(T* _obj = nullptr) :obj(_obj) {}

		//析构
		~unique_ptr() {
			delete obj;
		}

		//解引用*运算符
		T& operator*() const {
			return *obj;
		}

		//成员访问 -> 运算符
		T* operator->() {
			return obj;
		}

		friend std::ostream& operator<<(std::ostream& out, const unique_ptr<T>& up);

		// 删除 拷贝构造函数 和 "="赋值操作符，禁止复制
		unique_ptr& operator=(const unique_ptr& other) = delete;
		unique_ptr(const unique_ptr& other) = delete;
	};
	template<class T>
	std::ostream& operator<<(std::ostream& out, const unique_ptr<T>& up) {
		out << up.obj;
		return out;
	}
}

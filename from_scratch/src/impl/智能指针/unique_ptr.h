#pragma once
#include<iostream>

class Entity {
private:
	int id;
public:
	Entity(int d) :id(d) { std::cout << "Entity����\n"; }
	~Entity() { std::cout << "Entity����\n"; }
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

		//����
		unique_ptr() :obj(nullptr) {}
		unique_ptr(T* _obj = nullptr) :obj(_obj) {}

		//����
		~unique_ptr() {
			delete obj;
		}

		//������*�����
		T& operator*() const {
			return *obj;
		}

		//��Ա���� -> �����
		T* operator->() {
			return obj;
		}

		friend std::ostream& operator<<(std::ostream& out, const unique_ptr<T>& up);

		// ɾ�� �������캯�� �� "="��ֵ����������ֹ����
		unique_ptr& operator=(const unique_ptr& other) = delete;
		unique_ptr(const unique_ptr& other) = delete;
	};
	template<class T>
	std::ostream& operator<<(std::ostream& out, const unique_ptr<T>& up) {
		out << up.obj;
		return out;
	}
}

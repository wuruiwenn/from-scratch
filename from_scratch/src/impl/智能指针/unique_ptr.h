#pragma once

#include<iostream>

using std::cout;
using std::endl;

class Entity {
private:
	int id;
public:
	Entity(int d) :id(d) { cout << "Entity构造\n"; }
	~Entity() { cout << "Entity析构\n"; }
	void printId() { cout << "printId = " << id << endl; }
	friend std::ostream& operator<<(std::ostream& out, const Entity& obj);
};
std::ostream& operator<<(std::ostream& out, const Entity& obj) {
	out << "[Entity: " << obj.id << "]\n";
	return out;
}
namespace wrw
{
	template<class T>
	class unique_ptr {
	private:
		T* obj;
	public:

		//构造函数
		unique_ptr() :obj(nullptr) {
		}
		unique_ptr(T* ptr) :obj(ptr) {
		}

		//析构函数
		~unique_ptr() {
			delete obj;
		}

		//移动构造函数
		unique_ptr(unique_ptr&& other) noexcept {
			this->obj = other.obj;
			other.obj = nullptr;
		}

		//移动=赋值运算符
		unique_ptr& operator=(unique_ptr&& other) noexcept {
			if (this != &other) {//如果不是同一个对象才..，避免自赋值
				delete obj;//接管新的资源之前，要把之前的资源释放掉
				this->obj = other.obj;
				other.obj = nullptr;
			}
			return *this;
		}


		//解引用*运算符
		T& operator*() {
			return *obj;
		}

		//成员访问 -> 运算符
		T* operator->() {
			return obj;
		}

		//get()：返回绑定对象的原始指针，智能指针的控制权不变
		//注意这里const要和 operator<<重载函数内的参数 const统一，否则会"丢失限定符const"
		T* get() const {
			return obj;
		}

		//release()：返回绑定对象的原始指针，并将智能指针的控制权置空
		T* release() {
			T* tmp = obj;
			//delete obj; 不能用delete，否则目标对象本身会被释放
			obj = nullptr;//让当前智能指针不再持有该目标对象即可
			return tmp;
		}

		//允许unique_ptr的对象隐式转换为一个bool类型 ，if(up){}
		operator bool() {
			return obj != nullptr;
		}

		//reset()：释放所持有的目标对象，可接受一个可选的参数，就是即将要接管的新的目标对象的指针
		//可选参数，就是带默认值
		void reset(T* ptr = nullptr) {
			if (obj == ptr) {//如果传入的就是当前持有的目标对象，无需做任何操作

			}
			else {
				delete obj;//接管新的目标对象之前，旧资源要释放掉
				obj = ptr;
			}
		}

		// 删除 拷贝构造函数 和 "="赋值操作符，禁止复制
		unique_ptr& operator=(const unique_ptr& other) = delete;
		unique_ptr(const unique_ptr& other) = delete;

		template<class T>//友元，这里要 重新声明 模板，因为友元并不属于类内成员，它不能享有最开始声明的模板
		friend std::ostream& operator<<(std::ostream& out, const unique_ptr<T>& up);
	};
	template<class T>
	std::ostream& operator<<(std::ostream& out, const unique_ptr<T>& up) {
		out << up.get();//std::unique_ptr中对于"<<"的重载，是把 get()送入输出流，本质就是 obj
		return out;
	}
}
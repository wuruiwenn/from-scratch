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
	if (&obj) {//对象空，则不打印任何东西
		out << "[Entity: " << obj.id << "]\n";
		return out;
	}
	out << "[]\n";
	return out;
}
namespace wrw
{
	//智能指针，本质是一个class template
	template<class T>
	class unique_ptr {
	private:
		T* obj;//用于绑定目标对象的指针
	public:
		//构造函数
		unique_ptr() :obj(nullptr) {
			cout << "unique_ptr 无参构造.\n";
		}
		unique_ptr(T* ptr) :obj(ptr) {
			cout << "unique_ptr 有参构造.\n";
		}

		//析构函数
		~unique_ptr() {
			cout << "~unique_ptr 析构.\n";
			delete obj;
		}

		// 删除 拷贝构造函数 和 "="赋值操作符，禁止 拷贝
		unique_ptr(const unique_ptr& other) = delete;
		unique_ptr& operator=(const unique_ptr& other) = delete;

		//移动构造函数
		//移动构造，接收内容的对象(就是this)是空的，没有初始化的
		//移动构造，最大区别就是和 拷贝构造，移动构造并不拷贝
		//目标对象在这个场景下，移动，就是要转移控制权，
		//移动前后，新旧控制方都是绑定的同一个目标对象，
		//所以肯定不能对原始的控制方进行delete，否则目标对象也会被释放
		//且但凡是"移动"，则旧的控制方一定要置空 ，即nullptr
		unique_ptr(unique_ptr&& other) noexcept {
			this->obj = other.obj;
			other.obj = nullptr;
		}

		//移动=赋值运算符
		//赋值运算，接收内容的对象(就是this)是已经有绑定旧的目标对象的，=赋值，就是要绑定新的目标对象
		//所以this的内容就是所控制的旧的资源，是需要delete的
		//且但凡是"移动"，则旧的控制方一定要置空 ，即nullptr
		unique_ptr& operator=(unique_ptr&& other) noexcept {
			if (this != &other) {//如果不是同一个对象才..，避免自赋值
				delete obj;//接管新的资源之前，要把之前的资源释放掉
				this->obj = other.obj;
				//other.obj = nullptr;
			}
			other.obj = nullptr;
			return *this;
		}

		//只要是，移动构造/赋值，被移动的源智能指针肯定是需要置nullptr的
		//但是不能delete，因为新旧智能指针指向的是同一目标对象，
		//只是移动后，旧的智能指针不再管理它了

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
			obj = nullptr;//让当前智能指针指向空，即不再指向该目标对象
			return tmp;
		}

		//reset()：释放所持有的目标对象，可接受一个可选的参数，就是即将要接管的新的目标对象的指针
		//可选参数，就是带默认值
		void reset(T* ptr = nullptr) {
			//这里或许要判断2个点：
				//（1）是不是传入了新的指针 
				//（2）传入的目标对象是不是就是当前已经控制的同一个目标对象

			/*if (ptr == nullptr) {
				delete obj;
			}
			else {
				if (ptr == obj) {

				}
				else {
					delete obj;
					obj = ptr;
				}
			}*/
			delete obj;
			obj = nullptr;//避免目标对象被delete多次，因为当前智能指针对象是栈对象，出了main作用域后，析构时也会delete obj;那么obj如果还指向目标对象则会再次delete，而实际当前智能指针绑定的目标对象本身e并不会析构，因为在main中是堆对象
			if (ptr) {
				obj = ptr;
			}

			//更简洁写法
			/*if (obj != ptr) {
				delete obj;
				obj = ptr;
			}*/
		}
		void swap(unique_ptr& other) {
			T* tmp = this->obj;
			this->obj = other.obj;
			other.obj = tmp;
		}

		//允许unique_ptr的对象隐式转换为一个bool类型 ，让if(up){}成为可能
		explicit operator bool() {
			return obj != nullptr;
		}

		template<class T>//友元，这里要 重新声明 模板，因为友元并不属于类内成员，它不能享有最开始声明的模板
		friend std::ostream& operator<<(std::ostream& out, const unique_ptr<T>& up);
	};
	template<class T>
	std::ostream& operator<<(std::ostream& out, const unique_ptr<T>& up) {
		if (up.get()) {
			out << up.get();//std::unique_ptr中对于"<<"的重载，是把 get()送入输出流，本质就是 obj
		}
		return out;
	}
}
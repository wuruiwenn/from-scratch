#pragma once

/*
	更加符合 std::shared_ptr
	std::shared_ptr内部是和weak_ptr具有关联的，
	而且引用计数，是用的一个Counter类来实现，
	包括 shared_ptr的引用计数、weak_ptr的引用计数
*/

namespace wrw2
{
	template<class T> class weak_ptr;
	class Counter;

	template<class T>
	class shared_ptr {
	private:
		T* obj;
		Counter* counter;
	public:
		/*
			<普通构造>
			若传入目标对象，则：
				shared_ptr的引用计数应该初始化为1
				weak_ptr的引用计数不变
		*/
		shared_ptr() :obj(nullptr), counter(nullptr) {}
		shared_ptr(T* ptr = nullptr)
			:obj(ptr), counter(new Counter())
		{
			if (ptr)
			{
				counter->share_cnt = 1;
			}
			cout << "shared_ptr构造\n";
		}
		//析构
		~shared_ptr() {
			release();
			cout << "shared_ptr析构\n";
		}

		/*
			拷贝构造：
				拷贝other的目标对象
				拷贝other的引用计数Counter
				最重要的是：更新目标对象的shared_ptr的引用计数+1
		*/
		shared_ptr(const shared_ptr& other) {
			obj = other.obj;
			counter = other.counter;
			++(counter->share_cnt);
			cout << "shared_ptr 拷贝构造\n";
		}

		/*
			拷贝 = 赋值运算符
		*/
		shared_ptr& operator=(const shared_ptr& other) {
			if (this == &other || obj == other.obj) {
				return *this;
			}
			release();
			obj = other.obj;
			counter = other.counter;
			++(counter->share_cnt);

			return *this;
			cout << "shared_ptr 拷贝 = 赋值运算符\n";
		}

		/*
			移动构造
		*/
		shared_ptr(shared_ptr&& other) {

			obj = other.obj;
			counter = other.counter;
			++(counter->share_cnt);
			other.release();

			cout << "shared_ptr 移动构造\n";
		}

		/*
			移动 = 赋值运算符
		*/
		shared_ptr& operator=(shared_ptr&& other) {
			if (this == &other) {
				return *this;
			}
			if (obj == other.obj)
			{
				other.release();
			}
			else
			{
				release();
				obj = other.obj;
				counter = other.counter;
				++(counter->share_cnt);
				other.release();
			}
			return *this;
			cout << "shared_ptr 移动 = 赋值运算符\n";
		}

		/*
			release():
			解除当前shared_ptr对目标对象的控制权，
			解除绑定，意味着 引用计数--，所以：
				若shared_ptr引用计数 = 0，则销毁目标对象 obj
				若shared_ptr引用计数=0 && weak_ptr引用计数 = 0,
					则 Counter计数器也需销毁
		*/
		void release()
		{
			--(counter->share_cnt);
			if (0 == (counter->share_cnt))
			{
				delete obj;
				//obj = nullptr;
				if (0 == (counter->weak_cnt))//这里不是很明白，为什么weak_cnt=0，要delete cnter？
				{
					delete counter;
					//counter = nullptr;
				}
			}
			//我觉得这里，无论如何，
			//不管目标对象有没有被delete，也应该断开绑定
			obj = nullptr;
			counter = nullptr;
		}

		/*
			reset():
			重新控制新的目标对象。
				对于新的目标对象newobj，其shared_ptr的引用计数应该初始化为1
				weak_ptr引用计数不变
		*/
		void reset(T* newobj = nullptr) {
			if (obj == newobj) {
				return;
			}
			release();
			if (newobj) {
				obj = newobj;
				counter = new Counter();
				counter->share_cnt = 1;
			}
		}

		//一些成员函数
		T* get() const {
			return obj;
		}
		int use_count() {
			return counter == nullptr ? 0 : counter->share_cnt;
		}

		//一些操作符
		explicit operator bool() {
			return obj != nullptr;
		}

		T* operator->() {
			return obj;
		}

		T& operator*() {
			return *obj;
		}
	};

	class Counter
	{
	public:
		Counter() :share_cnt(0), weak_cnt(0) {}
		int share_cnt = 0;
		int weak_cnt = 0;
	};
}
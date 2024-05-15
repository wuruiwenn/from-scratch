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
				if (0 == (counter->weak_cnt))//如果weak_cnt不为0，还有用处，就是用于weak_ptr判断是否仍然有weak_ptr对象绑定了目标对象
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


	template<class T>
	class weak_ptr {
	public:
		friend class shared_ptr<T>;
	private:
		T* obj;
		Counter* counter;
	public:
		/*
			weak_ptr构造函数：
			weak_ptr只能通过shared_ptr来构造，不能直接传入目标对象obj
		*/
		weak_ptr() :obj(nullptr), counter(nullptr) {}
		weak_ptr(shared_ptr<T>& sp)
			:obj(sp.obj), counter(sp.counter)
		{
			if (counter) {
				++(counter->weak_cnt);
			}
		}

		//析构
		~weak_ptr() {
			release();
		}

		//拷贝构造
		weak_ptr(const weak_ptr& other) {
			obj = other.obj;
			counter = other.counter;
			++(counter->weak_cnt);
			cout << "weak_ptr 拷贝构造\n";
		}

		/*
			拷贝 = 赋值运算符
			有2种：
				传入weak_ptr
				传入shared_ptr
		*/
		weak_ptr& operator=(const weak_ptr& other) {
			if (this == &other) {
				return *this;
			}
			release();
			obj = other.obj;
			counter = other.counter;
			++(counter->weak_cnt);
			return *this;
		}
		weak_ptr& operator=(const shared_ptr& other) {
			//传入shared_ptr，自然不可能是同一个对象
			release();
			obj = other.obj;
			counter = other.counter;
			++(counter->weak_cnt);
			return *this;
		}



		/*
			重要函数：
				release()
				lock()
				expired()
		*/
		void release()
		{
			if (!counter)
				return;

			--(counter->weak_cnt);
			if (0 == (counter->weak_cnt) && 0 == (counter->share_cnt))
			{
				delete counter;
			}
			counter = nullptr;
		}

		/*
			lock()：
			从weak_ptr中获取一个shared_ptr对象，
			若目标对象已经被销毁，则返回空的shared_ptr，否则返回完整的shared_ptr
		*/
		shared_ptr<T>& lock() {
			return shared_ptr<T>(*this);
		}

		/*
			expired():
				判断目标对象是否仍存活
		*/
		bool expired() {

		}
	};
}
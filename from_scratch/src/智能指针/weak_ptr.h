#pragma once

#include"counter.h"
//#include"shared_ptr.h"

namespace wrw2
{
	//template<class T> shared_ptr;
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
			weak_ptr可通过shared_ptr来构造，也可通过weak_ptr来构造。
			但是，不能直接传入目标对象obj
		*/
		weak_ptr() :obj(nullptr), counter(nullptr) {}
		weka_ptr(const weak_ptr<T>& wp)
			:obj(wp.obj), counter(wp.counter)
		{
			if (counter) {
				++(counter->weak_cnt);
			}
		}
		weak_ptr(const shared_ptr<T>& sp)
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

		//release()
		//weak_ptr对象被销毁时，调用release()
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
			return expired() ? shared_ptr<T>(nullptr) : shared_ptr<T>(*this);
		}

		//expired() :
		//判断目标对象是否仍存活
		bool expired() {
			return counter->share_cnt <= 0 || !counter;
		}
	};
}

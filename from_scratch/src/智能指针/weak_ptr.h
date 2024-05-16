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
			weak_ptr���캯����
			weak_ptr��ͨ��shared_ptr�����죬Ҳ��ͨ��weak_ptr�����졣
			���ǣ�����ֱ�Ӵ���Ŀ�����obj
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

		//����
		~weak_ptr() {
			release();
		}

		//��������
		weak_ptr(const weak_ptr& other) {
			obj = other.obj;
			counter = other.counter;
			++(counter->weak_cnt);
			cout << "weak_ptr ��������\n";
		}

		/*
			���� = ��ֵ�����
			��2�֣�
				����weak_ptr
				����shared_ptr
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
			//����shared_ptr����Ȼ��������ͬһ������
			release();
			obj = other.obj;
			counter = other.counter;
			++(counter->weak_cnt);
			return *this;
		}

		//release()
		//weak_ptr��������ʱ������release()
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
			lock()��
			��weak_ptr�л�ȡһ��shared_ptr����
			��Ŀ������Ѿ������٣��򷵻ؿյ�shared_ptr�����򷵻�������shared_ptr
		*/
		shared_ptr<T>& lock() {
			return expired() ? shared_ptr<T>(nullptr) : shared_ptr<T>(*this);
		}

		//expired() :
		//�ж�Ŀ������Ƿ��Դ��
		bool expired() {
			return counter->share_cnt <= 0 || !counter;
		}
	};
}

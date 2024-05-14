#pragma once

/*
	���ӷ��� std::shared_ptr
	std::shared_ptr�ڲ��Ǻ�weak_ptr���й����ģ�
	�������ü��������õ�һ��Counter����ʵ�֣�
	���� shared_ptr�����ü�����weak_ptr�����ü���
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
			<��ͨ����>
			������Ŀ�������
				shared_ptr�����ü���Ӧ�ó�ʼ��Ϊ1
				weak_ptr�����ü�������
		*/
		shared_ptr() :obj(nullptr), counter(nullptr) {}
		shared_ptr(T* ptr = nullptr)
			:obj(ptr), counter(new Counter())
		{
			if (ptr)
			{
				counter->share_cnt = 1;
			}
			cout << "shared_ptr����\n";
		}
		//����
		~shared_ptr() {
			release();
			cout << "shared_ptr����\n";
		}

		/*
			release():
			�����ǰshared_ptr��Ŀ�����Ŀ���Ȩ��
			����󶨣���ζ�� ���ü���--�����ԣ�
				��shared_ptr���ü��� = 0��������Ŀ�����
				��weak_ptr���ü��� = 0����Counter������Ҳ������
		*/
		void release()
		{
			--(counter->share_cnt);
			if (0 == (counter->share_cnt))
			{
				delete obj;
				obj = nullptr;
				if (0 == (counter->share_cnt))
				{
					delete counter;
					counter = nullptr;
				}
			}
		}

		/*
			reset():
			���¿����µ�Ŀ�����
				�����µ�Ŀ�����newobj����shared_ptr�����ü���Ӧ�ó�ʼ��Ϊ1
				weak_ptr���ü�������
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



		T* get() const {
			return obj;
		}
		int use_count() {
			return counter == nullptr ? 0 : counter->share_cnt;
		}

		//һЩ������
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
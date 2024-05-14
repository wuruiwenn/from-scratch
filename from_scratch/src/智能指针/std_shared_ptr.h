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
			�������죺
				����other��Ŀ�����
				����other�����ü���Counter
				����Ҫ���ǣ�����Ŀ������shared_ptr�����ü���+1
		*/
		shared_ptr(const shared_ptr& other) {
			obj = other.obj;
			counter = other.counter;
			++(counter->share_cnt);
			cout << "shared_ptr ��������\n";
		}

		/*
			���� = ��ֵ�����
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
			cout << "shared_ptr ���� = ��ֵ�����\n";
		}

		/*
			�ƶ�����
		*/
		shared_ptr(shared_ptr&& other) {

			obj = other.obj;
			counter = other.counter;
			++(counter->share_cnt);
			other.release();

			cout << "shared_ptr �ƶ�����\n";
		}

		/*
			�ƶ� = ��ֵ�����
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
			cout << "shared_ptr �ƶ� = ��ֵ�����\n";
		}

		/*
			release():
			�����ǰshared_ptr��Ŀ�����Ŀ���Ȩ��
			����󶨣���ζ�� ���ü���--�����ԣ�
				��shared_ptr���ü��� = 0��������Ŀ����� obj
				��shared_ptr���ü���=0 && weak_ptr���ü��� = 0,
					�� Counter������Ҳ������
		*/
		void release()
		{
			--(counter->share_cnt);
			if (0 == (counter->share_cnt))
			{
				delete obj;
				//obj = nullptr;
				if (0 == (counter->weak_cnt))//���ﲻ�Ǻ����ף�Ϊʲôweak_cnt=0��Ҫdelete cnter��
				{
					delete counter;
					//counter = nullptr;
				}
			}
			//�Ҿ������������Σ�
			//����Ŀ�������û�б�delete��ҲӦ�öϿ���
			obj = nullptr;
			counter = nullptr;
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

		//һЩ��Ա����
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
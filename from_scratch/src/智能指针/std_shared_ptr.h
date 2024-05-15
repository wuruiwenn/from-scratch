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
				if (0 == (counter->weak_cnt))//���weak_cnt��Ϊ0�������ô�����������weak_ptr�ж��Ƿ���Ȼ��weak_ptr�������Ŀ�����
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
			weak_ptrֻ��ͨ��shared_ptr�����죬����ֱ�Ӵ���Ŀ�����obj
		*/
		weak_ptr() :obj(nullptr), counter(nullptr) {}
		weak_ptr(shared_ptr<T>& sp)
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



		/*
			��Ҫ������
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
			lock()��
			��weak_ptr�л�ȡһ��shared_ptr����
			��Ŀ������Ѿ������٣��򷵻ؿյ�shared_ptr�����򷵻�������shared_ptr
		*/
		shared_ptr<T>& lock() {
			return shared_ptr<T>(*this);
		}

		/*
			expired():
				�ж�Ŀ������Ƿ��Դ��
		*/
		bool expired() {

		}
	};
}
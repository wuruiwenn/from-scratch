#pragma once

/*
	shared_ptr�ĺ����ǣ����ü���
*/


namespace wrw
{
	template<class T>
	class shared_ptr {
	private:
		T* obj;
		int* p_cnt;//ָ�� Ŀ���������ü��� �� ָ��
	public:
		// <��ͨ���캯��>
		shared_ptr() :obj(nullptr), p_cnt(nullptr) {}
		shared_ptr(T* ptr) :obj(ptr), p_cnt(new int(1)) {}

		// <��������>
		~shared_ptr() {
			if (p_cnt != nullptr && (--(*p_cnt)) == 0) {
				cout << "Ŀ����� ���ü��� = 0���ͷ�Ŀ����� delete obj.\n";
				delete obj;
				delete p_cnt;
			}
			obj = nullptr;
			p_cnt = nullptr;
			cout << "shared_ptr ����\n";
		}

		/*
			<��������>��
			�������ü���
			����p_cnt�ǳ���Ŀ���������ü�����ָ�룬
			����ֻ�����this�����ü�����ʵ�ط��ʵ�ַ���¼���
		*/
		shared_ptr(const shared_ptr& other) {
			obj = other.obj;
			p_cnt = other.p_cnt;

			++(*p_cnt);
			cout << "shared_ptr��������\n";
		}

		/*
			<���� = ��ֵ�����>
		*/
		shared_ptr& operator=(const shared_ptr& other) {
			//����ͬһ��shared_ptr���󣬻�2����ͬshared_ptr������ͬһĿ�����
			if (&other == this || other.obj == this->obj) {
				return *this;
			}

			release();//ȡ����Ե�ǰĿ�����İ�(�����ü���=0�����delete)
			obj = other.obj;//���µĶ���
			p_cnt = other.p_cnt;//���ﷴ��������ǳ�������У���Ϊp_cnt��Ŀ���������ü���������shared_ptr���ڸ�Ŀ���������ü���������ָ��ͬһ���ط�
			++(*p_cnt);//����Ŀ���������ü���

			cout << "shared_ptr ���� = ��ֵ�����\n";
			return *this;
		}

		//ʵ������...

		//�ƶ�����
		shared_ptr(shared_ptr&& other) {

			obj = other.obj;
			p_cnt = other.p_cnt;

			//���ü���Ӧ������-1��Ȼ��+1����������ı�

			other.obj = nullptr;//Դ�����ÿ�
			other.p_cnt = nullptr;

			cout << "shared_ptr �ƶ�����\n";
		}

		//�ƶ�=��ֵ�����
		shared_ptr& operator=(shared_ptr&& other) {
			if (&other == this) {
				return *this;
			}
			release();//�ͷ���Ե�ǰĿ�����Ŀ���Ȩ
			obj = other.obj;
			p_cnt = other.p_cnt;

			other.obj = nullptr;
			other.p_cnt = nullptr;

			cout << "shared_ptr �ƶ�=��ֵ�����\n";
			return *this;
		}

		//һЩ��Ա����

		/*
			use_count():
			����Ŀ���������ü����ĸ���
		*/
		int use_count() {
			return *p_cnt;
		}

		/*
			bool unique()��
			����ָ���Ƿ�߱���ռȨ�������ü��� = 1
		*/
		bool unique() {
			return (*p_cnt) == 1;
		}

		/*
			release():
			��1��ȡ�����Ŀ�����Ŀ���Ȩ���Ҹ�Ŀ�����ļ���-1
			��2�������ü�����Ϊ0�������ͷ�Ŀ������ڴ�
			<ʵ��std::shared_ptr��û��release()������Ϊʲô��>
			unique_ptr����release����Ϊ��ĳһʱ��ֻ����һ�� unique_ptr ָ��ĳ������
			release���ֵĳ������ڣ�ʵ��Ŀ�����Ŀ���Ȩת�ƣ�
				���unique_ptr���󶨵�Ŀ�����Ŀ���Ȩ���ѿ���Ȩת�Ƹ���һ��unique_ptr����
				��Ϊunique_ptr�ǲ��ܸ��Ƶģ�����ֻ��ͨ��release����Ŀ�����Ŀ���Ȩ����ת�ƣ������� �ƶ����� Ҳ����ʵ��Ŀ�����Ŀ���Ȩת�� ����
			(���Ҫ��unique_ptr��reset���ֿ���
				reset�Ǵ�ͷ��β������Ե�ǰ���unique_ptr��reset�ĳ������ڣ�������ǰunique_ptr���󶨵�Ŀ�����)
			���ԣ�shared_ptrû��Ҫʹ��release��Ҳ����û��Ҫͨ��releaseĳһ��ת��Ŀ�����Ŀ���Ȩ
			��Ϊshared_ptr����ͨ�� �������� ֱ��ʵ�ֶ��shared_ptrֱ�ӻ�ȡ��ͬһ��Ŀ�����Ŀ���Ȩ
		*/
		void release() {
			if (p_cnt != nullptr && (--(*p_cnt)) == 0) {
				delete obj;
				delete p_cnt;
			}
			obj = nullptr;
			p_cnt = nullptr;//������Σ���ǰshared_ptr���ٹ����Ŀ������ˣ���ôָ���Ŀ���������ü���ҲҪ�Ͽ�
		}


		/*
			reset():
			shared_ptr��reset()��unique_ptr��rest()���кܴ���죺
			shared_ptr::reset()�����Ȱ�Ŀ���������ü�����һ��������ü���Ϊ0���Ż�deleteĿ����󣬷��򲢲���deleteĿ�����
			unique_ptr::reset()����ֱ��deleteĿ�����
		*/
		//�����ʵ�������⡷
		/*void reset(T* ptr = nullptr) {
			if (obj == ptr) {
				return;
			}
			if (p_cnt != nullptr && (--(*p_cnt)) == 0) {
				delete obj;
			}
			obj = ptr;
		}*/

		T* get() const {
			return obj;
		}

		//һЩ������
		T& operator*() {
			return *obj;
		}
		T* operator->() {
			return obj;
		}
		explicit operator bool() {
			return obj != nullptr;
		}
	};
}
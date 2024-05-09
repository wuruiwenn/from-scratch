#pragma once

/*
	shared_ptr�ĺ����ǣ����ü���
*/

namespace wrw
{
	template<class T>
	class shared_ptr {
	private:
		T* obj; //ִ�а󶨵�Ŀ������ָ��
		int* p_cnt;//ָ�� Ŀ���������ü��� �� ָ��
	public:
		// <��ͨ���캯��>
		shared_ptr() :obj(nullptr), p_cnt(nullptr) {}
		shared_ptr(T* ptr) :obj(ptr), p_cnt(new int(1)) {}

		// <��������>
		~shared_ptr() {
			cout << "shared_ptr ����\n";
			if (p_cnt != nullptr && (--(*p_cnt)) == 0) {
				cout << "Ŀ����� ���ü��� = 0���ͷ�Ŀ����� delete obj.\n";
				delete obj;
				delete p_cnt;
			}
			obj = nullptr;
			p_cnt = nullptr;
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

			this->release();//ȡ����Ե�ǰĿ�����İ�(�����ü���=0�����delete)
			obj = other.obj;//���µĶ���
			p_cnt = other.p_cnt;//���ﷴ��������ǳ�������У���Ϊp_cnt��Ŀ���������ü���������shared_ptr���ڸ�Ŀ���������ü���������ָ��ͬһ���ط�
			++(*p_cnt);//����Ŀ���������ü���

			cout << "shared_ptr ���� = ��ֵ�����\n";
			return *this;
		}


		// <�ƶ�����>
		shared_ptr(shared_ptr&& other) {

			obj = other.obj;
			p_cnt = other.p_cnt;

			//���ü���Ӧ������-1��Ȼ��+1����������ı�

			other.obj = nullptr;//Դ�����ÿ�
			other.p_cnt = nullptr;

			cout << "shared_ptr �ƶ�����\n";
		}



		// <�ƶ� = ��ֵ�����>
		shared_ptr& operator=(shared_ptr&& other) {
			if (&other == this) {
				return *this;
			}

			//�������ͬһsp���󣬵��ǰ󶨵�obj��ͬһ������Ȼ�ǿɲ�����
			//�����2��sp����󶨵�obj��ͬ�������Ӧ���ǲ�һ����
			if (this->obj == other.obj)//����ͬһ�����󣬱�move��sp�����ÿգ�p_cnt�ÿա�������spӵ�е�p_cnt-1.
			{
				//��Ϊ�󶨵���ͬһ��obj������this��other ��p_cntӦ��ָ����ͬһ���ط�������˭����
				/*--(*other.p_cnt);
				other.obj = nullptr;
				other.p_cnt = nullptr;*/
				other.release();
			}
			else//�󶨵��ǲ�ͬ����p_cnt�൱��û�и��£���Ϊһ��һ��
			{
				//���������⣺this.p_cntҪ--��Ȼ����ܰ��µ����ü����飬��other��obj�����ü�����
				this->release();
				this->obj = other.obj;
				this->p_cnt = other.p_cnt;
				++(*p_cnt);
				other.release();
			}
			cout << "shared_ptr �ƶ�=��ֵ�����\n";
			return *this;
		}



		//һЩ��Ա����

		/*
			use_count():
			����Ŀ���������ü����ĸ���
		*/
		int use_count() {
			return (p_cnt == nullptr) ? 0 : (*p_cnt);
		}

		/*
			bool unique()��
			����ָ���Ƿ�߱���ռȨ�������ü��� = 1
		*/
		bool unique() {
			return (p_cnt != nullptr) && (*p_cnt) == 1;
		}

		/*
			release():
			�ͷ�this�Ե�ǰĿ�����Ŀ���Ȩ��
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
				delete obj;//��Ϊ��Ŀ������Ѿ�û�б��κ�shared_ptr�����ˣ�����Ŀ�������Ա�������
				delete p_cnt;//��Ϊ��Ŀ������Ѿ�û�б��κ�shared_ptr�����ˣ��������ü���Ҳû��������
			}
			obj = nullptr;
			p_cnt = nullptr;//������Σ���ǰshared_ptr���ٹ����Ŀ������ˣ���ôָ���Ŀ���������ü���ҲҪ�Ͽ�
		}

		/*
			reset():
			shared_ptr��reset()��unique_ptr��rest()���кܴ���죺
			shared_ptr::reset()�����Ȱ�Ŀ���������ü�����һ��������ü���Ϊ0���Ż�deleteĿ����󣬷��򲢲���deleteĿ����������¶�������¶����¶������ü���+1
			unique_ptr::reset()����ֱ��deleteĿ�����Ȼ���������¶�������¶����¶������ü���+1

			shared_ptr reset(T* newobj): �и�����
			���ﴫ����¶���ֱ����Ŀ�����T*
			��ô���ڴ������Ŀ������ָ�룬��ô��ȡ��Ŀ������Ӧ��p_cnt�أ�
			���������
				���¶���newobj�ڴ�֮ǰ��shared_ptr(newobj)��ʽ�󶨹�����ô�������°󶨣������newobj�Ǳ����shared_ptrֱ�Ӱ󶨵ģ�(�����ǿ�����ʽ)�������double delete����
				���¶���newobj�ڴ�֮ǰû�б�shared_ptr�󶨹������ֱ�Ӱ󶨣���ʱ *p_cnt�϶��ǳ�ʼ��Ϊ 1
		*/
		void reset(T* newobj = nullptr) {
			if (this->obj == newobj) {//����°󶨶�����ǵ�ǰ�󶨵Ķ�����ʲôҲ����
				return;
			}
			this->release();//���ɵ�Ŀ�����
			if (newobj != nullptr) {//���������µĶ���������µİ�
				this->obj = newobj;
				this->p_cnt = new int(1);
			}
		}

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
			return obj != nullptr && p_cnt != nullptr;
		}
	};
}
#pragma once

/*
	C++ std::string ��дʱ����
	�漰����֪ʶ��
		1���������캯��������=��ֵ�����
		2����������أ��ر���[]
		3�����ü���
		4��proxy�������ģʽ

	��ûʵ���꣬�ο���
	https://blog.csdn.net/weixin_48617416/article/details/122182780

	https://blog.csdn.net/HappyKocola/article/details/72457003?spm=1001.2101.3001.6650.6&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-72457003-blog-122182780.235%5Ev43%5Epc_blog_bottom_relevance_base1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-72457003-blog-122182780.235%5Ev43%5Epc_blog_bottom_relevance_base1&utm_relevant_index=13

*/

namespace wrw_
{
	class string
	{
	public:
		char* obj;
		int m_size;
		int* p_cnt;//���ü���
	public:
		//���캯��
		string() :obj(nullptr), p_cnt(nullptr), m_size(0) {

		}
		string(const char* ptr) {
			int n = strlen(ptr);
			m_size = n;
			obj = new char[m_size + 1];
			p_cnt = new int(1);
			strcpy(obj, ptr);
		}
	public:
		//�������캯������Ӧ���� ��ʽ����
		string(const string& other) {
			obj = other.obj;//ǳ�������Ϳ�ʵ�� string��ʽ����
			m_size = other.m_size;
			p_cnt = other.p_cnt;
			++(*p_cnt);
		}
		//���� = ��ֵ�������������ֵ����Ӧ���� дʱ���� ������
		string& operator=(const string& other)
		{
			if (this != &other)
			{
				if (p_cnt && (*p_cnt) > 1)
				{
					//�ȿ��� (���ÿ�����ֱ�����µĸ��Ǿɵļ��ɣ�
					//���޸�Ԫ�ء���д����
					release();
					m_size = other.m_size;
					obj = new char[m_size + 1];
					p_cnt = other.p_cnt;
					++(*p_cnt);
				}
			}
			return *this;
		}
		//s[i] = 'A'�������޸ģ�ҲӦ�ô��� дʱ����
		//�����и�������ǣ�s[i]�������֪����Ҫ���ж����������ǣ�д�����أ�
		char& operator[](int pos) {
			return obj[pos];
		}

		void release()//�Ͽ���ָ���Ŀ���ַ���
		{
			obj = nullptr;
			p_cnt = nullptr;
		}
	public:
		int size() const {
			return m_size;
		}
	public:
		friend std::ostream& operator<<(std::ostream& stream, const string& s);
	};
	std::ostream& operator<<(std::ostream& stream, const string& s) {
		stream << "[";
		stream << s.obj << "]\n";
		return stream;
	}
}

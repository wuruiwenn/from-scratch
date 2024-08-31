#pragma once
#include"headers.h"


//带迭代器的 std::string
//是STL中 std::string、iterator的一个简单实现


namespace wrw {
	class string
	{
	private:
		char* m_ptr;
		int m_size;
		int m_capacity;
	public:
		//���캯��
		/*string()
			:m_ptr(new char[1]), m_size(0), m_capacity(0) {
			m_ptr[0] = '\0';
		}

		string(const char* str)
			:m_size(strlen(str)) {
			m_capacity = m_size;
			m_ptr = new char[m_capacity + 1];
			strcpy(m_ptr, str);
		}*/

		//�ϲ�Ϊ��Ĭ�ϲ����Ĺ��캯��
		string(const char* str = "")
			: m_size(strlen(str)) {
			m_capacity = m_size;
			m_ptr = new char[m_capacity + 1];
			strcpy(m_ptr, str);
		}

		//����
		~string() {
			delete[] m_ptr;
			m_size = m_capacity = 0;
		}

		//��������
		string(const string& other) {
			m_size = other.m_size;
			m_capacity = m_size;
			m_ptr = new char[m_capacity + 1];//Ĭ�Ͽ���������ǳ�������������ʵ�����������double delete
			strcpy(m_ptr, other.m_ptr);
			cout << "string��������\n";
		}
		string& operator=(const string& other) {
			if (this == &other) {
				return *this;
			}
			delete[] m_ptr;
			m_size = other.m_size;
			m_capacity = m_size;
			m_ptr = new char[m_capacity + 1];
			strcpy(m_ptr, other.m_ptr);
			cout << "string���� = ��ֵ�����\n";
			return *this;
		}

	public:
		const char* c_str() {
			return m_ptr;
		}

		char& operator[](int pos) {//�����ⲿͨ��[]���޸�string�����ڵ��ַ�
			_ASSERT(pos < m_size);
			return m_ptr[pos];
		}
		const char& operator[](int pos) const {//�ײ�Ҳ�ɼ���const����ֹ�ⲿ�޸ĸ��ַ�
			_ASSERT(pos < m_size);
			return m_ptr[pos];
		}

		int size() const {
			return m_size;
		}

		void Print(const string& str) {
			for (int i = 0; i < m_size; i++) {
				cout << str[i] << " ";//����������϶�������ͨ��[]�޸�string����ģ�����operator[]������const
			}
			cout << endl;
		}
	public:
		//ʵ�� string ������
		//����Ϊ �ڲ���
		class string_iterator {
		private:
			char* obj;
		public:
			string_iterator(char* ptr = nullptr) :obj(ptr) {}

			//�������
			string_iterator& operator++() {//++i
				++obj;//��������ָ��һ��char��λ��ָ�룬ֱ��++��ÿ��++��Ծһ��char����
				return *this;
			}
			string_iterator operator++(int) {//i++
				string_iterator tmp = *this;
				++obj;
				return tmp;
			}

			char& operator*() {
				return *obj;
			}
			char* operator->() {
				return obj;
			}
			bool operator==(const string_iterator& other) {
				return obj == other.obj;
			}
			bool operator!=(const string_iterator& other) {
				return obj != other.obj;
			}
		};
	public:
		//���� ������ ���ͱ���
		typedef string_iterator iterator;
		iterator begin() {
			return iterator(m_ptr);
		}
		iterator end() {
			return iterator(m_ptr + m_size);
		}
	public:
		friend std::ostream& operator<<(std::ostream& out, const string& str);
	};
	std::ostream& operator<<(std::ostream& out, const string& str) {
		out << str.m_ptr;
		return out;
	}
}
//int main() {
//	using wrw::string;
//	string s("ABCDEFG");
//
//	cout << "����������string\n";
//	for (auto it = s.begin(); it != s.end(); it++) {
//		cout << (*it) << " ";
//	}
//	cout << endl;
//	for (auto cur : s) {//���ʾ��ǵ��õ�������Ŀ�����ʵ���˵���������ʹ��
//		cout << cur << " ";
//	}
//	cout << endl;
//
//	//����������
//	auto it = s.begin();
//	cout << "it init = " << *it << endl;
//	//++it;
//	//++it;
//	//cout << "*it = " << *it << endl;
//	auto it2 = it++;
//	cout << "*it2 = " << *it2 << endl;
//	cout << "*it = " << *it << endl;
//
//	cout << "bool equals\n";
//	auto it3 = s.begin();
//	it3++;
//	it3++;
//	auto it4 = s.begin();
//	it4++;
//	++it4;
//	cout << "it3 == it4��" << (it3 == it4) << endl;
//
//}

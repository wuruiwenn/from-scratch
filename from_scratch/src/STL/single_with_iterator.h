#pragma once

namespace wrw
{
	class string
	{
	private:
		char* m_str;
		size_t m_size;
		size_t m_capacity;
	public:
		~string() {
			cout << "~string����\n";
			delete[] m_str;
			m_str = nullptr;
			m_size = m_capacity = 0;
		}
	public:
		/*string()
			:m_str(new char[1]),m_size(0),m_capacity(0) {
			m_str[0] = '\0';
		}
		string(const char* str){
			cout << "string���캯��\n";
			m_size = strlen(str);
			m_capacity = strlen(str);
			m_str = new char[m_size + 1];
			strncpy(m_str, str,m_size+1);
		}*/
		string(const char* str = "") {
			cout << "string�޲Ρ��вι���ϲ�\n";
			m_size = strlen(str);
			m_capacity = strlen(str);
			m_str = new char[m_size + 1];
			strcpy(m_str, str);
		}
	public:
		const char* c_str() {
			return m_str;
		}

		//string��operator []��2������
		//����ʵ��str[i]='x'���޸�
		char& operator[](int pos) {
			return m_str[pos];
		}
		//����string��ӡ
		const char& operator[](int pos) const{
			return m_str[pos];
		}
	public:
		//ʵ��string�ĵ�����
		//string�ĵ���������һ��char*����Եģ�����list�ĵ�������һ��ָ��list�ڵ�� node*
		class string_iterator {
		private:
			char* ptr;
		public:
			string_iterator(char* obj) :ptr(obj) {}

			char operator*() {// auto it = string.begin(), *it����ָ����ַ�����
				return *ptr;
			}
			//char* operator->() {//auto it = string.begin(),it->����ͨ����ָ��û��->����
			//	return ptr;
			//}

			bool operator==(const string_iterator& other) {
				return ptr == other.ptr;
			}
			bool operator!=(const string_iterator& other) {
				return ptr != other.ptr;
			}

			string_iterator& operator++() {
				ptr = ptr + sizeof(char);
				return *this;
			}

			string_iterator operator++(int) {//i++
				string_iterator tmp(*this);
				++(*this);
				return tmp;
			}
		};
	public:
		typedef string_iterator iterator;

		iterator begin() {
			return m_str;
		}
		iterator end() {
			return m_str + m_size;
		}
		

	public:
		friend std::ostream& operator<<(std::ostream& out, const string& str);
	};
	std::ostream& operator<<(std::ostream& out, const string& str) {
		out << "[string:";
		for (int i = 0; i < str.m_size; i++) {
			out << str[i] << ",";
			//str[i] = '9';���ﵱȻ�����޸ģ���Ϊ����str��const
		}
		out << "]\n";
		return out;
	}
};

/*
������
	��1�� c_str()���ؿ��ַ���ʱ����δ�ӡ���ݣ�
	��2�� �޲ι��졢�вι���ϲ�
	��3��operator[] constȨ��ƥ������
*/

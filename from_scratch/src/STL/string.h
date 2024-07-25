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
		string()
			:m_str(new char[1]),m_size(0),m_capacity(0) {
			m_str[0] = '\0';
		}
		string(const char* str){
			cout << "string���캯��\n";
			m_size = strlen(str);
			m_capacity = strlen(str);
			m_str = new char[m_size + 1];
			strncpy(m_str, str,m_size+1);
		}
	public:
		const char* c_str() {
			return m_str;
		}
		char& operator[](int pos) {
			return m_str[pos];
		}
	};
};

/*
������
	��1�� c_str()���ؿ��ַ���ʱ����δ�ӡ���ݣ�
	��2��
*/

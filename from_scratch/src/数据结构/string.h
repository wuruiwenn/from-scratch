#pragma once

//ʵ������ Java String

#include<string>
namespace wrw
{
	class String 
	{
	private:
		char* m_buffer;
		int m_size;
	public:
		~String() {
			delete[] m_buffer;
			cout << "String ��������\n";
		}
		String():m_buffer(nullptr), m_size(0) {}

		String(const char* str) {
			int n = strlen(str);
			m_size = n;
			m_buffer = new char[n+1];
			for (int i = 0; i < n; i++) {
				m_buffer[i] = str[i];
			}
			m_buffer[m_size] = '\0';
			cout << "String ���캯��\n";
		}
		//�������캯��
		//����������õ�ʱ������ǰ���󣬼�this����ʱ��û�б�����
		//����ͨ����������Ŀ�������й���
		String(const String& s) {
			int n = s.m_size;
			//this->m_buffer = s.m_buffer;//��������Ĭ������������������ǳ������ǳ�����Ļ�����Ŀ����󣬵�ǰ��������ʱ������delete m_buffer�����ͳһ�ڴ汻���delete
			this->m_buffer = new char[n+1];//���
			this->m_size = n;
			for (int i = 0; i < n; i++) {
				m_buffer[i] = s.m_buffer[i];
			}
			m_buffer[n] = '\0';
			cout << "String �������캯��\n";
		}

		//���� = ��ֵ�����
		// = ��ֵ���������ʱ������ǰ���󣬼�this�Ѿ�����ʼ���ˣ�
		// �ȴ������Ŀ����󸲸��Լ�
		String& operator=(const String& s){
			if (&s == this) {//�����ͬһ������
				return *this;
			}
			int n = s.m_size;
			this->m_size = n;
			//this->m_buffer = s.m_buffer;//��������� ǳ������� deleteͬһ�ڴ�����
			//this->m_buffer = new char[n + 1];//��ʱ��ǰ�������Ѿ���ʼ���˵ģ��������³�ʼ��
			//ֻ�踲��
			for (int i = 0; i < n; i++) {
				m_buffer[i] = s.m_buffer[i];
			}
			m_buffer[n] = '\0';
			cout << "String = ��ֵ�����\n";
			return *this;
		}

		//�ƶ����캯��
		//��Ŀ�����s������ת�Ƶ�this
		//�ƶ����� ����ʱ������ǰ����this��ʱ��δ�����죬�Ҵ����Ŀ������� ��ֵ
		String(String&& s) {
			int n = s.m_size;
			this->m_size = n;
			this->m_buffer = new char[n + 1];
			for (int i = 0; i < n; i++) {//Ŀ�����������ƶ���this
				this->m_buffer[i] = s.m_buffer[i];
			}
			this->m_buffer[n] = '\0';
			s.m_buffer = nullptr;//Ŀ�����"�ÿ�"
			s.m_size = 0;

			cout << "String �ƶ�����\n";
		}

		//�ƶ� = ��ֵ�����
		String& operator=(String&& s) {
			int n = s.m_size;
			this->m_size = n;
			//this->m_buffer = new char[n + 1];
			for (int i = 0; i < n; i++) {
				this->m_buffer[i] = s.m_buffer[i];
			}
			this->m_buffer[n] = '\0';
			s.m_buffer = nullptr;//Ŀ�����"�ÿ�"
			s.m_size = 0;
			cout << "String = �ƶ���ֵ�����\n";
			return *this;
		}

		//ʹ��String�������ʽת��Ϊһ��boolֵ
		operator bool() {
			return m_buffer != nullptr;
		}
		int GetStrSize() {
			return m_size;
		}
		friend std::ostream& operator<<(std::ostream& out, const String& s);
	};
	std::ostream& operator<<(std::ostream& out, const String& s) {
		out << "[String:" << s.m_buffer << "]\n";
		return out;
	}
}

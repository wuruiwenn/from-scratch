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

		//��ͨ���캯��
		//ͨ��һ�� �����ַ��� ����ʼ��һ��String����
		//���ľ��ǣ���Ҫִ���ڴ���� new char[]��Ȼ��ʹ��for���γ�ʼ��ÿ���ַ�
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
			/*
			Ĭ�� �������죬��ǳ������
			this->m_size = s.m_size;
			this->m_buffer = s.m_buffer; ������,�����õ�����ͬһ����ַ
				
			1��ǳ��������Ŀ����󣬵�ǰ��������ʱ������delete m_buffer��
				���ͳһ�ڴ汻���delete
			2��ǳ������������Ҫfor����ÿ���ַ���ֵ�ˣ�
			��Ϊm_buffer�����׵�ַ����Դ��������ַ���ʼ��Ϊ\0�ˣ�
			���Կ�����Ķ���Ҳ���Զ�ֹͣ��Ҳ��֪���������ַ�������
			3���������һ����Ҫfor���θ�ÿ���ַ���ֵ�ģ���Ϊ������൱������
			һ���µĵ�ַ�ϲ����������ǿյģ���û��Դ������ַ������ݴ���
			*/
			//���
			int n = s.m_size;
			this->m_size = n;
			this->m_buffer = new char[n+1];//���������newһ���µĵ�ַ
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
			if (&s == this) {//�����ͬһ��������ֱ��return
				return *this;
			}
			/*����=��ֵ���������ʱ���ǣ���ǰ����this�Ѿ�����ʼ��
			���ԣ�ֻ����other�����ݶ�this��ʹ��for�Ը��ַ����θ��Ǽ���
			
			��Ҫע�� Դ�ַ�����this�����ܳ��Ȳ�һ������Ҫʹ��Դ�ַ����ĳ��Ƚ��и���
			������� new char[] ���·������Դ�ַ�����С�������ȣ�
			�������Ҫ���������\0*/

			this->m_size = s.m_size;
			int n = this->m_size;
			this->m_buffer = new char[n + 1];
			//��ʱ��ǰ�������Ѿ���ʼ���˵ģ��������³�ʼ��new char[]
			//ֻ����forֱ�Ӹ������ݼ���
			for (int i = 0; i < n; i++) {
				m_buffer[i] = s.m_buffer[i];
			}
			m_buffer[n] = '\0';
			cout << "String = ��ֵ�����\n";
			return *this;
		}

		//�ƶ����캯��
		//�ƶ�����Ϳ��������������ǣ��ƶ�������Ҫ�����Դ������nullptr
		//�ҵ�ǰ����this��δ��ʼ����������Ҫnew char[]��ʼ���ڴ�
		String(String&& s) {
			
			this->m_size = s.m_size;
			int n = m_size;
			
			m_buffer = new char[m_size + 1];
			for (int i = 0; i < m_size; i++) {
				m_buffer[i] = s.m_buffer[i];
			}
			m_buffer[m_size] = '\0';

			//Ϊ�˱����"�ƶ�"������"����"��ԴĿ�����Ҫ"�ÿ�"
			s.m_buffer = nullptr;
			s.m_size = 0;

			cout << "String �ƶ�����\n";
		}

		//�ƶ� = ��ֵ�����
		//=��ֵ���������ʱ���ǣ���ǰ����this�Ѿ���ʼ����
		//���ֻ��ʹ��Դ��������ݣ���this���и��Ǽ��ɣ�Ȼ��Դ������nullptr
		//��Ҫע��Դ�����this�ַ������ȿ��ܲ�һ���������Ҫ���·����ڴ� new char[]
		String& operator=(String&& other) {
			if (&other == this) {
				return *this;
			}
			m_size = other.m_size;
			m_buffer = new char[m_size + 1];
			for (int i = 0; i < m_size; i++) {
				m_buffer[i] = other.m_buffer[i];
			}
			m_buffer[m_size] = '\0';

			other.m_size = 0;
			other.m_buffer = nullptr;

			cout << "String�ƶ�=��ֵ�����\n";
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

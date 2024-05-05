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
				��������Ĭ������������������ǳ������ǳ�����Ļ���
				��Ŀ����󣬵�ǰ��������ʱ������delete m_buffer��
				���ͳһ�ڴ汻���delete
			*/
			//this->m_size = s.m_size;
			//this->m_buffer = s.m_buffer; ������,�����õ�����ͬһ����ַ
			//for()...���θ�ֵÿ���ַ�
			//��������ǳ�������Ҿ��ò�����Ҫfor����ÿ���ַ���ֵ�ˣ�
			//��Ϊm_buffer�����׵�ַ�������ˣ���ΪԴ��������ַ���ʼ��Ϊ\0�ˣ�
			//���Կ�����Ķ���Ҳ���Զ�ֹͣ��Ҳ��֪���������ַ������ġ�
			//���������һ����Ҫfor���θ�ÿ���ַ���ֵ�ģ���Ϊ������൱������
			//һ���µĵ�ַ�ϲ����������ǿյģ���û��Դ������ַ������ݴ��ڡ�

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
			if (&s == this) {//�����ͬһ������
				return *this;
			}

			this->m_size = s.m_size;
			int n = this->m_size;
			//this->m_buffer = s.m_buffer;//��������� ǳ������� deleteͬһ�ڴ�����
			//this->m_buffer = new char[n + 1];
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
		//��Ŀ�����s������ת�Ƶ�this
		//�ƶ����� ����ʱ������ǰ����this��ʱ��δ�����죬�Ҵ����Ŀ������� ��ֵ

		//�ƶ�����Ϳ���������һ������ͬ�ģ�����ǰ����this��δ������������Ҫnew char[]��ʼ���ڴ�
		String(String&& s) {
			int n = s.m_size;
			this->m_size = n;
			
			//�ƶ����죬�������ʵ��ǳ������m_buffer = other.m_buffer��
			//�����Ҿ���C++���Ĭ�ϵ��ƶ����죬ҲӦ�þ�������ǳ����+Դ������nullptr��
			//��Ϊ��Դ����other.m_buffer�ս�����nullptr��������ڶ��deleteͬһ�ڴ�����
			//�������Ļ���m_bufferҲ������for���ǣ�ֱ�Ӹ��� m_buffer���ɡ�
			//this->m_buffer = new char[n + 1];
			//for (int i = 0; i < n; i++) {//Ŀ�����������ƶ���this
			//	this->m_buffer[i] = s.m_buffer[i];
			//}
			//this->m_buffer[n] = '\0';
			this->m_buffer = s.m_buffer;

			//Ϊ�˱����"�ƶ�"������"����"��ԴĿ�����Ҫ"�ÿ�"
			s.m_buffer = nullptr;
			s.m_size = 0;

			cout << "String �ƶ�����\n";
		}

		//�ƶ� = ��ֵ�����
		//�ƶ�=��ֵ������Ϳ���=��ֵ�������һ������ͬ�ģ���ǰ����this�Ѿ�����ʼ���ˣ���������new char[]
		//��ȻҲ���� m_buffer = other.m_buffer����Ϊother.m_buffer�ս���nullptr������������delete ͬһ�ڴ�����
		//���Ⲣ������"�ƶ�"����ƶ�Ӧ����Դ�������ж������ƶ���this�ϣ�����m_buffer
		String& operator=(String&& s) {
			if (&s == this) {
				return *this;//�����ͬһ������ֱ�ӷ���
			}
			int n = s.m_size;
			this->m_size = n;

			//this->m_buffer = new char[n + 1];
			/*for (int i = 0; i < n; i++) {
				this->m_buffer[i] = s.m_buffer[i];
			}
			this->m_buffer[n] = '\0';*/
			this->m_buffer = s.m_buffer;

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

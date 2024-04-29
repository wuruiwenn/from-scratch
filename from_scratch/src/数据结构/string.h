#pragma once

//实现类似 Java String

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
			cout << "String 析构函数\n";
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
			cout << "String 构造函数\n";
		}
		//拷贝构造函数
		//拷贝构造调用的时机：当前对象，即this，此时并没有被构造
		//正是通过传进来的目标对象进行构造
		String(const String& s) {
			int n = s.m_size;
			//this->m_buffer = s.m_buffer;//拷贝构造默认是这样，但是这是浅拷贝，浅拷贝的话，在目标对象，当前对象析构时，都会delete m_buffer，造成统一内存被多次delete
			this->m_buffer = new char[n+1];//深拷贝
			this->m_size = n;
			for (int i = 0; i < n; i++) {
				m_buffer[i] = s.m_buffer[i];
			}
			m_buffer[n] = '\0';
			cout << "String 拷贝构造函数\n";
		}

		//拷贝 = 赋值运算符
		// = 赋值运算符调用时机：当前对象，即this已经被初始化了，
		// 等待传入的目标对象覆盖自己
		String& operator=(const String& s){
			if (&s == this) {//如果是同一个对象
				return *this;
			}
			int n = s.m_size;
			this->m_size = n;
			//this->m_buffer = s.m_buffer;//这样会造成 浅拷贝多次 delete同一内存问题
			//this->m_buffer = new char[n + 1];//此时当前对象是已经初始化了的，不必重新初始化
			//只需覆盖
			for (int i = 0; i < n; i++) {
				m_buffer[i] = s.m_buffer[i];
			}
			m_buffer[n] = '\0';
			cout << "String = 赋值运算符\n";
			return *this;
		}

		//移动构造函数
		//把目标对象s的内容转移到this
		//移动构造 调用时机：当前对象this此时还未被构造，且传入的目标对象是 右值
		String(String&& s) {
			int n = s.m_size;
			this->m_size = n;
			this->m_buffer = new char[n + 1];
			for (int i = 0; i < n; i++) {//目标对象的内容移动到this
				this->m_buffer[i] = s.m_buffer[i];
			}
			this->m_buffer[n] = '\0';
			s.m_buffer = nullptr;//目标对象"置空"
			s.m_size = 0;

			cout << "String 移动构造\n";
		}

		//移动 = 赋值运算符
		String& operator=(String&& s) {
			int n = s.m_size;
			this->m_size = n;
			//this->m_buffer = new char[n + 1];
			for (int i = 0; i < n; i++) {
				this->m_buffer[i] = s.m_buffer[i];
			}
			this->m_buffer[n] = '\0';
			s.m_buffer = nullptr;//目标对象"置空"
			s.m_size = 0;
			cout << "String = 移动赋值运算符\n";
			return *this;
		}

		//使得String对象可隐式转换为一个bool值
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

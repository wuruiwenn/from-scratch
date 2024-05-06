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

		//普通构造函数
		//通过一个 常量字符串 来初始化一个String对象
		//核心就是，需要执行内存分配 new char[]，然后使用for依次初始化每个字符
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
			/*
			默认 拷贝构造，是浅拷贝：
			this->m_size = s.m_size;
			this->m_buffer = s.m_buffer; 仅这样,拷贝得到的是同一个地址
				
			1、浅拷贝，在目标对象，当前对象析构时，都会delete m_buffer，
				造成统一内存被多次delete
			2、浅拷贝，并不需要for依次每个字符赋值了，
			因为m_buffer就是首地址，且源对象最后字符初始化为\0了，
			所以拷贝后的对象也会自动停止，也即知道完整的字符串在哪
			3、深拷贝后，是一定需要for依次给每个字符赋值的，因为深拷贝，相当于是在
			一个新的地址上操作，内容是空的，并没有源对象的字符串内容存在
			*/
			//深拷贝
			int n = s.m_size;
			this->m_size = n;
			this->m_buffer = new char[n+1];//深拷贝，就是new一个新的地址
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
			if (&s == this) {//如果是同一个对象，则直接return
				return *this;
			}
			/*由于=赋值运算符调用时机是：当前对象this已经被初始化
			所以，只需用other的内容对this，使用for对各字符依次覆盖即可
			
			但要注意 源字符串和this，可能长度不一样，需要使用源字符串的长度进行覆盖
			因此仍需 new char[] 重新分配符合源字符串大小的数组宽度，
			并且最后要处理结束符\0*/

			this->m_size = s.m_size;
			int n = this->m_size;
			this->m_buffer = new char[n + 1];
			//此时当前对象是已经初始化了的，不必重新初始化new char[]
			//只需用for直接覆盖内容即可
			for (int i = 0; i < n; i++) {
				m_buffer[i] = s.m_buffer[i];
			}
			m_buffer[n] = '\0';
			cout << "String = 赋值运算符\n";
			return *this;
		}

		//移动构造函数
		//移动构造和拷贝构造的区别就是：移动构造需要额外把源对象置nullptr
		//且当前对象this仍未初始化，所以需要new char[]初始化内存
		String(String&& s) {
			
			this->m_size = s.m_size;
			int n = m_size;
			
			m_buffer = new char[m_size + 1];
			for (int i = 0; i < m_size; i++) {
				m_buffer[i] = s.m_buffer[i];
			}
			m_buffer[m_size] = '\0';

			//为了表达是"移动"，而非"拷贝"，源目标对象要"置空"
			s.m_buffer = nullptr;
			s.m_size = 0;

			cout << "String 移动构造\n";
		}

		//移动 = 赋值运算符
		//=赋值运算符调用时机是：当前对象this已经初始化了
		//因此只需使用源对象的内容，对this进行覆盖即可，然后源对象置nullptr
		//但要注意源对象和this字符串长度可能不一样，因而需要重新分配内存 new char[]
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

			cout << "String移动=赋值运算符\n";
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

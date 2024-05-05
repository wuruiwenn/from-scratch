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
				拷贝构造默认是这样，但是这是浅拷贝，浅拷贝的话，
				在目标对象，当前对象析构时，都会delete m_buffer，
				造成统一内存被多次delete
			*/
			//this->m_size = s.m_size;
			//this->m_buffer = s.m_buffer; 仅这样,拷贝得到的是同一个地址
			//for()...依次赋值每个字符
			//【不过，浅拷贝，我觉得并不需要for依次每个字符赋值了，
			//因为m_buffer就是首地址，拷贝了，因为源对象最后字符初始化为\0了，
			//所以拷贝后的对象也会自动停止，也即知道完整的字符串在哪】
			//【深拷贝后，是一定需要for依次给每个字符赋值的，因为深拷贝，相当于是在
			//一个新的地址上操作，内容是空的，并没有源对象的字符串内容存在】

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
			if (&s == this) {//如果是同一个对象
				return *this;
			}

			this->m_size = s.m_size;
			int n = this->m_size;
			//this->m_buffer = s.m_buffer;//这样会造成 浅拷贝多次 delete同一内存问题
			//this->m_buffer = new char[n + 1];
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
		//把目标对象s的内容转移到this
		//移动构造 调用时机：当前对象this此时还未被构造，且传入的目标对象是 右值

		//移动构造和拷贝构造有一点是相同的：即当前对象this还未构建，所以需要new char[]初始化内存
		String(String&& s) {
			int n = s.m_size;
			this->m_size = n;
			
			//移动构造，这里可以实现浅拷贝：m_buffer = other.m_buffer，
			//而且我觉得C++类的默认的移动构造，也应该就是类似浅拷贝+源对象置nullptr的
			//因为，源对象，other.m_buffer终将被置nullptr，不会存在多次delete同一内存问题
			//那这样的话，m_buffer也无需用for覆盖，直接覆盖 m_buffer即可。
			//this->m_buffer = new char[n + 1];
			//for (int i = 0; i < n; i++) {//目标对象的内容移动到this
			//	this->m_buffer[i] = s.m_buffer[i];
			//}
			//this->m_buffer[n] = '\0';
			this->m_buffer = s.m_buffer;

			//为了表达是"移动"，而非"拷贝"，源目标对象要"置空"
			s.m_buffer = nullptr;
			s.m_size = 0;

			cout << "String 移动构造\n";
		}

		//移动 = 赋值运算符
		//移动=赋值运算符和拷贝=赋值运算符有一点是相同的：当前对象this已经被初始化了，所以无需new char[]
		//当然也可以 m_buffer = other.m_buffer，因为other.m_buffer终将被nullptr，不会产生多次delete 同一内存问题
		//但这并不符合"移动"理念，移动应该是源对象所有东西都移动到this上，包括m_buffer
		String& operator=(String&& s) {
			if (&s == this) {
				return *this;//如果是同一个对象，直接返回
			}
			int n = s.m_size;
			this->m_size = n;

			//this->m_buffer = new char[n + 1];
			/*for (int i = 0; i < n; i++) {
				this->m_buffer[i] = s.m_buffer[i];
			}
			this->m_buffer[n] = '\0';*/
			this->m_buffer = s.m_buffer;

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

#pragma once
#include"headers.h"

namespace wrw {
	class string
	{
	private:
		char* m_ptr;
		int m_size;
		int m_capacity;
	public:
		//构造函数
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

		//合并为带默认参数的构造函数
		string(const char* str = "")
			: m_size(strlen(str)) {
			m_capacity = m_size;
			m_ptr = new char[m_capacity + 1];
			strcpy(m_ptr, str);
		}

		//析构
		~string() {
			delete[] m_ptr;
			m_size = m_capacity = 0;
		}

		//拷贝构造
		string(const string& other) {
			m_size = other.m_size;
			m_capacity = m_size;
			m_ptr = new char[m_capacity + 1];//默认拷贝构造是浅拷贝，这里必须实现深拷贝，否则double delete
			strcpy(m_ptr, other.m_ptr);
			cout << "string拷贝构造\n";
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
			cout << "string拷贝 = 赋值运算符\n";
			return *this;
		}

	public:
		const char* c_str() {
			return m_ptr;
		}

		char& operator[](int pos) {//允许外部通过[]来修改string对象内的字符
			_ASSERT(pos < m_size);
			return m_ptr[pos];
		}
		const char& operator[](int pos) const {//首部也可加上const，禁止外部修改该字符
			_ASSERT(pos < m_size);
			return m_ptr[pos];
		}

		int size() const {
			return m_size;
		}

		void Print(const string& str) {
			for (int i = 0; i < m_size; i++) {
				cout << str[i] << " ";//这里遍历，肯定不允许通过[]修改string对象的，所以operator[]必须是const
			}
			cout << endl;
		}
	public:
		//实现 string 迭代器
		//定义为 内部类
		class string_iterator {
		private:
			char* obj;
		public:
			string_iterator(char* ptr = nullptr) :obj(ptr) {}

			//正向迭代
			string_iterator& operator++() {//++i
				++obj;//本身就是指向一个char单位的指针，直接++，每次++跳跃一个char宽度
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
		//定义 迭代器 类型别名
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
//	cout << "迭代器访问string\n";
//	for (auto it = s.begin(); it != s.end(); it++) {
//		cout << (*it) << " ";
//	}
//	cout << endl;
//	for (auto cur : s) {//本质就是调用迭代器，目标对象实现了迭代器就能使用
//		cout << cur << " ";
//	}
//	cout << endl;
//
//	//迭代器操作
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
//	cout << "it3 == it4：" << (it3 == it4) << endl;
//
//}

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
			cout << "~string析构\n";
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
			cout << "string构造函数\n";
			m_size = strlen(str);
			m_capacity = strlen(str);
			m_str = new char[m_size + 1];
			strncpy(m_str, str,m_size+1);
		}*/
		string(const char* str = "") {
			cout << "string无参、有参构造合并\n";
			m_size = strlen(str);
			m_capacity = strlen(str);
			m_str = new char[m_size + 1];
			strcpy(m_str, str);
		}
	public:
		const char* c_str() {
			return m_str;
		}

		//string的operator []的2个重载
		//用于实现str[i]='x'的修改
		char& operator[](int pos) {
			return m_str[pos];
		}
		//用于string打印
		const char& operator[](int pos) const{
			return m_str[pos];
		}
	public:
		//实现string的迭代器
		//string的迭代器就是一个char*，相对的，容器list的迭代器是一个指向list节点的 node*
		class string_iterator {
		private:
			char* ptr;
		public:
			string_iterator(char* obj) :ptr(obj) {}

			char operator*() {// auto it = string.begin(), *it返回指向的字符就行
				return *ptr;
			}
			//char* operator->() {//auto it = string.begin(),it->，普通类型指针没有->操作
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
			//str[i] = '9';这里当然不能修改，因为这里str是const
		}
		out << "]\n";
		return out;
	}
};

/*
需解决：
	（1） c_str()返回空字符串时候，如何打印内容？
	（2） 无参构造、有参构造合并
	（3）operator[] const权限匹配问题
*/

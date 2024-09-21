#pragma once

/*
	C++ std::string 的写时拷贝
	涉及到的知识：
		1、拷贝构造函数、拷贝=赋值运算符
		2、运算符重载，特别是[]
		3、引用计数
		4、proxy代理设计模式

	还没实现完，参考：
	https://blog.csdn.net/weixin_48617416/article/details/122182780

	https://blog.csdn.net/HappyKocola/article/details/72457003?spm=1001.2101.3001.6650.6&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-72457003-blog-122182780.235%5Ev43%5Epc_blog_bottom_relevance_base1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-72457003-blog-122182780.235%5Ev43%5Epc_blog_bottom_relevance_base1&utm_relevant_index=13

*/

namespace wrw_
{
	class string
	{
	public:
		char* obj;
		int m_size;
		int* p_cnt;//引用计数
	public:
		//构造函数
		string() :obj(nullptr), p_cnt(nullptr), m_size(0) {

		}
		string(const char* ptr) {
			int n = strlen(ptr);
			m_size = n;
			obj = new char[m_size + 1];
			p_cnt = new int(1);
			strcpy(obj, ptr);
		}
	public:
		//拷贝构造函数（理应触发 隐式共享）
		string(const string& other) {
			obj = other.obj;//浅拷贝，就可实现 string隐式共享
			m_size = other.m_size;
			p_cnt = other.p_cnt;
			++(*p_cnt);
		}
		//拷贝 = 赋值运算符（拷贝赋值：理应触发 写时拷贝 动作）
		string& operator=(const string& other)
		{
			if (this != &other)
			{
				if (p_cnt && (*p_cnt) > 1)
				{
					//先拷贝 (不用拷贝，直接用新的覆盖旧的即可）
					//再修改元素——写操作
					release();
					m_size = other.m_size;
					obj = new char[m_size + 1];
					p_cnt = other.p_cnt;
					++(*p_cnt);
				}
			}
			return *this;
		}
		//s[i] = 'A'，这种修改，也应该触发 写时拷贝
		//这里有个问题就是，s[i]我们如何知道是要进行读操作、还是，写操作呢？
		char& operator[](int pos) {
			return obj[pos];
		}

		void release()//断开所指向的目标字符串
		{
			obj = nullptr;
			p_cnt = nullptr;
		}
	public:
		int size() const {
			return m_size;
		}
	public:
		friend std::ostream& operator<<(std::ostream& stream, const string& s);
	};
	std::ostream& operator<<(std::ostream& stream, const string& s) {
		stream << "[";
		stream << s.obj << "]\n";
		return stream;
	}
}

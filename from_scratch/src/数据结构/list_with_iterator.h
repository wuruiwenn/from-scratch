#pragma once

//带迭代器的单链表
//是STL中List、iterator的一个简单实现

#include<iostream>
#include<memory>
#include<utility>
#include<vector>
#include<numeric>
#include<string>
#include<algorithm>
#include<map>
#include<functional>

using std::endl;
using std::cout;
using std::map;
using std::vector;
using std::string;

namespace wrw
{
	template<class T>
	struct Node {
		T val;
		Node* next;
		Node(const T& value)
			:val(value), next(nullptr)
		{}
	};

	template<class T>
	class MyList {
	private:
		Node<T>* head;
		Node<T>* tail;
		int size;
	public://MyList 的构造方法
		MyList()
			:head(nullptr), tail(nullptr), size(0)
		{}
	private://内部类：迭代器 类模板
		template<class T>
		class list_iterator {
		private:
			Node<T>* obj;
		public:
			//Mylist<int>::list_iterator it = l.begin()
			list_iterator(Node<T>* ptr = nullptr)
				:obj(ptr)
			{}
			//一些操作符
			//迭代器的核心操作：++i、i++
			list_iterator& operator++() {//++i
				obj = obj->next;
				return *this;
			}
			list_iterator operator++(int) {//i++
				//list_iterator tmp(*this);
				list_iterator tmp = *this;
				//obj = obj->next;
				++(*this);//直接调用重载后的++
				return tmp;
			}

			T& operator*() {
				//return (*obj).val;
				return obj->val;
			}
			Node<T>* operator->() {
				return obj;
			}

			bool operator==(const list_iterator& other) {
				return other.obj == obj;
			}

			bool operator!=(const list_iterator& other) {
				return other.obj != obj;
			}
		};

	public://MyList 成员方法
		void push_back(const T& val) {
			if (head == nullptr) {
				head = new Node(val);
				tail = head;
			}
			else {
				tail->next = new Node(val);
				tail = tail->next;
			}
			size++;
		}
	public://容器和迭代器 建立关联
		//typedef list_iterator iterator;
		using iterator = list_iterator<T>;//类型别名

		//迭代器 头部、尾部
		// Mylist<int>::iterator it = lst.begin()
		iterator begin() {
			return iterator(head);
		}
		iterator end() {
			return iterator(tail->next);
		}


		template<class T>
		friend std::ostream& operator<<(std::ostream& out, const MyList<T>& l);
	};
	template<class T>
	std::ostream& operator<<(std::ostream& out, const MyList<T>& l) {
		if (l.size == 0) {
			out << "[]\n";
			return out;
		}
		Node<T>* ptr = l.head;
		out << "[";
		while (ptr != l.tail) {
			out << ptr->val << "->";
			ptr = ptr->next;
		}
		out << l.tail->val << "]\n";
		return out;
	}
	
}


/*
	int main() {
		MyList<int> list;
		for (int k = 1; k <= 5; k++) {
			list.push_back(k);
		}
		cout << list;

		cout << "\n..........使用迭代器进行遍历.............\n";
		for (MyList<int>::iterator it = list.begin(); it != list.end(); it++) {
			cout << *it << endl;
		}
	}
*/
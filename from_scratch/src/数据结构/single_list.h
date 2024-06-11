#pragma once

//单链表

#include<iostream>

namespace wrw
{
	using std::cout;
	using std::endl;

	struct Node {
		int val;
		Node* next;
		Node(int v) :val(v) {}
	};
	class SingleList {
	private:
		Node* head;
		int size;
	public:
		SingleList() {
			head = new Node(-1);
			head->next = nullptr;
			size = 0;
		}
		void addHead(int c) {
			++size;
			Node* node = new Node(c);
			if (head->next == nullptr) {
				head->next = node;
				return;
			}
			node->next = head->next;
			head->next = node;
		}
		void addLast(int c) {
			++size;
			Node* node = new Node(c);
			if (head->next == nullptr) {
				head->next = node;
				node->next = nullptr;
				return;
			}
			Node* ptr = head;
			while (ptr->next != nullptr) {
				ptr = ptr->next;
			}
			ptr->next = node;
			node->next = nullptr;
		}
		//移除值为val的节点
		void removeVal(int val) {
			Node* ptr = head;

			while (ptr != nullptr){
				//如果下一个节点 非空且是目标值，就删除且继续判断
				while (ptr->next != nullptr && ptr->next->val == val) {
					ptr->next = ptr->next->next;
					size--;
				}
				ptr = ptr->next;
			}
		}
		//移除尾结点
		void removeLast() {
			//removeVal();
		}
		//反转链表
		void reverse() {
			Node* p = head;
			Node* tmp = nullptr;
			while (p != nullptr) {
				Node* remNext = p->next;//先记住当前节点的下一个
				p->next = tmp;
				tmp = p;
				p = remNext;
			}
			head = tmp;
		}
		int GetSize() {
			return size;
		}
		friend std::ostream& operator<<(std::ostream& out, const SingleList& s);
	};
	std::ostream& operator<<(std::ostream& out, const SingleList& s) {
		cout << "\n======================\n";
		Node* tmp = s.head;
		out << "[" << tmp->val << "]";
		while (tmp->next != nullptr) {
			out << " -> " << tmp->next->val;
			tmp = tmp->next;
		}
		out << " -> nullptr";
		cout << "\n======================\n";
		return out;
	}
}

/*也可以这样实现，用head，tail2个指针表示单链表的头和尾*/

/*
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
public:
	MyList()
		:head(nullptr),tail(nullptr),size(0)
	{}
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
int main() {
	MyList<int> list;
	for (int k = 1; k <= 5; k++) {
		list.push_back(k);
	}
	cout << list;
}

*/
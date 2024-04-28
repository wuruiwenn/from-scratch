#pragma once

//������

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
		//�Ƴ�ֵΪval�Ľڵ�
		void removeVal(int val) {
			Node* ptr = head;

			while (ptr != nullptr){
				//�����һ���ڵ� �ǿ�����Ŀ��ֵ����ɾ���Ҽ����ж�
				while (ptr->next != nullptr && ptr->next->val == val) {
					ptr->next = ptr->next->next;
					size--;
				}
				ptr = ptr->next;
			}
		}
		//�Ƴ�β���
		void removeLast() {
			//removeVal();
		}
		//��ת����
		void reverse() {
			Node* p = head;
			Node* tmp = nullptr;
			while (p != nullptr) {
				Node* remNext = p->next;//�ȼ�ס��ǰ�ڵ����һ��
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

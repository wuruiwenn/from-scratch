#pragma once

#include<iostream>

using std::cout;
using std::endl;

class Entity {
private:
	int id;
public:
	Entity(int d) :id(d) { cout << "Entity����\n"; }
	~Entity() { cout << "Entity����\n"; }
	void printId() { cout << "printId = " << id << endl; }
	friend std::ostream& operator<<(std::ostream& out, const Entity& obj);
};
std::ostream& operator<<(std::ostream& out, const Entity& obj) {
	if (&obj) {//����գ��򲻴�ӡ�κζ���
		out << "[Entity: " << obj.id << "]\n";
		return out;
	}
	out << "[]\n";
	return out;
}
namespace wrw
{
	//����ָ�룬������һ��class template
	template<class T>
	class unique_ptr {
	private:
		T* obj;//���ڰ�Ŀ������ָ��
	public:
		//���캯��
		unique_ptr() :obj(nullptr) {
			cout << "unique_ptr �޲ι���.\n";
		}
		unique_ptr(T* ptr) :obj(ptr) {
			cout << "unique_ptr �вι���.\n";
		}

		//��������
		~unique_ptr() {
			cout << "~unique_ptr ����.\n";
			delete obj;
		}

		// ɾ�� �������캯�� �� "="��ֵ����������ֹ ����
		unique_ptr(const unique_ptr& other) = delete;
		unique_ptr& operator=(const unique_ptr& other) = delete;

		//�ƶ����캯��
		//�ƶ����죬�������ݵĶ���(����this)�ǿյģ�û�г�ʼ����
		//�ƶ����죬���������Ǻ� �������죬�ƶ����첢������
		//Ŀ���������������£��ƶ�������Ҫת�ƿ���Ȩ��
		//�ƶ�ǰ���¾ɿ��Ʒ����ǰ󶨵�ͬһ��Ŀ�����
		//���Կ϶����ܶ�ԭʼ�Ŀ��Ʒ�����delete������Ŀ�����Ҳ�ᱻ�ͷ�
		//�ҵ�����"�ƶ�"����ɵĿ��Ʒ�һ��Ҫ�ÿ� ����nullptr
		unique_ptr(unique_ptr&& other) noexcept {
			this->obj = other.obj;
			other.obj = nullptr;
		}

		//�ƶ�=��ֵ�����
		//��ֵ���㣬�������ݵĶ���(����this)���Ѿ��а󶨾ɵ�Ŀ�����ģ�=��ֵ������Ҫ���µ�Ŀ�����
		//����this�����ݾ��������Ƶľɵ���Դ������Ҫdelete��
		//�ҵ�����"�ƶ�"����ɵĿ��Ʒ�һ��Ҫ�ÿ� ����nullptr
		unique_ptr& operator=(unique_ptr&& other) noexcept {
			if (this != &other) {//�������ͬһ�������..�������Ը�ֵ
				delete obj;//�ӹ��µ���Դ֮ǰ��Ҫ��֮ǰ����Դ�ͷŵ�
				this->obj = other.obj;
				//other.obj = nullptr;
			}
			other.obj = nullptr;
			return *this;
		}

		//ֻҪ�ǣ��ƶ�����/��ֵ�����ƶ���Դ����ָ��϶�����Ҫ��nullptr��
		//���ǲ���delete����Ϊ�¾�����ָ��ָ�����ͬһĿ�����
		//ֻ���ƶ��󣬾ɵ�����ָ�벻�ٹ�������

		//������*�����
		T& operator*() {
			return *obj;
		}

		//��Ա���� -> �����
		T* operator->() {
			return obj;
		}

		//get()�����ذ󶨶����ԭʼָ�룬����ָ��Ŀ���Ȩ����
		//ע������constҪ�� operator<<���غ����ڵĲ��� constͳһ�������"��ʧ�޶���const"
		T* get() const {
			return obj;
		}

		//release()�����ذ󶨶����ԭʼָ�룬��������ָ��Ŀ���Ȩ�ÿ�
		T* release() {
			T* tmp = obj;
			//delete obj; ������delete������Ŀ�������ᱻ�ͷ�
			obj = nullptr;//�õ�ǰ����ָ��ָ��գ�������ָ���Ŀ�����
			return tmp;
		}

		//reset()���ͷ������е�Ŀ����󣬿ɽ���һ����ѡ�Ĳ��������Ǽ���Ҫ�ӹܵ��µ�Ŀ������ָ��
		//��ѡ���������Ǵ�Ĭ��ֵ
		void reset(T* ptr = nullptr) {
			//�������Ҫ�ж�2���㣺
				//��1���ǲ��Ǵ������µ�ָ�� 
				//��2�������Ŀ������ǲ��Ǿ��ǵ�ǰ�Ѿ����Ƶ�ͬһ��Ŀ�����

			/*if (ptr == nullptr) {
				delete obj;
			}
			else {
				if (ptr == obj) {

				}
				else {
					delete obj;
					obj = ptr;
				}
			}*/
			delete obj;
			obj = nullptr;//����Ŀ�����delete��Σ���Ϊ��ǰ����ָ�������ջ���󣬳���main�����������ʱҲ��delete obj;��ôobj�����ָ��Ŀ���������ٴ�delete����ʵ�ʵ�ǰ����ָ��󶨵�Ŀ�������e��������������Ϊ��main���ǶѶ���
			if (ptr) {
				obj = ptr;
			}

			//�����д��
			/*if (obj != ptr) {
				delete obj;
				obj = ptr;
			}*/
		}
		void swap(unique_ptr& other) {
			T* tmp = this->obj;
			this->obj = other.obj;
			other.obj = tmp;
		}

		//����unique_ptr�Ķ�����ʽת��Ϊһ��bool���� ����if(up){}��Ϊ����
		explicit operator bool() {
			return obj != nullptr;
		}

		template<class T>//��Ԫ������Ҫ �������� ģ�壬��Ϊ��Ԫ�����������ڳ�Ա�������������ʼ������ģ��
		friend std::ostream& operator<<(std::ostream& out, const unique_ptr<T>& up);
	};
	template<class T>
	std::ostream& operator<<(std::ostream& out, const unique_ptr<T>& up) {
		if (up.get()) {
			out << up.get();//std::unique_ptr�ж���"<<"�����أ��ǰ� get()��������������ʾ��� obj
		}
		return out;
	}
}
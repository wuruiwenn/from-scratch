#pragma once

/*
	shared_ptr的核心是：引用计数
*/

namespace wrw
{
	template<class T>
	class shared_ptr {
	private:
		T* obj; //执行绑定的目标对象的指针
		int* p_cnt;//指向 目标对象的引用计数 的 指针
	public:
		// <普通构造函数>
		shared_ptr() :obj(nullptr), p_cnt(nullptr) {}
		shared_ptr(T* ptr) :obj(ptr), p_cnt(new int(1)) {}

		// <析构函数>
		~shared_ptr() {
			cout << "shared_ptr 析构\n";
			if (p_cnt != nullptr && (--(*p_cnt)) == 0) {
				cout << "目标对象 引用计数 = 0，释放目标对象 delete obj.\n";
				delete obj;
				delete p_cnt;
			}
			obj = nullptr;
			p_cnt = nullptr;
		}

		/*
			<拷贝构造>：
			更新引用计数
			由于p_cnt是持有目标对象的引用计数的指针，
			所以只需更新this的引用计数，实地访问地址更新即可
		*/
		shared_ptr(const shared_ptr& other) {
			obj = other.obj;
			p_cnt = other.p_cnt;

			++(*p_cnt);
			cout << "shared_ptr拷贝构造\n";
		}

		/*
			<拷贝 = 赋值运算符>
		*/
		shared_ptr& operator=(const shared_ptr& other) {
			//若是同一个shared_ptr对象，或2个不同shared_ptr但绑定了同一目标对象
			if (&other == this || other.obj == this->obj) {
				return *this;
			}

			this->release();//取消针对当前目标对象的绑定(若引用计数=0，则会delete)
			obj = other.obj;//绑定新的对象
			p_cnt = other.p_cnt;//这里反而必须是浅拷贝才行，因为p_cnt是目标对象的引用计数，所有shared_ptr对于该目标对象的引用计数，都是指向同一个地方
			++(*p_cnt);//更新目标对象的引用计数

			cout << "shared_ptr 拷贝 = 赋值运算符\n";
			return *this;
		}


		// <移动构造>
		shared_ptr(shared_ptr&& other) {

			obj = other.obj;
			p_cnt = other.p_cnt;

			//引用计数应该是先-1，然后+1，所以无需改变

			other.obj = nullptr;//源对象置空
			other.p_cnt = nullptr;

			cout << "shared_ptr 移动构造\n";
		}



		// <移动 = 赋值运算符>
		shared_ptr& operator=(shared_ptr&& other) {
			if (&other == this) {
				return *this;
			}

			//如果不是同一sp对象，但是绑定的obj是同一个，仍然是可操作的
			//但如果2个sp对象绑定的obj不同，则操作应该是不一样的
			if (this->obj == other.obj)//若绑定同一个对象，被move的sp对象置空，p_cnt置空。且其他sp拥有的p_cnt-1.
			{
				//因为绑定的是同一个obj，所以this和other 的p_cnt应该指向了同一个地方，操作谁都可
				/*--(*other.p_cnt);
				other.obj = nullptr;
				other.p_cnt = nullptr;*/
				other.release();
			}
			else//绑定的是不同对象，p_cnt相当于没有更新，因为一加一减
			{
				//这里有问题：this.p_cnt要--，然后才能绑定新的引用计数块，即other的obj的引用计数块
				this->release();
				this->obj = other.obj;
				this->p_cnt = other.p_cnt;
				++(*p_cnt);
				other.release();
			}
			cout << "shared_ptr 移动=赋值运算符\n";
			return *this;
		}



		//一些成员函数

		/*
			use_count():
			返回目标对象的引用计数的个数
		*/
		int use_count() {
			return (p_cnt == nullptr) ? 0 : (*p_cnt);
		}

		/*
			bool unique()：
			返回指针是否具备独占权，即引用计数 = 1
		*/
		bool unique() {
			return (p_cnt != nullptr) && (*p_cnt) == 1;
		}

		/*
			release():
			释放this对当前目标对象的控制权。
			（1）取消针对目标对象的控制权，且该目标对象的计数-1
			（2）若引用计数变为0，则需释放目标对象内存
			<实际std::shared_ptr并没有release()函数，为什么？>
			unique_ptr中有release，因为在某一时刻只能有一个 unique_ptr 指向某个对象，
			release出现的初衷在于，实现目标对象的控制权转移：
				解除unique_ptr所绑定的目标对象的控制权，把控制权转移给另一个unique_ptr对象
				因为unique_ptr是不能复制的，所以只能通过release来把目标对象的控制权进行转移（但好像 移动构造 也可以实现目标对象的控制权转移 ！）
			(这点要和unique_ptr的reset区分开：
				reset是从头到尾都是针对当前这个unique_ptr，reset的初衷在于，更换当前unique_ptr所绑定的目标对象)
			所以，shared_ptr没必要使用release，也就是没必要通过release某一个转移目标对象的控制权
			因为shared_ptr可以通过 拷贝构造 直接实现多个shared_ptr直接获取对同一个目标对象的控制权
		*/
		void release() {
			if (p_cnt != nullptr && (--(*p_cnt)) == 0) {
				delete obj;//因为该目标对象已经没有被任何shared_ptr管理了，所以目标对象可以被析构了
				delete p_cnt;//因为该目标对象已经没有被任何shared_ptr管理了，所以引用计数也没有意义了
			}
			obj = nullptr;
			p_cnt = nullptr;//无论如何，当前shared_ptr不再管理该目标对象了，那么指向该目标对象的引用计数也要断开
		}

		/*
			reset():
			shared_ptr的reset()和unique_ptr的rest()具有很大差异：
			shared_ptr::reset()：会先把目标对象的引用计数减一，如果引用计数为0，才会delete目标对象，否则并不会delete目标对象；若有新对象，则绑定新对象，新对象引用计数+1
			unique_ptr::reset()：会直接delete目标对象，然后若传入新对象，则绑定新对象，新对象引用计数+1

			shared_ptr reset(T* newobj): 有个问题
			这里传入的新对象，直接是目标对象T*
			那么由于传入的是目标对象的指针，怎么获取该目标对象对应的p_cnt呢？
			这种情况：
				若新对象newobj在此之前被shared_ptr(newobj)形式绑定过，那么这里重新绑定，则这个newobj是被多个shared_ptr直接绑定的，(而不是拷贝形式)，会造成double delete问题
				若新对象newobj在此之前没有被shared_ptr绑定过，则可直接绑定，此时 *p_cnt肯定是初始化为 1
		*/
		void reset(T* newobj = nullptr) {
			if (this->obj == newobj) {//如果新绑定对象就是当前绑定的对象，则什么也不做
				return;
			}
			this->release();//解绑旧的目标对象
			if (newobj != nullptr) {//若传入了新的对象，则进行新的绑定
				this->obj = newobj;
				this->p_cnt = new int(1);
			}
		}

		T* get() const {
			return obj;
		}

		//一些操作符
		T& operator*() {
			return *obj;
		}
		T* operator->() {
			return obj;
		}
		explicit operator bool() {
			return obj != nullptr && p_cnt != nullptr;
		}
	};
}
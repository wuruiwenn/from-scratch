#pragma once

/*
	shared_ptr：
	非常简洁、简单的一个shared_ptr实现
	核心2部分：
		绑定目标对象
		目标对象的引用计数

	不涉及weak_ptr

	shared_ptr的核心是：引用计数
	引用计数 = 0，则shared_ptr所绑定的目标对象，应该被delete
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

			//或者：
			//++(*p_cnt);
			//other.release();
			/*
			这里不能先让待移动对象other.release()，因为该shared_ptr对象可能就是唯一管理obj的智能指针对象，
			release后会delete obj，则被管理的目标对象变为nullptr
			导致当前接受移动结果的对象obj指向了一个nullptr

			所以拷贝/移动一个东西，应该先处理完拷贝/移动的目标对象的内容，等拷贝/移动正式完毕后，
			才能把 源对象 置空，而不能先处理待拷贝/移动的源对象，导致还没拷贝/移动完毕就nullptr了

			或者，要么就干脆别更新p_cnt，移动确实无需更新，则这里不要调用release，而是手动置nullptr
			*/

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
				this->release();
				this->obj = other.obj;
				this->p_cnt = other.p_cnt;
				++(*p_cnt);
				other.release();

				/*更合理的流程应该是如下：
				由于this即将接管obj的控制权，所以obj不可能被析构，
				不用执行release内部的 "是否需要析构"的判断过程。
				this->release();
				this->obj = other.obj;
				this->p_cnt = other.p_cnt;
				++(*p_cnt);
				--(*p_cnt);
				other.obj = nullptr;
				other.p_cnt = nullptr;
				*/
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
				reset是从头到尾都是针对当前这个unique_ptr对象，reset的初衷在于，更换当前unique_ptr所绑定的目标对象)
				即：release是给同一个目标对象obj更换不同的unique_ptr智能指针对象进行绑定；
					reset是同一个unique_ptr智能指针对象，去更换不同的目标对象obj的绑定。
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
			shared_ptr::reset()：会先把目标对象的引用计数减一，如果引用计数为0，才会delete目标对象，否则并不会delete目标对象；若有新对象，则绑定新对象，新对象引用计数 初始化为1 (而不是+1)
			unique_ptr::reset()：会直接delete目标对象，然后若传入新对象，则绑定新对象，新对象引用计数+1

			shared_ptr reset(T* newobj): 有个问题
			这里传入的新对象，直接是目标对象T*
			那么由于传入的是目标对象的指针，怎么获取该目标对象对应的p_cnt呢？
			这种情况：
				若新对象newobj在此之前被shared_ptr(newobj)形式绑定过，那么这里重新绑定，则这个newobj是被多个shared_ptr直接绑定的，(而不是拷贝形式)，会造成double delete问题
				若新对象newobj在此之前没有被shared_ptr绑定过，则可直接绑定，此时 *p_cnt肯定是初始化为 1
		但是你可能会想，如果有以下情况：
		User* u1 = new User(1);
		User* u2 = new User(2);
		User* u3 = new User(3);
		using std::shared_ptr;这是标准std的shared_ptr
		shared_ptr<User> sp1(u1);
		shared_ptr<User> sp2(sp1);
		shared_ptr<User> sp3(u3);
		sp3.reset(u1);

		cout << "sp1.use_count = " << sp1.use_count() << endl;// 2
		cout << "sp2.use_count = " << sp2.use_count() << endl;// 2
		cout << "sp3.use_count = " << sp3.use_count() << endl;// 1
		首先，这里程序运行，直接编译报错了，
		因为这里sp3，sp1都以这种直接(u1)传入构造函数的方式控制u1，
		这种行为，std::shared_ptr是不允许的，会产生double delete问题，

		而且，你会发现，这里关于u1的use_count应该是3，因为他被sp1，sp2，sp3都接管了
		但是其实不是的，这里std::shared_ptr本身对于reset的实现结果可见：
		这里sp1.use_count = 2   sp2.use_count = 2，而sp3.use_count = 1
		这说明，std::shared_ptr本身实现机制就是：
			reset会对目标对象的引用计数初始化为1
			因为std::shared_ptr本身会相信程序员不会写出 double delete有问题的程序出来
			因为这个程序如果规范，就不会reset(u1)，传入这个已经被sp1(u1)，等其他shared_ptr对象绑定了的u1对象进来
			std::shared_ptr希望程序员去制造的场景是：reset(ux)，这个ux从未被其他shared_ptr绑定过（无论是拷贝构造，还是直接括号传入shared_ptr对象的方式）
		
		或者，其实可以从语义本身来理解这个问题：
		reset(newobj)，这里newobj不可能是被别人绑定过的，
		你reset不就是想给newobj换一个控制权吗？如果newobj被别人绑定过，你想为newobj换一个控制权，
		shared_ptr是可以拷贝的，直接用拷贝构造的方法就行，根本不需要reset()
		所以，传入被绑定过的newobj是没有意义的
		newobj肯定是没被绑定过的目标对象，才有意义。

		所以：
		（1）规范的shared_ptr编程：不要对reset(newobj)，这个传入的新对象newobj，不能是一个已经被shared_ptr所绑定了的对象，否则会产生double delete问题
		（2）reset(newobj)函数内部实现：目标对象newobj的引用计数初始化为：1
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
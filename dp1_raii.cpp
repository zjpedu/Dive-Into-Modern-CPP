/*
	C++ 之父把 RAII 比作 C++ 的垃圾回收器, 并且我们很确定它的调用时间,比 Java 的垃圾回收器
	具有更多的确定性. 所以 RAII、智能指针、移动语义这三驾马车保证了 C++ 高效的资源管理机制.
*/
#include <iostream>
using namespace std;

template <typename T>
class SmartPtr {
public:
	explicit SmartPtr(T* p = nullptr): p_(p) {

	}

	~SmartPtr() {
		delete p_;
	}
	void release() {
		delete p_;
		p_ = nullptr;
	}

	T* operator->() { return p_; }
	const T* operator->() const { return p_; }

	T& operator*() { return *p_; }
	const T& operator*() const { return *p_; }

private:
	T* p_;
	// 当前 delete 的原因是该 class 的数据成员是指针，
	// 默认生成的拷贝构造函数和拷贝赋值函数是错误的，在这个例子中这俩函数不重要，
	// 所以选择 delete
	SmartPtr(const SmartPtr&) = delete;
	SmartPtr& operator=(const SmartPtr&) = delete;
};

class MyClass{
public:
	MyClass(){
		cout<<"MyClass 初始化"<<endl;
	}

	~MyClass(){
		cout<<"MyClass 析构"<<endl;
	}

};


void process(int data)
{
	cout<<"process start"<<endl;

	//MyClass mc;  // 栈对象，最终出了作用域时会调用其析构函数,即使出现异常也会被调用

	// MyClass* p=new MyClass(); // 当后面出错时，会跳过溪沟函数
	SmartPtr p(new MyClass());  // RAII 智能指针

	if(data<0){
		invalid_argument exp("data");
		throw exp;
	}

	cout<<"process end"<<endl;
	// delete p;  // MyClass* p=new MyClass(); // 当后面出错时，会跳过溪沟函数
}

int main() {

	try {
		process(-100);
	} catch(invalid_argument& e) {
		cerr<<"invalid arg: " << e.what()<<endl;
	}
}
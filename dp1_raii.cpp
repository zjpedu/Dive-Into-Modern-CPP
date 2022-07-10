#include <cstdlib>
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

    //MyClass mc;  // 栈对象，最终出了作用域时会调用其析构函数

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
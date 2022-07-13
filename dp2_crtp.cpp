/*
	CRTP: curiously recursive template pattern. 这个是 C++ 提供的特性,它更像是 idiom.
	这里避免了使用虚函数,虚函数有存储和寻址的代价,并且不能内联,所以它的成本很高.现代 C++ 实际上
	不是很喜欢虚函数, 它的动态绑定特性产生了大量开销. CRTP 采用了模板的方式模拟了虚函数的调用机制,
	它属于静态绑定.
	CRTP 的本质是在基类中注入了子类的信息,并且它是在编译时就注入的子类信息.
	这个性能到底比运行时多态性好多少呢?大概在 10- 40 倍的性能提升. 当然这存在大数倍乘效应,比如你调用了 1000000 次.
	CRTP 可以替换虚函数,但是并不是全部替换. 
*/

#include <iostream>

template <typename T>
struct Base{
	Base():i_(0){};
	void process(){sub()->process_impl();};
	T* sub(){return static_cast<T*>(this);};  // 静态维护了一个多态性导出类的指针
	int get(){return i_;};
	~Base(){
		std::cout << "~Base()" << std::endl;
		// delete sub(); // 这里会导致死循环,因为子类的析构过程会自动调用父类的析构函数
	}
	void destroy(){
		delete sub();
	}
private:
	int i_;
};

struct Sub1: public Base<Sub1>{
	void process_impl(){
		std::cout << "Sub1 process_impl" << std::endl;
	}
	~Sub1(){
		std::cout << "~Sub1()" << std::endl;
	}
};


struct Sub2: public Base<Sub2>{
	void process_impl(){
		std::cout << "Sub2 process_impl" << std::endl;
	}
	~Sub2(){
		std::cout << "~Sub2()" << std::endl;
	}
};

int main(){
	Base<Sub1>* s1 = new Sub1();  // 这里存在多态性调用, delete 要注意
	s1->process();
	Base<Sub2>* s2 = new Sub2();
	s2->process();
	// delete s2;  // 不支持多态性删除,因为没有用 virtual ~Base()
	// delete s1;
	s2->destroy();  // CRTP 的多态性删除应该封装到 destroy 中
	s1->destroy();
	return 0;
}
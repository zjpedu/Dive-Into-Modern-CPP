## Rule of Five

### 概述

特殊 (特种) 成员函数的生成机制在 Modern C++ 算是基础中的基础了，只有明确了这些规则才知道到底
哪些类中需要用到何种特殊成员函数。当然本文不讨论如果没有这些函数我们应该如何正确定义这些函数。在
文章 [How to write special member functions correctly in modern C++](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/10_smfd.md)
将详细介绍这些函数正确的写法。C++ 中的特殊成员函数包括：
* 默认构造函数 (亦称为无参构造函数)
* 析构函数
* 拷贝构造函数
* 拷贝赋值函数
* 移动构造函数
* 移动赋值函数

这些函数只有在需要时才会生成。何谓需要？即在某些代码中使用了它们，而它门在类中并未显式声明的场合。基本简单的规定如下：

* 只有当类中不存在任何含参构造函数时，编译器才会生成默认构造函数，否则编译器会阻止生成默认构造函数.
* 在继承关系下，编译器一定会为继承类构造器生成子类的相应构造器调用，这是编译完整性的一个重要环节.
* 生成的特殊成员函数都是 public 且 inline 的，而且它们都是非虚性质的，除非讨论的是继承情况下的析构函数.在继承关系下，基类应该将其析构函数定义为虚函数，此时继承类生成的默认析构函数也是虚函数.
* 一旦用户写了析构函数，编译器就不再为你生成移动函数，但是会生成复制系列函数.


```C++
#include <memory>
#include <iostream>

struct A{
	int data;
	A(int _data):data{_data}{};
	A(const A& other) = default;
	A& operator=(const A& other) = default;
	A(A&& other) = default;
	A& operator=(A&& other)= default;
};

struct Foo
{
public:
	Foo(std::unique_ptr<A> ref) : mRef(std::move(ref)) {
		std::cout << "Foo default ctor" << std::endl;
	};

	// Foo(const Foo& other) : mRef {std::make_unique<A>(other.mRef->data)}{
	// 	std::cout << "Foo copy ctor" << std::endl;
	// };
	
	// Foo& operator=(const Foo& other) {
	// 	if(this == &other){
	// 		return *this;
	// 	}
	// 	Foo tmp(other);
	// 	std::swap(this->mRef->data, other.mRef->data);
	// 	std::cout << "Foo copy assignment" << std::endl;
	// 	return *this;
	// }

	// Foo(Foo&& other) : mRef(std::move(other.mRef)) {
	// 	std::cout << "Foo move ctor" << std::endl;
	// };

	// Foo& operator=(Foo&& other){
	// 	this->mRef = std::move(other.mRef);
	// 	std::cout << "Foo move assignment" << std::endl;
	// 	return *this;
	// }

	~Foo() = default;   // 哪怕你这样子写，也算是显式定义了析构函数
	// ~Foo(){
	// 	std::cout << "~Foo" << std::endl;
	// }
	std::unique_ptr<A> getMref(){
		return std::move(this->mRef);
	}
protected:
	std::unique_ptr<A> mRef;
};

int main(){
	Foo f1 = Foo(std::make_unique<A>(1));
	Foo f2 = f1; 
	Foo f3(f1);

	Foo f4 = Foo(std::make_unique<A>(2));
	Foo f5 (std::move(f1));
	Foo f6 = std::move(f4);
	
	return 0;
}
```


### 参考资料

1. Effective Modern C++ item 17.

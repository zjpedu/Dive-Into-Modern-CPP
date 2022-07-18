#include <iostream>
#include <string>
#include "abi.h"

// 这个类实际上还能被继承
struct MyPimpl::Impl{
	std::string text;
	int data;
	
	virtual void invoke()
	{
		std::cout << "invoke" << std::endl;
	}
};

MyPimpl::MyPimpl(): pimpl(new Impl()){
	std::cout << "default ctor" << std::endl;
}

MyPimpl::~MyPimpl(){
	delete pimpl;
	std::cout << "default dtor" << std::endl;
}

MyPimpl::MyPimpl(const MyPimpl& other) : pimpl(new Impl(*other.pimpl)){
	std::cout << "copy ctor" << std::endl;
}

void MyPimpl::process(){
	pimpl->invoke();  // 隐藏了 process 的具体实现
}

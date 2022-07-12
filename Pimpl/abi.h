#include <iostream>

struct MyPimpl{
	MyPimpl();
	~MyPimpl();

	MyPimpl(const MyPimpl&);

	void process();

private:
	struct Impl;
	Impl* pimpl;  // 指针指向不完整的类是合法的，在 .cpp 文件中仍然需要 Impl 的实现，这实现了延迟依赖

	// 数据区的内容实际上相当于下述定义，但是我们可能会频繁修改实现，并且可能需要引入其他的函数
	// 这些都不想暴露给用户
	/*
	struct Impl{
		std::string text;
		int data;
		
		virtual void invoke()
		{
			std::cout << "invoke" << std::endl;
		}
	};
	Impl* pimpl;
	*/
};
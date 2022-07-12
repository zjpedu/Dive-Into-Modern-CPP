###  Pimpl idiom

接口与实现分离，它使得用户能够得到稳定的 ABI. 提供给用户稳定的接口，接口的数据成员为指向具体实现的指针.

```c++
#include <iostream>

struct MyPimpl{
	MyPimpl();
	~MyPimpl();

	MyPimpl(const MyPimpl&);

	void process();

private:
	struct Impl;
	Impl* pimpl;
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
```

基于此，我们实现使用了 Pimpl 设计习语.



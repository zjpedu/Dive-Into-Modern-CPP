#include <iostream>
#include <memory>

struct MyClass{
	MyClass(){ std::cout<<"MyClass()"<< std::endl;}
	~MyClass(){ std::cout<<"~MyClass()"<< std::endl;}
private:
  double x,y,z;
};

int allocated_size = 0;  // 分配内存的大小，单位为 Byte
int nallocated = 0; // 分配内存的次数
int dallocated = 0; // 释放内存的次数
void* operator new(size_t size){
	void* p = std::malloc(size);
	nallocated++;
	std::cout << "new " << size << " Bytes" << std::endl;
	allocated_size += size;
	return p;
}
void operator delete(void* p) noexcept {
	std::cout << "delete memory" << std::endl;
	dallocated++;
	std::free(p);
	return;
}

namespace test_shared_init{
	int main(){
		std::cout << "allocated size: "<< allocated_size << std::endl;
		std::cout << "number of allocated: " << nallocated << std::endl;
		std::cout << "number of deallocated: " << dallocated << std::endl;
		std::cout << "---- 开始分配内存 ----" << std::endl;
		{
			std::shared_ptr<MyClass> sp1 {new MyClass{}};
		}
		std::cout << "allocated size: "<< allocated_size << std::endl;
		std::cout << "number of allocated: " << nallocated << std::endl;  // 2
		std::cout << "number of deallocated: " << dallocated << std::endl; // 2
		std::cout << "--------" << std::endl;
		
		{
			std::shared_ptr<MyClass> sp2 = std::make_shared<MyClass>();
		}
		std::cout << "allocated size: "<< allocated_size << std::endl;
		std::cout << "number of allocated: " << nallocated << std::endl;  // 1
		std::cout << "number of deallocated: " << dallocated << std::endl; // 1
		return 0;
	}
}

struct Base 
{ 
	int a; 
	virtual void process()  { 
		std::cout << "Base.process()"<< std::endl;
	}
	~Base(){
		std::cout<<"~Base"<< std::endl;
	}
};
 
struct Sub : public Base
{
	void process()  override { 
		std::cout << "Sub.process()"<< std::endl; 
	}

	void invoke(){
		std::cout << "Sub.invoke()"<< std::endl;
	}
	~Sub(){
		std::cout<<"~Sub"<< std::endl;
	}
};

namespace test_shared_cast{
	int main(){
		// {
		// 	Sub* sub = new Sub();
		// 	std::shared_ptr<Base> sp1{sub};
		// 	std::shared_ptr<Base> sp2{sp1};
		// 	std::shared_ptr<Base> sp3{sub};   // 这里发生了 sp1 和 sp3 抢夺所有权 (也就是抢夺谁来删除)
		// }

		{

			// shared_ptr<Base> sp1{new Base()};
			std::shared_ptr<Sub> sp2{new Sub()};
			std::shared_ptr<Base> sp3{sp2};
		
			std::cout<<sp3.use_count()<< std::endl;

			//1. 先对原生指针static_cast 2.再拷贝构造一个目标指针的shared_ptr
			// std::shared_ptr<Base> sp4{ std::shared_ptr<Base>{static_cast<Base*>(sp2.get())}}; // 错误！和下面的写法不等价
			std::shared_ptr<Base> sp4 = std::static_pointer_cast<Base>(sp2); 
			std::cout<<sp4.use_count()<<std::endl;

			std::shared_ptr<Sub> sp5 {dynamic_cast<Sub*>(sp4.get())};  //错误！这里实际上是所有权的抢夺，不是正确的共享引用计数
			std::cout << sp5.use_count() << std::endl;
			// std::shared_ptr<Sub>  sp6 = std::dynamic_pointer_cast<Sub>(sp4);    
			// cout <<  sp6.use_count() <<endl;
		} 
		return 0;
	}
}

namespace test_shared_copy{
	int main(){
		std::shared_ptr<Base> sp1 {new Base{}};
		std::shared_ptr<Base> sp2 {sp1};
		std::shared_ptr<int> sp3{sp1, &sp1->a}; // 这里共享了引用计数
		sp1.reset();
		return 0;
	}
}
int main(){
	// throw std::runtime_error("主动抛出异常");
	// throw std::exception();
	// test_shared_init::main();
	// test_shared_cast::main();
	test_shared_copy::main();
	return 0;
}
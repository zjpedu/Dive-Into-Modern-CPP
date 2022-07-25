#include "mm4_struct.h"

namespace test_unique_ptr_init{
	int main(){
		{
			// std::unique_ptr<Widget> w1 = new Widget(1,2,3);
			std::unique_ptr<Widget> w1(new Widget(1,2,3));
			// std::unique_ptr<Widget> w1 = std::unique_ptr<Widget>(new Widget(1,2,3));
			// Widget wt{10,20,30};
			// 不能包装栈上的指针，编译能通过，这是 runtime 错误
			// 栈上的错误会在变量的作用域结束时自动调用析构函数
			// 与此同时，unique_ptr 也会调用析构函数，同一个指针析构多次不合法
			// std::unique_ptr<Widget> t{&wt};

			w1->print();
			std::cout << sizeof(w1) << std::endl; 
    	}
    	std::cout<<"------ default delete"<<std::endl;

		{
			DeleteWithLog dw;
			// unique_ptr 实际上能够继承一个 delete policy
			// 可以使用函数对象、lambda、std::function 等一切可调用的对象
			// 如果 DeleteWithLog 不含有数据成员，那么因为 EBCO 大小还是 8 Byte
			std::unique_ptr<Widget,DeleteWithLog> w2(new Widget(10,20,30), dw);
			w2->print();
			std::cout << sizeof(w2) << std::endl; 
    	}

		int data1,data2,data3;
		{
			auto lambda = [=](Widget* w) { 
				std::cout<<data1<<data2<<data3<<std::endl;
				delete w; 
				std::cout<<"------ lambda delete w"<<std::endl;
			};
			std::unique_ptr<Widget, decltype(lambda)> w3(new Widget(100,200,300), lambda);
			w3->print();
			std::cout << sizeof(w3) << std::endl; 
		}

		{
			// 使用 std::function 作为 delete policy std::function 本身是有代价的，最小 40 Byte
			using DeleteFunction = std::function<void(Widget*)>;
			std::unique_ptr<Widget, DeleteFunction> 
				w4(new Widget(1000,2000,3000), deleteFunction);
			w4->print();
			std::cout << sizeof(w4) << std::endl; 
		}

		{
			// 使用函数指针
			std::unique_ptr<Widget, void(*)(Widget*)> 
				w4(new Widget(1000,2000,3000), deleteFunction);
			w4->print();
			std::cout << sizeof(w4) << std::endl; 
		}

		return 0;
	}
}

namespace test_unique_ptr_ownership{
	int main(){
		{
			// 因为这里实际上存在一个裸指针到智能指针的隐式类型转换
			// 但是 unique_ptr(pointer __p) 被声明为 explicit
			// 阻止了这种隐式转换的发生
			// std::unique_ptr<Widget> w0 = new Widget(1,2,3);
			
			// Widget* pw=new Widget(1,2,3);
			// std::unique_ptr<Widget> w1{pw};
			// std::unique_ptr<Widget> w2{pw};

			// std::unique_ptr<Widget> w3{new Widget(1,2,3)};
			// std::unique_ptr<Widget> w4{new Widget(1,2,3)};
			// std::unique_ptr<Widget> w2{w1};  // 这里实际上调用了 unique_ptr 的拷贝构造函数,unique_ptr 的拷贝构造函数已经被 delete 了
			// w1->print();

			// std::unique_ptr<Widget> w2 { new Widget(*w1)} ;  // 这里实际上调用了 Widget 的拷贝构造函数，深拷贝了 w1 之后生成一个临时对象绑定了 w2

			// std::unique_ptr<Widget> w3=w1; //错误，这里实际上调用了拷贝赋值函数
			// auto w3= std::unique_ptr<Widget>(new Widget(10,20,30));  // 这里实际上分为三步：1.调用 Widget 的 default ctor; 2. 构造了 unique_ptr 临时对象(临时对象为右值); 3. 调用了 unique_ptr 的移动赋值函数，右值被移动到 w3 上
			// auto w4=getWidgetPtr();
			// auto w5=std::move(w1);

			// if(w1==nullptr) std::cout<<"w1 is nullptr"<<std::endl;
			// w2->print();

			// w1.swap(w2);
			// w1->print();
			// w2->print();

			//w2.reset();
			//w2=nullptr; //与 w2.reset() 等价
			// w2.reset(new Widget(11,22,33)); 
			

			// if(w2!=nullptr)
			// {
			// 	std::cout<<"w2 is not null"<<std::endl;
			// }
			// else 
			// {
			// 	std::cout<<"w2 is null_ptr"<<std::endl;
			// }

		}
		// std::cout<<"----------"<<std::endl;
		
		// {
		// 	auto w1 = std::make_unique<Widget>(1000,2000,3000);
		// 	auto w3 = std::make_unique<Widget>(100,200,300);
		// 	w3->print();

		// 	//auto w4=w3;// 错误

		// 	auto w4=std::move(w3); //OK，w3不能用
		
		// 	std::unique_ptr<Widget> w5{std::move(w4)};

		// 	Widget* rawp1=w5.get(); 

		// 	w5->print();
		// 	*rawp1= *w1; // Widget&
			

		// 	process(w5.get());
		// 	w5->print();
		// 	//delete rawp1;

		// 	Widget* rawp=w5.release();//释放所有权
		// 	if(w5==nullptr) std::cout<<"w5 is null_ptr"<<std::endl;
		// 	delete rawp; //必须负责释放d

		// }
		return 0;
	}
	
}

namespace test_this_unique_ptr{
	int main(){
		// std::cout << "test_this_unique_ptr" << std::endl;
		// Widget* w1 = new Widget(100, 200, 300);
		// // std::unique_ptr<Widget> w2 {w1};
		// // std::unique_ptr<Widget> w3 = w2->getWidget(); // 这是错误的，这相当于 w1 的所有权被 w2 和 w3 同时管理着

		// Widget pst(100, 200, 300);
		// std::unique_ptr<Widget> w4 = pst.getWidget(); // 这也是错误的，运行时错误，这相当于w4 管理了栈内存的所有权
		return 0;
	}
}

struct Base 
{ 
	int a;
	Base(){
		std::cout << "Base default ctor" << std::endl;
	}
	virtual void process()  { 
		std::cout << "Base.process()"<< std::endl;
	}
	virtual ~Base(){
		std::cout<<"~Base()"<<std::endl;
	}
};
 
struct Sub : public Base
{
	int data {1};
	Sub(){
		std::cout << "Sub default ctor" << std::endl;
	}
	void process()  override{ 
		std::cout << "Sub.process()"<<std::endl; 
	}

	void invoke(){
		std::cout << "Sub.invoke()"<<std::endl;
	}
	~Sub() {
		std::cout<<"~Sub()"<<std::endl;
	}
};

namespace test_cast_unique{

	int main(){
		{
			// auto b1 = std::make_unique<Base>();  // b1 是 Base
			// b1->process();  // Base process

			// Sub* ps1=new Sub();
			// std::unique_ptr<Sub> u1{ps1};
			// std::unique_ptr<Sub> u2 = std::move(u1);
			// throw std::exception();
			// std::cout << (u1 == nullptr) << std::endl;
			// std::cout << "--------" << std::endl;
			// auto s1 = std::make_unique<Sub>();
			// s1->process();  // Sub process
		
			// std::unique_ptr<Base> b2 {std::move(s1)};   // b2 是 Sub
			// b2->process();  // Sub process

			// std::unique_ptr<Base> b3 = std::make_unique<Sub>();   // b3 是 Sub
			// std::unique_ptr<Sub>  s2 { dynamic_cast<Sub*>(b3.get()) };  // 这是运行时错误 因为 b3.get 拿到的这个裸指针被 b3 和 s2 同时管理了所有权，这不符合 unique_ptr 独占所有权的特性
			// std:: unique_ptr<Sub>  s2 ( b3.get() );  // 错误
			// std:: unique_ptr<Sub>  s2 ( dynamic_cast<Sub*>(b3.release()));
			// s2->invoke();

			// Base* pB=new Sub();
			// delete pB;
		}
		return 0;
	}
}

int main(){
	// test_unique_ptr_init::main();
	// test_unique_ptr_ownership::main();
	// test_this_unique_ptr::main();
	// test_cast_unique::main();
	return 0;
}
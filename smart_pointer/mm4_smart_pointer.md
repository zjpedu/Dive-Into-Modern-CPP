## 智能指针

智能指针是 C++ 11 标准之后引入的最重要的内存管理特性，熟练掌握**智能指针的内存模型**对于写出正确的代码
相当关键，因此本专题会单独介绍智能指针。这篇文章我条款的方式来写吧，并为每个条款都附有相应的代码片段。
后续代码使用了下面公共的 `Widget` 结构。

```C++
#include <iostream>
#include <memory>

struct Widget{
	int m_x;
	int m_y;
	int m_z;

public:
	Widget(int x,int y , int z):
		m_x(x), m_y(y),m_z(z)
	{
        std::cout << "Widget default ctor" << std::endl;
    }

	void print(){
		std::cout<<m_x<<","<<m_y<<","<<m_z<<std::endl;
	}

	Widget(const Widget& w){
		std::cout << "Widget copy ctor" << std::endl;
	}

	Widget& operator=(const Widget& w){
		std::cout << "Widget copy assignment" << std::endl;
		return *this;
	}

	Widget(Widget&& w){
		std::cout << "Widget move ctor" << std::endl;
	}

	Widget& operator=(Widget&& w){
		std::cout << "Widget move assignment" << std::endl;
		return w;
	}

	~Widget()
	{
		std::cout << "Widget dtor" << std::endl;
	}
	
	// 永远不要返回 this 指针的 unique_ptr，这会导致运行时错误
	// std::unique_ptr<Widget> getWidget(){
	// 	return std::unique_ptr<Widget>(this);
	// }
};

struct DeleteWithLog { 
	// int data {0};
	void operator()(Widget* w) { 
		delete w;
		std::cout<<"------ DeleteWithLog delete w"<<std::endl;
	} 
};

void deleteFunction(Widget* w) { 
	delete w;
	std::cout<<"------ deleteFunction delete w"<<std::endl;
}

std::unique_ptr<Widget> getWidgetPtr()
{
	std::unique_ptr<Widget> w(new Widget(10,20,30));
	return w;
}

void process(Widget* p)
{

} 
```


### unique_ptr

* item 1: 不允许直接将裸指针通过 = 赋值给 unique_ptr，这存在编译时错误.

```C++
int main(){
	// 因为这里实际上存在一个裸指针到智能指针的隐式类型转换
	// 但是 unique_ptr(pointer __p) 被声明为 explicit
	// 阻止了这种隐式转换的发生
	// demo 代码见 [08_explicit.cpp](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/08_explicit.cpp)
	std::unique_ptr<Widget> w0 = new Widget(1,2,3);
	return 0;
}
```

* item 2: unique_ptr 不能使用栈指针来初始化，这属于运行时错误.

```c++
int main(){
	{
		std::unique_ptr<Widget> w1 = new Widget(1,2,3);  // 错误的初始化方式，不能将普通指针赋值给智能指针
		// std::unique_ptr<Widget> w1(new Widget(1,2,3)); // 正确
		std::unique_ptr<Widget> w1 = std::unique_ptr<Widget>(new Widget(1,2,3));  // 正确

		Widget wt{10,20,30};
		// 不能包装栈上的指针，编译能通过，这是 runtime 错误
		// 栈上的错误会在变量的作用域结束时自动调用析构函数
		// 与此同时，unique_ptr 也会调用析构函数，同一个指针析构多次不合法
		std::unique_ptr<Widget> t{&wt};

		w1->print();
		std::cout << sizeof(w1) << std::endl; 
	}
	std::cout<<"------ default delete"<<std::endl;
	return 0;
}
```

* item 3: unique_ptr 在栈中占 8 Byte，一旦传入包含数据成员的可调用对象，其大小会发生变化.

```C++
struct DeleteWithLog { 
	// int data;  // 一旦解开这个数据成员，智能指针的大小将是自己的 8 Byte + data + 对齐
	void operator()(Widget* w) { 
		delete w;
		std::cout<<"------ DeleteWithLog delete w"<<std::endl;
	} 
};

//int DeleteWithLog::data=0;

int main(){
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
		// 使用 lambda 表达式作为 delete policy
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
		// 使用 std::function 作为 delete policy
		using DeleteFunction = std::function<void(Widget*)>;
		std::unique_ptr<Widget, DeleteFunction> 
			w4(new Widget(1000,2000,3000), deleteFunction);
		w4->print();
		std::cout << sizeof(w4) << std::endl; 
	}
}
```

* item 4: unique_ptr 能够传递 delete policy，并且它会继承 delete policy. 如果非要定义删除策略，使用不带数据成员的 functor，它没有额外的存储代价.

```C++
struct DeleteWithLog { 
	// int data {0};  // 一旦解开这个数据成员，智能指针的大小将是自己的 8 Byte + data + 对齐
	void operator()(Widget* w) { 
		delete w;
		std::cout<<"------ DeleteWithLog delete w"<<std::endl;
	} 
};

int main(){
	{
		// functor 作为 delete policy
		DeleteWithLog dw;
		std::unique_ptr<Widget,DeleteWithLog> w2(new Widget(10,20,30), dw);
		w2->print();
	}

	int data1,data2,data3;
	{
		// 使用 lambda 表达式作为 delete policy
		auto lambda = [=](Widget* w) { 
			std::cout<<data1<<data2<<data3<<std::endl;
			delete w; 
			std::cout<<"------ lambda delete w"<<std::endl;
		};
		std::unique_ptr<Widget, decltype(lambda)> w3(new Widget(100,200,300), lambda);
		w3->print();
	}

	{
		// 使用 std::function 作为 delete policy std::function 本身是有代价的，最小 40 Byte
		using DeleteFunction = std::function<void(Widget*)>;
		std::unique_ptr<Widget, DeleteFunction> 
			w4(new Widget(1000,2000,3000), deleteFunction);
		w4->print();
	}

	{
		// 使用函数指针,函数指针大小为 8 Byte
		std::unique_ptr<Widget, void(*)(Widget*)> 
			w4(new Widget(1000,2000,3000), deleteFunction);
		w4->print();
		std::cout << sizeof(w4) << std::endl; 
	}
}
```


* item 5: unique_ptr 只有移动构造和移动赋值函数，不能拷贝

```C++
int main(){
	{
		// 因为这里实际上存在一个裸指针到智能指针的隐式类型转换
		// 但是 unique_ptr(pointer __p) 被声明为 explicit
		// 阻止了这种隐式转换的发生
		// std::unique_ptr<Widget> w0 = new Widget(1,2,3);
		
		Widget* pw=new Widget(1,2,3);
		std::unique_ptr<Widget> w1{pw};
		// std::unique_ptr<Widget> w2{w1};  // 这里实际上调用了 unique_ptr 的拷贝构造函数,unique_ptr 的拷贝构造函数已经被 delete 了
		// w1->print();

		std::unique_ptr<Widget> w2 { new Widget(*w1)} ;  // 这里实际上调用了 Widget 的拷贝构造函数，深拷贝了 w1 之后生成一个临时对象绑定了 w2

		// std::unique_ptr<Widget> w3=w1; //错误，这里实际上调用了拷贝赋值函数
		// auto w3= std::unique_ptr<Widget>(new Widget(10,20,30));  // 这里实际上分为三步：1.调用 Widget 的 default ctor; 2. 构造了 unique_ptr 临时对象(临时对象为右值); 3. 调用了 unique_ptr 的移动赋值函数，右值被移动到 w3 上
		// auto w4=getWidgetPtr();
		auto w5=std::move(w1);

		if(w1==nullptr) std::cout<<"w1 is nullptr"<<std::endl;
		w1->print();
	}
}
```

* item 6: unique_ptr 重载了 == 操作符，所以能直接和 nullptr 比较, 它实际上比较的是内部的裸指针，但是 unique_ptr 本身不为空

```C++
int main(){
	Widget* pw=new Widget(1,2,3);
	std::unique_ptr<Widget> w1{pw};
	// 实际上是比较了 w1 内部的裸指针和 nullptr 的关系
	if(w1==nullptr) std::cout<<"w1 is nullptr"<<std::endl;
	w1->print();
}
```

* item 7: 不能有多个 unique_ptr 指向同一个裸指针

```C++
int main(){
	// w2 和 w1 实际上都指向了同一个裸指针，这种属于运行时错误
	// 当 w1 和 w2 出了作用域时，都要删除其指向的裸指针，w2 首先被析构，删除了 pw
	// 接着 w1 析构时也要删除 pw 指针，这是为定义行为，因为这块内存已经被释放了
	Widget* pw=new Widget(1,2,3);
	std::unique_ptr<Widget> w1{pw};
	std::unique_ptr<Widget> w2{pw};  // 这里发生了所有权的抢夺问题

	// 下面两句是正确的，因为 new 出来两个不同的临时对象
	std::unique_ptr<Widget> w3{new Widget(1,2,3)};
	std::unique_ptr<Widget> w4{new Widget(1,2,3)};
}
```

* item 8: make_unique 使用了变参模板.

```C++
template<class _Tp, class... _Args>
inline unique_ptr<_Tp> make_unique(_Args&&... __args)
{
    return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...));
}
```

* item 9: 永远不要包裹 this 的 unique_ptr，会导致运行时错误

```C++
int main(){
	std::cout << "test_this_unique_ptr" << std::endl;
	Widget* w1 = new Widget(100, 200, 300);
	// std::unique_ptr<Widget> w2 {w1};
	// std::unique_ptr<Widget> w3 = w2->getWidget(); // 这是错误的，这相当于 w1 的所有权被 w2 和 w3 同时管理着

	Widget pst(100, 200, 300);
	// std::unique_ptr<Widget> w4 = pst.getWidget(); // 这也是错误的，运行时错误，这相当于w4 管理了栈内存的所有权
	return 0;
}
```

```C++
struct Base 
{ 
	int a; 
	virtual void process()  { 
		std::cout << "Base.process()"<< std::endl;
	}
	~Base(){
		std::cout<<"~Base()"<<std::endl;
	}
};
 
struct Sub : public Base
{
	void process()  override{ 
		//Base::process();
		std::cout << "Sub.process()"<<std::endl; 
	}

	void invoke(){
		std::cout << "Sub.invoke()"<<std::endl;
	}
	~Sub() {
		std::cout<<"~Sub()"<<std::endl;
		//Base::~Base();
	}
};
```

* item 9: unique_ptr 支持多态，多态类型转换时要先 release 释放所有权，否则会产生运行时错误，double free 同一个堆内存

```C++
int main(){	
	std::unique_ptr<Base> b3 = std::make_unique<Sub>();   // b3 是 Sub
	// std::unique_ptr<Sub>  s2 { dynamic_cast<Sub*>(b3.get()) };  // 这是运行时错误 因为 b3.get 拿到的这个裸指针被 b3 和 s2 同时管理了所有权，这不符合 unique_ptr 独占所有权的特性
	std:: unique_ptr<Sub>  s2 ( dynamic_cast<Sub*>(b3.release()));  // 而 shared_ptr 提供了四个多态转型函数，且这四个函数只能在 shared_ptr 上用
	s2->invoke();
	return 0;
}
```

* item 10: 含有 unique_ptr 的类会隐式删除 copy 构造和 copy 赋值函数，如有需要，则用户需要自己定义.

这主要是因为 unique_ptr 天生不允许复制操作，复制 unique_ptr 会发生所有权不明确的问题。

* item 11: 含有 unique_ptr 是否生成 move 构造和 move 赋值函数，则由五法则决定.

原则是五个函数要写都写，因为一旦写了其中一个，编译器会认为用户否定了默认的编译器行为，或者认为编译器生成的行为
有错，将不再为用户生成。

* item 12: 有了 unique_ptr 之后，智能指针的传递的形式应该要发生变化. 请采用推荐的方式，避开不推荐的方式.

```C++
#include <iostream>
#include <memory>
 
using namespace std;


class Widget{
    int m_x;
    int m_y;
    int m_z;

public:
    Widget(int x=0,int y=0 , int z=0):
        m_x(x), m_y(y),m_z(z)
    {}

    void print() const{
        cout<<m_x<<","<<m_y<<","<<m_z<<endl;
    }

     ~Widget()
    {
        cout<<"Widget dtor"<<endl;
    }
};

// 不推荐，这个方法在裸指针时代比较适合
Widget* createWidget()
{
    Widget* p=new  Widget{0,0,0};
    return *p;
}

// 推荐，智能指针时代的工厂方法
unique_ptr<Widget> createWidget()
{
    unique_ptr<Widget> w(new Widget(0,0,0));
    return w;
}

// 不推荐，获取 widget 的所有权
void process1(unique_ptr<Widget> w)
{
    w->print();
}

//推荐， 仅仅使用这个 widget，不表达任何所有权
void process2(const Widget& w)
{
    w.print();
}

//推荐， 仅仅使用这个 widget，不表达任何所有权
void process3(Widget* w)
{
    w->print();
}

// 可行，不常用：打算重新指向别的对象，该参数是智能指针的引用
// 不会移动所有权，但是 w 的改变同样会导致实际参数的修改
void process4(unique_ptr<Widget>& w); 

// 不推荐： 通常不是想要的，这里的引用没有任何作用了
void process5(const unique_ptr<Widget>&); 

int main()
{
    unique_ptr<Widget> w1(new Widget(1,2,3));
    unique_ptr<Widget> w2(new Widget(10,20,30));
    unique_ptr<Widget> w3;

    process1( std::move(w1));//转移所有权，//w1==nullptr;
    process2(*w2);
    w3=createWidget();
    process3(w3.get());

}
```

* item 13: 智能指针嵌套析构会发生爆栈的情况，应当避免.

```C++
#include <memory>
#include <iostream>
using namespace std;

struct Node
{
	int data;
	// std::unique_ptr<Node> next;  // 这种写法会导致 stack overflow
	Node* next;  // 修改成裸指针，然后增加下面的构造函数，整个程序运行正常了

	Node(int _data, Node* next = nullptr):data{_data}{}; 

	~Node()
	{
		cout<<"dtor: "<<data<<endl;
	}
};

struct List
{
	std::unique_ptr<Node> head;
	void push(int data)
	{
		head = std::unique_ptr<Node>(new Node{data, head.get()});
	}
};

int main()
{
	List wall;
	for (int beer = 0; beer != 3000000000; ++beer)
	{
		wall.push(beer*10);
	}
}
```

### shared_ptr

* item 1: shared_ptr 仍然会 (同 unique_ptr) 发生抢夺所有权问题.

```C++
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
		{
			Sub* sub = new Sub();
			std::shared_ptr<Base> sp1{sub};
			std::shared_ptr<Base> sp2{sp1};
			std::shared_ptr<Base> sp3{sub};   // 这里发生了 sp1 和 sp3 抢夺所有权 (也就是抢夺谁来删除)
		}
		return 0;
	}
}
```

```C++
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
		{

			// shared_ptr<Base> sp1{new Base()};
			std::shared_ptr<Sub> sp2{new Sub()};
			std::shared_ptr<Base> sp3{sp2};
			std::cout<<sp3.use_count()<< std::endl;

            //1. 先对原生指针static_cast 2.再拷贝构造一个目标指针的shared_ptr
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
```
[转型过程中的所有权抢夺问题](https://github.com/jpzhu-edu/Dive_Into_Modern_CPP/blob/main/imgs/shared_ptr_conflict.png)

**所以，请注意 shared_ptr 多态转型提供了下面四个函数**:

```C++
    static_pointer_cast  = static_cast + copy ctor = 从而实现了共享引用计数
    dynamic_pointer_cast = dynamic_cast + copy ctor = 从而实现了共享引用计数
    const_pointer_cast = const_cast + copy ctor = 从而实现了共享引用计数
    reinterpret_pointer_cast = reinterpret_cast + copy ctor = 从而实现了共享引用计数
```

那么问题来了，既然上述存在等价关系，那么我们是否能像下面这么做？

```C++
// 先做 static_cat, 然后构造了新的 shared_ptr 对象，这样子仍然是错误的？这意味着我们智能使用 static_pointer_cast 这些函数来做
std::shared_ptr<Base> sp4{ std::shared_ptr<Base>{static_cast<Base*>(sp2.get())}}; // 错误！
```

* item 2: 优先使用 std::make_shared 初始化 shared_ptr，它仅仅分配一次连续的内存，因此减少了 new/detele 的次数，同时缓存也更加友好；普通初始化方法会分配两次内存，分别是给数据和控制块.

```C++
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

int main(){
	// throw std::runtime_error("主动抛出异常");
	// throw std::exception();
	test_shared_init::main();
	return 0;
}
```

* item 3: shared_ptr 提供了另外的共享引用计数的办法

```C++
namespace test_shared_copy{
	int main(){
		std::shared_ptr<Base> sp1 {new Base{}};
		std::shared_ptr<Base> sp2 {sp1};
		std::shared_ptr<int> sp3{sp1, &sp1->a}; // 这里共享了引用计数,这个构造函数很特殊，可以在调试模式下观察其行为
		sp1.reset();
		return 0;
	}
}
```

#### weak_ptr

weak_ptr 是 shared_ptr 的另一方面，难度比前面两个部分都大很多。

### 总结
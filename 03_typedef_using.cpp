#include <iostream>
#include <list>
#include <memory>  // unique_ptr
#include <unordered_map>

/*
	测试 typedef
*/
namespace test_typedef_typename{

	template <typename T>
	struct MyAllocList{
		typedef std::list<T, std::allocator<T>> type;
	};

	template <typename T>
	struct Widget{
		private:
		/*
			关于 typename 的解释参见 https://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords/613132#613132
			实际上这涉及到以下知识点：
			1. 首先 :: 操作符有两层含义：（1）访问类成员；（2）访问 static 成员，在非模板代码中，编译器掌握了类的定义，
			因此它知道通过 :: 运算符访问的是类型还是 static 成员，比如 string::size_type 当我们写下这个定义时，
			编译器有 string 定义，从而知道它是一个类型。但是对于模板代码存在困难，当写下 T::mem 时，编译器直到完全实例化之后
			才知道到底是类成员还是 static 成员。但是为了处理模板，编译器必须提前知道名字是否到底是一个类型，例如，当编译器遇到
			T::size_type * p; 这到底是乘法运算还是定义了一个类型指针？参见 C++ primer page 593 《使用类的类型成员》。
			2. typename 的依赖域含义，即它的具体定义依赖于模板参数
		*/
		typename MyAllocList<T>::type list;

	};
	struct Foo {};

	int main(){
		MyAllocList<std::string>::type li;
		Widget<Foo> w;
		return 0;
	}
}

/*
	测试 using
*/
namespace test_using{
	using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;

	template <typename T>
	using MyAllocList = std::list<T, std::allocator<T>>;

	template <typename T>
	struct Widget{
		private:
		MyAllocList<T> list;
	};
	struct Foo {};
	int main(){
		MyAllocList<std::string> lw;
		Widget<Foo> w;
		return 0;
	}
}

int main(){
	test_typedef_typename::main();
	test_using::main();
	return 0;
}
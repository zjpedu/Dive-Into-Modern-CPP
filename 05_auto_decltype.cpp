#include <iostream>
#include <typeinfo>
#include <vector>

namespace test_auto_decltype{
	const int & i = 5;
	decltype(i) j = 6;

	double compute(double x, double y){
		return x * y;
	}

	int main(){
		std::cout << i << " " << j << std::endl;
		// i = 7; // 表达式必须为可修改的左值，和 j 报错一致
		// j = 7;  // 表达式必须是可修改的左值，这说明当前 j 推断的类型为 const int &
		decltype(compute(2.0, 2.0)) z = compute(2.0, 2.0);
		std::cout << "z = " << z << std::endl;
		auto x = 1.0; // 正确
		auto y = x;  // 正确
		// auto z;  // 错误
		const int a = 5;
		auto b = a; // 此时 b 的类型为 int，不是 const int
		// a = 7; // 错误，表达式必须是可修改的左值，因为 a 的类型为 const int
		b = 7;  // 正确，折说明 b 仅仅是 int，忽略了顶层的 const
		const auto c = a; // 正确，如果想要 auto 定义的类型和顶层 const 完全相同，则需要显式使用 const

		const int m = 0, &n = m;
		// decltype(n) p; // 变量 p 是 const 类型，需要初始化
		// decltype(m) p;  // 常量 p 需要初始化设设定项
		decltype(m + n) p; // 正确，说明这个表达式的推断放弃了 const 语义
		decltype(m + 0) q; // 正确，说明 decltype 只要简单的运算就可以使得原先变量放弃 const 语义
		auto p1 = m + n;  // 这里表达式的推断没有 const 语义
		std::cout << "m + n = " << p << std::endl;

		double x0 = 1.0;
		const double &x1 = x0;
		auto x2 = x1;  // 所以这里推断出的 x2 类型实际上是 double x2，没有 const 和 引用 & 属性，推导出的类型实际上就是 double x2;
		x2++;
		std::cout << "typeid(x2) = " << typeid(x2).name() << " " << "x2 = " << x2 << " " << "x1 = " << x1<< std::endl;  // 推断 x2 是 double
		return 0;
	}
} // namespace test_auto_decltype

/*
	如果是函数模板，形如：
	template <typename T>
	void f1(T& param){
		return;
	}
	or
	template <typename T>
	void f2(T&& param){
		return;
	}
	or
	template <typename T>
	void f3(T param){
		return;
	}

	上述函数调用的形参实际上包含三种情况，它们分别是：
	* 引用或指针作为形参，万能引用除外
	* 万能引用作为形参
	* 无引用或指针的形参数

	并且在参数传递过程中，实际上有两个部分需要推导，它们分别是：
	* 类型 T 的推导
	* param 的推导
	实际情况中，T 的推导结果和 param 的推导结果往往不同。
*/
namespace test_function_template_auto
{
	// 首先我们来构造一个函数模板，在函数模板中，只输出传来的参数的信息
	template <typename T>
	void f(T& param){
		std::cout << "typeid(T) = " << typeid(T).name() << std::endl;
		std::cout << "typeid(param) = " << typeid(param).name() << " " << "param = " << param << std::endl;  // typeid(param) = i param = 1
		param++;  // param = 2
		std::cout << "param = " << param << std::endl;
	}
	int main(){
		int a = 1, &b = a;
		f(b); // T 的类型被推断为 int，所以 param 的类型推断为 int &, 因此，param 改变时，外部的 b 也跟着改变，这符合预期
		std::cout << "b = " << b << std::endl;  // b = 2;

		const int x = 1;
		// f(x);  // T 的类型被推断为 const int，此时 param 参数被推断为 const int &,所以 param++ 不符合预期，所以该句会编译报错
		// 如果传入的参数是 const，那么这个属性不会被忽略

		const int x0 = 1, &y = x0;
		// f(y);  // 此时 T 的类型被推断为 const int，我们发现 T 的类型推导中 & 被忽略了，这是符合预期的，param 的类型为 const int &，所以它其实不能执行 param++
		return 0;
	}
} // namespace test_function_template_auto


namespace test_misc{
	int main(){
		std::vector<int> v {1,2,3,4};
		auto len = v.size();
		// unsigned long len = v.size();  // 在我的 mac 平台上推导出的类型
		std::cout << "typeid(len) = " << typeid(len).name() << std::endl;  // typeid(len) = m m 表示 unsigned long, 所以推导正确
		return 0;
	}
}

int main(){
	test_auto_decltype::main();
    test_function_template_auto::main();
	test_misc::main();
	return 0;
}
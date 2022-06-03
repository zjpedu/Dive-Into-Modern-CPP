#include <iostream>
#include <vector>
#include <initializer_list>

namespace test_initializer_list{
	class Widget{
		int x = 0;
		int y {0};
		// int z (0);
	};
	int main(){
		double x {10};
	 	// error: type 'double' cannot be narrowed to 'int' in initializer list
		int sum (x);  // right
		std::cout << sum << std::endl;
		return 0;
	}
} // namespace test_initializer_list

namespace test_parse{
	class Widget{
		int x;
		public:
		Widget(){
			std::cout << "调用默认构造函数" << std::endl;
		}
		Widget(int _x): x(_x) {std::cout << "调用非默认构造函数" << std::endl;};
	};
	int main(){
		Widget w1(100);
		// warning: empty parentheses interpreted as a function declaration
		// note: remove parentheses to declare a variable
		// Widget w2();
		Widget w3{};  // right
		return 0;
	}
}

namespace test_initializer_deduced{
	template <typename T>
	void f(T param);
	template <typename T>
	void g(std::initializer_list<T> param){
		std::cout << "函数 g 参数推导成功" << std::endl;
		return;
	};

	int main(){
		// f({1,2,3,4});   // 会报错,推导不出 T 的类型
		g({1,2,3,4}); // 成功执行
		return 0;
	}
}
namespace test_narrowing_conversion{
	class Widget{
		public:
		Widget(){
			std::cout << "调用默认构造函数" << std::endl;
		};
		Widget(int i, bool b){
			std::cout << "调用显式 int bool 类型构造函数" << std::endl;
		}; // (1)
		Widget(int i, double d){
			std::cout << "调用 int double 类型构造函数" << std::endl;
		};  // (2)
		// Widget(std::initializer_list<bool> li){
		// 	std::cout << "调用 std::initializer_list<bool>" << std::endl;
		// };  // (3)
		Widget(std::initializer_list<double> li){
			std::cout << "调用 std::initializer_list<double>" << std::endl;
		};  // (4)
		// Widget(std::initializer_list<std::string> li){
		// 	std::cout << "调用 std::initializer_list<std::string>" << std::endl;
		// }
	};

	int main(){
		// Widget w1{10, 5.0};  // 会优先调用 (3),但是由于 {} 不能发生隐式的 narrowing conversion,因此报错
		Widget w1 {static_cast<bool>(10), static_cast<bool>(5.0)};  // 这是一种解决 narrowing conversion 的办法,显式的进行类型转换
		Widget w2 {10, 5.0};  // 会优先调用 (5) 但是不能发生隐式类型转换,即从 int float 转换成 std::string 所以不会选择该构造函数
		Widget w3 {}; // 这里如果既有默认构造函数,又有 std::initializer_list 构造函数会选择哪个?答案是会选择默认构造函数,因为 {}代表没有实参,并不代表空的 initializer_list
		Widget w4 ({10, 5.0});  // 还是按照 std::initializer_list 优先原则
		Widget w4_1 {{10, 5.0}};
		Widget w5 ({});  // 这个是构造了空的 std::initializer_list,优先调用包含 std::initializer__list 的构造函数
		Widget w6 {{}};  // 这个也是构造了空的 std::initializer_list,优先调用包含 std::initializer__list 的构造函数
		return 0;
	}
}

int main(){
	// test_initializer_list::main();
	// test_parse::main();
	// test_initializer_deduced::main();
	test_narrowing_conversion::main();
	return 0;
}
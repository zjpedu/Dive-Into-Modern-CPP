#include <iostream>

namespace test_scope_enum{
	enum class Color {red, white, black};
	int i = static_cast<int>(Color::red);
}

namespace test_unscope_enum{
	enum Color {red, white, black};
	int i = red;
	enum class Color1 {red, white, black};
	int i1 = static_cast<int>(Color1::red);  // red 被 class 隐藏了

	// Color2 中定义的枚举常量和之前 Color 中定义的枚举常量定义冲突，因为这种
	// unscope enumeration 它们的行为就像全局变量
	// enum Color2 {red, white, black};
	int main(){
		std::cout << "unscopre enumeration i = " << i << std::endl;
		std::cout << "scope enumeration i1 = " << i1  << std::endl;
		return 0;
	}
}

int main(){
	test_unscope_enum::main();
    return 0;
}
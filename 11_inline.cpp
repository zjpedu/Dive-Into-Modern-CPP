// g++ -o test 11_inline.cpp test_inline_1.cpp test_inline_2.cpp 按照它编译 运行结果为 8
// g++ -o test 11_inline.cpp test_inline_2.cpp test_inline_1.cpp 按照它编译 运行结果为 16
#include <iostream>
int test1();
int test2();
int t1();
int t2();

/*
	在这个部分,我将通过引入两个外部编译单元来定义两个同名,但是含义不同的 inline 函数,
	称为 int inline_test(),将他们放在两个独立的 cpp 文件中,分别是 test_inline_1.cpp 和
	test_inline_2.cpp
*/
namespace test_inline_function{
	int main(){
		std::cout << test1() + test2() << std::endl;
		return 0;
	}
}

namespace test_inline_variable{
	int main(){
		std::cout << t1() + t2() << std::endl;
		return 0;
	}
}

int main(){
	test_inline_function::main();  // test_inline_function
	test_inline_variable::main();  // test_inline_variable
	return 0;
}
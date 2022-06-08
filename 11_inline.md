### inline

一直以来,在我参与的项目中看到了很多 "inline" 修饰符,对它的理解停留在“它只是给编译器提示,将
inline 的函数展开到调用它的地方,避免产生一个 call function 指令,我们知道 call function
因为要切换上吓人所以存在较大的性能开销”.直到我决定深入到这个特性当中,我看到了编译器和 C++ 标准
给出的新的使用方法.他们包括:
* inline function
* inline variable
* inline namespace  版本库控制

关于 inline namespace 的部分,这里不讲,感兴趣的朋友可以找些资料来读.

* inline function

```cpp
// 保存文件名为 test_inline_1.cpp
#include <iostream>

inline int inline_test(int x){
    return x * x;
}

int test1(){
    return inline_test(2);
}
```

```cpp
// 保存为 test_inline_2.cpp
#include <iostream>

inline int inline_test(int x){
    return x * x * x;
}

int test2(){
    return inline_test(2);
}
```

```cpp
// 保存w文件名为 11_inline.cpp
// g++ -o test 11_inline.cpp test_inline_1.cpp test_inline_2.cpp 按照它编译 运行结果为 8
// g++ -o test 11_inline.cpp test_inline_2.cpp test_inline_1.cpp 按照它编译 运行结果为 16
#include <iostream>
int test1();
int test2();
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

}

int main(){
	test_inline_function::main();
	return 0;
}
```

当我们分别用以下指令编译代码时,得到不同的结果:

* g++ -o test 11_inline.cpp test_inline_1.cpp test_inline_2.cpp 按照它编译 运行结果为 8
* g++ -o test 11_inline.cpp test_inline_2.cpp test_inline_1.cpp 按照它编译 运行结果为 16

这个结果看起来很奇怪的,其实这些奇怪源于我们的代码.

* 我们在两个文件中定义了相同的函数 `inline_test`,并且都给他们加了 `inline` 修饰符.
* 如果两个文件中同名的 `inline_test` 函数都去掉 `inline` 修饰符,编译会报 `duplicate symbol 'inline_test(int)'`
不信你试试看.
* 于是我在代码中加上 `inline` 修饰符,编译不在报错,但是如果交换两个 cpp 文件的顺序会输出不同的值 (8 和 16).

这些都说明什么呢? **这说明编译器在看到 inline 之后选择一个代码版本內联到 main 函数中,**
**并且选择的内联代码是编译时写在前面的 (当然这种顺序可能在不同的编译器上表现不同)**.

总结下: inline function 实际上不仅仅是把代码展开到调用处,更重要的是,这些被标记了 `inline`
弱符号将编译器报错转换为某种未知的内联行为,因此要小心设计内联函数.

* inline variable

我实在不知道,内联变量到底有什么用,看起来很奇怪,难道仅仅是为了将变量展开到调用处吗?实际上不是,它
的作用仍然和 inline funcion 是一样的. 具体测试见测试代码.
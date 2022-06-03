### initializer_list

这个主题有一个很重要的问题:在创建对象时,什么时候应该使用大括号,什么时候转而使用小括号?这两种写法
在不甚严格的 C++ 程序中经常见到,甚至我们经常看到在一个程序中混用不同的初始化方法.本文回答以下
问题:
* () 和 {} 适合使用场景
* 大部分场景下如何选择初始化方法

#### 创建对象的不同方法

我们常常会看到如下初始化方法:

```c++
int a(0);  // 初始化放在小括号内 (1)
int b = 0; // 初始化放在等号后面 (2)
int c{0};  // 初始化放在大括号内 (3)
int d = {0};  //初始化同时使用 = 和 {}, C++ 标准一般认为它和上一种方法等价,所以这里不讨论
```

因此,我们将着重讨论 (1) (2) 和 (3). 为了统一这些不同的初始化方法, C++ 11 新标准引入了
uniform initialization (统一初始化),它是单一的、至少从概念上可以适用于一切场景,表达一切我们
想要的初始化含义.它的基础是使用 {} 形式,因此我更喜欢称之为大括号初始化 (braced initialization)
,请注意,在这里 braced initialization = uniform initialization. 可以说:
* "大括号初始化"其表,
* "统一初始化"其实.

大括号初始化可以让我们表达 C++ 11 以前无法表达的含义.比如,使用大括号来指定容器的初始化内内容变得
非常简单:

```C++
std::vector<int> v{1,2,3,4}; // v 的初始值为 1,2,3,4
```

大括号同样也可以用来为非静态成员制定默认初始化值,这在 C++ 11 新标准之后被允许.

```c++
#include <iostream>
#include <vector>

namespace test_initializer_list{
	class Widget{
		int x = 0;
		int y {0};
		// int z (0);  // 编译无法通过,不能使用 () 初始化
	};
	int main(){
		return 0;
	}
} // namespace test_initializer_list

int main(){
	test_initializer_list::main();
	return 0;
}
```

但是对于不可复制的对象 (如 std::atomic) 可以采用 {} 和 (), 但是不能使用 =;

```c++
std::atomic<int> x{0};
std::atomic<int> y(0);
std::atomic<int> z = 0; // 编译无法通过
```

从上面的例子中看到, {} 在任何场合下都能使用,因此它就被称为 uniform initialization.在 C++
的三种初始化写法中,只有 {} 能称得上 uniform.

#### C++ 初始化方法存在的问题

##### 窄化类型检查

我们需要注意大括号有一向新特性,就是它实际上**禁止**内建数据类型之间进行隐式窄化类型转换 (narrowing conversion)
,但是如果使用 () 或者 = 则不会进行窄化类型转换检查.测试如下:

```c++
double x = 10.2;
int sum1 {x};  // error: type 'double' cannot be narrowed to 'int' in initializer list
int sum2 = x;  //right, sum2 = 10,被截断
int sum3(x); // right
```

##### 解析语法问题

C++ 有这样一个规定:**在编译器解析语法时,能被解析为声明的都要解析为声明**. 看下面的例子:

```C++
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

// Output:
// 调用非默认构造函数
// 调用默认构造函数
```
对于 `Widget w2()` 实际上按照 C++ 的标准,它声明了一个返回 `Widget` 的函数 `w2`,但是实际
上我们想做的是声明 w2 对象,并且调用默认构造函数,这个声明被编译器理解成了声明函数,这就是解析语法问题.
但是使用 {} 没有出现这样的问题,并且调用了非默认构造函数.

前面,我们通过例子看到 {} 比 () 能适用于更多的场景,那么我们是否能够得出结论:
* 在任何场景下都应该使用 {} 定义对象.

想要回答这个问题,其实我们还需要探究究竟 {} 会有什么问题吗?
* 答案是肯定的,{} 的使用存在一些意外.这种意外源于:(1) 使用的初始化值,(2)std::initializer_list,
(3) 构造函数重载三者之间的关系.当类定义同时存在这三件事情时,看起来你为了做某件事,但是编译器缺做了
让你意想不到的选择.

在 auto 章节,我们讲过如下的推导
```c++
auto x = {1,2,3,4} // x 会被推导为 std::initializer_list 类型的对象

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
```

如果在你的构造函数中没有定义 std::initializer_list 那么 () 和 {} 没有任何区别.但是如果有一个
或多个构造函数声明了任何一个具备 std::initializer_list 类型的参数,那么采用了大括号初始化语法
的语句会**优先致命地**选择带有 std::initializer_list 类型的行参的重载版本,这真的非常致命.

```c++
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
```

如上,只要有 std::initializer_list 就会对 {} 形式的初始化物有致命的吸引力,调用时可能会:
* 允许类型转换的情况下 (不允许 narrowing conversion,除非主动使用 static_cast)
* 明确类型匹配的情况下
* 如果不能隐式发生转换,则会放弃 std::initializer_list 构造函数,转而找其它参数精确匹配的构造函数

##### vector

vector 应该是容器中最特殊的了.看下面代码

```C++
vector<int> v1 (10, 20);  // 初始化了一个长度为10, 值都为 20 的 vector
vector<int> v2 {10, 20};  // 初始化了一个长度为 2, 值为 10, 20 的 vector
```

总结:
* {} 初始化方法应用场景最广,但是一定要小心选择是否你的构造函数需要包含 std::initializer_list,
因为一旦有这个参数的构造函数,其它参数类型精确匹配的构造函数将会被**隐藏**.
* 使用 () 和 {} 初始化时, vector 是一个特例,需要记住.
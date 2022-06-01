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



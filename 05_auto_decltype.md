### auto, decltype and Deducing Types
#### 函数模板中的型别推导

由于函数传参数可以包括：
(1) 参数是指针或者引用，但不是万能引用
(2) 参数是万能引用
(3) 参数类型既不是指针也不是引用

如果是函数模板，形如：

```C++
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
```
	上述函数调用的形参实际上包含三种情况，它们分别是：
	* 引用或指针作为形参，万能引用除外
	* 万能引用作为形参
	* 无引用或指针的形参数

	并且在参数传递过程中，实际上有两个部分需要推导，它们分别是：
	* 类型 T 的推导
	* param 的推导
	实际情况中，T 的推导结果和 param 的推导结果往往不同。
因此我们将设计三个函数来测试函数模板中的参数推导。

```c++
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
```


#### auto

编程时通常需要把表达式的值赋值给变量，这就要求在声明变量的时候清楚地知道表达式的类型，
然而做到这一点并非那么容易，有时候甚至根本做不到。为了解决这个问题，C++ 11 新标准引入了
auto 类型说明符，用它就能够让编译器替我们去分析表达式所属的类型。和原来那些值对应一种类型的
说明符（如 double， int）不同，auto 让编译器通过初始值来推算变量的类型，显然，auto 定义的
变量必须要有初始值。

```C++
	auto x = 1.0; // 正确
	auto y = x;  // 正确
	auto z;  // 错误，这种情况下，编译器无法确定推断出变量 z 的类型
```

还需要注意的是 auto 在推断类型的时候，会忽略掉顶层定义的 const，也会忽略掉 & (引用)，比如
```C++
	const int a = 5;
	auto b = a;  // 此时的 b 是 int 类型，但不是 const int 类型

	auto x = 1.0; // 正确
	auto y = x;  // 正确
	// auto z;  // 错误
	const int a = 5;
	auto b = a; // 此时 b 的类型为 int，不是 const int
	// a = 7; // 错误，表达式必须是可修改的左值，因为 a 的类型为 const int
	b = 7;  // 正确，折说明 b 仅仅是 int，忽略了顶层的 const
	const auto c = a; // 正确，如果想要 auto 定义的类型和顶层 const 完全相同，则需要显式使用 const

	const double &x1 = 1.0;
	auto x2 = x1;  // 所以这里推断出的 x2 类型实际上是 double x2，没有 const 和 引用 & 属性
	x2++;
	double x0 = 1.0;
	const double &x1 = x0;
	auto x2 = x1;  // 所以这里推断出的 x2 类型实际上是 double x2，没有 const 和 引用 & 属性，推导出的类型实际上就是 double x2;
	x2++;
	std::cout << "typeid(x2) = " << typeid(x2).name() << " " << "x2 = " << x2 << " " << "x1 = " << x1<< std::endl;  // 推断 x2 是 double，并且 x2 的值 和 x1 的值没有同时改变，所以其引用属性实际上也没有推导出来
```

总结：
当满足下列两个条件时，可以用 auto 表示变量的类型，让编译器自己推断类型
* 当类型很复杂;

```c++
	vector<int> v;
	auto it = v.begin();
```

* 类型不容易得到.

```c++
	// 实际上 f 是 lambda 表达式，后续我们可以使用 f(x) 来调用该 lambda 表达式
	auto f = [](int x) -> bool{
		return true;
	}
```

auto 的性别推导完全和第一部分相同.

#### decltype

有时会遇到这种情况：希望从表达式的类型推断出要定义的变量的类型，但是不想用该表达式的值初始化
这个变量。为了满足这一要求，C++ 11 新标准引入了第二种类型说明符 decltype，它的作用时选择并返回
操作数的数据类型。在此过程中，编译器分析表达式并得到它的类型，却不实际计算表达式的值。

```C++
	double compute(double x, double y){
		return x * y;
	}
	// 这里实际上编译器只执行了一次 compute 函数，在 decltype 中并未执行 compute 函数，
	// 只是从该函数中推断了它的返回值类型而已
	decltype(compute(2.0, 2.0)) z = compute(2.0, 2.0);
```

使用 decltype 和 auto 在 const 类型上的处理略有不同，auto 会忽略掉顶层的 const 语义，
但是 decltype 返回的类型则会保留顶层的 const 语义，如：

```C++
	const int m = 0, &n = m;
	// decltype(n) p; // 变量 p 是 const 类型，需要初始化
	// decltype(m) p;  // 常量 p 需要初始化设设定项
	decltype(m + n) p; // 正确，说明这个表达式的推断放弃了 const 语义
	auto p1 = m + n;  // 这里表达式的推断没有 const 语义
```

**NOTE**

**decltype((var)) 无论 var 是什么类型，decltype 推断得到的类型永远是 &, 而 decltype(var)
只有当 var 本身真的是引用时，才会推断为引用类型。**

decltype(auto) 是 C++ 14 引入的新特性,它实际上是在使用 auto 的隐式声明的地方采用 decltype
的方式做型别推导.

#### MISC

auto 修饰符实际上非常强大,它能避免很多不合适的显式性别定义.举几个例子:

* 容器大小


```c++
std::vector<int> v{1,2,3,4};
auto len = v.size();
unsigned len = v.size();
int len = v.size();
```

上面三种容器大小的声明方式哪种最好呢?我们知道的是 `v.size()` 返回 `size_type`.
* 如果生命 unsigned len, 它在 32 位平台上和 64 位平台上的表现不同,在 64 位平台上它仍然为 32
位,但是在这里实际上
* 如果采用 int,那么实际上存在隐式类型转换,因此,最好的声明方式是 auto.


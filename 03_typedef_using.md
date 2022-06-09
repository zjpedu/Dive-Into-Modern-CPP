### 使用 using 而不要使用 typedef

typedef 关键字实际上是 C++ 98 的遗产，使用它可以为复杂类型添加别名，如

```c++
typedef std::list<std::string, std::allcocator<std::string>> MyList;
```

上述写法实际上用了一个非常简单的名字表示了一长串复杂的类型定义。

使用 using 能得到相同的结果，如

```c++
using MyList = std::list<std::string, std::allcocator<std::string>>
```

看起来它们是不是并无差别呢？在不使用模板时,两者确实并无差别.
**实际上是有差别的，只有当使用模版时，二者才存在差别。**

在 C++ 11 标准中,我们可以用下面语句定义包含模板参数的别名:

```C++
template <typename T>
using MyAllocList = std::list<T, MyAlloc<T>>;

// 我们可以使用下列方法使用定义好的别名
MyAllocList<Widget> lw;
```

但是在 C++ 98 标准下,无法直接替换使用 typedef.原因看下面的分析.

例子见 03_typedef_using.cpp 中的两段代码实现了相同的功能，但是写法上 typedef 要复杂一些。
尤其是当在模板中使用 typedef 定义了新的类型之后，在使用时，需要使用 :: 操作符, :: 操作符只有
在下面情况下可能用到:
* 类的静态值

```C++
struct Test{
	static int value = 5;
};

// 对于该成员的访问，我们使用下面方法
std::cout << Test::value::std::endl;
```

* 特化模版的数据成员

```C++
class Wine P{};
template <>
class MyAllocList<Wine>{
	private:
	enum class WineType{ White, Red, Rose};
	WineType type; // type 是一个数据成员
}

...

MyAllocList<Wine>::type // 指的是某一个数据成员
```

* 型别成员

```c++
/*
下面是 C++ 11 的 C++ 98 等价写法
	template <typename T>
	using MyAllocList = std::list<T, MyAlloc<T>>;
*/
template <typename T>
struct MyAllocList{
	private:
	typdef std::list<T, std::allocator<T>> type;
};

MyAllocList<Widget>::type lw;

template <typename T>
struct Widget{
	private:
	/*
		注意这里必须要讲 typename，这是为了告诉编译器，当前使用 :: 操组符定义的 type 是类的
		类型定义，不是静态成员变量，因为如果是类的成员变量，则这样的定义编译通不过，这里的
		typename 不可或缺
	*/
	typename MyAllocList<T>::type list;  // 如果你的代码中使用了模板参数的话,必须加关键字 typename,他是为了消除上面提到的 :: 操作符歧义
};
```
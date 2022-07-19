## 从变参模板到折叠表达式 （From variadic template to fold expression）

### 概述

这是一个黑魔法专题, 本文将包含下面两个内容:

* variadic template (C++11)
	* function
	* class or struct
* Fold Expression (C++17)

如上所示，variadic template 可以理解为变参模板，它是 C++11 引入的新特性，围绕该特性有不少黑魔法，
当然这都属于本文的范畴。fold expression 叫做折叠表达式，它是 C++17 引入的新特性，一方面为了替换
variadic template 的复杂性，另外方面它确实简化了代码。接下来的代码环节，我们将分别使用这两个技术，
实现相同的功能，当然不是所有的功能二者都能等价替换。

### 术语

在该专题开始之前有一些术语需要专门介绍，我们拿下面实现的代码为例 (如果你看不懂这段代码也没关系，后面会认真讲解)。

```C++
template<typename T, typename... Types> // 这里的 Types 我们成为 template type parameters pack.
void print(T firstArg, Types... args){ // 这里的 args 我们称为 function parameters pack.
	std::cout << firstArg << std::endl;
	print(args...);  // 在函数调用过程中 `...` 我们称为 ellipsis operator
}
```

上述不管是 template type parameters pack 还是 function parameters pack 实际上都被 `...` 分成两个部分，
`...` 之前的部分我们称为 pattern，之后 pack 中的每个部分展开都应该带着 `...` 之前的这个部分，`...`之后的部分
我们称为 pack，`...` 本身我们称为 pack expansion. 举个例子：

```C++
template <typename... Types>
// 假设用户传来的 Types 包含 A, B, C, D
// 那么上述展开就成为了 
template <typename A, typename B, typename C, typename D
// 也就是 A, B, C, D 每个都应该带着 ... 之前的部分，在这里就是 typename
```

下面是一个变参模板万能引用的例子
```C++
template<typename... Args> 
void bar(Args&&... args){
	foo(std::forward<Args>(args)...); // 一定要注意如果要将一包参数转发出去，必须要加 ...
}
```


### 变参模板 (variadic template)

#### 变参模板函数

##### 查看可变参数的个数

```C++
template <typename... T>
void print(T... args){
	std::cout << sizeof...(args) << std::endl;
}
```

通过上面的代码，我们能够得到 args 中到底包含多少个参数，但是这样就够了吗？我们该如何拿到 args 中
的每个参数以供我们处理呢？

##### 递归展开可变参数包

```c++
	print(1, 3.14, "hello"); 
```

这是一个打印功能，具有两个特征：

* 我们无法提前预知 print 函数实参个数
* 我们无法提前预知 print 函数实参类型

```C++
void print(){

}
// typename... Type 代表我们声明了一堆不确定的类型参数
// 这些参数可以为 0 个，也可以有很多个
template<typename T, typename... Type> 
void print(T firstArg, Type... args){
	std::cout << firstArg << std::endl;
	print(args...);
}

// or，上下代码实现方式不同，得到结果相同
// 那么显然上面的方法更加的简洁，因为实际上
// 可变参数个数可以为 0 
template <typename T>
void print(T firstArg){
	std::cout << firstArg << std::endl;
}
template<typename T, typename... Type>
void print(T firstArg, Type... args){
	print<T>(firstArg);
	print(args...);
}

int  main(){
	std::string str("hello");
	print(1, 3.14, str, "world!");
	return 0;
}
```

现在我们想通过可变参数模板求 1+2+... + 100 的和，应该如何实现呢？

```C++
double sum = 0;
void recursive_sum(){}
template <typename T, typename... Types>
void recursive_sum(T firstArg, Types... args){
	sum += firstArg;
	recursive_sum(args...); 
}
int  main(){
	recursive_sum(1, 3.14);
	std::cout << sum << std::endl;
	return 0;
}
```

如果我们要求函数返回 double 类型呢？上述代码应该如何修改？

```C++
template <typename T>
double recursive_sum(T firstArg){
	return static_cast<double>(firstArg);
}
template <typename T, typename... Types>
double recursive_sum(T firstArg, Types... args){
	return recursive_sum(firstArg) + recursive_sum(args...);
}
int  main(){
	std::cout << recursive_sum(1, 3.14) << std::endl;
	return 0;
}
```

or 改成下述代码也是对的

```C++
double recursive_sum(){
	return 0;
}
template <typename T, typename... Types>
double recursive_sum(T firstArg, Types... args){
	return firstArg + recursive_sum(args...);
}
int  main(){
	std::cout << recursive_sum(1, 3.14) << std::endl;
	return 0;
}
```

写了这么多代码之后，我们基本上能够感受到的一点就是模板递归实现技术和通常已经掌握的 recursive programming
有异曲同工之妙。首先必须要有递归结束的条件，其次在主程序中递归调用自己即可。

##### 统一初始化展开参数包

利用统一初始化操作符 {args...}，它会解开 parameters pack 中的每一个元素，这是什么原理呢？下面将讨论这部分内容。
下面的例子中因为展开之后只能放类型相同的元素，所以我们统一用 int 作为其真实的参数类型，后续会介绍一些变通方法。测试代码如下：

```C++
template <typename... Args>
void unpack(Args... args){
	int arr[] = {args...};  // 这里被展开 {1,2,3}
	for(int i = 0; i < sizeof...(args); ++i)
		std::cout << arr[i] << std::endl;
}
int  main(){
	unpack(1,2,3);
	return 0;
}
```

如果修改数组 `int arr[]` 的定义部分会发生什么情况？ 

```C++
template <typename... Args>
void unpack(Args... args){
	int arr[] = {(args, 0)...};  // 这里和上面的代码有区别
	for(int i = 0; i < sizeof...(args); ++i)
		std::cout << arr[i] << std::endl;
}

int  main(){
	unpack(1,2,3);
	return 0;
}
// 编译给出 warning: expression result unused [-Wunused-value]，说明 args 被展开了
// 输出结果为 0 0 0
// 这种情况下，我们没有处理 args 表达式展开的结果，怎么处理呢？接着看。
```

所以我们得知 {args...} 会解开 pack，但是我们需要处理 args 中的每个元素，这应该怎么办呢？

```C++
template <typename T>
void print(T t){
	std::cout << t << std::endl;
}

template <typename ...Args>
void print(Args... args)
{
	// 这个 arr 的大小为 sizeof...(args), 元素全部为 0
	int arr[] = {(print(args),0)...};
	// std::initializer_list<int> arr{(print(args),0)...}; // 与上面等价
}
int  main(){
	print(1,2,3);
	return 0;
}
```

这是什么原理呢？实际上把 args 传递给一个模板函数，处理其中的每一个元素，并且利用了 () 表达式的求值方式同时也定义了一个元素全部
为 0 的数组，从而实现了与递归解包一样的功能。C++ 11 中还引入了 lambda 表示，是否能够替换显示处理每个元素的 print 函数呢？
当然所有可调用的对象都可以传入 print 函数处理 args 展开的参数值。

```C++
template <typename F, typename ...Args>
void print(F&& f, Args... args)
{
	int arr[] = {(f(std::forward<Args>(args)),0)...};
}

int  main(){
	print([](auto i){std::cout << i << std::endl;}, 1,3.14,"hello");
	return 0;
}
```

#### 变参模板类

需求：实现标准库的 std::tuple，std::tuple 能够接受任意数量的参数，因此只能使用变参模板类。

##### 通过递归继承方式实现 tuple

```C++
template <typename... > struct tuple;  // 抽象不完整的类定义
template<> struct tuple<> {}; // 递归出口，如果我们注释掉这段代码，报错信息将提示我们定义这段结构
template <typename Head, typename... Tail>
struct tuple<Head, Tail...>: public tuple<Tail...>  // 都是定义为一个和一包的关系，递归解开一包
{
	using inherited = tuple<Tail...>;
protected:
	Head m_head;
public:
	tuple(){};
	tuple(Head h, Tail... tail): m_head(h), inherited(tail...){};
	Head head() {return m_head;};
	inherited& tail(){return *this;};
};
int  main(){
	tuple<int, float, std::string> t{1, 3.14, "hello"};
	std::cout << t.head() << std::endl;
	std::cout << t.tail().head() << std::endl;
	return 0;
}
```
##### 通过递归组合方式实现 tuple

```C++
// 单继承改写为组合是一个基本技能
template <typename... > struct tuple;  // 抽象不完整的类定义
template<> struct tuple<> {}; // 递归出口，如果我们注释掉这段代码，报错信息将提示我们定义这段结构
template <typename Head, typename... Tail>
struct tuple<Head, Tail...> // 都是定义为一个和一包的关系，递归解开一包
{
	using composited = tuple<Tail...>;
protected:
	Head m_head;
	composited m_tail;  // 声明一个变量，该变量对应继承出来的变量
public:
	tuple(){};
	tuple(Head h, Tail... tail): m_head(h), m_tail(tail...){};
	Head head() {return m_head;};
	composited& tail(){return m_tail;};
};
int  main(){
	tuple<int, float, std::string> t{1, 3.14, "hello"};
	std::cout << t.head() << std::endl;
	std::cout << t.tail().head() << std::endl;
	return 0;
}
```

当然对于上面两种方式，我们都能设计更加复杂的递归出口，代码如下所示：

```C++
template <typename... > struct tuple;  // 抽象不完整的类定义，告诉编译器 tuple 是一个变参模板类
template<typename Head> struct tuple<Head> {
protected:
	Head m_head;
public:
	tuple(){};
	tuple(Head h): m_head(h){};
	Head head() {return m_head;};
}; // 递归出口，如果我们注释掉这段代码，报错信息将提示我们定义这段结构
template <typename Head, typename... Tail>
struct tuple<Head, Tail...> // 都是定义为一个和一包的关系，递归解开一包
{
	using composited = tuple<Tail...>;
protected:
	Head m_head;
	composited m_tail;
public:
	tuple(){};
	tuple(Head h, Tail... tail): m_head(h), m_tail(tail...){};
	Head head() {return m_head;};
	composited& tail(){return m_tail;};
};
int  main(){
	tuple<int, float, std::string> t{1, 3.14, "hello"};
	std::cout << t.head() << std::endl;
	std::cout << t.tail().head() << std::endl;
	return 0;
}
```
不过显然这种写法增加了设计的复杂度，没必要。

### Fold Expression

折叠表达式是 C++ 17 引入的新特性，它能解决**变参模板函数**引入的解包问题，该技术相对之前部分较为简洁。

需求同样是实现 1 + 3.14 求和的例子，当然你可以传递更多的参数.

```C++
template<typename... Types>
double sum1(Types... args){
	return (... + args);  // 这里必须要加括号
}

template<typename T, typename... Types>
double sum2(T first, Types...args){
	return (first + ... + args);
}

template <typename... Types>
double sum3(Types... args){
	return (args + ...);
}

template<typename T, typename... Types>
double sum4(T first, Types...args){
	return (args + ... + first);
}

template<typename... Types>
double sum5(Types...args){
	return (args + ... + 0);
}
template<typename... Types>
double sum6(Types...args){
	return (0 + ... + args);
}
int main(){
	std::cout << sum1(1, 3.14) << std::endl;
	std::cout << sum2(1, 3.14) << std::endl;
	std::cout << sum3(1, 3.14) << std::endl;
	std::cout << sum4(1, 3.14) << std::endl;
	std::cout << sum5(1, 3.14) << std::endl;
	std::cout << sum6(1, 3.14) << std::endl;
	return 0;
}
```

再思考，我们如何通过折叠表达式实现前面所写的 `print` 函数打印每个元素的功能呢？

```C++
template<typename... Types>
void print1(Types... args){
	(std::cout << ... << args) << std::endl; 
}

template<typename... Types>
void print2(Types... args){
	((std::cout << args << std::endl), ...) ;
}

template<typename... Types>
void print3(Types... args){
	(..., (std::cout << args << std::endl)); 
}

template <typename T>
void printArg(T t){
	std::cout << t << std::endl;
}
template <typename... Types>
void print4(Types... args){
	(printArg(args), ...);   // C++ 17 这样子就可以展开了
}
int main(){
	print1(1, 3.14, "hello");
	std::cout << "---- print1 end ----" << std::endl;
	print2(1, 3.14, "hello");
	std::cout << "---- print2 end ----" << std::endl;
	print3(1, 3.14, "hello");
	std::cout << "---- print3 end ----" << std::endl;
	print4(1, 3.14, "hello");
	std::cout << "---- print4 end ----" << std::endl;
	return 0;
}
```

### 总结

综上，分别使用了 C++ 11 和 C++ 17 引入的新特性，不过我更喜欢 C++ 11 引入的变参模板，我比较偏爱
递归技术。

### 参考文献
1. 折叠表达式 https://zh.cppreference.com/w/cpp/language/fold
2. 变参模板 https://www.cnblogs.com/qicosmos/p/4325949.html 
3. 折叠表达式 http://purecpp.org/detail?id=1289
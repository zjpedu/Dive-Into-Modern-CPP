### enum 使用

enum 在 C++ 98 和 C++ 11 中也有显著的变化，最主要的变化是 C++ 11 将 enum 分成了 scope
和 unscope 两种，建议在程序中使用 C++ 11 提出的 scope 类型，因为 C++ 98 的 unscope 类型
其表现行为看起来很像全局变量。它们的定义方式分别如下：

```c++
/*
	定义方式
*/
enum class Color1 {red, white, black}; // scope enumeration
// enum struct Color1 {red, white, black}; // class 和 struct 可以互换
enum Color2 {yellow, blue, green}; // unscope enumeration


/*
	使用方式，从这段代码中可以看到，C++ 11 使用的 scope enum 不提供隐式类型转换，
	这样做其实更加的安全
*/
namespace test_scope_enum{
	enum class Color {red, white, black};
	int i = static_cast<int>(Color::red);
}

namespace test_unscope_enum{
	enum Color {red, white, black};
	int i = red;
}
```



### final 与 override 的使用

#### override

C++ 11 新标准允许派生类显式地注明它使用某个成员函数覆盖了它继承的虚函数.
具体的做法是在形参列表后面、或者在 const 成员函数的 const 关键字后面、或者在引用成员函数的引用限定符后面添加一个 override 关键字.
标识符 override 一定是用來标识 virtual 函数。而 virtual 函数存在 base class，就一定会被 derived classes 继承，derived classes 内继承而来的虚函数，有沒有 virtual 都无关紧要。
* 只要是 virtual 函数，即使出现 derived classes 也一定加上 virtual
* 只要 virtual 函数被重写 (overrided)，一定加上保留字 override
* 写上 override 就表示该函数 virtual，但我们还是写上 virtual 更好地标识它。


#### final

有时候我们会定义这样一种类，我们不希望其它类继承它，或者不想考虑它是否适合作为一个基类. 为了实现这一目的，C++11 新标准增加了一种防止继承发生的方法，即在类名后跟一个关键字 final.

```c++
struct BaseX final {};
```

另外一种方式是在函数中增加 final，这表示在继承关系中该函数不能被 override. **这种情况下，final 关键字必须和 virtual 一起使用.**

```c++
/*
	1. 如果在函数中使用了 final 修饰符，那么 virtual 修饰符也要存在
	2. 如果使用了 final 修饰符，那么该函数必须要有定义，也就是 {} 包裹的语句块，否则会报编译错误
*/
virtual void f(int) final {};
```
最佳实践：**在多继承关系的函数中加 virtual 是非常好的习惯**。

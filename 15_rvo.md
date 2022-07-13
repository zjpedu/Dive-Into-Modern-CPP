## Return Value Optimization

返回值优化是 C++ 17 新标准中非常重要的特性，当申明对象并用函数返回值初始化对象时，会用到返回值优化。
减少一次构造函数的调用。如下代码所示，实际上在 `b` 和 `create_nrvo` 创建的临时对象上发生了栈内存交换，
这免去了一次移动构造函数的调用。

```c++
{
    // Named Return Value Optimization, 要求 Base(Base&&) 必须存在，但是不会调用
    // Non-standard
    Base b = create_nrvo();
}
```

```c++
{
    Base b = create_rvo();  // Return Value Optimization, C++ 17 标准，消除了函数调用，直接交换内存
}
```
##  CRTP and virtual clone function

在设计过程中，我们有 dp2_crtp_virtual_clone.cpp 中的代码，并且想实现如下功能需求：

```C++
void process (Shape * s){
    Shape* s_clone = new Circle(s);
}
```

我们想要在 `process` 内部 clone 一个对象，如上代码所示，这里我们 hard cord 了 Circle,
不具有多态性，当然我们可以有其他的函数模板等方式实现，但是 dp2_crtp_virtual_clone.cpp 给出了
两种可能的实现。我们只需要向下面的代码一样:

```C++
void process(Shape* s){
    Shape* s_clone = s->clone(); // 这里会根据实参类型调用合适的 clone 函数，从而实现上述功能
}
```

**注意: CRTP 是编译时多态性.**
### default initializer and POD

POD is refer to the [MSVC](https://docs.microsoft.com/en-us/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170).
It is clear to POD.

**Conclusion**

When a class or struct is **both** trivial **and** standard-layout, it is a POD (Plain Old Data) type.
这句话的逆否命题也成立: 当它不是 POD 时,那么或者 struct/class 不满足 trivial 或者 不满足 standard-layout.

default initializer 在现代 C++ 中通常情况下都应该给予初值,这也符合定义变量同时初始化原则.
当然这样的初始化实际上会有性能开销,但是可能会减少因为未初始化造成的风险. 向下面这样,任何类型都能
使用 {} uniform initialization 给出初始化值.

```C++
struct Test1{
    int x {};
    int y {};
};
```


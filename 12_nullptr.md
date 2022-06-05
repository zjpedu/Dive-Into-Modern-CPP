### 0, NULL, nullptr

#### 0, NULL

```C++
#include <iostream>

namespace test_0_NULL{
	void f(int){
		std::cout << "f(int)" << std::endl;
	};
	void f(void*){
		std::cout << "f(void*)" << std::endl;
	};
	int main(){
		f(0);
		// f(NULL);// call to 'f' is ambigous. Because the NULL is some unsigned long type.
		f((void*)NULL);
		f(nullptr);
		return 0;
	};
};

int main(){
	test_0_NULL::main();
    return 0;
}

```

从上面这个例子我们看出,实际上 0 和 NULL 在某种程度上都有 int 的含义. 但是 nullptr 绝无 int 类型.
因此,相比于 0 和 NULL, 优先选用 nullptr.



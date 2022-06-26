### std::any implementation

std::any 在实际应用中感觉没什么用,但是其实现技术包含了非常重要的技术. 例子如下:

```c++
#include <iostream>
#include <vector>
#include <string>
#include <any>

/*
	any simulation using Object-Orient techniques.
*/
namespace test_any_implementation{
	struct message_base{
		virtual ~message_base() = default;
	};

	template <typename Msg>
	struct wrapped_message: message_base{
		public:
		Msg content;
		explicit wrapped_message(const Msg& contents_): content(contents_){};
	};
	int main(){
		message_base* m1 = new wrapped_message(5);
		message_base* m2 = new wrapped_message(3.14);
		message_base* m3 = new wrapped_message(std::string("hello"));
		std::vector<message_base*> v {m1, m2, m3};
		for(auto i: v){
			std::cout << i << std::endl;
		}
		return 0;
	}
}

int main(){
	test_any_implementation::main();
	return 0;
}
```

为了能放任意类型的对象到一个 vector 中,定义了一个 base 类 message_base, 然后其它任意包装类(wrapped_message)
都继承了 message_base,使得 vector 可以放任意子类对象.
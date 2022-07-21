#include <iostream>

/*
	对于构造函数中含有单个参数 (或相当于单个参数，比如其它参数都含有默认值)，那么加了 explicit 之后防止了隐式类型转换，
	这个性质非常重要，尤其在标准库 (std::unique_ptr std::shared_ptr 等) 中大量用了 explicit，
	所以这告诫我们，初始化时要用 {} 的统一初始化方法，不要用其他方式

*/

struct WidgetNoExplicit{
	int data;
	WidgetNoExplicit(int _data):data{_data}{};
	~WidgetNoExplicit(){
		std::cout << "----~WidgetNoExplicit()----" << std::endl;
	}
};


struct WidgetExplicit{
	int data;
	explicit WidgetExplicit(int _data):data{_data}{};
	~WidgetExplicit(){
		std::cout << "----~WidgetExplicit()----" << std::endl;
	}
};

/* 下面这两个 class 尤其其构造器中一个参数函授默认值，因此它其实符合上面的隐式转换的规则 */
struct WidgetMultiParameter{
	int data1;
	int data2;
	explicit WidgetMultiParameter(int data1, int data2 = 0): data1(data1){}
	~WidgetMultiParameter(){
		std::cout << "----~WidgetMultiParameter()----" << std::endl;
	}
};

struct WidgetMultiParameterNoExplicit{
	int data1;
	int data2;
	WidgetMultiParameterNoExplicit(int _data1, int _data2 = 0): data1(_data1){}
	~WidgetMultiParameterNoExplicit(){
		std::cout << "----~WidgetMultiParameterNoExplicit()----" << std::endl;
	}
};

namespace test_explicit{
	int main(){
		WidgetNoExplicit w1 = 1;
		
		// 下面这句实际上存在一个隐式的类型转换，
		// 当写了 explicit 之后，不允许这样的转换发生
		// 错误
		// WidgetExplicit w2 = 1;

		WidgetExplicit w2{1};

		// WidgetMultiParameter w3 = 1;  // 报错
		WidgetMultiParameter w3 {1};  // 报错
		WidgetMultiParameterNoExplicit w4 = 1;
		return 0;
	}
}

int main(){
	test_explicit::main();
	return 0;
}
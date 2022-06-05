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

#include <iostream>

// POD https://docs.microsoft.com/en-us/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170

namespace test_default_initializer{
	struct Test1{
		int x {};
		int y {};
		Test1(){std::cout << "Function Name: "<< __PRETTY_FUNCTION__ << " " << "Line: " <<__LINE__ << std::endl;};
	};

	struct Test2{
	private:
		int x;
		int y;
	};

	struct Test3{
	private:
		int x;
	public:
		int y;
	};

	int main(){
		Test1 t {};
		std::cout << t.x << " " << t.y << std::endl;
		std::cout << "-----------------------" << std::endl;
		std::cout << std::is_pod<Test1>::value << std::endl; // false
		std::cout << std::is_trivial<Test1>::value << std::endl; // false
		std::cout << std::is_standard_layout<Test1>::value << std::endl; // true
		std::cout << "-----------------------" << std::endl;
		std::cout << std::is_pod<Test2>::value << std::endl; // true
		std::cout << std::is_trivial<Test2>::value << std::endl; // true
		std::cout << std::is_standard_layout<Test2>::value << std::endl; // true
		std::cout << "-----------------------" << std::endl;
		std::cout << std::is_pod<Test3>::value << std::endl; // false
		std::cout << std::is_trivial<Test3>::value << std::endl; // true
		std::cout << std::is_standard_layout<Test3>::value << std::endl; // false
		return 0;
	}
}

int main(){
	test_default_initializer::main();
	return 0;
}
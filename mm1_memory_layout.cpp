#include <iostream>
#pragma pack(8)

/*
	首先我的平台是 64 位，按照 8 字节对齐.
	实际上内存对齐是按照有效对齐值做的，所谓的有效对齐值就是 #pragma pack 中指定的参数与类中
	最长数据类型
*/
namespace test_memory_align{
	class Test1{
		char a;
		double b;
		char c;
	};
	class Test2{
		double a;
		char b;
		char c;
	};
	class Test3{
		char a;
		char b;
		double c;
	};
	class C3
	{
		int i1; //4
		char c1;//1

		int i2; //4
		char c2; //1

		int i3;
		char c3;
		
		int i4;
		char c4; 
	
	};//32

	class C4
	{
		int i1; //4byte 
		int i2; 
		int i3;
		int i4;

		char c1;
		char c2; 
		char c3;
		char c4; 
	};//20
	int main(){
		std::cout << sizeof(Test1) << std::endl;
		std::cout << sizeof(Test2) << std::endl;
		std::cout << sizeof(Test3) << std::endl;
		std::cout << sizeof(C3) << std::endl;
		std::cout << sizeof(C4) << std::endl;
		return 0;
	}
}

int main(){
	test_memory_align::main();
	return 0;
}
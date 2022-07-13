#include <iostream>

namespace test_rvo{
	struct Base{
		int a;
		int b;

		Base() = default;
		Base(int, int) {
			std::cout << "Base ctor" << std::endl;
		};
		~Base() {
			std::cout << "Base dtor" << std::endl;
		};

		/*
		Base(const Base &){
			std::cout << "Base copy ctor" << std::endl;
		};

		Base& operator=(const Base&){
			std::cout << "Base operator= copy assigment" << std::endl;
			return *this;
		};
		*/

		Base(Base&&){
			std::cout << "Base move ctor" << std::endl;
		};
		Base& operator=(Base&&){
			std::cout << "Base operator= move assigment" << std::endl;
			return *this;
		};

		// Base(const Base &) = delete;
		// Base(Base&&) = delete;
		// Base& operator=(Base const&) = delete;
		// Base& operator=(Base&&) = delete;
	};

	Base create_rvo(){
		return Base(100, 200);
	}

	Base create_nrvo(){
		Base b(1, 2);
		// return std::move(b); // 这里会依赖 move 构造函数
		return b;
	}

	int main(){
		/* 对已经创建的 Base 对象，不存在返回值优化 */
		{
			Base b(1000, 2000);
			b = create_nrvo();
		}
		std::cout << "--------" << std::endl;
		{
			Base b(1000, 2000);
			b = create_rvo();
		}


		/* 未初始化的对象才会使用 RVO */
		std::cout << "--------" << std::endl;
		{
			// Named Return Value Optimization, 要求 Base(Base&&) 必须存在，但是不会调用
			Base b = create_nrvo();
		}
		std::cout << "--------" << std::endl;
		{
			Base b = create_rvo();  // Return Value Optimization
		}
		return 0;
	}
}

int main(){
	test_rvo::main();
	return 0;
}


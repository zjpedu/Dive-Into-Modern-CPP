// clang version 13.1.6
// 参考 C++ primer page 538
#include <iostream>

namespace test_override
{
	struct BaseX final{ };
	/* 不能将 final 类型作为基类*/
	// struct DerivedX: BaseX { };
	struct BaseY{
		/*
			final 实现需要有 {具体的函数定义逻辑} 否则编译通不过
			当然这个设计其实不合理
		*/
		virtual void f()final {};
		/*
			a missing vtable usually means the first non-inline virtual member
			function has no definition.
		*/
		// virtual void f_error() final;
		virtual float g(int){ return 0;};
		virtual void h(float) {};
		void F(int);
	};
	struct DerivedY: BaseY{
		// 无法重写 final 函数
		// virtual void f() override{};
		// 使用 override 声明的成员函数不能重写基类成员
		// virtual float g(long) override;
		virtual float g(int)override {return 0;};
		// virtual void g(int) override{};
		virtual void h(float) override {};
		/*
			不能在非 virtual 函数中声明 final
			实际上防止了 F 被子类重写
		*/
		virtual void F(int) final {};
	};

	struct DerivedZ: DerivedY{
		// 无法重写 final 函数
		// virtual void F(int) override{};
		/*virtual*/ float g(int) override {return 1;};
	};
	int main(){
		DerivedY dy;
		std::cout << dy.g(2) << std::endl;
		DerivedZ dz;
		std::cout << dz.g(2) << std::endl;
		return 0;
	}
}

int main(){
	std::cout << __cplusplus << std::endl;
	test_override::main();
	return 0;
}
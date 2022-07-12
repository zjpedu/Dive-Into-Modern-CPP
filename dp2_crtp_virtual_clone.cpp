#include <iostream>
#include <memory>

namespace test_virtual_clone_fiunction{
/*
	* 利用虚函数的多态性动态绑定了不同的 clone 实现，这在 C++ 中是一种著名的设计习语： 虚构造器
	* 在多态场景下，多态基类一般需要实现 virtual clone，通过自身实现浅拷贝或者深拷贝。
	* virtual clone 的返回值具有一致性，需要返回多态基类的指针，基于内存管理的要求，我们通常返回
	unique_ptr<Base>
	* 可以使用 crtp 设计习语来实现多态基类的深拷贝，代码见 namespace test_crtp
*/
	struct Shape{
		Shape() = default;
		Shape(const Shape&){
			std::cout << "Shape copy ctor" << std::endl;
		}
		Shape(Shape&&){
			std::cout << "Shape move ctor" << std::endl;
		};
		Shape& operator=(const Shape&) = default;
		Shape& operator=(Shape&&) = default;

		virtual std::unique_ptr<Shape> clone(){
			std:: cout << "Shape clone" << std::endl;
			// std::unique_ptr<Shape> ptr(new Shape(*this));
			std::unique_ptr<Shape> ptr(new Shape(std::move(*this)));   // 这里调用 Shape 的移动构造函数
			return ptr;
		}
		virtual ~Shape(){};
	};

	struct Line: public Shape{ // implementation inherent
		Line() = default;
		Line(const Line&){
			std::cout << "Line copy ctor" << std::endl;
		}
		Line(Line&&){
			std::cout << "Line move ctor" << std::endl;
		};
		Line& operator=(const Line&) = default;
		Line& operator=(Line&&) = default;
		virtual std::unique_ptr<Shape> clone() override{
			std:: cout << "Line clone" << std::endl;
			// std::unique_ptr<Line> ptr(new Line(*this));
			std::unique_ptr<Line> ptr(new Line(std::move(*this)));   // 这里调用 Line 的移动构造函数
			return ptr;
		}
	};

	struct Circle: public Shape{
		Circle() = default;
		Circle(const Circle&){
			std::cout << "Circle copy ctor" << std::endl;
		}
		Circle(Circle&&){
			std::cout << "Circle move ctor" << std::endl;
		};
		Circle& operator=(const Circle&) = default;
		Circle& operator=(Circle&&) = default;
		virtual std::unique_ptr<Shape> clone() override {
			std:: cout << "Circle clone" << std::endl;
			// std::unique_ptr<Circle> ptr(new Circle(*this)); // 这里 new Circle(*this) 实际上调用了 Circle 的拷贝构造函数
			std::unique_ptr<Circle> ptr(new Circle(std::move(*this)));   // 这里调用 Circle 的移动构造函数
			return ptr;
		}
	};

	int main(){
		Shape* s1 = new Circle();
		std::unique_ptr<Shape> s1_clone = s1->clone();
		std::cout << "------" << std::endl;
		Shape* s2 = new Line();
		std::unique_ptr<Shape> s2_clone = s2->clone();
		std::cout << "------" << std::endl;
		Shape* s3 = new Shape();
		std::unique_ptr<Shape> s3_clone = s3->clone();
		return 0;
	}
}

namespace test_crtp{
/*
	利用 CRTP (奇异递归模板模式) 实现了多态的 clone
*/
	struct Shape{
		virtual ~Shape() {
			std::cout << "Shape dtor" << std::endl;
		};
		virtual std::unique_ptr<Shape> clone() const = 0;  // pure virtual function
	};

	template <typename T>
	struct CloneShape: public Shape{  // interface inherent, 一般都是 public 继承
		virtual std::unique_ptr<Shape> clone() const{
			// (static_cast<T const&>(*this)) 这么转型是因为 T 需要做拷贝构造，
			// 调用了 T 的拷贝构造函数
			// 这里实际上存在多态性，即 Shape* 的指针指向了气子类的对象，这在多态场景下合法
			// std::unique_ptr<Shape> ptr(new T(static_cast<T const&>(*this))); 
			// return ptr;
			// 下面这里实际上构造了一个 T 类型的对象，所以会调用拷贝构造函数
			return std::make_unique<T> (static_cast<T const&>(*this));
		}
	};
	// CRTP
	struct Line: public CloneShape<Line>{
		Line() = default;
		Line(const Line&){
			std::cout << "Line copy ctor" << std::endl;
		}
		Line(Line &&) = default;
		Line& operator=(const Line&) = default;
		Line& operator=(Line&&) = default;
		virtual ~Line() {
			std::cout << "Line dtor" << std::endl;
		};
	};

	struct Circle: public CloneShape<Circle>{
		Circle() = default;
		Circle(const Circle&){
			std::cout << "Circle copy ctor" << std::endl;
		}
		Circle(Circle &&) = default;
		Circle& operator=(const Circle&) = default;
		Circle& operator=(Circle&&) = default;
		virtual ~Circle(){
			std::cout << "Circle dtor" << std::endl;
		};
	};
	void process(Shape* s){
		std::cout << "process" << std::endl;
		std::unique_ptr<Shape> s_clone = s->clone();
	};
	int main(){
		CloneShape<Line> cs1;
		std::unique_ptr<Shape> cs1_clone = cs1.clone();
		std::cout << "--------" << std::endl;
		CloneShape<Circle> cs2;
		std::unique_ptr<Shape> cs2_clone = cs2.clone();
		std::cout << "--------" << std::endl;
		process(new Line());
		return 0;
	}
}

int main(){
	std::cout << "----virtual ctor idiom----" << std::endl;
	test_virtual_clone_fiunction::main();
	std::cout << "----Curiously Recurrsive Template Pattern----" << std::endl;
	test_crtp::main();
	return 0;
}

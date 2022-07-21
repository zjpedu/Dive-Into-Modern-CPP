#include <memory>
#include <iostream>

struct A{
	int data;
	A(int _data):data{_data}{};
	A(const A& other) = default;
	A& operator=(const A& other) = default;
	A(A&& other) = default;
	A& operator=(A&& other)= default;
};

struct Foo
{
public:
	Foo(std::unique_ptr<A> ref) : mRef(std::move(ref)) {
		std::cout << "Foo default ctor" << std::endl;
	};

	Foo(const Foo& other) : mRef {std::make_unique<A>(other.mRef->data)}{
		std::cout << "Foo copy ctor" << std::endl;
	};
	
	Foo& operator=(const Foo& other) {
		if(this == &other){
			return *this;
		}
		Foo tmp(other);
		std::swap(this->mRef->data, other.mRef->data);
		std::cout << "Foo copy assignment" << std::endl;
		return *this;
	}

	Foo(Foo&& other) : mRef(std::move(other.mRef)) {
		std::cout << "Foo move ctor" << std::endl;
	};

	Foo& operator=(Foo&& other){
		this->mRef = std::move(other.mRef);
		std::cout << "Foo move assignment" << std::endl;
		return *this;
	}

	~Foo() = default;
	// ~Foo(){
	// 	std::cout << "~Foo" << std::endl;
	// }
	std::unique_ptr<A> getMref(){
		return std::move(this->mRef);
	}
protected:
	std::unique_ptr<A> mRef;
};

int main(){
	Foo f1 = Foo(std::make_unique<A>(1));
	Foo f2 = f1; 
	Foo f3(f1);

	Foo f4 = Foo(std::make_unique<A>(2));
	Foo f5 (std::move(f1));
	Foo f6 = std::move(f4);
	
	return 0;
}
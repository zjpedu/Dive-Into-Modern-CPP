/*
    使用 CRTP 实现 template method.
*/

#include <iostream>

template <typename T>
struct Library{
	void run(){
		s1();
		if(s2())
			s3();
		s4();
		s5();
	}
    void destroy(){
		delete sub();
	}
protected:
	void s1(){
		std::cout << "Library s1 method" << std::endl;
	}
	void s3(){
		std::cout << "Library s3 method" << std::endl;
	}
	bool s2(){
		return sub()->s2();  // 静态绑定多态导出类对象
	}
	void s4(){
		return sub()->s4(); // 静态绑定多态导出类对象
	}
	void s5(){
		std::cout << "Library s5 method" << std::endl;
	}
	T* sub(){return static_cast<T*>(this);};  // 模拟虚函数. 虚函数其实就是子类的指针

	~Library(){
		std::cout << "~Library()" << std::endl;
	};
	 int num {0};
};

struct App: public Library<App>{
	bool s2(){
		while(num < 5){
			std::cout << "App s2 method" << std::endl;
			num++;
		}
		return false;
	}
	void s4(){
		std::cout << "App s4 method num = " << num << std::endl;
	}
	~App(){
		std::cout << "~App()" << std::endl;
	}
};

int main(){
	Library<App>* lib = new App();  // 这里只能声明为指针或者引用,它们具有多态性,对象不具有多态性.
	lib->run();
	lib->destroy();
	return 0;
}
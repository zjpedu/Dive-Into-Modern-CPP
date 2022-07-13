/*
    使用 CRTP 实现 template method
*/

#include <iostream>

template <typename T>
struct Library{
    void run(){
        s1();
	    if(sub->s2())
		    s3();
	    sub->s4();
	    s5();
    }
    void s1(){
		std::cout << "Library s1 method" << std::endl;
	}
	void s3(){
		std::cout << "Library s3 method" << std::endl;
	}
	void s5(){
		std::cout << "Library s5 method" << std::endl;
	}
    T* sub(){return static_cast<T*>(this);};
    int num {0};
	~Library(){
        std::cout << "~Library()" << std::endl;
    };
};

struct App: public Library{
private:
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
};

int main(){
    Library* lib = new App();  // 这里只能声明为指针或者引用,它们具有多态性,对象不具有多态性.
    lib->run();
	delete lib;
    return 0;
}
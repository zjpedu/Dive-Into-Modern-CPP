#include <iostream>

struct Library{
    void run(){
        s1();
	    if(s2())
		    s3();
	    s4();
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
    int num {0};
	virtual ~Library(){};
private: // Non-virtual interface (NVI) 规定所有的 virtual 函数都应该是 private 或者 protected
    virtual bool s2() = 0;
    virtual void s4() = 0;
};

struct App: public Library{
private:
    virtual bool s2() override {
		while(num < 5){
			std::cout << "App s2 method" << std::endl;
			num++;
		}
		return false;
	}
	virtual void s4() override {
		std::cout << "App s4 method num = " << num << std::endl;
	}
};

int main(){
    Library* lib = new App();  // 这里只能声明为指针或者引用,它们具有多态性,对象不具有多态性.
    lib->run();
	delete lib;
    return 0;
}

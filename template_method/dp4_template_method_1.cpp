#include <iostream>

/*
    template method 方法的需求是:当前用户完成某个特定的任务需要依次调用 s1->s2->s3->s4->s5 方法,
    与此同时, s1 s3 s5 方法从由 Library 库给出,用户需要自己实现 s2 和 s4 方法. 要完成这个过程,我们可以设计如下代码.
*/

struct Library{
public:
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
};

struct App: public Library{
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
	Library lib;
	App app;

	// 实际上在这里用户组装了整个执行过程,这显示不好,这样的设计符合开闭原则
	lib.s1();
	if(!app.s2())
		lib.s3();
	app.s4();
	lib.s5();
	return 0;
}
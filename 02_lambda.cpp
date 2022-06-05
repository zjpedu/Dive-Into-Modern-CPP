#include <iostream>
#include <vector>
#include <algorithm>  // for_each

namespace test_lambda{
    void print(){
        std::vector<int> v{1,2,3,4,5,6,7};
        std::for_each(v.begin(), v.end(), [](int i){
                // i pass by value
                i++;
                std::cout << i << " ";
        });
        std::cout << std::endl;
        for(auto &i : v){
            std::cout << i << " ";
        }
        std::cout << std::endl;
        std::for_each(v.begin(), v.end(), [](int &i){
            // i pass by reference
            i++;
            std::cout << i << " ";
        });
        std::cout << std::endl;
         for(auto &i : v){
            std::cout << i << " ";
         }
         std::cout << std::endl;

    }
    int main(){
        print();
        return 0;
    }
};


namespace test_introducer{
	using FilterContainer = std::vector<std::function<bool()>>;
	FilterContainer filters;
	class Widget{
	public:
		void addFilter() const;
		Widget(int _w): divisor(_w) {};
	public:
		int divisor;
    };

	void Widget::addFilter() const{
		int divisorCopy = divisor;
		std::cout << "&divisorCopy = " << &divisorCopy << " " <<"&divisor = " << &divisor << std::endl;
		// std::cout <<"&divisor = " << &divisor << std::endl;
		std::cout << "divisorCopy = " << divisor << " " << "divisor = " << this->divisor << std::endl;
		// std::cout << "divisor = " << divisor << std::endl;
		std::cout << "----------" << std::endl;
		// filters.emplace_back([divisor = divisor]() -> bool{
		filters.emplace_back([&divisorCopy, this]() -> bool{
		// filters.emplace_back([=]() -> bool{
		// filters.emplace_back([&]() -> bool{
		// filters.emplace_back([divisor = divisor]() -> bool{
			std::cout << "&divisorCopy = " << &divisorCopy << " " <<"&divisor = " << &divisor << std::endl;
			// std::cout <<"&divisor = " << &divisor << std::endl;
			std::cout << "divisorCopy = " << divisorCopy << " " << "divisor = " << this->divisor << std::endl;
			// std::cout << "divisor = " << divisor << std::endl;
			return 1000 % divisor == 0;
		});
	}
	/*
		如果我们去掉 doSomework(), 将其逻辑移动到 main 函数中,那么上面我们采用 & 或者 = 捕获就能得到正确的结果.
	*/
	// void doSomework(){
	// 	auto pw = new Widget(1000);
	// 	pw->addFilter();
	// }

	int main(){
		// doSomework();
		auto pw = new Widget(1000);
		pw->addFilter();
		filters[0]();
		return 0;
	}
}


/*
	这个测试用来证明,gi 能被访问到不是因为 lambda 补货到了 gi,而是因为其是一个全局变量
	到底哪些变量能被捕获,参见下面链接
	https://en.cppreference.com/w/cpp/language/lambda 中 Explianation 部分
*/
int gi = 30;
namespace test_introducer_global_variable{
	int main(){
		int j = 30;
		{
			// auto lamb1 = [gi, j]()mutable{
			// 	std::cout << "&j = " << &j << ", j = " << ++j << ", &gi = " << &gi << ", gi = " << gi << std::endl;
			// };  // error: 'gi' cannot be captured because it does not have automatic storage duration
			// auto lamb2 = [&gi, &j](){
			// 	std::cout << "&j = " << &j << ", j = " << ++j << ", &gi = " << &gi << ", gi = " << gi << std::endl;
			// }; // error: 'gi' cannot be captured because it does not have automatic storage duration
			auto lamb3 = [=]()mutable{
				std::cout << "&j = " << &j << ", j = " << ++j << ", &gi = " << &gi << ", gi = " << gi << std::endl;
			};
			auto lamb4 = [&](){
				std::cout << "&j = " << &j << ", j = " << ++j << ", &gi = " << &gi << ", gi = " << gi << std::endl;
			};
			lamb3();
			std::cout << "&j = " << &j << ", j = " << ++j << ", &gi = " << &gi << ", gi = " << gi << std::endl;
			lamb4();
			std::cout << "&j = " << &j << ", j = " << ++j << ", &gi = " << &gi << ", gi = " << gi << std::endl;
		}
		return 0;
	}
}

int main(){
	// test_lambda::main();
	test_introducer::main();
	// test_introducer_global_variable::main();
	return 0;
}

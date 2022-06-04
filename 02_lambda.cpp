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
		// int divisorCopy = divisor;
		// std::cout << "&divisorCopy = " << &divisor << " " <<"&divisor = " << &divisor << std::endl;
		std::cout <<"&divisor = " << &divisor << std::endl;
		//std::cout << "divisorCopy = " << divisor << " " << "divisor = " << this->divisor << std::endl;
		std::cout << "divisor = " << divisor << std::endl;
		std::cout << "----------" << std::endl;
		// filters.emplace_back([&divisorCopy, this]() -> bool{
		filters.emplace_back([divisor = divisor]() -> bool{
			//std::cout << "&divisorCopy = " << &divisorCopy << " " <<"&divisor = " << &divisor << std::endl;
			std::cout <<"&divisor = " << &divisor << std::endl;
			//std::cout << "divisorCopy = " << divisorCopy << " " << "divisor = " << divisor << std::endl;
			std::cout << "divisor = " << divisor << std::endl;
			return 1000 % divisor == 0;
		});
	}
	void doSomework(){
		auto pw = std::make_unique<Widget>(1000);
		pw->addFilter();
	}

	int main(){
		doSomework();
		std::cout << filters[0]() << std::endl;
		return 0;
	}
}

int main(){
	// test_lambda::main();
	test_introducer::main();
	return 0;
}

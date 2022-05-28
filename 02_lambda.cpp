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
}

int main(){
    test_lambda::main();
    return 0;
}

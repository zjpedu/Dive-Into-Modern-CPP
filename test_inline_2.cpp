#include <iostream>

struct Test{
    inline static int a = 200;
};

inline int inline_test(int x){
    return x * x * x;
}

int test2(){
    return inline_test(2);
}

int t2(){
    return Test::a;
}
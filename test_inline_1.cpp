#include <iostream>

struct Test{
    inline static int a = 100;
};

inline int inline_test(int x){
    return x * x;
}

int test1(){
    return inline_test(2);
}

int t1(){
    return Test::a;
}
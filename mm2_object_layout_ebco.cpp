#include <iostream>
using namespace std;





class Base{
public:
    void process()
    {

    }
 
};

/*
// 0x0000800
void process(Base* this)
{

}*/

class Base2{
public:
    void invoke()
    {

    }
};

class Sub1{  
    Base b;
    double data; 

public:
    void func(){
        b.process();
    }
};

// 私有继承 == 组合
class Sub2: private Base { 
    double data; 

public:
    void func(){
        Base::process();
    }
};



int main()
{
    int d1;
    Base b; //1byte 
    Base* pb=&b;
    int d2;
    //b.process(); //process(&b)  -> JMP 0x0000800

    cout<<sizeof(Base)<<endl;
    cout<<sizeof(Sub1)<<endl;
    cout<<sizeof(Sub2)<<endl;

    
}
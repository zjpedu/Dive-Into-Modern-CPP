#include <iostream>

using namespace std;


class Base1{
public:
	long long d1;

	virtual unique_ptr<Base1> clone(){
		return nullptr;
	}
};

class Base2{
public:
    long long d2;
    
    virtual void M2(){
        
    }
};

class Sub: public Base1, public Base2{
public:
    long long d3;

    virtual void M3(){

    }
};

int main(){
	Base1 b1;


	Sub s;

	b1=s;

	b1.d1=100;
	Base2 b2;
	b2.d2=200;
	
	s.d1=100;
	s.d2=200;
	s.d3=300;
	cout<<sizeof(b1)<<endl;
	cout<<sizeof(b2)<<endl;
	cout<<sizeof(Sub)<<endl; //16+16+8 = 32+8=40

	long long* p1=(long long*)&b1;
	long long* pvt1=p1;
	cout<<*p1<<",";
	p1++;
	cout<<*p1<<endl;

    long long* p2=(long long*)&b2;
    long long* pvt2=p2;
    cout<<*p2<<",";
    p2++;
    cout<<*p2<<endl;

    long long* p3=(long long*)&s;
    long long* pvt3=p3;
    cout<<*p3<<",";
    p3++;
    cout<<*p3<<",";
    p3++;
    long long* pvt4=p3;
    cout<<*p3<<",";
    p3++;
    cout<<*p3<<",";
    p3++;
    cout<<*p3<<endl;


    cout<<*pvt1<<":"<< *((long long*)(*pvt1))<<endl;
    cout<<*pvt2<<":"<< *((long long*)(*pvt2))<<endl;
    
    cout<<*pvt3<<":"<< *((long long*)(*pvt3))<<endl;

    cout<<*pvt4<<":"<< *((long long*)(*pvt4))<<endl;
}



/*
cout<<sizeof(Sub)<<endl; //16+16+8 = 32+8=40 的结果如下：
reference: https://cloud.tencent.com/developer/article/1755489
*** Dumping AST Record Layout                                                   
  27          0 | class Base1                                                        
  26          0 |   (Base1 vtable pointer)                                           
  25          8 |   long long d1                                                     
  24            | [sizeof=16, dsize=16, align=8,                                     
  23            |  nvsize=16, nvalign=8]                                             
  22                                                                                 
  21 *** Dumping AST Record Layout                                                   
  20          0 | class Base2                                                        
  19          0 |   (Base2 vtable pointer)                                           
  18          8 |   long long d2                                                     
  17            | [sizeof=16, dsize=16, align=8,                                     
  16            |  nvsize=16, nvalign=8]                                             
  15                                                                                 
  14 *** Dumping AST Record Layout                                                   
  13          0 | class Sub                                                          
  12          0 |   class Base1 (primary base)                                       
  11          0 |     (Base1 vtable pointer)                                         
  10          8 |     long long d1                                                   
   9         16 |   class Base2 (base)                                               
   8         16 |     (Base2 vtable pointer)                                         
   7         24 |     long long d2                                                   
   6         32 |   long long d3                                                     
   5            | [sizeof=40, dsize=40, align=8,                                     
   4            |  nvsize=40, nvalign=8]     
*/

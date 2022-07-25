#include <iostream>
#include <memory>

struct Widget{
	int m_x;
	int m_y;
	int m_z;

public:
	Widget(int x,int y , int z):
		m_x(x), m_y(y),m_z(z)
	{
        std::cout << "Widget default ctor" << std::endl;
    }

	void print(){
		std::cout<<m_x<<","<<m_y<<","<<m_z<<std::endl;
	}

	Widget(const Widget& w){
		std::cout << "Widget copy ctor" << std::endl;
	}

	Widget& operator=(const Widget& w){
		std::cout << "Widget copy assignment" << std::endl;
		return *this;
	}

	Widget(Widget&& w){
		std::cout << "Widget move ctor" << std::endl;
	}

	Widget& operator=(Widget&& w){
		std::cout << "Widget move assignment" << std::endl;
		return w;
	}

	~Widget()
	{
		std::cout << "Widget dtor" << std::endl;
	}
	
	// 永远不要返回 this 指针的 unique_ptr，这会导致运行时错误
	// std::unique_ptr<Widget> getWidget(){
	// 	return std::unique_ptr<Widget>(this);
	// }
};

struct DeleteWithLog { 
	// int data {0};
	void operator()(Widget* w) { 
		delete w;
		std::cout<<"------ DeleteWithLog delete w"<<std::endl;
	} 
};

void deleteFunction(Widget* w) { 
	delete w;
	std::cout<<"------ deleteFunction delete w"<<std::endl;
}

std::unique_ptr<Widget> getWidgetPtr()
{
    std::unique_ptr<Widget> w(new Widget(10,20,30));
    return w;
}

void process(Widget* p)
{

}
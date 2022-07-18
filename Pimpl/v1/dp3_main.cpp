#include "abi.h"

int main(){
	MyPimpl m;
	std::cout << "----process start----" << std::endl;
	m.process();
	std::cout << "----process end----" << std::endl;	
	return 0;
}
#include <iostream>
#include <vector>

namespace test_initializer_list{
	class Widget{
		int x = 0;
		int y {0};
		// int z (0);
	};
	int main(){
		return 0;
	}
} // namespace test_initializer_list

int main(){
	test_initializer_list::main();
	return 0;
}
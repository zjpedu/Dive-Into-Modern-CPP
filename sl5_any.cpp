#include <iostream>
#include <vector>
#include <string>
#include <any>

/*
	any simulation using Object-Orient techniques.
*/
namespace test_any_implementation{
	struct message_base{
		virtual ~message_base() = default;
	};

	template <typename Msg>
	struct wrapped_message: message_base{
		public:
		Msg content;
		explicit wrapped_message(const Msg& contents_): content(contents_){};
	};
	int main(){
		message_base* m1 = new wrapped_message(5);
		message_base* m2 = new wrapped_message(3.14);
		message_base* m3 = new wrapped_message(std::string("hello"));
		std::vector<message_base*> v {m1, m2, m3};
		for(auto i: v){
			std::cout << i << std::endl;
		}
		return 0;
	}
}

int main(){
	test_any_implementation::main();
	return 0;
}


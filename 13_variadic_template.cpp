#include <iostream>
#include <string>

namespace test_variadic_template{
	/*
	template <typename... T>
	void print(T... args){
		std::cout << sizeof...(args) << std::endl;
	}
	*/
	/*
	void print(){

	}
	template<typename T, typename... Type>
	void print(T firstArg, Type... args){
		std::cout << firstArg << std::endl;
		print(args...);
	}
	
	template <typename T>
	void print(T firstArg){
		std::cout << firstArg << std::endl;
	}
	template<typename T, typename... Type>
	void print(T firstArg, Type... args){
		print<T>(firstArg);
		print(args...);
	}
	*/
	/*
	double sum = 0;
	void recursive_sum(){}
	template <typename T, typename... Types>
	void recursive_sum(T firstArg, Types... args){
		sum += firstArg;
		recursive_sum(args...); 
	}
	*/
	/*
	template <typename T>
	double recursive_sum(T firstArg){
		return static_cast<double>(firstArg);
	}
	template <typename T, typename... Types>
	double recursive_sum(T firstArg, Types... args){
		return recursive_sum(firstArg) + recursive_sum(args...);
	}
	
	double recursive_sum(){
		return 0;
	}
	template <typename T, typename... Types>
	double recursive_sum(T firstArg, Types... args){
		return firstArg + recursive_sum(args...);
	}
	*/
	// template <typename T>
	// void print(T t){
	// 	std::cout << t << std::endl;
	// }
	// template <typename ...Args>
	// void print(Args... args)
	// {
	// 	// int arr[] = {(print(args),0)...};
	// 	std::initializer_list<int> arr{(print(args),0)...};
	// }

	// template <typename... Args>
	// void unpack(Args... args){
	// 	int arr[] = {(args, 0)...};
	// 	for(int i = 0; i < sizeof...(args); ++i)
	// 		std::cout << arr[i] << std::endl;
	// }
	// template <typename F, typename ...Args>
	// void print(F&& f, Args... args)
	// {
	// 	int arr[] {(f(std::forward<Args>(args)),0)...};
	// }
	// template <typename... > struct tuple;  // 抽象不完整的类定义
	// template<> struct tuple<> {}; // 递归出口，如果我们注释掉这段代码，报错信息将提示我们定义这段结构
	// template <typename Head, typename... Tail>
	// struct tuple<Head, Tail...>: public tuple<Tail...>  // 都是定义为一个和一包的关系，递归解开一包
	// {
	// 	using inherited = tuple<Tail...>;
	// protected:
	// 	Head m_head;
	// public:
	// 	tuple(){};
	// 	tuple(Head h, Tail... tail): m_head(h), inherited(tail...){};
	// 	Head head() {return m_head;};
	// 	inherited& tail(){return *this;};
	// };

	// 继承改写为组合 
	// template <typename... > struct tuple;  // 抽象不完整的类定义
	// template<typename Head> struct tuple<Head> {
	// protected:
	// 	Head m_head;
	// public:
	// 	tuple(){};
	// 	tuple(Head h): m_head(h){};
	// 	Head head() {return m_head;};
	// }; // 递归出口，如果我们注释掉这段代码，报错信息将提示我们定义这段结构
	// template <typename Head, typename... Tail>
	// struct tuple<Head, Tail...> // 都是定义为一个和一包的关系，递归解开一包
	// {
	// 	using composited = tuple<Tail...>;
	// protected:
	// 	Head m_head;
	// 	composited m_tail;
	// public:
	// 	tuple(){};
	// 	tuple(Head h, Tail... tail): m_head(h), m_tail(tail...){};
	// 	Head head() {return m_head;};
	// 	composited& tail(){return m_tail;};
	// };

	template <typename... Args>
	void unpack(Args... args){
		int arr[] = {(args, 0)...};  // 这里和上面的代码有区别
		for(int i = 0; i < sizeof...(args); ++i)
			std::cout << arr[i] << std::endl;
	}
	int  main(){
		// std::string str("hello");
		// print(1, 3.14, str, "world!");
		unpack(1, 3.14, "hello");
		// recursive_sum(1, 3.14);
		// std::cout << sum << std::endl;
		// std::cout << recursive_sum(1, 3.14) << std::endl;
		// unpack(1,2,3);
		// print([](auto i){std::cout << i << std::endl;}, 1,3.14,"hello");
		// tuple<int, float, std::string> t{1, 3.14, "hello"};
		// std::cout << t.head() << std::endl;
		// std::cout << t.tail().head() << std::endl;
		return 0;
	}
}

namespace test_fold_expression{
	// template<typename... Types>
	// double sum1(Types... args){
	// 	return (... + args);  // 这里必须要加括号, 一元左折叠
	// }

	// template<typename T, typename... Types>
	// double sum2(T first, Types...args){
	// 	return (first + ... + args); // 二元左折叠
	// }

	// template <typename... Types>
	// double sum3(Types... args){
	// 	return (args + ...);  // 一元右折叠
	// }

	// template<typename T, typename... Types>
	// double sum4(T first, Types...args){
	// 	return (args + ... + first); // 二元右折叠
	// }

	// template<typename... Types>
	// double sum5(Types...args){
	// 	return (args + ... + 0); // 二元右折叠
	// }
	// template<typename... Types>
	// double sum6(Types...args){
	// 	return (0 + ... + args); // 二元左折叠
	// }


	// template<typename... Types>
	// void print1(Types... args){
	// 	(std::cout << ... << args) << std::endl; 
	// }
	
	// template<typename... Types>
	// void print2(Types... args){
	// 	((std::cout << args << std::endl), ...) ;
	// }

	// template<typename... Types>
	// void print3(Types... args){
	// 	(..., (std::cout << args << std::endl)); 
	// }

	// template <typename T>
	// void printArg(T t){
	// 	std::cout << t << std::endl;
	// }
	// template <typename... Types>
	// void print4(Types... args){
	// 	(printArg(args), ...);
	// }
	// int main(){
	// 	std::cout << sum1(1, 3.14) << std::endl;
	// 	std::cout << sum2(1, 3.14) << std::endl;
	// 	std::cout << sum3(1, 3.14) << std::endl;
	// 	std::cout << sum4(1, 3.14) << std::endl;
	// 	std::cout << sum5(1, 3.14) << std::endl;
	// 	 std::cout << sum6(1, 3.14) << std::endl;
	// 	print1(1, 3.14, "hello");
	// 	std::cout << "---- print1 end ----" << std::endl;
	// 	print2(1, 3.14, "hello");
	// 	std::cout << "---- print2 end ----" << std::endl;
	// 	print3(1, 3.14, "hello");
	// 	std::cout << "---- print3 end ----" << std::endl;
	// 	print4(1, 3.14, "hello");
	// 	std::cout << "---- print4 end ----" << std::endl;
	// 	return 0;
	// }
}

int main(){
	test_variadic_template::main();
	// test_fold_expression::main();
	return 0;
}
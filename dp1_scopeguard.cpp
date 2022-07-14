//  在 boost 和 folly 中都有 scopeguard
#include <iostream>
#include <stack>
using namespace std;

template <typename F>  // 这个模板参数是一个可调用的函数对象
class ScopeGuard
{
public:
	template <typename T> // 这个模板参数是一个可调用的函数对象
	explicit ScopeGuard(T&& t) : m_func(std::forward<T>(t)), m_dismiss(false){}

	explicit ScopeGuard(const F& f) : m_func(f), m_dismiss(false){}

	~ScopeGuard()
	{
		if (!m_dismiss)
			m_func();  //在析构 ScopeGuard 对象的时候回调 m_func
	}

	ScopeGuard(ScopeGuard && rhs) :
		m_func(std::move(rhs.m_func)), m_dismiss(rhs.m_dismiss){
			rhs.dismiss();
	}

	ScopeGuard()=delete;
	ScopeGuard(const ScopeGuard&)=delete;  // 没必要拷贝构造
	ScopeGuard& operator=(const ScopeGuard&)=delete;

	void dismiss()
	{
		m_dismiss = true;  // 解除 m_func 的调用
	}

private:
	F m_func;
	bool m_dismiss;
};


void FileProcess()
{
	FILE* fp = fopen("filename", "wb");  // FILE* 这不是一根指针,这是一个对象句柄,应该包装成为一个对象
	ScopeGuard scopeGuard(  [&]() { fclose(fp); }   );
	// 文件处理....
	//关闭文件
	//fclose(fp);
}

void invoke(int data)
{
	if(data<0)
	{
		invalid_argument exp("data");
		throw exp;
	}
}

void process()
{
	stack<string> cityStack;

	cityStack.push("Shanghai"s);
	auto lamb = [&](){
		string s=cityStack.top();
		cityStack.pop();
		cout<<"roll back: "<<s<<endl;
		};
	ScopeGuard scopeGuard1{lamb};
	ScopeGuard scopeGuard2{[&](){
		string s=cityStack.top();
		cityStack.pop();
		cout<<"roll back: "<<s<<endl;
		}};

	cout<<"invoke..."<<endl;
	invoke(-100);

	scopeGuard1.dismiss();
	scopeGuard2.dismiss();
}


int main(){
	try {
		process();
	} catch(invalid_argument& e) {
		cerr<<"invalid arg: " << e.what()<<endl;
	}
}

// class scope_guard {
//    public:
//     template <class Callable>
//     scope_guard(Callable&& undo_func) try
//     } catch (...) {
//         undo_func();
//         throw;
//     }

//     scope_guard(scope_guard&& other) : f(std::move(other.f)) {
//         other.f = nullptr;
//     }

//     ~scope_guard() {
//         if (f) f();  // must not throw
//     }

//     void dismiss() noexcept { f = nullptr; }

//     scope_guard(const scope_guard&) = delete;
//     void operator=(const scope_guard&) = delete;

//    private:
//     std::function<void()> f;
// };

// int main(){
//     auto lamb = [&](){
//             cout<<"roll back: " <<endl;
//             };
//     scope_guard scopeGuard1{lamb};
//     scope_guard scopeGuard2{[&](){
//         cout<<"roll back: "<<endl;
//         }};
//     return 0;
// }

// template <typename T>
// class A
// {
// public:
//     A(T&& t) : t_(std::move(t)) {std::cout << t << std::endl;};
//     // A(T& t) : t_(t) {std::cout << t << std::endl;};

// private:
//     T t_;
// };


// int main()
// {
//     double b = 5.5;
//     A a1(b);
//     A a2(5.6);
// }

// template<class T> struct A {
//     explicit A(const T&, ...) noexcept; // #1
//     A(T&&, ...);                        // #2
// };

// template <typename F>
// class ScopeGuard
// {
// public:
//     template <typename T>
//     explicit ScopeGuard(T&& t) : m_func(std::forward<T>(t)), m_dismiss(false)
//     {
//     }

//     explicit ScopeGuard(F& f) : m_func(f), m_dismiss(false) {}

//     ~ScopeGuard()
//     {
//         if (!m_dismiss)
//             m_func();
//     }

//     ScopeGuard(ScopeGuard&& rhs) :
//         m_func(std::move(rhs.m_func)), m_dismiss(rhs.m_dismiss) {
//         rhs.dismiss();
//     }

//     ScopeGuard() = delete;
//     ScopeGuard(const ScopeGuard&) = delete;
//     ScopeGuard& operator=(const ScopeGuard&) = delete;

//     void dismiss()
//     {
//         m_dismiss = true;
//     }

// private:
//     F m_func;
//     bool m_dismiss;

// };

// enum class ScopeGuardOnExit {};

// template <typename T>
// inline ScopeGuard<T> operator+(ScopeGuardOnExit, T&& t)
// {
//     auto lamd = []() {printf("%s", "HelloWorld\n");};
//     return ScopeGuard<T>(std::forward<T>(t));
// }

// int main()
// {
//     {
//         auto lamd = []() {printf("%s", "HelloWorld\n");};
//         auto tmp = ScopeGuardOnExit() + lamd;
//         auto tmp2 = ScopeGuardOnExit() + []() {printf("%s", "HelloWorld\n");};
//     }
// }

// template <typename T>
// class A
// {
// public:
//     template <typename U>
//     A(U&& u) : t_(u) {std::cout << t_ << std::endl;};
//     A(const T& t) : t_(t) {std::cout << t_ << std::endl;};

// private:
//     T t_;
// };

// // template <typename T>
// // A<T> make_a(T&& t) { return A<T>(std::forward<T>(t)); }

// int main()
// {
//     double b = 5.5;
//     // A a1(make_a(b));
//     A a1(b);
//     A<double&> a2(5.6);
// }

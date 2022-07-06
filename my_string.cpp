#include <iostream>
#include <functional>
#include <vector>
#include <set>
#include <any>
#include <algorithm>
#include <string>
using namespace std;

/*
 * 在32位系统中占用char* + size_t + 虚析构函数指针 = 12个字节，64为系统中为24字节
 */
class String {
public:
	// 默认构造函数
	String() :_data(nullptr), _len(0)
	{
		//cout << "DCtor, " << "this = "<< this <<  endl;
		cout << "DCtor" << endl;
	}
	// 普通构造函数
	String(const char* p) : _len(strlen(p))
	{
		cout << "Ctor" << endl;
		_init_data(p);
	}
	// 拷贝构造函数
	String(const String& str) : _len(str._len) {
		cout << "CCtor, " << "this = " << this << ", &str = " << &str << endl;
		_init_data(str._data);
	}
	// 拷贝赋值运算符
	String& operator= (const String& str) {
		cout << "CAsgn, " << "this = " << this << ", &str = " << &str << endl;
		if (this != &str) {
			if (_data) delete[] _data;
			_len = str._len;
			_init_data(str._data);
		}
		return *this;
	}
	// 移动构造函数，加上noexcept是为了让vector重新分配内存时调用
	String(String&& str) noexcept : _data(str._data), _len(str._len) {
		cout << "MCtor, " << "this = " << this << ", &str = " << &str << endl;
		str._len = 0;
		str._data = nullptr;
	}
	// 移动赋值运算符，加上noexcept是为了让vector重新分配内存时调用
	String& operator= (String&& str) noexcept {
		cout << "MAsgn, " << "this = " << this << ", &str = " << &str << endl;
		if (this != &str) {
			if (_data) delete[] _data;
			_len = str._len;
			_data = str._data;
			str._len = 0;
			str._data = nullptr;
		}
		return *this;
	}
	// 虚析构函数，占用对象的一个指针的内存
	virtual ~String() noexcept {
		// cout << "Dtor, " << "this = " << this << endl;
		cout << "Dtor" <<  endl;
		if (_data) {
			delete[] _data;
		}
	}
	// 为了可以放到set容器中，需要重载operator<，第一个参数是this指针
	bool operator< (const String& rhs) const{	// 为了让const对象也能调用，后面一个const不能少
		return this->_len < rhs._len;
	}
	// 为了可以放到set容器中，需要重载operator==，第一个参数是this指针
	bool operator== (const String& rhs) const {	// 为了让const对象也能调用，后面一个const不能少
		return string(this->_data) == string(rhs._data);
	}
	// 重载‘+’运算符
	String& operator+ (const String& rhs) {
		_len += rhs._len;
		_data = new char[_len];
        return *this;
	}
	// 输出流，第一个参数是ostream&，所以要申明为友元函数
	friend ostream& operator<< (ostream& os, const String& s);
private:
	char* _data;
	size_t _len;
	void _init_data(const char* s)
	{
		_data = new char[_len + 1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}
};

ostream& operator<< (ostream& os, const String& s) {
	return os << s._data;
}

int main() {
	String() = "xxxx";
	// String str {String{"hello world"}}; // Copy elision https://en.cppreference.com/w/cpp/language/copy_elision
        // String str = std::move(String{"hello world"});
        // String s {"hello, world~"};
        // String str1{std::move(s)};
}

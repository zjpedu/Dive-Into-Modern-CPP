![Github stars](https://img.shields.io/github/stars/zjpedu/Dive-Into-Modern-CPP.svg)
![github language](https://img.shields.io/badge/language-C++-green.svg)
![](https://img.shields.io/github/license/zjpedu/Dive-Into-Modern-CPP.svg)
![](https://img.shields.io/github/forks/zjpedu/Dive-Into-Modern-CPP.svg)

## Dive Into Modern C++

The project is aim to dive into c++ new features for languages, standard library, design pattern and memory management.
It is important to understand the nature of the dark magic. The C++ language is getting better and better.

### C++ Standard

C++ 11, C++ 14, C++ 17, and C++ 20 are used usually.

### How to run the project

In macos,I use the vscode to `mkbuild`, `cmake`, `compile`, `run`, and `rmbuild` the project.
I write the `tasks.json` and `launch.json` files to use easily the project.

```shell
command + shift + B # select "compile" or "run" or "cmake" or "mkbuild"  tasks.json
```

Then select the following options:

1. mkbuild. It will build directory for the compile and run.
2. cmake. It will issue the Makefile.
3. compile. It will build the project.
4. run. It will run the some executable file in tasks.json.
5. rmbuild. It can help you to delete the build file, which can re-generate the build files.

```shell
F5  # debug launch.json
```

If you may add the different cpp files, you should add executable file in `CMakeLists.txt`.

### Outline of Dark Magic

#### Language Features
* 01 `final` and `override` [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/01_final_override.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/01_final_override.cpp)
* 02 lambda and functor [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/02_lambda.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/02_lambda.cpp)
* 03 `typdef`, `typename` and `using` [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/03_typedef_using.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/03_typedef_using.cpp)
* 04 `enum` [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/04_enum.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/04_enum.cpp)
* 05 `auto`, `decltype` and deducing types [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/05_auto_decltype.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/05_auto_decltype.cpp)
* 06 initializer list and uniform initialization [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/06_initializer_list.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/06_initializer_list.cpp)
* 07 Covariant Return Types [Document](https://quuxplusone.github.io/blog/2019/01/20/covariance-and-contravariance/)
* 08 `explicit` [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/08_explicit.cpp)
* 09 Rule of Five [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/09_rule_of_five.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/09_rule_of_five.cpp)
* 10 How to write special member functions correctly in modern C++ [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/10_smfd.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/10_smfd.cpp)
* 11 `inline` [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/11_inline.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/11_inline.cpp) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/test_inline_1.cpp) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/test_inline_2.cpp)
* 12 `nullptr`, 0, and `NULL` [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/12_nullptr.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/12_nullptr.cpp)
* 13 From variadic templates to Fold Expression: An Template Recursive Techniques [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/13_variadic_template.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/13_variadic_template.cpp)
* 14 Default Initializers for Member Variables and POD [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/14_default_initializer.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/14_default_initializer.cpp)
* 15 Return Value Optimization [cppreference](https://en.cppreference.com/w/cpp/language/copy_elision) [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/15_rvo.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/15_rvo.cpp)


#### Standard Library

* SL1
* SL2 std::bind [Document]() [Code]()
* SL3 hash<T> [Document]() [Code]()
* SL4 Allocator [Document]() [Code]()
* SL5 std::any [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/sl5_any.md) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/sl5_any.cpp)
* SL6 std::function [Document]() [Code]()
* SL7 std::string [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/sl7_my_string.cpp)


#### Template Techniques


#### Design Pattern and Idiom

* DP1 ScopeGuard and RAII [Document]() [ScopeGuard Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/dp1_scopeguard.cpp) [RAII Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/dp1_raii.cpp)
* DP2 CRTP and `virtual clone` virtual constructor design idiom [Code1](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/dp2_crtp_virtual_clone.cpp) [Code2](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/dp2_crtp.cpp)
* DP3 PImpl [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/Pimpl/dp3_Pimpl_idiom.md) [Code1](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/Pimpl/dp3_Pimpl_idiom.cpp) [Code2](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/Pimpl/abi.h)
* DP4 Template Method [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/template_method/dp4_template_method.md) [Code1](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/template_method/dp4_template_method_1.cpp) [Code2](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/template_method/dp4_template_method_2.cpp) [Code3](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/template_method/dp4_crtp_template_method.cpp)
* DP5 Strategy design pattern and Policy-based idiom [Code1](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/strategy/dp5_strategy_1.cpp) [Code2](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/strategy/dp5_strategy_2.cpp) [Code3](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/strategy/dp5_policy_1.cpp) [Code4](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/strategy/dp5_policy_2.cpp)
* DP6 Observer Design Pattern [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/observer) The design pattern is very important.
* DP7 Factory Design Pattern

#### Memory Management

* MM1 class memory layout [imgs1](https://github.com/zjpedu/Dive-Into-Modern-CPP/blob/main/imgs/memory_align_1.jpeg) [imgs2](https://github.com/zjpedu/Dive-Into-Modern-CPP/blob/main/imgs/memory_align_2.jpeg) [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/mm1_memory_layout.cpp)
* MM2 object layout and EBCO [Code](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/mm2_object_layout_ebco.cpp)
* MM3 virtual function layout
* MM4 smart pointer [Document](https://github.com/jpzhu-edu/Dive-Into-Modern-CPP/blob/main/smart-pointer/mm4_smart_pointer.md) [unique_ptr](https://github.com/jpzhu-edu/Dive_Into_Modern_CPP/blob/main/smart_pointer/mm4_smart_pointer_unique.cpp) [shared_ptr](https://github.com/jpzhu-edu/Dive_Into_Modern_CPP/blob/main/smart_pointer/mm4_smart_pointer_shared.cpp) [Nest Smart Pointer](https://github.com/jpzhu-edu/Dive_Into_Modern_CPP/blob/main/smart_pointer/nest_smart_pointer.cpp)
* MM5 move semantics [Document]() [Code]()


#### Coroutines


### Contribute

If you want to add new features, please open the pull requests.

### References

1. https://arne-mertz.de/category/cpp/modern-cpp/
2. Effective Modern C++, by Scott Meyers
3. C++ Crash Course: A Fast-Paced Introduction, by Josh Lospinoso
4. C++ Template: The Completion Guide (2nd), by David Vandevoorde
5. C++ Concurrency in Action (2nd). by Anthony Williams
6. C++ core guidelines https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines

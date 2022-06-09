cmake_minimum_required(VERSION 3.10)

# 设置PROJECT_NAME变量
set(PROJECT_NAME DIVE_INTO_MODERN_CPP)

# 设置工程名
project (${PROJECT_NAME})

# 递归所有的 cpp 文件
file (GLOB_RECURSE SOURCE_FILES *.cpp)

# 设置 c++20 标准
# C standard can be overridden when this is used as a sub-project.
if(NOT CMAKE_C_STANDARD)
  # This project can use C20, but will gracefully decay down to C89.
  set(CMAKE_C_STANDARD 20)
  set(CMAKE_C_STANDARD_REQUIRED OFF)
  set(CMAKE_C_EXTENSIONS OFF)
endif(NOT CMAKE_C_STANDARD)

# C++ standard can be overridden when this is used as a sub-project.
if(NOT CMAKE_CXX_STANDARD)
  # This project requires C++20.
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)


# 一个个增加可执行文件,也就是一个个增加所有包含 main 函数的文件,将其编译为可执行文件
add_executable(test1 01_final_override.cpp)
add_executable(test2 02_lambda.cpp)
add_executable(test3 03_typedef_using.cpp)
add_executable(test4 04_enum.cpp)
add_executable(test5 05_auto_decltype.cpp)
add_executable(test6 06_initializer_list.cpp)
add_executable(test11 11_inline.cpp test_inline_1.cpp test_inline_2.cpp)
add_executable(test12 12_nullptr.cpp)
# add_executable(test13 13_variadic_template.cpp)
add_executable(test14 14_default_initializer.cpp)

add_executable(test_hanoi hanoi.cpp)
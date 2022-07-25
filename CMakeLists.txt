# https://www.hahack.com/codes/cmake/
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
add_executable(test8 08_explicit.cpp)
add_executable(test9 09_rule_of_five.cpp)
add_executable(test11 11_inline.cpp test_inline_1.cpp test_inline_2.cpp)
add_executable(test12 12_nullptr.cpp)
add_executable(test13 13_variadic_template.cpp)
add_executable(test14 14_default_initializer.cpp)
add_executable(test15 15_rvo.cpp)
# add_executable(test_hanoi hanoi.cpp)


add_executable(sl5 sl5_any.cpp)
add_executable(sl7 sl7_my_string.cpp)

add_executable(mm1 mm1_memory_layout.cpp)
add_executable(mm2 mm2_object_layout_ebco.cpp)
add_executable(mm3 mm3_virtual_function_layout.cpp)
add_executable(mm4_1 smart_pointer/mm4_smart_pointer_unique.cpp)
add_executable(mm4_2 smart_pointer/mm4_smart_pointer_shared.cpp)
add_executable(mm4_3 smart_pointer/nest_smart_pointer.cpp)

add_executable(dp1 dp1_scopeguard.cpp)
add_executable(dp1_raii dp1_raii.cpp)
add_executable(dp2 dp2_crtp_virtual_clone.cpp)
add_executable(dp2_1 dp2_crtp.cpp)
add_executable(dp3 Pimpl/v1/dp3_main.cpp Pimpl/v1/abi.h Pimpl/v1/dp3_Pimpl_idiom.cpp)
add_executable(dp4_1 template_method/dp4_template_method_1.cpp)
add_executable(dp4_2 template_method/dp4_template_method_2.cpp)
add_executable(dp4_3 template_method/dp4_crtp_template_method.cpp)
add_executable(dp5_1 strategy/dp5_strategy_1.cpp)
add_executable(dp5_2 strategy/dp5_strategy_2.cpp)
add_executable(dp5_3 strategy/dp5_policy_1.cpp)
add_executable(dp5_4 strategy/dp5_policy_2.cpp)
add_executable(dp6_1 observer/observer1/FileDownloader1.cpp observer/observer1/MainForm1.cpp observer/observer1/main.cpp)
add_executable(dp6_2 observer/observer2/FileDownloader2.cpp observer/observer2/MainForm2.cpp observer/observer2/main.cpp)
add_executable(dp6_3 observer/observer3/FileDownloader3.cpp observer/observer3/MainForm3.cpp observer/observer3/main.cpp)
add_executable(dp6_4 observer/observer4/FileDownloader4.cpp observer/observer4/MainForm4.cpp observer/observer4/main.cpp)
add_executable(dp6_5 observer/observer5/FileDownloader5.cpp)
add_executable(dp6_6 observer/observer6/FileDownloader6.cpp)


# Iterator the files to automatically get the executable file
# file(GLOB_RECURSE _sources RELATIVE
#   "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
# )
# foreach(_source IN LISTS _sources)
#  get_filename_component(_dest ${_source} NAME_WE)
#  add_executable(${_dest} ${_source})
#  set_target_properties(${_dest}
#    PROPERTIES
#      CXX_STANDARD 20
#      CXX_EXTENSIONS OFF
#      CXX_STANDARD_REQUIRED ON
#      POSITION_INDEPENDENT_CODE 1
#  )
# endforeach()
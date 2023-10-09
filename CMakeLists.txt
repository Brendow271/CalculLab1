cmake_minimum_required(VERSION 3.24)
project(CalcLab1)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_HEADERS Calculator.h Loader.h Operation.h)

add_executable (CalcLab1 ${PROJECT_SOURCE_DIR}/ Calculator.cpp main.cpp Loader.cpp Operation.cpp )

#add_library(sin SHARED ./dll_cpp/sin.cpp "dll_cpp/sin.cpp")
#add_library(cos SHARED ./dll_cpp/cos.cpp "dll_cpp/cos.cpp")
#add_library(Pow SHARED ./dll_cpp/Pow.cpp "dll_cpp/Pow.cpp")
#add_library(ln SHARED ./dll_cpp/ln.cpp "dll_cpp/ln.cpp")
#
#target_link_libraries(CalcLab1 sin cos ln Pow)

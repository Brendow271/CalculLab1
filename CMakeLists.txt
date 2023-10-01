cmake_minimum_required(VERSION 3.24)
project(CalcLab1)

set(CMAKE_CXX_STANDARD 24)
set(PROJECT_HEADERS Calculator.h Loader.h Operation.h)

add_executable (CalcLab1 ${PROJECT_SOURCE_DIR}/ Calculator.cpp main.cpp Loader.cpp Operation.cpp )
set_property(TARGET CalcLab1 PROPERTY CXX_STANDARD 23)

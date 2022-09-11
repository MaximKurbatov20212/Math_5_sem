cmake_minimum_required(VERSION 3.21)
project(Math)

set(CMAKE_CXX_STANDARD 11)

add_executable(Math main.cpp CubicEquation.cpp QuadraticEquation.cpp )

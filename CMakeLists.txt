cmake_minimum_required(VERSION 3.27)
project(Lab1CLion)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1CLion main.cpp
        shapes.cpp
        shapes.hpp
        interface.cpp
        interface.hpp)

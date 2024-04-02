cmake_minimum_required(VERSION 3.27)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1 main.cpp
        figures.cpp
        Figures/figures.hpp
        interface.cpp
        interface.hpp
        errorsandexceptions.hpp
        exceptions/NonViableNumberException.hpp
        exceptions/NotNumberException.hpp
        exceptions/EmptyListException.hpp
        exceptions/BadDeletionIndexException.hpp
        exceptions/BadDeletionPerimeterException.hpp
        Figures/Circle/Circle.cpp
        Figures/Circle/Circle.hpp
        Figures/Rectangle/Rectangle.cpp
        Figures/Rectangle/Rectangle.hpp
        Figures/Triangle/Triangle.cpp
        Figures/Triangle/Triangle.hpp
        exceptions/FigureNonViableException.hpp
        Point.cpp
        Point.hpp
        exceptions/InterfaceChoiceException.hpp
)

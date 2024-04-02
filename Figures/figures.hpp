#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "../Point.hpp"

using namespace std;

class Figure
{
protected:
    string inputName;

public:
    virtual string name();
    explicit Figure(string inputName);
    virtual double findPerimeter() = 0;
    virtual void showPerimeter() = 0;
    virtual void showParameters() = 0;
    virtual ~Figure() = default;
};

#endif // SHAPES_HPP

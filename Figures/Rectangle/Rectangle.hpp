#ifndef LAB1_RECTANGLE_HPP
#define LAB1_RECTANGLE_HPP

#include "../figures.hpp"
#include "../../exceptions/FigureNonViableException.hpp"
#include "../../Point.hpp"

class Rectangle : public Figure
{
public:
    Rectangle(const string &name, Point leftUpAngle, Point rightDownAngle);
    double findPerimeter() override;
    void showPerimeter() override;
    void showParameters() override;

private:
    Point getLeftUpAngle();
    Point getRightDownAngle();
    Point leftUpAngle, rightDownAngle;
};



#endif //LAB1_RECTANGLE_HPP

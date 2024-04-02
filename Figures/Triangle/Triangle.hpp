#ifndef LAB1_TRIANGLE_HPP
#define LAB1_TRIANGLE_HPP

#include "../figures.hpp"
#include "../../exceptions/FigureNonViableException.hpp"
#include "../../Point.hpp"

class Triangle : public Figure
{
public:
    Triangle(const string &name, Point firstAngle, Point secondAngle, Point thirdAngle);
    double findPerimeter() override;
    void showPerimeter() override;
    void showParameters() override;

private:
    Point firstAngle, secondAngle, thirdAngle;
};

#endif //LAB1_TRIANGLE_HPP

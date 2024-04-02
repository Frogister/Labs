#ifndef LAB1_CIRCLE_HPP
#define LAB1_CIRCLE_HPP

#include "../figures.hpp"
#include "../../exceptions/FigureNonViableException.hpp"
#include "../../Point.hpp"

class Circle : public Figure
{
public:
    Circle(const string &name, Point center, double radiusCircle);
    double findPerimeter() override;
    void showPerimeter() override;
    void showParameters() override;
    Point getCenter();

private:
    Point center;
    double radiusCircle;
};


#endif //LAB1_CIRCLE_HPP

#include "Rectangle.hpp"

Rectangle::Rectangle(const string &name, Point leftUpAngle, Point rightDownAngle)
        : Figure(name), leftUpAngle(leftUpAngle), rightDownAngle(rightDownAngle) {
    if (leftUpAngle.getX() == rightDownAngle.getX() || leftUpAngle.getY() == rightDownAngle.getY())
    {
        throw FigureNonViableException(FIGURE_NON_VIABLE);
    }
}

double Rectangle::findPerimeter() {
    double width = fabs(rightDownAngle.getX() - leftUpAngle.getX());
    double height = fabs(rightDownAngle.getY() - leftUpAngle.getY());
    return 2 * (width + height);
}

void Rectangle::showPerimeter() {
    cout << "Figure name: " << inputName << endl;
    cout << "Type: Rectangle" << endl;
    cout << "Perimeter: " << this->findPerimeter() << endl;
}

void Rectangle::showParameters()
{
    cout << "Figure name: " << inputName << endl;
    cout << "Type: Rectangle" << endl;
    cout << "Left Up Angle: (" << leftUpAngle.getX() << ", " << leftUpAngle.getY() << ")" << endl;
    cout << "Right Down Angle: (" << rightDownAngle.getX() << ", " << rightDownAngle.getY() << ")" << endl;
}
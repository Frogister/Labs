#include "Circle.hpp"

Circle::Circle(const string &name, Point center, double radius)
        : Figure(name), center(center), radiusCircle(radius)
        {
            if (radius <= 0)
            {
                throw FigureNonViableException(FIGURE_NON_VIABLE);
            }
        }

double Circle::findPerimeter() {
    return 2 * M_PI * radiusCircle;
}

void Circle::showPerimeter() {
    cout << "Figure name: " << inputName << endl;
    cout << "Type: Circle" << endl;
    cout << "Perimeter: " << this->findPerimeter() << endl;
}

void Circle::showParameters()
{
    cout << "Figure name: " << inputName << endl;
    cout << "Type: Circle" << endl;
    cout << "Center coordinates: (" << center.getX() << ", " << center.getY() << ") ";
}

#include "Triangle.hpp"

Triangle::Triangle(const string &name, Point firstAngle, Point secondAngle, Point thirdAngle)
        : Figure(name), firstAngle(firstAngle), secondAngle(secondAngle), thirdAngle(thirdAngle){
    double side1 = sqrt(pow(firstAngle.getX() - secondAngle.getX(), 2) + pow(firstAngle.getY() - secondAngle.getY(),2));
    double side2 = sqrt(pow(firstAngle.getX() - thirdAngle.getX(), 2) + pow(firstAngle.getY() - thirdAngle.getY(),2));
    double side3 = sqrt(pow(secondAngle.getX() - thirdAngle.getX(), 2) + pow(secondAngle.getY() - thirdAngle.getY(),2));
    if (side1 >= side2 + side3 || side2 >= side1 + side3 || side3 >= side1 + side2)
    {
        throw FigureNonViableException(FIGURE_NON_VIABLE);
    }
}

double Triangle::findPerimeter() {
    double side1 = sqrt(pow(firstAngle.getX() - secondAngle.getX(), 2) + pow(firstAngle.getY() - secondAngle.getY(),2));
    double side2 = sqrt(pow(firstAngle.getX() - thirdAngle.getX(), 2) + pow(firstAngle.getY() - thirdAngle.getY(),2));
    double side3 = sqrt(pow(secondAngle.getX() - thirdAngle.getX(), 2) + pow(secondAngle.getY() - thirdAngle.getY(),2));
    return side1 + side2 + side3;
}

void Triangle::showPerimeter() {
    cout << "Figure name: " << inputName << endl;
    cout << "Type: Triangle" << endl;
    cout << "Perimeter: " << this->findPerimeter() << endl;
}

void Triangle::showParameters() {
    cout << "Figure name: " << inputName << endl;
    cout << "Type: Triangle" << endl;
    cout << "First point coordinate: (" << firstAngle.getX() << "," << firstAngle.getY() << ")" << endl;
    cout << "Second point coordinate: (" << secondAngle.getX() << "," << secondAngle.getY() << ")" << endl;
    cout << "Third point coordinate: (" << thirdAngle.getX() << "," << thirdAngle.getY() << ")" << endl;
}
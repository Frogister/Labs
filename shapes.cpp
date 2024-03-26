#include "shapes.hpp"

Shape::Shape(string name) : inputName(std::move(name)) {}

string Shape::name()
{
    return inputName;
}

Circle::Circle(const string &name, pair<double, double> center, double radius)
        : Shape(name), center(center), radiusCircle(radius) {}

double Circle::perimeter() const
{
    return 2 * M_PI * radiusCircle;
}

Triangle::Triangle(const string &name, pair<double, double> firstAngle, pair<double, double> secondAngle, pair<double, double> thirdAngle)
        : Shape(name), firstAngle(std::move(firstAngle)), secondAngle(std::move(secondAngle)), thirdAngle(std::move(thirdAngle)) {}

double Triangle::perimeter() const
{
    double side1 = sqrt(pow(secondAngle.first - firstAngle.first, 2) + pow(secondAngle.second - firstAngle.second, 2));
    double side2 = sqrt(pow(thirdAngle.first - secondAngle.first, 2) + pow(thirdAngle.second - secondAngle.second, 2));
    double side3 = sqrt(pow(firstAngle.first - thirdAngle.first, 2) + pow(firstAngle.second - thirdAngle.second, 2));
    return side1 + side2 + side3;
}

Rectangle::Rectangle(const string &name, pair<double, double> leftUpAngle, pair<double, double> rightDownAngle)
        : Shape(name), leftUpAngle(std::move(leftUpAngle)), rightDownAngle(std::move(rightDownAngle)) {}

double Rectangle::perimeter() const
{
    double width = fabs(rightDownAngle.first - leftUpAngle.first);
    double height = fabs(rightDownAngle.second - leftUpAngle.second);
    return 2 * (width + height);
}

pair<double, double> Circle::getCenter()
{
    return center;
}

void Circle::setCenter(pair<double, double> newCenter)
{
    center = newCenter;
}

double Circle::getRadius() const
{
    return radiusCircle;
}

void Circle::setRadius(double newRadius)
{
    radiusCircle = newRadius;
}

pair<double, double> Rectangle::getLeftUpAngle()
{
    return leftUpAngle;
}

void Rectangle::setLeftUpAngle(pair<double, double> newLeftUpAngle)
{
    leftUpAngle = newLeftUpAngle;
}

pair<double, double> Rectangle::getRightDownAngle()
{
    return rightDownAngle;
}

void Rectangle::setRightDownAngle(pair<double, double> newRightDownAngle)
{
    rightDownAngle = newRightDownAngle;
}

pair<double, double> Triangle::getFirstAngle()
{
    return firstAngle;
}

void Triangle::setFirstAngle(pair<double, double> newFirstAngle)
{
    firstAngle = newFirstAngle;
}

pair<double, double> Triangle::getSecondAngle()
{
    return secondAngle;
}

void Triangle::setSecondAngle(pair<double, double> newSecondAngle) {
    secondAngle = newSecondAngle;
}

pair<double, double> Triangle::getThirdAngle() {
    return thirdAngle;
}

void Triangle::setThirdAngle(pair<double, double> newThirdAngle) {
    thirdAngle = newThirdAngle;
}

pair<double, double> inputPoint()
{
    double x, y;
    cin >> x >> y;
    if (cin.fail())
    {
        throw NotNumber("Not number");
    }
    return make_pair(x, y);
}
#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "errorsandexceptions.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Shape
{
protected:
    string inputName;

public:
    virtual string name();
    explicit Shape(string inputName);
    virtual double perimeter() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape
{
public:
    Circle(const string &name, pair<double, double> center, double radiusCircle);
    double perimeter() const override;
    pair<double, double> getCenter();
    double getRadius() const;
    void setCenter(pair<double, double> center);
    void setRadius(double radius);

private:
    pair<double, double> center;
    double radiusCircle;
};

class Triangle : public Shape
{
public:
    Triangle(const string &name, pair<double, double> firstAngle, pair<double, double> secondAngle, pair<double, double> thirdAngle);
    double perimeter() const override;
    pair<double, double> getFirstAngle(), getSecondAngle(), getThirdAngle();
    void setFirstAngle(pair<double, double> firstAngle);
    void setSecondAngle(pair<double, double> secondAngle);
    void setThirdAngle(pair<double, double> thirdAngle);

private:
    pair<double, double> firstAngle, secondAngle, thirdAngle;
};

class Rectangle : public Shape
{
public:
    Rectangle(const string &name, pair<double, double> leftUpAngle, pair<double, double> rightDownAngle);
    double perimeter() const override;
    pair<double, double> getLeftUpAngle();
    pair<double, double> getRightDownAngle();
    void setLeftUpAngle(pair<double, double> leftUpAngle);
    void setRightDownAngle(pair<double, double> rightDownAngle);

private:
    pair<double, double> leftUpAngle, rightDownAngle;
};

pair<double, double> inputPoint();

#endif // SHAPES_HPP

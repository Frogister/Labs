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

class Triangle : public Shape
{
public:
    Triangle(const string &name, pair<double, double> firstAngle, pair<double, double> secondAngle, pair<double, double> thirdAngle);
    double perimeter() const override;
    pair<double, double> getFirstAngle();
    pair<double, double> getSecondAngle();
    pair<double, double> getThirdAngle();
    void setFirstAngle(pair<double, double> firstAngle);
    void setSecondAngle(pair<double, double> secondAngle);
    void setThirdAngle(pair<double, double> thirdAngle);

private:
    pair<double, double> firstAngle, secondAngle, thirdAngle;
};

void addShape(vector<Shape *> &shapes);
void printShapesPerimeter(const vector<Shape *> &shapes);
void printShapesParameters(const vector<Shape *> &shapes);
void printSumPerimeters(const vector<Shape *> &shapes);
void sortShapesFromDownToUp(vector<Shape *> &shapes);
void deleteShapeByIndex(vector<Shape *> &shapes, int index);
void deleteShapeIfLessThanNum(vector<Shape *> &shapes, double personalPerimeter);

#endif // SHAPES_HPP

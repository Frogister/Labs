#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <map>
#include "shapes.hpp"
#include <functional>
#include "errorsandexceptions.hpp"

using namespace std;

class Menu
{
public:
    static map<int, function<void(vector<Shape *>&)>> menuOptions;
    static map<int, function<void(vector<Shape *>&)>> shapesOptions;
    static void initializeMenuOptions();
    static void initializeShapesOptions();
    static void executeMenu();
    static void callMenu();
    static void addShape(vector<Shape *> &shapes);
    static void addCircle(vector<Shape *> &shapes);
    static void addTriangle(vector<Shape *> &shapes);
    static void addRectangle(vector<Shape *> &shapes);
    static void printShapesParameters(vector<Shape *> &shapes);
    static void printShapesPerimeter(vector<Shape *> &shapes);
    static void printSumPerimeters(vector<Shape *> &shapes);
    static void sortShapesFromDownToUp(vector<Shape *> &shapes);
    static void deleteShapeByIndex(vector<Shape *> &shapes);
    static void deleteShapeIfLessThanNum(vector<Shape *> &shapes);
};

void listEmptinessCheck(vector<Shape *> &shapes);
bool comparePerimeters(Shape* a, Shape* b);
double getDeletionPerimeter();
int getDeletionIndex();

#endif // INTERFACE_HPP

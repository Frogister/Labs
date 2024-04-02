#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <string>
#include <map>
#include "Figures/figures.hpp"
#include "Figures/Circle/Circle.hpp"
#include "Figures/Rectangle/Rectangle.hpp"
#include "Figures/Triangle/Triangle.hpp"
#include "Point.hpp"
#include <functional>
#include "errorsandexceptions.hpp"

using namespace std;

class Interface
{
private:
    using MethodPtr = void (Interface::*)();
    void callMethod(const int& methodName);
    void callFigureMethod(const int& methodName);

    int exitInterface;
    vector<Figure *> figures;
    map<int, MethodPtr> InterfaceOptions;
    map<int, MethodPtr> figuresOptions;

    void initializeInterfaceOptions();
    void initializeFiguresOptions();
    void callInterface();
    void exitInterfaceExecute();

    void addFigure();
    void printFiguresParameters();
    void printFiguresPerimeter();
    void printSumPerimeters();
    void sortFiguresFromDownToUp();
    void deleteFigureByIndex();
    void deleteFigureIfLargerThanNum();

    void addCircle();
    void addTriangle();
    void addRectangle();

    Circle* getCircle();
    Triangle* getTriangle();
    Rectangle* getRectangle();

    static bool comparePerimeters(Figure* a, Figure* b);

    template<typename T>
    T inputValue();
public:
    void executeInterface();

};

void listEmptinessCheck(vector<Figure *> &Figures);

#endif // INTERFACE_HPP

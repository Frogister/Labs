#include "Point.hpp"

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

Point::Point(double cX, double cY) {
    x = cX;
    y = cY;
}
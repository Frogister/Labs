#ifndef LAB1_POINT_HPP
#define LAB1_POINT_HPP


class Point {
private:
    double x;
    double y;
public:
    Point(double cX, double cY);
    double getX() const;
    double getY() const;
};

#endif //LAB1_POINT_HPP

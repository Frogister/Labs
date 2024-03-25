#include "shapes.hpp"

Shape::Shape(string name) : inputName(std::move(name)) {}

string Shape::name()
{
    return inputName;
}

Circle::Circle(const string &name, pair<double, double> center, double radius)
        : Shape(name), center(std::move(center)), radiusCircle(radius) {}

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
        throw NonViableNumber("Non viable number");
    }
    return make_pair(x, y);
}

void addShape(vector<Shape *> &shapes)
{
    while (true) {
        cout << "Choose type of shape: " << endl;
        cout << "1. Circle" << endl;
        cout << "2. Triangle" << endl;
        cout << "3. Rectangle" << endl;
        int type;
        cin >> type;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter number" << endl;
        }
        if (type == 1)
        {
            cout << "Enter shape name: " << endl;
            string name;
            cin >> name;
            cout << "Enter center: " << endl;
            pair<double, double> center = inputPoint();

            cout << "Enter radius: " << endl;
            double radius;
            cin >> radius;
            while (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter number" << endl;
            }
            shapes.push_back(new Circle(name, center, radius));
            break;
        }
        else if (type == 2)
        {
            cout << "Enter shape name: " << endl;
            string name;
            cin >> name;
            cout << "Enter first angle: " << endl;
            pair<double, double> firstAngle = inputPoint();
            cout << "Enter second angle: " << endl;
            pair<double, double> secondAngle = inputPoint();
            cout << "Enter third angle: " << endl;
            pair<double, double> thirdAngle = inputPoint();
            shapes.push_back(new Triangle(name, firstAngle, secondAngle, thirdAngle));
            break;
        }
        else if (type == 3)
        {
            cout << "Enter shape name: " << endl;
            string name;
            cin >> name;
            cout << "Enter left up angle: " << endl;
            pair<double, double> leftUpAngle = inputPoint();
            cout << "Enter right down angle: " << endl;
            pair<double, double> rightDownAngle = inputPoint();
            shapes.push_back(new Rectangle(name, leftUpAngle, rightDownAngle));
            break;
        }
    }
}

void printShapesParameters(const vector<Shape *> &shapes)
{
    cout << "Numbered list of shapes with shape type and params: " << endl;
    for (int i = 0; i < shapes.size(); i++)
    {
        cout << i + 1 << ". ";
        if (dynamic_cast<Circle *>(shapes[i]) != nullptr)
        {
            auto *circle = dynamic_cast<Circle *>(shapes[i]);
            cout << "Circle: " << circle->name() << ", center: (" << circle->getCenter().first << ", " << circle->getCenter().second << "), radius: " << circle->getRadius() << endl;
        }
        else if (dynamic_cast<Triangle *>(shapes[i]) != nullptr)
        {
            auto *triangle = dynamic_cast<Triangle *>(shapes[i]);
            cout << "Triangle: " << triangle->name() << ", first angle: (" << triangle->getFirstAngle().first << ", " << triangle->getFirstAngle().second << "), second angle: (" << triangle->getSecondAngle().first << ", " << triangle->getSecondAngle().second << "), third angle: (" << triangle->getThirdAngle().first << ", " << triangle->getThirdAngle().second << ")" << endl;
        }
        else if (dynamic_cast<Rectangle *>(shapes[i]) != nullptr)
        {
            auto *rectangle = dynamic_cast<Rectangle *>(shapes[i]);
            cout << "Rectangle: " << rectangle->name() << ", left up angle: (" << rectangle->getLeftUpAngle().first << ", " << rectangle->getLeftUpAngle().second << "), right down angle: (" << rectangle->getRightDownAngle().first << ", " << rectangle->getRightDownAngle().second << ")" << endl;
        }
    }
}

void printShapesPerimeter(const vector<Shape *> &shapes)
{
    cout << "Perimeter of each shape:\n" << endl;
    for (const auto &shape : shapes)
    {
        cout << shape->name() << ": " << shape->perimeter() << endl;
    }
}

void printSumPerimeters(const vector<Shape *> &shapes)
{
    double sum = 0.0;
    for (const auto &shape : shapes)
    {
        sum += shape->perimeter();
    }
    cout << "Sum of perimeters: " << sum << endl;
}

void sortShapesFromDownToUp(vector<Shape *> &shapes)
{
    sort(shapes.begin(), shapes.end(), [](const Shape *a, const Shape *b) {
        return a->perimeter() < b->perimeter();
    });
}

void deleteShapeByIndex(vector<Shape *> &shapes, int index)
{
    if (index >= 0 && index < shapes.size())
    {
        delete shapes[index];
        shapes.erase(shapes.begin() + index);
    }
}

void deleteShapeIfLessThanNum(vector<Shape *> &shapes, double personalPerimeter)
{
    shapes.erase(remove_if(shapes.begin(), shapes.end(), [personalPerimeter](const Shape *shape) {
        return shape->perimeter() > personalPerimeter;
    }), shapes.end());
}

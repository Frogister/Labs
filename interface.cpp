#include "interface.hpp"

void Menu::executeMenu()
{
    vector<Shape *> shapes;
    Menu::initializeMenuOptions();
    int choice = 0;
    do
    {
            Menu::callMenu();
            cin >> choice;
            try
            {
                if (Menu::menuOptions.find(choice) != Menu::menuOptions.end())
                {
                    Menu::menuOptions[choice](shapes);
                }
                else if (choice == 8)
                {
                    exit(0);
                }
                else
                {
                    cerr << "Non viable number, enter a number between 1 and 8";
                }
            }
            catch (const NonViableNumber &error)
            {
                cerr << error.what() << endl;
            }
            catch (const NotNumber &error)
            {
                cerr << error.what() << endl;
            }
            catch (const EmptyList &error)
            {
                cerr << error.what() << endl;
            }
            catch (const BadDeletionPerimeter &error)
            {
                cerr << error.what() << endl;
            }
            catch (const BadDeletionIndex &error)
            {
                cerr << error.what() << endl;
            }
    } while (choice != 8);
}

map<int, function<void(vector<Shape* > &)>> Menu::menuOptions;
map<int, function<void(vector<Shape* > &)>> Menu::shapesOptions;

void Menu::initializeShapesOptions() {
    shapesOptions[1] = &Menu::addCircle;
    shapesOptions[2] = &Menu::addTriangle;
    shapesOptions[3] = &Menu::addRectangle;
}

void Menu::addShape(vector<Shape *> &shapes)
{
    Menu::initializeShapesOptions();
    int choice;
    cout << "Choose type of shape: (type the number of the shape)" << endl;
    cout << "1. Circle" << endl;
    cout << "2. Triangle" << endl;
    cout << "3. Rectangle" << endl;
    cin >> choice;
    if (cin.fail())
    {
        throw NotNumber("Not number");
    }
    if (Menu::shapesOptions.find(choice) != Menu::shapesOptions.end())
    {
        Menu::shapesOptions[choice](shapes);
        cout << "Shape add successful\n";
    }
    else
    {
        throw NonViableNumber("Non viable number");
    }
}

void Menu::addCircle(vector<Shape *> &shapes)
{
    Menu::initializeShapesOptions();
    cout << "Enter shape name: " << endl;
    string name;
    cin >> name;
    cout << "Enter center: " << endl;
    pair<double, double> center = inputPoint();
    cout << "Enter radius: " << endl;
    double radius;
    cin >> radius;
    shapes.push_back(new Circle(name, center, radius));
}

void Menu::addTriangle(vector<Shape *> &shapes)
{
    Menu::initializeShapesOptions();
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
}

void Menu::addRectangle(vector<Shape *> &shapes)
{
    Menu::initializeShapesOptions();
    cout << "Enter shape name: " << endl;
    string name;
    cin >> name;
    cout << "Enter left up angle: " << endl;
    pair<double, double> leftUpAngle = inputPoint();
    cout << "Enter right down angle: " << endl;
    pair<double, double> rightDownAngle = inputPoint();
    shapes.push_back(new Rectangle(name, leftUpAngle, rightDownAngle));
}

void Menu::printShapesParameters(vector<Shape *> &shapes)
{
    listEmptinessCheck(shapes);
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

void Menu::printShapesPerimeter(vector<Shape *> &shapes)
{
    listEmptinessCheck(shapes);
    cout << "Perimeter of each shape:\n" << endl;
    for (const auto &shape : shapes)
    {
        cout << shape->name() << ": " << shape->perimeter() << endl;
    }
}

void Menu::printSumPerimeters(vector<Shape *> &shapes)
{
    listEmptinessCheck(shapes);
    double sum = 0.0;
    for (const auto &shape : shapes)
    {
        sum += shape->perimeter();
    }
    cout << "Sum of perimeters: " << sum << endl;
}

void Menu::sortShapesFromDownToUp(vector<Shape *> &shapes)
{
    listEmptinessCheck(shapes);
    sort(shapes.begin(), shapes.end(), comparePerimeters);
    cout << "Shapes' list sorted" << endl;
}

void Menu::deleteShapeByIndex(vector<Shape *> &shapes)
{
    listEmptinessCheck(shapes);
    int index = getDeletionIndex();
    if (index > shapes.size())
    {
        throw BadDeletionIndex("Position is more, than a list size");
    }
    delete shapes[index];
    shapes.erase(shapes.begin() + index);
    cout << "Shape deleted" << endl;
}

void Menu::deleteShapeIfLessThanNum(vector<Shape *> &shapes)
{
    listEmptinessCheck(shapes);
    double deletionValue = getDeletionPerimeter();
    shapes.erase(remove_if(shapes.begin(), shapes.end(), [deletionValue](const Shape *shape)
    {
        return shape->perimeter() > deletionValue;
    }), shapes.end());
}

void listEmptinessCheck(vector<Shape *> &shapes)
{
    if (shapes.empty())
    {
        throw EmptyList("The list is empty");
    }
}

bool comparePerimeters(Shape* a, Shape* b)
{
    return (a->perimeter() < b->perimeter());
}

void Menu::initializeMenuOptions() {
    menuOptions[1] = &Menu::addShape;
    menuOptions[2] = &Menu::printShapesParameters;
    menuOptions[3] = &Menu::printShapesPerimeter;
    menuOptions[4] = &Menu::printSumPerimeters;
    menuOptions[5] = &Menu::sortShapesFromDownToUp;
    menuOptions[6] = &Menu::deleteShapeByIndex;
    menuOptions[7] = &Menu::deleteShapeIfLessThanNum;
}

int getDeletionIndex()
{
    int indexChoice = 0;
    cout << "Enter position of shape, that you want to delete (1 for first position)" << endl;
    cin >> indexChoice;
    if (cin.fail())
    {
        throw NotNumber("Not number");
    }
    if (indexChoice < 1) {
        cout << "Position can not be less, than 1" << endl;
    }
    else {
        return indexChoice - 1;
    }
    return 0;
}

double getDeletionPerimeter()
{
    cout << "Enter maximum perimeter for shapes (shapes, that have perimeter larger, than this number, will be deleted)" << endl;
    int minPerimeter = 0;
    cin >> minPerimeter;
    if (cin.fail())
    {
        throw BadDeletionPerimeter("");
    }
    if (minPerimeter < 0)
    {
        cout << "Perimeter can not be less, than 0" << endl;
    }
    else
    {
        return minPerimeter;
    }
    return 0;
}

void Menu::callMenu()
{
    cout << "\nMenu: \n" << endl;
    cout << "1. Add a shape" << endl;
    cout << "2. Print numbered list of shapes with shape type and params" << endl;
    cout << "3. Print numbered list of shapes with shape type and perimeter" << endl;
    cout << "4. Print sum of the perimeters of all shapes" << endl;
    cout << "5. Sort shapes by ascending perimeters" << endl;
    cout << "6. Delete shape by number" << endl;
    cout << "7. Delete shape by perimeters that are larger, than entered one" << endl;
    cout << "8. Exit\n" << endl;
    cout << "Your choice: ";
}
#include "interface.hpp"

void Interface::executeInterface()
{
    exitInterface = 0;
    initializeInterfaceOptions();
    initializeFiguresOptions();
    int choice;
    do
    {
        callInterface();
        cin >> choice;
        cout << endl;
        try
        {
            callMethod(choice);
        }
        catch (const NonViableNumberException &error)
        {
            cerr << error.what() << endl;
        }
        catch (const NotNumberException &error)
        {
            cerr << error.what() << endl;
        }
        catch (const EmptyListException &error)
        {
            cerr << error.what() << endl;
        }
        catch (const BadDeletionPerimeterException &error)
        {
            cerr << error.what() << endl;
        }
        catch (const BadDeletionIndexException &error)
        {
            cerr << error.what() << endl;
        }
        catch (const InterfaceChoiceException &error)
        {
            cerr << error.what() << endl;
        }
        catch (const FigureNonViableException &error)
        {
            cerr << error.what() << endl;
        }
        catch (const exception &error)
        {
            cerr << error.what() << endl;
        }
    } while (exitInterface == 0);
}

void Interface::initializeFiguresOptions() {
    figuresOptions[1] = &Interface::addCircle;
    figuresOptions[2] = &Interface::addTriangle;
    figuresOptions[3] = &Interface::addRectangle;
}

void Interface::addTriangle() {
    Triangle *triangle = getTriangle();
    figures.push_back(triangle);
}

Triangle *Interface::getTriangle() {
    cout << "Enter figure name: " << endl;
    string name;
    cin >> name;
    cout << "Enter first angle: " << endl;
    Point firstAngle(inputValue<double>(), inputValue<double>());
    cout << "Enter second angle: " << endl;
    Point secondAngle(inputValue<double>(), inputValue<double>());
    cout << "Enter third angle: " << endl;
    Point thirdAngle(inputValue<double>(), inputValue<double>());
    return new Triangle(name, firstAngle, secondAngle, thirdAngle);
}

void Interface::addCircle() {
    Circle *circle = getCircle();
    figures.push_back(circle);
}

Circle *Interface::getCircle() {
    cout << "Enter Figure name: " << endl;
    string name;
    cin >> name;
    cout << "Enter center: " << endl;
    Point center(inputValue<double>(), inputValue<double>());
    cout << "Enter radius: " << endl;
    double radius = (inputValue<double>());
    return new Circle(name, center, radius);
}

void Interface::addRectangle() {
    Rectangle *rectangle = getRectangle();
    figures.push_back(rectangle);
}

Rectangle *Interface::getRectangle() {
    cout << "Enter figure name: " << endl;
    string name;
    cin >> name;
    cout << "Enter left up angle: " << endl;
    Point leftUpAngle(inputValue<double>(), inputValue<double>());
    cout << "Enter right down angle: " << endl;
    Point rightDownAngle(inputValue<double>(), inputValue<double>());

    return new Rectangle(name, leftUpAngle, rightDownAngle);
}

void Interface::addFigure() {
    cout << "Choose type of Figure: (type the number of the Figure)" << endl;
    cout << "1. Circle" << endl;
    cout << "2. Triangle" << endl;
    cout << "3. Rectangle" << endl;
    int choice;
    cin >> choice;
    if (cin.fail()) {
        throw NotNumberException(NOT_NUMBER);
    }
    callFigureMethod(choice);
    cout << "Figure add successful\n";
}

void Interface::printFiguresParameters()
{
    unsigned listCount = 1;
    listEmptinessCheck(figures);
    for (const auto &figure: figures) {
        std::cout << listCount << ". ";
        figure->showParameters();
        listCount++;
    }
}

void Interface::printFiguresPerimeter()
{
    unsigned listCount = 1;
    listEmptinessCheck(figures);
    cout << "Perimeter of each figure:\n" << endl;
    for (const auto &figure: figures) {
        std::cout << listCount << ". ";
        figure->showPerimeter();
        listCount++;
    }
}

void Interface::printSumPerimeters()
{
    listEmptinessCheck(figures);
    double sum = 0.0;
    for (const auto &Figure : figures)
    {
        sum += Figure->findPerimeter();
    }
    cout << "Sum of perimeters: " << sum << endl;
}

void Interface::sortFiguresFromDownToUp()
{
    listEmptinessCheck(figures);
    sort(figures.begin(), figures.end(), comparePerimeters);
    cout << "Figures' list sorted" << endl;
}

void Interface::deleteFigureByIndex()
{
    listEmptinessCheck(figures);
    int index = inputValue<int>();
    if (index > figures.size())
    {
        throw BadDeletionIndexException("Position is more, than a list size");
    }
    delete figures[index];
    figures.erase(figures.begin() + index);
    cout << "Figure deleted" << endl;
}

void Interface::deleteFigureIfLargerThanNum()
{
    listEmptinessCheck(figures);
    auto deletionValue = inputValue<double>();
    figures.erase(remove_if(figures.begin(), figures.end(), [deletionValue](Figure *Figure)
    {
        return Figure->findPerimeter() > deletionValue;
    }), figures.end());
}

void listEmptinessCheck(vector<Figure *> &Figures)
{
    if (Figures.empty())
    {
        throw EmptyListException(EMPTY_LIST);
    }
}

bool Interface::comparePerimeters(Figure* a, Figure* b)
{
    return (a->findPerimeter() < b->findPerimeter());
}

void Interface::initializeInterfaceOptions() {
    InterfaceOptions[1] = &Interface::addFigure;
    InterfaceOptions[2] = &Interface::printFiguresParameters;
    InterfaceOptions[3] = &Interface::printFiguresPerimeter;
    InterfaceOptions[4] = &Interface::printSumPerimeters;
    InterfaceOptions[5] = &Interface::sortFiguresFromDownToUp;
    InterfaceOptions[6] = &Interface::deleteFigureByIndex;
    InterfaceOptions[7] = &Interface::deleteFigureIfLargerThanNum;
    InterfaceOptions[8] = &Interface::exitInterfaceExecute;
}

void Interface::callMethod(const int& methodName) {
    auto it = InterfaceOptions.find(methodName);
    if (it != InterfaceOptions.end()) {
        (this->*(it->second))();
    } else {
        throw InterfaceChoiceException(INTERFACE_CHOICE_EXCEPTION);
    }
}

void Interface::callFigureMethod(const int &methodName) {
    auto it = figuresOptions.find(methodName);
    if (it != figuresOptions.end()) {
        (this->*(it->second))();
    } else {
        throw NonViableNumberException(NON_VIABLE_NUMBER);
    }
}

void Interface::callInterface() {
    cout << "\n\nInterface: \n" << endl;
    cout << "1. Add a figure" << endl;
    cout << "2. Print numbered list of figures with figure type and params" << endl;
    cout << "3. Print numbered list of figures with figure type and perimeter" << endl;
    cout << "4. Print sum of the perimeters of all figures" << endl;
    cout << "5. Sort figures by ascending perimeters" << endl;
    cout << "6. Delete figure by number" << endl;
    cout << "7. Delete figure by perimeters that are larger, than entered one" << endl;
    cout << "8. Exit\n" << endl;
    cout << "Your choice: ";
}

void Interface::exitInterfaceExecute() {
    exitInterface = 1;
}

template<typename T>
T Interface::inputValue()
{
    T value;
    cin >> value;
    if (cin.fail())
    {
        throw NotNumberException(NOT_NUMBER);
    }
    return value;
}
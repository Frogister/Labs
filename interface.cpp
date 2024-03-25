#include "interface.hpp"

void callMenu()
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
}

int getDeletionIndex()
{
    cout << "Enter position of shape, that you want to delete" << endl;
    int indexChoice = 0;
    while (true) {
        cin >> indexChoice;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter number" << endl;
        }
        if (indexChoice <= 0) {
            cout << "Position can not be less, than 1" << endl;
        }
        else {
            return indexChoice;
        }
    }
}

double getDeletionPerimeter() // Здесь есть проверка на число
{
    cout << "Enter maximum perimeter for shapes (shapes, that have perimeter larger, than that number, will be deleted)" << endl;
    int minPerimeter = 0;
    while (true) {
        cin >> minPerimeter;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter number" << endl;
        }
        if (minPerimeter < 0)
        {
            cout << "Perimeter can not be less, than 0" << endl;
        }
        else {
            return minPerimeter;
        }
    }
}

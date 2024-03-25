#include "interface.hpp"

void callMenu()
{
    cout << "Menu: \n" << endl;
    cout << "1. Add a shape" << endl;
    cout << "2. Print numbered list of shapes with shape type and params" << endl;
    cout << "3. Print numbered list of shapes with shape type and perimeter" << endl;
    cout << "4. Print sum of the perimeters of all shapes" << endl;
    cout << "5. Sort shapes by ascending perimeters" << endl;
    cout << "6. Delete shape by number" << endl;
    cout << "7. Delete shape by perimeters that are larger, than entered one" << endl;
    cout << "8. Exit" << endl;
}

int getDeletionIndex()
{
    cout << "Enter position of shape, that you want to delete" << endl;
    int indexChoice = 0;
    cin >> indexChoice;
    if (indexChoice < 0)
    {
        cout << "Position can not be less, than 0" << endl;
    }
    return indexChoice;
}

double getDeletionPerimeter()
{
    cout << "Enter minimal perimeter for shapes (shapes, that have perimeter less, than that number, will be deleted)" << endl;
    int minPerimeter = 0;
    cin >> minPerimeter;
    if (minPerimeter < 0)
    {
        cout << "Perimeter can not be less, than 0" << endl;
    }
    return minPerimeter;
}
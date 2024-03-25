#include "interface.hpp"
#include "shapes.hpp"

int inputChoice();
string error(int error);
void operation(int choice, vector<Shape *> &shapes);

int main()
{
    vector<Shape *> shapes;
    callMenu();
    int menuChoice = inputChoice();
    string errorMessage = error(menuChoice);
    if (errorMessage.empty() != 0)
    {
        cout << errorMessage << endl;
        return 0;
    }
    cout << "You have chosen this option: " << menuChoice << endl;
    operation(menuChoice, shapes);
    return 0;
}

int inputChoice()
{
    int choice = 0;
    cin >> choice;
    if (choice < 1 || choice > 8)
    {
        return 0;
    }
    else
    {
        return choice;
    }
}

string error(int errorCode)
{
    if (errorCode == 0)
    {
        return "Invalid option";
    }
    else
    {
        return "";
    }
}

void operation(int choice, vector<Shape *> &shapes)
{
    int indexDeletion = 0;
    double perimeterDeletion = 0;
    switch(choice) {
        case 1:
            addShape(shapes);
            break;
        case 2:
            printShapesParameters(shapes);
            break;
        case 3:
            printShapesPerimeter(shapes);
            break;
        case 4:
            printSumPerimeters(shapes);
            break;
        case 5:
            sortShapesFromDownToUp(shapes);
            break;
        case 6:
            indexDeletion = getDeletionIndex();
            deleteShapeByIndex(shapes, indexDeletion);
            break;
        case 7:
            perimeterDeletion = getDeletionPerimeter();
            deleteShapeIfLessThanNum(shapes, perimeterDeletion);
            break;
        case 8:
            exit(0);
    }
}
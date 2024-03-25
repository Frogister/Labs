#include "interface.hpp"
#include "shapes.hpp"

int inputChoice();
void operation(int choice, vector<Shape *> &shapes);

int main()
{
    vector<Shape *> shapes;
    while (true)
    {
        int menuChoice = 0;
        callMenu();
        cout << "Your choice: ";
        try
        {
            menuChoice = inputChoice();
        }
        catch (NotNumber &error)
        {
            cout << error.errorMessage() << endl;
        }
        catch (NonViableNumber &error)
        {
            cout << error.errorMessage() << endl;
        }
        operation(menuChoice, shapes);
    }
}

int inputChoice()
{
    int choice = 0;
    cin >> choice;
    if (cin.fail())
    {
        throw NotNumber("Not number");
    }
    if (choice < 1 || choice > 8)
    {
        throw NonViableNumber("Non viable number");
    }
    else
    {
        return choice;
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

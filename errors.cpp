#include "errors.h"
#include "logic.h"
#include <cctype>
#include <cmath>
#include <cstring>

int errorify(AppContext* context, const char* base) {
    // Здесь должна быть нормальная функция, из-за которой не должно нахер вылетать
    return 0;
}


const char* getErrorMessage(int codeValue) {
    switch(codeValue) {
    case 101:
        return "Недопустимый ввод для выбранной системы счисления";
        break;
    case 102:
        return "Входное значение выходит за пределы 4-байтового знакового числа";
        break;
    }
    return nullptr;
}

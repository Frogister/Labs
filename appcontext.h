#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "errors.h"
#include "list.h"

struct AppContext
{
    double min;
    double med;
    double max;
    int totalLines;
    int totalSuccessfulLines;
    int totalErrorLines;
    Errors errorCode;
    char filePath[LINE_MAX_LENGHT];
    int year;
    char region[LINE_MAX_LENGHT];
    float npg;
    float birthRate;
    float deathRate;
    float gdw;
    float urbanization;
    List* table;
    char columnIndex[LINE_MAX_LENGHT];
};

#endif // APPCONTEXT_H

#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"


enum Operation
{
    Initialization,
    CopyFilePath,
    CopyRegionName,
    CopyColumnIndex,
    GetData,
    Calculation
};

struct AppParams
{
    char filePath[LINE_MAX_LENGHT];
    char region[LINE_MAX_LENGHT];
    char column[LINE_MAX_LENGHT];
};

void doOperation(Operation operation, AppContext* context, AppParams* param);

#endif // ENTRYPOINT_H

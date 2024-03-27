#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"

enum Operation
{
    Translation,
    Initialization,
    Validation,
    SwapReplace
};

struct AppParams {
    const char* newValue;
};

void doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H

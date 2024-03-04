#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"

enum Operation
{
    Translation,
    Initialization,
    ErrorOperation,
    SwapOperation,
    CopyOperation
};

struct AppParams {
    const char* newValue;
    const char* fromBase;
    const char* toBase;
};

const char* doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H

#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#include "errors.h"

struct AppContext {
    Errors errorCode;
    const char* translatedValue;
    int fromBase;
    int toBase;
};

#endif // APPCONTEXT_H

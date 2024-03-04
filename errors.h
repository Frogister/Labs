#ifndef ERRORS_H
#define ERRORS_H

#include "appcontext.h"

int errorify(AppContext* context, const char* base);
const char* getErrorMessage(int codeValue);

#endif // ERRORS_H

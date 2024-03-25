#ifndef APPCONTEXT_H
#define APPCONTEXT_H

struct AppContext {
    int errorCode;
    const char* translatedValue;
    const char* fromBase;
    const char* toBase;
};

#endif // APPCONTEXT_H

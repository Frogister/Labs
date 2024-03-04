#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"

#define DEFAULT_VALUE 0
#define ERROR_LINE ""
#define BYTE_LIMIT 4
#define BIT_LIMIT (BYTE_LIMIT * 8 - 1)
#define BIT_LIMIT_OCTAL (BIT_LIMIT / 3 + 1)

long long stringToInt(const char *str);
char* intToString(long long value);
void copyToClipboard(AppContext* context);
void translate(AppContext* context, const char* newValue, const char* fromBase, const char* toBase);
void initialize(AppContext* context);
char* decimalToBinary(const char* decimalStr);
char* decimalToOctal(const char* decimalStr);
char* binaryToDecimal(const char* binaryStr);
char* binaryToOctal(const char* binaryStr);
char* octalToDecimal(const char* octalStr);
char* octalToBinary(const char* octalStr);

#endif // LOGIC_H

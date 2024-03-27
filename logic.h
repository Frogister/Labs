#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"

#define DEFAULT_VALUE 0
#define ERROR_LINE ""
#define BYTE_LIMIT 4
#define BIT_LIMIT_OVERALL BYTE_LIMIT * 8
#define BIT_LIMIT_BINARY BYTE_LIMIT * 8
#define BIT_LIMIT_OCTAL BIT_LIMIT_OVERALL / 3 + 1
#define BIT_LIMIT_DECIMAL BIT_LIMIT_OVERALL / 3
#define DECIMAL 10
#define BINARY 2
#define OCTAL 8

long long stringToInt(const char *str);
void validate(AppContext* context, const char* input);
char* intToString(long long value);
void copyToClipboard(AppContext* context);
void translate(AppContext* context, const char* newValue);
void initialize(AppContext* context);
void swapReplace(AppContext* context, const char* newValue);
char* decimalToAll(const char* decimalStr, int baseTo);
char* allToDecimal(const char* AllStr, int baseFrom);
char* binaryToOctal(const char* binaryStr);
char* octalToBinary(const char* octalStr);

#endif // LOGIC_H
